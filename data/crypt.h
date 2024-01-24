#ifndef CRYPT_H
#define CRYPT_H

#include <stdio.h>
#include <stdint.h>

void crypt(uint8_t *input, uint8_t *output, uint8_t *key, size_t data_size, size_t key_size);
void freeBuffer(uint8_t *buffer);
uint8_t *readFile(FILE *file, size_t *size);

#endif