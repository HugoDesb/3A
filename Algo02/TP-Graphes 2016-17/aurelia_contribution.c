/**
* Polytech Marseille
* Case 925 - 163, avenue de Luminy
* 13288 Marseille CEDEX 9
*
* Ce fichier est l'oeuvre d'eleves de Polytech Marseille et de Marc Gengler, professeur à Polytech Marseille.
* Il ne peut etre reproduit, utilise ou modifie sans l'avis express de ses auteurs.
*/

/**
* @author BINETTI Aurelia <aurelia.binetti@etu.uni-amu.fr>
* @version 2.3 01/05/2016
* @todo 
* @bug Rien
*/

/**
* @file ma_contribution.c
* @brief Exercice sur les graphes
* Fichier En C
*/




/* Marc Gengler - Polytech Marseille - Janvier 2016 */

/* ------------------------------------------------------------ */

/* Les prototypes. Voir plus loin pour leurs descriptions.

   Toutes les fonctions comporteront les assert de rigueur. */

int graphe_non_oriente ( t_gra graphe ) ;

void fermeture_reflexive ( t_gra graphe ) ;

void fermeture_reflexive_pondere ( t_gra graphe , int poids ) ;

int graphe_AR ( t_gra graphe ) ;

int graphe_ARAS ( t_gra graphe ) ;

int degre_graphe ( t_gra graphe ) ;

int cherche_sommet_sec ( t_gra graphe ) ;
int connexe_vague ( t_gra graphe , int view ) ;

int nombre_aretes ( t_gra graphe ) ;
int est_un_arbre ( t_gra graphe ) ;

void parcours_profondeur_niveaux_rec ( t_gra graphe , int sommet , int niveau ) ;
void parcours_profondeur_niveaux ( t_gra graphe , int depart ) ;

int cherche_sommet_sec_et_predecesseurs_mouilles ( t_gra graphe ) ;
void tri_topologique ( t_gra graphe ) ;

void multiplie ( t_gra graphe ) ;

void floyd_warshall ( t_gra graphe ) ;

void multiplie_pondere ( t_gra graphe ) ;

void floyd_warshall_pondere ( t_gra graphe ) ;

int verifie_ponderation ( t_gra graphe ) ;
int cherche_sec_sommet_min ( t_gra graphe ) ;
void relax ( t_gra graphe , int table_predecesseurs[ ] , int pred , int sommet ) ;
void dijkstra ( int depart , t_gra graphe , int table_predecesseurs[ ] ) ;

int cherche_sec_sommet_max ( t_gra graphe ) ;
void relax_maximise_le_min ( t_gra graphe , int table_predecesseurs[ ] ,
			     int pred , int sommet , int depart ) ;
void dijkstra_maximise_le_min ( int depart , t_gra graphe , int table_predecesseurs[ ] ) ;

void calcule_residuel ( t_gra graphe_flot , t_gra graphe_residuel , int i , int j ) ;
void adapte_flot ( t_gra graphe_flot , int depuis , int vers , int valeur ) ;
void ford_et_fulkerson ( void ) ;

/* ------------------------------------------------------------ */

/* Le prédicat graphe_non_oriente dit si, OUI ou NON, le graphe fourni
   est symétrique ? Le graphe peut être pondéré ou non. Un graphe
   pondéré est symétrique si et seulement si les arcs ( a , b ) et
   ( b , a ) possèdent le même poids. */

int graphe_non_oriente ( t_gra graphe )
    {
			int i, j, poidSensNormal, poidSensInverse;
			int taille = taille_graphe(graphe);
			for (i = 0; i < taille; i++)
			{
				for (j = 0; j < taille; j++)
				{
					if ((get_arete(graphe, i, j)) && (graphe_pondere(graphe)))
					{
						poidSensNormal = poids_arc(graphe, i, j);
						poidSensInverse = poids_arc(graphe, j, i);
						if(poidSensNormal != poidSensInverse) return NON;
					}
					else if(get_arc(graphe, i, j))
					{
						if (!get_arc(graphe, j,i)) return NON;
					}
				}
			}
		 return OUI;
    }

/* ------------------------------------------------------------ */

/* La procédure fermeture_reflexive rajoute toutes les arêtes de la
   forme ( s , s ) manquantes, c'est-à-dire les arêtes d'un sommet s
   vers lui-même. Les nouvelles arêtes seront de la couleur donnée
   par la_couleur( ). Le graphe ne doit pas être pondéré. */

void fermeture_reflexive ( t_gra graphe )
     {
			 int i;
			 int taille = taille_graphe(graphe);
			 if (!graphe_pondere(graphe))
			 {
			 		for (i = 0; i < taille; i++)
			 		{
				 		if(!get_arete(graphe, i, i))
				 		{ 
				 			set_arete(graphe, i, i, la_couleur());
				 		}
     	 			}
			 }
		  }

/* ------------------------------------------------------------ */

/* La procédure fermeture_reflexive_pondere réalise la même opération
   que la procédure précédente, à ceci près qu'elle s'applique à un
   graphe pondéré et donne en conséquence un poids aux nouvelles arêtes.
   On vérifiera que le graphe est bien pondéré et que le poids donné
   est accepté par le graphe. */

