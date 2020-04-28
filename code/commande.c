/*INCLUDES
================================================================
*/

#include "commande.h"
#include "liste.h"

/*FONCTIONS
================================================================
*/

int ls (char * argv[], size_t t, liste lTag, liste lFic) {
  /*Execute ls, avec l'option spécifié. Traite l'option -TAG permettant
    de lister les fichiers contenant la composition de tag spécifié*/
  int res;
  if ( t<3 || strcmp (argv[1], "-TAG")){
    if ((res = fork()) == 0)
      execvp ("ls", argv);
    return res;
  }
  else {
    liste conj = creer_liste();
    liste neg = creer_liste();
    for (int i = 2; i<t; i++) {
      if (argv[i][0] == '!')
	insere_apres (neg, getTag (argv[i]+1, lTag));
      else
	insere_apres (conj, getTag (argv[i], lTag));
    }
    liste fic = getFichierTaguer (lFic, conj, neg);
    afficherListeFic (fic);
  }
  return 1;
}


int addtag (char *argv[], size_t t, liste lTag, liste lFic) {
  /*addtag permet d'ajouter un ou plusieurs tag au fichier spécifié.*/
  if (t<3) {
    printf ("Il manque des arguments:\nADDTAG fichier tag1 [tag2] [tag3] ...\n");
    return -1;
  }

  //On récupère ou creer le fichier concerné
  fichier * fic;
  struct stat statbuf;
  if ((fic = getFichierP (argv[1], lFic)) == NULL) {
    if (stat (argv[1], &statbuf) == -1){
      printf ("Oups! Il y a eu un soucis dans l'ajout des tags.\n");
      return -3;
    }
    fic = creerFichier (statbuf.st_ino, argv[1], lFic);
  }

  //On ajoute les tags au fichier, et a lTag si besoin
  liste tags = creer_liste();
  tag * newTag;
  for (int i = 2; i<t; i++) {
    if ((newTag = getTag (argv[i], lTag)) == NULL){
      newTag = creerTag (argv[i], creer_liste(), lTag);
    }
    insere_apres (tags, newTag);
  }


  if (ajouterTag (fic, tags) == NULL) {
    printf ("Oups! Il y a eu un soucis dans l'ajout des tags.\n");
    return -2;
  }
  printf ("Les tags");
  for (int j = 2; j<t; j++)
    printf (" %s", argv[j]);
  printf (" ont bien été ajouté au fichier %s.\n", argv[1]);
  return 1;
}
