/*
-----------------------------------------------------------------
-- File name :  types_construits_enreg2.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

typedef struct 
      {
          int num ;
          char nom[13];
          char val1 ;
          int val2 ;
      } t_enreg ;

t_enreg x ;
t_enreg y ;
int main(void)
{
      
     printf("Type enregistrement (struct) \n");
     printf("adresse de x : %p\n", &x);
     printf("Taille d'un element de type  t_enreg : %zu\n", sizeof(t_enreg));
     printf("adresse de x.num : %p\n", &x.num);
     printf("Taille de x.num : %zu\n", sizeof(x.num));
     printf("adresse de x.nom : %p\n", &x.nom);
     printf("Taille de x.nom : %zu\n", sizeof(x.nom));
     printf("adresse de x.val1 : %p\n", &x.val1);
     printf("Taille de x.val1 : %zu\n", sizeof(x.val1));
     printf("adresse de x.val2 : %p\n", &x.val2);
     printf("Taille de x.val2 : %zu\n", sizeof(x.val2));
     printf("adresse de y : %p\n", &y);
     printf("adresse de y.num : %p\n", &y.num);
     printf("adresse de y.nom : %p\n", &y.nom);
     printf("adresse de y.val1 : %p\n", &y.val1);
     return(0);
}
