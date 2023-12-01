#ifndef BLOC_H
#define BLOC_H
#include <stdbool.h>

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
void filtreBlocInitial(int blocInitial[], int taille, Station* listeFiltree, int contrainte);

#endif
