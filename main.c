#include <stdio.h>
#include "course.h"
#include "input.h"
#include "file_manager.h"

static int get_menu_choice(int *choice)
{
    char input[LINE_SIZE];

    if (!read_line("Select an option (1-7): ", input, sizeof(input)))
    {
        return 0;
    }

    if (!parse_integer(input, choice))
    {
        printf("Invalid input. Please enter a whole number.\n");
    }

    return 1;
}

int main(void)
{
    struct Course courses[MAX_COURSES];
    int count = 0;
    int choice;

    printf("Welcome to the Student Course Management System.\n");

    while (1)
    {
        display_menu();

        if (!get_menu_choice(&choice))
        {
            printf("\nInput ended. Exiting program.\n");
            break;
        }

        switch (choice)
        {
            case 1:
                add_course(courses, &count);
                break;
            case 2:
                view_courses(courses, count);
                break;
            case 3:
                search_course(courses, count);
                break;
            case 4:
                calculate_total_units(courses, count);
                break;
            case 5:
                save_courses(courses, count);
                break;
            case 6:
                load_courses(courses, &count);
                break;
            case 7:
                printf("Thank you for using the system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please select a number from 1 to 7.\n");
                break;
        }
    }

    return 0;
}
