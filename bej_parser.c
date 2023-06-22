#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Structure to represent a string in BEJ format
typedef struct {
    uint32_t length; // Length of the string
    char* data;      // Pointer to character data
} BEJString;

// Structure to represent a key-value map in BEJ format
typedef struct {
    uint32_t count;      // Number of key-value pairs
    BEJString* keys;     // Array of keys
    uint32_t* values;    // Array of values
} BEJMap;

// Function to write a BEJString structure to a file
void write_string(FILE* file, BEJString bejString) {
    fwrite(&bejString.length, sizeof(uint32_t), 1, file); // Write string length
    fwrite(bejString.data, 1, bejString.length, file);    // Write string data
}

// Function to write a BEJMap structure to a file
void write_map(FILE* file, BEJMap bejMap) {
    fwrite(&bejMap.count, sizeof(uint32_t), 1, file); // Write number of key-value pairs

    for (uint32_t i = 0; i < bejMap.count; i++) {
        write_string(file, bejMap.keys[i]);                      // Write each key
        fwrite(&bejMap.values[i], sizeof(uint32_t), 1, file);    // Write each value
    }
}

// Function to write a BEJMap structure to a BEJ binary file
void write_bej(const char* filename, BEJMap bejMap) {
    FILE* file = fopen(filename, "wb"); // Open file in binary write mode
    if (file == NULL) {
        printf("Failed to open BEJ file for writing.\n");
        return;
    }

    uint8_t valueType = 0x02;
    fwrite(&valueType, sizeof(uint8_t), 1, file); // Write value type to indicate BEJMap
    write_map(file, bejMap);                      // Write the BEJMap structure to the file

    fclose(file); // Close the file
}

// Function to parse a BEJString structure from a file
void parse_string(FILE* file, BEJString* bejString) {
    fread(&bejString->length, sizeof(uint32_t), 1, file);        // Read string length
    bejString->data = malloc(bejString->length + 1);             // Allocate memory for string data
    fread(bejString->data, 1, bejString->length, file);          // Read string data
    bejString->data[bejString->length] = '\0';                   // Append null character to make it a valid C string
}

// Function to parse a BEJMap structure from a file
void parse_map(FILE* file, BEJMap* bejMap) {
    fread(&bejMap->count, sizeof(uint32_t), 1, file);                // Read number of key-value pairs
    bejMap->keys = malloc(bejMap->count * sizeof(BEJString));        // Allocate memory for key array
    bejMap->values = malloc(bejMap->count * sizeof(uint32_t));       // Allocate memory for value array

    for (uint32_t i = 0; i < bejMap->count; i++) {
        parse_string(file, &bejMap->keys[i]);                          // Parse each key
        fread(&bejMap->values[i], sizeof(uint32_t), 1, file);          // Read each value
    }
}

// Function to parse a BEJ binary file and convert it to JSON
void parse_bej(const char* input_filename, const char* output_filename) {
    FILE* file = fopen(input_filename, "rb"); // Open file in binary read mode
    if (file == NULL) {
        printf("Failed to open BEJ file for reading.\n");
        return;
    }

    uint8_t valueType;
    fread(&valueType, sizeof(uint8_t), 1, file); // Read the value type

    if (valueType == 0x02) {
        BEJMap bejMap;
        parse_map(file, &bejMap); // Parse the BEJMap structure from the file

        char jsonFilename[strlen(output_filename) + 5]; // filename + ".json" + '\0'
        sprintf(jsonFilename, "%s.json", output_filename); // Construct the JSON file name

        FILE* jsonFile = fopen(jsonFilename, "w"); // Open the JSON file for writing
        if (jsonFile == NULL) {
            printf("Failed to open JSON file for writing.\n");
            fclose(file);
            return;
        }

        fprintf(jsonFile, "{"); // Start writing JSON object

        for (uint32_t i = 0; i < bejMap.count; i++) {
            fprintf(jsonFile, "\"%s\": %u", bejMap.keys[i].data, bejMap.values[i]); // Write key-value pair as JSON
            if (i < bejMap.count - 1) {
                fprintf(jsonFile, ", "); // Add comma if it's not the last pair
            }
        }

        fprintf(jsonFile, "}"); // End writing JSON object

        fclose(jsonFile); // Close the JSON file

        // Free allocated memory
        for (uint32_t i = 0; i < bejMap.count; i++) {
            free(bejMap.keys[i].data);
        }
        free(bejMap.keys);
        free(bejMap.values);
    }

    fclose(file); // Close the BEJ file
}
