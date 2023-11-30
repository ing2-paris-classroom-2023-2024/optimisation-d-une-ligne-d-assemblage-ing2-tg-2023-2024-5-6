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

int main()
{
    char nom_fichier[100];
    int tableau[100];
    int N;

    printf("Quel fichier voulez-vous lire ?\n");
    scanf("%99s", nom_fichier);

    lire_fichier(nom_fichier, tableau, &N);

    Afficher_Tableau(tableau, N);

    Trouver_Min_Max(tableau, N);

    return 0;
}
//prochaine étape créer un bloc 1 (le premier) qui va du min au max
//faire en sorte que le tableau(?) soit en allocation dynamique



/*
 * #include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* operations;
    int nombres;
} Station;

void lire_fichier(char* nom_fichier, int tableau[100], int** exclusion, int* N) {
    FILE *fichier = fopen(nom_fichier, "r");

    if (!fichier) {
        perror("Fichier non trouvé");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fscanf(fichier, "%d", &tableau[i]) != EOF) {
        exclusion[i] = calloc(*N, sizeof(int));
        i++;
    }

    *N = i;
    fclose(fichier);
}

void liberer_exclusion(int** exclusion, int N) {
    for (int i = 0; i < N; i++) {
        free(exclusion[i]);
    }
    free(exclusion);
}

void Trouver_Min_Max(int tableau[100], int** exclusion, int N) {
    int minV = INT_MAX, maxV = INT_MIN;

    // Exclusion des couples de valeurs ? (1, 4), (1,17 ), ...
    for (int i = 0; i < N; i++) {
        if (!exclusion[i][i]) {
            if (tableau[i] < minV) minV = tableau[i]; // Si la valeur est inférieure au min, on la remplace par la valeur actuelle
            if (tableau[i] > maxV) maxV = tableau[i]; // Si la valeur est supérieure au max, on la remplace par la valeur actuelle

            //Pour chaque valeur, on regarde si elle est égale à une autre valeur
            //PAS LOGIQUE PTN
            for (int j = i + 1; j < N; j++) {
                if (tableau[j] == tableau[i]) { // Si la valeur est égale à la valeur actuelle
                    exclusion[j][i] = exclusion[i][j] = 1; // On l'exclut
                }
            }
        }
    }

    printf("Le minimum est : %d\n", minV);
    printf("Le maximum est : %d\n", maxV);
}

/// https://www.youtube.com/watch?v=6mlp13UGfUM&ab_channel=HassanELBAHI
void Repartir_Operations(int tableau[100], int** exclusion, int N) {
    Station stations[3] = {{0}, {0}, {0}};

    for (int i = 0; i < N; i++)
    {
        if (!exclusion[i][i]) {
            int minStation = 0;
            for (int j = 1; j < 3; j++)
            {
                if (stations[j].nombres < stations[minStation].nombres) // Si le nombre d'opérations de la station j est inférieur au nombre d'opérations de la station minStation
                {
                    minStation = j; // On remplace minStation par j
                }
            }


            /// ALLOCATION DYNAMIQUE DU TABLEAU DE LA STATION MINSTATION
            /// // (http://sdz.tdct.org/sdz/ableaux-pointeurs-et-allocation-dynamique.html (Fonction))

            stations[minStation].operations = realloc(stations[minStation].operations,
                                                      (stations[minStation].nombres + 1) * sizeof(int));
            // On augmente la taille du tableau de la station minStation de 1 ==> FONCTION SUPER UTILE POUR NOUS, NE PAS OUBLIER LE +1

            stations[minStation].operations[stations[minStation].nombres++] = tableau[i];
            // On ajoute la valeur à la station minStation et on incrémente le nombre d'opérations de la station minStation afin de pouvoir ajouter une nouvelle valeur
            // CHERCHER LA DIFFERENCE

        }
    }

    for (int i = 0; i < 3; i++) {
        printf("Station %d : ", i + 1);
        for (int j = 0; j < stations[i].nombres; j++) {
            printf("%d ", stations[i].operations[j]);
        }
        printf("\n");

        free(stations[i].operations);
    }
}

void Afficher_Tableau(int tableau[100], int N) {
    printf("Tableau : ");
    for (int i = 0; i < N; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

int main() {
    char nom_fichier[100];
    int tableau[100];
    int** exclusion;
    int N;

    printf("Quel fichier voulez-vous lire ?\n");
    scanf("%99s", nom_fichier);

    exclusion = (int*)malloc(100 * sizeof(int));

    lire_fichier(nom_fichier, tableau, exclusion, &N);

    Afficher_Tableau(tableau, N);

    Trouver_Min_Max(tableau, exclusion, N);

    Repartir_Operations(tableau, exclusion, N);

    liberer_exclusion(exclusion, N);

    return 0;
}
 */
