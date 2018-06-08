# ECS

Lel's implementation of an Entity Component System (ECS)

## What's an Entity Component System ?

An ECS is an architectural pattern that gives great flexibility to an object
using the 'Composition over inheritence' rule. This pattern is mostly used in
game development.
An Entity is an object which characteristics relies on the Components it has.
A System is a class which holds one logic and apply modifications on Components.
There is also often Event objects that Systems to communicate together.

## Features

  * It can be extended at runtime with *shared libraries*.
  * System logic can be **changed at runtime**. You just need to *reload* it.
  * System can communicate together with **Events**.
  * Every ECS objects (Entity Component System Event) are in *shared libraries*.
  * *Automatic ID attribution* for every classes in the ECS. It can be
    customize and does not change how you check the ID of a system.
    Only if you are using the provided class templates 'CRTPX' but you can
    implement your own automatic ID attribution system logic.
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
be loaded (therefore dependent library will not follow the same logic). So
Components and Events that a System use will also be loaded. That's why there is
no manager for Components and Events.

## How to create a System for this ECS ?

To create a valid System, the System **MUST** to inherit from the interface IS.
A class template CRTPS<> is also provided that already implements some logics
related to the ECS operations. I recommend to make your System inherits from
this class template first.
Your class **MUST** can only have a constructor which takes as parameter a
`lel::ecs::CoreProxy&` object. This object is essential if you need to do
anything that handle Core (Fire Events, create Entities, ...).
If you want your System to listen to Events, it MUST inherits from `IEListener`
and makes its method `isListener()` should return `true`.
To identify which events has been broadcast you can just check their IDs with
`<ExpectedEvent>::getEventID()`.

### General advices for System creation

Be careful of **global variables and static class members**.
**On Linux AND with g++** if those are exported, these variables can be flaged
as a **STB\_GNU\_UNIQUE** symbol. If it happens then your system **cannot be
reloaded** because `dlclose` will not unload the library code because of this
symbol. It means that the System behavior cannot be changed at runtime (you will
have to restart the program). Other situations may lead to this but I do not
know what are these but you can check it with the command `readelf -Ws <your
library>`.

### When using the class template CRTPS<>

In one of your source file you will have to add the following macro
  ECS\_CREATE\_IDSYSTEM\_FULL(system\_name, class\_name)
This macro will help you to generate the id of your system.

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

## Example

You can clone an other repository which make use of the library here.
[https://github.com/vivi77/ECS\_sample]

## Incoming features

  * Control on Core startup through an interface to extend.
  * Asynchronous events.
  * Cross-compatibility with Windows.
  * System execution ordering.
  * Detection of libraries that contains STB\_GNU\_UNIQUE.
  * Detection of Component or Event replacement.

## Architecture

There is the description of this [ECS architecture](doc/architecture.md).
