#include <stdio.h>
#include <stdlib.h>

// Structure of BST Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to insert a node in BST
struct Node* insert(struct Node* root, int data) {

    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);

    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Function to find minimum value node (inorder successor)
struct Node* minValueNode(struct Node* root) {

    struct Node* current = root;

    while (current != NULL && current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node from BST (handles all 3 cases)
struct Node* deleteNode(struct Node* root, int data) {

    // Base case: tree empty
    if (root == NULL)
        return root;

    // Recur down the tree
    if (data < root->data)
        root->left = deleteNode(root->left, data);

    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    else {
        // Node found - time to delete

        // Case 1: No child (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        else if (root->left == NULL) {
            // Only right child exists
            struct Node* temp = root->right;
            free(root);
            return temp;
        }

        else if (root->right == NULL) {
            // Only left child exists
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        else {
            // Find inorder successor (smallest in right subtree)
            struct Node* temp = minValueNode(root->right);

            // Copy inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}

// Inorder Traversal (Left -> Root -> Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder Traversal (Root -> Left -> Right)
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal (Left -> Right -> Root)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to display the tree structure
void displayTree(struct Node* root, int level) {
    if (root == NULL)
        return;

    displayTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d\n", root->data);

    displayTree(root->left, level + 1);
}

// Main function
int main() {

    struct Node* root = NULL;
    int choice, value;

    // Pre-insert some values
    int arr[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("===== BINARY SEARCH TREE DELETION =====\n\n");

    printf("Initial Tree:\n");
    displayTree(root, 0);

    printf("\nInorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Delete a node\n");
        printf("2. Display Tree Structure\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to delete: ");
                scanf("%d", &value);

                root = deleteNode(root, value);

                printf("\nTree after deletion:\n");
                displayTree(root, 0);
                break;

            case 2:
                printf("\nTree Structure:\n");
                displayTree(root, 0);
                break;

            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
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