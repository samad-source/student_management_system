#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "course.h"

void save_courses(struct Course courses[], int count);
void load_courses(struct Course courses[], int *count);

#endif
