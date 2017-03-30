/* Marc Gengler - Polytech Marseille - Janvier 2016 */

/* ------------------------------------------------------------ */

/* N est le nombre maximal de sommets de tout graphe géré. */

#define N 12

/* ------------------------------------------------------------ */

#define OUI 1
#define NON 0

/* ------------------------------------------------------------ */

/* Le sommet a-t-il déjà été visité ou non ? */

#define SEC 0
#define MOUILLE 1

/* ------------------------------------------------------------ */

/* Le nombre de couleurs et les noms des couleurs. */

#define NOMBRE_COULEURS 12

#define NOIR 0
#define ROUGE 1
#define VERT 2
#define BLEU 3
#define JAUNE 4
#define ORANGE 5
#define VIOLET 6
#define OR 7
#define MAGENTA 8
#define GRIS 9
#define BLEUCIEL 10
#define VERTCLAIR 11

/* ------------------------------------------------------------ */

/* Des options pour l'affichage des couleurs des arcs et arêtes. */

#define TOUT_NOIR - 1
#define TOUTES_COULEURS - 2
#define DERNIERE_COULEUR - 3

/* ------------------------------------------------------------ */

/* Des alias pour les numéros des sommets. */

#define Sa 0
#define Sb 1
#define Sc 2
#define Sd 3
#define Se 4
#define Sf 5
#define Sg 6
#define Sh 7
#define Si 8
#define Sj 9
#define Sk 10
#define Sl 11

/* ------------------------------------------------------------ */

/* Les limites pour les pondérations acceptées. */

#define POIDS_MIN - 1000
#define POIDS_MAX 1000
#define PLUS_INF 10000
#define MOINS_INF - 10000

/* ------------------------------------------------------------ */

/* Le type "t_info" :

   Les informations associées à un arc sont, dans l'ordre,

   - le champ "défini" qui dit si, OUI ou NON, l'arc existe,

   - le champ "pondere" qui dit si, OUI ou NON, l'arc possède un poids,

   - le champ "flot" qui dit si, OUI ou NON, l'arc pondéré est l'arc
     d'un graphe de flot,

   - le champ "poids" qui donne le poids l'arc, si l'arc appartient
     à un graphe pondéré ou un graphe de flot,

   - le champ "capacite" qui donne le poids maximal, si l'arc figure
     dans un graphe de flot et

   - le champ "couleur" qui donne la couleur de l'arc. */

typedef struct
	{int defini ;
         int pondere ;
         int flot ;
	 int poids ;
         int capacite ;
	 int couleur ;
	}
t_info ;

/* ------------------------------------------------------------ */

/* Les types t_gra_struct et * t_gra :

   La structure d'un graphe. On y trouve, dans l'ordre,

   - le champ "taille" qui donne le nombre de sommets du graphe considéré,

   - le champ "pondere" qui dit si, OUI ou NON, le graphe est pondéré,

   - le champ "flot" qui dit si, OUI ou NON, le graphe est un graphe de
     flot, donc forcément pondéré,

   - le champ "poids_min" qui donne le poids minimal d'un arc ou une arête,
     hormis MOINS_INF, pour peu que le graphe soit pondéré,

   - le champ "poids_max" qui donne le poids maximal, hormis PLUS_INF, pour
     peu que le graphe soit pondéré,

   - la matrice carrée bi-dimensionnelle des informations associées aux arcs,
     c'est-à-dire le type t_info,

   - le vecteur "etatsommet" des états des sommets, à savoir SEC ou MOUILLE,

   - le vecteur "sommetpondere" qui dit, pour chaque sommet, si, OUI ou NON,
     il porte un poids et

   - le vecteur "sommetpoids" des éventuels poids.

   Les deux types définis ici sont "t_gra_struct", qui est utilisé seulement
   par malloc et "t_gra" qui est le pointeur sur le graphe utilisé partout. */

typedef struct
	{int taille ;
         int pondere ;
         int flot ;
         int poids_min ;
         int poids_max ;
	 t_info cases[ N ] [ N ] ;
	 int etatsommet[ N ] ;
         int sommetpondere[ N ] ;
	 int sommetpoids[ N ] ;
	}
t_gra_struct , * t_gra ;

/* ------------------------------------------------------------ */
