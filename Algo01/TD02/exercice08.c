/** 
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr>
 */


/**
 * @file exercice08.c
 * Fonction qui affiche un tableau et permet de
 * mettre a jour les données de ce dernier.
 */

#include <stdio.h>

#define LINES 4
#define COLS 5

int main(void){
	int i,j,k;
	float x,sum,tab[LINES][COLS] = {0};

	do{
		printf("Choisissez i :");
		scanf("%d",&i);

		printf("Choisissez j :");
		scanf("%d",&j);

		printf("Choisissez x :");
		scanf("%f",&x);

		if(x>=0 && i< LINES-1 && j< COLS-1){
			tab[i][j] = x;

			//compute sum on the col
			sum = 0;
			for(k=0; k<LINES-1;k++){
				sum += tab[k][j];
			}
			tab[LINES-1][j] = sum;

			//compute sum on the line 
			sum = 0;
			for(k=0;k<COLS-1;k++){
				sum += tab[i][k];
			}
			tab[i][COLS-1] = sum;


			//Calcul de la somme finale
			sum=0;
			for(k=0; k<LINES-1;k++){
				sum += tab[k][COLS-1];
			}
			tab[LINES-1][COLS-1] = sum;



			//display tab
			for(i=0;i<LINES;i++){
				if(i == LINES-1){
					printf("------------------------------------------\n");
				}
				
				for(j=0;j<COLS-1;j++){
					printf(" %2.1f |",tab[i][j]);
				}
				printf("| %2.1f\n",tab[i][COLS-1]);
			}
		}
	}while(x>=0);
	
		


}
