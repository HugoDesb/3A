/*
-----------------------------------------------------------------
-- File name : overflow_int2.c 
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  int imin=INT_MIN ;
  int imax=INT_MAX ;

  printf("Overflow : type int \n");
  printf("Plus petit int = %d\n",imin);
  printf("Plus petit int - 1 = %d\n", imin-1);
  printf("Plus grand int = %d\n",imax);
  printf("Plus grand int + 1  = %d\n", imax+1);
  printf("Opposé du plus petit int = %d\n", 0-imin);
  return(0);
}

