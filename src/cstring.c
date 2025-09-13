#include "cstring.h"

char* cstrncpy(char* destination, const char* source, size_t begin_n, 
    size_t end_n) {
        size_t length_old_string = strlen(source);

        // String is going backwards
        if (end_n <= begin_n) {
            return NULL;
        }

        // Substring beginning is out of source string scope
        if (begin_n >= length_old_string) {
            return NULL;
        }

        // Substring end is out of source string scope
        if (end_n > length_old_string) {
            return NULL;
        }

        size_t length_new_string = end_n - begin_n;

        size_t i;
        for (i = 0; i < length_new_string; i++) {
            destination[i] = source[begin_n + i];
        }

        // Add NULL terminator
        destination[i] = '\0';

        return destination;
}

char* cstrtrim(char str[]) {
    if (!str) {
        return NULL;
    }

    // Remove leading whitespace
    char* start_ptr = str;
    for (; *start_ptr == ' '; start_ptr++);

    if (*start_ptr != '\0') {
        // Remove trailing whitespace
        char* end_ptr = str + strlen(str) - 1; 
        for (; *end_ptr == ' '; end_ptr--);
    
        // Terminate new string
        *(++end_ptr) = '\0';
    }

    // Copy new memory into str
    if (start_ptr != str) {
        memmove(str, start_ptr, strlen(start_ptr)+1);
    }

    return str;
}