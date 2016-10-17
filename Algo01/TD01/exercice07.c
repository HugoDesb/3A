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
 * @file exercice06.c
 * 
 */

#include <stdio.h>

int main(void){
  int sum,i,timesBill;
  int billsValue [9] = {500,200,100,50,20,10,5,2,1}; 
  
  printf("Type the value you want decomposed\n");
  scanf("%d",&sum);

  i=0;
  printf("%d =",sum);
  while(sum!=0){
    //nombre de billets a utiliser pour la valeur du billet courant 
    timesBill = sum/billsValue[i];
    if(timesBill != 0){
      //reste a décomposer
      sum = sum % billsValue[i];
      printf(" %d x %d",timesBill,billsValue[i]);
      //si la sum est encore décomposable
      if(sum!=0){
        printf(" +");
      }
    }
    i++;
  }

  printf("\n");

  
  
}
