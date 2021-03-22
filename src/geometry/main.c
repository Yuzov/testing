#include <ctype.h>
#include <libgeometry/geometry.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        is_letter(&end);
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
