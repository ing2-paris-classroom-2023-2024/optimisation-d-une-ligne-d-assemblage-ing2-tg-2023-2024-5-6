#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>

#define NB_OPERATIONS 35

typedef struct {
    int id;
    int lst_precedents[NB_OPERATIONS];
    float duree;
} Operation;

//void initialisation_precedence

void intialisation_operations(Operation lst_operations[]) {
    int i;
    for (i = 0; i < NB_OPERATIONS; i++) {
        lst_operations[i].id = i;
        lst_operations[i].duree = 0;
        //lst_operations[i].lst_precedents[] = {0};
    }
}


void readGraphFromFile(const char *filename, Operation operations[], int *numOperations) {

    FILE *file = fopen("graphe.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    *numOperations = 0;

    while (fscanf(file, "%d %d %f", &operations[*numOperations].id,
                  &operations[*numOperations].lst_precedents[0],
                  &operations[*numOperations].duree) == 3) {
        // Increment the operation count
        (*numOperations)++;
    }

    fclose(file);
}

void printOperations(const Operation operations[], int numOperations) {
    for (int i = 0; i < numOperations; i++) {
        printf("Operation %d:\n", operations[i].id);
        printf("  Duration: %.2f\n", operations[i].duree);
        printf("  Precedents: ");

        for (int j = 0; operations[i].lst_precedents[j] != 0; j++) {
            printf("%d ", operations[i].lst_precedents[j]);
        }

        printf("\n\n");
    }
}

int main() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;

    // Replace "your_file.txt" with the actual file name
    readGraphFromFile("your_file.txt", operations, &numOperations);

    printOperations(operations, numOperations);

    return 0;
}