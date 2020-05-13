# InsTags
Marianne LEMOINNE
Hugo VOVARD

**Lien de la video de presentation**
https://youtu.be/YI5w4EmbwWM

Projet résalisé dans le cadre du cours de Système 2020 de la L3 informatique de l'université de Paris.

Ce programme se veut être un système de gestion de tag associé à vos fichier.

Pour **compiler** le programme, entrer les commandes:
```
make cleanall
make
```

Le **code source** se trouve dans le sous répertoire instags/code. Pour plus d'information, veuillez consulter ARCHITECHTURE.md

Pour **lancer le programme**, une fois compilée, entrer la commande:
`./Instags`
Une fois le programme lancer, tout fonctionne comme dans votre shell. Vous pouvez utiliser vos commandes habituelles.
Pour la gestion des tags, les commandes sont listées ci dessous.

Vos tags seront sauvegardé dans un fichier **TAG.csv** situé dans /instags. Le lien entre vos fichiers et vos tag est sauvegardé dans un second fichier, nommé **FIC.csv**, lui aussi situé dans /instags.

**RESUME DES COMMANDES:**

    ADDTAG : permet de marquer un fichier avec un/des tags.
    **ADDTAG Fichier Tag1 [Tag2] [Tag3] ...**

    UNTAG : permet d'effacer un/des tags d'un fichier.
    **UNTAG Fichier Tag1 [Tag2] [Tag3] ...**

    LT : permet de lister les tags d'un ou plusieurs fichiers.
    **LT Fichier1 [Fichier2] [Fichier3] ...**

    LS -TAG : permet de lister les fichier avec la combinaison de tags demandée. Un tag précédé de '!' est considéré comme la négation de ce tag.
    **LS -TAG [tag1] ... [!tag2] ...**
    *Exemple : LS -TAG couleur !bleu voiture
    Liste les fichiers comportant le tag couleur et voiture mais pas bleu*

    SONTAG : permet de spécifier un lien hierarchique entre deux tags.
    **SONTAG tagFils tagPere1 [tagPere2] ...**