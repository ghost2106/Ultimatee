#include <stdio.h>
#include <stdlib.h>

// Red Black Tree Node
struct Node {
    int data;
    char color;               // 'R' for Red, 'B' for Black
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

// Create new node
struct Node* createNode(int data) {

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->color = 'R';     // New nodes are always red
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

// Left rotate
void leftRotate(struct Node *x) {

    struct Node *y = x->right;

    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;

    else if (x == x->parent->left)
        x->parent->left = y;

    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right rotate
void rightRotate(struct Node *y) {

    struct Node *x = y->left;

    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;

    else if (y == y->parent->left)
        y->parent->left = x;

    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix Red Black Tree properties after insertion
void fixInsert(struct Node *z) {

    while (z->parent != NULL && z->parent->color == 'R') {

        // Parent is left child of grandparent
        if (z->parent == z->parent->parent->left) {

            struct Node *y = z->parent->parent->right;  // Uncle

            // Case 1: Uncle is red -> just recolor
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }

            else {
                // Case 2: z is right child -> left rotate parent
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }

                // Case 3: z is left child -> right rotate grandparent
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(z->parent->parent);
            }
        }

        // Parent is right child of grandparent
        else {

            struct Node *y = z->parent->parent->left;  // Uncle

            // Case 1: Uncle is red -> just recolor
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }

            else {
                // Case 2: z is left child -> right rotate parent
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }

                // Case 3: z is right child -> left rotate grandparent
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(z->parent->parent);
            }
        }
    }

    // Root must always be black
    root->color = 'B';
}

// Insert a node into Red Black Tree
void insert(int data) {

    struct Node *z = createNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    // Standard BST insertion
    while (x != NULL) {
        y = x;

        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        root = z;

    else if (z->data < y->data)
        y->left = z;

    else
        y->right = z;

    // Fix Red Black Tree properties
    fixInsert(z);
}

// Search for a node
struct Node* search(struct Node *root, int key) {

    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// Inorder traversal (displays node with color)
void inorder(struct Node *root) {

    if (root != NULL) {
        inorder(root->left);
        printf("%d(%c) ", root->data, root->color);
        inorder(root->right);
    }
}

// Main function
int main() {

    int n, value, key;
    struct Node *result;

    printf("===== RED BLACK TREE =====\n\n");

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        insert(value);
    }

    printf("\nRed Black Tree (Inorder Traversal with colors):\n");
    inorder(root);
    printf("\n");

    printf("\nEnter value to search: ");
    scanf("%d", &key);

    result = search(root, key);

    if (result != NULL)
        printf("Node %d found in Red Black Tree.\n", key);
    else
        printf("Node %d NOT found in Red Black Tree.\n", key);

    return 0;
}