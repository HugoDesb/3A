*/** 
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
 * @file exercice03a.c
 * 
 * Fonction qui affiche la différence entre les moyennes arithmétiques
 * et géométriques
 */

#include <stdio.h>
#include <math.h>

int main(void){
  int a,b;
  float arithmeticMean, geometricMean,difference;

  //a, b arbitrary numbers
  a = 30;
  b = 26;

  arithmeticMean = (a+b)/2.;
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
