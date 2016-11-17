/*
-----------------------------------------------------------------
-- File name : overflow_char3.c 
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  char cmin=CHAR_MIN ;
  char cmax=CHAR_MAX ;

  printf("Overflow : type char\n");
  printf("Plus petit char = %hhd\n",cmin);
  printf("Plus petit char - 1 = %hhd\n", cmin-1);
  printf("Plus grand char = %hhd\n",cmax);
  printf("Plus grand char + 1  = %hhd\n", cmax+1);
  return(0);
}

