/*
-----------------------------------------------------------------
-- File name : types_construits_tableaux.c 
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

typedef char tc[10];
typedef short ts[10];
typedef int ti[10];

int main(void)
{
	ti i;
	tc c; 
	ts s; 
	
	printf("Type tableaux\n");
	printf("Taille d'un tableau de 10 char : %zu\n", sizeof(tc));
	printf("Taille d'un tableau de 10 short : %zu\n", sizeof(ts));
	printf("Taille d'un tableau de 10 int : %zu\n", sizeof(ti));
	printf("Taille d'une variable  tableau de 10 char : %zu\n", sizeof(c));
	printf("Taille d'une variable  tableau de 10 short : %zu\n", sizeof(s));
	printf("Taille d'une variable  tableau de 10 int : %zu\n", sizeof(i));
	printf("Taille de la chaine \"O123456789\" : %zu\n", sizeof("0123456789"));
	return(0);
}
