#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "gestionTag.h"

#ifndef TAG_H
#define TAG_H

struct fichier {
  int inode;
  char * path;
  liste tag;
};
typedef struct fichier fichier;
//Fonction de gestion de la liste des fichiers

/*cree un fichier et le place dans la liste lFichier 
 *retourne le fichier creer
 *ou null en cas de probleme */
fichier *creerFichier (int inode, char *path, liste lFichier);

/*supprime le fichier f de la liste lFichier
 *retourne la liste lFichier si tout s'est bien passe, NULL sinon */
liste suppFichier (fichier f, liste lFichier);

/* retourn un fichier a partir de son inode */
fichier *getFichierI (int inode, liste lFichier);

/*retourn un fichier à partir de son chemin */
fichier *getFichierP (char *path, liste lfichier);

//Fonctions de gestion du lien fichier/tag

/*Ajouter une liste de tag au fichier f
 *retourne un pointeur vers le fichier f
 */
fichier *ajouterTag (fichier *f, liste t);

/*Supprime une liste de tag t au fichier f 
 *retourne un pointeur vers le fichier f
 */
fichier *retirerTag (fichier *f, liste t);

/*tagPresent verifie si le fichier f  est taguer 
 *par la liste de tag present 
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/
int tagPresent ( fichier *f, liste present);

/*tagAbsent verifie si le fichier f ne possede pas absent
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/
int tagAbsent (fichier *f, liste absent);

/*estTaguer verifie si la liste est taguer par tliste 
 *mais pas par nTListe, 
 *retourn n =/= 0 si le fichier respect les conditions, 0 sinon*/
int estTaguer (fichier *f, liste tListe, liste nTListe);

/*renvoi la liste des fichiers taguer par les tags tagpst 
 *mais pas par les tag tagabs*/
liste getFichierTaguer (liste lfichier, liste tagPst, liste tagAbs);

/*modifie le chemin absolu vers le fichier */
fichier *changerPath (fichier *f, char *newPath);

/*creer un nouveau fichier avec les même tag que f 
 *mais un nouvel inode et un nouveau chemin 
 *retourn NULL si la copie n'a pas eu lieu*/
fichier *cpFichier (fichier *f, int newInode, char *newPath, liste lfichier);


#endif
