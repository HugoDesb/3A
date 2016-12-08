#/*
#-------------------------------------------------------------------
#Nom du fichier : arbres.s
#Auteur : 
#Objet : Module implantant les arbres binaires de recherche 
#        contenant des entiers. Les noeuds sont doublement chainees.
#--------------------------------------------------------------------
#*/
##include <stdio.h> //pour la constante NULL 
#
##include "arbres.h" //pour verification de la coherence et définition
#                    // des types Arbre et Noeud
# arbres.h définit les types Noeud et Arbre. 
# Un élément de type Noeud sera represente'
# dans une zone 16 octets (4 pour le champ info,
# 4 pour le champ fils_gauche,  4 pour le champ fils_droit, 
# et 4 pour le champ pere).
#  Le champ info est a un deplacement 0 par rapport
# au debut de cette zone, le champ fils_gauche a un deplacement de 4,
# le champ fils_droit a un deplacement de 8,
# et le champ pere a un deplacement de 12.
# Un Arbre est un pointeur sur un Noeud. Un élément de type Arbre
# occupe 4 octets en mémoire ou dans un registre.

##include "memoire.h"
# memoire.h ne contient que des prototypes de fonctions.
##include "interface.h"
# interface.h ne contient que des prototypes de fonctions.
#
#/*
# Code des fonctions definies dans le module (entetes)
# - creer_arbre_vide, inserer, afficher_arbre_croissant,rechercher,
# afficher_min, supprime_min, ...
# */
#
#Arbre creer_arbre_vide(void)
        .text
	.globl creer_arbre_vide
creer_arbre_vide:
#/* creer_arbre_vide : retourne l'arbre vide
#*/
#{
#  return(NULL);
	move $v0, $0
	# retour a l'appelant
	jr $ra
#}
#
#
#Arbre inserer(Arbre a, int x)
	.globl inserer
# parametres : a dans $a0, x dans $a1
# resultat dans $v0
#/* inserer :
#insere l'entier x dans l'arbre binaire de recherche a et retourne
#l'arbre resultat
#*/
inserer:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS

#{
#      Noeud * p;
#      Noeud * q;
#      Noeud * r;
#
#      p = (Noeud *)my_malloc();
#     if (p==NULL)
#     {
#          afficher_chaine("insertion impossible : memoire pleine\n");
#          return(a);
#     }   
#     p->info = x ;
#     p->fils_gauche = NULL ;
#     p->fils_droit = NULL ;
#     if (a == NULL)
#     { 
#          p->pere = NULL ;
#          return(p);
#     }
#     
#     q=a;
#     do
#     {
#          r=q;
#          if (x < q->info)
#          {
#              q=q->fils_gauche ;
#          }
#          else
#          {
#              q=q->fils_droit ;
#          }
#     }while(q!=NULL);
#     p->pere = r ;
#     if (x < r->info)
#     {
#         r->fils_gauche=p ;
#     }
#     else
#     {
#         r->fils_droit=p ;
#     }
#     
#     return(a);
#     
#}
#
#
#void afficher_arbre_croissant(Arbre a)
# parametre a dans $a0
#/* 
#/* afficher_arbre_croissant : affiche les elements de l'arbre a dans
#   l'ordre #croissant 
#*/
	.globl afficher_arbre_croissant
afficher_arbre_croissant:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#{
#     if (a!= NULL)
#     {
#        afficher_arbre_croissant(a->fils_gauche);
#        afficher_chaine(" ");
#        afficher_entier(a->info);
#        afficher_arbre_croissant(a->fils_droit);
#     }
#}
#
#int rechercher(Arbre a, int x)
# parametres : a dans $a0, x dans $a1
# resultat dans $v0
#/* rechercher : retourne 1 si x est dans l'arbre a, 0 sinon
#*/
	.globl rechercher
rechercher:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#{
#     if (a == NULL) return(0) ;
#     if (a->info == x) return(1) ;
#     if (a->info > x) 
#     {
#         return(rechercher(a->fils_gauche, x));
#     }
#     else
#     {
#         return(rechercher(a->fils_droit, x));
#     }
#}
#
#void afficher_min(Arbre a)
# parametre a dans $a0
#/* 
#/* afficher_min :
#  Affiche la valeur minimale dans l'arbre a 
#*/
	.globl afficher_min
afficher_min:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS

#{
#      Noeud *p = a;
#      
#      if (a==NULL)
#      { 
#          printf("\nArbre vide!\n");
#      }
#      else
#      { 
#          while(p->fils_gauche != NULL)
#          {
#               p=p->fils_gauche ;
#          }
#          afficher_chaine("\n");
#          afficher_entier(p->info);
#          afficher_chaine("\n");
#      }
#}
#
#Arbre supprimer_min(Arbre a)
# parametre a dans $a0
# resultat dans $v0
#/* 
#/* supprimer_min :
#  Supprime de l'arbre a un element ayant une valeur minimale et retourne
#  l'arbre resultat
#*/
	.globl supprimer_min
supprimer_min:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#{
#      Noeud *p = a;
#      
#      if (a==NULL)
#      { 
#          printf("\nArbre vide!\n");
#          return(NULL);
#      }
#      while(p->fils_gauche != NULL)
#      {
#           p=p->fils_gauche ;
#      }
#      if (p->fils_droit != NULL)
#      {
#          p->fils_droit->pere=p->pere ;
#         if (p != a)
#         {
#              p->pere->fils_gauche = p->fils_droit ;
#         }
#         else
#         {
#              a = a->fils_droit ;
#         }
#      }
#      else // p n'a pas de fils droit
#      {
#             if (p == a) a=NULL ;
#             else p->pere->fils_gauche=NULL ;
#      }
#      my_free(p);
#      return(a);
#}
#
#/*--------------------fin arbres.s---------------------------*/
#
