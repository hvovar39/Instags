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
  liste conj;
  liste neg;
  liste fic;
  if ( t<3 || strcmp (argv[1], "-TAG")){
    if ((res = fork()) == 0)
      execvp ("ls", argv);
    return res;
  }
  else {
    conj = creer_liste();
    neg = creer_liste();
    for (int i = 2; i<t; i++) {
      if (argv[i][0] == '!')
	insere_apres (neg, getTag (argv[i]+1, lTag));
      else
	insere_apres (conj, getTag (argv[i], lTag));
    }
    fic = getFichierTaguer (lFic, conj, neg);
    afficherListeFic (fic);
  }
  detruire_liste(conj);
  detruire_liste(neg);
  detruire_liste(fic);
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
    detruire_liste (tags);
    return -2;
  }
  printf ("Les tags");
  for (int j = 2; j<t; j++)
    printf (" %s", argv[j]);
  printf (" ont bien été ajouté au fichier %s.\n", argv[1]);
  detruire_liste (tags);
  return 1;
}


int untag (char* argv[], size_t t, liste lTag, liste lFic) {
  /*untag retire les tags spécifié du fichier spécifié*/
  if (t<3) {
    printf ("Il manque des arguments:\nUNTAG fichier tag1 [tag2] [tag3] ...\n");
    return -1;
  }

  fichier * fic;
  if ((fic = getFichierP (argv[1], lFic)) == NULL) {
    printf ("Oups! Je n'ai pas trouver le fichier demandé.\n");
    return -1;
  }

  liste tags = creer_liste();
  tag * newTag;
  for (int i = 2; i<t; i++) {
    if ((newTag = getTag (argv[i], lTag)) == NULL){
      newTag = creerTag (argv[i], creer_liste(), lTag);
    }
    insere_apres (tags, newTag);
  }
  
  if (retirerTag (fic, tags) == NULL) {
    printf ("Oups! Il y a eu un soucis dans la deletions des tags.\n");
    detruire_liste (tags);
    return -2;
  }
  printf ("Les tags");
  for (int j = 2; j<t; j++)
    printf (" %s", argv[j]);
  printf (" ont bien été retirés du fichier %s.\n", argv[1]);
  detruire_liste (tags);
  return 1;
}


int lt (char* argv[], size_t t, liste lTag, liste lFic){
  /*lt gère la commande LT qui permet d'afficher les tags
    liés aux fichiers passés en argument.
    retourne le nombre de fichier traiter avec succès.
  */
  int res = 0;
  if (t<2){
    printf ("Il manque des arguments:\nLT fichier1 [fichier2] ...\n");
    return -1;
  }

  fichier * fic;
  
  for (int i = 1; i<t; i++) {
    if ((fic = getFichierP (argv[i], lFic)) == NULL)
      printf ("Oups! Il y a eu un soucis. Je n'ai pas trouver le fichier %s.\n", argv[i]);
    else {
      printf ("--%s :\n", argv[i]);
      afficherTag (fic->tag);
      res ++;
    }
  }
  return res;
}

int sontag (char* argv[], size_t t, liste lTag, liste lFic){
  /*traite la commande LT.
    Permet d'ajouter des peres au premier tag
    creer les tags qui n'existent pas
  */
  if (t<3) {
    printf ("Il manque des arguments:\nSONTAG fichierFils fichierPere1 [fichierPere2] ...\n");
    return -1;
  }

  tag * pere;
  liste lPere = creer_liste();
  for (int i = 2; i<t; i++) {
    if ((pere = getTag (argv[i], lTag)) == NULL)
      pere = creerTag (argv[i], creer_liste(), lTag);
    insere_apres (lPere, pere);
  }
  
  tag *fils;
  if ((fils = getTag (argv[1], lTag)) == NULL)
    creerTag (argv[1], lPere, lTag);
  else
    ajouterPere (fils, lPere);

  detruire_liste (lPere);
  return 1;
}

int sep_string (char *com, char *c, char *argv[], int argc) {
  char *tmp = strtok (com, c);
  int n = 0;
  
  while (n<argc-1 && tmp != NULL) {
    if (tmp [strlen(tmp)-1] == '\n')
      tmp [strlen(tmp)-1] = '\0';
    strcpy( argv[n++], tmp);
    tmp = strtok (NULL, c);
  }

  if (n < argc-1) {
    free (argv[n]);
    argv[n] = NULL;
  }

  return n;
}
