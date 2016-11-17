/*
-----------------------------------------------------------------
-- File name : overflow_U_int.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  unsigned int u_imin= 0 ;
  unsigned int u_imax=UINT_MAX ;
  unsigned int u_iminMoinsUn = u_imin-1;
  int u_imaxPlusUn = u_imax+1 ;

  printf("Overflow : type unsigned int\n");
  printf("Plus petit int = %u\n",u_imin);
  printf("Plus petit int - 1 = %u\n", u_iminMoinsUn);
  printf("Plus grand int = %u\n",u_imax);
  printf("Plus grand int + 1  = %u\n", u_imaxPlusUn);
  return(0);
}

