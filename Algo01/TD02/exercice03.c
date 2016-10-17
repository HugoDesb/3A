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
 * @file exercice03.c
 * 
 * Fonction qui accepte des valeurs en entrée et renvoie
 * et renvoie leur moyenne et le nombre de valeurs rentrées
 */

#include <stdio.h>

int main(void){
	float value, sum = 0;
	int count=0;
	do{
		printf("Entrez un nombre :");
		scanf("%f",&value);
		if(value>=0){
			sum += value;
			count++;
			printf("La somme est %f en %d itérations",sum,count);
		}
	}while(value>=0);
}
