#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint32_t get_value(char *buffer, int offset, size_t buffer_size) {
    uint32_t result;

	// Checking if function tries to read from an address beyond the buffer.
	if (buffer_size < offset + sizeof(uint32_t)) {
		return 0;
	}

	// Copying the uint32 value from address buffer + offset in result.
	memcpy(&result, buffer + offset, sizeof(uint32_t));
	return result;
}

int main() {
	
    char* str = "Hello World!\n";
    uint32_t value_of_offset = get_value(str, 9, strlen(str));

	// Print value returned by get_value.
    printf("%d\n", value_of_offset);
}