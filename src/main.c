/* Fichier Main du projet TG 2023-2024
 * Sources :
https://www.youtube.com/watch?v=FmaNOdbngLc&t=1843s&ab_channel=FormationVid%C3%A9o
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Bloc.h"

// Structure pour représenter une paire d'opérations exclues
typedef struct {
    int operation1;
    int operation2;
} ExclusionPair;


#define TAILLE_MAX 1000


// Lecture de fichier + Placement des éléments dans un tableau
void lire_fichier(char* nom_fichier, int tableau[TAILLE_MAX], int* N)
{
    FILE *fichier = fopen(nom_fichier, "r");

    if (!fichier)
    {
        printf("\n\n#### ERREUR ####\nFichier '%s' non trouvé, est-il bien dans le dossier du projet ?\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < TAILLE_MAX && fscanf(fichier, "%d", &tableau[i]) != EOF)
    {
        i++;
    }

    if (i == TAILLE_MAX)
    {
        printf("\n\n#### ERREUR ####\nLa taille du fichier dépasse la capacité maximale.\n");
        exit(EXIT_FAILURE);
    }

    *N = i; // La taille du tableau est maintenant dans N

    fclose(fichier);
}

    /////Partie allocation dynamique du tableau
    //http://sdz.tdct.org/sdz/ableaux-pointeurs-et-allocation-dynamique.html



//Le but de la fonction est de trouver le minimum et le maximum du fichier.txt
//On obtient le minimum ainsi que le maximum en comparant chaque valeur entre les deux colonnes (i et j)
//cette fonction permet à ce qu'on puisse crée par la suite un premier bloc (Bloc1) (où on mettra tous les éléments compris entre le min et max)

void Trouver_Min_Max(int tableau[TAILLE_MAX], int N, int* minV1, int* maxV1)
{
    int i;

    // Variable pour stocker le minimum et le maximum
    *minV1 = INT_MAX;
    *maxV1 = INT_MIN;

    for (i = 0; i< N; i++){
        if (tableau[i]< *minV1){
            *minV1 = tableau[i];
        }
        if (tableau[i] > *maxV1){
            *maxV1 = tableau[i];
        }
    }
    printf("minimum pour colonne 1 : %d\n", *minV1);
    printf("maximum pour colonne1 : %d\n", *maxV1);


}


void Afficher_Tableau (int tableau[TAILLE_MAX], int N) //DEBUG
{
    int i;

    // Parcours du tableau
    for (i = 0; i < N; i++)
    {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

void contraintes(int tableau[TAILLE_MAX], int N, int exclusion[TAILLE_MAX][2], int* nbContraintes)
{
    *nbContraintes = 0;

    for (int i = 0; i < N - 1; i += 2)
    {
        exclusion[*nbContraintes][0] = tableau[i]; // On ajoute la contrainte ET son opposé
        exclusion[*nbContraintes][1] = tableau[i + 1];
        (*nbContraintes)++;
    }
}

void AfficherContraintes(int exclusion[TAILLE_MAX][2], int nbContraintes)
{
    printf("Il y a %d couples de contrainte.\n", nbContraintes);
    for (int i = 0; i < nbContraintes; i++)
    {
        printf("%d %d\n", exclusion[i][0], exclusion[i][1]);
    }
}

// Fonction pour lire les exclusions à partir du fichier
int lireExclusions(ExclusionPair exclusions[TAILLE_MAX], const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'exclusions.\n");
        exit(EXIT_FAILURE);
    }

    int nbExclusions = 0;
    while (fscanf(fichier, "%d %d", &exclusions[nbExclusions].operation1, &exclusions[nbExclusions].operation2) == 2) {
        nbExclusions++;
        if (nbExclusions >= TAILLE_MAX) {
            printf("Trop d'exclusions. Ajustez TAILLE_MAX si nécessaire.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(fichier);
    return nbExclusions;
}


void Bloc_Initial(int minV1, int maxV1, int blocInitial[TAILLE_MAX], int* tailleBloc)
{
    int j = 0;

    for (int i = minV1; i <= maxV1; i++)
    {
        blocInitial[j] = i;
        j++;
    }

    // Mettez à jour la variable tailleBloc
    *tailleBloc = j;

    // Affichez le blocInitial après la construction
    printf("Voici le bloc initial : ");
    for (int k = 0; k < j; k++)
    {
        printf("%d ", blocInitial[k]);
    }
    printf("\n");
}



int main() {
    char nom_fichier[TAILLE_MAX];
    int tableau[TAILLE_MAX];
    int exclusion[TAILLE_MAX][2];
    int nbContraintes;
    int N;
    int operationsNonFiltrees[TAILLE_MAX];
    int nbOperationsNonFiltrees = 0; // Initialisez nbOperationsNonFiltrees

    int minV1, maxV1;
    int blocInitial[TAILLE_MAX];
    int tailleBloc;
    int iteration = 0;

    printf("Quel fichier voulez-vous lire ?\n");
    scanf("%s", nom_fichier);

    lire_fichier(nom_fichier, tableau, &N);
    contraintes(tableau, N, exclusion, &nbContraintes);

    AfficherContraintes(exclusion, nbContraintes);

    Trouver_Min_Max(tableau, N, &minV1, &maxV1);
    Bloc_Initial(minV1, maxV1, blocInitial, &tailleBloc);

    // Appel de la fonction Filtrage avec les paramètres appropriés
    Filtrage(exclusion, nbContraintes, blocInitial, tailleBloc);

    return 0;
}