#include <stdint.h>
#include <stdio.h>

void print_bits(uint32_t number) {
    uint8_t bit;
    while (number) {
        bit = number & 1;
        printf("%d", bit);
        number >>= 1;
    }
    printf("\n");
}

/*uint32_t print_bits_MSB(uint32_t number) {
    uint8_t bit;
    size_t number_of_bits = sizeof(number) * 8;
    for (int i = 0; i < number_of_bits; i++) {
        printf("%d", (number >> (number_of_bits - i)) & 1);
    }
    printf("\n");
} */

int main() {
	print_bits(18);
    //print_bits_MSB(11);
}