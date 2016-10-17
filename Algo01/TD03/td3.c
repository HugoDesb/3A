/* 
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille.
 * Il ne peut etre reproduit, utilise ou modifie sans l'avis
 * express de ses auteurs.
 */

/* @author GOBERT Esteban <esteban.gobert@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 23/09/2012
 * @todo ----------
 * @bug ----------
 */

/* @td3.c
*
* 
*
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define N 10
#define NA 10  //Taille du tableau A
#define NB 7  //Taille du tableau B
#define NC NA+NB  //Taille du tableau C
#define NL 3
#define NCO 3

int exo1(int A[], int B[]);
void exo2(int T[], int *val, int *rang);
int exo3(int T[], int X);
void exo4(int *T);
void exo5();
void exo6(int T[], int X);
void exo7();
void exo8();


int main(void) {
	int A[N]={1,2,4,8,9,7,5,4,3,2};
	int B[N]={1,3,4,5,5,5,5,4,8,2};
	int Z[N]={0,4,5,0,0,1,6,0,2,9};

	printf("Exercice 1\nResultat : %d\n\n",exo1(A,B));

	int T[N]={5,4,7,8,9,3,9,3,5,4}, val, rang, i, X;

	exo2(T, &val, &rang);
	printf("Exercice 2\nLa plus petite valeur :%d\nrang : %d\n\n",val,rang);

	X = 9;
	printf("Exercice 3\nrang le plus petit ou X = %d: %d\n\n",X,exo3(T,X));

	printf("Exercice 4\nTab avant tassement = ");
	for(i=0;i<N;i++) {printf("%d ",Z[i]);}
	exo4(Z);
	
	int TA[NA] = {0,5,7,8,10,11,14,17,18,19};
	int TB[NB] = {1,6,9,13,15,16,20};
	int TC[NC];
	printf("Exercice 5:\nTab A = ");
	for(i=0;i<NA;i++) {printf("%d ",TA[i]);}
	printf("\nTab B = ");
	for(i=0;i<NB;i++) {printf("%d ",TB[i]);}
	printf("\nTab C trie = ");
	exo5(TA,TB,TC);
	for(i=0;i<NC;i++) {printf("%d ",TC[i]);}
	printf("\n\n");

	X = 11;
	int T6[N] = {0,2,5,7,8,10,12,15,19,20};
	printf("Exercice 6:\nTab = ");
	for(i=0;i<N;i++) {printf("%d ",T6[i]);}
	printf("\nIndice choisi : %d\n", X);
	exo6(T6,X);

	printf("Exercice 7:\n");
	exo7();

	printf("Exercice 8:\n");
	exo8();

	return 0;
}

int exo1(int A[], int B[]) {
	int i, cpt = 0;

	for (i=0;i<N;i++)
	{
		if (A[i] == B[i]) {
			cpt ++;
		}
	}
	return cpt;
}

void exo2(int T[], int *val, int *rang){
	assert(N!=0);
	int i, valmin = T[0], rangmin;

	for(i=1;i<N;i++){
		if (T[i] <= valmin){
			valmin = T[i];
			rangmin = i;
		}
	}
	*val = valmin;
	*rang = rangmin;
}

int exo3(int T[], int X){
	int trouve = 0, i = 0;
	while(!trouve && i<N) {
		trouve = (T[i] == X);
		i++;
	}

	if (trouve) return(i-1);
	else return(-1);
}

void exo4(int T[]) {
	int i,j;

	/* On se place a la premiere occurrence nul du tableau */
	i=0;
	while(i<N && T[i]!=0){
		i++;
	}

	j=i;

	for(i++;i<N;i++){
		if(T[i]!=0){ // Si la valeur actuelle n'est pas nul on la reecrit
			T[j]=T[i];
			j++;
		}
	}

	printf("\nTab apres tassement = ");
	for(i=0;i<j;i++){ // j represente le nombre d'element non nul du tableau initial
		printf("%d ",T[i]);
	}
	printf("\n\n");
}

