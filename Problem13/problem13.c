#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "problem13.h"

// Function for swapping two calibration parameters
void swap_parameters(CALIBRATION_PARAMETER *a, CALIBRATION_PARAMETER *b) {
    CALIBRATION_PARAMETER temp = *a;
    *a = *b;
    *b = temp;
}

// Returning the actual size of a field in the enum TYPE
size_t size_of_type(TYPE type) {

    size_t result;

    switch (type) {
        case 0:
            result = sizeof(int8_t);
            break;
        case 1:
            result = sizeof(int16_t);
            break;
        case 2:
            result = sizeof(int32_t);
            break;
        case 3:
            result = sizeof(bool);
            break;
        case 4:
            result = sizeof(float);
            break;
    }

    return result;
}

// Sorting the database based on the size of the type of parameters
void sort_by_type_size(CALIBRATION_PARAMETER database[]) {
    for (int i = 0; i < DATABASE_SIZE - 1; i++) {
        for(int j = 0; j < DATABASE_SIZE - i - 1; j++) {
            if (size_of_type(database[j].type) > size_of_type(database[j + 1].type)) {
                swap_parameters(&database[j], &database[j + 1]);
            }
        }
    }
}

// Sorting the database based on the order in the enum TYPE
void sort_by_type(CALIBRATION_PARAMETER database[]) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        for (int j = 0; j < DATABASE_SIZE - i - 1; j++) {
            if (database[j].type > database[j + 1].type) {
                swap_parameters(&database[j], &database[j + 1]);
            }
        }
    }
}

// Function for getting the value of a parameter
float get_value(CALIBRATION_PARAMETER database) {

    float result;

    switch (database.type) {
        case 0:
            result = (float)database.value.int8_value;
            break;
        case 1:
            result = (float)database.value.int16_value;
            break;
        case 2:
            result = (float)database.value.int32_value;
            break;
        case 3:
            result = (float)database.value.bool_value;
            break;
        case 4:
            result = (float)database.value.float_value;
            break;
    }

    return result;
}

// Sorting the database based on the value of the parameters
void sort_by_value(CALIBRATION_PARAMETER database[]) {
    for (int i = 0; i < DATABASE_SIZE - 1; i++) {
        for (int j = 0; j < DATABASE_SIZE - i - 1; j++) {
            if (get_value(database[j]) > get_value(database[j + 1])) {
                swap_parameters(&database[j], &database[j + 1]);
            }
        }
    }
}

// Initialization of the database
void initialize_database(CALIBRATION_PARAMETER database[]) {

    srand(time(NULL));

    for (int i = 0; i < DATABASE_SIZE; i++) {
        sprintf(database[i].name, "Parameter %d: ", i);
        
        switch (i % 5) {
            case INT8:
                database[i].type = INT8;
                database[i].value.int8_value = (rand() % 100) + 1;
                break;
            case INT16:
                database[i].type = INT16;
                database[i].value.int16_value = (rand() % 100) + 1;
                break;
            case INT32:
                database[i].type = INT32;
                database[i].value.int32_value = (rand() % 100) + 1;
                break;
            case BOOL:
                database[i].type = FLOAT;
                database[i].value.float_value = ((float)rand() / (float)(RAND_MAX)) * 100; 
                break;
            case FLOAT:
                database[i].type = BOOL;
                database[i].value.bool_value = rand() % 2;
                break;
            default:
                break;
        }
    }
}

// Function for displaying the database
void display_database(CALIBRATION_PARAMETER database[]) {
    for (int i = 0; i < DATABASE_SIZE; i++) {

        switch (database[i].type) {
            case INT8:
                printf("%s Type: %s, Value: %d\n", database[i].name, display_type(database[i].type), database[i].value.int8_value);
                break;
            case INT16: 
                printf("%s Type: %s, Value: %d\n", database[i].name, display_type(database[i].type), database[i].value.int16_value);
                break;
            case INT32:
                printf("%s Type: %s, Value: %d\n", database[i].name, display_type(database[i].type), database[i].value.int32_value);
                break;
            case BOOL:
                printf("%s Type: %s, Value: %s\n", database[i].name, display_type(database[i].type), database[i].value.bool_value ? "true" : "false");
                break;
            case FLOAT:
                printf("%s Type: %s, Value: %f\n", database[i].name, display_type(database[i].type), database[i].value.float_value);
                break;
            default:
                break;
        }
    }
    printf("\n");
}

// Function for displaying the type of a parameter as a string
const char* display_type(TYPE type) {

    const char* result;

    switch (type) {
        case 0:
            result = "INT8";
            break;
        case 1:
            result = "INT16";
            break;
        case 2:
            result = "INT32";
            break;
        case 3:
            result = "BOOL";
            break;
        case 4:
            result = "FLOAT";
            break;
        default:
            break;
    }

    return result;
}

int main() {
    CALIBRATION_PARAMETER database[DATABASE_SIZE];

    initialize_database(database);

    printf("--------- INITIAL DATABASE ---------\n");
    display_database(database);

    printf("--------- SORTED BY TYPE_SIZE ---------\n");
    sort_by_type_size(database);
    display_database(database);

    printf("--------- SORTED BY TYPE ---------\n");
    sort_by_type(database);
    display_database(database);

    printf("--------- SORTED BY VALUE ---------\n");
    sort_by_value(database);
    display_database(database);
}