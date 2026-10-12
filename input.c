#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "input.h"

/* Read one line safely, removing the newline when present. */
int read_line(const char *prompt, char buffer[], size_t size)
{
    int ch;
    size_t length;

    if (size == 0)
    {
        return 0;
    }

    printf("%s", prompt);

    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        return 0;
    }

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }

    return 1;
}

/* Convert a string to a valid integer. Returns 1 on success, 0 otherwise. */
int parse_integer(const char *text, int *value)
{
    char *end_pointer;
    long number;

    while (isspace((unsigned char)*text))
    {
        text++;
    }

    if (*text == '\0')
    {
        return 0;
    }

    number = strtol(text, &end_pointer, 10);

    if (text == end_pointer)
    {
        return 0;
    }

    while (isspace((unsigned char)*end_pointer))
    {
        end_pointer++;
    }

    if (*end_pointer != '\0' || number < INT_MIN || number > INT_MAX)
    {
        return 0;
    }

    *value = (int)number;
    return 1;
}

int contains_delimiter(const char *text)
{
    return strchr(text, '|') != NULL;
}
