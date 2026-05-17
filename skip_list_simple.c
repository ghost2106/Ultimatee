#include <stdio.h>
#include <stdlib.h>

#define LEVELS 4

struct Node {
    int key;
    struct Node *right;
    struct Node *down;
};

struct Node *head[LEVELS];

struct Node *createNode(int key) {
    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    newNode->key = key;
    newNode->right = NULL;
    newNode->down = NULL;

    return newNode;
}

void create() {
    int i;

    for (i = 0; i < LEVELS; i++) {
        head[i] = createNode(-1);

        if (i > 0) {
            head[i]->down = head[i - 1];
        }
    }
}

void insertLevel0(int values[], int n) {
    struct Node *temp = head[0];

    int i;

    for (i = 0; i < n; i++) {
        struct Node *newNode = createNode(values[i]);

        temp->right = newNode;
        temp = temp->right;
    }
}

void createUpperLevels() {
    int level;

    for (level = 1; level < LEVELS; level++) {

        struct Node *lower = head[level - 1]->right;
        struct Node *upper = head[level];

        int index = 0;

        while (lower != NULL) {

            if (index % 2 == 0) {

                struct Node *newNode =
                    createNode(lower->key);

                newNode->down = lower;

                upper->right = newNode;
                upper = upper->right;
            }

            lower = lower->right;
            index++;
        }
    }
}

int search(int key) {

    struct Node *curr = head[LEVELS - 1];

    while (curr != NULL) {

        while (curr->right != NULL &&
               curr->right->key <= key) {

            curr = curr->right;
        }

        if (curr->key == key) {
            return 1;
        }

        curr = curr->down;
    }

    return 0;
}

void display() {

    int level;

    printf("\n===== SKIP LIST =====\n");

    for (level = LEVELS - 1; level >= 0; level--) {

        printf("Level %d: ", level);

        struct Node *temp = head[level]->right;

        while (temp != NULL) {

            printf("%d -> ", temp->key);

            temp = temp->right;
        }

        printf("NULL\n");
    }
}

int main() {

    int n;
    int values[100];
    int choice;
    int key;

    create();

    while (1) {

        printf("\n===== SKIP LIST =====\n");

        printf("1. Insert Values\n");
        printf("2. Search Value\n");
        printf("3. Display Skip List\n");
        printf("0. Exit\n");

        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {

        case 1:

            printf("Enter number of elements: ");
            scanf("%d", &n);

            printf("Enter sorted elements: ");

            int i;

            for (i = 0; i < n; i++) {
                scanf("%d", &values[i]);
            }

            insertLevel0(values, n);

            createUpperLevels();

            printf("Skip List created successfully!\n");

            break;

        case 2:

            printf("Enter key to search: ");
            scanf("%d", &key);

            if (search(key)) {
                printf("Key found!\n");
            }
            else {
                printf("Key not found!\n");
            }

            break;

        case 3:

            display();

            break;

        case 0:

            return 0;

        default:

            printf("Invalid choice!\n");
        }
    }

    return 0;
}
