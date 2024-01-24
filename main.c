#include <string.h>
#include <stdlib.h>
#include "data/crypt.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <output_file> <key_file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        printf("<input_file> can not equal <output_file>\n");
        return 1;
    }

    // Opening each file and checking if it is valid
    FILE *inputFile = fopen(argv[1], "rb");
    FILE *outputFile = fopen(argv[2], "wb");
    FILE *keyFile = fopen(argv[3], "rb");
    if (!inputFile || !outputFile || !keyFile) {
        perror("Error opening input files.\n");
        fclose(inputFile);
        fclose(outputFile);
        fclose(keyFile);
        return 1;
    }

    size_t dataSize, keySize;
    uint8_t *data_to_crypt = readFile(inputFile, &dataSize);
    uint8_t *key = readFile(keyFile, &keySize);
    uint8_t *crypted_data = (uint8_t *)malloc(dataSize); // New pointer for output data
    fclose(inputFile);
    fclose(keyFile);
    
    if (!data_to_crypt || !key || !crypted_data) {
        freeBuffer(data_to_crypt);
        freeBuffer(key);
        freeBuffer(crypted_data);
        fclose(outputFile);
        return 1; // Error reading file or memory allocation
    }

    // Crypt data and write to the output file
    crypt(data_to_crypt, crypted_data, key, dataSize, keySize);
    fwrite(crypted_data, 1, dataSize, outputFile);

    // Cleanup
    fclose(outputFile);
    freeBuffer(data_to_crypt);
    freeBuffer(key);
    freeBuffer(crypted_data);

    return 0;
}