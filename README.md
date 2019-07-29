   # Travail pratique 2

   ## Description

   Un petit programme qui fait de la cryptographie. La méthode  de césar (Caeser cipher) sera celle utilisée dans ce programme pour le cryptage des textes.
   Dans le cadre du cours INF3135 de l'Université du Quebec à Montréal.

   ## Auteur

   Okitapoy Koy Christian (OKIK08078702)

   ## Fonctionnement
Pour faire fonctionner le programme, il faut absolument passer des arguments par la ligne de commande. Voici les arguments obligatoires : -k suivi d’un chiffre entier, -c suivi d’une chaine de caractère de 12 caractères, -e ou -d (-d = décrypter et -e = encrypter). Voici les arguments facultatifs : -o suivie du nom du fichier sortant, -i suivi du nom du fichier entrant, -a suivi du chemin qui contient le fichier alphabet.txt.
Si les arguments facultatifs ne sont pas entrés, alors il faudra taper le texte a encrypter avec le clavier et si le fichier sortant n’est pas donné, alors le résultat sera affiché sur l’écran. On peut aussi partir le programme en mode bruteforce, pour le mode brutefoce, il faut entrer les arguments obligatoires suivant : -b pour specifier le mode, -l pour specifier le dossier des modeles de langue. les arguments -k et -e ou -d ne doivent pas etre entres.  

Exemple  :

* ./tp1 -c OKIK08078702 -e -k 90

Le prgramme demndera a l'utilisateur de taper le texte au clavier et affichera le résultat à l’écran. 

* ./tp1 -c OKIK08078702 -e -k 80 -i in.txt -o out.txt -a ./alpha/

Le programme va récupérer le contenu du fichier in.txt (ex : salut).
Il va encoder et mettre le résultat, qui sera ( ucnwv), dans le fichier out.txt

Exemple en mode bruteforce :

* ./tp1 -c OKIK08078702 -b -l dossier -i in.txt -o out.txt 



   ## Contenu du projet
* tp2.c : Un fichier de code source avec la fonction.

* README.md: Un fichier qui contient l'information sue l'usage de programme.

* makefile: Un fichier qui automatise des fonctions utiles au fonctionnement du progamme.

* .gitignore: Un fichier qui ignore certain type de fichiers pour ne pas les mettre dans le gestionnaire de source.

* cp.txt: un fichier qui contien le code permanent.

* evaluer-tp2.sh : un script pour rouler des tests

   ## Références

   Site web openclassroom : https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-lire-et-ecrire-dans-des-fichiers

   ## Statut

   COMPLETÉ
