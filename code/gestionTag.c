/*gestionTag.c
Code lier à la gestions des tags.
Creation, defenition de liens, ajout, deletion...
*/

#include "gestionTag.h"

/*La structure tag comporte un char * nom et un liste pere */

/*Creer un tag et le met dans le liste de Tag, 
 *retourne la liste des tags
 *si la création à bien eu lieu
 */
tag * creerTag (char *nom, liste pere, liste ltag){
  tag * tag = malloc (sizeof(tag));
  if (tag == NULL)
    return NULL;
  tag -> nom = nom;
  tag -> pere = pere;
  if (inserer_avant (ltag, tag) == NULL)
    return NULL;
  else
    return tag;
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
  if (est_vide (newfather))
    return orphelin;
  liste proudfather =creer_liste();
  liste test =creer_liste();
  liste tmp =newfather->suivant;
  while (!est_tete(tmp)){
    insere_apres(test,tmp);
    if(tagAbsent(orphelin->pere, test))
      insere_apres(proudfather,tmp);
    detruire_liste(test);
    tmp=tmp->suivant;
  }
  liste newpere = fusionner (orphelin -> pere, proudfather);
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

/*estTaguer verifie si le fichier f  est taguer 
 *par la liste de tag present 
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/

int tagPresent (liste tFichier, liste present){
  if (est_vide (present))
    return 1;
  if (est_vide (tFichier))
    return 0;
  
  liste cp = copier (present);
  tFichier = suivant (getTete(tFichier));

  while (!est_vide (cp) && !est_tete (tFichier)) {//pour chaque element de tFichier
    cp = suivant (getTete(cp));

    while (!est_tete (cp)) {//On test pour chaque element de cp
      if (cp->val == tFichier->val){
	cp = suivant (cp);
	supprimer_element(precedent (cp));
      }else
	cp = suivant(cp);
    }

    tagPresent (((tag *)tFichier->val)->pere, present);
    tFichier = suivant (tFichier);
  }

  if (est_vide (cp))
    return 1;
  return 0;
}

/*estTaguer verifie si le fichier f ne possede pas absent
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/

int tagAbsent (liste tFichier, liste absent){
  liste abs = absent -> suivant;
  while (!est_tete(abs)){
    liste test = creer_liste();
    insere_apres (test, abs->val);
    if (tagPresent(tFichier, test))
      return 0;
    abs=abs->suivant;
    detruire_liste(test);
  }
  return 1;
}

/*retourne le tag associé au nom ou NULL si il n'existe pas*/
tag * getTag (char *nom, liste ltag){
  liste tmp = suivant(getTete(ltag));
  if (est_tete(tmp)) 
    return NULL;
  while (strcmp(((tag *)(tmp -> val))-> nom, nom) != 0){
    tmp = tmp -> suivant;
    if (est_tete(tmp)) 
      return NULL;
  }
  return tmp -> val;
}

/*affiche une liste de tag */
void afficherTag (liste ltag){
  liste tagelem =ltag -> suivant;
  char *result = malloc (500 * sizeof(char));
  strcat (result, "Liste des tags");
  while (!est_tete(tagelem)){
    result = strcat(result, ",");
    result = strcat(result, ((tag *)(tagelem -> val))-> nom);
    tagelem = tagelem -> suivant;
  }
  result = strcat (result, "\n");
  printf("%s", result);
  free (result);
}

/*affiche les tags de la liste et leur peres associé */
void afficherFamilleTag (liste ltag){
  ltag = suivant (getTete (ltag));
  while (!est_tete (ltag)) {
    printf ("--%s\n", ((tag *)ltag->val)->nom);
    if (!est_vide (((tag *)ltag->val)->pere))
      afficherFamilleTag (((tag*)ltag->val)->pere);
    ltag = suivant (ltag);
  }
}
