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
  if(ff!=NULL && saveFile(lFile,ff))
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
  FILE *ft = fopen (fileT, "r");
  if(ft!=NULL && loadTag(lTag,ft))
    return 1;
  else
    return 0;
  FILE *ff = fopen(fileF, "r");
  if(ff!=NULL && loadFile(lFile,lTag,ff))
    return 1;
  else
    return 0;
}

//charge les fichiers et les tags à partir des fichiers fileT et fileF
int loadTag (liste lTag, FILE *f){
  char *tab[100];
  char buff[500];
  int i;
  tag *t;
  liste lPere;
  while (fgets(buff, 500, f)){ 
      i=sep_string(buff, SEP, tab, 100);

      lPere = creer_liste();
      for (int j = 1; j<i; j++) {
	if ((t = getTag (tab[j], lTag)) == NULL){
	  t = creerTag (tab[j], creer_liste(), lTag);
	  if(t==NULL)
	    return 0;
	}
	insere_apres (lPere, t);
      }
      if ((t = getTag (tab[0], lTag)) == NULL){
	if(creerTag (tab[0], lPere, lTag) ==NULL)
	  return 0;
      }
      else{
	if(ajouterPere (t, lPere)==NULL)
	  return 0;
	if(!detruire_liste (lPere))
	  return 0;

      }
  }
  return 1;  
}

int loadFile (liste lFile,liste lTag, FILE *f){
  char *tab[100];
  char buff[500];
  int i;
  tag *t;
  liste tag;
  while (fgets(buff, 500, f)){ 
    i=sep_string(buff, SEP, tab, 100);
    
    tag = creer_liste();
    for (int j = 2; j<i; j++) {
      if ((t = getTag (tab[j], lTag)) == NULL){
	  t = creerTag (tab[j], creer_liste(), lTag);
	  if(t==NULL)
	    return 0;
      }
      insere_apres (tag, t);
    }
    fichier *new = creerFichier(atoi(tab[0]), tab[1], lFile);
    if (new == NULL)
      return 0;
    if (ajouterTag(new, tag)==NULL)
      return 0;
    if(!detruire_liste(tag))
      return 0;
  }
  return 1;
}

