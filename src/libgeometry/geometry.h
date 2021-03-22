#pragma once
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_OF_ARR 256

struct Circle {
    double x[SIZE_OF_ARR];
    double y[SIZE_OF_ARR];
    double radius[SIZE_OF_ARR];
};

struct Triangle {
    double x1[SIZE_OF_ARR];
    double x2[SIZE_OF_ARR];
    double x3[SIZE_OF_ARR];
    double x4[SIZE_OF_ARR];
    double y1[SIZE_OF_ARR];
    double y2[SIZE_OF_ARR];
    double y3[SIZE_OF_ARR];
    double y4[SIZE_OF_ARR];
};

bool skip_space(int* circumflex_counter, char** first, char** second);
bool is_sign(char token, int* circumflex_counter, char** first, char** second);
bool add_word_length(int* circumflex_counter, char** first, char** second);
bool is_number(int* circumflex_counter, char** first);
bool is_EOF(int* circumflex_counter, char** first);
bool is_letter(char** second);
bool to_lower_all_str(char* array);
bool parse_circle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter);
bool parse_triangle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter);
bool parse_value(
        double* var, int* circumflex_counter, char*** curs, char*** end);