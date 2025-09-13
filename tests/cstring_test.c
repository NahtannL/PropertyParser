#include <stdio.h>
#include "cstring.h"

int cstring_test_cstrncpy(void) {
    char* source_string = "The string to copy.";
    char destination_string[strlen(source_string)+1];

    size_t begin_index = 0;
    size_t end_index = 10;

    // Test end_index > begin_index
    if (cstrncpy(destination_string, source_string, end_index, 
        begin_index) != NULL) {
            return 1;
    }

    // Test begin_index > source_string length && end_index > source_string
    // length
    if (cstrncpy(destination_string, source_string, strlen(source_string)+4, 
        strlen(source_string)+9) != NULL) {
            return 1;
    }

    // Test end_index > source_string length
    if (cstrncpy(destination_string, source_string, begin_index, 
        strlen(source_string)+5) != NULL) {
            return 1;
    }

    // Test empty string
    if (cstrncpy(destination_string, "", begin_index, end_index) != NULL) {
        return 1;
    }

    // Test valid substring
    char* expected_destination_string = "The string";
    cstrncpy(destination_string, source_string, begin_index, end_index);
    if (strcmp(destination_string, expected_destination_string) > 0) {
        return 1;
    }

    // Test copying entire string
    cstrncpy(destination_string, source_string, begin_index, 
        strlen(source_string)-1);
    if (strcmp(destination_string, source_string) > 0) {
        return 1;
    }

    // Test copying first character
    expected_destination_string = "T";
    cstrncpy(destination_string, source_string, begin_index, 1);
    if (strcmp(destination_string, expected_destination_string) > 0) {
        return 1;
    }

    // Test copying last character
    expected_destination_string = ".";
    cstrncpy(destination_string, source_string, strlen(source_string)-1, 
        strlen(source_string));
    if (strcmp(destination_string, expected_destination_string) > 0) {
        return 1;
    }

    return 0;
}

int cstring_test_cstrtrim(void) {
    // Test leading and trailing spaces
    char test_string1[] = "  Hello  ";
    char* expected_string = "Hello";
    char* destination_string = cstrtrim(test_string1);
    if (!destination_string) {
        return 1;
    }
    if (strcmp(expected_string, destination_string) || strcmp(expected_string, 
        test_string1)) {
            return 1;
    }

    // Test only trailing spaces
    char test_string2[] = "Hello  ";
    destination_string = cstrtrim(test_string2);
    if (!destination_string) {
        return 1;
    }
    if (strcmp(expected_string, destination_string) || strcmp(expected_string, 
        test_string2)) {
            return 1;
    }

    // Test only leading spaces
    char test_string3[] = "  Hello";
    destination_string = cstrtrim(test_string3);
    if (!destination_string) {
        return 1;
    }
    if (strcmp(expected_string, destination_string) || strcmp(expected_string, 
        test_string3)) {
            return 1;
    }

    // Test no spaces
    char test_string4[] = "Hello";
    destination_string = cstrtrim(test_string4);
    if (!destination_string) {
        return 1;
    }
    if (strcmp(expected_string, destination_string) || strcmp(expected_string, 
        test_string4)) {
            return 1;
    }

    // Test empty string
    char test_string5[] = "";
    expected_string = "";
    destination_string = cstrtrim(test_string5);
    if (!destination_string) {
        return 1;
    }
    if (strcmp(expected_string, destination_string) || strcmp(expected_string, 
        test_string5)) {
            return 1;
    }

    // Test only spaces
    char test_string6[] = "    ";
    destination_string = cstrtrim(test_string6);
    if (!destination_string) {
        return 1;
    }
    if (strcmp(expected_string, destination_string) || strcmp(expected_string, 
        test_string6)) {
            return 1;
    }

    // Test single character
    char test_string7[] = "  X  ";
    expected_string = "X";
    destination_string = cstrtrim(test_string7);
    if (!destination_string) {
        return 1;
    }
    if (strcmp(expected_string, destination_string) || strcmp(expected_string, 
        test_string7)) {
            return 1;
    }

    // Test NULL input
    if (cstrtrim(NULL)) {
        return 1;
    }

    return 0;
}

int main(void) {
    int num_failures = 0;
    int result;

    printf("Running cstring_test_cstrincpy... ");
    result = cstring_test_cstrncpy();
    if (result) {
        num_failures += result;
        printf("FAIL\n");
    }
    else {
        printf("PASS\n");
    }

    printf("Running cstring_test_cstrtrim... ");
    result = cstring_test_cstrtrim();
    if (result) {
        num_failures += result;
        printf("FAIL\n");
    }
    else {
        printf("PASS\n");
    }

    if (num_failures > 0) {
        printf("Number of tests failed: %d\n", num_failures);
        return 1;
    }

    return 0;
}