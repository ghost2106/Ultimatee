#include <stdio.h>
#include <stdlib.h>

// AVL Tree Node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get height
int height(struct Node *temp) {

    if (temp == NULL)
        return 0;

    return temp->height;
}

// Maximum of two numbers
int max(int a, int b) {

    if (a > b)
        return a;

    return b;
}

// Create new node
struct Node* createNode(int data) {

    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;  // New node height = 1

    return temp;
}

// Right Rotate
struct Node* rightRotate(struct Node* temp) {

    struct Node* ptr = temp->left;

    temp->left = ptr->right;
    ptr->right = temp;

    // Update heights
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    ptr->height = max(height(ptr->left), height(ptr->right)) + 1;

    return ptr;
}

// Left Rotate
struct Node* leftRotate(struct Node* temp) {

    struct Node* ptr = temp->right;

    temp->right = ptr->left;
    ptr->left = temp;

    // Update heights
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    ptr->height = max(height(ptr->left), height(ptr->right)) + 1;

    return ptr;
}

// Get Balance Factor
int getBalance(struct Node* temp) {

    if (temp == NULL)
        return 0;

    return height(temp->left) - height(temp->right);
}

// Insert Node
struct Node* insert(struct Node* temp, int data) {

    // Normal BST insertion
    if (temp == NULL)
        return createNode(data);

    if (data < temp->data)
        temp->left = insert(temp->left, data);

    else if (data > temp->data)
        temp->right = insert(temp->right, data);

    else
        return temp;  // Duplicate not allowed

    // Update height
    temp->height = 1 + max(height(temp->left), height(temp->right));

    // Get balance factor
    int balance = getBalance(temp);

    // Left Left Case
    if (balance > 1 && data < temp->left->data)
        return rightRotate(temp);

    // Right Right Case
    if (balance < -1 && data > temp->right->data)
        return leftRotate(temp);

    // Left Right Case
    if (balance > 1 && data > temp->left->data) {
        temp->left = leftRotate(temp->left);
        return rightRotate(temp);
    }

    // Right Left Case
    if (balance < -1 && data < temp->right->data) {
        temp->right = rightRotate(temp->right);
        return leftRotate(temp);
    }

    return temp;
}

// Find minimum value node
struct Node* minValueNode(struct Node* temp) {

    struct Node* ptr = temp;

    while (ptr->left != NULL)
        ptr = ptr->left;

    return ptr;
}

// Delete Node
struct Node* deleteNode(struct Node* temp, int data) {

    // Normal BST delete
    if (temp == NULL)
        return temp;

    if (data < temp->data)
        temp->left = deleteNode(temp->left, data);

    else if (data > temp->data)
        temp->right = deleteNode(temp->right, data);

    else {
        // Node found - delete it

        // Node with one child or no child
        if (temp->left == NULL || temp->right == NULL) {

            struct Node* ptr;

            if (temp->left != NULL)
                ptr = temp->left;
            else
                ptr = temp->right;

            // No child
            if (ptr == NULL) {
                ptr = temp;
                temp = NULL;
            }
            // One child
            else
                *temp = *ptr;

            free(ptr);
        }

        // Node with two children
        else {
            struct Node* ptr = minValueNode(temp->right);

            temp->data = ptr->data;

            temp->right = deleteNode(temp->right, ptr->data);
        }
    }

    // If tree had only one node
    if (temp == NULL)
        return temp;

    // Update height
    temp->height = 1 + max(height(temp->left), height(temp->right));

    // Get balance factor
    int balance = getBalance(temp);

    // Left Left Case
    if (balance > 1 && getBalance(temp->left) >= 0)
        return rightRotate(temp);

    // Left Right Case
    if (balance > 1 && getBalance(temp->left) < 0) {
        temp->left = leftRotate(temp->left);
        return rightRotate(temp);
    }

    // Right Right Case
    if (balance < -1 && getBalance(temp->right) <= 0)
        return leftRotate(temp);

    // Right Left Case
    if (balance < -1 && getBalance(temp->right) > 0) {
        temp->right = rightRotate(temp->right);
        return leftRotate(temp);
    }

    return temp;
}

// Search for a node
struct Node* search(struct Node* temp, int data) {

    if (temp == NULL || temp->data == data)
        return temp;

    if (data < temp->data)
        return search(temp->left, data);

    return search(temp->right, data);
}

// Inorder Traversal
void inorder(struct Node* temp) {

    if (temp != NULL) {
        inorder(temp->left);
        printf("%d ", temp->data);
        inorder(temp->right);
    }
}

// Main Function
int main() {

    struct Node* root = NULL;
    int choice, value;
    struct Node* result;

    while (1) {

        printf("\n--- AVL TREE MENU ---\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Inorder Traversal\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);

                root = insert(root, value);

                printf("Node %d inserted successfully.\n", value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);

                root = deleteNode(root, value);

                printf("Node %d deleted successfully.\n", value);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);

                result = search(root, value);

                if (result != NULL)
                    printf("Node %d found in AVL Tree.\n", value);
                else
                    printf("Node %d NOT found in AVL Tree.\n", value);
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}