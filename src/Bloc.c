#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

bool estVide(Station debut)
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

void afficherOperations(const char *nom, int *operations, int nbOperations) {
    printf("%s :\n", nom);
    for (int i = 0; i < nbOperations; i++) {
        printf("%d ", operations[i]);
    }
    printf("\n");
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

void Filtrage(int exclusion[TAILLE_MAX][2], int nbContraintes, int blocInitial[TAILLE_MAX], int tailleBloc)
{
    // https://c.developpez.com/cours/20-heures/?page=page_16
    // https://www.youtube.com/watch?v=6mlp13UGfUM&t=374s&ab_channel=HassanELBAHI
    //https://www.youtube.com/watch?v=eY9j3qmy3bQ&ab_channel=BilalEnesFedar

    int* operationsFiltrees = (int*)malloc(tailleBloc * sizeof(int));
    int* operationsNonFiltrees = (int*)malloc(tailleBloc * sizeof(int));
    int nbOperationsFiltrees = 0;
    int nbOperationsNonFiltrees = 0;

    /*
    On tente d'ajouter chaque opération du bloc initial dans le tableau des opérations filtrées
    On vérifie à chaque fois si l'opération peut être ajoutée en respectant les contraintes
    Si l'opération peut être ajoutée, on l'ajoute
    Sinon on passe à l'opération suivante

    Prochaine étape : On affiche les opérations non filtrées

    */


    // Boucle externe parcourant le bloc initial
    for (int i = 0; i < tailleBloc; i++)
    {
        int operationCourante = blocInitial[i];// On récupère les données du bloc initial
        bool peutEtreAjoute = true; // On suppose que l'opération peut être ajoutée

        // Boucle interne parcourant les contraintes
        for (int k = 0; k < nbContraintes; k++) // On utilise k pour parcourir les contraintes
        {
            if (exclusion[k][0] == operationCourante || exclusion[k][1] == operationCourante) // Si l'opération courante est dans une contrainte
            {
                int autreOperation = (exclusion[k][0] == operationCourante) ? exclusion[k][1] : exclusion[k][0];
                // On récupère l'autre opération de la contrainte
                // Nous sommes dans le cas d'un opérateur ternaire : condition ? valeur si vrai : valeur si faux
                // Car on veut récupérer l'autre opération de la contrainte
                // https://c.developpez.com/cours/20-heures/?page=page_16

                /*
                La signification de cet opérateur est la suivante :

                Dans notre cas, la condition est : exclusion[k][0] == operationCourante
                _ Si la condition est vraie, exclusion[k][1] est évaluée. ( l'autre opération de la contrainte - Ex: 4)
                _ Si la condition est fausse, exclusion[k][0] est évaluée. ( l'opération de la contrainte - Ex: 1)
                */


                // Boucle pour vérifier si l'autre opération est déjà présente dans les opérations filtrées
                for (int l = 0; l < nbOperationsFiltrees; l++) // On parcourt les opérations déjà filtrées
                {
                    if (operationsFiltrees[l] == autreOperation) // Si l'autre opération est déjà présente dans les opérations filtrées
                    {
                        // L'opération ne peut pas être ajoutée car elle a une contrainte avec une opération déjà présente
                        peutEtreAjoute = false;
                        break;
                    }
                }
            }
        }

        // Ajouter l'opération à la liste appropriée
        if (peutEtreAjoute)
        {
            operationsFiltrees[nbOperationsFiltrees] = operationCourante;
            nbOperationsFiltrees++;
        }
        else
        {
            operationsNonFiltrees[nbOperationsNonFiltrees] = operationCourante;
            nbOperationsNonFiltrees++;
        }
    }

    // Affichage des opérations filtrées
    printf("Operations filtrees :\n");
    for (int i = 0; i < nbOperationsFiltrees; i++)
    {
        printf("%d ", operationsFiltrees[i]);
    }
    printf("\n");

    // Affichage des opérations non filtrées
    printf("Operations non filtrees :\n");
    for (int i = 0; i < nbOperationsNonFiltrees; i++)
    {
        printf("%d ", operationsNonFiltrees[i]);
    }
    printf("\n");

    // Libération de la mémoire
    free(operationsFiltrees);
    free(operationsNonFiltrees);
}