void fermeture_reflexive_pondere ( t_gra graphe , int poids )
     {
			 int i;
			 int taille = taille_graphe(graphe);

			 if (graphe_pondere(graphe) && poids_ok(graphe, poids))
			 {
			 		 for (i = 0; i < taille; i++)
			 	 	 {
			 		 			if(!get_arete(graphe, i, i))
								{
									set_arete_pondere(graphe, i, i, poids, la_couleur());
								}
			 		 }
		   }
     }

/* ------------------------------------------------------------ */

/* Le prédicat graphe_AR dit si, OUI ou NON, le graphe fourni est
   anti-réflexif, c'est-à-dire ne possède aucune arête de la forme
   ( s , s ) ? Elle s'applique aussi bien aux graphes pondérés que
   non pondérés, orientés ou non. */

int graphe_AR ( t_gra graphe )
    {
			int i;
			int taille = taille_graphe(graphe);

			for (i = 0; i < taille; i++)
			{
				if (get_arete(graphe, i, i))
				{
				 return NON;
				}
			}
			return OUI;
    }

/* ------------------------------------------------------------ */

/* Le prédicat graphe_ARAS dit si, OUI ou NON, le graphe fourni
   est à la fois anti-réflexif et anti-symétrique ? Le graphe
   peut être pondéré ou non. */

int graphe_ARAS ( t_gra graphe )
    {
		 int i, j;
 		 int taille = taille_graphe(graphe);

		 if(!graphe_AR(graphe))
		 	{ 
		 		return NON;
		 	}
		 else
		 {
			 for (i = 0; i < taille; i++)
			 {
			 	for (j = 0; j < taille; j++)
				{
			 				 if (get_arc(graphe, i, j))
			 			 	 {
			 						if (get_arc(graphe, j, i)) return NON;
			 				 }
		    }
			}
		 }

		 return OUI;
    }

/* ------------------------------------------------------------ */

/* La fonction degre_graphe retourne le degré d'un graphe symétrique
   pondéré, ou non. La fonction vérifie explicitement que le graphe
   fourni est bien symétrique. On opte pour le choix normal qui
   consiste à dire qu'une arête réflexive de la forme ( a , a )
   compte pour 2 dans le degré du sommet a . */

int degre_graphe ( t_gra graphe )
    {
			int i, j, cpt;
			int max = 0;
			int taille = taille_graphe(graphe);

     if (!graphe_non_oriente(graphe))
		 {
			 printf("Graphe non symétrique\n");
			 return 0;
		 }
		 for (i = 0; i < taille; i++)
		 {
			 	cpt = 0;
				if (get_arete(graphe, i, i))
				{
					cpt = cpt + 1;
				}
		 		for (j = 0; j < taille; j++)
				{
					if (get_arete(graphe, i, j))
					{
		 				cpt = cpt + 1;
		 			}
		 		}
				if (max < cpt) max = cpt;
		 }
		 return max;
    }

/* ------------------------------------------------------------ */

/* La fonction connexe_vague s'applique aux seuls graphes non orientés.
   Elle détermine les composantes connexes en lançant des "vagues". La
   fonction rend le nombre de composantes connexes trouvées.

   Tant que l'on trouve un sommet sec "u", on lance une vague depuis "u".
   La fonction-prédicat cherche_sommet_sec sert à chercher un tel sommet.
   Si elle en trouve un, elle en retourne le numéro, c'est-à-dire un
   nombre positif. Si elle n'en trouve plus, elle retourne la valeur - 1 .

   La "vague" va mouiller chaque sommet rencontré. Les arêtes seront de
   couleurs différentes au fur et à mesure que l'on s'éloigne du sommet
   de départ, en suivant l'ordre des couleurs. On pourra donc savoir, à
   partir de la	 couleur d'une arête, s'il a déjà été visitée ou non.

   De plus, chaque sommet recevra comme poids le numéro d'étapes nécessaires
   pour le toucher la première fois. C'est d'ailleurs le même numéro que
   celui de l'arête qui l'atteint en premier. On calcule donc de surcroît
   les plus courts chemins du point de départ au sommet considéré.

   connexe_vague affichera, suivant l'état de view, donc OUI ou NON, le
   graphe et la progression de la vague pour chaque étape. Voir aussi
   le fichier de réponse type "reponse_de_refence".

   Cette fonctionnalité nécessite un parcours en largeur et va s'appuyer
   sur fonctions de gestion de file fournies dans fonctions.h .

   A la fin, tous les sommets sont à nouveau séchés.

   connexe_vague est un peu plus difficile à implanter que d'autres et on
   peut préférer résoudre d'abord certaines des questions qui suivent. */

int cherche_sommet_sec ( t_gra graphe )
    {
				int i = 0;
				int taille = taille_graphe(graphe);

				for (i = 0; i < taille; i++)
				{
					if (!mouille(graphe, i)) return i;
				}
				return -1;
    }

