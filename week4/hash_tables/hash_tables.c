/**
 * Hash Table Implementation in C
 * A personal experiment for CS50x, collaboratively developed
 * with multiple AI assistants to explore the limits of AI-driven coding.
 * Not intended for production use, purely an educational artifact.
 * 
 * @authors: Claude Sonnet, GPT-4o, Grok 3
 * @date: 03/03/2025
 * @version: 1.4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Constants */
#define DEFAULT_HASH_TABLE_SIZE 101
#define RESIZE_GROWTH_FACTOR 1.5  // More gradual growth factor
#define RESIZE_UP_THRESHOLD 0.75  // When to grow the table
#define RESIZE_DOWN_THRESHOLD 0.25 // When to shrink the table

typedef enum {
    SUCCESS = 0,
    FAILURE = 1,
    MEMORY_ERROR = 2,
    INVALID_INPUT = 3,
    KEY_NOT_FOUND = 4
} Status;

/**
 * Hash table element structure with key-value pair
 */
typedef struct Element {
    char *key;            /* Dynamically allocated string key */
    int value;            /* Integer value associated with the key */
    struct Element *next; /* Pointer to next element in the chain */
} Element;

/**
 * Hash table structure
 */
typedef struct HashTable {
    Element **buckets;   /* Array of pointers to element chains */
    size_t size;         /* Current number of elements in the hash table */
    size_t capacity;     /* Current capacity of the hash table */
} HashTable;

/* Function prototypes */
HashTable *createHashTable(size_t initialCapacity);
unsigned int hash(const char *key, size_t tableSize);
Element *createElement(const char *key, int value);
Status insert(HashTable *hashTable, const char *key, int value);
Status resize(HashTable *hashTable, size_t newCapacity);
Element *search(const HashTable *hashTable, const char *key);
Status deleteElement(HashTable *hashTable, const char *key);
void printHashTable(const HashTable *hashTable);
void freeHashTable(HashTable *hashTable);
double getLoadFactor(const HashTable *hashTable);
const char *statusToString(Status status); // New function for user-friendly error messages

/**
 * Main function to demonstrate hash table operations
 */
int main(void) {
    HashTable *myHashTable = createHashTable(DEFAULT_HASH_TABLE_SIZE);
    if (myHashTable == NULL) {
        fprintf(stderr, "Failed to create hash table\n");
        return EXIT_FAILURE;
    }

    /* Insert elements */
    insert(myHashTable, "key1", 1);
    insert(myHashTable, "key2", 2);
    insert(myHashTable, "key3", 3);
    
    printf("Hash table after insertions:\n");
    printHashTable(myHashTable);
    
    /* Search for an element */
    Element *element = search(myHashTable, "key2");
    if (element != NULL) {
        printf("\nElement found: Key: %s, Value: %d\n\n", element->key, element->value);
    } else {
        printf("\nElement not found\n\n");
    }
    
    /* Delete an element */
    Status deleteStatus = deleteElement(myHashTable, "key2");
    if (deleteStatus == SUCCESS) {
        printf("Element with key 'key2' deleted successfully\n\n");
    } else {
        printf("Failed to delete element with key 'key2', reason: %s\n\n", 
               statusToString(deleteStatus));
    }
    
    printf("Hash table after deletion:\n");
    printHashTable(myHashTable);
    
    /* Test performance with many elements */
    printf("\nAdding 1000 elements to test performance...\n");
    for (int i = 0; i < 1000; i++) {
        char key[20];
        sprintf(key, "perfkey%d", i);
        Status insertStatus = insert(myHashTable, key, i);
        if (insertStatus != SUCCESS) {
            printf("Failed to insert key '%s', reason: %s\n", 
                   key, statusToString(insertStatus));
        }
    }
    
    printf("Current load factor: %.2f\n", getLoadFactor(myHashTable));
    printf("Current capacity: %zu\n", myHashTable->capacity);
    printf("Current size: %zu\n", myHashTable->size);
    
    /* Test shrinking by removing many elements */
    printf("\nRemoving 800 elements to test shrinking...\n");
    for (int i = 0; i < 800; i++) {
        char key[20];
        sprintf(key, "perfkey%d", i);
        deleteElement(myHashTable, key);
    }
    
    printf("After deletion - load factor: %.2f\n", getLoadFactor(myHashTable));
    printf("After deletion - capacity: %zu\n", myHashTable->capacity);
    printf("After deletion - size: %zu\n", myHashTable->size);
    
    /* Clean up */
    freeHashTable(myHashTable);
    
    return EXIT_SUCCESS;
}

