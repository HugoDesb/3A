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
 * @file exercice.c
 * 
 * File for all exercices of the fourth TP
 */

#include <stdio.h>

#define N1 5
#define N2 10
#define NL 4
#define NC 4

// Prototypes
void exe1(void);
long int fibo(int n);
void exe2(void);
float expo(float x, int n);
int exe3(void);
int pgcd(int a, int b);
int exe4(void);


// Main
int main(void){
	//exe1(); 
	exe2();
	/* exe3(); */
	/* exe4(); */
	return 0;
}

// Functions
void exe1(void){
	int n;
	printf("Entrez un n >=0 :\n");
	scanf("%d",&n);
	printf("La valeur de fibo(%d) est : %li\n",n,fibo(n));
}
long int fibo(int n){
	if(n==0 || n==1){
		return 1;
	}else{
		return fibo(n-1)+fibo(n-2);
	}
}


void exe2(void){
	int n;
	float x;
	printf("Entrez un flottant :\n");
	scanf("%f",&x);
	printf("Entrez une puissance entière :\n");
	scanf("%d",&n);
	printf("La valeur de %f^%d est : %f\n",x,n,expo(x,n));
}

float expo(float x, int n){
	if(n==0){
		return 1;
	}else if(n%2==0){
		return expo(x,n/2)*expo(x,n/2);
	}else{
		return x*expo(x,n-1);
	}
}

int exe3(void){

	return 0;
}

int pgcd(int a, int b){
	
}


int exe4(void){
	return 0;
}
