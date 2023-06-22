#include "bej_parser.h"

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        printf("Usage: ./bej_parser <BEJ_file> <output_JSON_file>\n");
        return 1;
    }

    // Parse the BEJ file and generate the corresponding JSON file
    parse_bej(argv[1], argv[2]);

    return 0;
}
