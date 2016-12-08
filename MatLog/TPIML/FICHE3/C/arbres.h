/*
-------------------------------------------------------------------
Nom du fichier : arbres.h
Auteur :
Objet : entete du module implantant les arbres binaires de recherche 
        contenant des entiers. Les noeuds sont doublement chainees.
--------------------------------------------------------------------
*/

#ifndef _ARBRES_H_ 
#define _ARBRES_H_

/*
Definitions des types
Representation des arbres binaires de recherche 
 avec 1 lien sur le père dans chaque noeud
*/
typedef struct maillon{
        int info;
        struct maillon *fils_gauche ;
        struct maillon *fils_droit ;
        struct maillon *pere ;
}Noeud, *Arbre ;

//La macro TAILLE_NOEUD est Utilisé seulement dans 
//les commentaires
#define TAILLE_NOEUD (sizeof(Noeud))

/*
declaration des fonctions definies dans le module (entetes)
 - creer_arbre_vide, inserer, afficher_arbre_croissant,rechercher,
   afficher_min, supprime_min, ...
*/

/* creer_arbre_vide : retourne l'arbre vide
*/
Arbre creer_arbre_vide(void);

/* inserer :
insere l'entier x dans l'arbre binaire de recherche a et retourne
l'arbre resultat
*/
Arbre inserer(Arbre a, int x);

/* afficher_arbre_croissant : affiche les elements de l'arbre a 
   dans l'ordre croissant 
*/
void afficher_arbre_croissant(Arbre a);

/* rechercher : retourne 1 si x est dans l'arbre a, 0 sinon
*/
int rechercher(Arbre a, int x);

/* afficher_min :
  Affiche la valeur minimale dans l'arbre a 
*/
void afficher_min(Arbre a);

/* supprimer_min :
  Supprime de l'arbre a un element ayant une valeur minimale et retourne
  l'arbre resultat
*/
Arbre supprimer_min(Arbre a);

/*---------------------- fin arbres.h ---------------------------*/

#endif

