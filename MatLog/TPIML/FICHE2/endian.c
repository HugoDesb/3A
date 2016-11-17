/*
-----------------------------------------------------------------
-- File name : endian.c 
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

int main(void)
{
  int mot = 0x12345678;
  char *c = (char *)&mot;

  int i;
 
  printf("Little Endian ou Big Endian ? \n");
  printf("mot = %X\n", mot); 
  printf("Affiché octet par octet :  ");
  for (i=0; i<4; i++)
  { printf("%2X",c[i]);
  }
  printf("\n"); 
  return(0);
}
