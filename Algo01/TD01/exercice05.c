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
 * @file exercice05.c
 * 
 * Renvoie les solutions d'un polynôme du 2eme degré avec des 
 * coefficients entiers 
 */



#include <stdio.h>
#include <math.h>

int main(void){
  int a,b,c;
  int signed delta;

  //Demander les coeff
  printf("Type A :");
  scanf("%d",&a);

  printf("Type B :");
  scanf("%d",&b);

  printf("Type C :");
  scanf("%d",&c);

  if(a!=0){
    delta = b*b-4*a*c;
    printf("Delta : %d\n",delta);
    if(delta==0){
      float solution = -b/(2*a);
      printf("The solution is: %f",solution);
    }else if(delta>0){
      float solution1, solution2;
      solution1 = (-b + sqrt(delta))/(2*a);
      solution2 = (-b - sqrt(delta))/(2*a);
      printf("Solutions are : %f and %f",solution1,solution2);
    }else if(delta<0){
      float solutionReal,solutionImaginary;
      solutionReal = (-b)/(2*a);
      solutionImaginary = (sqrt(-delta))/(2*a);
      printf("There is two imaginary solutions : %f+i%f and %f-i%f",solutionReal,solutionImaginary,solutionReal,solutionImaginary);
    }
  }else{
    printf("ERROR: a=0, cannot divide by zero");
  }
  printf("\n");

}
