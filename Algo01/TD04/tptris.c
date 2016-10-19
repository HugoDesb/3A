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

//DONE
void tri_echange ( int T[] , int n ){
	int i,j,minIndex,temp;
	
	for(i=0;i<n;i++){
		minIndex = i;
		for(j=i+1;j<n;j++){
			if(T[j]<T[minIndex]){
				minIndex = j;
			}
		}
		temp = T[i];
		T[i] = T[minIndex];
		T[minIndex] = temp;
	}
}


//DONE
void tri_insertion ( int T[] , int n ){
	int i,j,temp;
	for(i=1;i<n;i++){
		j=i;
		while(T[j-1]>T[j] && j>0){
			temp = T[j-1];
			T[j-1] = T[j];
			T[j] = temp;
			j--;
		}
	}
}
void tri_shell ( int T[] , int n , int h0 ){
	
}


//DONE
void tri_bubble ( int T[] , int n ){
	int swap,i,temp;
	do{
		swap=0;
		for(i=0;i<n-1;i++){
			if(T[i]>T[i+1]){
				temp = T[i];
				T[i] = T[i+1];
				T[i+1] = temp;
				swap = 1;
			}
		}
	}while(swap);
}



void tri_bubble_opt ( int T[] , int n ){
	int swap,i,minI,temp;
	do{
		minI = 0;
		swap=0;
		for(i=minI;i<n-1;i++){
			if(T[i]>T[i+1]){
				temp = T[i];
				T[i] = T[i+1];
				T[i+1] = temp;
				if(!swap){
					
					swap = 1;
				}
			}
		}
		//ne pas aller jusqu'au bout puisque le dernier de chaque
		//itération est le max
		n --;
	}while(swap);
}
void tri_shaker ( int T[] , int n ){
	int swap,i,temp;
	do{
		swap=0;
		for(i=0;i<n-1;i++){
			if(T[i]>T[i+1]){
				temp = T[i];
				T[i] = T[i+1];
				T[i+1] = temp;
			}
		}
		for(i=n-2;i>=0;i--){
			if(T[i]>T[i+1]){
				temp = T[i];
				T[i] = T[i+1];
				T[i+1] = temp;
				swap = 1;
			}
		}
	}while(swap);
}

//TODO
void tri_quick ( int T[] , int n ){
	int mid,pivot,i;
	int result[n];

	pivot = 0;
	for(i=0;i<n;i++){
		
	}
	
}

//WIP
void tri_merge ( int T[] , int n ){
	
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