/**
 * Converts a status code to a human-readable string
 *
 * @param status The status code to convert
 * @return A string representation of the status
 */
const char *statusToString(Status status) {
    switch (status) {
        case SUCCESS: return "Success";
        case FAILURE: return "General failure";
        case MEMORY_ERROR: return "Memory allocation failed";
        case INVALID_INPUT: return "Invalid input";
        case KEY_NOT_FOUND: return "Key not found";
        default: return "Unknown status";
    }
}

/**
 * Calculates the current load factor of the hash table
 *
 * @param hashTable The hash table
 * @return The load factor (elements / capacity)
 */
double getLoadFactor(const HashTable *hashTable) {
    if (hashTable == NULL || hashTable->capacity == 0) {
        return 0.0;
    }
    return (double)hashTable->size / hashTable->capacity;
}

/**
 * Creates a new hash table with specified initial capacity
 * 
 * @param initialCapacity The initial capacity of the hash table
 * @return Pointer to newly created hash table or NULL if allocation fails
 */
HashTable *createHashTable(size_t initialCapacity) {
    if (initialCapacity == 0) {
        initialCapacity = DEFAULT_HASH_TABLE_SIZE;
    }
    
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        return NULL;
    }
    
    hashTable->buckets = (Element **)calloc(initialCapacity, sizeof(Element *));
    if (hashTable->buckets == NULL) {
        free(hashTable);
        return NULL;
    }
    
    hashTable->size = 0;
    hashTable->capacity = initialCapacity;
    return hashTable;
}

/**
 * Computes hash value for a given key using the djb2 algorithm
 * 
 * @param key The key to hash
 * @param tableSize The size of the hash table
 * @return Hash value between 0 and tableSize-1
 */
unsigned int hash(const char *key, size_t tableSize) {
    if (key == NULL || tableSize == 0) {
        return 0;
    }
    
    unsigned long hash = 5381;
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    return hash % tableSize;
}

/**
 * Creates a new element with the given key-value pair
 * 
 * @param key The key for the element
 * @param value The value associated with the key
 * @return Pointer to the new element or NULL if allocation fails
 */
Element *createElement(const char *key, int value) {
    if (key == NULL) {
        return NULL;
    }
    
    Element *newElement = (Element *)malloc(sizeof(Element));
    if (newElement == NULL) {
        return NULL;
    }
    
    size_t keyLength = strlen(key);
    newElement->key = (char *)malloc(keyLength + 1);
    if (newElement->key == NULL) {
        free(newElement);
        return NULL;
    }
    
    strcpy(newElement->key, key);
    newElement->value = value;
    newElement->next = NULL;
    return newElement;
}

/**
 * Resizes the hash table to the new capacity
 * 
 * @param hashTable The hash table to resize
 * @param newCapacity The new capacity for the hash table
 * @return SUCCESS on successful resize, error code otherwise
 */
Status resize(HashTable *hashTable, size_t newCapacity) {
    if (hashTable == NULL || newCapacity == 0) {
        return INVALID_INPUT;
    }
    
    /* Create a new bucket array */
    Element **newBuckets = (Element **)calloc(newCapacity, sizeof(Element *));
    if (newBuckets == NULL) {
        return MEMORY_ERROR;
    }
    
    /* Save old bucket array and capacity */
    Element **oldBuckets = hashTable->buckets;
    size_t oldCapacity = hashTable->capacity;
    
    /* Update hash table with new buckets */
    hashTable->buckets = newBuckets;
    hashTable->capacity = newCapacity;
    
    /* Rehash all elements into the new buckets */
    for (size_t i = 0; i < oldCapacity; i++) {
        Element *current = oldBuckets[i];
        while (current != NULL) {
            Element *next = current->next;
            
            /* Compute new hash and insert at the front of the new bucket */
            unsigned int newIndex = hash(current->key, newCapacity);
            current->next = hashTable->buckets[newIndex];
            hashTable->buckets[newIndex] = current;
            
            current = next;
        }
    }
    
    /* Free old buckets array */
    free(oldBuckets);
    
    return SUCCESS;
}

