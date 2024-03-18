#include <stdlib.h>
#include <stdio.h>

int* allocInLib() {
    
    int *alloc_lib = (int*)malloc(sizeof(int));

    if (NULL == alloc_lib) {
        printf("Error allocating memory!");
        exit(0);
    }

    printf("Allocated memory for an integer at adress: %p!\n", alloc_lib);
    return alloc_lib;
}

void freeInLib( int* to_free ) {
    printf("Freed integer %d at adress: %p\n", *to_free, to_free);
    free(to_free);
}

