#include "main.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

// Lecture du fichier.txt
/*void lecture_fichier() {
    FILE* fichier = fopen("graphe.txt", "r");
    char mot[100];

    if (fichier != NULL) {
        while (fscanf(fichier, "%s", mot) != EOF) {
            printf("%s\n", mot);
        }
        fclose(fichier);
    }
}*/
// Lecture du fichier.txt et extraction de min et max
int lecture_fichier(int* min, int* max)
{
    FILE* fichier = fopen("graphe.txt", "r");
    int nombre;

    if (fichier != NULL)
    {
        *min = INT_MAX;
        *max = INT_MIN;

        while (fscanf(fichier, "%d", &nombre) != EOF) {
            // Met à jour la valeur minimale si nécessaire
            if (nombre < *min)
            {
                *min = nombre;
            }

            // Met à jour la valeur maximale si nécessaire
            if (nombre > *max)
            {
                *max = nombre;
            }
        }

        fclose(fichier);

        // Vérifie si des valeurs ont été lues du fichier
        if (*min == INT_MAX && *max == INT_MIN)
        {
            fprintf(stderr, "Le fichier est vide ou ne contient pas de valeurs entières.\n");
            return 1; // Retourne une valeur d'erreur
        }
        else
        {
            return 0; // Retourne 0 en cas de succès
        }
    }
    else
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1; // Retourne une valeur d'erreur
    }
}

// Détermine le minimum et le maximum dans un ensemble de nombres à partir d'un fichier.
void echelle()
{
    FILE* fichier = fopen("graphe.txt", "r");

    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int min = INT_MAX;
    int max = INT_MIN;
    int nombre = 0;

    while (fscanf(fichier, "%d", &nombre) == 1)
    {
        if (nombre < min)
        {
            min = nombre;
        }

        if (nombre > max)
        {
            max = nombre;
        }
    }

    fclose(fichier);

    if (min == INT_MAX && max == INT_MIN)
    {
        printf("Le fichier est vide ou ne contient pas de valeurs entières.\n");
    }
    else
    {
        printf("Valeur minimale : %d\n", min);
        printf("Valeur maximale : %d\n", max);
    }
}

// Crée un bloc avec tous les éléments du min au max.
void CreationBloc(int min, int max, int bloc[])
{
    for (int i = 0; i < max - min + 1; i++)
    {
        bloc[i] = min + i;
    }
}


// Place les éléments dans le bloc en fonction des contraintes.
void PlaceElements(int min, int max, int blocA[], int n)
{
    int* blocB = malloc(n * sizeof(int));
    if (blocB == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        return;
    }

    int indexA = 0;
    int indexB = 0;
    bool contrainte = false;

    for (int i = 0; i < n; i++)
    {
        contrainte = false;

        if (i > 0 && blocA[indexA + i - 1] == i + min - 1)
        {
            contrainte = true;
        }

        if (contrainte)
        {
            blocB[indexB] = i + min;
            indexB++;
        }
        else
        {
            blocA[indexA] = i + min;
            indexA++;
        }
    }

    // Affiche le contenu des blocs
    printf("Bloc A : ");
    for (int i = 0; i < indexA; i++)
    {
        printf("%d ", blocA[i]);
    }
    printf("\n");

    printf("Bloc B : ");
    for (int i = 0; i < indexB; i++)
    {
        printf("%d ", blocB[i]);
    }
    printf("\n");

    free(blocB); // Libère la mémoire allouée dynamiquement
}

int main()
{
    int min, max;
    int* blocA;

    // Appeler la fonction lecture_fichier pour obtenir min et max
    if (lecture_fichier(&min, &max) != 0)
    {
        // Gérer l'erreur si la lecture du fichier échoue
        return 1;
    }

    printf("Min : %d\n", min);
    printf("Max : %d\n", max);

    int n = max - min + 1;

    blocA = malloc(n * sizeof(int));
    if (blocA == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        return 1;
    }

    CreationBloc(min, max, blocA);
    PlaceElements(min, max, blocA, n);

    // Libération de la mémoire
    free(blocA);

    return 0;
}