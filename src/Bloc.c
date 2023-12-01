#include <stdio.h>
#include <stdlib.h>
#include "Bloc.h"

/*___________________________________________________________*/

Station creerNoeud(int valeur)
{
    Station nouveauNoeud = (Station)malloc(sizeof(Bloc));
    if (nouveauNoeud == NULL)
    {
        printf("Échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    nouveauNoeud->valeur = valeur;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

/*___________________________________________________________*/

Bool estVide(Station debut)
{
    if (debut == NULL)
        return True;
    else
        return False;
}

/*___________________________________________________________*/

int Longueur_Bloc(Station Station)
{
    int taille = 0;

    if (!estVide(Station))
        while (Station != NULL)
        {
            taille++;
            Station = Station->suivant;
        }
    return taille;
}

/*___________________________________________________________*/

void insererFin(Station* debut, int valeur)
{
    Station nouveauNoeud = creerNoeud(valeur);

    if (estVide(*debut))
        *debut = nouveauNoeud;
    else
    {
        Station temp = *debut;
        while (temp->suivant != NULL)
        {
            temp = temp->suivant;
        }
        temp->suivant = nouveauNoeud;
    }
}

/*___________________________________________________________*/

void afficherListe(Station debut)
{
    if (estVide(debut))
        printf("La liste est vide.\n");
    else
    {
        printf("La liste contient %d elements.\n", Longueur_Bloc(debut));
        while (debut != NULL)
        {
            printf("%d\n", debut->valeur);
            debut = debut->suivant;
        }
    }
}

/*___________________________________________________________*/

/*

void filtreBlocInitial(int blocInitial[], int taille, Station* listeFiltree, int pair, int impair)
{
    for (int i = 0; i < taille; i++) // On parcourt le bloc initial
    {
        if (blocInitial[i] % pair == 0) // Si le nombre est pair
        {
            int doublon = 0;
            for (int j=0; j < taille ; j++) // On parcourt le bloc
            {

            }
        }
    }
}

 */