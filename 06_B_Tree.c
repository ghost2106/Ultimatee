#include <stdio.h>
#include <stdlib.h>

#define MAX 3   // Maximum children = 3 (3-Way B Tree)
#define MIN 1   // Minimum keys

struct BTreeNode {
    int keys[MAX];
    struct BTreeNode *child[MAX + 1];
    int count;
    int leaf;
};

struct BTreeNode *root = NULL;

// Create new node
struct BTreeNode* createNode(int leaf) {

    struct BTreeNode *newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));

    newNode->count = 0;
    newNode->leaf = leaf;

    for (int i = 0; i <= MAX; i++)
        newNode->child[i] = NULL;

    return newNode;
}

// Split child
void splitChild(struct BTreeNode *parent, int i, struct BTreeNode *fullChild) {

    struct BTreeNode *newNode = createNode(fullChild->leaf);

    newNode->count = MIN;

    // Copy last keys to new node
    for (int j = 0; j < MIN; j++)
        newNode->keys[j] = fullChild->keys[j + MIN + 1];

    // Copy children if not leaf
    if (!fullChild->leaf) {
        for (int j = 0; j <= MIN; j++)
            newNode->child[j] = fullChild->child[j + MIN + 1];
    }

    fullChild->count = MIN;

    // Shift parent's children
    for (int j = parent->count; j >= i + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[i + 1] = newNode;

    // Shift parent's keys
    for (int j = parent->count - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    // Move middle key to parent
    parent->keys[i] = fullChild->keys[MIN];

    parent->count++;
}

// Insert into non-full node
void insertNonFull(struct BTreeNode *node, int key) {

    int i = node->count - 1;

    // If leaf node
    if (node->leaf) {

        // Shift greater keys
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->count++;
    }

    else {

        // Find child position
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        // If child full, split
        if (node->child[i]->count == MAX) {

            splitChild(node, i, node->child[i]);

            if (key > node->keys[i])
                i++;
        }

        insertNonFull(node->child[i], key);
    }
}

// Insert key
void insert(int key) {

    // If tree empty
    if (root == NULL) {

        root = createNode(1);
        root->keys[0] = key;
        root->count = 1;

        return;
    }

    // If root full
    if (root->count == MAX) {

        struct BTreeNode *newRoot = createNode(0);

        newRoot->child[0] = root;

        splitChild(newRoot, 0, root);

        int i = 0;

        if (key > newRoot->keys[0])
            i++;

        insertNonFull(newRoot->child[i], key);

        root = newRoot;
    }

    else {
        insertNonFull(root, key);
    }
}

// Inorder traversal
void inorder(struct BTreeNode *node) {

    if (node != NULL) {

        int i;

        for (i = 0; i < node->count; i++) {

            inorder(node->child[i]);

            printf("%d ", node->keys[i]);
        }

        inorder(node->child[i]);
    }
}

// Main Function
int main() {

    int n, value;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        insert(value);
    }

    printf("\nInorder Traversal:\n");
    inorder(root);
    printf("\n");

    return 0;
}