#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "sample.h"


int main() {

    int *alloc_from_lib = allocInLib();

    *alloc_from_lib = 100;

    printf("Value %d was assignated at adress: %p \n", *alloc_from_lib, alloc_from_lib);

    freeInLib(alloc_from_lib); 

}