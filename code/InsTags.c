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


/*DEFINE
================================================================
*/

#define ARGC 25


/*HEADERS
================================================================
*/

int ls (char *[]);
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
  printf (">");
  
  while (fgets(commande, 500, stdin)) {
    if ( (n = sep_com (commande, args, ARGC)) != 0){
      //On separe la commande passer
      
      if ( (d = strcmp ("ls", args[0])) == 0)
	ls (args);
      
      for (int i = 0; i<n; i++)
	printf("%d -> %s!\n", i, args[i]);
      
      re_init_arg (args); //On re malloc ce qui a été free
      printf (">");
      memset (commande, 0, strlen(commande));
    }
  }

  return 0;
}


/*FONCTIONS
================================================================
*/
    

int ls (char * argv[]) {
  if (fork() == 0)
    execvp ("ls", argv);
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

