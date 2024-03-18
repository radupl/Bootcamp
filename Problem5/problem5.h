#define DBG_PRINT(debug_level, format, ...) \
    printf("[%d][%s][%s]", debug_level, format, __VA_ARGS__);

typedef struct _COMPONENT_DATA {
    int attributes;
    char *name;
    size_t name_size;
} COMPONENT_DATA, *PCOMPONENT_DATA;

extern int serialize_data(COMPONENT_DATA *component_info, void* buffer, size_t buffer_size, size_t *result);

extern int deserialize_data(void* buffer, size_t buffer_size, COMPONENT_DATA* component_info, size_t* result);