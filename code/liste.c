/*liste.c
Code lier aux listes generiques.
Definition de la structure.
Fonctions utile sur les listes.
*/

/*INCLUDES
================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "liste.h"

/*FONCTIONS
================================================================
*/

/* creer_liste cree la tête de la liste, 
 *retourn NULL si ça echoue, la liste l sinon */

liste creer_liste(){
  liste l = malloc(sizeof(elem));
  if(l==NULL) /*si l'allocation de memoire a echoué*/
    return NULL;
  l->suivant = l->precedent = l;
  l->val = NULL;
  return l;
}

/*est_vide verifie si la liste est vide, 
 *c-a-d qu'elle ne contient que la tete.
 *retourn n =/= 0 si la liste est vide, 0 sinon*/

int est_vide (liste l){
  return l->suivant == l;
}

/*inserer_après(previous, valeur) 
 *insere un nouvel element apres previous
 *cet element a pour valeur valeur
 *retourn NULL si l'insertion echou
 *retourn un pointeur vers l'element inserer si succes.
 */

liste insere_apres(liste previous, void *valeur){
  if (valeur == NULL)
    return NULL; /*on ne peut pas inserer NULL */
  liste nouveau = malloc(sizeof(elem));
  if (nouveau == NULL)
    return NULL; /*l'allocation de memoire a echouee */
  liste next = previous-> suivant;
  previous->suivant = next->precedent = nouveau;
  nouveau->precedent = previous;
  nouveau->suivant = next;
  nouveau->val = valeur;
  return nouveau;
}

/*inserer_avant (next, valeur)
 *insere un nouvel element avant next
 *cet element a pour valeur valeur
 *retourn NULL si l'insertion echou
 *retourn un pointeur vers l'element inserer si succes.
 */

liste inserer_avant (liste next, void *valeur){
  return insere_apres(next->precedent, valeur);
}

/*est_tete (l) permet de teste si un element est la tete de la liste
 *retourne n =/= 0 si c'est le cas, 0 sinon*/

int est_tete(liste l){
  if (l == NULL)
    return -1;
  else if (l->val == NULL)
    return 1;
  else
    return 0;
}

/*supprimer_element (l) supprime un element de la liste
 * on ne peut pas supprimer la tete
 * retourne un pointeur vers les donnees supprimees, 
 *NULL si la suppression n'est pas possible*/

void *supprimer_element(liste l){
  if(est_tete(l))
    return NULL; /*on ne peut pas supprimer la tete */
  liste previous = l->precedent;
  liste next = l->suivant;
  previous->suivant = next;
  next->precedent = previous;
  void *valeur = l->val;
  free(l);
  return valeur;
}

/*vider_liste(l) supprimer tous les element de la liste sauf la tete *l pointe vers la tete
 *retourne la tete si la suppression a eu lieu, NULL sinon */

liste vide_liste(liste l){
  l = getTete (l);
  l = suivant (l);
  while (!est_tete (l)){
    l = suivant (l);
    supprimer_element (precedent(l));
  }
  return l;
}


/*detruire_liste supprime tous les element d'une liste et sa tete
 *l pointe vers la tete de la liste
 *retourne 1 si la suppression à eu lieu, 0 sinon 
*/

int detruire_liste(liste l){
  liste tmp = vide_liste(l);
  if (tmp==NULL)
    return 0;
  free (l);
  return 1;
}


/*fusinne les deux liste l et p et retourne la liste definitive*/

liste fusionner(liste l, liste p){
  if (est_vide (p)) {
    detruire_liste (p);
    return l;
  }
  else{
    l = getTete (l);
    p = suivant (getTete (p));
    while (!est_tete(p)){
      insere_apres (l, p->val);
      p = suivant (p);
    }      
    if (! detruire_liste (p))
      return NULL;
  }
  return l;
}

/*valeur(l) retourne la valeur de l'element l*/

void *valeur(liste l){
  return l->val;
}

/*suivant(l) retourne l'element suivant de l*/

liste suivant(liste l){
  return l->suivant;
}

/*precedent(l) retourne l'element precedent de l*/

liste precedent(liste l){
  return l->precedent;
}

/*retourne l'element associé a la valeur v */

liste getElem (void * v, liste l){
  liste tmp = l -> suivant;
  if(est_tete(tmp))
    return NULL;
  while (tmp -> val != v){
    tmp = tmp -> suivant;
    if (est_tete(tmp)) 
      return NULL;
  }
  return tmp;
}

/*getTete retourne la tete de la liste */

liste getTete (liste l){
  while (!est_tete(l))
    l = l -> suivant;
  return l;
}

/*copie une liste */

liste copier (liste l) {
  liste res = creer_liste();
  if (est_vide (l))
    return res;
  l = suivant (getTete (l));
  while (!est_tete (l)){
    inserer_avant (res, l->val);
    l = suivant (l);
  }
  return res;
}
