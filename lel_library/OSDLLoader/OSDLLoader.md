# OSDLLoader

Cross-platform dynamic library loader.
Use [DLLoader](DLLoader.md) template.

## Example

lib\_source.cpp
```
OS_EXPORT_ATTRIBUTE int fsquare(int n)
{
  return n * n;
}
```

main.cpp
```
void main(int, char** av)
{
  lel::OSDLLoader loader{av[1]};

  if (!loader.isValid())
    return 1;

  auto symbol = loader.getSymbol<int(*)(int)>("fsquare");
  if (!symbol.isValid())
    return 1;
  std::cout << symbol(13) << "\n"; // Print 169
  return 0;
}
```
