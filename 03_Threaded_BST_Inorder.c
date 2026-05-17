#include <stdio.h>
#include <stdlib.h>

// Structure for Threaded BST Node
struct Node {
    int data;
    struct Node *left, *right;
    int lbit, rbit;  // 0 = real child, 1 = thread
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lbit = 1;  // Initially thread
    newNode->rbit = 1;  // Initially thread

    return newNode;
}

// Function to insert a value into Threaded BST
struct Node* insert(struct Node* root, int data) {

    struct Node *ptr = root;
    struct Node *par = NULL;

    // Find the position to insert
    while (ptr != NULL) {

        if (data == ptr->data) {
            printf("Duplicate key: %d\n", data);
            return root;
        }

        par = ptr;

        if (data < ptr->data) {
            if (ptr->lbit == 0)       // Real left child exists
                ptr = ptr->left;
            else
                break;                // Left is thread, found position
        }

        else {
            if (ptr->rbit == 0)       // Real right child exists
                ptr = ptr->right;
            else
                break;                // Right is thread, found position
        }
    }

    // Create new node
    struct Node* newNode = createNode(data);

    // If tree is empty
    if (par == NULL) {
        root = newNode;
        newNode->left = NULL;
        newNode->right = NULL;
    }

    // Insert as left child
    else if (data < par->data) {
        newNode->left = par->left;     // Inherit predecessor thread
        newNode->right = par;          // Thread to parent (successor)
        par->lbit = 0;                 // Mark as real child
        par->left = newNode;
    }

    // Insert as right child
    else {
        newNode->left = par;           // Thread to parent (predecessor)
        newNode->right = par->right;   // Inherit successor thread
        par->rbit = 0;                 // Mark as real child
        par->right = newNode;
    }

    return root;
}

// Function to find leftmost node (smallest)
struct Node* findLeftmost(struct Node* node) {

    if (node == NULL)
        return NULL;

    while (node->lbit == 0)    // While real left child exists
        node = node->left;

    return node;
}

// Inorder Traversal using threads (no recursion, no stack)
void inorder(struct Node* root) {

    if (root == NULL) {
        printf("Tree is empty!\n");
        return;
    }

    struct Node* cur = findLeftmost(root);

    while (cur != NULL) {
        printf("%d ", cur->data);

        // If right is thread, follow it to successor
        if (cur->rbit == 1)
            cur = cur->right;

        // Else go to leftmost of right child
        else
            cur = findLeftmost(cur->right);
    }

    printf("\n");
}

// Main function
int main() {

    struct Node* root = NULL;
    int n, value;

    printf("===== THREADED BINARY SEARCH TREE =====\n\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nInorder Traversal (using threads): ");
    inorder(root);

    return 0;
}