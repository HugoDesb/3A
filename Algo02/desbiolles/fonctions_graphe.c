/* Marc Gengler - Polytech Marseille - Janvier 2016 */

/* Ce fichier n'est pas commenté puisqu'il n'est pas sensé être lu.
   Il donne les implantations des fonctions de fonctions_graphe.h .
   Ces prototypes sont définis et décrits dans le fichier
   fonctions_graphe.h .

   Il se peut que le compilateur exige de changer 

#include <malloc/malloc.h>

   en

#include <malloc.h> */

/* ------------------------------------------------------------ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "constantes_type_graphe.h"

#include "fonctions_graphe.h"

/* ------------------------------------------------------------ */

char Transcode[ N ] = { 'a' , 'b' , 'c' , 'd' , 'e' , 'f' ,
			'g' , 'h' , 'i' , 'j' , 'k' , 'l' } ;

char * Transcouleur[ 12 ] = { "black" , "red" , "green3" , "blue" ,
			     "yellow" , "orange" , "darkviolet" , "gold" ,
			     "magenta" , "grey" , "deepskyblue" , "chartreuse" } ;

int Couleur ;

int Forme_memorisee = 0 ;

char Str_mem[ N ][ 200 ] ; 
  
/* ------------------------------------------------------------ */

int g_nonpond_cinq_AR_S[ 25 ] = { 0 , 1 , 0 , 0 , 0 ,
				  1 , 0 , 1 , 1 , 0 ,
				  0 , 1 , 0 , 1 , 0 ,
				  0 , 1 , 1 , 0 , 1 ,
				  0 , 0 , 0 , 1 , 0 } ;

int g_nonpond_six_DAG[ 36 ] = { 0 , 0 , 0 , 1 , 1 , 0 ,
				1 , 0 , 0 , 1 , 0 , 0 ,
				0 , 1 , 0 , 0 , 0 , 0 ,
				0 , 0 , 0 , 0 , 0 , 0 ,
				0 , 0 , 0 , 1 , 0 , 0 ,
				0 , 0 , 1 , 0 , 0 , 0 } ;

