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
 * File for all exercices of the third TP
 */

#include <stdio.h>

#define N1 5
#define N2 10
#define NL 4
#define NC 4

int exe1(void);
int exe21(void);
int exe22(void);
int exe3(void);
int exe4(void);
int exe5(void);
int exe6(void);
int findByDichotomy(int tab[], int x, int size);
int exe7(void);
int exe8(void);

int main(void){
	/* exe1(); */
	/* exe21(); */
	/* exe22(); */
	/* exe3(); */
	/* exe4(); */
	/* exe5(); */
	/* exe6(); */
	exe7();

	
	return 0;
}

/**
 *
 *
 */
int exe1(void){
	int tabA[N1] = {1,2,0,4,5};
       	int tabB[N1] = {1,0,3,0,5};
	int count = 0;
	int i;
	for(i=0;i<N1;i++){
         	if(tabA[i]==tabB[i]){
	                count++;
                }
	}
	printf("Numbers of ids : %d \n", count);
	return 0;
}



int exe21(void){
	int tab[N1] = {10,2,10,2,3};
	int min = tab[0];
	int i;
	for(i=0;i<N1;i++){
		if(min>tab[i]){
			min = tab[i];
		}
	}
       	printf("Minimum : %d \n", min);
	return 0;
}

int exe22(void){

	int tab[N1] = {10,2,10,2,3};
	int min = tab[0];
	int i,rangMin=0;
	for(i=0;i<N1;i++){
		if(min>tab[i]){
			min = tab[i];
			rangMin = i;
		}
	}
	printf("Rang du minimum : %d \n", rangMin);
	return 0;
}
  

int exe3(void){
	int trouve = 0,i=0,x=9;
	int T[N2] = {1,2,3,4,5,6,7,8,9,0};
	while(!trouve && i<N2){
		trouve = (T[i]==x);
		i++;
	}
	if(trouve){
		printf("Le rang trouve est %d\n",i-1);
	}else{
		printf("Aucun rang n'a été trouvé\n");
	}
	return 0;
}



int exe4(void){
	int i,count=0;
	int tab[N2] = {1,2,0,4,0,6,7,8,9,0};

	for(i=0;i<N2;i++){
	
		if(tab[i]>0 && count>0){
			//si ma valeur>0 et 1 zero a été passé, je décale
			//le nb vers la gauche du nombre de zéros passés
			tab[i-count]=tab[i];
			tab[i] = 0;
		}else if(tab[i]==0){
			//j'incremente le nb de zéros passés
			count++;
		}		
	}


	//Affichage du tableau sans les zéros de la fin
	i=0;
	while(tab[i]>0){
		printf("%d ", tab[i]);
		i++;
	}

	return 0;
}

int exe5(void){
	int A[N1] = {1,2,7,8,12};
	int B[N1] = {5,9,11,17,18};
	int C[N2];

	int i,j,rangA=0,rangB=0;

	for(i=0;i<N2;i++){
		if(rangB<N1 && rangA<N1){
			if(A[rangA]>B[rangB]){
					C[i] = B[rangB];
					rangB++;
				}else if(A[rangA]<B[rangB]){
				C[i] = A[rangA];
				rangA++;
			}
		}else if(rangB>=N1){
			for(j=rangA;j<N1;j++){
				C[i] = A[j];
			}
		}else if(rangA >= N1){
			for(j=rangB;j<N1;j++){
				C[i] = B[j];
				i++;
			}
		}else{
			printf("ranga:%d et rangB:%d",rangA,rangB);
		}
	
	}
	for(i=0;i<N2;i++){
		printf("%d ",C[i]);
	}
	printf("\n");
	return 0;
	
}

int exe6(void){
	int tab[N2] = {1,2,5,8,9,14,16,17,21,23};
	int x = 0;
	int rank = findByDichotomy(tab, x, N2);
	printf("Rank found :%d",rank);


	return 0;
}
/**
 * Récursive function to find a member : 
 * - if size ==1, returns whether the element must be added after or before
 * - else, determines which part of the array to choose.
 */
int findByDichotomy(int tab[], int x, int size){
	int mid = size/2;
	
	if(size ==1){
		if(x>tab[0]){
			return 1;
		}else{
			return 0;
		}
	}else{
		if(tab[mid]==x){
			return mid;
		}else if(tab[mid]>x){
			return findByDichotomy(tab, x, mid);
		}else{
			return mid + findByDichotomy(&tab[mid], x, size-mid);
		}
	}
}


int exe7(void){
	typedef struct tuples{
		int val;
		int l;
		int c;
	} tuple;
	
	int A[NL][NC] ={{1,0,0,0},{6,5,6,7},{2,6,5,6},{3,9,1,0}};
	int p,q;
	tuple minL[NL],maxC[NC];
	int min,minRank;
	int max,maxRank;
	tuple t;

	for(p=0;p<NL;p++){
		min = A[p][0];
		for(q=0;q<NC;q++){
			if(A[p][q]<=min){
				min = A[p][q];
				minRank = q;

			}
		}
		t.val = min;
		t.l = p;
		t.c = minRank;
		minL[p] = t;
	}

	for(q=0;q<NC;q++){
		max = A[0][q];
		for(p=0;p<NL;p++){
			if(A[p][q]>=max){
				max = A[p][q];
				maxRank = p;
			}
		}
		
		t.val = max;
		t.l = maxRank;
		t.c = q;
		maxC[q] = t;
	}	
	
	for(p=0;p<NL;p++){
		for(q=0;q<NC;q++){
			if(minL[p].l == maxC[q].l && minL[p].c == maxC[q].c){
				printf("(%d,%d)=%d\n",minL[p].l,minL[p].c,minL[p].val);
			}
		}
	}
	printf("tous les couples ont été affichés\n");
	return 0;
}
