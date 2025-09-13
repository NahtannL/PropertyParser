#include "map.h"

struct Map map_init() {
    struct Map map = {.current_count = 0};
    return map;
}

int map_insert(struct Map* map, char* key, char* value) {
    // Check if map is full
    if (map->current_count == MAX_KEYS) {
        return -1;
    }

    // Update existing key if exists
    for (int i = 0; i < map->current_count; i++) {
        if (!strcmp(map->keys[i], key)) {
            map->values[i] = value;
            return 0;
        }
    }

    // Add new key-value pair
    map->keys[map->current_count] = key;
    map->values[map->current_count] = value;
    map->current_count++;
    return 0;
}

int map_delete(struct Map* map, char* key) {
    // Check if map is empty
    if (!map->current_count) {
        return -1;
    }

    // Find position of the key
    int pos = -1;
    for (int i = 0; i < map->current_count; i++) {
        if (!strcmp(map->keys[i], key)) {
            pos = i;
            break;
        }
    }

    // Return error if key is not found
    if (pos == -1) {
        return -1;
    }

    // Replace deleted key-value pair with the last key-value pair
    map->keys[pos] = map->keys[map->current_count-1];
    map->values[pos] = map->values[map->current_count-1];
    map->current_count--;
    return 0;
}

int map_clear(struct Map* map) {
    map->current_count = 0;
    return 0;
}

char* map_get(struct Map* map, char* key) {
    // Check if map is empty
    if (!map->current_count) {
        return NULL;
    }

    // Search for key
    for (int i = 0; i < map->current_count; i++) {
        if (!strcmp(map->keys[i], key)) {
            return map->values[i];
        }
    }

    return NULL;
}