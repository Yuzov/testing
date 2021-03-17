#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ARR 256

bool skip_space(int* circumflex_counter, char** first, char** second);
bool is_sign(char token, int* circumflex_counter, char** first, char** second);
bool add_word_length(int* circumflex_counter, char** first, char** second);
bool is_number(int* circumflex_counter, char** first, char** second);
bool is_EOF(int* circumflex_counter, char** first);
bool is_letter(int* circumflex_counter, char** first, char** second);
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

int main()
{
    char str[SIZE_OF_ARR];
    int circumflex_counter;
    char* curs;
    char* end;
    unsigned int record_counter = 0;
    printf("Enter a circle or triangle in WKT format\n");
    printf("After entering the figures, enter any non-alphabetic character or "
           "press Enter again to complete the entry\n");
    while (fgets(str, SIZE_OF_ARR, stdin)) {
        curs = str;
        end = str;
        circumflex_counter = 0;
        to_lower_all_str(str);
        skip_space(&circumflex_counter, &curs, &end);
        is_letter(&circumflex_counter, &curs, &end);
        if (strncmp(curs, "circle", end - curs) == 0) //ПРОВЕРКА НА CIRCLE
        {
            parse_circle(&circumflex_counter, &curs, &end, &record_counter);
        } else {
            if (strncmp(curs, "triangle", end - curs)
                == 0) //ПРОВЕРКА НА TRIANGLE
            {
                parse_triangle(
                        &circumflex_counter, &curs, &end, &record_counter);
            } else {
                for (int exit_anticipatorily = 0;
                     exit_anticipatorily < circumflex_counter;
                     exit_anticipatorily++) {
                    printf(" ");
                }
                printf("^\n");
                printf("Error at column %d: expected 'circle' or 'triangle'\n",
                       circumflex_counter);
            }
        }
    }
}

bool skip_space(int* circumflex_counter, char** first, char** second)
{
    while (isspace(**first)) {
        *first = *first + 1;
        *second = *second + 1;
        *circumflex_counter = *circumflex_counter + 1;
    }
    return true;
}

bool is_sign(char token, int* circumflex_counter, char** first, char** second)
{
    if (**first != token) {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("Error at column %d: expected '%c'\n",
               *circumflex_counter,
               token);
        return false;
    } else {
        *first = *first + 1;
        *second = *second + 1;
        *circumflex_counter = *circumflex_counter + 1;
    }
    return true;
}

bool add_word_length(int* circumflex_counter, char** first, char** second)
{
    *circumflex_counter = *circumflex_counter + (*second - *first);
    *first = *second;
    return true;
}

bool is_number(int* circumflex_counter, char** first, char** second)
{
    if (isdigit(**first) == 0) {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("Error at column %d: expected '<double>'\n",
               *circumflex_counter);
        return false;
    }
    return true;
}

bool is_EOF(int* circumflex_counter, char** first)
{
    if (**first != '\0') {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("unexpected token\n");
        return false;
    }
    return true;
}

bool is_letter(int* circumflex_counter, char** first, char** second)
{
    if ((**second >= '\x61') && (**second <= '\x7a')) {
        while (**second != ' ') {
            *second = *second + 1;
        }
    } else {
        printf("Input completed");
        exit(0);
    }
    return true;
}

bool to_lower_all_str(char* array)
{
    for (int i = 0; i < SIZE_OF_ARR; i++) {
        array[i] = tolower(array[i]);
    }
    return true;
}

bool parse_value(
        double* var, int* circumflex_counter, char*** curs, char*** end)
{
    bool error = is_number(circumflex_counter, *curs, *end);
    if (!error)
        return false;
    *var = strtod(**curs, *end);
    add_word_length(circumflex_counter, *curs, *end);
    skip_space(circumflex_counter, *curs, *end);
    return true;
}

