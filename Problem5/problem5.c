#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "problem5.h"

int serialize_data(COMPONENT_DATA *component_info, void* buffer, size_t buffer_size, size_t *result) {
    if (buffer_size < sizeof(int) + component_info->name_size + sizeof(size_t)) {
        printf("Buffer not big enough!");
        *result = 1;
        return 0;
    }
    
    // Copy into the buffer attributes field of the struct.
    memcpy(buffer, &(component_info->attributes), sizeof(int));
    
    // Offset for skipping 4 bytes in the buffer.
    int offset = sizeof(int);
    
    // Adding the name_size to the buffer
    memcpy(buffer + offset, &(component_info->name_size), sizeof(size_t));
    
    // Offset for skipping 8 bytes in the buffer.
    offset += sizeof(size_t);

    // Adding the name to the buffer.
    memcpy(buffer + offset, component_info->name, component_info->name_size);
    
    *result = 0;
    return sizeof(int) + sizeof(size_t) + component_info->name_size;
}

int deserialize_data(void* buffer, size_t buffer_size, COMPONENT_DATA* component_info, size_t* result) {
    
    // Copying first 4 bytes of the buffer into attributes.
    memcpy(&(component_info->attributes), buffer, sizeof(int));
    // Skipping (int) bytes to get name_size.
    int offset = sizeof(int);
    
    // Copying next (size_t) bytes of the buffer into name_size.
    memcpy(&(component_info->name_size), buffer + offset, sizeof(size_t));
    // Skipping next (size_t) bytes to get name.
    offset += sizeof(size_t);

    // Skipping (size_t) bytes to get name.
    memcpy(component_info->name, buffer + offset, component_info->name_size);
    //printf("%s %zu", component_info->name, component_info->name_size);
    
    *result = 0;
    return sizeof(int) + sizeof(size_t) + component_info->name_size; 
}

void print_serialize_deserialize() {
    
    //Initialize result with 1 (0 is for succes)
    size_t result = 1;

    size_t result2 = 1;
	
	COMPONENT_DATA component_info = {
        .attributes = 5,
        .name = "Hello World!",
        .name_size = strlen(component_info.name) + 1
    };

    COMPONENT_DATA component_info2 = {
        .attributes = 6,
        .name = "Another string!1234bhbh",
        .name_size = strlen(component_info2.name) + 1
    };

    size_t buffer_size2 = sizeof(int) + sizeof(size_t) + component_info2.name_size;
    
    size_t buffer_size = sizeof(int) + sizeof(size_t) + component_info.name_size;

    char* buffer = (char*)malloc(buffer_size);
    if (NULL == buffer) {
        printf("Error allocating memory!");
        return;
    }
    
    char* buffer2 = (char*)malloc(buffer_size);
    if (NULL == buffer) {
        printf("Error allocating memory!");
        return;
    }
    
    int serialize = serialize_data(&component_info, buffer, buffer_size, &result);

    int serialize2 = serialize_data(&component_info2, buffer2, buffer_size2, &result2);
    
    printf("Serialize (return): %d\n", serialize);
    printf("Serialize (result): %zu\n", result);

    COMPONENT_DATA component_info_deserialize;
    component_info_deserialize.name_size = buffer_size;
    component_info_deserialize.name = (char*)malloc(component_info.name_size);

    // for (int i = 0; i < buffer_size; i++) {
    //     printf("%x ", buffer[i]);
    // }
    // 48 65 6C 6C 6F 20 57 6F 72 6C 64 21

    int deserialize = deserialize_data(buffer, buffer_size, &component_info_deserialize, &result);
    
    printf("Deserialize (return): %d\n", deserialize);
    printf("Deserialize (result): %zu\n", result);
    printf("Deserialize (content): %d %s %zu\n", component_info_deserialize.attributes, component_info_deserialize.name, component_info_deserialize.name_size);
   
    deserialize = deserialize_data(buffer2, buffer_size2, &component_info_deserialize, &result);
    
    printf("Deserialize (return): %d\n", deserialize);
    printf("Deserialize (result): %zu\n", result);
    printf("Deserialize (content): %d %s %zu\n", component_info_deserialize.attributes, component_info_deserialize.name, component_info_deserialize.name_size);
    component_info_deserialize.name = "hello";
    printf("Deserialize (content): %d %s %zu\n", component_info_deserialize.attributes, component_info_deserialize.name, component_info_deserialize.name_size);

    free(buffer);

}

int main() {
    
    print_serialize_deserialize();
}