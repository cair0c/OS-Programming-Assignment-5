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

#define MAX_FRAMES 10

int main(int argc, char *argv[]) {
    // checking for the correct amount of arguments in input
    if (argc != 2) {
        printf("Incorrect argument input.\n");
        return 1;
    }

    char *pageRefFile = argv[1];
    int numFrames = atoi(argv[1]);

    // opening file
    FILE *file = fopen(pageRefFile, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // checking for correct number of frames
    if (numFrames < 1 || numFrames > MAX_FRAMES) {
        printf("Number of frames should be between 1 and 10 inclusive");
        return 1;
    }

    // read page references from the file
    int pages[MAX_FRAMES * 10];
    int num_pages = 0;
    int page;
    while (fscanf(file, "%d", &page) == 1) {
        pages[num_pages++] = page;
    }
    fclose(file);


}
