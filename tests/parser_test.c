#include <stdio.h>
#include <unistd.h>
#include "parser.h"

int parser_test_parser_open_file(void) {
    char* invalid_file_string = "test.txt";
    char* valid_file_string = "test.properties";

    struct Parser_Obj test_parser = parser_init();
    
    // Test wrong file extension
    if (parser_open_file(&test_parser, invalid_file_string) != -2) {
        return 1;
    }

    // Test invalid file
    if (parser_open_file(&test_parser, "invalid.properties") != -3) {
        return 1;
    }

    // Test valid file
    if (parser_open_file(&test_parser, valid_file_string) != 0) {
        printf("%d\n", parser_open_file(&test_parser, valid_file_string));
        return 1;
    }

    return 0;
}

int parser_test_parser_parse(void) {
    char* valid_file_string = "test.properties";
    struct Parser_Obj test_parser = parser_init();

    // Test parser not parse ready
    if (parser_parse(&test_parser) != -1) {
        return 1;
    }

    // Open file
    if (parser_open_file(&test_parser, valid_file_string) != 0) {
        return 1;
    }

    // Test valid file
    int result = parser_parse(&test_parser);
    if (result != 0) {
        return 1;
    }

    char* expected_keys[] = {
        "key1",
        "key2",
        "key3",
        "Url"
    };

    char* expected_values[] = {
        "value1",
        "value2",
        "value3",
        "https://www.google.com/"
    };

    for (int i = 0; i < 4; i++) {
        if (strcmp(expected_keys[i], test_parser.info.keys[i]) > 0) {
            printf("%s | %s\n", expected_keys[i], test_parser.info.keys[i]);
            return 1;
        }

        if (strcmp(expected_values[i], test_parser.info.values[i]) > 0) {
            printf("%s | %s\n", expected_values[i], test_parser.info.values[i]);
            return 1;
        }
    }

    return 0;
}

int parser_test_parser_close_file(void) {
    struct Parser_Obj test_parser = parser_init();

    // Test when no file open
    if (parser_close_file(&test_parser)) {
        return 1;
    }

    // Test when file is open
    if (parser_open_file(&test_parser, "test.properties")) {
        return 1;
    }
    if (parser_close_file(&test_parser)) {
        return 1;
    }

    return 0;
}

int main(void) {
    int num_failures = 0;
    int result;

    printf("Running parser_test_parser_open_file... ");
    result = parser_test_parser_open_file();
    if (result) {
        num_failures += result;
        printf("FAIL\n");
    }
    else {
        printf("PASS\n");
    }

    printf("Running parser_test_parser_parse... ");
    result = parser_test_parser_parse();
    if (result) {
        num_failures += result;
        printf("FAIL\n");
    }
    else {
        printf("PASS\n");
    }

    printf("Running parser_test_parser_close_file... ");
    result = parser_test_parser_close_file();
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
    
    printf("All tests passed!\n");
    return 0;
}