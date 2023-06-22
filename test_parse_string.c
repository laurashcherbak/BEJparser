#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bej_parser.h"  // Including the header file with function declarations

void test_parse_string() {
    // Open test file for writing
    FILE* file = fopen("test_file.bin", "wb");
    if (file == NULL) {
        printf("Failed to open test file for writing.\n");
        return;
    }

    BEJString bejString;
    bejString.length = 5;
    bejString.data = "apple";

    // Write string to the file
    write_string(file, bejString);

    fclose(file);

    // Open test file for reading
    file = fopen("test_file.bin", "rb");
    if (file == NULL) {
        printf("Failed to open test file for reading.\n");
        return;
    }

    BEJString parsedString;
    // Parse the string from the file
    parse_string(file, &parsedString);

    fclose(file);

    // Check the results
    if (parsedString.length != bejString.length) {
        printf("parse_string test failed: Incorrect length.\n");
        return;
    }

    if (strcmp(parsedString.data, bejString.data) != 0) {
        printf("parse_string test failed: Incorrect data.\n");
        return;
    }

    printf("parse_string test passed.\n");

    // Memory cleanup
    free(parsedString.data);
}

int main() {
    // Run the test for parsing a string
    test_parse_string();
    return 0;
}
