#include <stdio.h>
#include <string.h>
#include "file_manager.h"
#include "course.h"

#define DATA_FILE "courses.txt"

/* Save records in the format: code|title|units */
void save_courses(struct Course courses[], int count)
{
    FILE *file;
    int i;

    file = fopen(DATA_FILE, "w");

    if (file == NULL)
    {
        perror("Could not open file for saving");
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (fprintf(file, "%s|%s|%d\n", courses[i].code,
                    courses[i].title, courses[i].units) < 0)
        {
            printf("An error occurred while writing the file.\n");
            fclose(file);
            return;
        }
    }

    if (fclose(file) != 0)
    {
        perror("Could not close the file correctly");
        return;
    }

    printf("%d course(s) saved to '%s'.\n", count, DATA_FILE);
}

void load_courses(struct Course courses[], int *count)
{
    FILE *file;
    char line[LINE_SIZE];
    struct Course loaded[MAX_COURSES];
    int loaded_count = 0;
    int line_number = 0;
    int units;
    char code[CODE_SIZE];
    char title[TITLE_SIZE];
    char extra;

    file = fopen(DATA_FILE, "r");

    if (file == NULL)
    {
        perror("Could not open file for loading");
        printf("Save courses first, or check that '%s' exists.\n", DATA_FILE);
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;
        line[strcspn(line, "\r\n")] = '\0';

        if (line[0] == '\0')
        {
            continue;
        }

        code[0] = '\0';
        title[0] = '\0';
        units = 0;

        if (sscanf(line, "%19[^|]|%99[^|]|%d%c", code, title,
                   &units, &extra) != 3 || code[0] == '\0' ||
            title[0] == '\0' || units <= 0)
        {
            printf("Skipping invalid record on line %d.\n", line_number);
            continue;
        }

        if (loaded_count >= MAX_COURSES)
        {
            printf("Maximum capacity reached. Remaining records were ignored.\n");
            break;
        }

        if (find_course_index(loaded, loaded_count, code) != -1)
        {
            printf("Skipping duplicate course code on line %d.\n", line_number);
            continue;
        }

        strcpy(loaded[loaded_count].code, code);
        strcpy(loaded[loaded_count].title, title);
        loaded[loaded_count].units = units;
        loaded_count++;
    }

    if (ferror(file))
    {
        perror("An error occurred while reading the file");
        fclose(file);
        return;
    }

    fclose(file);

    for (int i = 0; i < loaded_count; i++)
    {
        courses[i] = loaded[i];
    }

    *count = loaded_count;
    printf("%d course(s) loaded from '%s'.\n", *count, DATA_FILE);
}
