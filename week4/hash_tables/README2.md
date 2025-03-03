# Advanced Hash Table Implementation

This file describes a dynamically resizable hash table implementation in the C language.

## Features

- **Separate Chaining**: Collisions are resolved using linked lists
- **Dynamic Resizing**: Table automatically expands when load factor exceeds a threshold and shrinks when it falls too low
- **Flexible Capacity**: Initial capacity can be configured
- **Advanced Error Handling**: Better error catching with detailed error codes and user-friendly messages
- **Performance Optimization**: Optimized with prime number sizing and manual memory management
- **Gradual Growth and Shrinking**: Optimized memory usage with gradual growth and shrinking strategies

## Usage

```c
// Creating a hash table
HashTable *table = createHashTable(101); // A table with capacity of 101

// Adding an element
insert(table, "key", 42);

// Searching for an element
Element *elem = search(table, "key");
if (elem != NULL) {
    printf("Value: %d\n", elem->value);
}

// Deleting an element
deleteElement(table, "key");

// Printing the table
printHashTable(table);

// Freeing memory
freeHashTable(table);
```

## Error Codes and Messages

- `SUCCESS (0)`: Operation completed successfully
- `FAILURE (1)`: General error
- `MEMORY_ERROR (2)`: Memory allocation error
- `INVALID_INPUT (3)`: Invalid input parameters
- `KEY_NOT_FOUND (4)`: Key not found

You can use the `statusToString()` function to get user-friendly error messages:

```c
Status result = insert(table, "key", 100);
printf("Result: %s\n", statusToString(result));
```

## Performance Tips

1. Always choose a prime number for `DEFAULT_HASH_TABLE_SIZE`
2. Adjust the `RESIZE_UP_THRESHOLD` and `RESIZE_DOWN_THRESHOLD` values according to your application needs:
   - Higher thresholds (0.9) for memory-constrained systems
   - Lower thresholds (0.5) for speed-requiring systems
3. If you're adding a lot of data, create a larger table initially
4. Adjust the `RESIZE_GROWTH_FACTOR` to optimize memory consumption (default is 1.5)

## Improvements

This implementation includes the following improvements:

1. **Prime Number Table Size**: Provides better key distribution
2. **Gradual Growth Strategy**: Uses 1.5x growth factor to optimize memory usage with each resize
3. **Automatic Shrinking**: Table automatically shrinks when the load factor falls below threshold
4. **Safe Memory Management**: Improved resize algorithm for safer memory handling
5. **User-Friendly Error Messages**: Status codes are converted to readable text
6. **Load Factor Monitoring**: Makes it easier to monitor table performance
