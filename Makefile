CC = gcc

CFLAGS = -Wall -g

ALL = InsTags

F = code/

all : $(ALL)

liste.o : $(F)liste.c $(F)liste.h

gestionTag.o : $(F)gestionTag.c $(F)gestionTag.h $(F)liste.h

fichier.o : $(F)fichier.c $(F)fichier.h $(F)liste.h $(F)gestionTag.h

gestionSauvegarde.o : $(F)gestionSauvegarde.c $(F)gestionSauvegarde.h $(F)liste.h $(F)gestionTag.h $(F)fichier.h

commande.o : $(F)commande.c $(F)fichier.h $(F)liste.h

InsTags.o : $(F)InsTags.c $(F)liste.h $(F)fichier.h $(F)gestionTag.h $(F)gestionSauvegarde.h $(F)commande.h

InsTags : $(F)InsTags.o $(F)liste.o $(F)gestionSauvegarde.o $(F)fichier.o $(F)gestionTag.o $(F)commande.o
	gcc $(F)InsTags.o $(F)liste.o $(F)gestionSauvegarde.o $(F)fichier.o $(F)gestionTag.o $(F)commande.o -o InsTags

clean :
	rm -rf $(F)*~

cleanall :
	rm -rf $(F)*~ $(F)*.o $(ALL)
