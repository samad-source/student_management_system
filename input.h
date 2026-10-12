#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

int read_line(const char *prompt, char buffer[], size_t size);
int parse_integer(const char *text, int *value);
int contains_delimiter(const char *text);

#endif
