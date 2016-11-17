/*
-----------------------------------------------------------------
-- File name :  types_construits_union.c
-- Objet :  TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

typedef struct 
      {
          int num ;
          union{
          char nom[10];
          int val;
          } id ;
      } t_union ;

int main(void)
{
     t_union x ;
     t_union y ;

     printf("Type union\n");
     printf("Taille d'un element de type  t_union : %zu\n", sizeof(t_union));
     printf("adresse de x : %p\n", &x);
     printf("adresse de x.num : %p\n", &x.num);
     printf("adresse de x.id.nom : %p\n", &x.id.nom);
     printf("adresse de x.id.val : %p\n", &x.id.val);
     printf("adresse de y : %p\n", &y);
     printf("adresse de y.num : %p\n", &y.num);
     printf("adresse de y.id.nom : %p\n", &y.id.nom);
     printf("adresse de y.id.val : %p\n", &y.id.val);
     return(0);
}
