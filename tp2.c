#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>





#define IN "<"
#define OUT ">"
#define ARG_CODE_P  "-c"
#define ARG_ENCRYPT "-e"
#define ARG_DECRYPT "-d"
#define ARG_CLE "-k"
#define ARG_B "-b"
#define ARG_BF "--bruteforce"
#define ARG_MODELS "-l"

#define ARG_ENTREE "-i"
#define ARG_SORTIE "-o"
#define ARG_FIC_ALPHA "-a"
#define ALPHA "alphabet.txt"
#define ALPHA_SLASH "/alphabet.txt"







//reprent un mot
typedef struct{
  char mot[30];

}mots_s;







double compteMot(char text[]){

    int taille = strlen(text);
    double nbrMots = 1;

    int indiceDebut = 0;

    for(int i = 0; i < taille; i++){
        if(text[i] != ' '){
         indiceDebut = i;
         break;
        }
    }




    for(int i = indiceDebut; i < taille; i++){


       if(text[i] == ' '){

         while(text[i] == ' '){
          i++;
         };

         if(text[i] != '\0'){
         nbrMots++;
         }
       }
    }

return nbrMots;

}











int occurrence(char string[],int taille, mots_s mots[]){

int nbr = 0;
for(int i = 0; i < taille ; i++){

   if(strcmp(string,mots[i].mot) == 0 ){

       nbr = 1;
      break;

   }

}

return nbr;


}

/*

int nombreMot(char filename[]){


char leMot[30];
int leMotChar = 0;


        FILE * fp = fopen(filename, "r");
        if (fp == NULL){
        exit(12);
        }
	char c;
        int count = 0;
        while((c = fgetc(fp)) != EOF)
        {
                if(c == ' ' || c == '\n')
                {
                       printf("%s\n",leMot);
                       memset(leMot,'\0',sizeof(leMot));
                       leMotChar = 0;




                        printf("\n");
                        ++count;
                }
                else
                {
                       leMot[leMotChar] = c;
                       leMotChar++;
                }
        }
	fclose(fp);

return count;



}


*/











//verifier la langue retourne 1 : francais   2 : anglais   3 : allemand
int verifierLangue(char fichierMod[]){

    int langue = 0; // 1:francais      2:anglais   3:allemand

    for(int i = 0; i < strlen(fichierMod); i++){
        if(fichierMod[i] == '.'){

            if(i + 2 == strlen(fichierMod) - 1){
                if(fichierMod[i + 1] == 'f' && fichierMod[i + 2] == 'r'){
                    langue = 1;
                }else if (fichierMod[i + 1] == 'e' && fichierMod[i + 2] == 'n'){
                    langue = 2;
                }else if (fichierMod[i + 1] == 'd' && fichierMod[i + 2] == 'e'){
                    langue = 3;

                }
            }

	}
    }

    return langue;

}






// compte nombr e de fichier dans le dossier
int nombreFichierMod(char nomFichier[]){


        FILE * fp = fopen(nomFichier, "r");
        if (fp == NULL){
          exit(12);
        }
	char c;
        int count = 0;
        while((c = fgetc(fp)) != EOF)
        {
                if(c == ' ' || c == '\n')
                {
                        ++count;
                }
        }
	fclose(fp);
return count;

}











// prend le contenu de -l et l'aligne : un fichier par ligne et met dans un  fichier nomme listefichier.modele_koy
void alignerModele(char path[]){

char command[100];
char p1[] = "cd ";
char p2[] = "; ls -1 > ../listeFichiers.modeles_koy";

strcat(command,p1);
strcat(command,path);
strcat(command,p2);

system(command);
}














