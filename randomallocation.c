#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100

int memory[MAX_BLOCKS];

void contiguousAllocation(int numFiles, int fileSize[]) {
    for (int i = 0; i < numFiles; i++) {
        int startBlock = rand() % (MAX_BLOCKS - fileSize[i]);
        int canAllocate = 1;

        // Check if space is available for contiguous allocation
        for (int j = startBlock; j < startBlock + fileSize[i]; j++) {
            if (memory[j] == 1) {
                canAllocate = 0;
                break;
            }
        }

        if (canAllocate) {
            // Allocate memory for the file
            for (int j = startBlock; j < startBlock + fileSize[i]; j++) {
                memory[j] = 1;
            }
            printf("File %d allocated from block %d to block %d\n", i + 1, startBlock, startBlock + fileSize[i] - 1);
        } else {
            printf("File %d could not be allocated due to lack of space.\n", i + 1);
        }
    }
}

int main() {
    int numFiles;
    srand(time(NULL)); // For random number generation

    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    int fileSize[numFiles];
    for (int i = 0; i < numFiles; i++) {
        printf("Enter size of file %d: ", i + 1);
        scanf("%d", &fileSize[i]);
    }

    // Initialize memory
    for (int i = 0; i < MAX_BLOCKS; i++) {
        memory[i] = 0; // 0 means free
    }

    contiguousAllocation(numFiles, fileSize);

    return 0;
}
