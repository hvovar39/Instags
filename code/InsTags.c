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
int sep_com (char *, char *[], int);


/*MAIN
================================================================
*/

int main () {
  int n = 0;
  char *commande = malloc (500*sizeof(char));
  char *args[ARGC];
  init_arg (args);
  

  liste lTag = creer_liste();
  liste lFic = creer_liste();
  loadFic (lTag, lFic);
  printf (">");
  
  while (fgets(commande, 500, stdin)) {
    if ( (n = sep_string (commande, " ", args, ARGC)) == 0){
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
    
    re_init_arg (args); //On re malloc ce qui a été free
    wait (NULL);
    printf (">");
    memset (commande, 0, strlen(commande)); 
  }

  save (lTag, lFic, "TAG.csv", "FIC.csv");
  printf ("les tags ont bien été sauvegardés.\n");
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


