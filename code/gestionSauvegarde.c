/*gestionFichier.c
Code lier à la gestions des fichiers.
Ecriture et lecture des fichiers de sauvegardes.
*/

#include "gestionSauvegarde.h"
#define SEP ","


//sauvegarde la liste des tags et des fichiers dans fileT et fileF
int save (liste lTag, liste lFile, char *fileT, char * fileF){
  FILE *ft =fopen (fileT, "w");
  if(ft!=NULL && saveTag(lTag,ft))
    return 1;
  else
    return 0;
  FILE *ff = fopen(fileF, "w");
  if(ff!=NULL && saveTag(lFile,ff))
    return 1;
  else
    return 0;
}


//Sauvegarde la liste des tags dans le fichier f (nom du tag et noms des peres, separer par SEP et un saut de ligne apres chaque tag.
//retourne 0 en cas d'échec et 1 si la sauvegarde à bien marché.
int saveTag (liste lTag, FILE *f){
  char *result=malloc (500*sizeof(char));
  result[0]='\0';
  if (result==NULL)
    return 0;
  liste tmp = getTete(lTag);
  tmp = tmp -> suivant;
  while (!est_tete(tmp)){
    result = strcat(result,((tag *)(tmp->val))->nom);
    liste tmppere = getTete(((tag *)(tmp->val))->pere);
    tmppere=tmppere ->suivant;
    while (!est_tete(tmppere)){
      result=strcat(result,SEP);
      result=strcat(result,((tag *)(tmppere->val))->nom);
    }
    result = strcat(result,"\n");
    fprintf(f,"%s",result);
    memset(result, 0, strlen(result));
    result[0]='\0';
  }
  free(result);
  return 1;
}


//Sauvegarde la liste des fichiers dans le fichier f
int saveFile (liste lFile, FILE *f){
  char *result=malloc (500*sizeof(char));
  char buff[20];
  result[0]='\0';
  if (result==NULL)
    return 0;
  liste tmp = getTete(lFile);
  tmp = tmp -> suivant;
  while (!est_tete(tmp)){
    sprintf (buff,  "%d", ((fichier *)(tmp->val))->inode);
    result = strcat(result,buff);
    result = strcat(result,SEP);
    result = strcat(result,((fichier *)(tmp->val))->path);
    liste tmptag = getTete(((fichier *)(tmp->val))->tag);
    tmptag=tmptag ->suivant;
    while (!est_tete(tmptag)){
      result=strcat(result,SEP);
      result=strcat(result,((tag *)(tmptag->val))->nom);
    }
    result = strcat(result,"\n");
    fprintf(f,"%s",result);
    memset(result, 0, strlen(result));
    result[0]='\0';
  }
  free(result);
  return 1;
}

int load (liste lTag, liste lFile, char *fileT, char *fileF){
  return 1;
    }
//charge les fichiers et les tags à partir des fichiers fileT et fileF
int loadTag (liste lTag, int desc){
  return 1;
}
int loadFile (liste lFile, int desc){
  return 1;
}
