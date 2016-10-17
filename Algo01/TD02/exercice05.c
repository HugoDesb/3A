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
 * @file exercice05.c
 * 
 * Fonction qui compte les apparitions de nombres entre 0 et 20 (inclus)
 */

#include <stdio.h>

#define N 21

int main(void){

	int value,count,i, tab[N] = {0};

	
	count = 0;
	do{
		printf("Entrez une valeur : ");
		scanf("%d",&value);

		if(value>=0 && value<N){
			tab[value] = tab[value]+1;

			for(i = 0; i<N;i++){
				printf("%d : %d apparitions\n",i,tab[i]);
			}
		} 
	}
	while(count<N && value>=0);

	
}
