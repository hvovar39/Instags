
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "liste.h"

#ifndef GESTIONTAG_H
#define GESTIONTAG_H

struct tag {
  char * nom;
  liste pere;
};
typedef struct tag tag;


tag *creerTag (char *nom, liste pere, liste ltag);
/*Creer un tag et le met dans le liste de Tag, 
 *si la création à bien eu lieu
 */

liste suppTag (tag eviltag, liste ltag);
/*Supprime eviltag de liste tags (en cas de gestion d'erreur)
 *retourne le liste de tag 
 */ 

tag * ajouterPere (tag *orphelin, liste newfather);
/*Ajouter une liste de pere au tag orphelin 
 *retourne un pointeur vers le tag orphelin
 */

tag * supprimerPere (tag * orphelin, liste lostfather);
/*Supprime une liste de pere au tag orphelin 
 *retourne un pointeur vers le tag orphelin
 */

tag * getTag (char *nom, liste ltag);
/*retourne le tag associé au nom */

void afficherTag (liste ltag);
/*affiche une liste de tag */

void afficherFamilleTag (liste ltag);
/*affiche les tags de la liste et leur peres associé */


// A FAIRE

void afficherTags (liste lTag);
/*Affiche la liste de tag*/


#endif
