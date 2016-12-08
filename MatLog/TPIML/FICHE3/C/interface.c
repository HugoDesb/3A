/*
-------------------------------------------------------------------
Nom du fichier : interface.c
Objet : Module implantant les fonctions de saisie et d'affichage
        On utilise un module a part pour la traduction en langage
        d'assemblage  
--------------------------------------------------------------------
*/
#include <stdio.h> // pour les fonctions printf et scanf
#include "interface.h" //pour verification de la coherence

/* lire_entier : Lit un entier a la console et retourne sa valeur 
*/
int lire_entier(void)
{  int x;
   if (scanf("%d",&x) ==0) x=0;
   return(x);
}

/* afficher_entier : affiche a la console l'entier passe en parametre 
*/
void afficher_entier(int x)
{
  printf("%d", x);
}

/* afficher_chaine : affiche a la console la chaine passee en parametre 
*/
void afficher_chaine(char *s)
{
  printf("%s", s);
}

/*-----------------fin interface.c-----------------------------------*/

