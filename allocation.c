#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of memory blocks
#define MAX_BLOCKS 10

// Structure to represent a memory block
typedef struct {
    int size;
    int isFree;
    int processID;
} Block;

// Function prototypes
void initializeMemory(Block memory[], int n);
void displayMemory(Block memory[], int n);
int allocateMemory(Block memory[], int n, int size, int strategy, int processID);
int deallocateMemory(Block memory[], int n, int processID);
int firstFit(Block memory[], int n, int size);
int bestFit(Block memory[], int n, int size);
int worstFit(Block memory[], int n, int size);
void menu();

// Allocation strategies
#define FIRST_FIT 1
#define BEST_FIT 2
#define WORST_FIT 3

int main() {
    menu();
    return 0;
}

// Function to initialize memory blocks
void initializeMemory(Block memory[], int n) {
    for(int i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i+1);
        scanf("%d", &memory[i].size);
        memory[i].isFree = 1;    // Initially, all blocks are free
        memory[i].processID = 0; // No process allocated
    }
}

// Function to display the current state of memory
void displayMemory(Block memory[], int n) {
    printf("\nMemory Blocks:\n");
    printf("-------------------------------------------------\n");
    printf("| Block No | Size | Status | Process ID |\n");
    printf("-------------------------------------------------\n");
    for(int i = 0; i < n; i++) {
        printf("|    %2d    |  %3d |  %s  |     %d     |\n",
               i+1,
               memory[i].size,
               memory[i].isFree ? "Free" : "Occupied",
               memory[i].processID);
    }
    printf("-------------------------------------------------\n\n");
}

// Function to allocate memory based on strategy
int allocateMemory(Block memory[], int n, int size, int strategy, int processID) {
    int index = -1;
    switch(strategy) {
        case FIRST_FIT:
            index = firstFit(memory, n, size);
            break;
        case BEST_FIT:
            index = bestFit(memory, n, size);
            break;
        case WORST_FIT:
            index = worstFit(memory, n, size);
            break;
        default:
            printf("Invalid allocation strategy.\n");
            return -1;
    }

    if(index != -1) {
        memory[index].isFree = 0;
        memory[index].processID = processID;
        printf("Process %d allocated to Block %d.\n", processID, index+1);
        return index;
    } else {
        printf("No suitable block found for Process %d.\n", processID);
        return -1;
    }
}

// First-Fit strategy
int firstFit(Block memory[], int n, int size) {
    for(int i = 0; i < n; i++) {
        if(memory[i].isFree && memory[i].size >= size) {
            return i;
        }
    }
    return -1;
}

// Best-Fit strategy
int bestFit(Block memory[], int n, int size) {
    int bestIdx = -1;
    int minWaste = __INT32_MAX__;
    for(int i = 0; i < n; i++) {
        if(memory[i].isFree && memory[i].size >= size) {
            int waste = memory[i].size - size;
            if(waste < minWaste) {
                minWaste = waste;
                bestIdx = i;
            }
        }
    }
    return bestIdx;
}

// Worst-Fit strategy
int worstFit(Block memory[], int n, int size) {
    int worstIdx = -1;
    int maxWaste = -1;
    for(int i = 0; i < n; i++) {
        if(memory[i].isFree && memory[i].size >= size) {
            int waste = memory[i].size - size;
            if(waste > maxWaste) {
                maxWaste = waste;
                worstIdx = i;
            }
        }
    }
    return worstIdx;
}

// Function to deallocate memory
int deallocateMemory(Block memory[], int n, int processID) {
    int found = 0;
    for(int i = 0; i < n; i++) {
        if(memory[i].processID == processID) {
            memory[i].isFree = 1;
            memory[i].processID = 0;
            printf("Process %d deallocated from Block %d.\n", processID, i+1);
            found = 1;
        }
    }
    if(!found) {
        printf("Process %d not found.\n", processID);
    }
    return found;
}

// Function to display menu and handle user input
void menu() {
    int n;
    printf("=== Memory Allocation Simulation ===\n");
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    if(n <= 0 || n > MAX_BLOCKS) {
        printf("Invalid number of blocks. Please enter a value between 1 and %d.\n", MAX_BLOCKS);
        return;
    }

    Block memory[n];
    initializeMemory(memory, n);
    displayMemory(memory, n);

    int choice;
    int processID = 1; // Start process IDs from 1
    while(1) {
        printf("Choose an action:\n");
        printf("1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Memory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            int size, strategy;
            printf("Enter size of the process to allocate: ");
            scanf("%d", &size);
            printf("Choose Allocation Strategy:\n");
            printf("1. First-Fit\n");
            printf("2. Best-Fit\n");
            printf("3. Worst-Fit\n");
            printf("Enter your choice: ");
            scanf("%d", &strategy);
            allocateMemory(memory, n, size, strategy, processID);
            processID++;
        }
        else if(choice == 2) {
            int pid;
            printf("Enter Process ID to deallocate: ");
            scanf("%d", &pid);
            deallocateMemory(memory, n, pid);
        }
        else if(choice == 3) {
            displayMemory(memory, n);
        }
        else if(choice == 4) {
            printf("Exiting program.\n");
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}
