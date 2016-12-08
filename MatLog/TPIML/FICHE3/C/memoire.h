/*
-------------------------------------------------------------------
Nom du fichier : memoire.h
Auteur :
Objet :  entete du module memoire 
--------------------------------------------------------------------
*/

#ifndef _MEMOIRE_H_
#define _MEMOIRE_H_

/* init_mem : Initialise les structures de donnees utilisees pour gerer
              l'allocation et la liberation de la memoire 
              SANS OBJET si on utilise malloc et free du systeme
*/
void init_mem(void);

/* my_malloc : alloue un bloc de taille TAILLE_NOEUD (fixe : cf listes.h) 
               et  retourne l'adresse du bloc (retourne 0 si allocation 
               impossible)
*/
void *my_malloc(void);

/* my_free : libere le bloc passe en parametre.
*/
void my_free(void *bloc);
#endif
/*----------------fin memoire.h--------------------------------------*/

