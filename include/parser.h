/**
 * @file parser.h
 * @author Nathan Lieu
 * @version 1.0
 * @date September 8, 2025
 * 
 * @brief Properties file parser
 * 
 * This library provides functionality to parse .properties files and extract
 * key-value pairs into a map structure.
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <regex.h>

#include "map.h"
#include "cstring.h"

/**
 * @brief Seperator character used to splot key-value pairs
 * 
 * Key and value components in the .properties file is divided by this 
 * character.
 */
#define SEPERATOR ":"

/**
 * @brief Parser object that maintains parser state
 * 
 * Contains the information map, file handle, and parsing status needed to
 * process a .properties file.
 */
struct Parser_Obj {
    /**
     * Map storing key-value pairs
     */
    struct Map info;

    /**
     * File handle for the properties file
     */
    FILE* in_file;

    /**
     * Flag indicating if parser is ready (1) or not (0)
     */
    int parse_ready;
};

/**
 * @brief Initializes a new parser object
 * 
 * Creates and initializes a new Parser_Obj with default values. Initializes
 * the info map with map_init() and sets parse_ready to 0.
 * 
 * @return Initialized Parser_Obj structure
 * 
 * @example
 * ```
 * struct Parser_Obj parser = parser_init();
 * ```
 * 
 * @see map_init()
 */
struct Parser_Obj parser_init(void);

/**
 * @brief Opens a properties file for parsing
 * 
 * Validates that the specified file has a .properties extension, which is then
 * opened for reading. Sets parse_ready flag if successful.
 * 
 * @param parser_obj Pointer to parser object
 * @param file_path Path to the .properties file to open
 * 
 * @return 0 on success, or one of the following error codes otherwise:
 *      -1: Regex compilation error
 *      -2: File doesn't have .properties extension
 *      -3: File could not be opened
 * 
 * @example
 * ```
 * struct Parser_Obj parser = parser_init();
 * int result = parser_open_file(&parser, "config.properties");
 * ```
 */
int parser_open_file(struct Parser_Obj* parser_obj, char* file_path);

/**
 * @brief Parses the .properties file
 * 
 * Reads the file line by line, extracting key-value pairs seperated by the
 * SEPERATOR character. Whitespace found in the key and value strings are
 * trimmed before being stored in the map.
 * 
 * @param parser_obj Pointer to the parser object
 * 
 * @return 0 on success, or one of the following error codes otherwise:
 *      -1: Parser not ready or string copy error
 *      -2: Invalid .properties file formatting
 * 
 * @note Function allocates memory for key and value strings
 * 
 * @example
 * ```
 * struct Parser_Obj parser = parser_init();
 * if (!parser_open_file(&parser, "config.properties")) {
 *      // Error handling
 *      printf("Error\n");
 *      return 1;
 * }
 * 
 * if (!parser_parse(&parser)) {
 *      // Error handling
 *      printf("Error\n");
 *      return 1;
 * }
 * 
 * char* value = map_get(&parser.info, "username");
 * ```
 * 
 * @see SEPERATOR 
 */
int parser_parse(struct Parser_Obj* parser_obj);

/**
 * @brief Closes the currently open .properties file
 * 
 * Closes the open file handle and sets parse_ready to 0. Should be called when
 * done with parsing to free resources.
 * 
 * @param parser_obj Pointer to a parser object
 * 
 * @return 0 on success, or -1 on failure
 */
int parser_close_file(struct Parser_Obj* parser_obj);

/**
 * @brief Retrieves a value by key from the info map
 * 
 * @param parser_obj Pointer to a parser object
 * @param key The lookup key
 * 
 * @return The associated value, or NULL if not found
 */
char* parser_get_value(struct Parser_Obj* parser_obj, char* key);

/**
 * @brief Frees all memory allocated by the parser
 * 
 * Cleans up the memory for the key-value pairs and closes the .properties file
 * if still open.
 * 
 * @param parser_obj Pointer to a parser object
 * 
 * @return 0 on success
 */
int parser_cleanup(struct Parser_Obj* parser_obj);

#endif