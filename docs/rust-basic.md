# Rust basics

encase you need help understanding rust syntax. Also I used a some of **Fireship**'s video called **Rust in 100 seconds** to help me understand rust better. So if it sounds like I'm copying word for word I apologize

## What to know beforehand?

Rust is a memory-safe compilied programming language design for building memory-safe and high performance applications, the language can work with C code via linkings. 

## Variables

Every value in a rust application is assigned to single variable known as its owner. When that memory goes out of scope

There are two ways of declaring variables in rust using **let** or **let mut** i'll explain them from what I understand 

### Let 

the **let** keyword declares a variable that cannot be modified after defining it's value. Here's an example

```rust
let size = 5;
```

what you cannot do is this

```rust
let size = 5;
size = 10; // Not allowed 
```

### Let mut

the **let mut** keywords declares a variable is **mutable** thus can be changed. If you are confused what **mutable** means I'll explain it you. **mutable** basically means able to change, so a variable can it value though the runtime of the program after it's been created. Here's an example let's say you don't like a certain band anymore

```rust 
let mut band = "I Prevail";
band = "Avenged Sevenfold"; // Allowed
```