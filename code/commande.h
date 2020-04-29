#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "liste.h"
#include "tag.h"

#ifndef COMMANDE_H
#define COMMANDE_H


int ls (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande ls

int addtag (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande ADDTAGS qui ajoute un tag à un fichier

int untag (char* argv[], size_t t, liste lTag, liste lFic);
//traite la commande UNTAG;


#endif
