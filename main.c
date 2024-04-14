// Cairo Crawford PantherID: 6389250
// Cedric Cherestal PantherID: 5512167
// Camila Castaneda PantherID: 6059028
//
// This program is meant to determine how many page faults will occur when using
// both FIFO and LRU replacement policies. This program takes in a command from
// the command line with 2 arguments containing the reference file and the amount
// of frames then output the number of page faults and the final state of the
// memory.

#include <stdio.h>
#include <stdlib.h>

//declaring function prototypes
int findPosition(int value, int *array, int size);
int findLRU(int *timestamps, int size);
void printResults(char *policy, int pageFaults, int *frames, int numberOfFrames);

int main(int argc, char *argv[])
{
    //input validation
    if (argc != 3)
    {
        printf("Usage: %s pagereffile numberofframes\n", argv[0]);
        return 1;
    }

    int numberOfFrames = atoi(argv[2]);

    //more input validation
    if (numberOfFrames < 1 || numberOfFrames > 10)
    {
        printf("Number of frames must be between 1 and 10.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    //error handling
    if (!file)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int *framesFIFO = (int *)malloc(numberOfFrames * sizeof(int));
    int *framesLRU = (int *)malloc(numberOfFrames * sizeof(int));
    int *timestamps = (int *)malloc(numberOfFrames * sizeof(int));
    int page, pos, currentTime = 0, fifoIndex = 0;
    int pageFaultsFIFO = 0, pageFaultsLRU = 0;

    for (int i = 0; i < numberOfFrames; i++)
    {
        framesFIFO[i] = -1;
        framesLRU[i] = -1;
        timestamps[i] = 0;
    }

    while (fscanf(file, "%d", &page) != EOF)
    {
        currentTime++;

        // FIFO implementation
        if (findPosition(page, framesFIFO, numberOfFrames) == -1) {
            framesFIFO[fifoIndex] = page;
            fifoIndex = (fifoIndex + 1) % numberOfFrames;
            pageFaultsFIFO++;
        }

        // LRU implementation
        pos = findPosition(page, framesLRU, numberOfFrames);
        if (pos == -1) {
            pos = findLRU(timestamps, numberOfFrames);
            framesLRU[pos] = page;
            pageFaultsLRU++;
        }
        timestamps[pos] = currentTime;
    }

    fclose(file);

    printResults("FIFO", pageFaultsFIFO, framesFIFO, numberOfFrames);
    printResults("LRU", pageFaultsLRU, framesLRU, numberOfFrames);

    //free memory to prevent leaks
    free(framesFIFO);
    free(framesLRU);
    free(timestamps);

    return 0;
}

int findPosition(int value, int *array, int size) {

    for (int i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            return i;
        }
    }
    return -1;
}

int findLRU(int *timestamps, int size) {
    int min = timestamps[0];
    int pos = 0;
    for (int i = 1; i < size; i++)
    {
        if (timestamps[i] < min)
        {
            min = timestamps[i];
            pos = i;
        }
    }
    return pos;
}

void printResults(char *policy, int pageFaults, int *frames, int numberOfFrames) {
    printf("%s: %d page faults\n", policy, pageFaults);
    printf("Final state of memory: ");
    for (int i = 0; i < numberOfFrames; i++)
    {
        printf("%d ", frames[i]);
    }
    printf("\n");
}
