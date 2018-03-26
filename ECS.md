# ECS

Lel's implementation of an Entity Component System.

## Specificity

  * It completely works with *shared libraries*.
  * Use a system of events.
  * Low risk of conflicting ID between systems, components or events.

## How it works ?

*In this section every path will be relative to the***executable**.

A Core class handles the whole ECS.
It will read a setup file named *./startup.ecs* and load all the system indicated
in this file.
The systems are searched in the folder *./lib/S* and in the order specified by
*./startup.ecs*.
Then all systems will execute their tasks in the same order as the load order.

## How to create shared libraries for this ECS ?

Thanks to the dynamic library loader API, a shared library will also load its
dependencies before. **All** shared libraries should ask the ID generators a new
ID in a function tagged as *constructor* (`__attribute__((constructor))` on
Linux or `DLLMain` on Windows).

I will named 'ecs objects' something that can be either a *system*, a
*component* or an *event*.
All 'ecs objects' *should* be inside of shared libraries.
When any 'ecs object' uses an other 'ecs objects', it *should* be linked against
it and **not use the other 'ecs objects' source code**.
**I recommend to not compile your 'ecs object' with the source files of an other
one as it will duplicate the code of the last one.**
