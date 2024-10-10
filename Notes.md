# Table Of Contents

1. [Macros](#macros)
    - [Sources](#sources)
2. [Pragmas](#pragmas)
    - [Sources](#sources)

### Objected-Orientated And Functional Languages
* That’s what the paradigm name literally says—an object-oriented language wants you to orient your code along the rows of types. A functional language instead encourages you to lump each column’s worth of code together into a function.
### Product Construction
* The goal is split the product's code so that it has a interpreter and a compiler. There is also a Virtual Machine, that will download a language a user wants to learn and sets everything up in a virtual machine

* *generate_code* will use **crow** as its web-framework and inja for the template engine. I have included notes in *generate_code.cc* that will need to be implemented 
* **Sources:**
    * **Crow user manual/releases**:
        - *https://github.com/CrowCpp/Crow/releases*
        - *https://crowcpp.org/master/*
    * **inja user manual**:
        - *https://github.com/pantor/inja*
### Macros
* They function like functions but they are `directives` meaning they are `pre-proccessed` before `compilation`
* Need to add `\` whenever you want a new line 
# Sources
* **macros**:
    * *https://cplusplus.com/doc/tutorial/preprocessor/*
    * *https://learn.microsoft.com/en-us/cpp/preprocessor/macros-and-cpp?view=msvc-170*
    * *https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170*
    * *https://learn.microsoft.com/en-us/cpp/standard-library/aligned-storage-class?view=msvc-170*
    * *https://stackoverflow.com/questions/45477355/difference-between-pragma-and-pragma-in-c*
    * *https://learn.microsoft.com/en-us/cpp/preprocessor/macros-c-cpp?view=msvc-170*
### Pragmas
* They can be embedded with macros and can parse a directive if needed

# Sources
* **Pragmas**:
* *https://en.cppreference.com/w/cpp/preprocessor/impl*
* **Translation Phase**:
    * *https://en.cppreference.com/w/cpp/language/translation_phases#Phase_3*
* **preproccessor replace**:
    * *https://en.cppreference.com/w/cpp/preprocessor/replace*
