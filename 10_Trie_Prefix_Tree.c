#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie Node Structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;   // 1 if word ends here, 0 otherwise
};

// Function to create a new Trie node
struct TrieNode* createNode() {

    struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode));

    node->isEndOfWord = 0;

    // Initialize all children as NULL
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    return node;
}

// Function to insert a word into Trie
void insert(struct TrieNode *root, char *key) {

    struct TrieNode *curr = root;

    // Traverse each character of the key
    for (int i = 0; key[i] != '\0'; i++) {

        int index = key[i] - 'a';    // Convert character to index (0-25)

        // Create node if path does not exist
        if (curr->children[index] == NULL)
            curr->children[index] = createNode();

        // Move to next node
        curr = curr->children[index];
    }

    // Mark the last node as end of word
    curr->isEndOfWord = 1;

    printf("Word '%s' inserted successfully.\n", key);
}

// Function to search a complete word in Trie
int search(struct TrieNode *root, char *key) {

    struct TrieNode *curr = root;

    // Traverse each character
    for (int i = 0; key[i] != '\0'; i++) {

        int index = key[i] - 'a';

        // If path does not exist, word is not present
        if (curr->children[index] == NULL)
            return 0;

        curr = curr->children[index];
    }

    // Return true only if complete word exists (end of word flag is set)
    return curr->isEndOfWord;
}

// Function to check if a prefix exists in Trie
int startsWith(struct TrieNode *root, char *prefix) {

    struct TrieNode *curr = root;

    // Traverse each character
    for (int i = 0; prefix[i] != '\0'; i++) {

        int index = prefix[i] - 'a';

        // If path does not exist, prefix is not present
        if (curr->children[index] == NULL)
            return 0;

        curr = curr->children[index];
    }

    // Prefix exists
    return 1;
}

// Main function
int main() {

    struct TrieNode *root = createNode();

    int choice;
    char word[100];

    printf("===== TRIE (PREFIX TREE) =====\n\n");

    while (1) {

        printf("\n--- Trie Operations Menu ---\n");
        printf("1. Insert Word\n");
        printf("2. Search Word\n");
        printf("3. Check Prefix\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter word to insert (lowercase only): ");
                scanf("%s", word);

                insert(root, word);
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%s", word);

                if (search(root, word))
                    printf("'%s' -> Found (Word exists in Trie)\n", word);
                else
                    printf("'%s' -> Not Found (Word does NOT exist in Trie)\n", word);

                break;

            case 3:
                printf("Enter prefix to check: ");
                scanf("%s", word);

                if (startsWith(root, word))
                    printf("'%s' -> Prefix Exists in Trie\n", word);
                else
                    printf("'%s' -> Prefix Does NOT Exist in Trie\n", word);

                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}