/*
-------------------------------------------------------------------
Nom du fichier : main.c
Auteur :
Objet : Module principale 
--------------------------------------------------------------------
*/

#include <stdio.h>
#include "arbres.h"
#include "interface.h"
#include "memoire.h"

/*
cette fonction affiche un menu qui donne les commandes disponibles
pour effectuer les operations sur les arbres  
*/
static void menu(void)
{
	afficher_chaine("\n------------------Menu-----------------\n");
	afficher_chaine(" 1 : Creer un arbre vide \n");
	afficher_chaine(" 2 : Inserer un nouvel element \n");
	afficher_chaine(" 3 : Afficher l'arbre dans l'ordre croissant \n");
	afficher_chaine(" 4 : Rechercher un element\n");
	afficher_chaine(" 5 : Afficher la valeur minimale \n");
	afficher_chaine(" 6 : Supprimer un element ayant la valeur minimal \n");
	afficher_chaine(" 0 : Quitter \n");
	afficher_chaine("\n");
	afficher_chaine("choix : \n");
}

int main(void)
{
    int choix ;
    int nb ;
    
    Arbre mon_arbre ;
    
    // initialisation des structures de donnees utilisees pour la
    // gestion de la memoire.
    init_mem(); 
    
    mon_arbre = creer_arbre_vide() ; 
    menu();    
    choix = lire_entier() ;
    while (choix != 0)
    {
        switch(choix)
        {
            case 1 : 
                   mon_arbre = creer_arbre_vide() ; 
                   break;
            case 2 : 
                   afficher_chaine("nombre a inserer ? ");
                   nb = lire_entier();
                   mon_arbre = inserer(mon_arbre, nb);
                   break ;

            case 3 : 
                   if (mon_arbre !=NULL)
                        afficher_arbre_croissant(mon_arbre);
                   else
                        afficher_chaine(" arbre vide! \n");
                   break ;
            case 4 : 
                   afficher_chaine("nombre a rechercher ? ");
                   nb = lire_entier();
                   if(rechercher(mon_arbre, nb) !=0)
                        afficher_chaine (" present!\n");
                   else 
                        afficher_chaine(" absent!\n");
                   break; 
           
            case 5 : 
                   afficher_min(mon_arbre);
                   break ;
           
            case 6: 
                   mon_arbre = supprimer_min(mon_arbre); 
                   break ;
            
         }
         menu();
         choix = lire_entier() ;
    }

return(0);
}
/*------------------------fin main.c------------------------------*/
