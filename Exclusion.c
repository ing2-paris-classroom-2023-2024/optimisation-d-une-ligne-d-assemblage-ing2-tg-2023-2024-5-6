

// STRUCTURE DE DONNEES
#include <stdio.h>
#include <stdlib.h>

// STRUCTURE POUR REPRESENTER UN GRAPHE
typedef struct Graphe
{
    int nombre_sommets;
    int** matrice_adjacence;
} Graphe;

// FONCTION POUR INITIALISER UN GRAPHE
Graphe* initialiser_graphe(int nombre_sommets)
{

    // Allocation dynamique de la mémoire
    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));

    // Allocation dynamique de la mémoire et initialisation à 0 pour la matrice d'adjacence
    graphe->nombre_sommets = nombre_sommets;
    graphe->matrice_adjacence = (int**)malloc(nombre_sommets * sizeof(int*));
    for (int i = 0; i < nombre_sommets; i++)
    {
        graphe->matrice_adjacence[i] = (int*)malloc(nombre_sommets * sizeof(int));
        for (int j = 0; j < nombre_sommets; j++)
        {
            graphe->matrice_adjacence[i][j] = 0;
        }
    }
    return graphe;
}

// FONCTION POUR LIBERER LA MEMOIRE OCCUPEE PAR UN GRAPHE
void liberer_graphe(Graphe* graphe)
{
    for (int i = 0; i < graphe->nombre_sommets; i++)
    {
        free(graphe->matrice_adjacence[i]);
    }
    free(graphe->matrice_adjacence);
    free(graphe);
}

// FONCTION POUR AJOUTER UNE ARETE ENTRE DEUX SOMMETS
void ajouter_arete(Graphe* graphe, int sommet1, int sommet2)
{
    graphe->matrice_adjacence[sommet1][sommet2] = 1;
    graphe->matrice_adjacence[sommet2][sommet1] = 1;
}

// FONCTION POUR COLORER LE GRAPHE
void colorer_graphe(Graphe* graphe, int* coloration, int sommet, int nombre_couleurs)
{
    // Initialisation de toutes les couleurs à -1 (non coloré)
    for (int i = 0; i < graphe->nombre_sommets; i++)
    {
        coloration[i] = -1; // On utilise -1 pour indiquer que le sommet n'est pas coloré
    }

    // Coloration du sommet de départ
    coloration[0] = 0;
_________________________________________________________________________________________
    // Coloration des autres sommets
    for (int i = 1; i < graphe->nombre_sommets; i++)
    {
        // Initialisation de toutes les couleurs à 0 (non utilisé)
        int couleurs_utilisees[nombre_couleurs];
        for (int j = 0; j < nombre_couleurs; j++)
        {
            couleurs_utilisees[j] = 0;
        }

        // Parcours des sommets adjacents
        for (int j = 0; j < graphe->nombre_sommets; j++)
        {
            // Si le sommet est adjacent et coloré, on marque la couleur comme utilisée
            if (graphe->matrice_adjacence[i][j] == 1 && coloration[j] != -1)
            {
                couleurs_utilisees[coloration[j]] = 1;
            }
        }

        // Parcours des couleurs utilisées pour trouver la première couleur non utilisée
        for (int j = 0; j < nombre_couleurs; j++)
        {
            if (couleurs_utilisees[j] == 0)
            {
                coloration[i] = j;
                break;
            }
        }




    }
}


/*
 On applique l'allocation dynamique car,
 on ne connait pas la taille du tableau à l'avance
 et on ne sait pas si elle variera au cours du temps.
 */





/*
#define OPERATION_MAX 100
#define NB_STATIONS_MAX 10

// Structure pour représenter les contraintes d'exclusion
typedef struct
{
    int op1;
    int op2;
} Exclusion;

// Structure pour représenter la répartition des opérations sur les stations
typedef struct
{
    int station[OPERATION_MAX];
} Repartition;




// LECTURE DES FICHIERS DE CONTRAINTES

void LireFichierContraintes(char* nomFichier, Exclusion* exclusion, int* nbExclusions)
{
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    fscanf(fichier, "%d", nbExclusions);

    for (int i = 0; i < *nbExclusions; i++) {
        fscanf(fichier, "%d %d", &exclusion[i].op1, &exclusion[i].op2);
    }

    fclose(fichier);
}




// INITIALISATION DE LA REPARTITION DES OPERATIONS SUR LES STATIONS

void initialisationRepartition(Repartition* repartition)
{
    for (int i = 0; i < OPERATION_MAX; i++)
    {
        repartition->station[i] = -1;
    }
}


// SYSTEME DE VERIFICATION DE LA REPARTITION DES OPERATIONS SUR LES STATIONS

void verification (Repartition* repartition, Exclusion* exclusion, int nbExclusions)
{
    for (int i = 0; i < nbExclusions; i++)
    {
        if (repartition->station[exclusion[i].op1] == repartition->station[exclusion[i].op2])
        {
            printf("Erreur : les opérations %d et %d sont sur la même station\n", exclusion[i].op1, exclusion[i].op2);
            exit(EXIT_FAILURE);
        }
    }
}



// ATTRIBUTION DE LA REPARTITION DES OPERATIONS SUR LES STATIONS

void attributionRepartition(Repartition* repartition, const Exclusion exclusion[], int nbExclusions)
{
    int station = 1;
    for (int i = 0; i < nbExclusions; i++) {
        if (repartition->station[exclusion[i].op1 - 1] == -1) {
            repartition->station[exclusion[i].op1 - 1] = station;
        }

        if (repartition->station[exclusion[i].op2 - 1] == -1) {
            repartition->station[exclusion[i].op2 - 1] = station;
        }

        station = (station % NB_STATIONS_MAX) + 1;
    }
}

*/






