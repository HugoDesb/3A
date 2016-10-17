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
 * @file exercice02.c
 * 
 * Fonction qui prend en paramètre une valeur flottante TTC et imprime
 * la TVA et le prix HT
 */

#include <stdio.h>

const float TX_TVA = 0.2;

int main(void){
  float valueTTC, tva, valueTVA, valueHT;
  tva = 1+TX_TVA;

  //Lecture de la valeur
  printf("Tapez le prix TTC :");
  scanf("%f",&valueTTC);

  //calcul de la valeur HT puis TVA
  valueHT = valueTTC / tva;
  valueTVA = valueTTC - valueHT;
  
  
  printf("Le prix HT est : %f€ plus %f€ de TVA\n",valueHT, valueTVA);
}
