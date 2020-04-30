#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "liste.h"
#include "fichier.h"
#include "gestionTag.h"

#ifndef COMMANDE_H
#define COMMANDE_H


int ls (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande ls

int addtag (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande ADDTAGS qui ajoute un tag à un fichier

int untag (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande UNTAG;

int lt (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande LT

int sontag (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande SONTAG

int sep_string (char *com, char c, char *argv[], int argc);


#endif
