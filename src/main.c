/* Fichier Main du projet TG 2023-2024
 * Sources :
*/


//1234
//commentaires pour expliquer ce qu'on pourrait faire pour contrainte d'exclusion 

//lecture du fichier.txt
//determiner le maximum et le minimum dans l'ensemble 
//cette détermination va permettre de pouvoir avoir tous les éléments COMPRIS entre le min et max de l'ensemble 
//(si pas de contrainte avec un nombre à l'int, il sera quand même compris)

//on créé un bloc A
//on y place tous les éléments (du min au max) dans ce bloc A

//on ne touche PAS le minimum de l'ensemble
//boucle : for i=0; i<n; i++
//on utilise le principe de file 
//1+i -> regarder s'il a une contrainte avec celui/ceux d'avant

//tant qu'on n'a pas atteint le max
//booléen : 1 (contrainte) -> on place bloc en + (si A on passe B -> on peut aussi faire bloc 1, 2...)
//          0 (pas de contrainte) -> on place le nombre dans le bloc où il n'y a pas de contrainte

//on peut créer des tableaux dyn pour les blocs? 

//une fois le max atteint (et sa contrainte comprise) -> on affiche tous les blocs. 




//quelques pistes de réflexion : 
//créer une fonction pour remplir le tableau (station) -> tourne autour fonction qui fait remplissage
//structure stockage
//n stations (donc il faut que le nombre de bloc soit en allocation dynamique aussi?)


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Lecture de fichier + Placement des éléments dans un tableau
void lire_fichier(char* nom_fichier, int MinMax[100][100], int *N)
{
    FILE* fichier = fopen(nom_fichier, "r");

    if (!fichier)
    {
        printf("\n\n#### ERREUR ####\nFichier '%s' non trouvé, est-il bien dans le dossier du projet ?\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    int i = 0, j = 0;
    while (fscanf(fichier, "%d", &MinMax[i][j]) != EOF)
    {
        i++; //représente la première colonne
        j++; //représente la deuxième colonne
    }

    *N = i; // La taille du tableau est maintenant dans N

    fclose(fichier);
}

//Le but de la fonction est de trouver le minimum et le maximum du fichier.txt
//On obtient le minimum ainsi que le maximum en comparant chaque valeur entre les deux colonnes (i et j)
//cette fonction permet à ce qu'on puisse crée par la suite un premier bloc (Bloc1) (où on mettra tous les éléments compris entre le min et max)

void Trouver_Min_Max(int MinMax[100][100], int N) //maximum 100 valeurs pour les deux colonnes
{
    int i, j;

    // Variable pour stocker le minimum et le maximum
    int minV = INT_MAX, maxV = INT_MIN;

    // Parcours du tableau
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            // Si l'élément actuel est plus petit que le minimum
            if (MinMax[i][j] < minV)
            {
                minV = MinMax[i][j]; //coquille?
            }

            // Si l'élément actuel est plus grand que le maximum
            if (MinMax[i][j] > maxV)
            {
                maxV = MinMax[i][j];
            }
        }
    }

    //Debug min max
    printf("Le minimum est : %d\n", minV);
    printf("Le maximum est : %d\n", maxV);
}

int main()
{
    char nom_fichier[100];
    int tableau[100][100];
    int N;

    printf("Quel fichier voulez-vous lire ?\n");
    scanf("%99s", nom_fichier);

    lire_fichier(nom_fichier, tableau, &N);
    Trouver_Min_Max(tableau, N);

    return 0;
}

//prochaine étape créer un bloc 1 (le premier) qui va du min au max
//faire en sorte que le tableau(?) soit en allocation dynamique