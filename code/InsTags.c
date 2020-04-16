/*InsTags.c
Fichier principal
Contient la boucle d'interaction
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main () {
  char * commande = malloc (500*sizeof(char));
  while (fgets(commande, 500, stdin)) {
    printf ("%s", commande);
    memset (commande, 0, strlen(commande));
  }

  return 0;
}
    
