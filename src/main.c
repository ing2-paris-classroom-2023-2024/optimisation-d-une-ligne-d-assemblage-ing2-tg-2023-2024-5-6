/* Fichier Main du projet TG 2023-2024
 * Sources :
*/

#include "src/main.h"
#include <stdio.h>


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


//tests alara


