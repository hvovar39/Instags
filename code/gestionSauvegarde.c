/*gestionSauvegarde.c
Code lier à la gestions des fichiers.
Ecriture et lecture des fichiers de sauvegardes.
*/

/*INCLUDES
================================================================
*/

#include "gestionSauvegarde.h"
#define SEP ","

/*FONCTIONS
================================================================
*/


//sauvegarde la liste des tags et des fichiers dans fileT et fileF

int save (liste lTag, liste lFile, char *fileT, char * fileF){
  FILE *ft;
  FILE *ff;
  if ((ft = fopen (fileT, "w")) != NULL) {
    if ((ff = fopen (fileF, "w")) != NULL) {
      if (saveTag (lTag, ft) && saveFile (lFile, ff)) {
	fclose (ft);
	fclose (ff);
	return 1;
      }
      fclose (ff);     	
    }
    fclose (ft);
  }
  return 0;
}


//Sauvegarde la liste des tags dans le fichier f (nom du tag et noms des peres, separer par SEP et un saut de ligne apres chaque tag.
//retourne 0 en cas d'échec et 1 si la sauvegarde à bien marché.

int saveTag (liste lTag, FILE *f){
  char *result=malloc (1000*sizeof(char));
  result[0]='\0';
  if (result==NULL)
    return 0;
  liste tmp = suivant (getTete (lTag));
  liste tmppere;
  while (!est_tete (tmp)){
    result = strcat (result, ((tag *)tmp->val)->nom);
    tmppere = suivant (getTete (((tag *)tmp->val)->pere));
    while (!est_tete(tmppere)){
      result = strcat (result, SEP);
      result = strcat (result, ((tag *)tmppere->val)->nom);
      tmppere = suivant (tmppere);
    }
    result = strcat (result, "\n");
    fprintf (f, "%s", result);
    memset (result, 0, strlen (result));
    result[0] = '\0';
    tmp = suivant (tmp);
  }
  free (result);
  return 1;
}


//Sauvegarde la liste des fichiers dans le fichier f

int saveFile (liste lFile, FILE *f){
  char *result=malloc (100*sizeof(char));
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
      tmptag = suivant (tmptag);
    }
    result = strcat(result,"\n");
    fprintf(f,"%s",result);
    memset(result, 0, strlen(result));
    result[0]='\0';
    tmp = suivant(tmp);
  }
  free(result);
  return 1;
}

//charge les fichiers et les tags à partir des fichiers fileT et fileF

int load (liste lTag, liste lFile, char *fileT, char *fileF){
  FILE *ft;
  FILE *ff;
  if ((ft = fopen (fileT, "r")) != NULL) {
    if ((ff = fopen (fileF, "r")) != NULL) {
      if (loadTag (lTag, ft) && loadFile (lFile, lTag, ff)) {
	fclose (ft);
	fclose (ff);
	return 1;
      }
      fclose (ff);     	
    }
    fclose (ft);
  }
  return 0;
}

//charge les tags à partir d'un fichier 

int loadTag (liste lTag, FILE *f){
  char *tab[50];
  for (int c = 0; c<50; c++){
    tab[c] = malloc (50*sizeof(char));
    tab[c][0] = '\0';
  }
  char buff[500];
  int i;
  tag *t;
  liste lPere;
  while (fgets(buff, 500, f)){
    i=sep_string(buff, SEP, tab, 50, 0);
    
    lPere = creer_liste();
    for (int j = 1; j<i; j++) {
      if ((t = getTag (tab[j], lTag)) == NULL){
	t = creerTag (tab[j], lTag);
	if(t==NULL){
	  for (int c = 0; c>50; c++)
	    free (tab[c]);
	  return 0;
	}
      }
      insere_apres (lPere, t);
    }
    if ((t = getTag (tab[0], lTag)) == NULL)
      t = creerTag (tab[0], lTag); 
    ajouterPere (t, lPere);
  }
  for (int c = 0; c>50; c++)
    free (tab[c]); 
  return 1;  
}

//charge des fichier à partir d'un fichier f

int loadFile (liste lFile,liste lTag, FILE *f){
  char *tab[50];
  for (int c = 0; c<50; c++){
    tab[c] = malloc (50*sizeof(char));
    tab[c][0] = '\0';
  }
  char buff[500];
  int i;
  tag *t;
  liste tag;
  while (fgets(buff, 500, f)){ 
    i=sep_string(buff, SEP, tab, 100, 0);
    
    tag = creer_liste();
    for (int j = 2; j<i; j++) {
      if ((t = getTag (tab[j], lTag)) == NULL){
	  t = creerTag (tab[j], lTag);
	  if(t==NULL)
	    return 0;
      }
      insere_apres (tag, t);
    }
    fichier *new = creerFichier(atoi(tab[0]), tab[1], lFile);
    if (new == NULL){
      for (int c = 0; c>50; c++)
	free (tab[c]);
      return 0;
    }
    if (ajouterTag(new, tag)==NULL){
      for (int c = 0; c>50; c++)
	free (tab[c]);
      return 0;
    }
  }
  for (int c = 0; c>50; c++)
    free (tab[c]);
  return 1;
}

