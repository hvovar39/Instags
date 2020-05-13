**Lien de la video de presentation** 
https://youtu.be/YI5w4EmbwWM

Nous avons fait le choix d'associé les numéros d'e-noeud des fichiers avec une liste de tag leurs correspondants.
De ce faites, nous travaillons principalement avec 2 listes circulaires doublement chainées:
-La liste des tags, qui contient la totalité des tags créés.
-La liste des fichiers, qui contient tous les fichiers marqué par au moins un tag.

Les deux structures utilisé dans ces listes sont :
-La strucutre tag, composé d'un nom (chaine de charactère) et d'une liste de tag père.
-La structure fichier, composé du nom du fichier, de sont numéros d'i-neud et d'une liste des tags qui lui sont associé.

Les deux listes seront sauvegardé au format csv dans deux fichiers:
-La liste des tags sera sauvegardé dans TAG.csv
-La liste des fichiers sera sauvegardé dans FIC.csv

Lorsque l'on lance le programme une fonction LOAD chargera la liste des tags et celle des fichiers.
A la fin du programme une fonction SAVE enregistrera les modification faite sur ces listes.


RESUME DES COMMANDES CREE:

    ADDTAG : permet de marquer un fichier avec un/des tags (Rajoute le fichier/les tags à la liste concérné si besoin)
    ADDTAG Fichier Tag1 [Tag2] [Tag3] ...

    UNTAG : permet d'effacer un/des tags d'un fichier (supprime le fichier de la liste si il n'a plus de tag)
    UNTAG Fichier Tag1 [Tag2] [Tag3] ...

    LT : permet de lister les tags d'un ou plusieurs fichiers
    LT Fichier1 [Fichier2] [Fichier3] ...

    LS -TAG : permet de lister les fichier avec les tags demandé. Un tag précédé de '!' est considéré comme la négation de ce tag
    LS -TAG [tag1] ... [!tag2] ...
    Exemple : LS -TAG couleur !bleu voiture
    Liste les fichiers comportant le tag couleur et voiture mais pas bleu

    SONTAG : permet de spécifier un lien hierarchique entre deux tags (créé les tags si besoin)
    SONTAG tagFils tagPere1 [tagPere2] ...

RESUME DES COMMMANDE A PRENDRE EN COMPTE:

    mv : Modifie le path du fichier. Ne modifie pas sont numéros d'i-noeud ou ses tags.

    cp : Copier un fichier créer un nouveau fichier avec un nouvel i-noeud. Les tags du fichiers d'origines seront copier pour le fichier créé.
    
    ln : un lien physique à le même enoeud que le fichier, cela ne pose donc pas de probleme.
    Pour les lien symbolique nous avont un nouvel e noeud il faudra donc que l'on 
    accede au fichier pour obtenir les tags.

    rm : Si l'on supprime un fichier on doit le supprimer de la liste des fichiers