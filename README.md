Costa Rican Institute of Technology - Computer Engineering School  
Compilers and Interpreters  
Project 1 - Micro-Compiler  
Made by Luis Alvarado & Heiner León - August, 2015  

##Brief Information  

Micro is a simple language from the chapter 2 of the book *Crafting a compiler with C* by Charles N. Fischer and Richard J. LeBlanc Jr:

- The only data type is integer.
- All identifiers are implicitly declared and are no longer than 32 characters. Identifiers must begin with a letter and are composed of letters, digits, and underscores.
- Literals are strings of digits.
- Comments begin with -- and end at the end of the current line
- Statements types are:
    - Assignment:
        - ID:= Expression;
    - Input/Output:
        - read(List of IDs);
        - write(List of Expressions);
- Expression is an infix expression constructed from identifiers, literals, and the operators + and -; parentheses are also allowed.
- **begin**, **end**, **read**, and **write** are reserved words.
- Each statement is terminated by a semicolon (;). The body of a program is delimited by **begin** and **end**.
- A blank is appended to the right end of each source line; thus tokens may not extend across line boundaries.

##Compilation Instructions

*IMPORTANT: gcc compiler required*

1. Open a new terminal window in the project folder.
2. Use the makefile. Type in the terminal the command "make".

Once the program is compiled, the compiler will be in the folder 'dist'

##How to Use

1. Open a new terminal window in the dist folder of the project. (./dist).
2. Type in the terminal the compiler name (mcc) followed by the micro program which want to be compiled.  
    ```
    ./mcc programa1.micro
    ```
3. Once finished the compilation process, it will create a .asm file. Open it with [QtSPIM](http://spimsimulator.sourceforge.net) (or SPIM).  
