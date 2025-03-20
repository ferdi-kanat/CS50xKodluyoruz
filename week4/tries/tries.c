/**
 * @file tries.c
 * @brief A simple tree-like structure for storing and retrieving university names.
 *        Note: This is not a traditional trie but a fixed-depth tree with indexed paths.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Constants used throughout the trie implementation
 */
enum Constants
{
    MAX_PATHS = 10,      ///< Maximum number of paths from each node
    MAX_NAME_LENGTH = 20 ///< Maximum length for university names
};

/**
 * @brief Structure representing a node in the trie
 */
typedef struct TrieNode
{
    char* university;              ///< University name stored in this node
    struct TrieNode* paths[MAX_PATHS]; ///< Array of pointers to child nodes
} TrieNode;

// Function prototypes
TrieNode* trieCreateNode(const char* university);
bool trieInsert(TrieNode* root, const char* university, int index);
TrieNode* trieSearch(TrieNode* root, const char* university);
void trieDelete(TrieNode* root);
void triePrint(TrieNode* root, int level);

int main(void)
{
    TrieNode* root = trieCreateNode("Root University");
    if (!root)
    {
        fprintf(stderr, "Failed to create root node\n");
        return EXIT_FAILURE;
    }

    trieInsert(root, "Harvard", 0);
    trieInsert(root, "MIT", 1);
    trieInsert(root, "Stanford", 9);
        
    printf("Trie structure:\n");
    triePrint(root, 0);
    
    TrieNode* found = trieSearch(root, "MIT");
    if (found)
    {
        printf("Found %s\n", found->university);
    }
    else
    {
        printf("Not found\n");
    }
    
    trieDelete(root);
    return EXIT_SUCCESS;
}

/**
 * @brief Creates a new TrieNode with the given university name.
 * @param university Name to store in the node.
 * @return Pointer to the new node, or NULL if allocation fails.
 */
TrieNode* trieCreateNode(const char* university)
{
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    if (!newNode)
    {
        fprintf(stderr, "Memory allocation failed for node\n");
        return NULL;
    }
    
    newNode->university = (char*)malloc(strlen(university) + 1);
    if (!newNode->university)
    {
        free(newNode);
        fprintf(stderr, "Memory allocation failed for university name\n");
        return NULL;
    }

    strcpy(newNode->university, university);
    
    for (int i = 0; i < MAX_PATHS; i++)
    {
        newNode->paths[i] = NULL;
    }
    
    return newNode;
}

/**
 * @brief Insert a university into the trie at specified index
 * @param root Root node of the trie
 * @param university Name of the university to insert
 * @param index Path index where to insert the university
 * @return true if insertion was successful, false otherwise
 */
bool trieInsert(TrieNode* root, const char* university, int index)
{
    if (!root)
    {
        return false;
    }
    
    if (index < 0 || index >= MAX_PATHS)
    {
        fprintf(stderr, "Invalid index %d for insertion\n", index);
        return false;
    }
    
    if (root->paths[index])
    {
        fprintf(stderr, "Path already occupied at index %d\n", index);
        return false;
    }
    
    root->paths[index] = trieCreateNode(university);
    return (root->paths[index] != NULL);
}

/**
 * @brief Search for a university in the trie
 * @param root Root node of the trie
 * @param university Name of the university to search for
 * @return Pointer to node if found, NULL otherwise
 */
TrieNode* trieSearch(TrieNode* root, const char* university)
{
    if (!root)
    {
        return NULL;
    }
    
    if (strcmp(root->university, university) == 0)
    {
        return root;
    }
    
    for (int i = 0; i < MAX_PATHS; i++)
    {
        if (root->paths[i])
        {
            TrieNode* found = trieSearch(root->paths[i], university);
            if (found)
            {
                return found;
            }
        }
    }
    return NULL;
}

/**
 * @brief Delete the entire trie and free memory
 * @param root Root node of the trie to delete
 */
void trieDelete(TrieNode* root)
{
    if (!root)
    {
        return;
    }
    
    for (int i = 0; i < MAX_PATHS; i++)
    {
        if (root->paths[i])
        {
            trieDelete(root->paths[i]);
        }
    }
    
    free(root->university);
    free(root);
}

/**
 * @brief Print the trie structure with indentation showing tree levels
 * @param root Root node of the trie to print
 * @param level Current level of indentation
 */
void triePrint(TrieNode* root, int level)
{
    if (!root)
    {
        return;
    }
    
    for (int i = 0; i < level; i++)
    {
        printf("  ");
    }
    
    printf("%s\n", root->university);
    
    for (int i = 0; i < MAX_PATHS; i++)
    {
        if (root->paths[i])
        {
            triePrint(root->paths[i], level + 1);
        }
    }
}