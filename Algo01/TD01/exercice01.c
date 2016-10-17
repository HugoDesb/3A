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
 * @file exercice01.c
 * 
 * Fonction qui prend en paramètre une valeur flottante et renvoie 
 * cette valeur plus la TVA
 */

#include <stdio.h>

const float TX_TVA = 0.2;

int main(void){
  float value, tva;
  tva = 1+TX_TVA;
  printf("Entrez une valeur :");
  scanf("%f",&value);

  value = value *tva;
  
  printf("Le prix TTC est : %f€\n",value);
}
