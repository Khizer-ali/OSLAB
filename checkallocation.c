#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100 // Total number of blocks in the memory

int blocks[MAX_BLOCKS]; // Array to track block allocation (0 = free, 1 = occupied)

// Function to check if a block is free
int isFree(int block) {
    return blocks[block] == 0;
}

// Function to allocate a block
void allocateBlock(int block) {
    blocks[block] = 1; // Mark block as allocated
}

int main() {
    int n; // Number of files
    int length, block; // Length of file (number of blocks) and block to allocate
    srand(time(NULL)); // Seed for random number generation

    // Initialize all blocks as free
    for (int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i] = 0;
    }

    printf("\n--- Post Lab Task: File Allocation ---\n");
    printf("Enter the number of files: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("\nFile %d:\n", i);
        printf("Enter the memory requirement (in blocks): ");
        scanf("%d", &length);

        int allocated = 0;

        while (!allocated) {
            block = rand() % MAX_BLOCKS; // Random block selection
            
            // Check if the selected block and required locations are free
            int free = 1;
            for (int j = 0; j < length; j++) {
                if (block + j >= MAX_BLOCKS || !isFree(block + j)) {
                    free = 0;
                    break;
                }
            }
            
            if (free) {
                // Allocate the required locations
                for (int j = 0; j < length; j++) {
                    allocateBlock(block + j);
                }
                printf("File %d allocated: Start Block = %d, Length = %d\n", i, block, length);
                allocated = 1;
            } else {
                printf("Block %d is not free. Retrying...\n", block);
            }
        }
    }

    // Display final allocation status
    printf("\n--- Final Memory Allocation Status ---\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Block %d: %s\n", i, blocks[i] ? "Occupied" : "Free");
    }

    return 0;}
