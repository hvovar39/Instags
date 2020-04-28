/*InsTags.c
Fichier principal
Contient la boucle d'interaction
*/

/*INCLUDES
================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "liste.h"
#include "gestionFichier.h"

/*DEFINE
================================================================
*/

#define ARGC 25


/*HEADERS
================================================================
*/

int loadFic (liste, liste);
int ls (char *[], size_t, liste);
void init_arg (char *[]);
void re_init_arg (char *[]);
int sep_com (char *, char *[], int);


/*MAIN
================================================================
*/

int main () {
  int n = 0, d;
  char *commande = malloc (500*sizeof(char));
  char *args[ARGC];
  init_arg (args);
  

  liste lTag = creer_liste();
  liste lFic = creer_liste();
  loadFic (lTag, lFic);
  
  while (fgets(commande, 500, stdin)) {
    if ( (n = sep_com (commande, args, ARGC)) == 0){
      //On separe la commande passer
      printf ("Oups, il y a eu un soucis avec la commande passé!\n");
      return -1;
    }
      
    if ( (d = strcmp ("ls", args[0])) == 0)
      ls (args, n, lTag);
    
    for (int i = 0; i<n; i++)
      printf("%d -> %s!\n", i, args[i]);
    
    re_init_arg (args); //On re malloc ce qui a été free
    printf (">");
    memset (commande, 0, strlen(commande)); 
  }

  

  return 0;
}


/*FONCTIONS
================================================================
*/

int loadFic (liste lTag, liste lFic) {
  //Chargement des listes de tag et de fichiers
  char buff[50];
  printf ("Souhaitez vous chargez les tags à partir des fichiers de sauvegarde ?\n >");
  fgets (buff, 50, stdin);
  if (buff[0] == 'y' && load (lTag, lFic, "TAG.csv", "FITAG.csv")){
    printf ("Fichier bien chagré\n");
    return 1;
  }
  printf ("Oups, il y a eu un soucis de chargement.\n");
  return 0;
}

int ls (char * argv[], size_t t, liste lTag) {
  //Execute ls, avec l'option spécifié. Traite l'option
  if ( t<5 || strcmp (argv[1] == "-TAG")){
    if (fork() == 0)
      execvp ("ls", argv);
    return 1;
  } else {
    liste conj = creer_liste();
    liste neg = creer_liste();
    for (int i = 3; i<t; i++) {
      if (argv[i][0] == '!')
	insere_apres (neg, getTag (argv[i]+1, lTag));
    }
  }
  return 1;
}

void init_arg (char *argv[]) {
  for (int i = 0; i<ARGC-1; i++)
    argv[i] = malloc (200*sizeof(char));
  argv[ARGC-1] = NULL;
}

void re_init_arg (char *argv[]) {
  for (int i = 0; i<ARGC-1; i++) {
    if (argv[i] == NULL)
      argv[i] = malloc (200*sizeof(char)); 
  }
}

int sep_com (char *com, char *argv[], int argc) {
  char *tmp = strtok (com, " ");
  int n = 0;
  
  while (n<argc-1 && tmp != NULL) {
    if (tmp [strlen(tmp)-1] == '\n')
      tmp [strlen(tmp)-1] = '\0';
    strcpy( argv[n++], tmp);
    tmp = strtok (NULL, " ");
  }

  if (n < argc-1) {
    free (argv[n]);
    argv[n] = NULL;
  }

  return n;
}

