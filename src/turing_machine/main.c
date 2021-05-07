#include <ctype.h>
#include <libgeometry/geometry.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    char str[SIZE_OF_ARR];
    int circumflex_counter;
    char* curs;
    char* end;
    unsigned int circle_record_counter = 0;
    unsigned int triangle_record_counter = 0;
    printf("Enter a circle or triangle in WKT format\n");
    printf("After entering the figures, enter any non-alphabetic character or "
           "press Enter again to complete the entry\n");
    while (fgets(str, SIZE_OF_ARR, stdin)) {
        curs = str;
        end = str;
        circumflex_counter = 0;
        bool intersects_print = false;
        bool end_of_input
                = prepare_input(str, &circumflex_counter, &curs, &end);
        int ind_cir[SIZE_OF_ARR];
        int ind_tri[SIZE_OF_ARR];
        int circ_ind_cntr, tria_ind_cntr, return_status;
        if (end_of_input == false) {
            printf("Input completed\n");
            exit(0);
        }
        if (strncmp(curs, "circle", end - curs) == 0) {
            return_status = parse_circle(
                    &circumflex_counter,
                    &curs,
                    &end,
                    &circle_record_counter,
                    &var_circle);
            if (return_status == 0) {
                printf("The circle has been added successfully!\n");
                printf("Your figure - circle(%.1lf %.1lf, %.1lf)\n",
                       var_circle.x[circle_record_counter],
                       var_circle.y[circle_record_counter],
                       var_circle.radius[circle_record_counter]);
                printf("perimeter = %lf\n",
                       calculate_perimeter_circle(
                               var_circle.radius[circle_record_counter]));
                printf("area = %lf\n",
                       calculate_area_circle(
                               var_circle.radius[circle_record_counter]));
                is_intersection(
                        circle_record_counter,
                        triangle_record_counter,
                        var_circle,
                        var_triangle,
                        "circle",
                        ind_cir,
                        ind_tri,
                        &circ_ind_cntr,
                        &tria_ind_cntr);
                if ((circ_ind_cntr > 0) || (tria_ind_cntr > 0)) {
                    if (intersects_print == false) {
                        intersects_print = true;
                        printf("intersects:\n");
                    }
                    for (int k = 0; k < circ_ind_cntr; k++) {
                        printf("    circle( %.1lf %.1lf , %.1lf )\n\n",
                               var_circle.x[k],
                               var_circle.y[k],
                               var_circle.radius[k]);
                    }
                    for (int k = 0; k < tria_ind_cntr; k++) {
                        printf("    triangle (( %.1lf %.1lf, %.1lf %.1lf, "
                               "%.1lf "
                               "%.1lf "
                               "))\n\n",
                               var_triangle.x1[k],
                               var_triangle.y1[k],
                               var_triangle.x2[k],
                               var_triangle.y2[k],
                               var_triangle.x3[k],
                               var_triangle.y3[k]);
                    }
                }
                circle_record_counter++;
            }
            if (return_status == -1) {
                print_errormsg(&circumflex_counter);
                printf("Error at column %d: expected '('\n\n",
                       circumflex_counter);
            }
            if (return_status == -2 || return_status == -3
                || return_status == -5) {
                print_errormsg(&circumflex_counter);
                printf("Error at column %d: expected '<double>'\n",
                       circumflex_counter);
            }
            if (return_status == -4) {
                print_errormsg(&circumflex_counter);
                printf("Error at column %d: expected ','\n\n",
                       circumflex_counter);
            }
            if (return_status == -6) {
                printf("Radius can not be negative\n\n");
            }
            if (return_status == -7) {
                print_errormsg(&circumflex_counter);
                printf("Error at column %d: expected ')'\n\n",
                       circumflex_counter);
            }
            if (return_status == -8) {
                print_errormsg(&circumflex_counter);
                printf("unexpected token\n\n");
                printf("The circle has NOT been added !\n\n");
            }
        } else {
            if (strncmp(curs, "triangle", end - curs) == 0) {
                return_status = parse_triangle(
                        &circumflex_counter,
                        &curs,
                        &end,
                        &triangle_record_counter,
                        &var_triangle);
                if (return_status == 0) {
                    printf("The triangle has been added successfully!\n");
                    printf("Your figure - triangle((%.1f %.1f, %.1f %.1f, %.1f "
                           "%.1f, "
                           "%.1f %.1f))\n",
                           var_triangle.x1[triangle_record_counter],
                           var_triangle.y1[triangle_record_counter],
                           var_triangle.x2[triangle_record_counter],
                           var_triangle.y2[triangle_record_counter],
                           var_triangle.x3[triangle_record_counter],
                           var_triangle.y3[triangle_record_counter],
                           var_triangle.x1[triangle_record_counter],
                           var_triangle.y1[triangle_record_counter]);
                    printf("perimeter = %lf\n",
                           calculate_perimeter_triangle(
                                   var_triangle.x1[triangle_record_counter],
                                   var_triangle.y1[triangle_record_counter],
                                   var_triangle.x2[triangle_record_counter],
                                   var_triangle.y2[triangle_record_counter],
                                   var_triangle.x3[triangle_record_counter],
                                   var_triangle.y3[triangle_record_counter]));
                    printf("area = %lf\n",
                           calculate_area_triangle(
                                   var_triangle.x1[triangle_record_counter],
                                   var_triangle.y1[triangle_record_counter],
                                   var_triangle.x2[triangle_record_counter],
                                   var_triangle.y2[triangle_record_counter],
                                   var_triangle.x3[triangle_record_counter],
                                   var_triangle.y3[triangle_record_counter]));
                    is_intersection(
                            circle_record_counter,
                            triangle_record_counter,
                            var_circle,
                            var_triangle,
                            "triangle",
                            ind_cir,
                            ind_tri,
                            &circ_ind_cntr,
                            &tria_ind_cntr);
                    if ((circ_ind_cntr > 0) || (tria_ind_cntr > 0)) {
                        if (intersects_print == false) {
                            intersects_print = true;
                            printf("intersects:\n");
                        }
                        for (int k = 0; k < circ_ind_cntr; k++) {
                            printf("    circle( %.1lf %.1lf , %.1lf )\n\n",
                                   var_circle.x[k],
                                   var_circle.y[k],
                                   var_circle.radius[k]);
                        }
                        for (int k = 0; k < tria_ind_cntr; k++) {
                            printf("    triangle (( %.1lf %.1lf, %.1lf %.1lf, "
                                   "%.1lf "
                                   "%.1lf "
                                   "))\n\n",
                                   var_triangle.x1[k],
                                   var_triangle.y1[k],
                                   var_triangle.x2[k],
                                   var_triangle.y2[k],
                                   var_triangle.x3[k],
                                   var_triangle.y3[k]);
                        }
                    }
                    triangle_record_counter++;
                }
                if (return_status == -1) {
                    print_errormsg(&circumflex_counter);
                    printf("Error at column %d: expected '('\n\n",
                           circumflex_counter);
                }
                if (return_status == -2 || return_status == -3) {
                    print_errormsg(&circumflex_counter);
                    printf("Error at column %d: expected '<double>'\n",
                           circumflex_counter);
                }
                if (return_status == -4) {
                    print_errormsg(&circumflex_counter);
                    printf("Error at column %d: expected ','\n\n",
                           circumflex_counter);
                }
                if (return_status == -5) {
                    print_errormsg(&circumflex_counter);
                    printf("Error at column %d: expected ')'\n\n",
                           circumflex_counter);
                }
                if (return_status == -6) {
                    print_errormsg(&circumflex_counter);
                    printf("unexpected token\n\n");
                    printf("The triangle has NOT been added !\n\n");
                }
                if (return_status == -7) {
                    printf("The triangle can not close !\n\n");
                }
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