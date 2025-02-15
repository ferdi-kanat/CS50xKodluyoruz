/**
 * @file caesar.c
 * @author Ferdi Kanat
 * @date 2025/02/11
 * 
 * @brief Encrypts a message using the Caesar cipher.
 * 
 * This program encrypts a message using the Caesar cipher. The Caesar cipher
 * is a substitution cipher where each letter in the plaintext is shifted a
 * certain number of places down the alphabet. For example, with a shift of 1,
 * 'A' would be replaced by 'B', 'B' would become 'C', and so on.
 * 
 * The Caesar cipher has a key, which is the number of positions each letter
 * should be shifted. The key is an integer from 1 to 25. The key is used to
 * encrypt the message by shifting the letters by the key positions.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_MESSAGE_SIZE 1000

/* Function prototypes */
void encrypt(char message[], int key);

int main(int argc, char *argv[])
{
    char message[MAX_MESSAGE_SIZE];
    int key;

    // Validate command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s key\n", argv[0]);
        return 1;
    }

    // Get the key from the command-line arguments
    if (sscanf(argv[1], "%d", &key) != 1)
    {
        fprintf(stderr, "Error: Key must be a positive integer.\n");
        return 1;
    }

    // Normalize key to be within 0-25
    key = key % 26;

    // Get the message to encrypt
    printf("plaintext: ");
    fgets(message, sizeof(message), stdin);

    // Remove newline if present
    size_t len = strlen(message);
    if (len > 0 && message[len-1] == '\n') {
        message[len-1] = '\0';
    }

    // Print encrypted message
    printf("ciphertext: ");
    encrypt(message, key);
    printf("%s\n", message);


    return 0;
}

/**
 * @brief Encrypts a message using the Caesar cipher.
 * @param message The message to encrypt.
 * @param key The key to use for encryption.
 */
void encrypt(char message[], int key)
{
    for (int i = 0; message[i] != '\0'; i++)
    {
        if (isalpha(message[i]))
        {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = ((message[i] - base + key) % 26) + base;
        }
    }
}