
#include <stdio.h>
#include <stdlib.h>

typedef struct Graphe {
    int ordre;
    char** noms_sommets;
} Graphe;


#include <stdio.h>
#include <stdlib.h>

typedef struct Graphe {
    int ordre;
    char** noms_sommets;
} Graphe;

Graphe* CreerGraphe(int ordre) {
    Graphe* Newgraphe = (Graphe*)malloc(sizeof(Graphe));
    Newgraphe->ordre = ordre;
    Newgraphe->noms_sommets = (char**)malloc(ordre * sizeof(char*));

    for (int i = 0; i < ordre; i++) {
        Newgraphe->noms_sommets[i] = (char*)malloc(2 * sizeof(char)); // Assuming two-character names
        // Initialise les noms des sommets à des chaînes vides
        Newgraphe->noms_sommets[i][0] = '\0';
        Newgraphe->noms_sommets[i][1] = '\0';
    }

    // Allocation de la mémoire pour la matrice des capacités des arcs
    Newgraphe->capacites_arcs = (int**)malloc(ordre * sizeof(int*));
    for (int i = 0; i < ordre; i++) {
        Newgraphe->capacites_arcs[i] = (int*)malloc(ordre * sizeof(int));
    }

    return Newgraphe;
}

// Fonction pour lire le fichier et appeler les fonctions CreeArete
// et CreerGraphe afin de transposer le graphe du fichier en structure de données
Graphe* lire_graphe(const char* nom_fichier) {
    FILE* ifs = fopen(nom_fichier, "r");
    if (!ifs) {
        printf("\n\n#### ERREUR ####\nFichier '%s' non trouvé, est-il bien dans le dossier du projet ?\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    int ordre;
    fscanf(ifs, "%d", &ordre);
    Graphe* graphe = CreerGraphe(ordre);

    // Lecture des noms des sommets
    for (int i = 0; i < ordre; ++i) {
        fscanf(ifs, "%s", graphe->noms_sommets[i]);
    }

    // Lecture des capacités des arcs
    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            fscanf(ifs, "%d", &graphe->capacites_arcs[i][j]);
        }
    }

    fclose(ifs);
    return graphe;
}

void afficher_graphe(Graphe* graphe) {
    printf("### AFFICHAGE DU GRAPHE ###\nOrdre du graphe: %d\n", graphe->ordre);

    printf("Liste des sommets:\n");
    for (int i = 0; i < graphe->ordre; i++) {
        printf("%s\n", graphe->noms_sommets[i]);
    }

    printf("#############################################\n\n");
}

void colorer_graphe(Graphe* graphe, int* coloration) {
    for (int i = 0; i < graphe->ordre; i++) {
        coloration[i] = i; // Attribution de couleurs indépendamment de la connectivité
    }
}

int main() {
    char nom_fichier[100];
    printf("Veuillez entrer le nom du fichier : ");
    scanf("%99s", nom_fichier);

    Graphe* g = lire_graphe(nom_fichier);
    afficher_graphe(g);

    int* coloration = (int*)malloc(g->ordre * sizeof(int));

    colorer_graphe(g, coloration);

    printf("### COULEURS ATTRIBUÉES AUX SOMMETS ###\n");
    for (int i = 0; i < g->ordre; i++) {
        printf("Sommet %s : Couleur %d\n", g->noms_sommets[i], coloration[i]);
    }

    // Libérer la mémoire
    for (int i = 0; i < g->ordre; i++) {
        free(g->noms_sommets[i]);
    }
    free(g->noms_sommets);
    free(g);
    free(coloration);

    return 0;
}
//test


// Fonction pour lire le fichier et appeler les fonctions CreeArete
// et CreerGraphe afin de transposer le graphe du fichier en structure de données
Graphe* lire_graphe(const char* nom_fichier) {
    FILE* ifs = fopen(nom_fichier, "r");
    if (!ifs) {
        printf("\n\n#### ERREUR ####\nFichier '%s' non trouvé, est-il bien dans le dossier du projet ?\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    int ordre;
    fscanf(ifs, "%d", &ordre);
    Graphe* graphe = CreerGraphe(ordre);

    // Lecture des noms des sommets
    for (int i = 0; i < ordre; ++i) {
        fscanf(ifs, "%s", graphe->noms_sommets[i]);
    }

    // Lecture des capacités des arcs
    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            fscanf(ifs, "%d", &graphe->capacites_arcs[i][j]);
        }
    }

    fclose(ifs);
    return graphe;
}

