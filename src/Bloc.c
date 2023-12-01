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


// Fonction qui vérifie si une opération peut être ajoutée en respectant les contraintes
Bool peutAjouterOperation(int operation, int exclusion[TAILLE_MAX][2], int nbContraintes, int operationsFiltrees[], int nbOperationsFiltrees)
{
    for (int j = 0; j < nbContraintes; j++)
    {
        if (exclusion[j][0] == operation || exclusion[j][1] == operation)
        {
            int autreOperation = (exclusion[j][0] == operation) ? exclusion[j][1] : exclusion[j][0];

            for (int k = 0; k < nbOperationsFiltrees; k++)
            {
                if (operationsFiltrees[k] == autreOperation)
                {
                    return False; // L'opération ne peut pas être ajoutée car elle a une contrainte avec une opération déjà présente
                }
            }
        }
    }

    return True; // L'opération peut être ajoutée
}

/*___________________________________________________________*/

void Filtrage(int exclusion[TAILLE_MAX][2], int nbContraintes, int blocInitial[TAILLE_MAX], int tailleBloc)
{
    // https://c.developpez.com/cours/20-heures/?page=page_16
    // https://www.youtube.com/watch?v=6mlp13UGfUM&t=374s&ab_channel=HassanELBAHI
    //https://www.youtube.com/watch?v=eY9j3qmy3bQ&ab_channel=BilalEnesFedar

    int* operationsFiltrees = (int*)malloc(tailleBloc * sizeof(int)); // On alloue un tableau de taille tailleBloc pour stocker les opérations filtrées
    int nbOperationsFiltrees = 0;

    /*
     On tente d'ajouter chaque opération du bloc initial dans le tableau des opérations filtrées
     On vérifie à chaque fois si l'opération peut être ajoutée en respectant les contraintes
     Si l'opération peut être ajoutée, on l'ajoute
     Sinon on passe à l'opération suivante

     Prochaine étape : On affiche les opérations non filtrées

     */

    for (int i = 0; i < tailleBloc; i++) // On parcourt le bloc initial
    {
        int operationCourante = blocInitial[i]; // On récupère l'opération courante
        bool peutEtreAjoute = true; // On suppose que l'opération peut être ajoutée

        for (int k = 0; k < nbContraintes; k++) // On utilise k pour parcourir les contraintes
        {
            if (exclusion[k][0] == operationCourante || exclusion[k][1] == operationCourante) // Si l'opération courante est dans une contrainte
            {
                // On récupère l'autre opération de la contrainte
                int autreOperation = (exclusion[k][0] == operationCourante) ? exclusion[k][1] : exclusion[k][0];
                // Nous sommes dans le cas d'un opérateur ternaire : condition ? valeur si vrai : valeur si faux
                // Car on veut récupérer l'autre opération de la contrainte
                // https://c.developpez.com/cours/20-heures/?page=page_16

                /*
                 La signification de cet opérateur est la suivante :

                 Évalue la condition.
                 _ Si la condition est vraie, l'expression après le point d'interrogation (?) est évaluée.
                 _ Si la condition est fausse, l'expression après les deux-points (:) est évaluée.
                 */

                for (int l = 0; l < nbOperationsFiltrees; l++) // On parcourt les opérations déjà filtrées
                {
                    if (operationsFiltrees[l] == autreOperation) // Si l'autre opération est déjà présente dans les opérations filtrées
                    {
                        // L'opération ne peut pas être ajoutée, car elle a une contrainte avec une opération déjà présente
                        peutEtreAjoute = false;
                        break;
                    }
                }
            }
        }

        if (peutEtreAjoute) // Si l'opération peut être ajoutée, on l'ajoute
        {
            operationsFiltrees[nbOperationsFiltrees] = operationCourante; // On ajoute l'opération
            nbOperationsFiltrees++;
        }
    }

    // Affichage des opérations filtrées
    printf("Operations filtrees :\n");
    for (int i = 0; i < nbOperationsFiltrees; i++)
    {
        printf("%d ", operationsFiltrees[i]);
    }
    printf("\n");

    free(operationsFiltrees);
}
