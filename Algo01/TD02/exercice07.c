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
 * @file exercice07.c
 * 
 * Fonction qui affiche un triangle 
 * de je-sai-pas-quoi-si-ça-se-trouve-ça-a-même-pas-de-nom.
 */

#include <stdio.h>
#define N 30

int main(void){
	int i,j,k,l;
	
	for(i=1;i<=N ;i++){
		for(j=1;j<=N-i;j++){
			printf("-");
		}
		k = (2*i)-1;
		for(j=i;j<=k;j++){
			printf("%d",j%10);
		}
		for(j=j-2;j>=i;j--){
			printf("%d",j%10);
		}
		for(j=i+1;j<=N;j++){
			printf("-");
		}
		printf("\n");
	}

}
