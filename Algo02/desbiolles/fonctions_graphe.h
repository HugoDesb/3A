/* Marc Gengler - Polytech Marseille - Janvier 2016 */

/* Ce fichier donne les variables globales et les prototypes que
   l'utilisateur est sensé connaître. */

/* ------------------------------------------------------------ */

/* Ces variables globales contiennent les graphes utilisés pour
   illustrer les fonctionnalités dans le fichier ma_contribution.c .
   Les graphes en question sont lus via la procédure lire_les_graphes
   et libérés à la fin de l'exécution via liberer_les_graphes.
   L'utilisateur peut donc parfaitement ignorer leurs noms. */

t_gra G_5_nonpond_S ;
t_gra G_6_nonpond_DAG ;
t_gra G_8_ARAS_non_DAG ;
t_gra G_9_nonpond_S ;
t_gra G_9_arbre ;
t_gra G_9_nonpond_NS ;
t_gra G_8_nonpond_S ;
t_gra G_8_nonpond_S_bis ;
t_gra G_6_pond_NS ;
t_gra G_6_pond_NS_bis ;
t_gra G_8_pond_NS ;
t_gra G_8_pond_NS_bis ;
t_gra G_8_pond_NS_ter ;
t_gra G_9_flot ;

/* ------------------------------------------------------------ */

int min ( int a , int b ) ;

int max ( int a , int b ) ;

/* ------------------------------------------------------------ */

/* Inutiles à l'utilisateur, elles servent seulement au programme principal. */

void lire_les_graphes ( void ) ;

void liberer_les_graphes ( void ) ;

/* ------------------------------------------------------------ */

/* definir_couleur permet de définir la couleur actuelle et couleur_suivante
   passe à la couleur suivante, d'après la liste des couleurs donnée dans
   constantes.h . la_couleur retourne la couleur active. */

void definir_couleur ( int couleur ) ;

void couleur_suivante ( void ) ;

int la_couleur ( void ) ;

/* ------------------------------------------------------------ */

/* set_arc crée un arc dans le graphe en lui donnant une couleur.
   set_arete crée les deux arcs, dans un sens et dans l'autre.
   Ces fonctions ne s'appliquent que sur un graphe non pondéré.

   set_arc_pondere et set_arete_pondere sont les versions pondérées des
   mêmes fonctions. Elles s'appliquent uniquement sur des graphes pondérés.

   Ces quatre fonctions écrasent toute information antérieure.

   Le prédicat poids_ok permet de tester si un poids donné est
   acceptable ou non pour le graphe ? */

void set_arc ( t_gra graphe , int i , int j , int couleur ) ;

void set_arete ( t_gra graphe , int i , int j , int couleur ) ;

void set_arc_pondere ( t_gra graphe , int i , int j , int poids , int couleur ) ;

void set_arete_pondere ( t_gra graphe , int i , int j , int poids , int couleur ) ;

int poids_ok ( t_gra graphe , int poids ) ;

/* ------------------------------------------------------------ */

/* get_arc et get_arete sont des prédicats qui disent si, OUI ou NON,
   l'arc ou l'arête existe dans le graphe ? get_arete est vraie
   seulement si les deux arcs existent. */

int get_arc ( t_gra graphe , int i , int j ) ;

int get_arete ( t_gra graphe , int i , int j ) ;

/* ------------------------------------------------------------ */

/* poids_arc rend le poids d'un arc d'un graphe pondéré. ajoute_poids_arc
   ajoute un poids à l'arc. Celui-ci doit exister et le nouveau poids
   doit vérifier toutes les contraintes. capacite_arc rend la capacité
   d'un arc de graphe de flot. couleur_arc retourne la couleur d'un arc
   et couleur_arete celle d'une paire d'arcs tête-bêche et de même
   couleur. set_couleur_arc permet de changer la couleur d'un arc existant. */

int poids_arc ( t_gra graphe , int i , int j ) ;

void ajoute_poids_arc ( t_gra graphe , int i , int j , int poids ) ;

int couleur_arc ( t_gra graphe , int i , int j ) ;

int capacite_arc ( t_gra graphe , int i , int j ) ;

int couleur_arete ( t_gra graphe , int i , int j ) ;

void set_couleur_arc ( t_gra graphe , int i , int j , int couleur ) ;

/* ------------------------------------------------------------ */

/* Ces fonctions suppriment un arc ou une arête. */

void unset_arc ( t_gra graphe , int i , int j ) ;

void unset_arete ( t_gra graphe , int i , int j ) ;

/* ------------------------------------------------------------ */

/* tremper positionne un marqueur sur un sommet. secher l'enlève et
   mouille teste si, OUI ou NON, le marqueur est positionné ?

   Un sommet dont le marqueur est positionné sera affiché avec une "*"
   accollée au nom du sommet, comme "a*" par exemple. */

