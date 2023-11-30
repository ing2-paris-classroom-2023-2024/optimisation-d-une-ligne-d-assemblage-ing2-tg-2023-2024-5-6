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


///*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Lecture de fichier + Placement des éléments dans un tableau
void lire_fichier(char* nom_fichier, int tableau[100], int* N)
{
    FILE *fichier = fopen(nom_fichier, "r");

    if (!fichier)
    {
        printf("\n\n#### ERREUR ####\nFichier '%s' non trouvé, est-il bien dans le dossier du projet ?\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fscanf(fichier, "%d", &tableau[i]) != EOF)
    {
        i++;
    }

    *N = i; // La taille du tableau est maintenant dans N

    fclose(fichier);
}

//Le but de la fonction est de trouver le minimum et le maximum du fichier.txt
//On obtient le minimum ainsi que le maximum en comparant chaque valeur entre les deux colonnes (i et j)
//cette fonction permet à ce qu'on puisse crée par la suite un premier bloc (Bloc1) (où on mettra tous les éléments compris entre le min et max)

void Trouver_Min_Max(int tableau[100], int N)
{
    int i;

    // Variable pour stocker le minimum et le maximum
    int minV1 = INT_MAX;
    int maxV1 = INT_MIN;

    for (i = 0; i< N; i++){
        if (tableau[i]<minV1){
            minV1 = tableau[i];
        }
        if (tableau[i] > maxV1){
            maxV1 = tableau[i];
        }
    }
    printf("minimum pour colonne 1 : %d\n", minV1);
    printf("maximum pour colonne1 : %d\n", maxV1);


    }


void Afficher_Tableau (int tableau[100], int N) //DEBUG
{
    int i;

    // Parcours du tableau
    for (i = 0; i < N; i++)
    {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

 int contraintes (int tableau[100], int N){
    int paire_contraintes;
    int pair;
    int impair;

    for (int i = -1; i< N-1; i++){

        paire_contraintes = i+1;
        //printf("l'élément est : %d\n", paire_contraintes);
        //printf("impaire c'est : %d\n", paire_contraintes%2);
        //printf("\n");


        if (paire_contraintes%2 == 0){
            pair = tableau[paire_contraintes];
            printf("voici la paire contrainte %d ", pair);
        }

        if (paire_contraintes%2 != 0){
            impair = tableau[paire_contraintes];
            printf("%d\n", impair);
            //printf("Voici la paire contrainte: %d %d\n", tableau[paire_contraintes], tableau[paire_contraintes--]);
        }

    }
    return paire_contraintes;
}

int main()
{
    char nom_fichier[100];
    int tableau[100];
    int N;

    printf("Quel fichier voulez-vous lire ?\n");
    scanf("%99s", nom_fichier);

    lire_fichier(nom_fichier, tableau, &N);

   // Afficher_Tableau(tableau, N);
    contraintes(tableau, N);
    Trouver_Min_Max(tableau, N);

    return 0;
}
//prochaine étape créer un bloc 1 (le premier) qui va du min au max
//faire en sorte que le tableau(?) soit en allocation dynamique
//*/
