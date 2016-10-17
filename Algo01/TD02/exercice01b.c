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
 * @file exercice01b.c
 * 
 * Fonction qui répète l'opération tva tant que le prix>=0
 * puis affiche la somme.
 */

#include <stdio.h>

const float TX_TVA = 0.2;


int main(void){
	const float TVA = 1 + TX_TVA;
	float value ,sum = 0;
	int count = 0;
	do{
		printf("Entrez une valeur :");
		scanf("%f",&value);
		
		if(value!=0){
			 value = value * TVA;
			 printf("Le prix TTC est : %f€\n",value);
			 sum += value;
			 count ++;
		}
	}while(value!=0);

	printf("La somme des opérations est %f et le nombre d'opérations est %d",sum, count);
}
