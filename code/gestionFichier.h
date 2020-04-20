#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

int save (liste lTag, liste lFile, char *fileT, char * fileF);
//sauvegarde la liste des tags et des fichiers dans fileT et fileF
int saveTag (liste lTag, int desc);
//Sauvegarde la liste des tags dans le fichier ayant pour descripteir desc
int saveFile (liste lFile, int desc);
//Sauvegarde la liste des fichiers dans le fichier ayant pour descripteir desc

int load (liste lTag, liste lFile, char *fileT, char *fileF);
//charge les fichiers et les tags à partir des fichiers fileT et fileF
int loadTag (liste lTag, int desc);
int loadFile (liste lFile, int desc);

#endif
