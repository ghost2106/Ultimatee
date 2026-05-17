#include <stdio.h>

int tree[1000];   // Segment Tree array (size can be increased if needed)
int arr[1000];    // Original array

// Build the segment tree from the given array
void buildTree(int node, int start, int end) {

    if (start == end) {
        // Leaf node: store array element
        tree[node] = arr[start];
    }

    else {
        int mid = (start + end) / 2;

        // Recursively build left and right subtrees
        buildTree(2 * node, start, mid);
        buildTree(2 * node + 1, mid + 1, end);

        // Internal node: store sum of children
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// Update value at a specific index in the array
void updateTree(int node, int start, int end, int idx, int value) {

    if (start == end) {
        // Leaf node: update the value
        arr[idx] = value;
        tree[node] = value;
    }

    else {
        int mid = (start + end) / 2;

        // Go to left or right subtree
        if (idx <= mid)
            updateTree(2 * node, start, mid, idx, value);
        else
            updateTree(2 * node + 1, mid + 1, end, idx, value);

        // Update internal node after child update
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// Range Query: find sum in range [l, r]
int rangeQuery(int node, int start, int end, int l, int r) {

    // Case 1: No overlap
    if (r < start || end < l)
        return 0;

    // Case 2: Complete overlap
    if (l <= start && end <= r)
        return tree[node];

    // Case 3: Partial overlap - go to both children
    int mid = (start + end) / 2;

    int leftSum = rangeQuery(2 * node, start, mid, l, r);
    int rightSum = rangeQuery(2 * node + 1, mid + 1, end, l, r);

    return leftSum + rightSum;
}

// Print the segment tree array
void printTree(int size) {

    printf("Segment Tree Elements: ");

    for (int i = 1; i < 2 * size; i++)
        printf("%d ", tree[i]);

    printf("\n");
}

// Main function
int main() {

    int n;

    printf("===== SEGMENT TREE =====\n\n");

    printf("Enter size of array: ");
    scanf("%d", &n);

    printf("Enter %d array elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Build the segment tree
    buildTree(1, 0, n - 1);

    printf("\nAfter Building Tree:\n");
    printTree(n);

    // Update operation
    int idx, value;

    printf("\n--- Update Operation ---\n");
    printf("Enter index to update: ");
    scanf("%d", &idx);

    printf("Enter new value: ");
    scanf("%d", &value);

    updateTree(1, 0, n - 1, idx, value);

    printf("\nAfter Updating Index %d to %d:\n", idx, value);
    printTree(n);

    // Range Query
    int l, r;

    printf("\n--- Range Query ---\n");
    printf("Enter range (l r): ");
    scanf("%d %d", &l, &r);

    int sum = rangeQuery(1, 0, n - 1, l, r);

    printf("Sum in range [%d, %d] = %d\n", l, r, sum);

    return 0;
}