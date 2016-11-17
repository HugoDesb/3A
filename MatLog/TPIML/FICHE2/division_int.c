/*
-----------------------------------------------------------------
-- File name : division_int.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/

#include <stdio.h>
#include <limits.h>

int main(void)
{
  int x ;
  int y ;

  printf ("Test division entiere\n");
  printf ("Entrez deux nombres entiers : \n");
  scanf("%d",&x);
  scanf("%d",&y);
  printf("%d / %d = %d\n", x, y, x/y);
  printf("%d Modulo %d = %d\n", x, y, x%y);
  return(0);
}

