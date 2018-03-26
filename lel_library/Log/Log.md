# Log

Simple log class which log only when either macro *DEBUG* or *_DEBUG* are
defined.

## Usage

It take an `std::ostream` (output stream) as a reference.
By default it will be `std::cout`.

Just use the overload `operator<<` of this class to log anything that can be
printed.

## Example

```
void main()
{
  lel::Log{} << "Start of program\n";
  lel::Log l;
  l << "End of program\n";
  return 0;
}
```
