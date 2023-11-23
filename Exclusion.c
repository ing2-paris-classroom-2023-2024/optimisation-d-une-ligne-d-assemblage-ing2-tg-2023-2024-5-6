

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
