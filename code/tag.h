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
liste creerFichier (int inode, char *path, liste lFichier);
liste suppFichier (fichier f, liste lFichier);
fichier *getFichierI (int inode, liste lFichier);
fichier *getFichierP (char *path, liste lfichier);

//Fonctions de gestion du lien fichier/tag
fichier *ajouterTag (fichier f, liste t);
fichier *retirerTag (fichier f, liste t);
int estTaguer (fichier f, liste tListe, liste nTListe);
fichier *changerPath (fichier f, char *newPath);
fichier *cpFichier (fichier f, int newInode, char *newPath);


#endif
