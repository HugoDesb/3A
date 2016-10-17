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
 * @file exercice04a.c
 * 
 * Demande une valeur et renvoie son arrondi inférieur
 */

#include <stdio.h>
#include <math.h>

int main(void){

  float value;
  int roundedValue;

  //asking values for a & b
  printf("Type a value :\n");
  scanf("%f",&value);

  roundedValue = floor(value);
  printf("The closest inferior integer is %d€\n",roundedValue);
}
