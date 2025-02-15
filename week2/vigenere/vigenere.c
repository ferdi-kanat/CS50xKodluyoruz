/**
 * @file vigenere.c
 * @author Ferdi Kanat
 * @date 2025/02/15
 * 
 * @brief Encrypts a message using the Vigenère cipher.
 * 
 * This program encrypts a message using the Vigenère cipher. The Vigenère cipher
 * is a polyalphabetic substitution cipher where each letter in the plaintext is
 * shifted a certain number of places down the alphabet. The number of places to
 * shift each letter is determined by a keyword. The keyword is a string of letters
 * that is repeated to match the length of the message.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define MAX_MESSAGE_SIZE 1000

/* Function prototypes */
static bool is_alpha_string(const char *str);
void encrypt(char message[], char keyword[]);
int shift(char c);

int main(int argc, char *argv[])
{
    // Check argument count
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s keyword\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Validate keyword is alphabetic
    if (!is_alpha_string(argv[1])) 
    {
        fprintf(stderr, "Keyword must be alphabetic\n");
        return EXIT_FAILURE;
    }

    char message[MAX_MESSAGE_SIZE];
    char keyword[MAX_MESSAGE_SIZE];

    // Copy validated keyword 
    strncpy(keyword, argv[1], MAX_MESSAGE_SIZE - 1);
    keyword[MAX_MESSAGE_SIZE - 1] = '\0';

    // Get plaintext
    printf("plaintext: ");
    if (!fgets(message, sizeof(message), stdin))
    {
        return EXIT_FAILURE;
    }

    // Remove newline
    size_t len = strlen(message);
    if (len > 0 && message[len-1] == '\n')
    {
        message[len-1] = '\0';
    }

    // Print encrypted message
    printf("ciphertext: ");
    encrypt(message, keyword);

    return EXIT_SUCCESS;
}

/**
 * @brief Checks if string contains only alphabetic characters
 * @param str String to check
 * @return true if string is alphabetic, false otherwise
 */
static bool is_alpha_string(const char *str) 
{
    while (*str) 
    {
        if (!isalpha(*str)) 
        {
            return false;
        }
        str++;
    }
    return true;
}

/**
 * Encrypts a message using the Vigenère cipher.
 * 
 * @param message The message to encrypt.
 * @param keyword The keyword to use for encryption.
 */
void encrypt(char message[], char keyword[])
{
    int keylen = strlen(keyword);
    int key[keylen];

    // Convert keyword to key
    for (int i = 0; i < keylen; i++)
    {
        key[i] = shift(keyword[i]);
    }

    // Encrypt message
    for (int i = 0, j = 0; message[i] != '\0'; i++)
    {
        if (isalpha(message[i]))
        {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = ((message[i] - base + key[j]) % 26) + base;
            j = (j + 1) % keylen;
        }
        printf("%c", message[i]);
    }

    printf("\n");
}

/**
 * Returns the shift value for a given character.
 * 
 * @param c The character to get the shift value for.
 * @return The shift value for the character.
 */
int shift(char c)
{
    return isupper(c) ? c - 'A' : c - 'a';
}