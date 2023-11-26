

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













/* TEST 1

#include "src/main.h"
#include <stdio.h>


//Commit Test d'Alara sur ma branche dédiée


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
    initialiser_couleurs(coloration, graphe->nombre_sommets);

    // Coloration du sommet de départ
    coloration[sommet] = 0;

    // Coloration des autres sommets
    for (int i = 1; i < graphe->nombre_sommets; i++)
    {
        // Tableau pour marquer les couleurs utilisées par les voisins
        int couleurs_utilisees[nombre_couleurs];
        for (int k = 0; k < nombre_couleurs; k++)
        {
            couleurs_utilisees[k] = 0;
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

        // Trouver la première couleur non utilisée
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


// FONCTION POUR LIRE LE GRAPHE A PARTIR D'UN FICHIER
Graphe* lire_graphe_de_fichier(const char* nom_fichier)
{
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int nombre_sommets;
    fscanf(fichier, "%d", &nombre_sommets);

    Graphe* graphe = initialiser_graphe(nombre_sommets);

    int sommet1, sommet2;
    while (fscanf(fichier, "%d %d", &sommet1, &sommet2) == 2) // Lire les sommets de l'arête
    {
        ajouter_arete(graphe, sommet1, sommet2);
    }

    fclose(fichier);

    return graphe;
}




// FONCTION PRINCIPALE
int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        printf("Usage: %s <nom_fichier_graphe> <nombre_couleurs>\n", argv[0]);
        return EXIT_FAILURE;
    }


    const char* nom_fichier = argv[1]; // argv[0] est le nom du programme
    int nombre_couleurs = atoi(argv[2]); // atoi convertit une chaîne de caractères en entier

    Graphe* graphe = lire_graphe_de_fichier(nom_fichier);

    // Allocation dynamique de la mémoire pour la coloration
    int* coloration = (int*)malloc(graphe->nombre_sommets * sizeof(int));

    // Appliquer l'algorithme de coloration
    colorer_graphe(graphe, coloration, nombre_couleurs, graphe->nombre_sommets);

    // Afficher les couleurs attribuées aux sommets
    for (int i = 0; i < graphe->nombre_sommets; i++)
    {
        printf("Sommet %d : Couleur %d\n", i, coloration[i]);
    }

    // Libérer la mémoire
    liberer_graphe(graphe);
    free(coloration);

    return 0;
}
*/


