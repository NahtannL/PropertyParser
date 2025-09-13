/**
 * @file cstring.h
 * @author Nathan Lieu
 * @version 1.0
 * @date September 12, 2025
 * 
 * @brief Extended string manipulation utilities
 * 
 * Provides enhanced string manipulation functions that extend the standard C
 * string library functionality. It includes utilities for substring
 * extraction, string trimming, and other common string operations not available
 * in the standard library.
 */

#ifndef CSTRING_H
#define CSTRING_H

#include <stdio.h>
#include <string.h>

/**
 * @brief Copies a substring from source to destination.
 * 
 * Extracts a substring from the source string starting at index `begin_n` 
 * (inclusive) and ending at index `end_n` (exclusive), which is copied to the
 * destination buffer. The destination buffer is expected to be pre-allocated
 * with sufficient space to hold the substring and the null terminator.
 * 
 * @param destination Pre-allocated buffer
 * @param source The source string to extract from
 * @param begin_n Starting index of substring (inclusive)
 * @param end_n Ending index of substring (exclusive)
 * 
 * @return Pointer to destination string on success. Returns NULL if:
 *          - range invalid
 *          - begin_n is out of bounds
 *          - end_n is out of bounds
 * 
 * @note The destination buffer must have enough space for at least 
 * `end_n - begin_n + 1` characters to accomodate the substring and NULL 
 * terminator.
 * 
 * @example
 * ```
 * char destination_str[10];
 * char* result = cstrncpy(destination_str, "Hello", 0, 3);
 * // destination_str = "Hel"
 * ```
 */
char* cstrncpy(char* destination, const char* source, size_t begin_n, 
    size_t end_n);

/**
 * @brief Trims leading and trailing whitespace from a string.
 * 
 * Removes all spaces from the beginning and end of the input string. The
 * operation is performed in-place, with the original string being modified.
 * 
 * @param str The string to be trimmed (must be modifiable)
 * 
 * @return Pointer to the trimmed string on success. Returns NULL if input
 * string is NULL. Returns empty string if the string contains only whitespace.
 * 
 * @note `str` must be a mutable string and not a string lateral 
 * (e.g. `char example[]`).
 */
char* cstrtrim(char str[]);

#endif