int g_nonpond_huit_non_DAG[ 64 ] = { 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 ,
				     0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 ,
				     0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
				     0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
				     0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 ,
				     0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 ,
				     0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 ,
				     0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;

int g_nonpond_neuf_S[ 81 ] = { 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 ,
			       1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 ,
			       1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
			       0 , 1 , 0 , 1 , 1 , 0 , 0 , 0 , 0 ,
			       0 , 0 , 1 , 1 , 0 , 1 , 0 , 0 , 0 ,
			       0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
			       0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 ,
			       0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 ,
			       0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 } ;

int g_arbre_neuf[ 81 ] = { 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
			   1 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 ,
			   0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
			   0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
			   1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
			   0 , 0 , 0 , 0 , 1 , 0 , 1 , 1 , 1 ,
			   0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
			   0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
			   0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 } ;

int g_nonpond_huit_sym[ 64 ] = { 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 ,
				 1 , 0 , 1 , 1 , 0 , 0 , 0 , 0 ,
				 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 ,
				 0 , 1 , 1 , 0 , 1 , 1 , 0 , 0 ,
				 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
				 0 , 0 , 1 , 1 , 0 , 0 , 1 , 0 ,
				 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 ,
				 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 } ;

int g_pond_six_nonsym[ 36 ] = { - 1 ,  4  , - 1 , - 1 , - 1 , - 1 ,
				 3  , - 1 ,  7  ,  2  , - 1 , - 1 ,
				- 1 ,  7  , - 1 ,  5  , - 1 ,  4  ,
				- 1 , - 1 ,  5  , - 1 ,  8  ,  6  ,
				- 1 , - 1 , - 1 ,  8  , - 1 , - 1 ,
				- 1 , - 1 ,  8  ,  6  , - 1 , - 1 } ;

int g_pond_huit_nonsym[ 64 ] = { - 1 , - 1 ,  11 ,  7  , - 1 , - 1 ,  6  , - 1 ,
				 - 1 , - 1 , - 1 , - 1 ,  20 ,  9  , - 1 , - 1 ,
				  11 ,  20 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,
				 - 1 , - 1 , - 1 , - 1 ,  8  , - 1 , - 1 , - 1 ,
				 - 1 ,  10 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,
				 - 1 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,  5  ,
				  6  , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,  9  ,
				 - 1 , - 1 , - 1 , - 1 , - 1 ,  5  , - 1 , - 1 } ;

int g_pond_huit_nonsym_lim[ 64 ] = { - 1 , - 1 ,  11 , - 1 , - 1 , - 1 ,  6  , - 1 ,
				     - 1 , - 1 , - 1 , - 1 ,  20 ,  9  , - 1 , - 1 ,
				      11 ,  20 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,
				     - 1 , - 1 , - 1 , - 1 ,  8  , - 1 , - 1 , - 1 ,
				     - 1 ,  10 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,
				     - 1 , - 1 , - 1 , - 1 ,  5  , - 1 , - 1 , - 1 ,
				      6  , - 1 , - 1 , - 1 , - 1 , - 1 ,  9  , - 1 ,
				     - 1 , - 1 , - 1 ,  12 , - 1 , - 1 , - 1 , - 1 } ;

int g_pond_huit[ 64 ] = { - 1 , - 1 ,  11 ,  7  , - 1 , - 1 ,  6  , - 1 ,
				 - 1 , - 1 , - 1 , - 1 ,  20 ,  9  , - 1 , - 1 ,
				  11 ,  20 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,
				 - 1 , - 1 , - 1 , - 1 ,  8  , - 1 , - 1 , - 1 ,
				 - 1 ,  10 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,
				 - 1 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,  5  ,
				  6  , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 ,  9  ,
				 - 1 , - 1 , - 1 , - 1 , - 1 ,  5  , - 1 , - 1 } ;

int g_flot_neuf[ 81 ] = { - 1 ,  21 , - 1 , - 1 ,  9  , - 1 , - 1 , - 1 , - 1 ,
			  - 1 , - 1 ,  18 , - 1 ,  3  ,  1  , - 1 , - 1 , - 1 ,
			  - 1 ,  12 , - 1 ,  7  ,  5  ,  6  , - 1 ,  1  , - 1 ,
			  - 1 , - 1 ,  5  , - 1 , - 1 ,  4  ,  2  , - 1 ,  16 ,
			  - 1 ,  2  ,  3  , - 1 , - 1 ,  12 , - 1 ,  3  , - 1 ,
			  - 1 , - 1 ,  5  ,  6  ,  12 , - 1 ,  5  ,  4  , - 1 ,
			  - 1 , - 1 , - 1 ,  2  , - 1 ,  5  , - 1 ,  2  ,  9  ,
			  - 1 , - 1 , - 1 , - 1 ,  2  , - 1 ,  3  , - 1 ,  6  ,
			  - 1 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 , - 1 } ;

/* ------------------------------------------------------------ */

void set_case_detail ( t_gra graphe , int i , int j , int defini , int couleur ) ;

void set_case_detail_pondere ( t_gra graphe , int i , int j ,
			       int defini , int poids , int couleur ) ;

void init_detail_flot( t_gra graphe , int i , int j , int poids ,
		       int capacite , int couleur ) ;

void imprime_case ( t_gra graphe , int i , int j , int info_couleur ,
		    int derniere_couleur , int sym , int limite ) ;

t_gra lire_graphe ( int valeurs[ ] , int n ) ;

t_gra lire_graphe_pondere ( int valeurs[ ] , int n ) ;

t_gra lire_graphe_flot ( int valeurs[ ] , int n ) ;

void parcours_pnr ( t_gra graphe , int sommet , int niveau ) ;

void parcours_pn ( t_gra graphe , int depart ) ;

void ajoute_nombre_inf ( char str[ ] , int nombre , char * sep ) ;

int est_sym ( t_gra graphe ) ;

/* ------------------------------------------------------------ */

void set_case_detail ( t_gra graphe , int i , int j , int defini , int couleur )
     {graphe->cases[ i ][ j ].defini = defini ;
      graphe->cases[ i ][ j ].pondere = NON ;
      graphe->cases[ i ][ j ].couleur = couleur ;
     }

void set_case_detail_pondere ( t_gra graphe , int i , int j ,
			       int defini , int poids , int couleur )
     {graphe->cases[ i ][ j ].defini = defini ;
      graphe->cases[ i ][ j ].pondere = OUI ;
      graphe->cases[ i ][ j ].flot = NON ;
      graphe->cases[ i ][ j ].poids = poids ;
      graphe->cases[ i ][ j ].couleur = couleur ;
     }

void init_detail_flot ( t_gra graphe , int i , int j , int poids ,
		        int capacite , int couleur )
     {graphe->cases[ i ][ j ].defini = OUI ;
      graphe->cases[ i ][ j ].pondere = OUI ;
      graphe->cases[ i ][ j ].flot = OUI ;
      graphe->cases[ i ][ j ].poids = poids ;
      graphe->cases[ i ][ j ].capacite = capacite ;
      graphe->cases[ i ][ j ].couleur = couleur ;
     }

void imprime_case ( t_gra graphe , int i , int j , int info_couleur ,
		    int derniere_couleur , int sym , int limite )
     {int couleur = NOIR ;
      char * symbole = "->" ;
      char str_printf[ 40 ] = "" ;
      t_info entree = graphe->cases[ i ][ j ] ;
      int test = ( entree.defini && entree.couleur <= limite ) ;
      if ( test )
	 {if ( info_couleur == TOUTES_COULEURS
	      || ( info_couleur == DERNIERE_COULEUR
		  && entree.couleur == derniere_couleur ) )
	     couleur = entree.couleur ;
	  if ( couleur == NOIR && graphe->flot && info_couleur == TOUT_NOIR
	      && entree.poids == entree.capacite )
	     couleur = ROUGE ;
	  if ( sym )
	     symbole = "--" ;
	  (void)printf( "; %c %s %c" , Transcode[ i ] , symbole , Transcode[ j ] ) ;
	  if ( couleur != NOIR )
	     {(void)sprintf( str_printf , "color=%s" , Transcouleur[ couleur ] ) ;
	      if ( graphe->pondere || graphe->flot )
		 strcat( str_printf , "," ) ;
	     }
	  if ( graphe->pondere || graphe->flot )
	     strcat( str_printf , "label=" ) ;
	  if ( graphe->flot )
	     {strcat( str_printf , "\"" ) ;
	      if ( entree.poids == entree.capacite )
		  strcat( str_printf , "**" ) ;
	     }
	  if ( graphe->pondere && ! graphe->flot )
	     ajoute_nombre_inf( str_printf , entree.poids , "\"" ) ;
	  if ( graphe->flot )
	     ajoute_nombre_inf( str_printf , entree.poids , "" ) ;
	  if ( graphe->flot )
	     {strcat( str_printf , " / " ) ;
	      ajoute_nombre_inf( str_printf , entree.capacite , "" ) ;
	      if ( entree.poids == entree.capacite )
		 strcat( str_printf , "**" ) ;
	      strcat( str_printf , "\"" ) ;
	     }
	  if ( strlen( str_printf ) != 0 )
	     (void)printf( "[%s]" , str_printf ) ;
	 }
     }

t_gra lire_graphe ( int valeurs[ ] , int n )
      {t_gra nouveau = nouveau_graphe( n ) ;
       int i , j , indice = 0 ;
       for ( i = 0 ; i < n ; i++ )
	   for ( j = 0 ; j < n ; j++ )
	       if ( valeurs[ indice++ ] > 0 )
		  set_arc( nouveau , i , j , NOIR ) ;
       return( nouveau ) ;
      }

t_gra lire_graphe_pondere ( int valeurs[ ] , int n )
      {t_gra nouveau = nouveau_graphe_pondere( n , - 200 , 200 ) ;
       int i , j , indice = 0 ;
       for ( i = 0 ; i < n ; i++ )
	   for ( j = 0 ; j < n ; j++ )
	       {if ( valeurs[ indice ] >= 0 )
		   set_arc_pondere( nouveau , i , j , valeurs[ indice ] , NOIR ) ;
		indice++ ;
	       }
       return( nouveau ) ;
      }

t_gra lire_graphe_flot ( int valeurs[ ] , int n )
      {t_gra nouveau = nouveau_graphe_flot( n , 50 ) ;
       int i , j , indice = 0 ;
       for ( i = 0 ; i < n ; i++ )
	   for ( j = 0 ; j < n ; j++ )
	       {if ( valeurs[ indice ] >= 0 )
		   init_detail_flot( nouveau , i , j , 0 , valeurs[ indice ] , NOIR ) ;
		indice++ ;
	       }
       return( nouveau ) ;
      }

void parcours_pnr ( t_gra graphe , int sommet , int niveau )
     {int voisin , taille = taille_graphe( graphe ) ;
      if ( ! mouille( graphe , sommet ) )
	 {if ( niveau < sommet_get_poids( graphe , sommet ) )
	     sommet_set_poids( graphe , sommet , niveau ) ;
	  tremper( graphe , sommet ) ;
	  for ( voisin = 0 ; voisin < taille ; voisin++ )
	      if ( get_arc( graphe , sommet , voisin ) )
		 parcours_pnr( graphe , voisin , niveau + 1 ) ;
	  secher( graphe , sommet ) ;
	 }
     }

void parcours_pn ( t_gra graphe , int depart )
     {int sommet , taille = taille_graphe( graphe ) ;
      for ( sommet = 0 ; sommet < taille ; sommet++ )
	  if ( sommet != depart )
	     sommet_set_poids( graphe , sommet , PLUS_INF ) ;
	  else
	     sommet_set_poids( graphe , sommet , 0 ) ;
      parcours_pnr( graphe , depart , 0 ) ;
     }

void ajoute_nombre_inf ( char str[ ] , int nombre , char * sep )
     {char str_aux[ 10 ] ;
      if ( nombre == PLUS_INF )
	 (void)sprintf( str_aux , "%s+inf%s" , sep , sep ) ;
      else
	 if ( nombre == MOINS_INF )
	    (void)sprintf( str_aux , "%s-inf%s" , sep , sep ) ;
	 else
	    (void)sprintf( str_aux , "%d" , nombre ) ;
      strcat( str , str_aux ) ;
     }

int est_sym ( t_gra graphe )
    {int i , j ;
     for ( i = 0 ; i < graphe->taille ; i++ )
	 for ( j = 0 ; j < graphe->taille ; j++ )
	     if ( graphe->cases[ i ][ j ].defini != graphe->cases[ j ][ i ].defini
		 || ( graphe->pondere && graphe->cases[ i ][ j ].defini
		     && graphe->cases[ i ][ j ].poids
		       != graphe->cases[ j ][ i ].poids ) )
		return( NON ) ;
     return( OUI ) ;
    }

/* ------------------------------------------------------------ */

int min ( int a , int b )
    {if ( a <= b )
	return( a ) ;
     else
	return( b ) ;
    }

int max ( int a , int b )
    {if ( a >= b )
	return( a ) ;
     else
	return( b ) ;
    }

/* ------------------------------------------------------------ */

/* Les fonctions dont les prototypes figurent dans fonctions_graphe.h . */

void lire_les_graphes ( void )
     {G_5_nonpond_S = lire_graphe( g_nonpond_cinq_AR_S , 5 ) ;
      G_6_nonpond_DAG = lire_graphe( g_nonpond_six_DAG , 6 ) ;
      G_8_ARAS_non_DAG = lire_graphe( g_nonpond_huit_non_DAG , 8 ) ;
      G_9_nonpond_S = lire_graphe( g_nonpond_neuf_S , 9 ) ;
      G_9_arbre = lire_graphe( g_arbre_neuf , 9 ) ;
      G_9_nonpond_NS = lire_graphe( g_flot_neuf , 9 ) ;
      G_9_nonpond_NS->pondere = NON ;
      G_8_nonpond_S = lire_graphe( g_nonpond_huit_sym , 8 ) ;
      G_8_nonpond_S_bis = lire_graphe( g_nonpond_huit_sym , 8 ) ;
      G_6_pond_NS = lire_graphe_pondere( g_pond_six_nonsym , 6 ) ;
      G_6_pond_NS_bis = lire_graphe_pondere( g_pond_six_nonsym , 6 ) ;
      G_8_pond_NS = lire_graphe_pondere( g_pond_huit_nonsym , 8 ) ;
      G_8_pond_NS_bis = lire_graphe_pondere( g_pond_huit_nonsym_lim , 8 ) ;
      G_8_pond_NS_ter = lire_graphe_pondere( g_pond_huit_nonsym , 8 ) ;
      G_9_flot = lire_graphe_flot( g_flot_neuf , 9 ) ;
     }

void liberer_les_graphes ( void )
     {free( G_5_nonpond_S ) ;
      free( G_6_nonpond_DAG ) ;
      free( G_8_ARAS_non_DAG ) ;
      free( G_9_nonpond_S ) ;
      free( G_9_arbre ) ;
      free( G_9_nonpond_NS ) ;
      free( G_8_nonpond_S ) ;
      free( G_8_nonpond_S_bis ) ;
      free( G_6_pond_NS ) ;
      free( G_6_pond_NS_bis ) ;
      free( G_8_pond_NS ) ;
      free( G_8_pond_NS_bis ) ;
      free( G_8_pond_NS_ter ) ;
      free( G_9_flot ) ;
     }

void definir_couleur ( int couleur )
     {assert( 0 <= couleur && couleur < NOMBRE_COULEURS ) ;
      Couleur = couleur ;
     }

void couleur_suivante ( void )
     {if ( Couleur + 1 != NOMBRE_COULEURS )
	 Couleur++ ;
     }

int la_couleur ( void )
    {return( Couleur ) ;
    }

void set_arc ( t_gra graphe , int i , int j , int couleur )
     {assert( 0 <= i && i < graphe->taille ) ; 
      assert( 0 <= j && j < graphe->taille ) ; 
      assert( 0 <= couleur && couleur < NOMBRE_COULEURS ) ;
      assert( ! graphe->pondere ) ;
      set_case_detail( graphe , i , j , OUI , couleur ) ;
     }

void set_arete ( t_gra graphe , int i , int j , int couleur )
     {set_arc( graphe , i , j , couleur ) ;
      set_arc( graphe , j , i , couleur ) ;
     }

void set_arc_pondere ( t_gra graphe , int i , int j , int poids , int couleur )
     {assert( 0 <= i && i < graphe->taille ) ; 
      assert( 0 <= j && j < graphe->taille ) ; 
      assert( 0<= couleur && couleur < NOMBRE_COULEURS ) ;
      assert( graphe->pondere ) ;
      assert( ( POIDS_MIN <= poids && poids <= POIDS_MAX )
	      || poids == MOINS_INF || poids == PLUS_INF ) ;
      set_case_detail_pondere( graphe , i , j , OUI , poids , couleur ) ;
     }

void set_arete_pondere ( t_gra graphe , int i , int j , int poids , int couleur )
     {set_arc_pondere( graphe , i , j , poids , couleur ) ;
      set_arc_pondere( graphe , j , i , poids , couleur ) ;
     }

int poids_ok ( t_gra graphe , int poids )
    {return( ( POIDS_MIN <= poids && poids <= POIDS_MAX )
	    || poids == MOINS_INF || poids == PLUS_INF ) ;
    }

int get_arc ( t_gra graphe , int i , int j )
    {assert( 0 <= i && i < graphe->taille ) ;
     assert( 0 <= j && j < graphe->taille ) ;
     return( graphe->cases[ i ][ j ].defini ) ;
    }

int get_arete ( t_gra graphe , int i , int j )
    {assert( 0 <= i && i < graphe->taille ) ;
     assert( 0 <= j && j < graphe->taille ) ;
     return( graphe->cases[ i ][ j ].defini && graphe->cases[ j ][ i ].defini ) ;
    }

int poids_arc ( t_gra graphe , int i , int j )
    {assert( graphe->pondere ) ;
     assert( get_arc( graphe , i , j ) ) ;
     return( graphe->cases[ i ][ j ].poids ) ;
    }

void ajoute_poids_arc ( t_gra graphe , int i , int j , int poids )
     {assert( graphe->pondere ) ;
      assert( get_arc( graphe , i , j ) ) ;
      assert( poids_ok( graphe , poids_arc( graphe , i , j ) + poids ) ) ;
      graphe->cases[ i ][ j ].poids += poids ;
     }

int capacite_arc ( t_gra graphe , int i , int j )
    {assert( graphe->pondere && graphe->flot ) ;
     assert( get_arc( graphe , i , j ) ) ;
     return( graphe->cases[ i ][ j ].capacite ) ;
    }

int couleur_arc ( t_gra graphe , int i , int j )
    {assert( get_arc( graphe , i , j ) ) ;
     return( graphe->cases[ i ][ j ].couleur ) ;
    }

int couleur_arete ( t_gra graphe , int i , int j )
    {int couleur = couleur_arc( graphe , i , j ) ;
     assert( couleur == couleur_arc( graphe , j , i ) ) ;
     return( couleur ) ;
    }

void set_couleur_arc ( t_gra graphe , int i , int j , int couleur )
     {assert( get_arc( graphe , i , j ) ) ;
      assert( 0<= couleur && couleur < NOMBRE_COULEURS ) ;
      graphe->cases[ i ][ j ].couleur = couleur ;
     }

void unset_arc ( t_gra graphe , int i , int j )
     {assert( 0 <= i && i < graphe->taille ) ; 
      assert( 0 <= j && j < graphe->taille ) ; 
      set_case_detail( graphe , i , j , NON , NOIR ) ;
     }

void unset_arete ( t_gra graphe , int i , int j )
     {unset_arc( graphe , i , j ) ;
      unset_arc( graphe , j , i ) ;
     }

void tremper ( t_gra graphe , int s )
     {assert( 0 <= s && s < graphe->taille ) ;
      graphe->etatsommet[ s ] = MOUILLE ;
     }

void secher (t_gra graphe , int s )
     {assert( 0 <= s && s < graphe->taille ) ;
      graphe->etatsommet[ s ] = SEC ;
     }

int mouille (t_gra graphe , int s )
     {assert( 0 <= s && s < graphe->taille ) ;
      return( graphe->etatsommet[ s ] == MOUILLE ) ;
     }

void sommet_set_poids ( t_gra graphe , int s , int poids )
     {assert( 0 <= s && s < graphe->taille ) ;
      graphe->sommetpondere[ s ] = OUI ;
      graphe->sommetpoids[ s ] = poids ;
     }

void sommet_unset_poids ( t_gra graphe , int s )
     {assert( 0 <= s && s < graphe->taille ) ;
      graphe->sommetpondere[ s ] = NON ;
     }

int sommet_possede_poids ( t_gra graphe , int s )
    {assert( 0 <= s && s < graphe->taille ) ;
     return( graphe->sommetpondere[ s ] ) ;
    }

int sommet_get_poids ( t_gra graphe , int s )
    {assert( 0 <= s && s < graphe->taille && graphe->sommetpondere[ s ] ) ;
     return( graphe->sommetpoids[ s ] ) ;
    }

t_gra nouveau_graphe ( int n )
      {t_gra nouveau ;
       int i , j ;
       assert( n <= N ) ;
       nouveau = (t_gra)malloc( sizeof( t_gra_struct ) ) ;
       nouveau->taille = n ;
       nouveau->pondere = NON ;
       for ( i = 0 ; i < n ; i++ )
	   {for ( j = 0 ; j < n ; j++ )
		set_case_detail( nouveau , i , j , NON , Couleur ) ;
	    nouveau->etatsommet[ i ] = SEC ;
	    nouveau->sommetpondere[ i ] = NON ;
	   }
       return( nouveau ) ;
      }

t_gra nouveau_graphe_pondere ( int n , int poids_min , int poids_max )
      {t_gra nouveau = nouveau_graphe( n ) ;
       assert( POIDS_MIN <= poids_min
	      && poids_min <= poids_max
	      && poids_max <= POIDS_MAX ) ;
       nouveau->pondere = OUI ;
       nouveau->flot = NON ;
       nouveau->poids_min = poids_min ;
       nouveau->poids_max = poids_max ;
       return( nouveau ) ;
      }

t_gra nouveau_graphe_flot ( int n , int capacite )
      {t_gra nouveau = nouveau_graphe_pondere( n , 0 , capacite ) ;
       assert( 0 < capacite && capacite <= POIDS_MAX ) ;
       nouveau->flot = OUI ;
       return( nouveau ) ;
      }

void memorise_forme_graphe_flot ( t_gra graphe )
     {int i , j , taille = taille_graphe( graphe ) ;
      char str_str[ 20 ] ;
      if ( graphe->pondere && graphe->flot )
	 {Forme_memorisee = OUI ;
	  for ( i = 0 ; i < N ; i++ )
	      strcpy( Str_mem[ i ] , "" ) ;
	  parcours_pn( graphe , 0 ) ;
	  assert( sommet_get_poids( graphe , taille - 1 ) > 0 ) ;
	  for ( i = 0 ; i < taille ; i++ )
	      {int deja = 0 ;
	       char str_printf[ 50 ] = "; {rank=same;" ;
	       for ( j = 0 ; j < taille - 1 ; j++ )
		   if ( sommet_get_poids( graphe , j ) == i )
		      {if ( deja )
			  strcat( str_printf , "," ) ;
		       (void)sprintf( str_str , "%c" , Transcode[ j ] ) ;
		       strcat( str_printf , str_str ) ;
		       deja = 1 ;
		      }
	       strcat( str_printf , "}" ) ;
	       if ( deja )
		  strcat( Str_mem[ taille ] , str_printf ) ;
	      }
	  (void)sprintf( str_str , "; {rank=same;%c}" , Transcode[ taille - 1 ] ) ;
          strcat( Str_mem[ taille ] , str_str ) ;
	  for ( i = 0 ; i < taille ; i++ )
	      sommet_unset_poids( graphe , i ) ;
	 }
     }

void oublie_forme_graphe_flot ( void )
     {Forme_memorisee = NON ;
     }

void copie_graphe ( t_gra graphe , t_gra nouveau )
     {memcpy( nouveau , graphe , sizeof( t_gra_struct ) ) ;
     }

int taille_graphe ( t_gra graphe )
    {return( graphe->taille ) ;
    }

int graphe_pondere ( t_gra graphe )
    {return( graphe->pondere ) ;
    }

int graphe_flot ( t_gra graphe )
    {return( graphe->flot ) ;
    }

void imprime_graphe ( t_gra graphe , int info_couleur , int gauche_droite )
     {int i , j , taille = graphe->taille , derniere_couleur = NOIR ;
      for ( i = 0 ; i < taille ; i++ )
	  for ( j = 0 ; j < taille ; j++ )
	      if ( graphe->cases[ i ][ j ].defini
		  && graphe->cases[ i ][ j ].couleur > derniere_couleur )
		 derniere_couleur = graphe->cases[ i ][ j ].couleur ;
      imprime_graphe_limite( graphe , info_couleur , derniere_couleur , gauche_droite ) ;
     }

void imprime_graphe_limite ( t_gra graphe , int info_couleur ,
			     int limite , int gauche_droite )
     {int i , j , sym , taille = graphe->taille ;
      sym = est_sym( graphe ) ;
      if ( sym )
	 (void)printf( "\ngraph{" ) ;
      else
	 (void)printf( "\ndigraph{" ) ;
      for ( i = 0 ; i < taille ; i++ )
	  {char str_add[ 20 ] = "" ;
	   if ( graphe->etatsommet[ i ] == MOUILLE )
	      strcat( str_add , "*" ) ;
	   if ( graphe->sommetpondere[ i ] )
	      {strcat( str_add , " / " ) ;
	       ajoute_nombre_inf( str_add , graphe->sommetpoids[ i ] , "" ) ;
	      }
	   if ( i != 0 )
	      (void)printf( ";" ) ;
	   if ( strlen( str_add ) != 0 )
	      (void)printf( " %c[label=\"%c%s\"]" ,
			    Transcode[ i ] , Transcode[ i ] , str_add ) ;
	   else
	      (void)printf( " %c[label=%c]" , Transcode[ i ] , Transcode[ i ] ) ;
	  }
      for ( i = 0 ; i < taille ; i++ )
	  for ( j = sym * i ; j < taille ; j++ )
	      imprime_case( graphe , i , j , info_couleur , limite , sym , limite ) ; 
      if ( Forme_memorisee )
	 (void)printf( "%s" , Str_mem[ taille ] ) ;
      if ( gauche_droite )
	 (void)printf( "; rankdir=LR" ) ;
      (void)printf( " }\n\n" ) ;
     }

void imprime_graphe_etapes ( t_gra graphe , int info_couleur , int gauche_droite )
     {int i , j , taille = graphe->taille ;
      int derniere_couleur = NOIR ;
      int premiere_couleur = NOMBRE_COULEURS - 1 ;
      for ( i = 0 ; i < taille ; i++ )
	  for ( j = 0 ; j < taille ; j++ )
	      if ( graphe->cases[ i ][ j ].defini )
		 {if ( graphe->cases[ i ][ j ].couleur > derniere_couleur )
		     derniere_couleur = graphe->cases[ i ][ j ].couleur ;
		  if ( graphe->cases[ i ][ j ].couleur < premiere_couleur )
		     premiere_couleur = graphe->cases[ i ][ j ].couleur ;
		 }
      for ( i = premiere_couleur ; i <= derniere_couleur ; i++ )
	  imprime_graphe_limite( graphe , info_couleur , i , gauche_droite ) ;
     }

/* ------------------------------------------------------------ */

t_file cree_file_vide ( void )
       {return( (t_file)NULL ) ;
       }

int est_file_vide ( t_file file )
    {return( file == cree_file_vide() ) ;
    }

t_file insere_file ( int sommet , t_file file )
       {t_file nouv ;
	nouv = (t_file)malloc( sizeof ( struct_file ) ) ;
	nouv->sommet = sommet ;
	nouv->suiv = cree_file_vide( ) ;
	if ( est_file_vide( file ) )
	   return( nouv ) ;
	else
	   {t_file local = file ;
	    while ( local->suiv != NULL )
		  local = local->suiv ;
	    local->suiv = nouv ;
            return( file ) ;
           }
       }

int tete_file ( t_file file )
    {assert( ! est_file_vide( file ) ) ;
     return( file->sommet ) ;
    }

t_file supprime_tete_file ( t_file file )
       {assert( ! est_file_vide( file ) ) ;
        return( file->suiv ) ;
       }

/* ------------------------------------------------------------ */
