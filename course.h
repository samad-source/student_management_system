#ifndef COURSE_H
#define COURSE_H

#define MAX_COURSES 50
#define CODE_SIZE 20
#define TITLE_SIZE 100
#define LINE_SIZE 256

struct Course
{
    char code[CODE_SIZE];
    char title[TITLE_SIZE];
    int units;
};

void display_menu(void);
int find_course_index(struct Course courses[], int count, const char code[]);
void add_course(struct Course courses[], int *count);
void view_courses(struct Course courses[], int count);
void search_course(struct Course courses[], int count);
int total_units_recursive(struct Course courses[], int count, int index);
void calculate_total_units(struct Course courses[], int count);

#endif
