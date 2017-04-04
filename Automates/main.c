
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[]);
int isText(char c);
int isTitle(int rank);
int isAuthor(int rank);
int isTitleOrAuthor();
int scanner();
void append(void);


FILE *source;
FILE *target = NULL;
char c;
enum TokenType {MOTCLE, SECTION, SSECTION, LIGNEVIDE, MOT, FIN} tokenType;
char tokenValue[50];
char title[4] = "itre";
char author[5] = "uteur";




int main(int argc, char const *argv[]){
  int i,scan=1;
  // Ouvre le fichier test.txt en lecture seulement (le fichier doit exister) :
  source = fopen("test.txt", "r");
  // Cree et ouvre un fichier tmp.html en lecture/ecriture,
  // avec suppression du contenu au prealable :
  target = fopen("target.html", "w+");

  if (source == NULL) {
    printf("Impossible d'ouvrir le fichier source\n");
    return -1;
  }
  
  if (target == NULL) {
    printf("Impossible d'ouvrir le fichier target\n");
    return -1;
  }
  
  c = fgetc(source); // lecture du caractere suivant du fichier source
  while(tokenType!=FIN && scan) { // tant que la fin du fichier n'est pas atteinte
    
    scan = scanner();
    printf("TokenType : %i ||\tTokenValue : %s\n", tokenType,tokenValue);
    //remise a zéro
    for(i = 0;i<50;i++){
      tokenValue[i] = 0; 
    }
  }
  
  if (source != NULL) {fclose(source);} // fermeture du fichier source
  if (target != NULL) {fclose(target);} // fermeture du fichier target

  return 0;
}


int scanner(){

qI :
  if(c=='\t'){c = fgetc(source);goto qI;}
  if(c==' '){c = fgetc(source);goto qI;}
  if(c=='\n'){goto qI_qL1;}
  if(c=='>'){goto qMC1;}
  if(c=='+'){goto qS;}
  if(c==EOF){goto qF1;}
  if(isText(c)){append();goto qM;}
  return 0;
  
qI_qL1:
  c = fgetc(source);
  if(c=='\t'){goto qI_qL1;}
  if(c==' '){goto qI_qL1;}
  if(c=='\n'){goto qI_qL1_qL2;}
  if(c=='>'){goto qMC1;}
  if(c=='+'){goto qS;}
  if(c==EOF){goto qF1;}
  if(isText(c)){append();goto qM;}
  return 0;

qI_qL1_qL2:
  c = fgetc(source);
  if(c=='\t'){goto qI_qL1_qL2;}
  if(c==' '){goto qI_qL1_qL2;}
  if(c=='\n'){goto qI_qL1_qL2;}
  if(c=='>'){goto qLF;}
  if(c=='+'){goto qLF;}
  if(c==EOF){goto qF1;}
  if(isText(c)){append();goto qLF;}
  return 0;

qMC1:
  c = fgetc(source);
  if(isTitleOrAuthor(c)){goto qMC2;}
  return 0;

qS:
  c = fgetc(source);
  if(c=='\t'){goto qSF;}
  if(c==' '){goto qSF;}
  if(c=='\n'){goto qSF;}
  if(c=='+'){goto qSS;}
  if(c==EOF){goto qSF;}
  return 0;

qM:
  c = fgetc(source);
  if(c=='\t'){goto qMF;}
  if(c==' '){goto qMF;}
  if(c=='\n'){goto qMF;}
  if(c==EOF){goto qMF;}
  if(isText(c)){append();goto qM;}
  return 0;

qMC2:
  c = fgetc(source);
  if(c=='\t'){goto qMCF;}
  if(c==' '){goto qMCF;}
  if(c=='\n'){goto qMCF;}
  if(c==EOF){goto qMCF;}
  return 0;
  
qSS:
  c = fgetc(source);
  if(c=='\t'){goto qSSF;}
  if(c==' '){goto qSSF;}
  if(c=='\n'){goto qSSF;}
  if(c==EOF){goto qSSF;}
  return 0;


 qMCF:
  tokenType = MOTCLE;
  return 1;
 qSF:
 tokenType = SECTION;
  return 1;
 qSSF:
 tokenType = SSECTION;
  return 1;
 qLF:
 tokenType = LIGNEVIDE;
  return 1;
 qMF:
 tokenType = MOT;
  return 1;
 qF1:
 tokenType = FIN;
  return 1;
}



/*------------------------------------------------------------------*/
/*                            ANALYSEURS                            */
/*------------------------------------------------------------------*/
int analyseurSyntaxique(){
  scanner();
  return analyseurAxiome();
}

int analyseurAxiome(){
  analyseurHead();
  scanner();
  analyseurBody();
  if(tokenType == FIN){
    printf("Analyse Axiome FIN\n");
    return 1;
  }else{
    printf("Analyse Axiome ERREUR\n");
    return 0;
  }
}

int analyseurHead(){
  if(tokenType == MOTCLE){
    scanner();
    analyseurText();
    if(tokenType==MOTCLE){
      scanner();  
      return analyseurText();
      
    }else{
      printf("Analyse Head ERREUR\n");
      return 0;
    }
  }else{
    printf("Analyse Head ERREUR\n");
    return 0;
  }
}
int analyseurBody(){
  return 0; 
}
int analyseurText(){
  return 0;
}



/*------------------------------------------------------------------*/
/*                              TOOLS                               */
/*------------------------------------------------------------------*/
int isText(char c){
  return (c>='a' && c<='z')
    || (c>='A' && c<='Z')
    || (c>='0' && c<='9')
    || (c=='.')
    || (c=='?')
    || (c=='!')
    || (c==',')
    || (c==';')
    || (c==':');
}

int isTitle(int rank){
  if(c==title[rank]){
    rank+=1;
    if(rank == 4){
      return 1;
    }else{
      c = fgetc(source);
      return isTitle(rank);
    }
  }else{
    return 0;
  }
}
int isAuthor(int rank){
  if(c==author[rank]){
    rank+=1;
    if(rank==5){
      return 1;
    }else{
      c = fgetc(source);
      return isAuthor(rank);
    }
  }else{
    return 0;
  }
}

int isTitleOrAuthor(){
  if(c=='t' ){
    c = fgetc(source);
    return isTitle(0);
  }
  if(c=='a'){
    c = fgetc(source);
    return isAuthor(0);
  }
  return 0;
}

void append(void){
  tokenValue[strlen(tokenValue)] = c;
}

