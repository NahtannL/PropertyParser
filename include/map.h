/**
 * @author Nathan Lieu
 * @version 1.0
 * @date September 8, 2025
 * @brief Map implementation with key-value pairs
 * 
 * @details Provides map functionality in C with key-value pairs, and
 * basic functionality (eg. insert, delete, get, etc.).
 */

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <string.h>

/**
 * Max number of key-value pairs that can be stored in the map.
 */
#define MAX_KEYS 100

/**
 * A key-value map implementation using arrays.
 */
struct Map {
    char* keys[MAX_KEYS];
    char* values[MAX_KEYS];
    int current_count;
};

/**
 * Initialize a map.
 * 
 * @return struct Map
 */
struct Map map_init();

/**
 * Inserts a key-value pair into the map.
 * 
 * @param map The map struct to modify
 * @param key The key to insert
 * @param value The value to associate with the key
 * @return 1 on success, -1 if map is full
 * 
 * @note key-value pair is copied; stored pointer
 */
int map_insert(struct Map* map, char* key, char* value);

/**
 * Removes a key-value pair from the map.
 * 
 * @param map The map struct to modify 
 * @param key The key to remove
 * @return 0 on success, -1 if key not found or map empty
 */
int map_delete(struct Map* map, char* key);

/**
 * Clear all contents in map.
 * 
 * @param map The map struct to modify
 * @return 0 on success
 */
int map_clear(struct Map* map);

/**
 * Retrieves the value associated with the given key.
 * 
 * @param map The map struct to modify
 * @param key The key to lookup
 * @return the associated value, or NULL if not found
 */
char* map_get(struct Map* map, char* key);

#endif