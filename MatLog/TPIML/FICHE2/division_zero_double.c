/*
-----------------------------------------------------------------
-- File name : division_zero_double.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/

#include <stdio.h>
#include <limits.h>

int main(void)
{
  double x ;
  double y = 0.0;

  printf ("Test division d'un double par zero\n");
  printf("Entrez un double : ");
  scanf("%lf",&x);
  printf("%lf / 0 = %lf\n", x, x/y);
  printf ("Fin du programme division_zero_double\n");
  return(0);
}

