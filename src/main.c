
/* Fichier  Main du projet TG 2023-2024
 * Sources : https://www.youtube.com/watch?v=FmaNOdbngLc&t=1843s&ab_channel=FormationVid%C3%A9o
*/

#include <main.h>
#include <precedence.h>
#include <exclusion.h>
#include <multi_contraintes.h>
#include <Fonctions_tests_affichage.h>
#include <color.h>

int main() {
    affichage_debut();

    /*
     * 1. Initialisation des opérations
     * 2. Précédence
     */

    Operation *operations = initialisation_graphe_p();

    /*
     * 3. Exclusion
     */

    printf("\n");
    attente_entre_fonctions(5);

    int **station;
    station = exclusion();

    /*
     * 4. Multi-contraintes
     */

    printf("\n");
    attente_entre_fonctions(5);
    printf("\n");

    multi_contraintes(station, operations);
    return 0;
}

