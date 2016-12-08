/*
-------------------------------------------------------------------
Nom du fichier : arbres.c
Auteur : 
Objet : Module implantant les arbres binaires de recherche 
        contenant des entiers. Les noeuds sont doublement chainees.
--------------------------------------------------------------------
*/
#include <stdio.h> //pour la constante NULL 

#include "arbres.h" //pour verification de la coherence et définition
                    // des types Arbre et Noeud
#include "memoire.h"
#include "interface.h"

/*
 Code des fonctions definies dans le module (entetes)
 - creer_arbre_vide, inserer, afficher_arbre_croissant,rechercher,
 afficher_min, supprime_min, ...
 */

Arbre creer_arbre_vide(void)
/* creer_arbre_vide : retourne l'arbre vide
*/
{
  return(NULL);
}


Arbre inserer(Arbre a, int x)
/* inserer :
insere l'entier x dans l'arbre binaire de recherche a et retourne
l'arbre resultat
*/
{
      Noeud * p;
      Noeud * q;
      Noeud * r;

      p = (Noeud *)my_malloc();
     if (p==NULL)
     {
          afficher_chaine("insertion impossible : memoire pleine\n");
          return(a);
     }   
     p->info = x ;
     p->fils_gauche = NULL ;
     p->fils_droit = NULL ;
     if (a == NULL)
     { 
          p->pere = NULL ;
          return(p);
     }
     
     q=a;
     do
     {
          r=q;
          if (x < q->info)
          {
              q=q->fils_gauche ;
          }
          else
          {
              q=q->fils_droit ;
          }
     }while(q!=NULL);
     p->pere = r ;
     if (x < r->info)
     {
         r->fils_gauche=p ;
     }
     else
     {
         r->fils_droit=p ;
     }
     
     return(a);
     
}


void afficher_arbre_croissant(Arbre a)
/* afficher_arbre_croissant : affiche les elements de l'arbre a 
   dans l'ordre croissant 
*/
{
     if (a!= NULL)
     {
        afficher_arbre_croissant(a->fils_gauche);
        afficher_chaine(" ");
        afficher_entier(a->info);
        afficher_arbre_croissant(a->fils_droit);
     }
}

int rechercher(Arbre a, int x)
/* rechercher : retourne 1 si x est dans l'arbre a, 0 sinon
*/
{
     if (a == NULL) return(0) ;
     if (a->info == x) return(1) ;
     if (a->info > x) 
     {
         return(rechercher(a->fils_gauche, x));
     }
     else
     {
         return(rechercher(a->fils_droit, x));
     }
}

void afficher_min(Arbre a)
/* afficher_min :
  Affiche la valeur minimale dans l'arbre a 
*/
{
      Noeud *p = a;
      
      if (a==NULL)
      { 
          printf("\nArbre vide!\n");
      }
      else
      { 
          while(p->fils_gauche != NULL)
          {
               p=p->fils_gauche ;
          }
          afficher_chaine("\n");
          afficher_entier(p->info);
          afficher_chaine("\n");
      }
}

Arbre supprimer_min(Arbre a)
/* supprimer_min :
  Supprime de l'arbre a un element ayant une valeur minimale et retourne
  l'arbre resultat
*/
{
      Noeud *p = a;
      
      if (a==NULL)
      { 
          printf("\nArbre vide!\n");
          return(NULL);
      }
      while(p->fils_gauche != NULL)
      {
           p=p->fils_gauche ;
      }
      if (p->fils_droit != NULL)
      {
          p->fils_droit->pere=p->pere ;
         if (p != a)
         {
              p->pere->fils_gauche = p->fils_droit ;
         }
         else
         {
              a = a->fils_droit ;
         }
      }
      else // p n'a pas de fils droit
      {
             if (p == a) a=NULL ;
             else p->pere->fils_gauche=NULL ;
      }
      my_free(p);
      return(a);
}

/*--------------------fin arbres.c---------------------------*/

