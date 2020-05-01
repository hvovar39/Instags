#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "liste.h"
#include "gestionTag.h"
#include "fichier.h"
#include "commande.h"


#ifndef GESTIONSAUVEGARDE_H
#define GESTIONSAUVEGARDE_H

int save (liste lTag, liste lFile, char *fileT, char * fileF);
//sauvegarde la liste des tags et des fichiers dans fileT et fileF
int saveTag (liste lTag, FILE *f);
//Sauvegarde la liste des tags dans le fichier ayant pour descripteir desc
int saveFile (liste lFile, FILE *f);
//Sauvegarde la liste des fichier  dans le fichier ayant pour descripteir desc

int load (liste lTag, liste lFile, char *fileT, char *fileF);
//charge les fichiers et les tags à partir des fichiers fileT et fileF
int loadTag (liste lTag, FILE *f);
int loadFile (liste lFile, liste lTag, FILE *f);

#endif
