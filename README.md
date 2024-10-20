### Interpreter
```
    This is a open source project that uses c++ to compile and run a custom programming language called tatical nuke.
```

# Table Of Contents

1. [Getting Started](#getting-started)
2. [Project Construction](#product-construction)
3. [What Is Tatical Nuke?](#what-is-tatical-nuke-?)
4. [Project Motivation and Potential Applications](#project-motivation-and-potential-applications)

### Getting Started:
* You can run tatical nuke by issuing `make` inside the root directory to generate `exec_interpreter`. If you are stuck on understanding tatical nuke's syntax, view the syntax located in `Code-Analysis`.
* If you're wanting to contribute to this project, here are a couple pointers:
    1. View the header file called `declarations.h`. It declares user types, and uses various template techniques that makes the codebase very organized.
    2. `definitions.h` is a header that contains all the defined types including types that require `extern`. Those are wrapped in `directives` to simply avoid `mulitple definitions` and or `undefined references`.

### Product Construction
* The goal is to create a hand-made interpreter that processes a language called Tatical Nuke written in c++. It will have the option to either be interpeted, (if the user chooses not manually manage memory), or compiled.

### What Is Tatical Nuke
* ***Pros***:
    * Tatical Nuke is a language that I implemented myself. It is inspired by low level languages and has a mixture of keywords from modern languages. 
    * It has a keyword called Query that is connected to a database. 
    * It is less strict than c++ but should offer the same performance.
    * To create classes you type `Radation`, `posioning` for functions, and `MUSHROOMCLOUD` to include other code. 
* ***Cons***:
* It will spam out random ASCI characters, and display TATICAL NUKE and delete itself, if the programmer messes up the syntax.
* That is it basically. 

### Project Motivation and Potential Applications

This project serves as my inaugural venture into crafting a customly made language inspired by c++. Beyond this primary goal, I'm eager to explore how the techniques I learn can be applied to various domains in software development and data processing. Some intriguing areas for future exploration include:

- Parsing complex configuration files
- Handling data serialization formats
- Creating and processing Domain-Specific Languages (DSLs)
- Advancing natural language processing capabilities
- Developing compiler front-ends
- Interpreting query languages
- Building code analysis and static checking tools
- Enhancing document processing systems

