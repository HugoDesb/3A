/*
-----------------------------------------------------------------
-- File name : overflow_char4.c  
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
  char cminMoinsUn = cmin-1;
  char cmaxPlusUn = cmax+1 ;
  
  printf("Overflow : type char \n");
  printf("Plus petit char = %c\n",cmin);
  printf("Plus petit char - 1 = %c\n", cminMoinsUn);
  printf("Plus grand char = %c\n",cmax);
  printf("Plus grand char + 1  = %c\n", cmaxPlusUn);
  return(0);
}