int connexe_vague ( t_gra graphe , int view )
    {
			int u, v, i, poidsu;
			int nb_connexe;
			int taille;
			t_file file, file2;

			taille = taille_graphe(graphe);
			file = cree_file_vide();
			file2 = cree_file_vide();
			u = cherche_sommet_sec(graphe);
			nb_connexe = 0;
			poidsu = 0;

			assert(graphe_non_oriente(graphe));

			while( u != -1)
			{
				nb_connexe = nb_connexe + 1;
				tremper(graphe, u);
				sommet_set_poids(graphe, u, poidsu);
				poidsu = 1;

				
				file  = insere_file(u, file);

				while(!est_file_vide(file))
				{
					
					v = tete_file(file);
					file = supprime_tete_file(file);

					for (i = 0; i < taille; i++)
					{
						if (get_arete(graphe, i, v))
						{
							if (!mouille(graphe, i))
							{
								file2 = insere_file(i, file2);
								tremper(graphe, i);
							}
							
							if ((sommet_possede_poids(graphe, i) && sommet_get_poids(graphe, i) > poidsu) || !sommet_possede_poids(graphe, i))
							{
								sommet_set_poids(graphe, i, poidsu);
							}
							set_couleur_arc(graphe, v, i, la_couleur());
						}
					}

					if(est_file_vide(file))
					{
						if (!est_file_vide(file2))
						{
							if(view) imprime_graphe(graphe, TOUTES_COULEURS, la_couleur());
							couleur_suivante();
							poidsu = poidsu + 1;
						}
						file = file2;
						file2 = cree_file_vide();
					}
				}
				u = cherche_sommet_sec(graphe);
				poidsu = 0;
				definir_couleur(ROUGE);
			}
			
			for (i = 0; i < taille; i++) secher(graphe, i);

			return nb_connexe;
	  }
/* ------------------------------------------------------------ */

/* Ecrire le prédicat est_un_arbre qui s'applique aux seuls graphes
   anti-réflexifs et non orientés et qui dit si, OUI ou NON, le graphe
   est un arbre. Il suffira de compter le nombre d'arêtes et de vérifier
   que le graphe possède exactement une seule composante connexe. */

int nombre_aretes ( t_gra graphe )
    {
			int i, j, cpt=0;
			int taille = taille_graphe(graphe);

			for(i=0; i < taille; i++)
			{
				if (get_arete(graphe,i,i)) cpt++;

				for (j = 0; j < taille; j++)
				{
					if (get_arete(graphe,i,j)) cpt++;
				}
			}
			return cpt/2;
    }

int est_un_arbre ( t_gra graphe )
    {
			int taille = taille_graphe(graphe);

			if (graphe_AR(graphe) && graphe_non_oriente(graphe) && nombre_aretes(graphe) == (taille-1) && connexe_vague(graphe, 0) == 1)
			{
				return OUI;
			}
			return NON;
		}

/* ------------------------------------------------------------ */

/* parcours_profondeur_niveaux parcourt un graphe depuis le sommet
   de départ en utilisant un parcours en profondeur. Pour éviter de
   boucler, on utilisera les états SEC et MOUILLE des sommets. Les
   appels récursifs incrémentent le niveau à chaque appel et tout
   sommet sec recevra comme poids le niveau le moins élevé avec
   lequel il a été touché. Cette procédure calcule donc au
   passage les plus courts chemins depuis le sommet de départ, bien
   que l'algorithme ne soit pas, et de loin, le plus efficace.

   parcours_profondeur_niveaux initialise les poids des sommets et
   parcours_profondeur_niveaux_rec effectue le parcours. */

void parcours_profondeur_niveaux_rec ( t_gra graphe , int sommet , int niveau )
     {
			int voisin , taille = taille_graphe(graphe);
	     if (!mouille(graphe , sommet))
		   {
			  	if ( niveau < sommet_get_poids( graphe , sommet ) )
			  	{
			  		 sommet_set_poids( graphe , sommet , niveau );
			  	}
		      tremper(graphe , sommet);
		      for (voisin = 0; voisin < taille; voisin++)
		      {
					  if (get_arc(graphe , sommet , voisin))
					  {
					  	 parcours_profondeur_niveaux_rec(graphe, voisin, niveau+1);
					  }
			  }
			 secher(graphe , sommet);
		   }
     }

void parcours_profondeur_niveaux ( t_gra graphe , int depart )
     {
			 int sommet, taille = taille_graphe(graphe);
			 for (sommet = 0; sommet < taille; sommet++)
			 {
			 	if(sommet != depart) 
			 	{
			 		 sommet_set_poids(graphe, sommet, PLUS_INF);
			 	}
				else
				{ 
					sommet_set_poids(graphe, sommet, 0);
				}
			 }
			 parcours_profondeur_niveaux_rec(graphe, depart, 0);
	   }

/* ------------------------------------------------------------ */

