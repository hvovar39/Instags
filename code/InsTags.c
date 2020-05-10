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
#include <sys/types.h>
#include <sys/wait.h>
#include "liste.h"
#include "gestionSauvegarde.h"
#include "commande.h"

/*DEFINE
================================================================
*/

#define ARGC 25


/*HEADERS
================================================================
*/

int loadFic (liste, liste);
void init_arg (char *[]);
void re_init_arg (char *[]);
int saveFic (liste, liste, char *);

/*MAIN
================================================================
*/

int main () {
  int n = 0;
  char *commande = malloc (500*sizeof(char));
  char buf [100];
  char *args[ARGC];
  init_arg (args);

  char savePath[100];
  getcwd (savePath, 100);
  
  liste lTag = creer_liste();
  liste lFic = creer_liste();
  loadFic (lTag, lFic);
  lTag = getTete (lTag);
  lFic = getTete (lFic);
  afficherTag (lTag);
  printf (">");
  
  while (fgets(commande, 500, stdin)) {
    if ( (n = sep_string (commande, " ", args, ARGC, 1)) == 0){
      //On separe la commande passer
      printf ("Oups, il y a eu un soucis avec la commande passé!\n");
      return -1;
    }
      
    if (strcmp ("ls", args[0]) == 0)
      ls (args, n, lTag, lFic);

    else if (strcmp ("ADDTAG", args[0]) == 0)
      addtag (args, n, lTag, lFic);

    else if (strcmp ("UNTAG", args[0]) == 0)
      untag (args, n, lTag, lFic);

    else if (strcmp ("LT", args[0]) == 0)
      lt (args, n, lTag, lFic);

    else if (strcmp ("SONTAG", args[0]) == 0)
      sontag (args, n, lTag, lFic);

    else if (strcmp ("mv", args[0]) == 0)
      mv (args, n, lTag, lFic);

    else if (strcmp ("cp", args[0]) == 0)
      cp (args, n, lTag, lFic);

    else if (strcmp ("rm", args[0]) == 0)
    rm (args, n, lTag, lFic);

    else if (strcmp ("cd", args[0]) == 0){
      if (chdir (args[1]) != 0){
	printf("Oups! Il y a eu un soucis de déplacement dans l'arborescence\n");
	return -1;
      } else 
	printf ("Nous nous sommes déplacé. Nous voici à :\n%s\n", getcwd (buf, 100));
    }

    else {
      if (fork() == 0 && execvp (args[0], args) == -1)
	exit (0);
    }
    
    re_init_arg (args); //On re malloc ce qui a été free
    wait (NULL);
    printf (">");
    memset (commande, 0, strlen(commande)); 
  }

  saveFic (lTag, lFic, savePath);
  detruire_liste (lFic);
  detruire_liste (lTag);
  free (commande);
  return 0;
}


/*FONCTIONS
================================================================
*/

int loadFic (liste lTag, liste lFic) {
  //Chargement des listes de tag et de fichiers
  char buff[50];
  printf ("Souhaitez vous chargez les tags à partir des fichiers de sauvegarde ?\n>");
  fgets (buff, 50, stdin);
  if (buff[0] == 'y' && (load (lTag, lFic, "TAG.csv", "FIC.csv"))){
    printf ("Fichier bien chagré\n");
    return 1;
  }
  else {
    if (buff[0] == 'n')
      return 1;
    printf ("Oups, il y a eu un soucis de chargement.\n");
  }
  return 0;
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


int saveFic (liste lTag, liste lFic, char *path) {
  char tag[120];
  tag[0] = '\0';
  strcat (tag, path);
  strcat (tag, "/TAG.csv");
  char fic[120];
  fic[0] = '\0';
  strcat (fic, path);
  strcat (fic, "/FIC.csv");
  
  char buff[50];
  printf ("Souhaitez vous sauvegarder les changements ?\n>");
  fgets (buff, 50, stdin);
  if (buff[0] == 'y' &&  save (lTag, lFic, tag, fic)){
    printf ("Sauvegarde éfféctuée.\n");
    return 1;
  }
  else {
    if (buff[0] == 'n')
      return 1;
    printf ("Oups, il y a eu un soucis de sauvegarde.\n");
  }
  return 0;
}