void exo5(int A[], int B[], int *C) {
	int i=0,j=0,k=0;  //Les indices respectivements des tableaux A, B et C
	

	/* Boucle sur les tableaux A et B simultanement */

	while(i<NA && j<NB){
		if(A[i]<B[j]){
			C[k]=A[i];  // On recopie la valeur de A dans C et on incrémente i
			k++;
			i++;
		}else{
			C[k]=B[j];  // On recopie la valeur de B dans C et on incrémente j
			k++;
			j++;
		}
	}
	
	/* On rentre les valeurs restantes dans tableau si l'autre est vide */

	while(i<NA){
		C[k]=A[i];
		k++;
		i++;
	}
	
	while(j<NB){
		C[k]=B[j];
		k++;
		j++;
	}

}

void exo6(int T[], int X) {
	int i=0; // Borne inférieure de recherche
	int j=N-1;  // Borne supérieure de recherche
	int m;  // Milieu de l'intervalle

	/* Test si l'élément est hors du tableau */
	
	if(X<T[0] || X>T[N-1]){
		printf("L'élément est hors du tableau\n");
	}else{
	
	/* On procède par dichotomie */
	
		do{
			m=(i+j)/2;
			if(X<T[m]){
				j=m;
			}else{
				i=m;
			}
		}while(X!=T[m] && j!=i+1); // Tant qu'on a pas trouvé X
		
		/* On affiche le résultat */
		
		if(X==T[m]){
			printf("La valeur appartient au tableau et est en position %i\n",m);
		}else{
			printf("La valeur n'appartient pas au tableau est devrait etre placer en position %i\n",j);
		}
	}
}

void exo7() {
	int p,q; // Le couple d'indices
	int A[NL][NCO]={{10,7,7},{8,7,9},{1,5,6}};  // La matrice
	int Imin[NCO];  // Imin[] contient les minimuns de la ligne courante 
	int min,nbMin,maxC,i,j;
	
	// Programme

	/* Boucle sur les lignes */
	
	for(p=0;p<NL;p=p+1){
		min=A[p][0];
		Imin[0]=0;
		nbMin=1;
				
		/* Boucle sur les colonnes */
		
		for(q=1;q<NCO;q=q+1){
			if(A[p][q]<min){
				Imin[0]=q;  	// On recupere la colonne du min
				min=A[p][q];	// Ainsi que sa valeur
				nbMin=1;
			}else if(A[p][q]==min){
				Imin[nbMin]=q;
				nbMin++;
			}
		}
		
		/* On cherche si le minimun trouvé est un maximun de la ligne */
		
		maxC = min; // Le minimun de la ligne est un max de la colonne ? */
		for(j=0;j<nbMin;j=j+1){
			q=Imin[j];
			i=0;
			while(i<NL && A[i][q]<=maxC){ // On parcoure les lignes
				i++;
			}
			if(i==NL){ // Si on a parcouru les lignes sans trouver d'autre max
				printf("Le couple (%i, %i) est un min-max\n",p,q);
			}
		}
	}
}

void exo8() {
	int n,T[N],i,j;
	int milieu; // Le milieu de la ligne
	int x,y; // Les entiers nécessaires au calcul de la nouvelle ligne
	
	/* On récupere n */	
	
	printf("Rentrer une valeur inférieure ou égale à %i\n",N);
	scanf("%i",&n);
	
	/* Boucle sur la ligne du triangle */
	
	T[0]=1;
	T[1]=1;
	for(i=3;i<=n;i++){
		milieu=(i+1)/2;
		x=T[0];
		y=T[1];
		
		/* Boucle sur les colonne du triangle */
		
		for(j=1;j<milieu;j++){
			T[j]=x+y;
			x=y;
			y=T[j+1];
		}
		
		/* Boucle sur la 2eme partie de la ligne */
		
		if(i%2==1){  // Ligne impaire
			for(j=1;j<milieu;j++){
				T[milieu-1+j]=T[milieu-1-j];
			}
		}else{
			milieu=i/2;
			for(j=0;j<milieu;j++){
				T[milieu+j]=T[milieu-1-j];
			}
		}
	}
	
	printf("La %ième ligne du triangle de Pascal est :\n",n);
	for(i=0;i<n;i++){
		printf("%i ",T[i]);
	}
	printf("\n");
}