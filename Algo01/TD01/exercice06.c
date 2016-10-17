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
 * 
 */

#include <stdio.h>

int main(void){
  int j,m,a;
  int daysInMonth [12] = {31,28,31,30,31,30,31,31,30,31,30,31};

  //  getDate
  printf("day :");
  scanf("%d",&j);

  printf("month :");
  scanf("%d",&m);

  printf("year :");
  scanf("%d",&a);

  //qd l'annee est bissextile
  if((a%4==0 && a%100!=0)|| a%400==0){
    daysInMonth[2] = 29;
  }
  j++;

  //si nouveau du mois
  if(j>daysInMonth[m-1]){
    j=1;
    m++;
    //si nouvelle année
    if(m>12){
      m=1;
      a++;
    }
  }

  
  
  printf("La date du lendemain est :%d/%d/%d\n",j,m,a);


  //reinitialisation
  daysInMonth[2] = 28;
}
