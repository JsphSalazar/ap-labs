# Lab 0.2 - Strings Manipulation Library


 Follow the instructions in the attached link
- Submit your code to your ap-labs github repository in the labs/lab0.2/ directory.
- Add a README.md file with description and instructions to compile and execute your program.

<https://softfire-143705.appspot.com/hello-c-world/03-linking.slide#6>


- Implement a library for string manipulation strlib.c with the following functions:

    int strlen(char *str)
    *char stradd(char *origin, char *addition)
    int strfind(char *origin, char *substr)


## To Compile
Use the following commands for compilation and linking

    gcc -c str-main.c -o str-main.o
    gcc -c strlib.c -o strlib.o
    gcc str-main.o strlib.o -o str-final.o



