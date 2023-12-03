
/* Fichier  Main du projet TG 2023-2024
 * Sources : https://www.youtube.com/watch?v=FmaNOdbngLc&t=1843s&ab_channel=FormationVid%C3%A9o
*/

#include <main.h>
#include <precedence.h>
#include <exclusion.h>
#include <multi_contraintes.h>
#include <Fonctions_tests_affichage.h>


int main() {
    affichage_debut();

    /*
     * 1. Initialisation des opérations
     * 2. Précédence
     */

    initialisation_graphe_p();

    /*
     * 3. Exclusion
     */

    printf("\n");
    int **station;
    station = malloc(3 * sizeof(int *));
    exclusion(station);

    /*
     * 4. Multi-contraintes
     */

    printf("\n");
    multi_contraintes();
    return 0;
}

