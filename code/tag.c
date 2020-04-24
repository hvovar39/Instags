/*tag.c
Code faisant le liens fichier/tag
Fonction lier aux commandes (addtags, untag, lt, ...)
utilise gestionFichier.c et getsionTag.c
*/

#include "tag.h"

//Fonction de gestion de la liste des fichiers

/*cree un fichier et le place dans la liste lFichier 
 *retourne la liste des fichier
 *ou null en cas de probleme */

liste creerFichier (int inode, char *path, liste lFichier){
  fichier * fichier = malloc (sizeof(fichier));
  if (fichier == NULL)
    return NULL;
  fichier -> inode = inode;
  fichier -> path = path;
  liste ltag = creer_liste ();
  if (ltag == NULL)
    return NULL;
  fichier -> tag = ltag;
  if (inserer_avant (lFichier, fichier)== NULL)
    return NULL;
  return lFichier;
}

/*supprime le fichier f de la liste lFichier
 *retourne la liste lFichier si tout s'est bien passe, NULL sinon */

liste suppFichier (fichier f, liste lFichier){
  if (est_vide (lFichier))
    return NULL;
  else {
    if (supprimer_element (getElem(&f, lFichier)) == NULL)
      return NULL;
    else
      return lFichier;
  }
  return NULL;
}

/* retourn un fichier a partir de son inode */

fichier *getFichierI (int inode, liste lFichier){
  liste tmp = lFichier -> suivant;
  while (((fichier *)(tmp -> val))-> inode != inode){
    if (est_tete(tmp)) 
      return NULL;
    else
      tmp = tmp -> suivant;
  }
  return tmp -> val;
}

/*retourn un fichier à partir de son chemin */

fichier *getFichierP (char *path, liste lFichier){
  liste tmp = lFichier -> suivant;
  while (!strcmp(((fichier *)(tmp -> val))-> path, path)){
    if (est_tete(tmp)) 
      return NULL;
    else
      tmp = tmp -> suivant;
  }
  return tmp -> val;
}

//Fonctions de gestion du lien fichier/tag

/*Ajouter une liste de tag au fichier f
 *retourne un pointeur vers le fichier f
 */

fichier *ajouterTag (fichier *f, liste t){
  t = fusionner (f -> tag, t);
  if (t == NULL)
    return NULL;
  else
    f -> tag = t;
  return f;
}

/*Supprime une liste de tag t au fichier f 
 *retourne un pointeur vers le fichier f
 */
fichier *retirerTag (fichier *f, liste t){
  liste tmp = f -> tag -> suivant;
  liste sup = t -> suivant;
  if (est_vide (t))
    return f;
  while (sup -> val != NULL){
    while (tmp -> val != sup -> val && !est_tete(tmp))
	tmp = tmp -> suivant;
    if (!est_tete(tmp)){
      if (supprimer_element(tmp) == NULL)
	return NULL;
    }
    sup = sup -> suivant;
    tmp = f -> tag -> suivant;
  }
  return f;
}



/*estTaguer verifie si le fichier f  est taguer 
 *par la liste de tag present 
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/

int tagPresent ( fichier *f, liste present){
  liste tag = f -> tag -> suivant;
  liste verif = present -> suivant;
  while (!est_tete(verif)){
    while (tag != verif){
      if(est_tete(tag))
	return 0;
      tag = tag-> suivant;
    }
    verif = verif -> suivant;
  }
  return 1;
}

/*estTaguer verifie si le fichier f ne possede pas absent
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/

int tagAbsent (fichier *f, liste absent){
  liste  tag = f -> tag -> suivant;
  liste verif = absent -> suivant;
  while (!est_tete(verif)){
    while (!est_tete(tag)){
      if (verif == tag)
	return 0;
      tag = tag -> suivant;
    }
    verif = verif -> suivant;
  }
  return 1;
}

/*estTaguer verifie si la liste est taguer par tliste 
 *mais pas par nTListe, 
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/

int estTaguer (fichier *f, liste tListe, liste nTListe){
  if (tagPresent (f, tListe) && tagAbsent (f, nTListe))
    return 1;
  return 0;
}

fichier *changerPath (fichier f, char *newPath);
fichier *cpFichier (fichier f, int newInode, char *newPath);
