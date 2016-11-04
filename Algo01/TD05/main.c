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
 * File for all exercices of the fifth TP
 */

#include <stdio.h>

#define N1 5

int f(int x);
void ff(int x, int *res);
int fibo(int x);
void ffibo(int x, int *res);
int binomial( int p , int n);
int pair(int x);
int impair(int x);
int collatz(int x);
int collatz2(int x);
int ackermann(int m, int n, int p);

int main(void){
	int n,p,resultat;

	
	printf("Facto recur :");
	n = 4;
	printf("!%d = %d\n",n,f(n));

	printf("Facto pointer :");
	n = 4;
	ff(n,&resultat);
	printf("!%d = %d\n",n,resultat);

	printf("Fibo recur :");
	n = 5;
	printf("fibo(%d) = %d\n",n,fibo(n));


	printf("Fibo pointer :");
  n = 5;
	ffibo(n,&resultat);
	printf("fibo(%d) = %d\n",n,resultat);

	printf("binomial :");
	p = 5;
	n = 7;
	printf("(%d %d) = %d\n",p,n,binomial(p,n));

	n = 4;
	p = 5;
	printf("%d est impair ? Réponse : %d\n",n,impair(n));
	printf("%d est pair ? Réponse : %d\n",n,pair(n));
	printf("%d est impair ? Réponse : %d\n",p,impair(p));
	printf("%d est pair ? Réponse : %d\n",p, pair(p));


	n = 27;
	/* printf("Collatz(%d)=%d",n,collatz(n)); */
	// erreur de segmentation car cette suite est
	// infinie (retourne 4,2,1 indéfiniement)
	/* collatz2(n); */

	printf("Ackermann(2,3,0) = %d\n",ackermann(2, 3, 0));
	printf("Ackermann(2,3,1) = %d\n",ackermann(2, 3, 1));
	printf("Ackermann(2,3,2) = %d\n",ackermann(2, 3, 2));
	printf("Ackermann(3,3,0) = %d\n",ackermann(3, 3, 0));
	printf("Ackermann(3,3,1) = %d\n",ackermann(3, 3, 1));
	printf("Ackermann(3,3,2) = %d\n",ackermann(3, 3, 2));

	
	return 0;
}

int f(int x){
	if(x==1){
		return 1;
	}else{
		return x*f(x-1);
	}
}

void ff(int x, int *res){
	if(x==1){
		*res=1;
	}else{
		ff(x-1,res);
		*res = x*(*res);
	}
}


int fibo(int x){
	if(x==0){
		return 0;
	}else if(x==1){
		return 1;
	}else{
		return fibo(x-1)+fibo(x-2);
	}
}
void ffibo(int x, int *res){
	int temp;
	if(x==0 || x==1){
		*res=x;
	}else{
		ffibo(x-1,res);
		ffibo(x-2,&temp);
		*res = temp + *res;
	}
}
int binomial( int p , int n){
	if((p==0) || (n == p)){
		return 1;
	}else{
		return binomial(p-1, n-1)+binomial(p, n-1);
	}
}
int pair(int x){
	if(x==0){
		return 1;
	}else{
		return impair(x-1);
	}
}
int impair(int x){
	if(x==0){
		return 0;
	}else{
		return pair(x-1);
	}
}
int collatz(int x){
	if(x==1){
		return 0;
	}else if(x%2){
		return collatz(x/2);
	}else{
		return collatz(3*x +1);
	}
}
int collatz2(int x){
	printf(" %d ,",x);
	if(x==1){
		return 0;
	}else if(x%2==0){
		return collatz2(x/2);
	}else{
		return collatz2(3*x +1);
	}
}
int ackermann(int m, int n, int p){
	if(p==0){
		return m+n;
	}else if(n==0){
		if(p==1){
			return 0;
		}else if(p==2){
			return 1;
		}else{
			return m;
		}
	}else{
		return ackermann(m, ackermann(m, n-1,p), p-1);
	}
}
