#ifndef BEJ_PARSER_H
#define BEJ_PARSER_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t length;
    char* data;
} BEJString;

typedef struct {
    uint32_t count;
    BEJString* keys;
    uint32_t* values;
} BEJMap;

void write_string(FILE* file, BEJString bejString);
void write_map(FILE* file, BEJMap bejMap);
void write_bej(const char* filename, BEJMap bejMap);
void parse_string(FILE* file, BEJString* bejString);
void parse_map(FILE* file, BEJMap* bejMap);
void parse_bej(const char* input_filename, const char* output_filename);

#endif  // BEJ_PARSER_H
