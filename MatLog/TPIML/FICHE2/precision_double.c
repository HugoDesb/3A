/*
-----------------------------------------------------------------
-- File name : precision_double.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

int main(void)
{
  double f ;
  double g ;
  double h ;

  printf("Type double : précision \n");
  printf("Entrer un double : ");
  scanf ("%lf", &f);
  g = f+1 ;
  h= f-1 ;
  printf(" f= %lf  , f+1 =%lf , f-1 = %lf \n ", f, g, h);
  printf(" f= %e  , f+1 =%e , f-1 = %e \n ", f, g, h);
  printf(" f= %a  , f+1 =%a , f-1 = %a \n ", f, g, h);
  return(0);
}