void valider(char *tab[],int taille){

   for(int i = 1; i < taille; i++){
      if(tab[i][0] == '-' && strcmp(tab[i-1],"-k") != 0){

       if(strcmp(tab[i],ARG_CODE_P) != 0 && strcmp(tab[i],ARG_ENCRYPT) != 0 && strcmp(tab[i],ARG_DECRYPT) != 0 && 
          strcmp(tab[i],ARG_CLE) != 0 &&  strcmp(tab[i],ARG_ENTREE) != 0 &&  strcmp(tab[i],ARG_SORTIE) != 0 && 
         strcmp(tab[i],ARG_FIC_ALPHA) != 0 && strcmp(tab[i],ARG_B) != 0 && strcmp(tab[i],ARG_BF) != 0 && strcmp(tab[i],ARG_MODELS) != 0  ){



           if(strcmp(tab[i-1],ARG_SORTIE) != 0 && strcmp(tab[i-1],ARG_ENTREE) != 0 &&
              strcmp(tab[i-1],ARG_FIC_ALPHA) != 0 ){

              printf("un argument present est invalide\n");
             exit(3);
           }

        }

      }

   }

}

int nbrSautLigne(char *tablo){
   int nombre = 0;

   for(int i = 0; i < strlen(tablo); i++){

     if(tablo[i] == '\n'){
     nombre++;
    }

   }


   return nombre;
}


//cryptage du texte
void cryptage(char *leTexte,char *alphabet,long lePas){

     int nombreSaut = nbrSautLigne(alphabet);
    long alphaLength = strlen(alphabet) - nombreSaut;


    long textLength = strlen(leTexte);

    if(lePas > alphaLength){
        lePas = lePas % alphaLength;
    }else if(lePas < 0 && (lePas * -1) > alphaLength){
        lePas = ((lePas * -1) % alphaLength) * -1;
    }



    for(int i = 0; i < textLength; i++){


      if(isalpha(leTexte[i])){

            for(int n = 0; n < alphaLength;n++){
                if(leTexte[i] == alphabet[n]){
                    if(n + lePas < alphaLength && n + lePas >= 0 ){
                        leTexte[i] =  alphabet[n + lePas];
                    }else{
                        if(lePas > 0){

                            long difference = (alphaLength) - n;
                            long cleDeborde = lePas - difference;
                            leTexte[i] = alphabet[cleDeborde];

                        }else if(lePas < 0){
                            long differenceNeg = (alphaLength) + n;
                            long cleDebordeNeg = lePas + differenceNeg;
                            leTexte[i] = alphabet[cleDebordeNeg];

                        }
                    }

                    break;
                }
            }

       }
    }




}




//lit le fichier entree et cree une varabile de la chaine avec pointeur
void lireFichier(char *pointeur, const char fichierEntree[],int taille,int erreur){

  FILE *fichierIn = NULL;
  char caractere;
  int indice = 0;
  fichierIn = fopen(fichierEntree,"r");

  if(fichierIn != NULL){
    do{


       caractere = fgetc(fichierIn);

       if(indice < taille && caractere != EOF){
       pointeur[indice] = caractere;
       indice++;

       }

   }while(caractere != EOF);
  fclose(fichierIn);

 }else{
   printf("Erreur de fichier");
   exit(erreur);
 }


}




int longueurFichier(const char fichierEntree[]){


  FILE *fichierIn = NULL;
  int caractere;
  int sizeFichierEntree = 0;
  fichierIn = fopen(fichierEntree,"r");

  if(fichierIn != NULL){
    do{

       caractere = fgetc(fichierIn);
       sizeFichierEntree++;

   }while(caractere != EOF);
  fclose(fichierIn);

 }
  return sizeFichierEntree;
}


//verifier les arguments des chemins des fichier
int verifierArgFichier(char *tab[],int tailleTab,char argument[]){
  int codeRetour = -1;
  int compteur = 0;

  for(int i = 1; i < tailleTab; i++){
     if(strcmp(argument,tab[i]) == 0){
        codeRetour = i;
        compteur++;
     }

  }

 if(compteur > 1){
   exit(12);
 }

  return codeRetour;

}




