#include <stdint.h>
#include <stdbool.h>

#define DATABASE_SIZE 10

typedef enum Type {
    INT8,
    INT16,
    INT32,
    BOOL,
    FLOAT
}TYPE;

typedef union Value {
    int8_t int8_value;
    int16_t int16_value;
    int32_t int32_value;
    bool bool_value;
    float float_value;
}VALUE;

typedef struct Database {
    char name[50];
    TYPE type;
    VALUE value;
}CALIBRATION_PARAMETER;

extern const char* display_type(TYPE type);

extern void display_database(CALIBRATION_PARAMETER database[]);

extern void initialize_database(CALIBRATION_PARAMETER database[]);

extern void swap_parameters(CALIBRATION_PARAMETER *a, CALIBRATION_PARAMETER *b);

extern size_t size_of_type(TYPE type);

extern void sort_by_type_size(CALIBRATION_PARAMETER database[]);

extern void sort_by_type(CALIBRATION_PARAMETER database[]);

extern float get_value(CALIBRATION_PARAMETER database);

extern void sort_by_value(CALIBRATION_PARAMETER database[]);