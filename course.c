#include <stdio.h>
#include <string.h>
#include "course.h"
#include "input.h"

/* Find a course by code. Returns its index, or -1 if not found. */
int find_course_index(struct Course courses[], int count, const char code[])
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(courses[i].code, code) == 0)
        {
            return i;
        }
    }

    return -1;
}

void display_menu(void)
{
    printf("\n============================================\n");
    printf("       STUDENT COURSE MANAGEMENT SYSTEM\n");
    printf("============================================\n");
    printf("1. Add Course\n");
    printf("2. View All Courses\n");
    printf("3. Search Course by Code\n");
    printf("4. Calculate Total Units\n");
    printf("5. Save Courses to File\n");
    printf("6. Load Courses from File\n");
    printf("7. Exit\n");
    printf("============================================\n");
}

void add_course(struct Course courses[], int *count)
{
    char code[CODE_SIZE];
    char title[TITLE_SIZE];
    char input[LINE_SIZE];
    int units;

    if (*count >= MAX_COURSES)
    {
        printf("\nCourse storage is full. Maximum: %d courses.\n", MAX_COURSES);
        return;
    }

    if (!read_line("Enter course code (e.g. COS201): ", code, sizeof(code)))
    {
        printf("\nInput ended. Course was not added.\n");
        return;
    }

    if (code[0] == '\0' || contains_delimiter(code))
    {
        printf("Course code cannot be empty or contain '|'.\n");
        return;
    }

    if (find_course_index(courses, *count, code) != -1)
    {
        printf("A course with that code already exists.\n");
        return;
    }

    if (!read_line("Enter course title: ", title, sizeof(title)))
    {
        printf("\nInput ended. Course was not added.\n");
        return;
    }

    if (title[0] == '\0' || contains_delimiter(title))
    {
        printf("Course title cannot be empty or contain '|'.\n");
        return;
    }

    if (!read_line("Enter credit units (positive whole number): ",
                   input, sizeof(input)))
    {
        printf("\nInput ended. Course was not added.\n");
        return;
    }

    if (!parse_integer(input, &units) || units <= 0)
    {
        printf("Invalid units. Enter a positive whole number.\n");
        return;
    }

    strcpy(courses[*count].code, code);
    strcpy(courses[*count].title, title);
    courses[*count].units = units;
    (*count)++;

    printf("Course added successfully.\n");
}

void view_courses(struct Course courses[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo courses have been recorded yet.\n");
        return;
    }

    printf("\n---------------- REGISTERED COURSES ----------------\n");

    for (i = 0; i < count; i++)
    {
        printf("\nCourse %d\n", i + 1);
        printf("  Code:  %s\n", courses[i].code);
        printf("  Title: %s\n", courses[i].title);
        printf("  Units: %d\n", courses[i].units);
    }

    printf("\nTotal courses: %d\n", count);
}

void search_course(struct Course courses[], int count)
{
    char code[CODE_SIZE];
    int index;

    if (count == 0)
    {
        printf("\nThere are no courses to search.\n");
        return;
    }

    if (!read_line("Enter the course code to search for: ",
                   code, sizeof(code)))
    {
        printf("\nInput ended.\n");
        return;
    }

    index = find_course_index(courses, count, code);

    if (index == -1)
    {
        printf("Course '%s' was not found.\n", code);
    }
    else
    {
        printf("\nCourse found:\n");
        printf("  Code:  %s\n", courses[index].code);
        printf("  Title: %s\n", courses[index].title);
        printf("  Units: %d\n", courses[index].units);
    }
}

/* Recursion adds this course's units to the units of the remaining courses. */
int total_units_recursive(struct Course courses[], int count, int index)
{
    if (index >= count)
    {
        return 0;
    }

    return courses[index].units +
           total_units_recursive(courses, count, index + 1);
}

void calculate_total_units(struct Course courses[], int count)
{
    int total = total_units_recursive(courses, count, 0);

    printf("\nTotal registered courses: %d\n", count);
    printf("Total credit units: %d\n", total);
}