//fonction qui verifier si -e ou -d ou -b est present retourne 1  pour crypter et -1 pour decrypter et -5 pour bruteforce
int verfierArgCryptage(char *tab[],int tailleTab){
  int codeRetour = 0;
  int cryptage = 1;
  int decryptage = -1;
  int compt = 0;
  int retourBrutforce = -5;

  int comptBrut = 0;

  for(int i = 1; i < tailleTab; i++){
     if(strcmp(ARG_ENCRYPT,tab[i]) == 0){
       codeRetour = cryptage;
       compt++;
     }else if(strcmp(ARG_DECRYPT,tab[i]) == 0){
       codeRetour = decryptage;
      compt++;
     }else if(strcmp(ARG_B,tab[i]) == 0 || strcmp(ARG_BF,tab[i]) == 0){
      codeRetour = retourBrutforce;
      comptBrut++;
     }
  }

  if(codeRetour == 0){
    printf("argument -e ou -d ou -b n'est pas present\n");
    exit(4);
  }else if(compt > 1 || comptBrut > 1 || ( compt != 0 && comptBrut != 0)){
   exit (12);
 }

   return codeRetour;

}


//fonction qui verifie si un argument obligatoire  est present

int verifierArgPresent(char *tab[],int tailleTab,char argument[],int codeErreur){
  int codeRetour = -1;
  int compteur = 0;

  for(int i = 1; i < tailleTab; i++){
     if(strcmp(argument,tab[i]) == 0){
       codeRetour = i;
       compteur++;
     }
  }

  if(codeRetour ==  -1){
   exit(codeErreur);
  }else if(compteur > 1){
   exit(12);
  }


  return codeRetour;

}


//fonction qui verifie si un String a juste des chiffre ou non

void veriferChiffre(char *tab[],int indiceFixe){

  int n = 0;
  int taille = strlen(tab[indiceFixe]);

  if(tab[indiceFixe][0] == '-'){
    n = 1;
  }

  for(int i = n; i < taille; i++){
    char c = tab[indiceFixe][i];
    if(!isdigit(c)){
      printf("valeur de -k non conforme\n");
      exit(7);
    }
  }
}





