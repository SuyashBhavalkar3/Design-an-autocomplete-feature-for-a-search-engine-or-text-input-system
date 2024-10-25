#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26 // Assuming only lowercase a-z
#define MAX_WORD_LENGTH 100

// Trie Node structure
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord; // 1 if the node represents the end of a word
} TrieNode;

// Trie structure
typedef struct Trie {
    TrieNode *root;
} Trie;

// Function to create a new trie node
TrieNode* createNode() {
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to initialize the trie
Trie* createTrie() {
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    trie->root = createNode();
    return trie;
}

// Function to insert a word into the trie
void insert(Trie *trie, const char *word) {
    TrieNode *current = trie->root;
    while (*word) {
        int index = tolower(*word) - 'a'; // Convert char to index
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
        word++;
    }
    current->isEndOfWord = 1; // Mark the end of the word
}

// Function to collect suggestions
void collectSuggestions(TrieNode *current, char *prefix, int level) {
    // If current node is end of a word, print the prefix
    if (current->isEndOfWord) {
        prefix[level] = '\0'; // Null terminate the string
        printf("%s\n", prefix); // Print the word
    }

    // Traverse all possible children
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (current->children[i] != NULL) {
            prefix[level] = 'a' + i; // Assign the character to the prefix
            collectSuggestions(current->children[i], prefix, level + 1);
        }
    }
}

// Function to search for a prefix in the trie
void searchSuggestions(Trie *trie, const char *prefix) {
    TrieNode *current = trie->root;
    char prefixBuffer[MAX_WORD_LENGTH];
    int level = 0;

    // Navigate through the trie according to the prefix
    while (*prefix) {
        int index = tolower(*prefix) - 'a';
        if (current->children[index] == NULL) {
            printf("No suggestions found\n");
            return; // No words with the given prefix
        }
        prefixBuffer[level++] = *prefix; // Add to prefixBuffer
        current = current->children[index]; // Move to the next node
        prefix++;
    }

    // Collect suggestions from the current node
    collectSuggestions(current, prefixBuffer, level);
}

// Main function to demonstrate usage
// Main function to demonstrate usage
int main() {
    Trie *trie = createTrie();
    char input[MAX_WORD_LENGTH];
    
    // User input for inserting words
    printf("Enter words to insert into the trie (type 'exit' to stop):\n");
    while (1) {
        printf("Insert word: ");
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) {
            break; // Exit if the user types 'exit'
        }
        insert(trie, input);
    }

    // User input for autocomplete suggestions
    printf("Enter a prefix for suggestions (type 'exit' to stop):\n");
    while (1) {
        printf("Prefix: ");
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) {
            break; // Exit if the user types 'exit'
        }
        printf("Suggestions for '%s':\n", input);
        searchSuggestions(trie, input);
    }

    // Free the allocated memory (not implemented here for simplicity)

    return 0;
}

