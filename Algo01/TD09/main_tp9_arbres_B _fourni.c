#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <limits.h>

typedef struct mm
{
	int feuille ;
	int val ;
	char etiq ;
	struct mm *fg ;
	struct mm *fd ;
}
	t_feuille , *t_ptr_arbre ;

typedef t_ptr_arbre tpa ;

typedef struct mmmmm
{
	tpa val;
	struct mmmmm *next ;
}
	t_liste_tpa , *tpl_tpa ;



/* -------------------------------------------- */

#define N 16

int Tableau[ N ][ N ] ;

typedef struct mmmm
{
	int tab[ N ][ N ] ;
	struct mmmm *suiv ;
}
	t_liste , *tpl ;

tpl Solutions ;

int Nombre_solutions ;

/* -------------------------------------------- */
tpl_tpa cree_vide(void);
int est_vide(tpl_tpa l);
tpl_tpa ajout_liste(tpa val, tpl_tpa l);
tpa tete_liste(tpl_tpa l);
tpl_tpa queue_liste(tpl_tpa l);

tpa cree_feuille ( int valeur ) ;
int val_feuille ( tpa arbre ) ;
int est_feuille ( tpa arbre ) ;
tpa cree_noeud ( tpa gauche , tpa droit , char etiquette ) ;
tpa arbre_fg ( tpa arbre ) ;
tpa arbre_fd ( tpa arbre ) ;
char arbre_etiq ( tpa arbre ) ;

int petit ( tpa a , tpa b ) ;
int trois_poss ( tpa a , tpa b ) ;
int ordre_prefixe ( tpa a ) ;
int ordre_prefixe_rec ( tpa a , int * maxi ) ;
int egal_prof ( tpa a ) ;
int egal_prof_rec ( tpa a , int prof ) ;

tpa arbre_fibo( int n ) ;
void infixe ( tpa arbre ) ;

int initialise ( void ) ;
int possible ( int ligne , int colonne , int n ) ;
void afficher ( tpl liste , int n ) ;
void back_track( int ligne , int n ) ;

int main ( void ) ;

/* -------------------------------------------- */
/**
 * Renvoie le pointeur vide
 */
tpl_tpa cree_vide(void){
	return (tpl_tpa)NULL;
}
/**
 * T si la liste est égale au pointeur null, F autrement
 */
int est_vide(tpl_tpa l){
	return l==cree_vide();
}
/**
 * Ajoute la valeur au début de la liste, renvoie la nouvelle liste
 */
tpl_tpa ajout_liste(tpa val, tpl_tpa l){
	tpl_tpa newL;
	newL = (tpl_tpa)malloc(sizeof(tpl_tpa));
	newL->val = val;
	newL->next = l;
	return newL;
}
/**
 * Renvoie la première valeur de la liste
 */
tpa tete_liste(tpl_tpa l){
	assert(l);
	return l->val;
}
/**
 * Renvoie le ptr vers l'élément suivant de la liste
 */
tpl_tpa queue_liste(tpl_tpa l){
	assert(l);
	return l->next;
}


tpa cree_feuille ( int valeur )
{
	tpa nouv ;
	nouv = (tpa)malloc( sizeof( t_feuille ) ) ;
	nouv->feuille = 1 ;
	nouv->val = valeur ;
	return( nouv ) ;
}

int val_feuille ( tpa arbre )
{
	assert( est_feuille ( arbre ) ) ;
	return( arbre->val ) ;
}

int est_feuille ( tpa arbre )
{
	return( arbre->feuille ) ;
}

tpa cree_noeud ( tpa gauche , tpa droit , char etiquette )
{
	tpa nouv ;
	nouv = (tpa)malloc( sizeof( t_feuille ) ) ;
	nouv->feuille = 0 ;
	nouv->etiq = etiquette ;
	nouv->fg = gauche ;
	nouv->fd = droit ;
	return( nouv ) ;
}

tpa arbre_fg ( tpa arbre )
{assert( ! est_feuille( arbre ) ) ;
	return( arbre->fg ) ;
}

tpa arbre_fd ( tpa arbre )
{assert( ! est_feuille( arbre ) ) ;
	return( arbre->fd ) ;
}

char arbre_etiq ( tpa arbre )
{assert( ! est_feuille( arbre ) ) ;
	return( arbre->etiq ) ;
}

/* -------------------------------------------- */

int petit ( tpa a , tpa b )
{
	if(est_feuille(a)){
		return 1;
	}else{
		if(est_feuille(b)){
			return 0;
		}else{
			return petit(arbre_fg(a),arbre_fg(b)) && petit(arbre_fg(a),arbre_fg(b));
		}
	}
}

int trois_poss ( tpa a , tpa b )
{
	return petit(a,b)-petit(b,a);
}

/* Pour tester l'ordre, il faut retourner un booléen qui dit si le
   parcours de fils gauche a donné des feuilles dans l'ordre, plus la
   valeur la plus grande. Celle-ci est retournée par l'intermédiaire
   d'une variable passée par référence. On triche, car cette variable
   est initialisée à INT_MIN, alors que MAX n'a en fait pas de
   neutre. INT_MIN provient de limits.h */

int ordre_prefixe ( tpa a )
{
	int maxi;
	return ordre_prefixe_rec(a, &maxi);
}

int ordre_prefixe_rec ( tpa a , int * maxi )
{
	if(est_feuille(a)){
		if(val_feuille(a)>= *maxi){
			*maxi = val_feuille(a);
			return 1;
		}else{
			return 0;
		}
	}else{
		return ordre_prefixe_rec(arbre_fg(a), maxi) && ordre_prefixe_rec(arbre_fd(a), maxi);
	}
}

int egal_prof ( tpa a )
{
	return egal_prof_rec(a, 0);
}

