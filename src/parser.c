#include "parser.h"

struct Parser_Obj parser_init(void) {
    struct Parser_Obj parser_obj = {.info = map_init(), .parse_ready = 0};
    return parser_obj;
}

int parser_open_file(struct Parser_Obj* parser_obj, char* file_path) {
    regex_t regex_extension;
    int result = regcomp(&regex_extension, "\\.properties$", REG_EXTENDED);
    if (result) {
        return -1;
    }

    // Execute regex comparison
    result = regexec(&regex_extension, file_path, 0, NULL, 0);
    regfree(&regex_extension); // Free compiled regex pattern

    if (result == REG_NOMATCH) {
        parser_obj->parse_ready = 0;
        return -2; // File doesn't have .properties extension
    }

    parser_obj->in_file = fopen(file_path, "r");

    if (parser_obj->in_file == NULL) {
        parser_obj->parse_ready = 0;
        return -3;
    }

    parser_obj->parse_ready = 1;

    return 0;
}

int parser_parse(struct Parser_Obj* parser_obj) {
    if (!parser_obj->parse_ready) {
        return -1;
    }

    char line[MAX_KEYS];
    while (fgets(line, MAX_KEYS, parser_obj->in_file)) {
        int current_line_length = strlen(line);
        // Ensure line is valid
        if (!current_line_length) {
            continue;
        }

        // Seperate key and value by seperator
        size_t chars_to_seperator = strcspn(line, ":");
        if (chars_to_seperator == current_line_length) {
            // Continue if seperator not found
            continue;
        }

        // Define key and value substrings
        char* key_str = (char*) malloc(sizeof(char) * (chars_to_seperator+1));
        char* value_str = (char*) malloc(sizeof(char) * 
            (current_line_length - chars_to_seperator + 1));

        if (!cstrncpy(key_str, line, 0, chars_to_seperator)) {
            return -1;
        }

        if (!cstrncpy(value_str, line, chars_to_seperator+1, 
            current_line_length)) {
                return -1;
        }

        // Check invalid formatting
        if (!strtok(value_str, ":")) {
            return -2;
        }

        // Remove leading and trailing whitespace in both the key and value
        // substrings
        cstrtrim(key_str);
        cstrtrim(value_str);

        // Store key and value in map
        map_insert(&parser_obj->info, key_str, value_str);
    }

    return 0;
}

int parser_close_file(struct Parser_Obj* parser_obj) {
    if (!parser_obj->parse_ready) {
        return 0;
    }

    if (fclose(parser_obj->in_file) == EOF) {
        return -1;
    }

    return 0;
}

char* parser_get_value(struct Parser_Obj* parser_obj, char* key) {
    char* retrieved_value = map_get(&parser_obj->info, key);

    if (!retrieved_value) {
        return NULL;
    }

    return retrieved_value;
}

int parser_cleanup(struct Parser_Obj* parser_obj) {
    if (parser_obj->parse_ready) {
        parser_close(parser_obj);
    }

    if (!parser_obj->info.current_count) {
        return 0;
    }

    for (int i = 0; i < parser_obj->info.current_count; i++) {
        free(parser_obj->info.keys[i]);
        free(parser_obj->info.values[i]);
    }

    return 0;
}