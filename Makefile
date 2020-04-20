CC = gcc

CFLAGS = -Wall -g

ALL = InsTags

F = code/

all : $(ALL)

liste.o : $(F)liste.c $(F)liste.h

gestionTag.o : $(F)gestionTag.c $(F)gestionTag.h $(F)liste.h

tag.o : $(F)tag.c $(F)tag.h $(F)liste.h $(F)gestionTag.h

gestionFichier.o : $(F)gestionFichier.c $(F)gestionFichier.h $(F)liste.h $(F)gestionTag.h $(F)tag.h

InsTags.o : $(F)InsTags.c $(F)liste.h $(F)tag.h $(F)gestionTag.h $(F)gestionFichier.h

InsTags : $(F)InsTags.o $(F)liste.o $(F)gestionFichier.o $(F)tag.o $(F)gestionTag.o
	gcc $(F)InsTags.o $(F)liste.o $(F)gestionFichier.o $(F)tag.o $(F)gestionTag.o -o InsTags

clean :
	rm -rf $(F)*~

cleanall :
	rm -rf $(F)*~ $(F)*.o $(ALL)
