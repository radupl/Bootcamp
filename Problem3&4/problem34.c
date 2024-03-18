#include <stdio.h>
#include <stdarg.h>

#define DBG_INFO 1
// Macro for debugging [Problem 4]
#define DBG_PRINT(debug_level, format, ...) \
    printf("[%d][%s][%d] " format "\n", debug_level, __FILE__, __LINE__, __VA_ARGS__); 

typedef void (*CallbackFunction)(int progress, int data_size);

void progress_callback(int index, int data_size) {
    int progress = (index + 1) * 100 / data_size;
    printf("%d%%\n\n", progress);
}

void handle_data(CallbackFunction progress_callback, char* data, int data_size) {
    for (int i = 0; i < data_size; i++) {
        printf("%c\n", *(data + i));
        progress_callback(i, data_size);
    }
}

int main() {

    char data[] = "Hello World2!";
    int data_size = sizeof(data) - 1;
    DBG_PRINT(DBG_INFO, "My value is %d and %s", 5, "something");
    handle_data(progress_callback, data, data_size);
    return 0;
}