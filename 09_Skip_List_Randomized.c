#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 4
#define P 0.5

// Skip List Node
struct Node {
    int key;
    struct Node *forward[MAX_LEVEL];
};

// Create a new node
struct Node* createNode(int key, int level) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->key = key;

    for (int i = 0; i < MAX_LEVEL; i++)
        newNode->forward[i] = NULL;

    return newNode;
}

// Generate random level for a new node
int randomLevel() {

    int level = 1;

    while ((float)rand() / RAND_MAX < P && level < MAX_LEVEL)
        level++;

    return level;
}

// Insert a key into the skip list
void insert(struct Node *header, int key) {

    struct Node *update[MAX_LEVEL];
    struct Node *curr = header;

    // Find position to insert at each level
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {

        while (curr->forward[i] != NULL && curr->forward[i]->key < key)
            curr = curr->forward[i];

        update[i] = curr;
    }

    curr = curr->forward[0];

    // If key does not already exist, insert it
    if (curr == NULL || curr->key != key) {

        int level = randomLevel();

        struct Node *newNode = createNode(key, level);

        // Update pointers at each level
        for (int i = 0; i < level; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        printf("Inserted %d at level %d\n", key, level);
    }
}

// Search for a key in the skip list
int search(struct Node *header, int key) {

    struct Node *curr = header;

    // Start from highest level and go down
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {

        while (curr->forward[i] && curr->forward[i]->key < key)
            curr = curr->forward[i];
    }

    curr = curr->forward[0];

    if (curr && curr->key == key)
        return 1;   // Found

    return 0;       // Not found
}

// Display the skip list at all levels
void display(struct Node *header) {

    printf("\n=== Skip List (All Levels) ===\n");

    for (int i = MAX_LEVEL - 1; i >= 0; i--) {

        printf("Level %d: ", i);

        struct Node *node = header->forward[i];

        while (node != NULL) {
            printf("%d ", node->key);
            node = node->forward[i];
        }

        printf("\n");
    }
}

// Main function
int main() {

    srand(time(NULL));

    // Create header node
    struct Node *header = createNode(-1, MAX_LEVEL);

    int n, key, s;

    printf("===== SKIP LIST =====\n\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(header, key);
    }

    // Display the skip list
    display(header);

    // Search for a key
    printf("\nEnter element to search: ");
    scanf("%d", &s);

    if (search(header, s))
        printf("%d found in Skip List!\n", s);
    else
        printf("%d NOT found in Skip List!\n", s);

    return 0;
}
