/* Marc Gengler - Polytech Marseille - Janvier 2016 */

/* ------------------------------------------------------------ */

/* Les librairies standard. Attention, certains systèmes refusent

#include <malloc/malloc.h>

   et exigent plutôt

#include <malloc.h> */

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

/* ------------------------------------------------------------ */

/* Inclusion des constantes et prototypes définis ailleurs. */

#include "constantes_type_graphe.h"

#include "fonctions_graphe.h"

/* ------------------------------------------------------------ */

/* Les prototypes des fonctions locales. */

void exemples ( void ) ;

void ma_contribution ( void ) ;

int main ( void ) ;

/* ------------------------------------------------------------ */

/* Le fichier des contributions demandées aux élèves. C'est
   définitivement le seul fichier qui puisse être modifié. */

#include "ma_contribution.c"

/* ------------------------------------------------------------ */

/* Une fonction à lire pour comprendre le fonctionnement. */

void exemples ( void )
     {t_gra G , GP , GPP ;
      int i ;

     (void)printf( "C'est parti :\n\n" ) ;

      definir_couleur( ROUGE ) ;
      G = nouveau_graphe( 5 ) ;
      for ( i = 0 ; i < 4 ; i++ )
	  {set_arc( G , i , i , la_couleur( ) ) ;
           couleur_suivante( ) ;
	  }
      tremper( G , Sc ) ;

      (void)printf( "Impression d'un graphe non orienté dans toutes les couleurs :\n" ) ;
      imprime_graphe( G , TOUTES_COULEURS , NON ) ;
      (void)printf( "Impression du même graphe en noir et blanc :\n" ) ;
      imprime_graphe( G , TOUT_NOIR , NON ) ;

      couleur_suivante( ) ;
      set_arc( G , Sc , Sd , la_couleur( ) ) ;
      set_arete( G , 4 , 1 , JAUNE ) ;

      (void)printf( "Impression d'un graphe orienté dans toutes les couleurs :\n" ) ;
      imprime_graphe( G , TOUTES_COULEURS , NON ) ;
      (void)printf( "Impression de ce graphe en gardant la seule dernière couleur :\n" ) ;
      imprime_graphe( G , DERNIERE_COULEUR , NON ) ;

      tremper( G , Se ) ;
      sommet_set_poids( G , 4 , 15 ) ;
      sommet_set_poids( G , Sb , 25 ) ;

      (void)printf( "Impression qui se limite aux couleurs jusqu'au VERT :\n" ) ;
      imprime_graphe_limite( G , TOUTES_COULEURS , VERT , NON ) ;
      (void)printf( "Variante où on se limite aux couleurs jusqu'au JAUNE :\n" ) ;
      imprime_graphe_limite( G , DERNIERE_COULEUR , JAUNE , NON ) ;

      definir_couleur( NOIR ) ;
      GP = nouveau_graphe_pondere( 6 , - 500 , 500 ) ;
      set_arc_pondere( GP , Sa , Sb , MOINS_INF , ROUGE ) ;
      set_arc_pondere( GP , Sb , Sc , 17 , VERT ) ;
      set_arc_pondere( GP , Sc , Sd , 55 , BLEU ) ;
      set_arc_pondere( GP , Sc , Sc , - 119 , JAUNE ) ;
      set_arete_pondere( GP , Sd , Se , - 40 , VERT ) ;
      set_arc_pondere( GP , Se , Sf , - 157 , BLEU ) ;

      (void)printf( "Un graphe orienté pondéré et polychrome :\n" ) ;
      imprime_graphe( GP , TOUTES_COULEURS , OUI ) ;

      unset_arc( GP , Sd , 4 ) ;

      (void)printf( "On enlève un arc et se limite au JAUNE en uni-colore :\n" ) ;
      imprime_graphe_limite( GP , DERNIERE_COULEUR , JAUNE , OUI ) ;

      (void)printf( "Impression de toutes les étapes de couleurs intermédiaires :\n" ) ;
      imprime_graphe_etapes( GP , DERNIERE_COULEUR , OUI ) ;

      definir_couleur( NOIR ) ;
      GPP = nouveau_graphe_pondere( 6 , - 100 , 100) ;
      sommet_set_poids( GPP , Sc , 25 ) ;
      tremper( GPP , Sc ) ;
      sommet_set_poids( GPP , 5 , 10543 ) ;
      tremper( GPP , Sa ) ;
      set_arc_pondere( GPP , Sa , Sb , 5 , 0 ) ;
      couleur_suivante( ) ;
      set_arc_pondere( GPP , Sb , Sc , 10 , 1 ) ;
      couleur_suivante( ) ;
      set_arete_pondere( GPP , Sc , Sd , 15 , 2 ) ;
      couleur_suivante( ) ;
      set_arc_pondere( GPP , Sd , Se , 20 , 3 ) ;
      set_arc_pondere( GPP , Sd , Sd , - 44 , 3 ) ;
      couleur_suivante( ) ;
      set_arete_pondere( GPP , Se , Sf , 25 , 4 ) ;
      couleur_suivante( ) ;
      set_arc_pondere( GPP , Sf , Sa , 30 , 5 ) ;
      couleur_suivante( ) ;
      set_arc_pondere( GPP , Sa , Sc , 35 , 6 ) ;
      couleur_suivante( ) ;
      set_arc_pondere( GPP , Sc , Se , 40 , 7 ) ;
      couleur_suivante( ) ;
      set_arete_pondere( GPP , Se , Sa , 45 , 8 ) ;
      couleur_suivante( ) ;
      set_arc_pondere( GPP , Sb , Sd , 50 , 9 ) ;
      couleur_suivante( ) ;
      set_arete_pondere( GPP , Sd , Sf , 55 , 10 ) ;
      couleur_suivante( ) ;
      set_arete_pondere( GPP , Sf , Sb , 60 , 11 ) ;

      (void)printf( "Et le dernier, à afficher avec l'option circo :\n" ) ;
      imprime_graphe_etapes( GPP , TOUTES_COULEURS , NON ) ; 

      free( G ) ;
      free( GP ) ;
      free( GPP ) ;
     }