bool parse_circle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter)
{
    struct Circle var_circle;
    bool error = true;
    for (;;) {
        double x, y, radius;
        add_word_length(circumflex_counter, curs, end);
        skip_space(circumflex_counter, curs, end);
        error = is_sign('(', circumflex_counter, curs, end);
        if (!error)
            break;
        skip_space(circumflex_counter, curs, end);
        error = parse_value(&x, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = parse_value(&y, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = is_sign(',', circumflex_counter, curs, end);
        if (!error)
            break;
        skip_space(circumflex_counter, curs, end);
        error = parse_value(&radius, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = is_sign(')', circumflex_counter, curs, end);
        if (!error)
            break;
        skip_space(circumflex_counter, curs, end);
        error = is_EOF(circumflex_counter, curs);
        if (error == true) {
            var_circle.x[*record_counter] = x;
            var_circle.y[*record_counter] = y;
            var_circle.radius[*record_counter] = radius;
            printf("The circle has been added successfully!\n");
            printf("Your figure - circle(%.1f %.1f, %.1f)\n",
                   var_circle.x[*record_counter],
                   var_circle.y[*record_counter],
                   var_circle.radius[*record_counter]);
            *record_counter = *record_counter + 1;
            break;
        } else {
            printf("The circle has NOT been added !\n");
            break;
        }
    }
    return true;
}

bool parse_triangle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter)
{
    struct Triangle var_triangle;
    bool error = true;
    for (;;) {
        double x1, x2, x3, x4, y1, y2, y3, y4;
        bool exit_anticipatorily = false;
        add_word_length(circumflex_counter, curs, end);
        skip_space(circumflex_counter, curs, end);
        for (int i = 0; i < 2; i++) {
            error = is_sign('(', circumflex_counter, curs, end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            skip_space(circumflex_counter, curs, end);
        }
        if (exit_anticipatorily == true)
            break;
        for (int i = 0; i < 3; i++) {
            double varx, vary;
            error = parse_value(&varx, circumflex_counter, &curs, &end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            error = parse_value(&vary, circumflex_counter, &curs, &end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            error = is_sign(',', circumflex_counter, curs, end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            if (i == 0) {
                x1 = varx;
                y1 = vary;
            }
            if (i == 1) {
                x2 = varx;
                y2 = vary;
            }
            if (i == 2) {
                x3 = varx;
                y3 = vary;
            }
            skip_space(circumflex_counter, curs, end);
        }
        if (exit_anticipatorily == true)
            break;
        error = parse_value(&x4, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = parse_value(&y4, circumflex_counter, &curs, &end);
        if (!error)
            break;
        for (int i = 0; i < 2; i++) {
            error = is_sign(')', circumflex_counter, curs, end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            skip_space(circumflex_counter, curs, end);
        }
        if (exit_anticipatorily == true)
            break;
        error = is_EOF(circumflex_counter, curs);
        if ((error == true) && (x1 == x4) && (y1 == y4)) {
            var_triangle.x1[*record_counter] = x1;
            var_triangle.x2[*record_counter] = x2;
            var_triangle.x3[*record_counter] = x3;
            var_triangle.x4[*record_counter] = x4;
            var_triangle.y1[*record_counter] = y1;
            var_triangle.y2[*record_counter] = y2;
            var_triangle.y3[*record_counter] = y3;
            var_triangle.y4[*record_counter] = y4;
            printf("The triangle has been added successfully!\n");
            printf("Your figure - triangle((%.1f %.1f, %.1f %.1f, %.1f %.1f, "
                   "%.1f %.1f))\n",
                   var_triangle.x1[*record_counter],
                   var_triangle.y1[*record_counter],
                   var_triangle.x2[*record_counter],
                   var_triangle.y2[*record_counter],
                   var_triangle.x3[*record_counter],
                   var_triangle.y3[*record_counter],
                   var_triangle.x4[*record_counter],
                   var_triangle.y4[*record_counter]);
            *record_counter = *record_counter + 1;
            break;
        } else {
            printf("The triangle has NOT been added !\n");
            break;
        }
    }
    return true;
}