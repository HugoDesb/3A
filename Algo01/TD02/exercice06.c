/** 
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr>
 */


/**
 * @file exercice06.c
 * 
 * Fonction qui affiche des couples de valeurs.
 */

#include <stdio.h>


int main(void){

	int x,y,p=3,q=5;

	for(x=1;x<=p;x++){
		for(y=1;y<=q;y++){
			printf("(%d, %d) ",x,y);
		}
		printf("\n");
	}
}
