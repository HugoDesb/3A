/*
-----------------------------------------------------------------
-- File name : overflow_int1.c
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
  int iminMoinsUn = imin-1;
  int imaxPlusUn = imax+1 ;
  int moinsImin = 0 - imin ;

  printf("Overflow : type int\n");
  printf("Plus petit int = %d\n",imin);
  printf("Plus petit int - 1 = %d\n", iminMoinsUn);
  printf("Plus grand int = %d\n",imax);
  printf("Plus grand int + 1  = %d\n", imaxPlusUn);
  printf("Opposé du plus petit int  = %d\n", moinsImin);
  return(0);
}

