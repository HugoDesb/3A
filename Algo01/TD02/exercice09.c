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
 * @file exercice08.c
 * Fonction qui calcule le plus petit n tel que 100*(n^2)<2^n
 */

#include <stdio.h>
#include <math.h>


int main(void){
	int n=0,cont=1;
	
	while(cont){
		n++;
		if(100*pow(n,2) < pow(2,n)){
			cont = 0;
		}
	}

	printf("La plus petite valeur de n tel que 100*(n^2)<2^n est : %d\n",n);

	return 0;
}
