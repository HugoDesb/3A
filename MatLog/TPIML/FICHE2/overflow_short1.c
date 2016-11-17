/*
-----------------------------------------------------------------
-- File name : overflow_short1.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  short smin=SHRT_MIN ;
  short smax=SHRT_MAX ;
  short sminMoinsUn = smin-1;
  short smaxPlusUn = smax+1 ;

  printf("Overflow : type short\n");
  printf("Plus petit short = %d\n",smin);
  printf("Plus petit short - 1 = %d\n", sminMoinsUn);
  printf("Plus grand short = %d\n",smax);
  printf("Plus grand short + 1  = %d\n", smaxPlusUn);
  return(0);
}