void afficher_graphe(Graphe* graphe) {
    printf("### AFFICHAGE DU GRAPHE ###\nOrdre du graphe: %d\n", graphe->ordre);

    printf("Liste des sommets:\n");
    for (int i = 0; i < graphe->ordre; i++) {
        printf("%s\n", graphe->noms_sommets[i]);
    }

    printf("#############################################\n\n");
}

void colorer_graphe(Graphe* graphe, int* coloration) {
    for (int i = 0; i < graphe->ordre; i++) {
        coloration[i] = i; // Attribution de couleurs indépendamment de la connectivité
    }
}

int main() {
    char nom_fichier[100];
    printf("Veuillez entrer le nom du fichier : ");
    scanf("%99s", nom_fichier);

    Graphe* g = lire_graphe(nom_fichier);
    afficher_graphe(g);

    int* coloration = (int*)malloc(g->ordre * sizeof(int));

    colorer_graphe(g, coloration);

    printf("### COULEURS ATTRIBUÉES AUX SOMMETS ###\n");
    for (int i = 0; i < g->ordre; i++) {
        printf("Sommet %s : Couleur %d\n", g->noms_sommets[i], coloration[i]);
    }

    // Libérer la mémoire
    for (int i = 0; i < g->ordre; i++) {
        free(g->noms_sommets[i]);
    }
    free(g->noms_sommets);
    free(g);
    free(coloration);

    return 0;
}




