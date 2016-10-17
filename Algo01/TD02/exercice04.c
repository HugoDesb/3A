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
 * @file exercice04.c
 * 
 * Fonction qui accepte des valeurs et les imprime
 * dans l'ordre inverse dans lesquelles elles ont
 * étés rentrées.
 */

#include <stdio.h>

#define N 10

int main(void){
	float tab[N],value ;
	int count,i;

	count = 0;
	do{
		printf("Entrez une valeur : ");
		scanf("%f",&value);

		if(value>=0){
			tab[count++]= value;	
		} 
	}
	while(count<N && value>=0);

	for(i = count-1; i>=0;i--){
		printf("%f\n",tab[i]);
	}
}
