/**
 * Singly Linked List Implementation
 * 
 * This file contains the implementation of a singly linked list data structure,
 * which allows for efficient insertion and deletion of elements.
 * 
 * Features:
 * - Creation and destruction of lists
 * - Insertion at beginning, end, or specific position
 * - Deletion by value or position
 * - Search functionality
 * - Complete memory management
 * 
 * @author Ferdi Kanat
 * @version 1.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Node structure for the singly linked list
 */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/**
 * Singly linked list structure
 */
typedef struct SinglyLinkedList {
    Node* head;
    size_t size; // Track the size of the list
} SinglyLinkedList;

/* Function prototypes */
SinglyLinkedList* create_singly_linked_list(void);
bool insert_at_beginning(SinglyLinkedList* list, int data);
bool insert_at_end(SinglyLinkedList* list, int data);
bool insert_at_position(SinglyLinkedList* list, int data, size_t position);
bool delete_by_value(SinglyLinkedList* list, int data);
bool delete_at_position(SinglyLinkedList* list, size_t position);
Node* find_node(const SinglyLinkedList* list, int data);
void print_list(const SinglyLinkedList* list);
size_t get_size(const SinglyLinkedList* list);
bool is_empty(const SinglyLinkedList* list);
void clear_list(SinglyLinkedList* list);
void free_singly_linked_list(SinglyLinkedList* list);

/**
 * Main function demonstrating the usage of the singly linked list
 */
int main(void) {
    // Create a new singly linked list
    SinglyLinkedList* list = create_singly_linked_list();
    if (list == NULL) {
        fprintf(stderr, "ERROR: Failed to create list\n");
        return EXIT_FAILURE;
    }

    // Demonstrate insertion
    printf("Inserting elements at the beginning: 30, 20, 10\n");
    insert_at_beginning(list, 30);
    insert_at_beginning(list, 20);
    insert_at_beginning(list, 10);
    print_list(list);

    printf("Inserting element at the end: 40\n");
    insert_at_end(list, 40);
    print_list(list);

    printf("Inserting element at position 2: 25\n");
    insert_at_position(list, 25, 2);
    print_list(list);

    // Demonstrate search
    int search_value = 25;
    Node* found = find_node(list, search_value);
    if (found) {
        printf("Found value %d in the list\n", search_value);
    } else {
        printf("Value %d not found in the list\n", search_value);
    }

    // Demonstrate deletion
    printf("Deleting value 20 from the list\n");
    if (delete_by_value(list, 20)) {
        printf("Successfully deleted 20\n");
    } else {
        printf("Failed to delete 20\n");
    }
    print_list(list);

    printf("Deleting element at position 1\n");
    if (delete_at_position(list, 1)) {
        printf("Successfully deleted element at position 1\n");
    } else {
        printf("Failed to delete element at position 1\n");
    }
    print_list(list);

    printf("List size: %zu\n", get_size(list));

    // Clean up
    free_singly_linked_list(list);
    printf("List freed successfully\n");

    return EXIT_SUCCESS;
}

/**
 * Creates a new singly linked list
 * 
 * @return Pointer to the newly created list or NULL if allocation fails
 */
SinglyLinkedList* create_singly_linked_list(void) {
    SinglyLinkedList* list = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

/**
 * Inserts a new node with the given data at the beginning of the list
 * 
 * @param list Pointer to the list
 * @param data Data to be inserted
 * @return true if insertion was successful, false otherwise
 */
bool insert_at_beginning(SinglyLinkedList* list, int data) {
    if (list == NULL) {
        return false;
    }

    // Create a new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for new node\n");
        return false;
    }
    
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    
    return true;
}

/**
 * Inserts a new node with the given data at the end of the list
 * 
 * @param list Pointer to the list
 * @param data Data to be inserted
 * @return true if insertion was successful, false otherwise
 */
bool insert_at_end(SinglyLinkedList* list, int data) {
    if (list == NULL) {
        return false;
    }

    // Create a new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for new node\n");
        return false;
    }
    
    new_node->data = data;
    new_node->next = NULL;
    
    // If the list is empty, set the new node as the head
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        // Traverse to the last node
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->size++;
    return true;
}

