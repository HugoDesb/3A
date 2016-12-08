/*
-------------------------------------------------------------------
Nom du fichier : memoire.c
Auteur :
Objet : Module implantant les fonctions d'allocation et de liberation
        de la memoire  
--------------------------------------------------------------------
*/
#include <stdlib.h>
#include "arbres.h" 
#include "memoire.h" //pour verification de la coherence


/*
Code des fonctions definies dans le module (entetes dans memoire.h):
 - init_mem, my_malloc et my_free

Pour simplifier on alloue la memoire par blocs de taille fixe (la taille
d'un noeud). Les blocs libres sont stockees dans une pile.
*/

#define MAX 400 // nombre maximum de blocs

static Noeud memoire[MAX] ; // On reserve MAX blocs
static Arbre blocs_libres ; // Sommet de la pile des blocs libres

/* init_mem : Initialise les structures de donnees utilisees pour gerer
              l'allocation et la liberation de la memoire 
              On met tous les blocs libre sur une pile. 
*/

void init_mem(void)
{
   int i ;
   
   i=0 ;
   do 
   {
       memoire[i].pere = (Noeud *)(&memoire[i+1]);
       i=i+1;
   } while (i<MAX-1);
   memoire[MAX-1].pere = NULL ; 
   blocs_libres = memoire ;

}
/* my_malloc : alloue un bloc de taille TAILLE_NOEUD (fixe: cf arbres.h) et 
               retourne l'adresse du bloc (retourne NULL si allocation 
               impossible)
*/
void *my_malloc(void)
{  
   Arbre p;

   p =  blocs_libres ;
   if (p!=NULL)
   {
       blocs_libres = blocs_libres->pere ;
   } 
   return((void *)p);
}

/* my_free : libere le bloc passe en parametre.
     ajoute le bloc au sommet de la pile des blocs
     libres
*/
void my_free(void *bloc)
{
   ((Arbre)bloc)->pere = blocs_libres ;
   blocs_libres = (Arbre)bloc ;
}
/*----------------fin memoire.c--------------------------------------*/

