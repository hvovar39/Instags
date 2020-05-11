/*INCLUDES
================================================================
*/

#include <sys/types.h>
#include <sys/wait.h>
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
  if ( t<2 || strcmp (argv[1], "-TAG")){
    if (fork() == 0)
      execvp ("ls", argv);
    return 1;
  }
  else {
    if (t==2){
      printf ("Il manque des arguments:\nls -TAG tag1 [tag2] [tag3] ...\n");
      return -1;
    }
    conj = creer_liste();
    neg = creer_liste();
    tag *tConj;
    tag *tNeg;
    for (int i = 2; i<t; i++) {
      if (argv[i][0] == '!') {
	if ((tNeg = getTag (argv[i]+1, lTag)) != NULL)
	  insere_apres (neg, tNeg);
      }else{
	if ((tConj = getTag (argv[i], lTag)) != NULL)
	  insere_apres (conj, tConj);
      }
    }
    if (!est_vide (conj) || !est_vide (neg)) {
      fic = getFichierTaguer (lFic, conj, neg);
      afficherListeFic (fic);
      detruire_liste(fic);
    }
  }
  detruire_liste(conj);
  detruire_liste(neg);
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
  char *tab[25];
  int n;
  for (int i = 0; i<25; i++){
    tab [i] = malloc (sizeof (char) * 25);
    tab[0] = '\0';
  }
  if (stat (argv[1], &statbuf) == -1){
    printf ("Oups! Je n'ai pas trouver le fichier demandé.\n");
    for (int i = 0; i<25; i++)
      free (tab[i]);
    return -2;
  }
  if ((fic = getFichierI (statbuf.st_ino, lFic)) == NULL){
    n = sep_string (argv[1], "/", tab, 25, 0);
    fic = creerFichier (statbuf.st_ino, tab[n-1], lFic);
  }
  
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
    for (int i = 0; i<25; i++)
      free (tab[i]);
    return -3;
  }
  printf ("Les tags");
  for (int j = 2; j<t; j++)
    printf (" %s", argv[j]);
  printf (" ont bien été ajouté au fichier %s.\n", argv[1]);
  for (int i = 0; i<25; i++)
      free (tab[i]);
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
  tag *sup;
  for (int i = 2; i<t; i++) {
    if ((sup = getTag (argv[i], lTag)) != NULL)
      insere_apres (tags, sup);
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
    printf ("Il manque des arguments:\nSONTAG tagFils tagPere1 [tagPere2] ...\n");
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
    fils = creerTag (argv[1], lTag);
  ajouterPere (fils, lPere);

  return 1;
}

int mv (char* argv[], size_t t, liste lTag, liste lFic){
  /*traite la commande mv.
    Change le nom du fichier concerné.
  */
  int flagOp = 0, i = 1, n;
  char *newName[50];
  struct stat statbuf;
  fichier *fic;
  for (int  i = 0; i<50; i++){
    newName[i] = malloc (sizeof (char)*50);
    newName[i][0] = '\0';
  }
  
  if (t>=3) {
    while (argv[i][0] == '-'){
      if (strchr (argv[i], 't'))
	flagOp++;
      i++;
    }

    if (!flagOp) {
      n = sep_string (argv[i+1], "/", newName, 50, 0);
      if (stat (argv[i], &statbuf) == -1 || (fic = getFichierI (statbuf.st_ino, lFic)) == NULL) {
	printf ("Oups, je n'ai pas trouvé le fichier demandé.\n");
	for (int i = 0; i<50; i++)
	  free (newName[i]);
	return -1;
      }
      if (changerPath (fic, newName[n-1]) == NULL) {
	printf ("Oups, il y a eu un soucis de déplacement du fichier.\n");
	for (int i = 0; i<50; i++)
	  free (newName[i]);
	return -2;
      }
    }
  }

  if (fork() == 0 && execvp ("mv", argv) == -1)
    return -3;
      	
  for (int i = 0; i<50; i++)
    free (newName[i]);	
  return 1;
}


int cp (char* argv[], size_t t, liste lTag, liste lFic){
//traite la commande cp
  if (fork() == 0 && execvp ("cp", argv) == -1)
    return -1;
  wait (NULL);
  
  fichier *ficO;
  fichier *ficC;
  struct stat statbufO;
  struct stat statbufC;
  int utile = 1, option = 0, n;
  char *tab[25];
  for (int  i = 0; i<25; i++){
    tab[i] = malloc (sizeof (char) * 25);
    tab[i][0] = '\0';
  }
  char *path = malloc (sizeof (char) * 200);
  path[0] = '\0';
  if (t>=3) {
    while (argv[utile][0] == '-'){
      if (strchr (argv[utile++], 't'))
	option++;
    }

    if (option) {
      for (int i = utile+1; i<t; i++) {
	if (stat (argv[i], &statbufO) == -1)
	  printf ("Oups! Je n'ai pas trouver le fichire d'origine.\n");
	else if ((ficO = getFichierI (statbufO.st_ino, lFic)) != NULL) {
	  n = sep_string (argv[i], "/", tab, 25, 0);
	  strcpy (path, argv[utile]);
	  strcat (path, "/");
	  strcat (path, tab[n-1]);
	  if (stat (path, &statbufC) == -1)
	    printf ("Oups! Je n'ai pas trouvé le fichier copié.\n");
	  else{
	    if ((ficC = creerFichier (statbufC.st_ino, tab[n-1], lFic)) != NULL)
	      ajouterTag (ficC, copier (ficO->tag));
	  }
	}
      }
    } else {
      for (int i = utile; i<t-1; i++) {
	if (stat (argv[i], &statbufO) == -1)
	  printf ("Oups! Je n'ai pas trouver le fichire d'origine.\n");
	else if ((ficO = getFichierI (statbufO.st_ino, lFic)) != NULL) {
	  n = sep_string (argv[i], "/", tab, 25, 0);
	  strcpy (path, argv[t-1]);
	  strcat (path, "/");
	  strcat (path, tab[n-1]);
	  if (stat (path, &statbufC) == -1)
	    printf ("Oups! Je n'ai pas trouvé le fichier copié.\n");
	  else{
	    if ((ficC = creerFichier (statbufC.st_ino, tab[n-1], lFic)) != NULL)
	      ajouterTag (ficC, copier (ficO->tag));
	  }
	}
      }
    }
  }
  
  for (int i = 0; i<25; i++)
    free (tab[i]);
  return 1;
}

int rm (char* argv[], size_t t, liste lTag, liste lFic){
//traite la commande rm

  fichier *fic;
  struct stat statbuf;
  for (int i = 1; i<t; i++) {
    if (lstat (argv[i], &statbuf) == -1)
      printf ("Oups! Le fichier demandé n'existe pas.\n");
    if (statbuf.st_nlink <= 1){
      if ((fic = getFichierI (statbuf.st_ino, lFic)) != NULL)
	suppFichier (fic, lFic);
    }
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