/*
// Fichier Header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition
typedef struct Graphe {
    int ordre;
    char** noms_sommets;
    int** capacites_arcs;
    int** capacites_restantes;
    int** flots;
} Graphe;

// Fonction pour allouer un graphe et ses attributs dynaniquement
Graphe* CreerGraphe(int ordre) {
    Graphe* Newgraphe = (Graphe*)malloc(sizeof(Graphe));
    Newgraphe->ordre = ordre;
    Newgraphe->noms_sommets = (char**)malloc(ordre * sizeof(char*));
    Newgraphe->capacites_arcs = (int**)malloc(ordre * sizeof(int*));
    Newgraphe->capacites_restantes = (int**)malloc(ordre * sizeof(int*));
    Newgraphe->flots = (int**)malloc(ordre * sizeof(int*));

    // Remplir la matrice avec des 0
    for (int i = 0; i < ordre; i++) {
        Newgraphe->noms_sommets[i] = (char*)malloc(2 * sizeof(char)); // Assuming two-character names
        Newgraphe->capacites_arcs[i] = (int*)calloc(ordre, sizeof(int));
        Newgraphe->capacites_restantes[i] = (int*)calloc(ordre, sizeof(int));
        Newgraphe->flots[i] = (int*)calloc(ordre, sizeof(int));
    }
    return Newgraphe;
}

// Fonction pour lire le fichier et appeler les fonctions CreeArete
// et CreerGraphe afin de transposer le graphe du fichier en structure de données
Graphe* lire_graphe(const char* nom_fichier) {
    FILE* ifs = fopen(nom_fichier, "r");
    if (!ifs) {
        printf("\n\n#### ERREUR ####\nFichier '%s' non trouvé, est-il bien dans le dossier du projet ?\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    int ordre;
    fscanf(ifs, "%d", &ordre);
    Graphe* graphe = CreerGraphe(ordre);

    for (int i = 0; i < ordre; ++i) {
        fscanf(ifs, "%s", graphe->noms_sommets[i]);
    }

    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            fscanf(ifs, "%d", &graphe->capacites_arcs[i][j]);
        }
    }

    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            graphe->capacites_restantes[i][j] = graphe->capacites_arcs[i][j];
        }
    }

    fclose(ifs);
    return graphe;
}

// Fonction pour afficher le graphe
void afficher_graphe(Graphe* graphe) {
    printf("### AFFICHAGE DU GRAPHE ###\nOrdre du graphe: %d\n", graphe->ordre);

    // Display capacities of arcs in a square matrix
    printf("Capacités des arcs:\n");
    for (int i = 0; i < graphe->ordre; i++) {
        printf("%s | ", graphe->noms_sommets[i]);
        for (int j = 0; j < graphe->ordre; j++) {
            printf("%d ", graphe->capacites_arcs[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // Afficher la liste des arcs avec leurs capacités sous la forme :
    printf("Liste des arcs avec leurs capa:\n");
    for (int i = 0; i < graphe->ordre; i++) {
        for (int j = 0; j < graphe->ordre; j++) {
            if (graphe->capacites_arcs[i][j] != 0) {
                printf("%s -> %s |%d|  ", graphe->noms_sommets[i], graphe->noms_sommets[j], graphe->capacites_arcs[i][j]);
            }
        }
        (i == graphe->ordre - 1) ? printf("") : printf("\n");
    }

    printf("#############################################\n\n");
}

// FONCTION POUR COLORER LE GRAPHE
// Fonction pour initialiser les couleurs
void initialiser_couleurs(int* coloration, int nombre_sommets)
{
    for (int i = 0; i < nombre_sommets; i++)
    {
        coloration[i] = -1; // -1 signifie que le sommet n'est pas coloré
    }
}

// Fonction pour colorer le graphe
void colorer_graphe(Graphe* graphe, int* coloration, int sommet, int nombre_couleurs)
{
    initialiser_couleurs(coloration, graphe->ordre);

    // Coloration du sommet de départ
    coloration[sommet] = 0;

    // Coloration des autres sommets
    for (int i = 0; i < graphe->ordre; i++)
    {
        if (graphe->capacites_arcs[sommet][i] != 0)
        {
            coloration[i] = 1;
        }
    }

    // Coloration des sommets restants
    for (int i = 0; i < graphe->ordre; i++)
    {
        if (coloration[i] == -1)
        {
            int couleur_disponible[graphe->ordre]; // Tableau pour stocker les couleurs disponibles
            for (int j = 0; j < graphe->ordre; j++)
            {
                couleur_disponible[j] = 1; // 1 signifie que la couleur est disponible
            }

            // Parcourir les sommets adjacents et marquer les couleurs indisponibles
            for (int j = 0; j < graphe->ordre; j++)
            {
                if (graphe->capacites_arcs[i][j] != 0 && coloration[j] != -1)
                {
                    couleur_disponible[coloration[j]] = 0; // 0 signifie que la couleur n'est pas disponible
                }
            }

            // Trouver la première couleur disponible
            for (int j = 0; j < graphe->ordre; j++)
            {
                if (couleur_disponible[j] == 1)
                {
                    coloration[i] = j;
                    break;
                }
            }
        }
    }
}

int main() {
    char nom_fichier[100];  // Déclare un tableau de caractères pour stocker le nom du fichier
    printf("Veuillez entrer le nom du fichier : ");
    scanf("%99s", nom_fichier);  // Utilisez %99s pour éviter un dépassement de tampon

    Graphe* g = lire_graphe(nom_fichier);
    afficher_graphe(g);

    // Allocation dynamique de la mémoire pour la coloration
    int* coloration = (int*)malloc(g->ordre * sizeof(int));

    // Appliquer la coloration
    colorer_graphe(g, coloration, 0, g->ordre);  // Vous pouvez choisir un sommet initial (ici, le premier sommet, d'où le 0)

    // Afficher les couleurs attribuées aux sommets
    for (int i = 0; i < g->ordre; i++)
    {
        printf("Sommet %d : Couleur %d\n", i, coloration[i]);
    }

    // Libérer la mémoire
    for (int i = 0; i < g->ordre; i++) {
        free(g->noms_sommets[i]);
        free(g->capacites_arcs[i]);
        free(g->capacites_restantes[i]);
        free(g->flots[i]);
    }
    free(g->noms_sommets);
    free(g->capacites_arcs);
    free(g->capacites_restantes);
    free(g->flots);
    free(g);
    free(coloration);

    return 0;
}

*/