int main(int argc,char * argv[]) {


  //indice d'ou se trouve les args dans le tableau
  int indiceCodeP;
  int indiceCryptage;
  int indiceNombreSaut;
  int indiceFichierEntree;
  int indiceFichierSortie;
  int indiceFichierAlpha;
  int indiceFichierModeles;

  long cle;
  char fichierEntree[100];
  char fichierSortie[100];
  char fichierAlpha[100];
  char fichierModeles[100];



  char  *pointeurEntree = NULL;
  char  *pointeurAlpha = NULL;


  if(argc == 1){
  printf("ERREUR 1.Vous devez entrer les arguments comme l'exemple ci dessous.\n");
  fprintf(stderr, "Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
    exit(1);
  }else{
   valider(argv,argc);
   indiceCodeP =  verifierArgPresent(argv,argc,ARG_CODE_P,1) + 1;
  }

   if(indiceCodeP < argc && strlen(argv[indiceCodeP]) != 12){
    printf("ERREUR 2.la valeur de -c doit etre de 12 caracteres\n");
     exit(2);
   }else if(indiceCodeP >= argc){
     exit(1);
   }





  indiceCryptage = verfierArgCryptage(argv,argc);


  if(indiceCryptage != -5){// -5 = bruteforce
     indiceNombreSaut  =  verifierArgPresent(argv,argc,ARG_CLE,7) + 1;

    //valider la cle et transformenr en string
     if(indiceNombreSaut >= argc){
       printf("ERREUR 7.largument de -k est invalide");
       exit(7);
     }else{
       veriferChiffre(argv,indiceNombreSaut);
       cle = strtol(argv[indiceNombreSaut],NULL,10);
       cle = cle * indiceCryptage;
     }
  }



//fichier en entree 
  indiceFichierEntree = verifierArgFichier(argv,argc,ARG_ENTREE) + 1;
  if(indiceFichierEntree != 0){
    if(indiceFichierEntree >= argc){
      printf("ERREUR 5.l'argument -i n'a pas de valeur\n");
      exit(5);
    }else{
      strcpy(fichierEntree,argv[indiceFichierEntree]);

     int sizeFichierEntree = longueurFichier(fichierEntree);

    pointeurEntree = (char*) malloc(sizeFichierEntree * sizeof(char));
   lireFichier(pointeurEntree,fichierEntree,sizeFichierEntree,5);

    }

  }else{

   pointeurEntree = (char*) malloc(1000 * sizeof(char));
   fgets(pointeurEntree,1000,stdin);

  }







//fichier alpha
  indiceFichierAlpha = verifierArgFichier(argv,argc,ARG_FIC_ALPHA) + 1;
  if(indiceFichierAlpha != 0){
    if(indiceFichierAlpha >= argc){
      printf("ERREUR 8.l'argument -a n'a pas de valeur\n");
      exit(8);
    }else{
      strcpy(fichierAlpha,argv[indiceFichierAlpha]);

      if(fichierAlpha[strlen(fichierAlpha)-1] == '/'){
       strcat(fichierAlpha,ALPHA);
      }else{
      strcat(fichierAlpha,ALPHA_SLASH);

      }


    }

  }else{
      strcpy(fichierAlpha,ALPHA);

  }
   int sizeFichierAlpha = longueurFichier(fichierAlpha);

   pointeurAlpha = (char*) malloc(sizeFichierAlpha * sizeof(char));
   lireFichier(pointeurAlpha,fichierAlpha,sizeFichierAlpha,8);




 if(indiceCryptage != -5){
    cryptage(pointeurEntree,pointeurAlpha,cle);
 }else{
  indiceFichierModeles = verifierArgFichier(argv,argc,ARG_MODELS) + 1;

  if(indiceFichierModeles == 0){
    exit(9);
  }

   strcpy(fichierModeles,argv[indiceFichierModeles]);


  alignerModele(fichierModeles);

  int nombreFichier = nombreFichierMod("listeFichiers.modeles_koy");


  mots_s *motFrancais = (mots_s*) malloc(3000 * sizeof(mots_s));
  mots_s *motAnglais = (mots_s*) malloc(3000 * sizeof(mots_s));
  mots_s *motAllemand = (mots_s*) malloc(3000 * sizeof(mots_s));
mots_s *modeles = (mots_s*) malloc(nombreFichier * sizeof(mots_s));
  int indiceFrancais = 0;
  int indiceAnglais = 0;
  int indiceAllemand = 0;
int nbrModele = 0;
  int langue = 0;
  int ficValide = 0; 




       char filename[] = "listeFichiers.modeles_koy";
       char barre[] = "/";





         FILE * fp = fopen(filename, "r");
        if (fp == NULL){
        exit (12);
        }
        char c[100];

         while((fgets(c,100,fp)) != NULL) {


c[strlen(c) -  1] = '\0';
 char pathLangue[1024];


           strcat(pathLangue,fichierModeles);
           strcat(pathLangue,barre);
           strcat(pathLangue,c);
strcpy(modeles[nbrModele].mot,pathLangue);
nbrModele++;


          memset(pathLangue,'\0',sizeof(pathLangue));
          langue = 0;
       }
	fclose(fp);



for(int i = 0; i < nbrModele; i++){



 langue = verifierLangue(modeles[i].mot);


char leMot[30];
int leMotChar = 0;



        FILE * fp3 = fopen(modeles[i].mot, "r");
        if (fp3 == NULL){
        exit(12);
        }
        char cara;
        int count = 0;
        while((cara = fgetc(fp3)) != EOF)
        {
                if(cara == ' ' || cara == '\n')
                {


                    if(langue == 1){
                    ficValide++;

                    strcpy(motFrancais[indiceFrancais].mot,leMot);

                    indiceFrancais++;


                    }else if(langue == 2){
                     ficValide++;

                    strcpy(motAnglais[indiceAnglais].mot,leMot);
                    indiceAnglais++;

                    }else if(langue == 3){
                     ficValide++;

                     strcpy(motAllemand[indiceAllemand].mot,leMot);
                     indiceAllemand++;
                    }




                       memset(leMot,'\0',sizeof(leMot));
                       leMotChar = 0;




                        ++count;
                }
                else
                {
                       leMot[leMotChar] = cara;
                       leMotChar++;
                }
        }
        fclose(fp);


}








double nbrMotsEntree = compteMot(pointeurEntree);
int cleBruteFra = 0;
int cleBruteAng = 0;
int cleBruteAll = 0;

int occFra = 0;
int occAng = 0;
int occAll = 0;

double compteFra = 0;
double compteAng = 0;
double compteAll = 0;

int debutAlpha = -1 * sizeFichierAlpha;

for(int i = debutAlpha; i <= sizeFichierAlpha; i++){
cryptage(pointeurEntree,pointeurAlpha,i);



    FILE *tempo = NULL;
    tempo = fopen("tempo.koy_x","w");
   if(tempo != NULL){
   fputs(pointeurEntree,tempo);
   fclose(tempo);

   }else{
   printf("ERREUR 6.erreur avec le fichier sortie");
   exit(12);
   }






char leMot[30];
int leMotChar = 0;


         FILE * fp = fopen("tempo.koy_x", "r");
        if (fp == NULL){
         exit(12);
        }
        char c;
        int count = 0;
        while((c = fgetc(fp)) != EOF)
        {
                if(c == ' ' || c == '\n')
                {

                occFra = 0;
                occAng = 0;
                occAll = 0;


                      occFra = occurrence(leMot, indiceFrancais, motFrancais);

                      if((occFra / nbrMotsEntree) >= 1){
                      cleBruteFra = i;
                      compteFra = 1;
                      break;
                      }

                      if((occFra / nbrMotsEntree) > compteFra){
                         cleBruteFra = i;
                         compteFra = (occFra / nbrMotsEntree);
                       }



                     occAng = occurrence(leMot, indiceAnglais, motAnglais);

                      if((occAng / nbrMotsEntree) >= 1){
                       cleBruteAng = i;
                      compteAng = 1;
                      break;
                      }


                      if((occAng / nbrMotsEntree) > compteAng){
                         cleBruteAng = i;
                         compteAng = (occAng / nbrMotsEntree);
                       }



                    occAll = occurrence(leMot, indiceAllemand, motAllemand);


                      if((occAll / nbrMotsEntree) >= 1){
                      cleBruteAll = i;
                      compteAll = 1;
                      break;
                      }

                       if((occAll / nbrMotsEntree) > compteAll){
                        cleBruteAll = i;
                         compteAll = (occAll / nbrMotsEntree);
                       }




                       memset(leMot,'\0',sizeof(leMot));
                       leMotChar = 0;




                        ++count;
                }
                else
                {
                       leMot[leMotChar] = c;
                       leMotChar++;
                }
        }
	fclose(fp);






cryptage(pointeurEntree,pointeurAlpha,( -1 * i));
}


if(compteFra > compteAng && compteFra > compteAll){
cryptage(pointeurEntree,pointeurAlpha, cleBruteFra);

}else if(compteAng > compteFra && compteAng > compteAll){
cryptage(pointeurEntree,pointeurAlpha,cleBruteAng);

}else{
cryptage(pointeurEntree,pointeurAlpha,cleBruteAll);

}




 }

















//fichier en sortie 
  indiceFichierSortie = verifierArgFichier(argv,argc,ARG_SORTIE) + 1;
  if(indiceFichierSortie != 0){
    if(indiceFichierSortie >= argc){
      printf("ERREUR 6.l'argument -o n'a pas de valeur\n");
      exit(6);
    }else{
      strcpy(fichierSortie,argv[indiceFichierSortie]);

    FILE *fichierOut = NULL;
    fichierOut = fopen(fichierSortie,"w");
   if(fichierOut != NULL){
   fputs(pointeurEntree,fichierOut);
   fclose(fichierOut);

   }else{
   printf("ERREUR 6.erreur avec le fichier sortie");
   exit(6);
   }

    }

  }else{
   fputs(pointeurEntree,stdout);

  }







//printf("\nFIN NORMALE DU PROGRAMME\n");


    return 0;
}
