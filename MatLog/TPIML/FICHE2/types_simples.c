/*
-----------------------------------------------------------------
-- File name : types_simples.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

int main(void)
{
	//prédire l'affichage
	printf("Types simples\n");
	printf("Taille d'un char : %zu\n", sizeof(char)); //1
	printf("Taille d'un int : %zu\n", sizeof(int));//4
	printf("Taille d'un short : %zu\n", sizeof(short));//2
	printf("Taille d'un long : %zu\n", sizeof(long));//8
	printf("Taille d'un long long : %zu\n", sizeof(long long));//8
	printf("Taille d'un float : %zu\n", sizeof(float));//4
	printf("Taille d'un double : %zu\n", sizeof(double));//8
	printf("Taille d'un pointeur sur char : %zu\n",sizeof(char *));//8
	printf("Taille d'un pointeur sur int : %zu\n",sizeof(int *));//8
	printf("Taille d'un pointeur sur double : %zu\n",sizeof(double *));//8
	printf("Taille d'un pointeur de type void * : %zu\n",sizeof(void *));//8
	return(0);
}
