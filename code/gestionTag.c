/*gestionTag.c
Code lier à la gestions des tags.
Creation, defenition de liens, ajout, deletion...
*/

#include "gestionTag.h"

/*La structure tag comporte un char * nom et un liste pere */

/*Creer un tag et le met dans le liste de Tag, 
 *retourne un pointeur vers le tag creer 
 *si la création à bien eu lieu
 */
liste creerTag (char *nom, liste pere, liste ltag){
  tag * tag= malloc (sizeof(tag));
  if (tag == NULL)
    return NULL;
  tag -> nom = nom;
  tag -> pere = pere;
  if (inserer_avant (ltag, tag) == NULL)
    return NULL;
  else
    return ltag;
}

/*Supprime eviltag de liste tags (en cas de gestion d'erreur)
 *retourne le liste de tag 
 */ 
liste suppTag (tag eviltag, liste ltag){
  if (est_vide (ltag))
    return NULL;
  else {
    if (supprimer_element (getElem(&eviltag, ltag)) == NULL)
      return NULL;
    else
      return ltag;
  }
  return NULL;
}

/*Ajouter une liste de pere au tag orphelin 
 *retourne un pointeur vers le tag orphelin
 */
tag * ajouterPere (tag * orphelin, liste newfather){
  liste newpere = fusionner (orphelin -> pere, newfather);
  if (newpere == NULL)
    return NULL;
  else
    orphelin -> pere = newpere;
  return orphelin;
}

/*Supprime une liste de pere au tag orphelin 
 *retourne un pointeur vers le tag orphelin
 */
tag * supprimerPere (tag * orphelin, liste lostfather){
  liste tmp = orphelin -> pere -> suivant;
  liste sup = lostfather -> suivant;
  if (est_vide (lostfather))
    return orphelin;
  while (sup -> val != NULL){
    while (tmp -> val != sup -> val && !est_tete(tmp))
	tmp = tmp -> suivant;
    if (!est_tete(tmp)){
      if (supprimer_element(tmp) == NULL)
	return NULL;
    }
    sup = sup -> suivant;
    tmp = orphelin -> pere -> suivant;
  }
  return orphelin;
}

/*retourne le tag associé au nom */
tag * getTag (char *nom, liste ltag){
  liste tmp = ltag -> suivant;
  while (!strcmp(((tag *)(tmp -> val))-> nom, nom))
    tmp = tmp -> suivant;
  return tmp -> val;
}

/*retourne l'element associe au tag t */
liste getElem (tag *t, liste ltag){
  liste tmp = ltag -> suivant;
  while (tmp -> val != t)
    tmp = tmp -> suivant;
  return tmp;
}

/*affiche une liste de tag */
void afficherTag (liste ltag);

/*affiche les tags de la liste et leur peres associé */
void afficherFamilleTag (liste ltag);
