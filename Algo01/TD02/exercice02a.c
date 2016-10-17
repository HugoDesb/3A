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
 * @file exercice02a.c
 * 
 * Affiche les valeurs de sin(x) pour x allant 
 * de 0 a 90 par pas de 15.
 */

#include <stdio.h>
#include <math.h>

int main(void){
	float radian = acos(-1)/180;
	int i;
	for( i = 0;i<=90;i=i+15){
		printf("sin(%d) = %f\n",i,sin(i*radian));
	}
}