/* ------------------------------------------------------------ */

/* Cette fonction donne la séquence des problèmes à traiter. Elle ne doit pas
   être modifiée. Le descriptif détaillé  est donné dans ma_contribution.c ! */

void ma_contribution (void )
     {int table_predecesseurs[ N ] , nombre_composantes ;
      definir_couleur( NOIR ) ;

/* Ecrire graphe_non_oriente. */

      (void)printf( "Graphe %s non orienté : %d\n\n" , "G_5_nonpond_S" ,
		    graphe_non_oriente( G_5_nonpond_S ) ) ;
      (void)printf( "Le graphe G_5_nonpond_S :\n" ) ;
      imprime_graphe( G_5_nonpond_S , TOUT_NOIR , OUI ) ;

      (void)printf( "Graphe %s non orienté : %d\n\n" , "G_6_nonpond_DAG" ,
      		    graphe_non_oriente( G_6_nonpond_DAG ) ) ;
      (void)printf( "Le graphe G_6_nonpond_DAG :\n" ) ;
      imprime_graphe( G_6_nonpond_DAG , TOUT_NOIR , OUI ) ;

/* Ecrire graphe_AR. */

      (void)printf( "Graphe %s anti-réflexif : %d\n\n" , "G_5_nonpond_S" ,
		    graphe_AR( G_5_nonpond_S ) ) ;

/* Ecrire fermeture_reflexive. */

      couleur_suivante( ) ;
      fermeture_reflexive( G_5_nonpond_S ) ;
      (void)printf( "Le graphe %s fermé réflexivement :\n" , "G_5_nonpond_S" ) ;
      imprime_graphe( G_5_nonpond_S , TOUTES_COULEURS , OUI ) ;

/* Ecrire graphe_AR. */

      (void)printf( "%s n'est plus anti-réflexif : %d\n\n" , "G_5_nonpond_S" ,
		    graphe_AR( G_5_nonpond_S ) ) ;
      (void)printf( "Le graphe %s est anti-réflexif : %d\n\n" , "G_6_nonpond_DAG" ,
		    graphe_AR( G_6_nonpond_DAG ) ) ;

/* Ecrire graphe_ARAS. */

      (void)printf( "Graphe %s anti-réflexif et anti-symétrique : %d\n\n" ,
		    "G_6_nonpond_DAG" , graphe_ARAS( G_6_nonpond_DAG ) ) ;

/* Ecrire degre_graphe pour des graphes symétriques. */

      (void)printf( "Le degré du graphe symétrique %s fermé réflexivement : %d\n\n" ,
		    "G_5_nonpond_S" , degre_graphe( G_5_nonpond_S ) ) ;

/* Ecrire connexe_vague. */

      (void)printf( "Le graphe %s :\n" , "G_9_nonpond_S" ) ;
      imprime_graphe( G_9_nonpond_S , TOUT_NOIR , OUI ) ;
      (void)printf( "Les étapes de propagation des vagues dans %s :\n" ,
		    "G_9_nonpond_S" ) ;
      nombre_composantes = connexe_vague( G_9_nonpond_S , OUI ) ;
      (void)printf( "Il y a %d composantes connexes.\n\n" , nombre_composantes ) ;

/* Ecrire est_un_arbre. */

      (void)printf( "Le graphe %s est un arbre : %d\n" ,
		    "G_9_arbre" , est_un_arbre( G_9_arbre ) ) ;
      imprime_graphe( G_9_arbre , TOUT_NOIR , NON ) ;
      unset_arete( G_9_arbre ,  Sb , Sd ) ;
      set_arete( G_9_arbre , Sb , Sg , NOIR ) ;
      (void)printf( "Ce graphe est un arbre : %d\n" , est_un_arbre( G_9_arbre ) ) ;
      imprime_graphe( G_9_arbre , TOUT_NOIR , NON ) ;

/* Ecrire parcours_profondeur_niveaux. */

      (void)printf( "Le graphe %s avec les distances depuis %d :\n" ,
		    "G_9_nonpond_NS" , Sa ) ;
      parcours_profondeur_niveaux( G_9_nonpond_NS , Sa ) ;
      imprime_graphe( G_9_nonpond_NS , TOUT_NOIR , NON ) ;

/* Ecrire tri_topologique. */ 

      (void)printf( "Le tri topologique de %s donne :\n" , "G_6_nonpond_DAG" ) ;
      tri_topologique( G_6_nonpond_DAG ) ;
      imprime_graphe( G_6_nonpond_DAG , TOUTES_COULEURS , OUI ) ;

      (void)printf( "Le tri topologique de %s donne :\n" , "G_8_ARAS_non_DAG" ) ;
      tri_topologique( G_8_ARAS_non_DAG ) ;
      imprime_graphe( G_8_ARAS_non_DAG , TOUTES_COULEURS , OUI ) ;

/* Ecrire multiplie. */

      (void)printf( "La multiplication matricielle donne ces étapes pour %s :\n" ,
		    "G_8_nonpond_S" ) ;
      multiplie( G_8_nonpond_S ) ;
      imprime_graphe_etapes( G_8_nonpond_S , DERNIERE_COULEUR , OUI ) ;

/* Ecrire floyd-warshall. */

      (void)printf( "Floyd-Warshall donne ces étapes pour %s :\n" ,
		    "G_8_nonpond_S_bis" ) ;
      floyd_warshall( G_8_nonpond_S_bis ) ;
      imprime_graphe_etapes( G_8_nonpond_S_bis , DERNIERE_COULEUR , OUI ) ;

/* Ecrire multiplie_pondere. */

      (void)printf( "La multiplication donne ces étapes pour %s pondéré :\n" ,
		    "G_6_pond_NS" ) ;
      multiplie_pondere( G_6_pond_NS ) ;
      imprime_graphe_etapes( G_6_pond_NS , DERNIERE_COULEUR , OUI ) ;

/* Ecrire floyd_warshall_pondere. */

      (void)printf( "Floyd-Warshall donne ces étapes pour %s pondéré :\n" ,
		    "G_6_pond_NS_bis" ) ;
      floyd_warshall_pondere( G_6_pond_NS_bis ) ;
      imprime_graphe_etapes( G_6_pond_NS_bis , DERNIERE_COULEUR , OUI ) ;

/* Ecrire dijkstra. */

      (void)printf( "L'algorithme de Dijkstra donne ce graphe pour le départ %d :\n" ,
		    Sa ) ;
      dijkstra( Sa , G_8_pond_NS , table_predecesseurs ) ;
      imprime_graphe( G_8_pond_NS , TOUTES_COULEURS , OUI ) ;

      (void)printf( "L'algorithme de Dijkstra donne ce graphe pour le départ %d :\n" ,
		    Sa ) ;
      dijkstra( Sa , G_8_pond_NS_bis , table_predecesseurs ) ;
      imprime_graphe( G_8_pond_NS_bis , TOUTES_COULEURS , OUI ) ;

/* Ecrire dijkstra_maximise_le_min. */

      (void)printf( "Dijkstra qui maximise le minimum pour le départ %d :\n" ,
		    Sa ) ;
      dijkstra_maximise_le_min( Sa , G_8_pond_NS_ter , table_predecesseurs ) ;
      imprime_graphe( G_8_pond_NS_ter , TOUTES_COULEURS , OUI ) ;

/* Compléter ford_et_fulkerson. */

      ford_et_fulkerson( ) ;

     }

/* ------------------------------------------------------------ */

/* Après avoir déroulé les exemples, on lit les graphes prédéfinis pour leur
   appliquer les tâches prévues et les libérer avant de quitter le programme. */

int main ( void )
    {exemples( ) ; 

     lire_les_graphes( ) ;

     ma_contribution( ) ;

     liberer_les_graphes( ) ;

     (void)printf( "\nBye !\n" ) ;
     return( 0 ) ;
    }

/* ------------------------------------------------------------ */
