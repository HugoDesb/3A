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
 * @file exercice02c.c
 *
 * Affiche les valeurs de sin(x) pour x allant 
 * de D a F par pas de P.
 * P = pas, entré par User
 * D,F = angles de départ et arrivée, entrés par User
 */

#include <stdio.h>
#include <math.h>

int main(void){
	float radian = acos(-1)/180;
	int i,step, startAngle, endAngle;

	printf("Entrez le pas : ");
	scanf("%d",&step);
	printf("Entrez l'angle de départ : ");
	scanf("%d",&startAngle);
	printf("Entrez l'angle d'arrivée : ");
	scanf("%d",&endAngle);

	for( i = startAngle;i<=endAngle;i=i+step){
		printf("sin(%d) = %f\n",i,sin(i*radian));
	}
	scanf("%d", &value);

}