/* tri_topologique calcule une valuation "topologique" pour les sommets
   d'un graphe qui est un DAG. On peut consulter l'énoncé du premier TD
   pour les définitions. La vérification de la propriétés ARAS ne pose
   pas de problème. La vérification de l'absence de circuits est plus
   délicate et on ne la fera pas sous forme d'une recherche de circuits.

   L'algorithme mis en application est celui vu en TD. Il consiste à dire :

   Tantque tous les sommets ne portent pas une valeur

	- Chercher un sommet "u" dont tous les prédécesseurs possèdent
	  déjà une valeur. Chaque sommet est mouillé au moment où il reçoit
          une valeur. L'objectif peut donc être réalisé à travers la
	  fonction cherche_sommet_sec_et_predecesseurs_mouilles qui
	  retourne un tel sommet "u". Le premier TD a montré qu'un tel
	  choix est toujours possible, si le graphe ne possède pas de
	  circuit.

	- Donner à "u" une valeur plus grande que celle de tous ses
	  prédécesseurs. C'est trivial. De plus, on va colorier les
	  arcs.

   Le fait que cherche_sommet_sec_et_predecesseurs_mouilles ne trouve
   pas de sommet permet donc de conclure que le graphe possède des
   circuits. Dans ce cas, la fonction donne un message clair et la
   suite du calcul est abandonnée. Le graphe rendu ne sera donc
   que partiellement valué. */

int cherche_sommet_sec_et_predecesseurs_mouilles ( t_gra graphe )
    {
			int taille, u, check, i;
			taille = taille_graphe(graphe);
			u = 0;

			while(u<taille)
			{
	
				if(!mouille(graphe, u))
				{
					check = 1;
					
					for ( i = 0; i < taille; i++)
					{
						if (get_arc(graphe, i, u))
						{
							check = check && (mouille(graphe, i));
						}
					}
					if(check) return u;
				}
				u++;
			}
			return -1;
    }

void tri_topologique ( t_gra graphe )
     {
			 int taille, cptsommet, pdsu, i, j, k;
			 cptsommet = 0;
			 taille = taille_graphe(graphe);

			 
			 definir_couleur(ROUGE);

			 int u = cherche_sommet_sec_et_predecesseurs_mouilles(graphe);

			 while(u != -1)
			 {
				 pdsu = -1;
				 for (i = 0; i < taille; i++)
				 {
				 	if(get_arc(graphe, i, u) && sommet_get_poids(graphe, i) > pdsu)
				 	{
						pdsu = sommet_get_poids(graphe, i);
					}
				 }

				 
				 tremper(graphe, u);
				 sommet_set_poids(graphe, u, pdsu+1);

				
				 for (j = 0; j < pdsu+1; j++)
				 {
				 	couleur_suivante();
				 }

				 
				 for (k = 0; k < taille; k++)
				 {
				 	if(get_arc(graphe, u, k))
				 	{ 
				 		set_couleur_arc(graphe, u, k, la_couleur());
				 	}
				 }

				 definir_couleur(ROUGE);

				 cptsommet = cptsommet + 1;
				 u = cherche_sommet_sec_et_predecesseurs_mouilles(graphe);
			 }

			
			 if (cptsommet != taille) printf("LE GRAPHE COMPORTE DES CIRCUITS !\n");
     }

/* ------------------------------------------------------------ */

/* On considère un graphe non pondéré et on souhaite calculer les plus
   courts chemins au sens du "nombre d'étapes", c'est-à-dire du "nombre
   arcs ou arêtes à traverser". Le graphe peut être orienté ou non.

   On partira d'une matrice M = M^1 qui est fermée réflexivement. La
   fermeture réflexive est une des questions qui précèdent.

   Il s'agira ensuite de calculer pour tous les sommets u et v :

	M^(2*i) ( u , v ) = max_k  M^i ( u , k ) * M^i ( k , v )

   où k parcourt tous les sommets.

   Il faudra calculer M^k, avec k plus grand ou égal au diamètre maximal
   du graphe, c'est-à-dire taille_graphe( graphe ) - 1 . On effectuera
   les optimisations de calcul vues en TD, à savoir on évitera de
   recalculer les éléments de la diagonale, ainsi que toute entrée
   qui est déjà à un.

   Pour chaque multiplication de matrice on choisira une autre couleur
   pour les arcs et arêtes introduits. Voir "reponse_de_reference".

   Il faut, à tout moment, deux matrices en mémoire, à savoir M^i et
   M^(2*i) que l'on est en train de calculer. A l'étape suivante, la
   dernière matrice M^(2*i) va jouer le rôle de M^i. On peut recourir
   à la procédure copie_graphe qui copie des graphes et pour laquelle
   l'appel "copie_graphe( graphe , nouveau ) ;" a pour effet de
   recopier "graphe" en "nouveau". */

void multiplie ( t_gra graphe )
     {
			 int taille = taille_graphe(graphe);
			 int i, j, maxi, k = 0, cpt = 1;
			
			 t_gra graphest = nouveau_graphe(taille);
			 definir_couleur(NOIR);
			 
			 for (i = 0; i < taille; i++)
			 {
			 	for (j = 0; j < taille; j++)
				{
			 		if (i != j && get_arc(graphe, i, j))
			 		{
						set_couleur_arc(graphe, i, j, la_couleur());
					}
			 	}
			 }

		 couleur_suivante();
		 fermeture_reflexive(graphe);
		 couleur_suivante();
		 copie_graphe(graphe, graphest);

		 while(cpt < taille-1)
		 {
			 for (i = 0; i < taille; i++)
			 {
			 	for (j = 0; j < taille; j++)
				{
			 		
					if (i !=j && !get_arc(graphe, i, j))
					{
						maxi = 0;
						for (k = 0; k < taille; k++)
						{
							maxi = max(get_arc(graphest, i, k)*get_arc(graphest, k, j), maxi);
						}
						
						if (maxi) 
						{
							set_arc(graphe, i, j, la_couleur());
						}
					}
			 	}
			 }
			 
			 copie_graphe(graphe, graphest);
			 couleur_suivante();
			 cpt = cpt + 1;
		 }
	 }

