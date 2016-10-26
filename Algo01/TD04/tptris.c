#include <stdio.h>
#include <stdlib.h>

#define TAILLE 15
#define VALMAX 20

#define ECHANGE 1
#define INSERTION 2
#define SHELL 3
#define BUBBLE0 4
#define BUBBLE1 5
#define SHAKER 6
#define QUICKSORT 7
#define MERGESORT 8

/* -------------------------------------------- */

void remplir ( int T[] , int n ) ;
void display ( int T[] , int n ) ;
int choisir ( void ) ;
void swap(int T[], int indexFirst, int indexSecond);

void tri_echange ( int T[] , int n ) ;
void tri_insertion ( int T[] , int n ) ;
void tri_shell ( int T[] , int n , int h0 ) ;
void tri_bubble ( int T[] , int n ) ;
void tri_bubble_opt ( int T[] , int n ) ;
void tri_shaker ( int T[] , int n ) ;
void tri_quick ( int T[] , int n ) ;
void tri_merge ( int T[] , int n ) ;

int main ( void ) ;

/* -------------------------------------------- */

void remplir ( int T[] , int n )
     {int i ;
      for ( i = 0 ; i < n ; i++ )
          T[ i ] = rand() % VALMAX ;
     }

void display ( int T[] , int n )
     {int i ;
      (void)printf( "( " ) ;
      for ( i = 0 ; i < n - 1 ; i++ )
          (void)printf( "%d , " , T[i] ) ;
      (void)printf( "%d )\n" , T[ n - 1 ] ) ;
     }

int choisir ( void )
    {int reponse ;
     do {(void)printf( "Choix : \n%d - Echange / %d - Insertion / %d - Shell / " ,
                       ECHANGE , INSERTION , SHELL ) ;
         (void)printf( "%d - Bubble simple \n%d - Bubble optimisé / " ,
                       BUBBLE0 , BUBBLE1 ) ;
         (void)printf( "%d - Shaker / %d - Quick sort / %d - Merge sort : " ,
                      SHAKER , QUICKSORT , MERGESORT ) ;
         (void)scanf( "%d" , &reponse ) ;
        }
     while ( reponse < ECHANGE || reponse > MERGESORT ) ;
     return( reponse ) ;
    }

/* -------------------------------------------- */

/* Vos fonctions */
/**
 * A function which swap the position in the array
 * of the elements at indexFirst and indexSecond.
 **/
void swap(int T[], int indexFirst, int indexSecond){
	int temp;
	temp = T[indexFirst];
	T[indexFirst] = T[indexSecond];
	T[indexSecond] = temp;
}



//--------------------------------------------------------------DONE
void tri_echange ( int T[] , int n ){
	int i,j,minIndex;
	
	for(i=0;i<n;i++){
		minIndex = i;
		for(j=i+1;j<n;j++){
			if(T[j]<T[minIndex]){
				minIndex = j;
			}
		}
		swap(T,i,minIndex);
	}
}

//--------------------------------------------------------------DONE
void tri_insertion ( int T[] , int n ){
	int i,j;
	for(i=1;i<n;i++){
		j=i;
		while(T[j-1]>T[j] && j>0){
			swap(T,j,j-1);
			j--;
		}
	}
}

//--------------------------------------------------------------TODO
void tri_shell ( int T[] , int n , int h0 ){
	
}


//--------------------------------------------------------------DONE
void tri_bubble ( int T[] , int n ){
	int doSwap,i;
	do{
		doSwap=0;
		for(i=0;i<n-1;i++){
			if(T[i]>T[i+1]){
				swap(T,i,i+1);
				doSwap = 1;
			}
		}
	}while(doSwap);
}


