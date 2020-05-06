/*tag.c
Code faisant le liens fichier/tag
Fonction lier aux commandes (addtags, untag, lt, ...)
utilise gestionFichier.c et getsionTag.c
*/

#include "fichier.h"

//Fonction de gestion de la liste des fichiers

/*cree un fichier et le place dans la liste lFichier 
 *retourne le fichier creer
 *ou null en cas de probleme */

fichier *creerFichier (int inode, char *path, liste lFichier){
  fichier * fichier = malloc (sizeof(fichier));
  if (fichier == NULL)
    return NULL;
  char * nom = malloc (sizeof (char) *(strlen (path)+1));
  nom[0] = '\0';
  strcpy (nom, path);
  fichier -> inode = inode;
  fichier -> path = nom;
  liste ltag = creer_liste ();
  if (ltag == NULL)
    return NULL;
  fichier -> tag = ltag;
  lFichier = getTete (lFichier);
  if (inserer_avant (lFichier, fichier) == NULL)
    return NULL;
  return fichier;
}

/*supprime le fichier f de la liste lFichier
 *retourne la liste lFichier si tout s'est bien passe, NULL sinon */

liste suppFichier (fichier *f, liste lFichier){
  if (est_vide (lFichier))
    return NULL;
  else {
    if (supprimer_element (getElem(f, lFichier)) == NULL)
      return NULL;
    else
      return lFichier;
  }
  return NULL;
}

/* retourn un fichier a partir de son inode */

fichier *getFichierI (int inode, liste lFichier){
  lFichier = suivant (getTete (lFichier));
  while (!est_tete (lFichier) && ((fichier *)(lFichier -> val))-> inode != inode)
    lFichier = suivant (lFichier);
  if (est_tete (lFichier))
    return NULL;
  return lFichier -> val;
}

//Fonctions de gestion du lien fichier/tag

/*Ajouter une liste de tag au fichier f
 *retourne un pointeur vers le fichier f
 */

fichier *ajouterTag (fichier *f, liste t){
  fusionner (f -> tag, t);
  return f;
}

/*Supprime une liste de tag t au fichier f 
 *retourne un pointeur vers le fichier f
 */
fichier *retirerTag (fichier *f, liste t){
  liste tmp = suivant (f -> tag);
  liste sup = suivant (getTete (t));
  if (est_vide (t))
    return f;
  while (!est_tete (t)){
    while (tmp -> val != sup -> val && !est_tete(tmp))
	tmp = tmp -> suivant;
    if (!est_tete(tmp)){
      tmp = suivant (tmp);
      if (supprimer_element(precedent (tmp)) == NULL)
	return NULL;
    }
    sup = suivant (sup);
  }
  return f;
}

/*estTaguer verifie si la liste est taguer par tliste 
 *mais pas par nTListe, 
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/
int estTaguer (fichier *f, liste tListe, liste nTListe){
  if (tagPresent (f->tag, tListe) && tagAbsent (f->tag, nTListe))
    return 1;
  return 0;
}

/*renvoi la liste des fichiers taguer par les tags tagpst 
 *mais pas par les tag tagabs*/

liste getFichierTaguer (liste lfichier, liste tagPst, liste tagAbs){
  liste result = creer_liste ();
  if (result == NULL)
    return NULL;
  liste tmp = suivant (getTete (lfichier));
  while (!est_tete(tmp)){
    if (estTaguer(tmp -> val, tagPst, tagAbs)){
      if (inserer_avant (result, tmp-> val)==NULL)
	return NULL;
    }
    tmp = tmp -> suivant;
  }
  return result;
}

/*modifie le chemin absolu vers le fichier */
fichier *changerPath (fichier *f, char *newPath){
  f->path = realloc (f->path, sizeof (char) * (strlen (newPath) - 1));
  strcpy (f->path, newPath);
  return f;
}

/*creer un nouveau fichier avec les même tag que f 
 *mais un nouvel inode et un nouveau chemin 
 *retourn NULL si la copie n'a pas eu lieu*/
fichier *cpFichier (fichier *f, int newInode, char *newPath, liste  lfichier){
  fichier *newf = creerFichier(newInode, newPath, lfichier);
  if (newf == NULL)
    return NULL;
  return ajouterTag(newf, f -> tag);
}

void afficherListeFic (liste lFic) {
  lFic = suivant (getTete (lFic));
  while (!est_tete (lFic)){
    printf (" %d -> %s\n", ((fichier *)lFic->val)->inode, ((fichier *)lFic->val)->path);
    lFic = suivant (lFic);
  }
}
