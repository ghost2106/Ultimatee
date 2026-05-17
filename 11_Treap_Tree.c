#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Treap Node structure
struct Node {
    int key;
    int priority;
    struct Node *left, *right;
};

// Create a new Treap node
struct Node* createNode(int key) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->key = key;
    newNode->priority = rand() % 100;  // Random priority
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Right rotate
struct Node* rightRotate(struct Node* y) {

    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

// Left rotate
struct Node* leftRotate(struct Node* x) {

    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

// Insert a key into Treap (BST + Heap property)
struct Node* insert(struct Node* root, int key) {

    // Standard BST insertion
    if (root == NULL)
        return createNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);

        // If heap property is violated, rotate right
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }

    else if (key > root->key) {
        root->right = insert(root->right, key);

        // If heap property is violated, rotate left
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

    return root;
}

// Search for a key in Treap
struct Node* search(struct Node* root, int key) {

    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Delete a key from Treap
struct Node* deleteNode(struct Node* root, int key) {

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // Node found - delete it

        // If leaf node
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }

        // If only right child exists
        else if (root->left == NULL) {
            struct Node* temp = root;
            root = root->right;
            free(temp);
        }

        // If only left child exists
        else if (root->right == NULL) {
            struct Node* temp = root;
            root = root->left;
            free(temp);
        }

        // Two children - rotate based on priority
        else {
            if (root->left->priority > root->right->priority) {
                root = rightRotate(root);
                root->right = deleteNode(root->right, key);
            } else {
                root = leftRotate(root);
                root->left = deleteNode(root->left, key);
            }
        }
    }

    return root;
}

// Inorder Traversal
void inorder(struct Node* root) {

    if (root != NULL) {
        inorder(root->left);
        printf("Key: %d (Priority: %d)\n", root->key, root->priority);
        inorder(root->right);
    }
}

// Display tree structure
void displayTree(struct Node* root, int level) {

    if (root == NULL)
        return;

    displayTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d(p%d)\n", root->key, root->priority);

    displayTree(root->left, level + 1);
}

// Main function
int main() {

    srand(time(NULL));

    struct Node* root = NULL;
    int choice, value;
    struct Node* result;

    printf("===== TREAP TREE =====\n\n");

    while (1) {

        printf("\n--- Treap Menu ---\n");
        printf("1. Insert Key\n");
        printf("2. Search Key\n");
        printf("3. Delete Key\n");
        printf("4. Inorder Traversal\n");
        printf("5. Display Tree Structure\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &value);

                root = insert(root, value);

                printf("Key %d inserted with random priority.\n", value);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &value);

                result = search(root, value);

                if (result != NULL)
                    printf("Key %d found in Treap! (Priority: %d)\n",
                           result->key, result->priority);
                else
                    printf("Key %d NOT found in Treap.\n", value);
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &value);

                root = deleteNode(root, value);

                printf("Key %d deleted successfully.\n", value);
                break;

            case 4:
                printf("\nInorder Traversal:\n");
                inorder(root);
                break;

            case 5:
                printf("\nTree Structure (key(p) means key with priority p):\n");
                displayTree(root, 0);
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}