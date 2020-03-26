Nous avons fait le choix d'attribuer les tags aux fichiers en créant une liste 
sur laquelle serait stocker les numéros d'e-noeud des fichiers et les tags qui 
lui sont associé (nous appeleront ce fichier le FITAG). Ainsi qu'un fichier 
dans lequel serait stocker les tags existant et leur lien de " parenté ". 

Lorsque l'on lance le programme une fonction LOAD chargera l'arborescence des
tags. A la fin du programme une fonction SAVE enregistrera les modification 
faite sur cette arbre.

ADDTAGS : permet de marquer un fichier avec un/des tags donc de le rajouter 
dans FITAG (si il y est déjà de rajouter seulement les nouveau tags à sa liste; 
si il n'y est pas rajouter une ligne avec son numéro d'enoeud et les tags qui 
lui sont associé.)

UNTAG : permet d'effacer un tag d'un fichier et donc de le supprimer de la liste 
des tags du fichier dans FITAG

LT : permet de lister les tags d'un fichier

LS -TAG : permet de lister les fichier avec les tags demandé

SONTAG : permet de spécifier un lien hierarchique entre deux tags (modifie donc 
l'arbre des tags ainsi que les tags des fichiers déjà existant)

Les fonctions déjà existante :

mv : FITAG fonctionnant avec le numero d'enoeud des fichier il n'y a pas de 
changement à prévoir.

cp : copier un fichier créer un nouveau fichier avec un nouvel enoeud, il faudra
donc copier les tags du premier fichier pour créer le second mais une fois cela 
fait les fichier et leur tags sont independant.

ln : un lien physique à le même enoeud que le fichier, cela ne pose donc pas de 
probleme.
Pour les lien symbolique nous avont un nouvel e noeud il faudra donc que l'on 
accede au fichier pour obtenir les tags.

rm : Si l'on supprime un fichier on doit le supprimer de FITAG