# ECS

Lel's implementation of an Entity Component System (ECS) using C++17.

## What's an Entity Component System ?

An ECS is an architectural pattern that gives great flexibility to an object
using the 'Composition over inheritence' rule. This pattern is mostly used in
game development.

An *Entity* is an object which characteristics relies on the Components it has.

A *Component* should only be an object which holds data.

A *System* is a class which holds one logic and apply modifications on Components.
There is also often Event objects that Systems to communicate together.

## Features and Specificities

  * It can be extended at runtime with **shared libraries**.
  * System logic can be **changed at runtime**. You just need to *reload* it.
  * System can communicate together with **Events**.
  * Components, Systems and Events are in **shared libraries**.
  * [Customizable automatic ID attribution](#create-your-own-attribution-id-logic)
    for Entity, Components, Systems andEvents in the ECS. It can be customize and
    does not change how you check the ID of thoses objects.

    Only if you are using the provided class templates 'CRTPX' but you can
    implement your own automatic ID attribution logic.
  * It is possible to have more than 1 Core class. (Well what can be the usage
    of such feature ? I don't know...)
  * Its usage is not only restricted to game development.

## How does it work ?

*In this section every path will be relative to the* **executable**.

A Core class will act as a mediator and as a system manager for all the systems.
It will load, unload, reload systems. At the beginning of the program, it will
read a file named *./startup.ecs*.

All the shared libraries in this file will be loaded. The program will look in
the folder *./lib/S*. The order of the system in this file is IMPORTANT because
the execution of all the systems will follow the same order as specified in the
file.

When a System is loaded thanks to the dynamic loader its dependencies will also
be loaded (therefore dependent library will not follow the same logic). So the
Components and Events that a System use will also be loaded.

## How to create a System for this ECS ?

To create a valid System, the System **MUST** inherit from the interface IS.
A class template CRTPS<> is also provided that already implements some logics
related to the ECS operations. I recommend to make your Systems inherit from
this class template first.

Your System **MUST** only have a constructor which takes as parameter a
`lel::ecs::CoreProxy&` object. This object is essential if you need to do
anything that handle Core (Fire Events, create Entities, ...).

If you want your System to listen to Events, it **MUST** inherits from
`IEListener` and makes its method `isListener()` should return `true`.
To identify which events has been broadcast you can just check their IDs with
`<ExpectedEvent>::getEventID()`.

### General advices for System creation

Be careful of **global variables and static class members**.

**On Linux AND with g++** if those are exported, these variables can be flaged
as a **STB\_GNU\_UNIQUE** symbol. If it happens then your system **cannot be
reloaded**. `dlclose` will not unload the library code because of this
symbol. It means that the System behavior cannot be changed at runtime (you will
have to restart the program).

Other situations may lead to this but I do not know what are these but you can
check STB\_GNU\_UNIQUE symbol with the command `readelf -Ws <your library> |
grep UNIQUE`.

### When using the class template CRTPS<>

In one of your source file you will have to add the following macro
  `ECS_CREATE_IDSYSTEM_FULL(system_name, class_name)`
This macro will help you to generate the id of your system.

### Code sample

system.hh
```c++
#include "CoreProxy.hh"
// Inherit IEListener if the systeme needs to listen to events.
class MySystem : public CRTPS<MySystem>//, public lel::ecs::event::IEListener
{
public:
  MySystem(lel::ecs::CoreProxy& proxy);
  //All virtual methods needed.
};
```

system.cpp
```c++
#include "system.hh"
ECS_CREATE_IDSYSTEM_FULL(MySystem)

MySystem::MySystem(lel::ecs::CoreProxy& proxy)
  : CRTPS{proxy}
{}
```

### If you are not using the class template CRTPS<>

Be careful to **not export** the symbol that you use as your system ID if it is
a global or a static class member.

## How to create a Component or an Event for this ECS ?

You just have to implement the corresponding interface (IC for the Component and
IE for the Event).

There is also 2 class templates CRTPC<> for Component and CRTPE<> for Event that
implement logic related to the ECS operations and that can be inherited.

### General advices for Component and Event creation

Components and Events have no specific restriction like Systems.

## Usage

Now it is designed to be used with `cmake`. Just clone the repository and in
your CMakeLists.txt, use `add_subdirectory(ecs)` (or any other name you may have
given to the repository) and add the library as a dependency of your executable
`target_link_libraries(... ... ecs_core)`

### Example

You can clone an other repository which make use of the library here.
[https://github.com/vivi77/ECS\_sample]

## Incoming features

  * Control on Core startup through an interface to extend.
  * Asynchronous events.
  * Cross-compatibility with Windows.
  * System execution ordering.
  * Detection of libraries that contains STB\_GNU\_UNIQUE.
  * Detection of Component or Event update.

## Architecture

Here is a description of this [ECS architecture](doc/architecture.md).

## Create your own attribution ID logic

### When using CRTPX<> classes

To create your own attribution ID logic for a class, you **MUST**:

  * create a custom ID type. This is needed because templates are involved and
    using a same type will share the IDGenerator between all classes that use
    the same ID type.
    **NB**: This is not an error. You may want to use the same ID type for
    everything.
  * create an IDGenerator that inherit from
    `lel::ecs::utility::IIDGenerator<YourCustomIDType>`
  * create a **free function** with the following signature and symbol:
    ```c++
    template <>
    std::unique_ptr<lel::ecs::utility::IIDGenerator<`yourIDGenerator`>
    createGenerator();
    ```

### When **not using** CRTPX<> classes

You will have to think all the system but here are my advice:

  * Access to the class ID can be done through a method or a call to a static
    member function. So the ID will probably be a global or a static member
    variable.

    *NOTE: Be careful Systems have a different way to get their ID than
    Components and Events because they need to be reloadable. So exported global
    or static member class should be avoided.*
  * Your IDGenerator will *PROBABLY* need to be a **shared library**. If it is
    not in a shared library then the IDGenerator will be duplicated directly in
    the code of your shared library and so the ID that your Systems will get
    will be the first one that give a newly created IDGenerator.

### Alternative

Everything can be hard-coded... This is not mandatory to have this system. The
minimum required is that you should avoid duplicate ID.
