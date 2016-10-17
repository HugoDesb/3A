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
 *
 * @version 0.0.1 / 20-09-2012
 */


/**
 * @file exercice03b.c
 * 
 * Fonction qui affiche la différence entre les moyennes arithmétiques
 * et géométriques
 */

#include <stdio.h>
#include <math.h>

int main(void){

  float a,b,arithmeticMean, geometricMean,difference;

  //asking values for a & b
  printf("Type a :\n");
  scanf("%f",&a);

  printf("Type b :\n");
  scanf("%f",&b);

  arithmeticMean = (a+b)/2;
  printf("A :%f",arithmeticMean);
  geometricMean = a*b;

  //avoid sqrt of negative number
  if(geometricMean>=0){
    geometricMean = sqrt(geometricMean);
    difference = arithmeticMean - geometricMean;
    printf("The difference is : %f",difference);
  }else{
    printf("There was an error, one of the numbers is negative");
  }

  printf("\n");
}
