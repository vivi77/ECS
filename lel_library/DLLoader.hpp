#pragma once

#include <unordered_map>
#include "DLLoader_concept.hpp"

namespace lel
{
  /** @brief Class which handles a dynamic libraries
   *
   *  @param <OS> A class with OS related type alias and functions
   */
  template <typename OS>
  class DLLoader
  {
    using Handle_t = typename OS::Handle;
    using Symbol_t = typename OS::Symbol;
    using LoadOption = typename OS::LoadOption;

  public:
    using LibPath = const char*;

  private:
    /** @brief A symbol extracted from a library
     */
    template <typename T>
    class Symbol
    {
    public:
      Symbol(Symbol_t symbol, const bool validity = true)
        : _symbol{symbol}
        , _validity{validity}
      {}

      /** @brief Check if the symbol is usable
       */
      bool isValid() const noexcept
      {
        return _validity;
      }

      /** @brief Convert the symbol to the specified type
       */
      operator T()
      {
        return OS::template convertSymbol<T>(_symbol);
      }

      /** @brief Return an invalid symbol
       */
      static Symbol getInvalidSymbol()
      {
        return {nullptr, false};
      }

    private:
      Symbol_t _symbol; /**< Store a symbol */
      bool _validity; /**< Indicate if the symbol is valid */
    };

    /** @brief Count how many times a library has been open
     */
    class RefCounter
    {
    public:
      using CounterType = size_t;
      using HashKey = size_t;

    private:
      RefCounter() = default;

    public:
      static RefCounter& getSingleton()
      {
        static RefCounter refCounter{};
        return refCounter;
      }

      static constexpr HashKey getDefaultHash()
      {
        return 0;
      }

      /** @brief Reference the library
       *
       *  @param libPath Something to reference
       *
       *  @return A key which reference the library
       *
       *  @remarks If it is already referenced, this function will have no effect
       */
      HashKey addRef(LibPath libPath) noexcept
      {
        const auto libHash = std::hash<LibPath>{}(libPath);
        auto it = _refs.find(libHash);

        if (it == _refs.end())
          _refs.insert(std::make_pair(libHash, 1));
        return libHash;
      }

      /** @brief Add 1 to the counter of a referenced library
       *
       *  @param libHash Hash of a referenced library
       */
      void incRef(const HashKey libHash) noexcept
      {
        auto it = _refs.find(libHash);

        if (it != _refs.end())
          ++it->second;
      }

      /** @brief Remove 1 to the count reference of the parameter. Delete it when
       * it reaches 0
       *
       *  @param libHash Hash of the library. (those one returned by addRef)
       *
       *  @return `true` when the reference has been removed (ie. counter reaches
       *  0). Else `false` (even when the reference is not found).
       */
      bool removeRef(const HashKey libHash) noexcept
      {
        auto it = _refs.find(libHash);

        if (it != _refs.end())
        {
          --it->second;
          if (it->second == 0)
          {
            _refs.erase(it);
            return true;
          }
        }
        return false;
      }

      /** @brief Get the number of usage of a library
       *
       *  @param libHash Hash of a given library.
       *
       *  @return Number of usage of a library, return 0 if the library is not
       */
      CounterType getCountUsage(const HashKey libHash) const noexcept
      {
        auto it = _refs.find(libHash);
        return it == std::end(_refs) ? 0 : it->second;
      }

    private:
      std::unordered_map<HashKey, CounterType> _refs; /**< Referencer */
    };

  public:
    DLLoader() = default;

    DLLoader(LibPath path)
    {
      loadLibrary(path);
    }

    DLLoader(LibPath path, const LoadOption option)
    {
      loadLibrary(path, option);
    }

    DLLoader(const DLLoader& rhs)
      : _handle{rhs._handle}
      , _libHash{rhs._libHash}
    {
      RefCounter::getSingleton().incRef(_libHash);
    }

    DLLoader(DLLoader&& rhs)
      : _handle{std::move(rhs._handle)}
      , _libHash{std::move(rhs._libHash)}
    {
      rhs._invalidate();
    }

    ~DLLoader()
    {
      _close();
    }

    DLLoader& operator=(const DLLoader& rhs)
    {
      if (this != &rhs)
      {
        _handle = rhs._handle;
        _libHash = rhs._libHash;
        RefCounter::getSingleton().addRef(_libHash);
      }
      return *this;
    }

    DLLoader& operator=(DLLoader&& rhs)
    {
      if (this != &rhs)
      {
        _handle = std::move(rhs._handle);
        _libHash = std::move(rhs._libHash);
        rhs._invalidate();
      }
      return *this;
    }

    /** @brief Check if the loader can be used
     */
    bool isValid() const noexcept
    {
      return _handle != OS::NULL_HANDLE;
    }

    /** @brief Load a dynamic library
     *
     *  @param libPath Path to the library
     *  @param option Option to send to the library loader
     *
     *  @return `true` on success, else `false`
     *
     *  @remarks This does not load a new library if it handles one already. If it
     *  replaces the old one with the new one, it mostly will break the program
     */
    bool loadLibrary(LibPath libPath, const std::optional<LoadOption> option = std::nullopt) noexcept
    {
      if (isValid()) //Check if the object handles one library
        return false;

      if (option.has_value())
        _handle = OS::loadLibrary(libPath, option.value());
      else
        _handle = OS::loadLibrary(libPath);

      if (!isValid())
        return false;
      _libHash = RefCounter::getSingleton().addRef(libPath);
      return true;
    }

    /** @brief Unload the current dynamic library.
     *
     *  @remarks Nothing happen if it handles any library
     */
    void unloadLibrary() noexcept
    {
      if (!isValid())
        return ;
      _close();
      _invalidate();
    }

    /** @brief Extract a symbol from a dynamic library.
     *
     *  @param symName Symbol name
     *
     *  @return A symbol class
     */
    template <typename T>
    Symbol<T> getSymbol(const char* symName)
    {
      if (!isValid())
        return Symbol<T>::getInvalidSymbol();
      Symbol_t rawSym = OS::getSymbol(_handle, symName);
      return rawSym == nullptr ?
        Symbol<T>::getInvalidSymbol() :
        Symbol<T>{rawSym};
    }

    /** @brief Get the last error that happened
     */
    const char* getLastError() const noexcept
    {
      return OS::getLastError();
    }

    /** @brief Get the number of usage of a library.
     *
     *  @return Number of usage of a library
     */
    typename RefCounter::CounterType countUsage() const noexcept
    {
      return RefCounter::getSingleton().getCountUsage(_libHash);
    }

    /** @brief Check if a library has already been loaded
     *
     *  @param libPath Path to the library.
     *
     *  @return true if it is already loaded
     */
    static bool isLibraryLoaded(const char* libPath) noexcept
    {
      return OS::isLibraryLoaded(libPath);
    }

  private:
    Handle_t _handle = OS::NULL_HANDLE; /**< Library handler */
    typename RefCounter::HashKey _libHash = RefCounter::getDefaultHash(); /**< For reference counting */

    /** @brief Close properly the library
     */
    void _close() noexcept
    {
      if (RefCounter::getSingleton().removeRef(_libHash))
        OS::unloadLibrary(_handle);
    }

    /** @brief Invalidate the handler
     */
    void _invalidate()
    {
      _handle = OS::NULL_HANDLE;
      _libHash = RefCounter::getDefaultHash();
    }

    static_assert(concept::DLLoader<OS>::value);
  };
} /* !lel */