/* ------------------------------------------------------------ */

/* Ecrire la procédure de Floyd_Warshall des plus courts chemins sur
   un graphe non pondéré. Chaque "barbecue" utilisera une autre
   couleur d'arc pour marquer les nouvelles connaissances. */

void floyd_warshall ( t_gra graphe )
     {
			 int maxi, i, j, k;
			 int taille = taille_graphe(graphe);
			 t_gra graphest = nouveau_graphe(taille);

			 definir_couleur(ROUGE); // cf reponse de reference 

			 copie_graphe(graphe, graphest);

			
			 for (k = 0; k < taille; k++)
			 {
			 	for (i = 0; i < taille; i++)
				{
			 		for (j = 0; j < taille; j++)
					{
			 			
						if (!get_arc(graphe, i, j))
						{
							maxi = get_arc(graphest, i, k)*get_arc(graphest, k, j);
							if(maxi)
							{
								 set_arc(graphe, i, j, la_couleur());
							}
						}
			 		}
			 	}
			
				copie_graphe(graphe, graphest);
				
				couleur_suivante();
			 }
	    }

/* ------------------------------------------------------------ */

/* On considère un graphe pondéré. Ecrire la procédure de calcul des
   chemins les plus légers, c'est-à-dire en termes de somme des poids
   des arcs et arêtes.

   Attention, à la différence de qui a été considéré lors des TD, un
   arc ou une arête absente ne porte pas le poids + infini, mais
   retourne - 1 à travers les prédicats get_arc ou get_arete.

   On est garanti du fait que la constante PLUS_INF est neutre pour la
   minimisation et la constante MOINS_INF neutre pour la maximisation. */

void multiplie_pondere ( t_gra graphe )
     {
			 int taille = taille_graphe(graphe);
			 int mini, i, j, l, imin, jmin, pdsij, k = 1, up = 1;

			 definir_couleur(ROUGE);

			 fermeture_reflexive_pondere(graphe, 0);
			 couleur_suivante();
			
			 t_gra graphest = nouveau_graphe(taille);
			 copie_graphe(graphe, graphest);

			 while((k < taille - 1) && up)
			 {
				 up = NON;
				 for (i = 0; i < taille; i++)
				 {
				 	for (j = 0; j < taille; j++)
					{
						if(i != j)
						{
					 		mini = PLUS_INF;
							
							for (l = 0; l < taille; l++)
							{
								if (i != l && j != l)
								{
									if(get_arc(graphest, i, l))
									{ 
										imin = poids_arc(graphest, i, l);
									}
									else 
									{
										imin = PLUS_INF;
									}

									if(get_arc(graphest, l, j))
									{ 
										jmin = poids_arc(graphest, l, j);
									}
									else 
									{
										jmin = PLUS_INF;
									}

									mini = min(imin + jmin, mini);
								}
							}

							
							if (mini < PLUS_INF)
							{
								if(get_arc(graphest, i, j))
								{
									 pdsij = poids_arc(graphest, i, j);
								}
								else
								{
									 pdsij = PLUS_INF;
								}

								if (mini < pdsij)
								{
									set_arc_pondere(graphe, i, j, mini, la_couleur());
									up = OUI;
								}
							}
						}
				 	}
				 }
				
				 copie_graphe(graphe, graphest);
				
				 couleur_suivante();
				 k = k * 2;
			 }
     }

/* ------------------------------------------------------------ */



void floyd_warshall_pondere ( t_gra graphe )
     {
			 int i, j, k, mini, imin, jmin, pdsij;
			 int taille = taille_graphe(graphe);

			 definir_couleur(ROUGE);

			 fermeture_reflexive_pondere(graphe, 0);
			 couleur_suivante();


			 t_gra graphest = nouveau_graphe(taille);
			 copie_graphe(graphe, graphest);

			 for (k = 0; k < taille; k++)
			 {
			 	for (i = 0; i < taille; i++)
				{
			 		for (j = 0; j < taille; j++)
					{
			 			if(i != j)
						{
							mini = PLUS_INF;
							if (get_arc(graphest, i, k)) 
							{ 
								imin = poids_arc(graphest, i, k);
							}
							else 
							{	
								imin = PLUS_INF;
							} 

							if (get_arc(graphest, k, j)) 
							{
								jmin = poids_arc(graphest, k, j);
							}
							else 
							{	
								jmin = PLUS_INF;
							}

							mini = min (imin + jmin, mini);

							if(mini < PLUS_INF)
							{
								if(get_arc(graphest, i, j)) 
								{	
									pdsij = poids_arc(graphest, i, j);
								}
								else 
								{
									pdsij = PLUS_INF;
								}

								if(mini < pdsij)
								{	
									set_arc_pondere(graphe, i, j, mini, la_couleur());
								}
							}
						}
			 		}
			 	}
				copie_graphe(graphe, graphest);
	
				couleur_suivante();
			 }
     }

