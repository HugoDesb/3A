/*
-----------------------------------------------------------------
-- File name : precision_float.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2 
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

int main(void)
{
  float f ;
  float g ;
  float h ;

  printf("Le type float : precision \n");
  printf(" Entrez un nombre float : ");
  scanf ("%f", &f);
  g = f+1 ;
  h= f-1 ;
  printf(" f= %f  , f+1 =%f , f-1 = %f \n ", f, g, h);
  printf(" f= %e  , f+1 =%e , f-1 = %e\n ", f, g, h);
  printf(" f= %a  , f+1 =%a , f-1 = %a\n ", f, g, h);
  printf(" f= %X  , f+1 =%X , f-1 = %X\n ", *((int *)&f), *((int *)&g), *((int *)&h));
  return(0);
}
