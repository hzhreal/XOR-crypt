#include <stdlib.h>
#include "crypt.h"

// Function to perform XOR encryption or decryption on two uint8_t arrays of potentially different sizes
void crypt(uint8_t *input, uint8_t *output, uint8_t *key, size_t data_size, size_t key_size) {
    for (size_t i = 0; i < data_size; ++i) {
        output[i] = input[i] ^ key[i % key_size];
    }
}

void freeBuffer(uint8_t *buffer) {
    free(buffer);
}

uint8_t *readFile(FILE *file, size_t *size) {
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *buffer = (uint8_t *)malloc(*size);
    if (!buffer) {
        perror("Memory allocation error.\n");
        return NULL;
    }

    fread(buffer, 1, *size, file);

    return buffer;
}