/* ------------------------------------------------------------ */

/* dijkstra calcule les chemins les plus légers depuis un sommet de
   de départ vers tous les autres sommets. Les poids des arcs et arêtes
   doivent être positifs ou nuls. Ceci est vérifié à l'aide du
   prédicat verifie_ponderation.

   Attention, à la différence de ce qui a été vu en cours, il se peut
   que certains sommets ne sont peut-être pas atteignables depuis le
   sommet de départ.

   Pour tout sommet u , D( u ) est représenté à l'aide du poids associé
   au sommet. P( u ) est géré à travers le tableau table_predecesseurs
   qui est passé en argument à dijkstra. Toutes les informations sont
   initialisées comme vu en cours et TD. On pourra utiliser - 1 pour
   indiquer dans table_predecesseurs que l'on ne connaît pas le
   prédécesseur d'un sommet donné.

   cherche_sec_sommet_min retourne l'indice du sommet u pour lequel
   D( u ) est minimal parmi tous les sommets encore secs et mouille le
   sommet en question.

   relax est l'opération de relaxation de Dijsktra. Si le sommet s accepte
   le sommet p comme nouveau prédécesseur, on met à jour D( s ) et P( s ).
   L'arc p -> s sera alors colorié en ROUGE, et tout éventuel ancien arc
   rouge x -> s redeviendra NOIR.

   La table des prédécesseurs table_predecesseurs est considérée non
   initialisée et doit donc être initialisée. De même, on ne suppose rien
   sur les poids de sommets. */

int verifie_ponderation ( t_gra graphe )
    {
			int taille = taille_graphe(graphe);
			int i, j;

			for(i = 0; i < taille; i++)
			{
				for(j = 0; j < taille; j++)
				{
					if (get_arc(graphe, i, j))
					{
						if(poids_arc(graphe, i, j) < 0) return NON;
					}
				}
			}

			return OUI;
    }

int cherche_sec_sommet_min ( t_gra graphe )
    {
     int taille = taille_graphe(graphe);
		 int i, umin = -1, pdsmin = PLUS_INF;

		 
		 for (i = 0; i < taille; i++)
		 {
			
		 	if(sommet_possede_poids(graphe, i) && sommet_get_poids(graphe, i) < PLUS_INF);
			{
				if(sommet_get_poids(graphe, i) < pdsmin && !mouille(graphe, i))
				{
					umin = i;
					pdsmin = sommet_get_poids(graphe, i);
				}
			}
		 }
		 return umin;
    }

void relax ( t_gra graphe , int table_predecesseurs[ ] , int pred , int sommet )
     {
			 
			 int sum = sommet_get_poids(graphe, pred) + poids_arc(graphe, pred, sommet);

		
			 if(sum < sommet_get_poids(graphe, sommet))
			 {
				 sommet_set_poids(graphe, sommet, sum);
				 if(table_predecesseurs[sommet] != -1)
				 {
					set_couleur_arc(graphe, table_predecesseurs[sommet], sommet, NOIR);
				 }

				 table_predecesseurs[sommet] = pred;
				 set_couleur_arc(graphe, table_predecesseurs[sommet], sommet, ROUGE);
			 }

     }

void dijkstra ( int depart , t_gra graphe , int table_predecesseurs[ ] )
     {
			 assert(verifie_ponderation(graphe));
			 int taille = taille_graphe(graphe);
			 int i, vois, u;

			 for(i = 0; i < taille; i++)
			 {
				 if(i == depart)
				 {
					 sommet_set_poids(graphe, i, 0);
					 table_predecesseurs[i] = 0;
				 }
				 else
				 {
					 sommet_set_poids(graphe, i, PLUS_INF);
					 table_predecesseurs[i] = -1;
				 }
			 }

			 u = depart;
			 definir_couleur(NOIR);
			 while(u != -1)
			 {
				 tremper(graphe, u);
				 for(vois = 0; vois < taille; vois++)
				 {
					 if (!mouille(graphe, vois) && get_arc(graphe, u, vois))
					 {
					 	relax(graphe, table_predecesseurs, u, vois);
					 }
				 }
				
				 u = cherche_sec_sommet_min(graphe);
			 }
     }

/* ------------------------------------------------------------ */

/* dijkstra_maximise_le_min calcule les meilleurs chemins en maximisant
   l'arc ou l'arête minimal du chemin. Il faut adapter les fonctions
   et procédures précédentes.

   relax_maximise_le_min prend le sommet de départ comme argument
   supplémentaire, car le traitement est particulier lorsque le
   prédécesseur est égal au sommet de départ.

   Attention, à la différence de ce qui a été vu en cours, il se peut
   que certains sommets ne sont peut-être pas atteignables depuis le
   sommet de départ. */

