# Pallox
A lightweight region-based, semi-automatic memory manager

**Compilation**: ``clang $(find ./src -name "*.c") -I./include/pallox && ./a.out``

While it would be easy to implement a static registry inside a "gc_handler(void)" function, the norm prevents me from doing that which makes it extremely unconvenient (passing a registry_t * variable to every single function).

Therefore, the better approach would be to use macros with compiler attributes.
However, while it is way more convenient, this seems more like a GC than an arena memory manager.

Here would be a header for that approach:
```c
#ifndef ROUTINES_H_
    #define ROUTINES_H_
    =======[ LIBRARIES ]=======
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <string.h>

    =======[ MODIFIED DATA TYPES ]=======
    #define _CHAR __attribute__((cleanup(f_ptr))) char *
    #define _ARR __attribute__((cleanup(f_arr))) char **
    #define _FILE __attribute__((cleanup(f_file))) FILE *

    =======[ CONSTRUCTORS ]=======
    #define FILE(name, path, p) _FILE name = fopen(path, p)
    #define STRING(name, size) _CHAR name = malloc(size)
    #define STRDUP(name, str) _CHAR name = strdup(str)
    #define CHAR_ARR(name, size) _ARR name = calloc(size + 1, sizeof(char *))

=======[ PROTOTYPES ]=======
void f_arr(char ***ptr);
void f_ptr(char **ptr);
void f_file(FILE **file);

#endif
```
