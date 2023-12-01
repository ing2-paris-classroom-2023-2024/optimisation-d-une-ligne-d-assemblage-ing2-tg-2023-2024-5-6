#ifndef BLOC_H
#define BLOC_H
#define TAILLE_MAX 1000

#include <stdbool.h>
//
// Définition du type Booléen
typedef enum
{
    False,
    True
} Bool;

// Définition du type Bloc
typedef struct Bloc
{
    int valeur;
    struct Bloc* suivant;
} Bloc, *Station;

Station creerNoeud(int valeur);
Bool estVide(Station debut);
int Longueur_Bloc(Station Station);
void insererFin(Station* tete, int valeur);
void afficherListe(Station debut);
Bool peutAjouterOperation(int operation, int exclusion[TAILLE_MAX][2], int nbContraintes, int operationsFiltrees[], int nbOperationsFiltrees);
void Filtrage(int exclusion[TAILLE_MAX][2], int nbContraintes, int blocInitial[TAILLE_MAX], int tailleBloc);

#endif