int cherche_sec_sommet_max ( t_gra graphe )
{
  int taille = taille_graphe(graphe);
  int i, umax = -1, pdsmax = MOINS_INF;

 		
  for (i = 0; i < taille; i++)
    {
 		
      if(sommet_possede_poids(graphe, i) && sommet_get_poids(graphe, i) < PLUS_INF)
	{
 				
	  if(sommet_get_poids(graphe, i) > pdsmax && !mouille(graphe, i))
	    {
	      umax = i;
	      pdsmax = sommet_get_poids(graphe, i);
	    }
	}
    }
  return umax;
    }

void relax_maximise_le_min ( t_gra graphe , int table_predecesseurs[ ] ,
			     int pred , int sommet , int depart )
{
  int mini, mini2, maxi;

  if(pred == depart)
    {
      sommet_set_poids(graphe, sommet, poids_arc(graphe, pred, sommet));
      table_predecesseurs[sommet] = pred;
      set_couleur_arc(graphe, pred, sommet, la_couleur());
    }
  else if (sommet_get_poids(graphe, sommet) == PLUS_INF)
    {
      mini2 = min(poids_arc(graphe, pred, sommet), sommet_get_poids(graphe, pred));
      sommet_set_poids(graphe, sommet, mini2);
      table_predecesseurs[sommet] = pred;
      set_couleur_arc(graphe, pred, sommet, la_couleur());
    }
  else
    {
      mini = min(poids_arc(graphe, pred, sommet), sommet_get_poids(graphe, pred));
      maxi = max(mini, sommet_get_poids(graphe, sommet));

      if(maxi != sommet_get_poids(graphe, sommet))
	{
	  sommet_set_poids(graphe, sommet, maxi);

					
	  if(table_predecesseurs[sommet] != -1)
	    {
	      set_couleur_arc(graphe, table_predecesseurs[sommet], sommet, NOIR);
	    }
				
	  table_predecesseurs[sommet] = pred;
	  set_couleur_arc(graphe, pred, sommet, la_couleur());
	}
    }
}

void dijkstra_maximise_le_min ( int depart , t_gra graphe , int table_predecesseurs[ ] )
     {
			 assert(verifie_ponderation(graphe));
			 int taille = taille_graphe(graphe);
			 int i, u, vois;

			 for(i = 0; i < taille; i++)
			 {
				 if(depart == i)
				 {
					 sommet_set_poids(graphe, i, 0);
					 table_predecesseurs[i] = 0;
				 }
				 else
				 {
					 sommet_set_poids(graphe, i, PLUS_INF);
					 table_predecesseurs[i] = -1;
				 }
			 }

			 u = depart;
			 definir_couleur(NOIR);
			 couleur_suivante();
			 while (u != -1)
			 {
			 	tremper(graphe, u);
				for(vois = 0; vois < taille; vois++)
				{
					if(!mouille(graphe, vois) && get_arc(graphe, u, vois))
					{
						relax_maximise_le_min(graphe, table_predecesseurs, u, vois, depart);
					}
				}
				u = cherche_sec_sommet_max(graphe);
			 }
     }

/* ------------------------------------------------------------ */

/* La boucle principale de calcul d'un graphe de flot est donnée
   dans ford_et_fulkerson. Il s'agit de la compléter en définissant
   deux fonctions.

   ford_et_fulkerson commence par vérifier que le graphe est correct
   avec Sa comme source et le sommet d'indice taille_graphe( graphe ) - 1
   comme puits. De plus, il faut que tous les sommets puissent être
   atteints depuis la source.

   calcule_residuel prend en argument le graphe de flot et le graphe
   résiduel en construction. Pour des sommets i et j donnés, avec i != j,
   il s'agit de calculer la marge dans le sens "i vers j" et de mettre
   à jour le graphe résiduel. capacite_arc donne la capacité de l'arc
   et poids_arc donne le flot de l'arc. graphe_residuel est un
   graphe pondéré ordinaire.

   adapte_flot change le flot dans le graphe de flot entre les sommets
   depuis et vers et ceci d'une quantité égale à la valeur donnée.
   Eventuellement, on sera obligé de modifier les deux arcs
   ( depuis , vers ) et ( vers , depuis ) dans le graphe de flot.
   Chaque arc modifié reçoit la couleur courante. */

void calcule_residuel ( t_gra graphe_flot , t_gra graphe_residuel , int i , int j )
{
	int marge = 0;

	if(get_arc(graphe_flot, i, j))
				marge = capacite_arc(graphe_flot, i, j) - poids_arc(graphe_flot, i, j);

	//Il faut prendre compte du flot en sens inverse
	if(get_arc(graphe_flot, j, i))
		marge = marge + poids_arc(graphe_flot, j, i);

		if(marge)
		{
			set_arc_pondere(graphe_residuel, i, j, marge, NOIR);
		}
}