/**
 * Inserts a key-value pair into the hash table
 * If the key already exists, updates its value
 * Automatically resizes the table if load factor exceeds threshold
 * 
 * @param hashTable The hash table to insert into
 * @param key The key to insert
 * @param value The value to associate with the key
 * @return SUCCESS on successful insertion, error code otherwise
 */
Status insert(HashTable *hashTable, const char *key, int value) {
    if (hashTable == NULL || key == NULL) {
        return INVALID_INPUT;
    }
    
    /* Check load factor and resize if necessary */
    if (getLoadFactor(hashTable) >= RESIZE_UP_THRESHOLD) {
        size_t newCapacity = (size_t)(hashTable->capacity * RESIZE_GROWTH_FACTOR);
        if (newCapacity <= hashTable->capacity) {
            newCapacity = hashTable->capacity + 1; // Ensure we grow at least by 1
        }
        Status resizeStatus = resize(hashTable, newCapacity);
        if (resizeStatus != SUCCESS) {
            return resizeStatus;
        }
    }
    
    Element *existing = search(hashTable, key);
    if (existing != NULL) {
        existing->value = value; /* Update */
        return SUCCESS;
    }
    
    unsigned int index = hash(key, hashTable->capacity);
    Element *newElement = createElement(key, value);
    if (newElement == NULL) {
        return MEMORY_ERROR;
    }
    
    newElement->next = hashTable->buckets[index];
    hashTable->buckets[index] = newElement;
    hashTable->size++;
    return SUCCESS;
}

/**
 * Searches for an element with the given key
 * 
 * @param hashTable The hash table to search in
 * @param key The key to search for
 * @return Pointer to the element if found, NULL otherwise
 */
Element *search(const HashTable *hashTable, const char *key) {
    if (hashTable == NULL || key == NULL) {
        return NULL;
    }
    
    unsigned int index = hash(key, hashTable->capacity);
    Element *current = hashTable->buckets[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Deletes an element with the given key from the hash table
 * 
 * @param hashTable The hash table to delete from
 * @param key The key of the element to delete
 * @return SUCCESS if element was deleted, KEY_NOT_FOUND if not found, error code otherwise
 */
Status deleteElement(HashTable *hashTable, const char *key) {
    if (hashTable == NULL || key == NULL) {
        return INVALID_INPUT;
    }
    
    unsigned int index = hash(key, hashTable->capacity);
    Element *current = hashTable->buckets[index];
    Element *prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            /* Remove element from the chain */
            if (prev == NULL) {
                hashTable->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            
            /* Free memory */
            free(current->key);
            free(current);
            
            hashTable->size--;
            
            /* Check if we should shrink the table */
            if (getLoadFactor(hashTable) < RESIZE_DOWN_THRESHOLD && 
                hashTable->capacity > DEFAULT_HASH_TABLE_SIZE) {
                size_t newCapacity = hashTable->capacity / 2;
                if (newCapacity < DEFAULT_HASH_TABLE_SIZE) {
                    newCapacity = DEFAULT_HASH_TABLE_SIZE;
                }
                resize(hashTable, newCapacity);
            }
            
            return SUCCESS;
        }
        
        prev = current;
        current = current->next;
    }
    
    return KEY_NOT_FOUND; /* Key not found */
}

/**
 * Prints all key-value pairs in the hash table
 * 
 * @param hashTable The hash table to print
 */
void printHashTable(const HashTable *hashTable) {
    if (hashTable == NULL) {
        printf("Hash table is NULL\n");
        return;
    }
    
    if (hashTable->size == 0) {
        printf("Hash table is empty\n");
        return;
    }
    
    printf("Hash table contents (%zu elements, capacity %zu, load factor %.2f):\n", 
           hashTable->size, hashTable->capacity, getLoadFactor(hashTable));
           
    for (size_t i = 0; i < hashTable->capacity; i++) {
        Element *current = hashTable->buckets[i];
        if (current != NULL) {
            printf("Bucket %zu: ", i);
            while (current != NULL) {
                printf("[%s: %d] ", current->key, current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

/**
 * Frees all memory allocated for the hash table
 * 
 * @param hashTable The hash table to free
 */
void freeHashTable(HashTable *hashTable) {
    if (hashTable == NULL) {
        return;
    }
    
    /* Free each element and its key */
    for (size_t i = 0; i < hashTable->capacity; i++) {
        Element *current = hashTable->buckets[i];
        while (current != NULL) {
            Element *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    
    /* Free the buckets array and hash table structure */
    free(hashTable->buckets);
    free(hashTable);
}