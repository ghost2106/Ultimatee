#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Job structure
typedef struct {
    int jobNo;
    char jobName[50];
    int priority;
} Job;

// Heap structure
typedef struct {
    Job arr[MAX];
    int size;
    int type; // 1 = Max Heap (high priority first), 0 = Min Heap (low priority first)
} Heap;

// Swap two jobs
void swap(Job *a, Job *b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

// Compare based on heap type
int compare(Job a, Job b, int type) {

    if (type == 1)      // Max Heap
        return a.priority > b.priority;
    else                // Min Heap
        return a.priority < b.priority;
}

// Heapify up (used after insertion)
void heapifyUp(Heap *h, int i) {

    int parent = (i - 1) / 2;

    if (i > 0 && compare(h->arr[i], h->arr[parent], h->type)) {
        swap(&h->arr[i], &h->arr[parent]);
        heapifyUp(h, parent);
    }
}

// Heapify down (used after deletion)
void heapifyDown(Heap *h, int i) {

    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int extreme = i;

    if (left < h->size && compare(h->arr[left], h->arr[extreme], h->type))
        extreme = left;

    if (right < h->size && compare(h->arr[right], h->arr[extreme], h->type))
        extreme = right;

    if (extreme != i) {
        swap(&h->arr[i], &h->arr[extreme]);
        heapifyDown(h, extreme);
    }
}

// Insert job into priority queue
void insert(Heap *h, Job j) {

    if (h->size == MAX) {
        printf("Heap Full! Cannot insert more jobs.\n");
        return;
    }

    h->arr[h->size] = j;
    heapifyUp(h, h->size);
    h->size++;

    printf("Job %s inserted successfully.\n", j.jobName);
}

// Peek at the highest priority job (for Max Heap) or lowest (for Min Heap)
void peek(Heap *h) {

    if (h->size == 0) {
        printf("Heap Empty! No jobs available.\n");
        return;
    }

    printf("\n=== Top Priority Job ===\n");

    if (h->type == 1)
        printf("(Highest Priority Job)\n");
    else
        printf("(Lowest Priority Job)\n");

    printf("Job No: %d\n", h->arr[0].jobNo);
    printf("Job Name: %s\n", h->arr[0].jobName);
    printf("Priority: %d\n", h->arr[0].priority);
}

// Delete the root job (highest or lowest priority)
void deleteRoot(Heap *h) {

    if (h->size == 0) {
        printf("Heap Empty! No jobs to delete.\n");
        return;
    }

    printf("\nDeleted Job: %s (Job No: %d, Priority: %d)\n",
           h->arr[0].jobName, h->arr[0].jobNo, h->arr[0].priority);

    h->arr[0] = h->arr[h->size - 1];
    h->size--;

    heapifyDown(h, 0);
}

// Display all jobs in the heap
void display(Heap *h) {

    if (h->size == 0) {
        printf("Heap Empty! No jobs to display.\n");
        return;
    }

    printf("\n=== Complete Job Queue ===\n");

    for (int i = 0; i < h->size; i++) {
        printf("Job No: %d | Name: %s | Priority: %d\n",
               h->arr[i].jobNo, h->arr[i].jobName, h->arr[i].priority);
    }
}

// Main function
int main() {

    Heap h;
    h.size = 0;

    int choice, type;
    Job j;

    printf("===== PRIORITY QUEUE - JOB SCHEDULING =====\n\n");

    printf("Choose Heap Type:\n");
    printf("1. Max Heap (High Priority First)\n");
    printf("0. Min Heap (Low Priority First)\n");
    printf("Enter choice: ");
    scanf("%d", &type);

    h.type = type;

    while (1) {

        printf("\n--- Job Queue Menu ---\n");
        printf("1. Insert Job\n");
        printf("2. Delete Top Job\n");
        printf("3. View Top Job\n");
        printf("4. Display All Jobs\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter Job No: ");
                scanf("%d", &j.jobNo);

                printf("Enter Job Name: ");
                scanf("%s", j.jobName);

                printf("Enter Priority: ");
                scanf("%d", &j.priority);

                insert(&h, j);
                break;

            case 2:
                deleteRoot(&h);
                break;

            case 3:
                peek(&h);
                break;

            case 4:
                display(&h);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}