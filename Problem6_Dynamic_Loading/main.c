#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>


int main() {

    void *handle_alloc;
    void *handle_free;
    int* (*my_malloc)(void);
    void (*my_free)( int* );
    char *error;

    handle_alloc = dlopen("/home/uig70502/Documents/Probleme/My_library/libsample.so", RTLD_LAZY);
    if (!handle_alloc) {
        printf("Error opening library!");
        dlerror();
        exit(0);
    }

    handle_free = dlopen("/home/uig70502/Documents/Probleme/My_library/libsample.so", RTLD_LAZY);
    if (!handle_free) {
        printf("Error opening library!");
        dlerror();
        exit(0);
    }

    my_malloc = dlsym(handle_alloc, "allocInLib");
    if ( NULL != (error = dlerror()) ) {
        printf("Error handling allocInLib symbol!");
        exit(0);
    }

    my_free = dlsym(handle_free, "freeInLib");
    if ( NULL != (error = dlerror()) ) {
        printf("Error handling freeInLib symbol!");
        exit(0);
    }

    // Allocating memory for the integer and assigning value.
    int* result = (*my_malloc)();
    *result = 100;
    printf("Value %d was asignated to memory adress: %p\n", *result, result);

    // Freeing memory allocated for the integer.
    (*my_free)(result);

    dlclose(handle_alloc);
    dlclose(handle_free);
}