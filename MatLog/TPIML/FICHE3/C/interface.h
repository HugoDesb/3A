/*
-------------------------------------------------------------------
Nom du fichier : interface.h
Objet: Entete du module implantant les fonctions de saisie et d'affichage
--------------------------------------------------------------------
*/
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/* lire_entier : Lit un entier a la console et retourne sa valeur 
*/
int lire_entier(void);

/* afficher_entier : affiche a la console l'entier passe en parametre 
*/
void afficher_entier(int x);

/* afficher_chaine : affiche a la console la chaine passee en parametre 
*/
void afficher_chaine(char *s);
#endif
/*-----------------fin interface.h-----------------------------------*/
