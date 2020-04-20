/*liste.c
Code lier aux listes generiques.
Definition de la structure.
Fonctions utile sur les listes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

/*listes doublement chainees circulaires
 *chaque liste possede une tete qui, elle, ne contient pas de valeur
 */

struct elem{
  struct elem *suivant; /*pointeur vers l'element suivant*/
  struct elem *precedent; /*pointeur vers l'element precedent*/
  void *val; /*pointeur vers les donnees de chaque element*/
};
typedef struct elem elem;
typedef elem *liste;

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
  return (l->val == NULL) ; /*la valeur est NULL pour la tete*/
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
  if (!est_tete(l))
    return NULL;
  for (liste tmp=l->suivant; !est_tete(tmp); tmp=tmp->suivant)
    supprimer_element(tmp);
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

