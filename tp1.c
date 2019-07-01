#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ARG_CODE_P  "-c"
#define ARG_ENCRYPT "-e"
#define ARG_DECRYPT "-d"
#define ARG_CLE "-k"

#define ARG_ENTREE "-i"
#define ARG_SORTIE "-o"
#define ARG_FIC_ALPHA "-a"
#define ALPHA "alphabet.txt"
#define ALPHA_SLASH "/alphabet.txt"

void valider(char *tab[],int taille){

   for(int i = 1; i < taille; i++){
      if(tab[i][0] == '-' && strcmp(tab[i-1],"-k") != 0){

       if(strcmp(tab[i],ARG_CODE_P) != 0 && strcmp(tab[i],ARG_ENCRYPT) != 0 && strcmp(tab[i],ARG_DECRYPT) != 0 && 
          strcmp(tab[i],ARG_CLE) != 0 &&  strcmp(tab[i],ARG_ENTREE) != 0 &&  strcmp(tab[i],ARG_SORTIE) != 0 && 
         strcmp(tab[i],ARG_FIC_ALPHA) != 0 ){



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

printf("\n");

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


int verifierArgFichier(char *tab[],int tailleTab,char argument[]){
  int codeRetour = -1;


  for(int i = 1; i < tailleTab; i++){
     if(strcmp(argument,tab[i]) == 0){
        codeRetour = i;
     }

  }

  return codeRetour;

}




//fonction qui verifier si -e ou -d est present retourne 1  pour crypter et -1 pour decrypter
int verfierArgCryptage(char *tab[],int tailleTab){
  int codeRetour = 0;
  int cryptage = 1;
  int decryptage = -1;

  for(int i = 1; i < tailleTab; i++){
     if(strcmp(ARG_ENCRYPT,tab[i]) == 0){
       codeRetour = cryptage;
     }else if(strcmp(ARG_DECRYPT,tab[i]) == 0){
       codeRetour = decryptage;
     }
  }

  if(codeRetour == 0){
    printf("argument -e ou -d n'est pas present\n");
    exit(4);
  }

   return codeRetour;

}


//fonction qui verifie si un argument obligatoire  est present

int verifierArgPresent(char *tab[],int tailleTab,char argument[],int codeErreur){
  int codeRetour = -1;

  for(int i = 1; i < tailleTab; i++){
     if(strcmp(argument,tab[i]) == 0){
       codeRetour = i;
     }
  }

  if(codeRetour ==  -1){
   exit(codeErreur);
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

  long cle;
  char fichierEntree[100];
  char fichierSortie[100];
  char fichierAlpha[100];



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
    printf("Veillez entrer le texte pour le cryptage/decryptage :  ");
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



cryptage(pointeurEntree,pointeurAlpha,cle);



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







printf("\nFIN NORMALE DU PROGRAMME\n");


    return 0;
}
