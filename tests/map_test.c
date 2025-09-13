#include <stdio.h>
#include "map.h"

int map_test_insert(void) {
    struct Map map_test = map_init();

    char* expected_key_one = "test_key_one";
    char* expected_value_one = "test_value_one";

    char* expected_key_two = "test_key_one";
    char* expected_value_two = "test_value_one";

    // Test if insert function returns success
    if (map_insert(&map_test, expected_key_one, expected_value_one) == -1) {
        return 1;
    }

    if (map_insert(&map_test, expected_key_two, expected_value_two) == -1) {
        return 1;
    }

    // Test map to see if key-value pairs are inserted correctly
    if (map_test.keys[0] != expected_key_one) {
        return 1;
    }

    if (map_test.values[0] != expected_value_one) {
        return 1;
    }

    if (map_test.keys[0] != expected_key_two) {
        return 1;
    }

    if (map_test.values[0] != expected_value_two) {
        return 1;
    }

    return 0;
}

int map_test_delete(void) {
    struct Map map_test = map_init();

    // Test deleting empty array
    if (map_delete(&map_test, "test") != -1) {
        return 1;
    }

    // Add test values
    int length_arr = 4;
    char* arr_keys[] = {
        "key1",
        "key2",
        "key3",
        "key4"
    };
    char* arr_values[] = {
        "val1",
        "val2",
        "val3",
        "val4"
    };
    for (int i = 0; i < length_arr; i++) {
        map_insert(&map_test, arr_keys[i], arr_values[i]);
    }

    // Test deleting every key-value pair
    for (int i = 0; i < length_arr; i++) {
        if (map_delete(&map_test, arr_keys[i]) != 0) {
            return 1;
        }
    }

    // Check if map is empty
    if (map_test.current_count > 0) {
        return 1;
    }

    return 0;
}

int map_test_clear(void) {
    struct Map map_test = map_init();

    // Add test values
    int length_arr = 4;
    char* arr_keys[] = {
        "key1",
        "key2",
        "key3",
        "key4"
    };
    char* arr_values[] = {
        "val1",
        "val2",
        "val3",
        "val4"
    };
    for (int i = 0; i < length_arr; i++) {
        map_insert(&map_test, arr_keys[i], arr_values[i]);
    }

    // Test if key-value pairs are cleared
    map_clear(&map_test);
    if (map_test.current_count > 0) {
        return 1;
    }

    return 0;
}

int map_test_get(void) {
    struct Map map_test = map_init();

    // Test empty map
    if (map_get(&map_test, "empty") != NULL) {
        return 1;
    }

    // Add test values
    int length_arr = 4;
    char* arr_keys[] = {
        "key1",
        "key2",
        "key3",
        "key4"
    };
    char* arr_values[] = {
        "val1",
        "val2",
        "val3",
        "val4"
    };
    for (int i = 0; i < length_arr; i++) {
        map_insert(&map_test, arr_keys[i], arr_values[i]);
    }

    // Test if existing key can be found
    if (strcmp(map_get(&map_test, "key4"), "val4")) {
        return 1;
    }

    // Test if non-existent key is not found
    if (map_get(&map_test, "value5") != NULL) {
        return 1;
    }

    // Test if deleted key is not found
    map_delete(&map_test, "key4");
    if (map_get(&map_test, "val4") != NULL) {
        return 1;
    }

    return 0;
}

int main(void) {
    int num_failures = 0;
    int result;

    printf("Running map_test_insert... ");
    result = map_test_insert();
    if (result) {
        num_failures += result;
        printf("FAIL\n");
    }
    else {
        printf("PASS\n");
    }

    printf("Running map_test_delete... ");
    result = map_test_delete();
    if (result) {
        num_failures += result;
        printf("FAIL\n");
    }
    else {
        printf("PASS\n");
    }

    printf("Running map_test_clear... ");
    result = map_test_clear();
    if (result) {
        num_failures += result;
        printf("FAIL\n");
    }
    else {
        printf("PASS\n");
    }

    printf("Running map_test_get... ");
    result = map_test_get();
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