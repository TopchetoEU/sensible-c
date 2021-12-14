# Sensible C (C+)
A transpiled to C language

## What is it?
A language, which just adds some features to C, making it a much easier to code on C. The language still translates to C

## Why use it?
Basically, it adds some much needed functionality to C (like extention functions, namespaces, clearer typing, etc.), while still keeping the low-level nature of C. It is a great choice for anyone that actually wants to get some job done.

## What does it add?
- Namespaces - Basically helps you keep your code organised, while still keeping it usable for C files. A namespace is defined similarly to C++. The namespaces are hierarchical (described by the `::` operator, for example `foo::bar::baz(int, int)`). A namespace may only contain declarations and definitions. A namespace may be implied if `using ...;` is used
- Extention functions - They add the ability to emulate the so-called methods, by being able to define an extention method. This is done by declaring it in the following manner: `this thistype returntype(...);`. The specified extended type may be `void`, in which case, any value is accepted. After that, you can call on any value of the specified type the extention in this way: `foo.baz(...)`. Inside the extention method, there will be the `this` keyword available, but remember, it still may be `NULL`, since this is just a function, that has nothing to do with the value itself.
- Structure functions - Very similar to extention functions, and they act similarly to the well-known methods. Still, they are a far cry from the functions, since they still can be called on a `NULL` pointer, so be careful and make the appropriate checks. A function may call `this.func(...)`, where `func` is another structure function. `this` is not mandatory, but certainly reccomended for clearer and collisionless code.
- Better typing - In regular C, when you write the following: `struct foo { int a; };`, this creates the structure globally, and requires the programmer to write `struct foo` anywhere he wants to use the type, which requires more code and can turn out to be a major annoyance. C++ has solved this issue, but C hasn't. In C+, structures may be either: type specifiers - then they MUST be annonymous (if it has a name, it will be rejected), and type declarations - then they MUST have a name (if they don't have one, the declaration will be rejected). In that case, syntax like this:
```c
struct foo {
    int bar;
} baz;

struct foo myFoo;
```
Is still entirely valid, since the transpiler won't add the structure to its record, but still will output it, and when the `struct foo` type specifier is encountered, it will be outputted, no questions asked.
- Better declaration syntax - Basically you now don't need to add semicolons to the end of declarations, except for field/variable declarations
- Inline code - You can write code directly in the global scope of the file, and the code will automatically be encapsulated in an `int main(int argc, const char* argv[])` scope, so be careful with multiple files and write inline code only in a single file. This is a feature for simpler projects
- Better importing - Makes the `import ...;` syntax valid syntax, being replaced with `#include "..."`, so still a file should be specified after the `import` keyword

## Contribute
The project is still in the idea stage, so any help on it is well appreciated. Please, do log issues, since that helps me fix annoying bugs before they 'bug' me. 