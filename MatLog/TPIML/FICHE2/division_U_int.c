/*
-----------------------------------------------------------------
-- File name : division_U_int.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2 
-- 
----------------------------------------------------------------
*/

#include <stdio.h>
#include <limits.h>

int main(void)
{
  unsigned int x ;
  unsigned int y ;

  printf ("Test division entiere\n");
  printf ("Entrez deux nombres entiers positifs: \n");
  scanf("%u",&x);
  scanf("%u",&y);
  printf("%u / %u = %u\n", x, y, x/y);
  printf("%u Modulo %u = %u\n", x, y, x%y);
  return(0);
}