void adapte_flot ( t_gra graphe_flot , int depuis , int vers , int valeur )
     {
			 int valeurinv = 0, temp, max_flow;

			 if(valeur < 0)
			 {
				 temp = depuis;
				 depuis = vers;
				 vers = temp;
				 valeur = - valeur;
			 }

			 max_flow = capacite_arc(graphe_flot, depuis, vers) - poids_arc(graphe_flot, depuis, vers);

			 if(valeur > max_flow)
			 {
				 valeurinv = valeur;
				 valeur = max_flow;
				 valeurinv = valeurinv - valeur;
			 }

			 if(valeur)
			 {
				 set_arc_pondere(graphe_flot, depuis, vers, poids_arc(graphe_flot, depuis, vers) + valeur, la_couleur());
			 }

			 if(valeurinv)
			 {
				 set_arc_pondere(graphe_flot, vers, depuis, poids_arc(graphe_flot, vers, depuis) - valeur, la_couleur());
			 }
     }

		 void ford_et_fulkerson(void)  {
		 	int i, j, sommet, taille, continuer, table_predecesseurs[N];
		 	definir_couleur(NOIR);
		 	taille = taille_graphe(G_9_flot);

		 	/* Vérification de la forme du graphe. */

		 	// Les 3 lignes suivantes sont à décommenter une fois les fonctions écrites.
		 	assert(graphe_AR(G_9_flot));
		 	assert(verifie_ponderation(G_9_flot));
		 	parcours_profondeur_niveaux(G_9_flot, Sa);

		 	/* Ces 2 lignes passent en commentaire au moment ou les précédentes sont activées. */
		 	// for(sommet = 1; sommet < taille; sommet++) {
		 	// 	sommet_set_poids(G_9_flot, sommet, 1);
		 	// }

		 	for(sommet = 0; sommet < taille; sommet++) {
		 		assert(!Sa || sommet_get_poids(G_9_flot, sommet) > 0);
		 		sommet_unset_poids(G_9_flot, sommet);
		 		assert(!get_arc(G_9_flot, taille - 1, sommet));
		 		assert(!get_arc(G_9_flot, sommet, Sa));
		 	}

		 		/* La disposition des sommets est arrêtée et mémorisée. Les graphes de
		 		flots et résiduels vont tous être affichés de la même manière. */

		 	definir_couleur(NOIR);
		 	memorise_forme_graphe_flot(G_9_flot);

		 	do {
		 		continuer = NON;

		 		/* Chaque itération utilise une nouvelle couleur
		 			et alloue un nouveau graphe résiduel. */

		 		couleur_suivante();
		 		t_gra graphe_residuel = nouveau_graphe_pondere(taille, - 100, 100);

		 		printf("Le graphe de flot donné :\n");
		 		imprime_graphe(G_9_flot, DERNIERE_COULEUR, NON);

		 		/* Ici, on calcule le graphe résiduel. */

		 		for(i = 0; i < taille; i++) {
		 			for(j = 0; j < taille; j++) {
		 				if(i != j &&(get_arc(G_9_flot, i, j) || get_arc(G_9_flot, j, i))) {
		 					calcule_residuel(G_9_flot, graphe_residuel, i, j);
		 				}
		 			}
		 		}

		 		/* Ici, on calcule le meilleur chemin augmentant, à savoir celui
		 			dont le maillon faible est aussi grand que possible.

		 			Le tableau table_predecesseurs donne le prédécesseur de
		 			chaque sommet le long du chemin retenu. */

		 		for(sommet = Sb; sommet < taille; sommet++) {
		 			table_predecesseurs[sommet] = - 1;
		 		}
		 		table_predecesseurs[Sa] = Sa;
		 		dijkstra_maximise_le_min(Sa, graphe_residuel, table_predecesseurs);

		 		/* Si le chemin retenu ne permet pas de rejoindre le
		 			puits, l'algorithme se termine. */

		 		continuer = (table_predecesseurs[taille - 1] != - 1);

		 		/* Le graphe résiduel est affiché avec le chemin augmentant en bleu. */

		 		if(continuer) {
		 			sommet = taille - 1;
		 			while(sommet != Sa) {
		 				set_couleur_arc(graphe_residuel, table_predecesseurs[sommet], sommet, BLEU);
		 				sommet = table_predecesseurs[sommet];
		 			}
		 		}
		 		printf("Le graphe résiduel et son meilleur chemin augmentant :\n");
		 		imprime_graphe(graphe_residuel, DERNIERE_COULEUR, NON);

		 		/* Ici, on modifie le graphe de flot en changeant les flots le
		 			long du chemin augmentant trouvé dans le graphe résiduel.

		 			Le poids de modification poids_modif est la valeur du
		 			maillon faible du chemin augmentant. Celle-ci correspond
		 			au poids qui a été associé au puits lors du calcul du
		 			du chemin augmentant. */

		 		if(continuer) {
		 			int poids_modif = sommet_get_poids(graphe_residuel, taille - 1);
		 			sommet = taille - 1;
		 			while(sommet != Sa) {
		 				adapte_flot(G_9_flot, table_predecesseurs[sommet], sommet, poids_modif);
		 				sommet = table_predecesseurs[sommet];
		 			}
		 		}

		 		/* On jette le graphe résiduel et on recommence éventuellement. */

		 		free(graphe_residuel);
		 	} while(continuer);

		 	/* L'affichage du résultat final. */
		 	printf("Le graphe de flot final où les arcs saturés sont en rouge :\n");
		 	imprime_graphe(G_9_flot, TOUT_NOIR, NON);
		 	oublie_forme_graphe_flot();

		 }
/* ------------------------------------------------------------ */
