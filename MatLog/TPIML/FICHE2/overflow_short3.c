/*
-----------------------------------------------------------------
-- File name : overflow_short3.c
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
  
  printf("Overflow : type short\n");
  printf("Plus petit short = %hd\n",smin);
  printf("Plus petit short - 1 = %hd\n", smin-1);
  printf("Plus grand short = %hd\n",smax);
  printf("Plus grand short + 1  = %hd\n", smax+1);
  return(0);
}

