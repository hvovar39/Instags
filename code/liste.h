#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#ifndef LISTE_H
#define LISTE_H

/*listes doublement chainees circulaires
 *chaque liste possede une tete qui, elle, ne contient pas de valeur
 */

struct elem{
  struct elem *suivant; /*pointeur vers l'element suivant*/
  struct elem *precendent; /*pointeur vers l'element precedent*/
  void *val; /*pointeur vers les donnees de chaque element*/
};
typedef struct elem elem;
typedef elem *liste;

/* creer_liste cree la tête de la liste, 
 *retourn NULL si ça echoue, la liste l sinon */
liste creer_liste();

/*est_vide verifie si la liste est vide, 
 *c-a-d qu'elle ne contient que la tete.
 *retourn n =/= 0 si la liste est vide, 0 sinon*/
int est_vide (liste l);

/*inserer_après(previous, valeur) 
 *insere un nouvel element apres previous
 *cet element a pour valeur valeur
 *retourn NULL si l'insertion echou
 *retourn un pointeur vers l'element inserer si succes.
 */
liste insere_apres(liste previous, void *valeur);

/*inserer_avant (next, valeur)
 *insere un nouvel element avant next
 *cet element a pour valeur valeur
 *retourn NULL si l'insertion echou
 *retourn un pointeur vers l'element inserer si succes.
 */
liste inserer_avant (liste next, void *valeur);

/*est_tete (l) permet de teste si un element est la tete de la liste
 *retourne n =/= 0 si c'est le cas, 0 sinon*/
int est_tete(liste l);

/*supprimer_element (l) supprime un element de la liste
 * on ne peut pas supprimer la tete
 * retourne un pointeur vers les donnees supprimees, 
 *NULL si la suppression n'est pas possible*/
void *supprimer_element(liste l);

/*vider_liste(l) supprimer tous les element de la liste sauf la tete *l pointe vers la tete
 *retourne la tete si la suppression a eu lieu, NULL sinon */
liste vide_liste(liste l);

/*detruire_liste supprime tous les element d'une liste et sa tete
 *l pointe vers la tete de la liste
 *retourne 1 si la suppression à eu lieu, 0 sinon 
*/
int detruire_liste(liste l);

/*fusinne les deux liste l et p et retourne la liste definitive*/
liste fusionner(liste l, liste p);

/*valeur(l) retourne la valeur de l'element l*/
void *valeur(liste l);

/*suivant(l) retourne l'element suivant de l*/
liste suivant(liste l);

/*precedent(l) retourne l'element precedent de l*/
liste precedent(liste l);

liste getElem (void * v, liste l);

#endif
