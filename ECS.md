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
  * It is possible to have more than 1 Core class. (Well what can be the usage
    of such feature ? I don't know...)
  * Its usage is not only restricted to game development.

## How does it work ?

*In this section every path will be relative to the***executable**.

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

To create a valid System, the System needs to inherit from the interface IS. A
class template CRTPS<> is also provided that already implements some logics
related to the ECS operations. I recommend to make your System inherits from
this class template first.

### General advices

Be careful of **global variables and static class members**.
**On Linux AND with g++** if those are exported, these variables can be flaged
as a **STB\_GNU\_UNIQUE** symbol. If it happens then your system **cannot be
reloaded** because `dlclose` will not unload the library code because of this
symbol. It means that the System behavior cannot be changed at runtime (you will
have to restart the program).

### When using the class template CRTPS<>

In one of your source file you will have to add the following macro
  ECS\_CREATE\_IDSYSTEM\_FULL(system\_name, class\_name)
This macro will help you to generate the id of your system.

### If you are not using the class template CRTPS<>

Be careful to **not export** the symbol that you use as your system ID.

## How to create a Component or an Event for this ECS ?

You just have to implement the corresponding interface (IC for the Component and
IE for the Event).
There is also 2 class templates CRTPC for Component and CRTPE for Event that
implement logic related to the ECS operations and that can be inherited.

### General advices

Components and Events have no specific restriction like Systems.

## Usage

## Incoming features

  * Control on Core startup through an interface to extend.
  * *Asynchronous events* because actual events are all synchronous.
  * Detection of library that contains STB\_GNU\_UNIQUE