//--------------------------------------------------------------DONE
void tri_bubble_opt ( int T[] , int n ){
	int doSwap,i,minI;
	do{
		minI = 0;
		doSwap=0;
		for(i=minI;i<n-1;i++){
			if(T[i]>T[i+1]){
				swap(T,i,i+1);
				if(!doSwap){
					doSwap = 1;
				}
			}
		}
		//ne pas aller jusqu'au bout puisque le dernier de chaque
		//itération est le max
		n--;
	}while(doSwap);
}

//--------------------------------------------------------------DONE
void tri_shaker ( int T[] , int n ){
	int doSwap,i;
	do{
		doSwap=0;
		for(i=0;i<n-1;i++){
			if(T[i]>T[i+1]){
				swap(T,i,i+1);
			}
		}
		for(i=n-2;i>=0;i--){
			if(T[i]>T[i+1]){
				swap(T,i,i+1);
				doSwap = 1;
			}
		}
	}while(doSwap);
}

//--------------------------------------------------------------DONE
void tri_quick ( int T[] , int n ){
	int pivot,i,indexS,indexB;
	int small[n],big[n];

	pivot = T[0];
	indexB = 0;
	indexS = 0;
	for(i=1;i<n;i++){
		
		if(T[i]<pivot){
			small[indexS] = T[i];
			indexS++;
		}else{
			big[indexB] = T[i];
			indexB++;
		}		
	}
	if(indexS>=2){
		tri_quick(small, indexS);
	}
	if(indexB>=2){
		tri_quick(big, indexB);
	}


	for(i=0;i<indexS;i++){
		T[i]=small[i];
	}
	T[i]=pivot;
	i++;
	for(i=0;i<indexB;i++){
		T[i+indexS+1]=big[i];
	}
}

//--------------------------------------------------------------TODO
void tri_merge ( int T[] , int n ){
	int i,j,mid;
	int low[n],high[n];
	printf("taille:%d",n);

	if(n == 1){
		return;
	}else{
		mid = n/2;
		tri_merge(T, mid);
		tri_merge(T[mid],n-mid);

		i=0;
		j=0;
		while(i+j<n){
			if(i==mid){
				T[i+j]=high[j];
				j++;
			}else if(j==n-mid){
				T[i+j]=low[i];
				i++;
			}else{
				if(low[i]<=high[j]){
					T[i+j] = low[i];
					i++;
				}else{
					T[i+j] = high[j];
					j++;
				}
			}
		}
	}
	
	//milieu
	//séparation
	//tri ensemble
}

/* -------------------------------------------- */

int main ( void )
     {int T[ TAILLE ] , encore , choix ;
      do {remplir( T , TAILLE ) ;
          (void)printf( "Le tableau initial :\n" ) ;
          display( T , TAILLE ) ;
          choix = choisir() ;
          switch ( choix )
                 {case ECHANGE : tri_echange( T , TAILLE ) ; break ;
                  case INSERTION : tri_insertion( T , TAILLE ) ; break ;
                  case SHELL : tri_shell( T , TAILLE , 5 ) ; break ;
/* On a : tri_insertion( T , TAILLE ) équivaut à tri_shell( T , TAILLE , 1 ) */
                  case BUBBLE0 : tri_bubble( T , TAILLE ) ; break ;
                  case BUBBLE1 : tri_bubble_opt( T , TAILLE ) ; break ;
                  case SHAKER : tri_shaker( T , TAILLE ) ; break ;
                  case QUICKSORT : (void)printf( "Quick sort !\n" ) ;
                                   tri_quick( T , TAILLE ) ;
                                   break ;
                  case MERGESORT : (void)printf( "Merge sort !\n" ) ;
                                   tri_merge( T , TAILLE ) ;
                                   break ;
                 }
          (void)printf( "Le tableau trié :\n" ) ;
          display( T , TAILLE ) ;
          (void)printf( " Encore ? " ) ;
          (void)scanf( "%d" , &encore ) ;
         }
      while ( encore ) ;
      (void)printf( "Bye !\n" ) ;
      return( 0 ) ;
     }