int egal_prof_rec ( tpa a , int prof )
{
	if(est_feuille(a)==prof){
		return 1;
	}else{
		prof++;
		return egal_prof_rec(arbre_fg(a), prof) && egal_prof_rec(arbre_fd(a), prof);
	}
}

/* -------------------------------------------- */

void infixe ( tpa a )
{
	if(est_feuille(a)){
		printf("%d",val_feuille(a));
	}else{
		printf("(");
		infixe(arbre_fg(a));
		printf(" %c ",arbre_etiq(a));
		infixe(arbre_fd(a));
		printf(")");
	}
}

tpa arbre_fibo ( int n )
{
	if(n == 0){
		return cree_feuille(0);
	}else if(n == 1){
		return cree_feuille(1);
	}else{
		return cree_noeud(arbre_fibo(n-1), arbre_fibo(n-2), '+');
	}
}


/* -------------------------------------------- */

int initialise ( void )
{
	int i , j , lu ;
	for ( i = 0 ; i < N ; i++ ){
		for ( j = 0 ; j < N ; j++ ){
			Tableau[ i ][ j ] = 0 ;
		}
	}	
	Solutions = (tpl)NULL ;
	Nombre_solutions = 0 ;
	do {
		(void) printf( "Taille de l'échiquier ( 1 - %d ) ? " , N ) ;
		(void)scanf( "%d" , &lu ) ;
	}while ( lu < 1 || lu > N ) ;
	return( lu ) ;
}

int possible ( int ligne , int colonne , int n )
{
	return 0;
}

void afficher ( tpl liste , int n )
{
}

void back_track ( int ligne , int n )
{
}

/* -------------------------------------------- */

int main ( void )
{
	t_ptr_arbre arbre_a , arbre_b , arbre_c ;
	int n , lu ;
	arbre_a = cree_noeud( cree_noeud( cree_feuille( 5 ) ,
	                                  cree_noeud( cree_feuille( 6 ) ,
	                                              cree_feuille( 9 ) ,
	                                              '+' ) ,
	                                  '*' ) ,
	                      cree_noeud( cree_noeud( cree_noeud( cree_feuille( 15 ) ,
	                                                          cree_feuille( 19 ) ,
	                                                          '+' ) ,
	                                              cree_feuille( 10 ) ,
	                                              '*' ) ,
	                                  cree_noeud( cree_feuille( 11 ) ,
	                                              cree_feuille( 13 ) ,
	                                              '/' ) ,
	                                  '/' ) ,
	                      '-' ) ;
	arbre_b = cree_noeud( cree_noeud( cree_noeud( cree_feuille( 1 ) ,
	                                              cree_feuille( 2 ) ,
	                                              '*' ) ,
	                                  cree_noeud( cree_feuille( 4 ) ,
	                                              cree_feuille( 5 ) ,
	                                              '/' ) ,
	                                  '/' ) ,
	                      cree_noeud( cree_feuille( 5 ) ,
	                                  cree_noeud( cree_feuille( 6 ) ,
	                                              cree_feuille( 9 ) ,
	                                              '+' ) ,
	                                  '*' ) ,
	                      '-' ) ;
	arbre_c = cree_noeud( cree_feuille( 1 ) ,
	                      cree_noeud( cree_feuille( 2 ) ,
	                                  cree_feuille( 2 ) ,
	                                  '+' ) ,
	                      '*' ) ;
	(void)printf( "A plus petit que B ? : %d\n" , petit( arbre_a , arbre_b ) ) ;
	(void)printf( "B plus petit que A ? : %d\n" , petit( arbre_b , arbre_a ) ) ;
	(void)printf( "A plus petit que A ? : %d\n" , petit( arbre_a , arbre_a ) ) ;
	(void)printf( "Fils gauche de A plus petit que B ? : %d\n" ,
	              petit( arbre_fg( arbre_a ) , arbre_b ) ) ;
	(void)printf( "3poss entre A et B ? : %d\n" , trois_poss( arbre_a , arbre_b ) ) ;
	(void)printf( "3poss entre A et A ? : %d\n" , trois_poss( arbre_a , arbre_a ) ) ;
	(void)printf( "3poss entre A et fils gauche de A ? : %d\n" ,
	              trois_poss( arbre_a , arbre_fg( arbre_a ) ) ) ;
	(void)printf( "Feuilles de A dans l'ordre ( parcours profondeur ) ? : %d\n" ,
	              ordre_prefixe( arbre_a ) ) ;
	(void)printf( "Feuilles de B dans l'ordre ( parcours profondeur ) ? : %d\n" ,
	              ordre_prefixe( arbre_b ) ) ;
	(void)printf( "Valeurs des feuilles égales à la profondeur pour A ? : %d\n" ,
	              egal_prof( arbre_a ) ) ;
	(void)printf( "Valeurs des feuilles égales à la profondeur pour C ? : %d\n" ,
	              egal_prof( arbre_c ) ) ;
	do {
		(void)printf( "La valeur pour laquelle calculer l'arbre " ) ;
		(void)printf( "de Fibonacci (arrêt si négatif) : " ) ;
		scanf( "%d" , & n ) ;
		if ( n >= 0 )
			{
				infixe( arbre_fibo( n ) ) ;
				(void)printf( "\n" ) ;
			}
	}
	while ( n >= 0 ) ;
	n = initialise( ) ;
	back_track( 0 , n ) ;
	(void)printf( "Il y a %d solutions !\n" , Nombre_solutions ) ;
	(void)printf( "Souhaitez-vous les voir (0/1) ? " ) ;
	(void)scanf( "%d" , &lu ) ;
	if ( lu )
		afficher( Solutions , n ) ;
	(void)printf( "Bye !\n" ) ;
	return( 0 ) ;
}
