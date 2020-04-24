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
  liste tag = creer_liste ();
  if (tag == NULL)
    return NULL;
  fichier -> tag = tag;
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
fichier *ajouterTag (fichier f, liste t);
fichier *retirerTag (fichier f, liste t);
int estTaguer (fichier f, liste tListe, liste nTListe);
fichier *changerPath (fichier f, char *newPath);
fichier *cpFichier (fichier f, int newInode, char *newPath);