/**
 * Inserts a new node with the given data at the specified position
 * 
 * @param list Pointer to the list
 * @param data Data to be inserted
 * @param position Position at which to insert (0-based index)
 * @return true if insertion was successful, false otherwise
 */
bool insert_at_position(SinglyLinkedList* list, int data, size_t position) {
    if (list == NULL) {
        return false;
    }
    
    // If position is 0, insert at the beginning
    if (position == 0) {
        return insert_at_beginning(list, data);
    }
    
    // If position is greater than the size, insert at the end
    if (position >= list->size) {
        return insert_at_end(list, data);
    }
    
    // Create a new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for new node\n");
        return false;
    }
    
    new_node->data = data;
    
    // Find the node at position - 1
    Node* current = list->head;
    for (size_t i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    // Insert the new node
    new_node->next = current->next;
    current->next = new_node;
    
    list->size++;
    return true;
}

/**
 * Deletes a node with the given data from the list
 * 
 * @param list Pointer to the list
 * @param data Data to be deleted
 * @return true if deletion was successful, false otherwise
 */
bool delete_by_value(SinglyLinkedList* list, int data) {
    if (list == NULL || list->head == NULL) {
        return false;
    }

    Node* current = list->head;
    Node* previous = NULL;
    
    // Find the node with the given data
    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    // If the node is found, delete it
    if (current != NULL) {
        if (previous == NULL) {
            // Node to delete is the head
            list->head = current->next;
        } else {
            previous->next = current->next;
        }
        free(current);
        list->size--;
        return true;
    }
    
    return false; // Node not found
}

/**
 * Deletes a node at the specified position
 * 
 * @param list Pointer to the list
 * @param position Position of the node to delete (0-based index)
 * @return true if deletion was successful, false otherwise
 */
bool delete_at_position(SinglyLinkedList* list, size_t position) {
    if (list == NULL || list->head == NULL || position >= list->size) {
        return false;
    }

    Node* current = list->head;
    Node* previous = NULL;
    
    // Find the node at the given position
    for (size_t i = 0; i < position && current != NULL; i++) {
        previous = current;
        current = current->next;
    }

    // If the node is found, delete it
    if (current != NULL) {
        if (previous == NULL) {
            // Node to delete is the head
            list->head = current->next;
        } else {
            previous->next = current->next;
        }
        free(current);
        list->size--;
        return true;
    }
    
    return false; // Node not found
}

/**
 * Finds a node with the given data in the list
 * 
 * @param list Pointer to the list
 * @param data Data to search for
 * @return Pointer to the node if found, NULL otherwise
 */
Node* find_node(const SinglyLinkedList* list, int data) {
    if (list == NULL) {
        return NULL;
    }

    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    
    return NULL; // Node not found
}

/**
 * Prints the elements of the list
 * 
 * @param list Pointer to the list
 */
void print_list(const SinglyLinkedList* list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return;
    }

    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    printf("List contents: ");
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/**
 * Returns the size of the list
 * 
 * @param list Pointer to the list
 * @return Size of the list, 0 if list is NULL
 */
size_t get_size(const SinglyLinkedList* list) {
    return (list != NULL) ? list->size : 0;
}

/**
 * Checks if the list is empty
 * 
 * @param list Pointer to the list
 * @return true if list is empty or NULL, false otherwise
 */
bool is_empty(const SinglyLinkedList* list) {
    return (list == NULL || list->head == NULL);
}

/**
 * Clears all elements from the list but keeps the list structure
 * 
 * @param list Pointer to the list
 */
void clear_list(SinglyLinkedList* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    list->head = NULL;
    list->size = 0;
}

/**
 * Frees all memory allocated for the list including the list structure
 * 
 * @param list Pointer to the list
 */
void free_singly_linked_list(SinglyLinkedList* list) {
    if (list == NULL) {
        return;
    }

    clear_list(list);
    free(list);
}