void tremper ( t_gra graphe , int s ) ;

void secher (t_gra graphe , int s ) ;

int mouille (t_gra graphe , int s ) ;

/* ------------------------------------------------------------ */

/* sommet_set_poids permet d'associer un poids à un sommet. La procédure
   sommet_unset_poids supprime l'information de poids. Le prédicat
   sommet_possede_poids dit si, OUI ou NON, le sommet possède un poids.
   sommet_get_poids retourne le poids d'un sommet pondéré.

   Le sommet "a" pondéré de la valeur 25 sera affiché comme "a / 25".

   Le tri_topologie attribue des poids aux sommets, de même que
   l'algorithme de Dijkstra. */ 

void sommet_set_poids ( t_gra graphe , int s , int poids ) ;

void sommet_unset_poids ( t_gra graphe , int s ) ;

int sommet_possede_poids ( t_gra graphe , int s ) ;

int sommet_get_poids ( t_gra graphe , int s ) ;

/* ------------------------------------------------------------ */

/* nouveau_graphe alloue un nouveau graphe non pondéré à n sommets
   et retourne le pointeur. Aucun arc n'est défini.

   nouveau_graphe_pondere alloue un nouveau graphe pondéré à n sommets
   et retourne le pointeur. Aucun arc n'est défini. Les futurs poids
   des arcs et arêtes devront se situer entre poids_min et poids_max,
   à moins de valoir PLUS_INF et MOINS_INF. Ces deux valeurs représentent
   le  +infini et le -infini. */

t_gra nouveau_graphe ( int n ) ;

t_gra nouveau_graphe_pondere ( int n , int poids_min , int poids_max ) ;

t_gra nouveau_graphe_flot ( int n , int poids_max ) ;

void copie_graphe ( t_gra graphe , t_gra nouveau ) ;

/* ------------------------------------------------------------ */

void memorise_forme_graphe_flot ( t_gra graphe ) ;

void oublie_forme_graphe_flot ( void ) ;

/* ------------------------------------------------------------ */

/* taille_graphe rend le nombre de sommets du graphe. graphe_pondere dit
   si, OUI ou NON, le graphe est pondéré ? graphe_flot dit si, OUI ou
   NON, un graphe pondéré est un graphe de flot. */

int taille_graphe ( t_gra graphe ) ;

int graphe_pondere ( t_gra graphe ) ;

int graphe_flot ( t_gra graphe ) ;

/* ------------------------------------------------------------ */

/* Les fonctions d'affichage du graphe (cf. la présentation générale
   des TP). Ces fonctions servent à imprimer les graphes. */

/* imprime_graphe imprime le graphe en utilisant 3 options de
   couleur possibles. Ce sont

   - TOUT_NOIR, qui ne nécessite aucun commentaire,

   - TOUTES_COULEURS, qui est également triviale et

   - DERNIERE_COULEUR, qui affiche la seule dernière couleur (au sens de la
     suite des couleurs dans constantes.h) et qui transforme les autres
     couleurs en NOIR. Ceci sert donc, en autre, à mettre en exergue les
     modifications dues à la dernière étape d'un algorithme.

   Si graphe est pondéré chaque arc ou arête porte un poids. S'il s'agit
   d'un graphe de flot, chaque arc porte une annotation qui sera
   de la forme "13 / 35", par exemple.

   Le paramètre gauche_droite dit si le placement des sommets doit se faire
   en privilégiant une orientation de gauche à droite, plutôt que verticale. */

void imprime_graphe ( t_gra graphe , int info_couleur , int gauche_droite ) ;

/* imprime_graphe_limite se limite à imprimer les arcs et arêtes dont
   la couleur n'excède pas la valeur limite. D'autres arcs et arêtes,
   bien que peut-être définies dans le graphe, ne sont pas affichés.
   Les options d'affichage restent les mêmes que pour imprime_graphe. */

void imprime_graphe_limite ( t_gra graphe , int info_couleur ,
			     int limite , int gauche_droite ) ;

/* imprime_graphe_etapes permet d'afficher toutes les étapes d'un calcul.
   Si chaque étape du calcul choisit une nouvelle couleur, la fonction
   imprime_graphe_etapes appelle la fonction précédente pour chaque couleur
   du graphe. On peut ainsi observer la progression des calculs. */

void imprime_graphe_etapes ( t_gra graphe , int info_couleur , int gauche_droite ) ;

/* ------------------------------------------------------------ */

/* Une gestion classique des files et leur type de données. */

typedef struct mm_file
        {int sommet ;
         struct mm_file * suiv ;
        }
struct_file , * t_file ;

t_file cree_file_vide ( void ) ;

int est_file_vide ( t_file file ) ;

t_file insere_file ( int sommet , t_file file ) ;

int tete_file ( t_file file ) ;

t_file supprime_tete_file ( t_file file ) ;

/* ------------------------------------------------------------ */
