/*
-----------------------------------------------------------------
-- File name : overflow_long.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  long limin=LONG_MIN ;
  long limax=LONG_MAX ;
  long liminMoinsUn = limin-1;
  long limaxPlusUn = limax+1 ;

  printf("Overflow : type long \n");
  printf("Plus petit long = %ld\n",limin);
  printf("Plus petit long - 1 = %ld\n", liminMoinsUn);
  printf("Plus grand long = %ld\n",limax);
  printf("Plus grand long + 1  = %ld\n", limaxPlusUn);
  return(0);
}

