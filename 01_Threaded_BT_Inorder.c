#include <stdio.h>
#include <stdlib.h>

// Structure of a Threaded Binary Tree Node
struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread;  // 1 = thread, 0 = real child
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = 1;  // Initially thread
    newNode->rthread = 1;  // Initially thread

    return newNode;
}

// Function to find inorder successor of a node
struct Node* inorderSuccessor(struct Node* ptr) {

    // If right is a thread, just go to right
    if (ptr->rthread == 1)
        return ptr->right;

    // Else go to right child and then find leftmost node
    ptr = ptr->right;

    while (ptr->lthread == 0)
        ptr = ptr->left;

    return ptr;
}

// Inorder traversal using threads (no recursion, no stack)
void inorder(struct Node* root) {

    if (root == NULL) {
        printf("Tree Empty!\n");
        return;
    }

    struct Node* ptr = root;

    // Go to leftmost node
    while (ptr->lthread == 0)
        ptr = ptr->left;

    // Now traverse using threads
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = inorderSuccessor(ptr);
    }

    printf("\n");
}

// Main function
int main() {

    // Creating nodes manually
    struct Node* root = createNode(1);
    struct Node* n2 = createNode(2);
    struct Node* n3 = createNode(3);
    struct Node* n4 = createNode(4);
    struct Node* n5 = createNode(5);

    /*
            1
          /   \
         2     3
        / \
       4   5
    */

    // Real child connections
    root->left = n2;
    root->right = n3;
    root->lthread = 0;
    root->rthread = 0;

    n2->left = n4;
    n2->right = n5;
    n2->lthread = 0;
    n2->rthread = 0;

    // Thread connections

    // 4 -> inorder successor = 2
    n4->right = n2;

    // 5 -> inorder successor = 1
    n5->right = root;

    // 5 -> inorder predecessor = 2
    n5->left = n2;

    // 3 -> inorder predecessor = 1
    n3->left = root;

    // Display inorder traversal
    printf("Threaded Binary Tree - Inorder Traversal:\n");
    inorder(root);

    return 0;
}