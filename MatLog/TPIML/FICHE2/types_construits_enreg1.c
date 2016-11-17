/*
-----------------------------------------------------------------
-- File name :  types_construits_enreg1.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

typedef struct 
      {
          int num ;
          char nom[10];
          int val ;
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
     printf("adresse de x.val : %p\n", &x.val);
     printf("Taille de x.val : %zu\n", sizeof(x.val));
     printf("adresse de y : %p\n", &y);
     printf("adresse de y.num : %p\n", &y.num);
     printf("adresse de y.nom : %p\n", &y.nom);
     printf("adresse de y.val : %p\n", &y.val);
     return(0);
}
