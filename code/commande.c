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
  liste conj;
  liste neg;
  liste fic;
  if ( t<3 || strcmp (argv[1], "-TAG")){
    if (fork() == 0)
      execvp ("ls", argv);
    return 1;
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
  if (stat (argv[1], &statbuf) == -1){
    printf ("Oups! Je n'ai pas trouver le fichier demandé.\n");
    return -2;
  }
  if ((fic = getFichierI (statbuf.st_ino, lFic)) == NULL)
    fic = creerFichier (statbuf.st_ino, argv[1], lFic);

  //On ajoute les tags au fichier, et a lTag si besoin
  liste tags = creer_liste();
  tag * newTag;
  for (int i = 2; i<t; i++) {
    if ((newTag = getTag (argv[i], lTag)) == NULL){
      newTag = creerTag (argv[i], lTag);
    }
    insere_apres (tags, newTag);
  }


  if (ajouterTag (fic, tags) == NULL) {
    detruire_liste (tags);
    return -3;
  }
  printf ("Les tags");
  for (int j = 2; j<t; j++)
    printf (" %s", argv[j]);
  printf (" ont bien été ajouté au fichier %s.\n", argv[1]);
  return 1;
}


int untag (char* argv[], size_t t, liste lTag, liste lFic) {
  /*untag retire les tags spécifié du fichier spécifié*/
  if (t<3) {
    printf ("Il manque des arguments:\nUNTAG fichier tag1 [tag2] [tag3] ...\n");
    return -1;
  }

  fichier * fic;
  struct stat statbuf;
  if (stat (argv[1], &statbuf) == -1){
    printf ("Oups! Je n'ai pas trouver le fichier demandé.\n");
    return -2;
  }
  if ((fic = getFichierI (statbuf.st_ino, lFic)) == NULL){
    printf ("Oups! Je n'ai pas trouver le fichier demandé.\n");
    return -3;
  } 

  liste tags = creer_liste();
  tag * newTag;
  for (int i = 2; i<t; i++) {
    if ((newTag = getTag (argv[i], lTag)) == NULL){
      newTag = creerTag (argv[i], lTag);
    }
    insere_apres (tags, newTag);
  }
  
  if (retirerTag (fic, tags) == NULL) {
    printf ("Oups! Il y a eu un soucis dans la deletions des tags.\n");
    detruire_liste (tags);
    return -4;
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
  struct stat statbuf;
  for (int i = 1; i<t; i++) {
    if (stat (argv[1], &statbuf) == -1)
      printf ("Oups! Je n'ai pas trouvé le fichier demandé.\n");
    else{
      if ((fic = getFichierI (statbuf.st_ino, lFic)) == NULL)
	fic = creerFichier (statbuf.st_ino, argv[1], lFic);
      printf ("--%s :\n", argv[i]);
      afficherFamilleTag (fic->tag);
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
      pere = creerTag (argv[i], lTag);
    insere_apres (lPere, pere);
  }
  
  tag *fils;
  if ((fils = getTag (argv[1], lTag)) == NULL)
    creerTag (argv[1], lTag);
  else
    ajouterPere (fils, lPere);

  detruire_liste (lPere);
  return 1;
}

int mv (char* argv[], size_t t, liste lTag, liste lFic){
  /*traite la commande mv.
    Change le nom du fichier concerné.
  */

  fichier * fic;
  struct stat statbuf;
  int utile = 1, option = 0, n;
  char *tab[25];
  if (t>=3) {
    while (argv[utile][0] == '-'){
      if (strchr (argv[utile++], 't') != NULL)
	option++;
    }

    if (!option) {
      n = sep_string (argv[utile+1], "/", tab, 25, 0);
      if (stat (argv[utile], &statbuf) == -1)
	printf ("Oups! Je n'ai pas trouvé le fichier demandé.\n");
      else{
	if ((fic = getFichierI (statbuf.st_ino, lFic)) != NULL)
	  fic->path = tab[n-1];
      }
    }
  }

  if (fork() == 0)
    execvp ("mv", argv);

  return 1;
}


int cp (char* argv[], size_t t, liste lTag, liste lFic){
//traite la commande cp
  if (fork() == 0)
    execvp ("cp", argv);
  
  fichier *ficO;
  fichier *ficC;
  struct stat statbufO, statbufC;
  int utile = 1, option = 0, n;
  char *tab[25];
  char path[200];
  if (t>=3) {
    while (argv[utile][0] == '-'){
      if (strchr (argv[utile++], 't') != NULL)

	option++;
    }

    if (option) {
      for (int i = utile+1; i<t; i++) {
	n = sep_string (argv[i], "/", tab, 25, 0);
	strcpy (path, argv[1]);
	strcat (path, tab[n-1]);
	if (stat (path, &statbufC) == -1 || stat (argv[i], &statbufO) == -1)
	  printf ("Oups! Je n'ai pas trouvé le fichier demandé.\n");
	else{
	  if ((ficC = creerFichier (statbufC.st_ino, tab[n-1], lFic)) != NULL && (ficO = getFichierI (statbufO.st_ino, lFic)) != NULL )
	    ajouterTag (ficC, ficO->tag);
	}
      }
    }else {
      for (int i = utile; i<t-1; i++) {
	n = sep_string (argv[i], "/", tab, 25, 0);
	strcpy (path, argv[t-1]);
	strcat (path, tab[n-1]);
	if (stat (path, &statbufC) == -1 || stat (argv[i], &statbufO) == -1)
	  printf ("Oups! Je n'ai pas trouvé le fichier demandé.\n");
	else{
	  if ((ficC = creerFichier (statbufC.st_ino, tab[n-1], lFic)) != NULL && (ficO = getFichierI (statbufO.st_ino, lFic)) != NULL )
	    ajouterTag (ficC, ficO->tag);
	}
      }
    }
  }
  return 1;
}

int rm (char* argv[], size_t t, liste lTag, liste lFic){
//traite la commande rm

  fichier *fic;
  struct stat statbuf;
  for (int i = 1; i<t; i++) {
    if (stat (argv[i], &statbuf) == -1)
      printf ("Oups! Le fichier demandé n'existe pas.\n");
    if ((fic = getFichierI (statbuf.st_ino, lFic)) != NULL)
      suppFichier (fic, lFic);
  }
  if (fork() == 0)
    execvp ("rm", argv);

  return 1;
}



int sep_string (char *com, char *c, char *argv[], int argc, int commande) {
  char *tmp = strtok (com, c);
  int n = 0;
  
  while (n<argc-1 && tmp != NULL) {
    if (tmp [strlen(tmp)-1] == '\n')
      tmp [strlen(tmp)-1] = '\0';
    strcpy (argv[n++], tmp);
    tmp = strtok (NULL, c);
  }

  if (n < argc-1 && commande) {
    free (argv[n]);
    argv[n] = NULL;
  }

  return n;
}
