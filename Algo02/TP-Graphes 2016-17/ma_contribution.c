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
{/* +/- 10 lignes. Il faudra retourner une valeur convenable. */
    int stay = 1, i,j;

    for(i=0; ((i<taille_graphe(graphe)-1) && stay);i++){
        for(j=i+1;(j<taille_graphe(graphe) && stay);j++){
            //si le lien existe
            if(get_arc(graphe,i,j)||get_arc(graphe,j,i)){
                stay = get_arete(graphe,i,j);
            }
        }
    }
    return stay; 
}

/* ------------------------------------------------------------ */

/* La procédure fermeture_reflexive rajoute toutes les arêtes de la
   forme ( s , s ) manquantes, c'est-à-dire les arêtes d'un sommet s
   vers lui-même. Les nouvelles arêtes seront de la couleur donnée
   par la_couleur( ). Le graphe ne doit pas être pondéré. */  

void fermeture_reflexive ( t_gra graphe )
{
    /* +/- 5 lignes */
    int i;
    if(!graphe_pondere(graphe)){
        for(i=0;i<taille_graphe(graphe);i++){
            set_arete(graphe, i,i, la_couleur());
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
    /* +/- 5 lignes */
    int i;
    assert(graphe_pondere(graphe));
    assert(poids_ok(graphe,poids));
    if(poids_ok(graphe,poids) && graphe_pondere(graphe)){
        for(i=0;i<taille_graphe(graphe);i++){
            set_arete_pondere(graphe, i,i, la_couleur(),poids);
        }
    }
}

/* ------------------------------------------------------------ */

/* Le prédicat graphe_AR dit si, OUI ou NON, le graphe fourni est
   anti-réflexif, c'est-à-dire ne possède aucune arête de la forme
   ( s , s ) ? Elle s'applique aussi bien aux graphes pondérés que
   non pondérés, orientés ou non. */

int graphe_AR ( t_gra graphe )
{/* +/- 5 lignes. Il faudra retourner une valeur convenable. */
    int i, AR = 1;
    for(i=0;(i<taille_graphe(graphe));i++){
        AR = AR && !get_arc(graphe,i,i);
    }
    return( AR ) ;   
}

/* ------------------------------------------------------------ */

/* Le prédicat graphe_ARAS dit si, OUI ou NON, le graphe fourni
   est à la fois anti-réflexif et anti-symétrique ? Le graphe
   peut être pondéré ou non. */

int graphe_ARAS ( t_gra graphe )
{/* +/- 10 lignes. Il faudra retourner une valeur convenable. */
	  int i, j, antisymetrique=1;
    //on détermine l'antisymétrie
    for(i=0;i<(taille_graphe(graphe)-1);i++){
        for(j=i+1;j<taille_graphe(graphe);j++){
	        if(graphe_pondere(graphe) && get_arete(graphe,i,j)){
		        antisymetrique = antisymetrique &&
			        (poids_arc(graphe,i,j)!=poids_arc(graphe,j,i));
	        }else{
		        antisymetrique = antisymetrique && !get_arete(graphe,i,j);
	        }
        }
    }

    return( graphe_AR(graphe) && antisymetrique ) ; 
}

/* ------------------------------------------------------------ */

/* La fonction degre_graphe retourne le degré d'un graphe symétrique
   pondéré, ou non. La fonction vérifie explicitement que le graphe
   fourni est bien symétrique. On opte pour le choix normal qui
   consiste à dire qu'une arête réflexive de la forme ( a , a )
   compte pour 2 dans le degré du sommet a . */

int degre_graphe ( t_gra graphe )
    {/* +/- 15 lignes. Il faudra retourner une valeur convenable. */
	    int i,j,symetrique=1, degre,degreMax = 0;
	    //symetrique ssi arete existe (a,b) et (b,a)
	    //pour chaque sommet, ajouter degré +2 pour (a,b) et (b,a)
	    // non symétrique si les deux n'existent pas
	    for(i=0;i<(taille_graphe(graphe) && symetrique);i++){
		    degre = 0;
		    for(j=i;j<(taille_graphe(graphe) && symetrique);j++){
			    if(get_arc(graphe,i,j) && get_arc(graphe,j,i) && symetrique){
				    //Cas arete existe
				    degre+=2;
				    //test de la symétrie
				    if(graphe_pondere(graphe) && symetrique){
					    symetrique = symetrique &&
						    (poids_arc(graphe,i,j) == poids_arc(graphe,j,i));
				    }
			    }else if((get_arc(graphe,i,j) || get_arc(graphe,j,i))
			             && symetrique){
				    //Cas 1 seul arc --> pas symetrique
				    symetrique = 0;
			    }
		    }
		    //trouver degre max (degre du graphe)
		    if(degre>degreMax){
			    degreMax = degre;
		    }
	    }

	    //Ne renvoyer le degre que si le graphe est symétrique
	    if (symetrique){
		    return degreMax;
	    }
     return( 0 ) ; 
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

   De plus, chaque sommet recevra comme poids le numéro d'étapes
   nécessaires pour le toucher la première fois. C'est d'ailleurs le même
   numéro que celui de l'arête qui l'atteint en premier. On calcule donc
   de surcroît les plus courts chemins du point de départ au sommet
   considéré.

   connexe_vague affichera, suivant l'état de view, donc OUI ou NON, le
   graphe et la progression de la vague pour chaque étape. Voir aussi
   le fichier de réponse type "reponse_de_refence".

   Cette fonctionnalité nécessite un parcours en largeur et va s'appuyer
   sur fonctions de gestion de file fournies dans fonctions.h .

   A la fin, tous les sommets sont à nouveau séchés.

   connexe_vague est un peu plus difficile à implanter que d'autres et on
   peut préférer résoudre d'abord certaines des questions qui suivent. */ 

int cherche_sommet_sec ( t_gra graphe )
{/* +/- 5 lignes. Il faudra retourner une valeur convenable. */
  int i=0,ret = -1;
  while(i<taille_graphe(graphe) && ret == -1){
    if(!mouille(graphe,i)){
      ret = i;
    }
    i++;
  }
  return( ret ) ; 
}

int connexe_vague ( t_gra graphe , int view )
{/* +/- 40 lignes. Il faudra retourner une valeur convenable. */
  int cc = 0,p,u,v;
  t_file sDep = cree_file_vide();

  assert(graphe_non_oriente(graphe));
  
  //tant qu'on peut trouver une composante connexe
  while((u = cherche_sommet_sec(graphe))!=-1){
    definir_couleur(1);
    sommet_set_poids(graphe,u,0);
    tremper(graphe,u);
    sDep = insere_file(u,sDep);
    cc++;
    p=1;
    // tant que la vague lancée n'est pas terminée
    while(!est_file_vide(sDep)){
      u = tete_file(sDep);
      sDep = supprime_tete_file(sDep);
      //on checke si on doit changer la couleur (cad on est ds une nouvelle vague)
      // on utilise la prop qui stipule qu'a la vague n°x, toutes les sommets
      // sont a une distance x du premier sommet
      // si on tombe sur un sommet de départ de la vague x+1, alors on change la
      // couleur
      if(sommet_get_poids(graphe,u)+1>p){
	p++;//pour détecter les chgments de vague suivant
	    //distance +1 a partir d'ici
	couleur_suivante();
	if(view){
	  imprime_graphe(graphe,TOUTES_COULEURS,OUI);
	}
      }
      //pour chaque voisin v de u
      for(v=0;v<(taille_graphe(graphe));v++){
	if(!mouille(graphe,v) && get_arete(graphe,u,v)){
	  set_couleur_arc(graphe,u,v,la_couleur());
	  tremper(graphe,v);
	  sommet_set_poids(graphe,v,sommet_get_poids(graphe,u)+1);
	  sDep = insere_file(v,sDep);
	}
      }
    }
  }

  //On sèche tous les sommets
  for(v=0;v<taille_graphe(graphe);v++){
    secher(graphe,v);
  }
  
  return( cc ) ; 
}

/* ------------------------------------------------------------ */

/* Ecrire le prédicat est_un_arbre qui s'applique aux seuls graphes
   anti-réflexifs et non orientés et qui dit si, OUI ou NON, le graphe
   est un arbre. Il suffira de compter le nombre d'arêtes et de vérifier
   que le graphe possède exactement une seule composante connexe. */

int nombre_aretes ( t_gra graphe ) //DONE
    {/* +/- 10 lignes. Il faudra retourner une valeur convenable. */
      int i,j,nbAretes=0;
      for(i=0;i<(taille_graphe(graphe)-1);i++){
	for(j=i+1;j<taille_graphe(graphe);j++){
	  if(get_arete(graphe,i,j)){
	    nbAretes++;
	  }
	}
      }
     return( nbAretes ) ; 
    }

int est_un_arbre ( t_gra graphe ) //DONE
{/* +/- 5 lignes. Il faudra retourner une valeur convenable. */
      
  assert(graphe_AR(graphe) && graphe_non_oriente(graphe));
      
      
  return( (nombre_aretes(graphe)-1) == taille_graphe(graphe)
	  && connexe_vague(graphe, NON)==1) ; 
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

void parcours_profondeur_niveaux_rec ( t_gra graphe , int sommet , int niveau ) //DONE
{
  /* +/- 10 lignes */
  int i;
  for(i=0;i<taille_graphe(graphe);i++){
    if(!mouille(graphe,i) && get_arc(graphe,sommet,i)){
      tremper(graphe,i);
      sommet_set_poids(graphe,i,min(niveau,sommet_get_poids(graphe,i)));
      parcours_profondeur_niveaux_rec(graphe, i, niveau+1);
      secher(graphe,i);
    }
  }
}

void parcours_profondeur_niveaux ( t_gra graphe , int depart ) //DONE
{
  int i;
  for(i=0;i<taille_graphe(graphe);i++){
    sommet_set_poids(graphe,i,PLUS_INF);
  }
  sommet_set_poids(graphe,depart,0);
  tremper(graphe,depart);
  parcours_profondeur_niveaux_rec(graphe, depart, 1);
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

int cherche_sommet_sec_et_predecesseurs_mouilles ( t_gra graphe ) //DONE
{/* +/- 15 lignes. Il faudra retourner une valeur convenable. */
  
  int u,v,toutPredecesseurMouille,pasDePredecesseur;
  for(v=0; v<taille_graphe(graphe);v++){
    if(!mouille(graphe,v)){
      toutPredecesseurMouille = 1;
      pasDePredecesseur = 1;
      //printf("v : %d\n",v);
      for(u=0;u<taille_graphe(graphe);u++){
	//printf("    u : %d\n",u);
	toutPredecesseurMouille = toutPredecesseurMouille
	  && (!get_arc(graphe,u,v) || (mouille(graphe,u) && get_arc(graphe,u,v)));
	pasDePredecesseur = pasDePredecesseur && !get_arc(graphe,u,v);
      }
      if(toutPredecesseurMouille || pasDePredecesseur){
	//printf("ret : %d\n",v);
	return v;
      }
    }
  }
  return (-1);
}

void tri_topologique ( t_gra graphe ) //DONE
{
  /* +/- 20 lignes */
  int aNodeDoesntHaveWeight,hasCycle = 0;
  int sommet,i,max;
  do{
    sommet = cherche_sommet_sec_et_predecesseurs_mouilles(graphe);
    if(sommet == -1){
      hasCycle=1;
      printf("LE GRAPHE COMPORTE DES CIRCUITS !\n");
    }else{
      //parmi tout les prédécesseurs mouillés, on obtient le poids maximum
      max = 0;
      for(i=0;i<taille_graphe(graphe);i++){
	if(get_arc(graphe,i,sommet) && mouille(graphe,i)){
	  if(sommet_get_poids(graphe,i)>=max){
	    max = sommet_get_poids(graphe,i) + 1;
	  }
	  set_couleur_arc(graphe,i,sommet,sommet_get_poids(graphe,i)+1);
	  
	}
      }
      //on assigne un poids au sommet courant, et on le mouille
      sommet_set_poids(graphe,sommet,max);
      tremper(graphe,sommet);

      //on regarde si il reste des sommets a valuer
      aNodeDoesntHaveWeight = 0;
      for(i=0;i<taille_graphe(graphe);i++){
	aNodeDoesntHaveWeight = aNodeDoesntHaveWeight
	  || !sommet_possede_poids(graphe,i);
      }
    }
  }while(aNodeDoesntHaveWeight && !hasCycle);
  
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

void multiplie ( t_gra graphe ) //DONE
{
  int u,v,k,K=1;
  t_gra copieGraphe = nouveau_graphe(taille_graphe(graphe));

  definir_couleur(NOIR);
  for(u=0; u<taille_graphe(copieGraphe);u++){
    for(v=0; v<taille_graphe(copieGraphe);v++){
      if(get_arc(graphe,u,v)){
	set_couleur_arc(graphe,u,v,la_couleur());
      }
    }
  }
	 
  couleur_suivante();
  fermeture_reflexive(graphe);
  couleur_suivante();

       
  while(K<taille_graphe(graphe)-1){
    copie_graphe(graphe, copieGraphe);
    //chgment couleur
	
    K=K*2;
	 
    //pour u
    for(u=0; u<taille_graphe(copieGraphe);u++){
      //printf("u : %d\n",u);
      //pour v
      for(v=0; v<taille_graphe(copieGraphe);v++){
	//printf("    v : %d\n",v);
	//on enlève les cas pas pertinent (reflexif et get_arc(u,v)=1)
	if(u!=v && !get_arc(graphe,u,v)){
	  //pour k
	  for(k=0; k<taille_graphe(copieGraphe);k++){
	    //printf("        k : %d\n",k);
	    //Si on peut créer un arc, on le fait
	    if(get_arc(copieGraphe,u,k)*get_arc(copieGraphe,k,v)){
	      set_arc(graphe,u,v,la_couleur());
	      //printf("        YEAH\n");
	    }
	  }
	}
      }
    }
    couleur_suivante();
  }
}

/* ------------------------------------------------------------ */

/* Ecrire la procédure de Floyd_Warshall des plus courts chemins sur
   un graphe non pondéré. Chaque "barbecue" utilisera une autre
   couleur d'arc pour marquer les nouvelles connaissances. */

void floyd_warshall ( t_gra graphe ) //BUG
{
  /* +/- 15 lignes */
  //imprime_graphe(graphe,TOUTES_COULEURS,OUI);
  int u,v,k;
  t_gra copieGraphe = nouveau_graphe(taille_graphe(graphe));

  definir_couleur(ROUGE);
  couleur_suivante();
  
  copie_graphe(graphe, copieGraphe);
  //imprime_graphe(copieGraphe,TOUTES_COULEURS,OUI);

  //pour u
  for(u=0; u<taille_graphe(copieGraphe);u++){
    //pour v
    for(v=0; v<taille_graphe(copieGraphe);v++){
      //pour k
      for(k=0; k<taille_graphe(copieGraphe);k++){
	//Si on peut créer un arc, on le fait
	if(get_arc(copieGraphe,u,k)*get_arc(copieGraphe,k,v)){
	  set_arc(graphe,u,v,la_couleur());
	}
      }
    }
    couleur_suivante();
    copie_graphe(graphe, copieGraphe);
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

void multiplie_pondere ( t_gra graphe ) //DONE
{
  /* +/- 25 lignes */
  int u,v,k,K=1,mini;
  t_gra copieGraphe = nouveau_graphe_pondere(taille_graphe(graphe),POIDS_MIN,POIDS_MAX);

  definir_couleur(NOIR);
  for(u=0; u<taille_graphe(copieGraphe);u++){
    for(v=0; v<taille_graphe(copieGraphe);v++){
      if(get_arc(graphe,u,v)){
	set_couleur_arc(graphe,u,v,la_couleur());
      }
    }
  }
	 
  couleur_suivante();
  fermeture_reflexive(graphe);
  couleur_suivante();

       
  while(K<taille_graphe(graphe)-1){
    copie_graphe(graphe, copieGraphe);
	
    K=K*2;
	 
    //pour u
    for(u=0; u<taille_graphe(copieGraphe);u++){
      //pour v
      for(v=0; v<taille_graphe(copieGraphe);v++){
	//on enlève les cas pas pertinent (reflexif et get_arc(u,v)=1)
	if(u!=v && !get_arc(graphe,u,v)){
	  //pour k
	  mini = PLUS_INF;
	  for(k=0; k<taille_graphe(copieGraphe);k++){	    
	    if(get_arc(copieGraphe,u,k) && get_arc(copieGraphe,k,v)){
	      mini = min(poids_arc(graphe,u,k)+poids_arc(graphe,k,v),mini);
	    }
	  }
	  if(mini != PLUS_INF){
	    set_arc_pondere(graphe,u,v,mini,la_couleur());
	  }
	 
	}
      }
    }
    couleur_suivante();
  }
}

/* ------------------------------------------------------------ */

/* La version pondérée de Floyd-Warshall. */

void floyd_warshall_pondere ( t_gra graphe )
     {
	/* +/- 20 lignes */
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

int verifie_ponderation ( t_gra graphe ) //BUG?
{/* +/- 10 lignes. Il faudra retourner une valeur convenable. */
  int ret=1,u,v;
  for(u=0;u<taille_graphe(graphe);u++){
    for(v=0;v<taille_graphe(graphe);v++){
      if(get_arc(graphe,u,v)){
	      ret = ret && (poids_arc(graphe,u,v)>=0);
      }
    }
  }
  return(ret) ; 
}

int cherche_sec_sommet_min ( t_gra graphe )
{/* +/- 10 lignes. Il faudra retourner une valeur convenable. */
  int u,mini=PLUS_INF,sommet_min=-1;
  for(u=0;u<taille_graphe(graphe);u++){
    if(sommet_possede_poids(graphe,u) && (sommet_get_poids(graphe,u)<mini ) && !mouille(graphe, u)){
      sommet_min = u;
      mini = sommet_get_poids(graphe,u);
    }
  }
  if(sommet_min!=-1){
    tremper(graphe,sommet_min);
  }
  return( sommet_min ) ; 
}

void relax ( t_gra graphe , int table_predecesseurs[ ] , int pred , int sommet )
{
	/* +/- 10 lignes */
  int distance = sommet_get_poids(graphe,pred) + poids_arc(graphe, pred, sommet);
  //sommet accepte pred comme nouveau prédecesseur
	if(distance < sommet_get_poids(graphe,sommet)){
    if(table_predecesseurs[sommet]!=-1){
      definir_couleur(NOIR);
      set_couleur_arc(graphe,table_predecesseurs[sommet],sommet,la_couleur());
    }
    definir_couleur(ROUGE);
    set_couleur_arc(graphe,pred,sommet,la_couleur());
    sommet_set_poids(graphe,sommet,distance);
    table_predecesseurs[sommet] = pred;
  }
}

void dijkstra ( int depart , t_gra graphe , int table_predecesseurs[ ] )
{
  int u,v,taille = taille_graphe(graphe);
  //initialisation
  //vérification des pondérations
  assert(verifie_ponderation(graphe));

  //Distances = +INFINI sauf départ
  for(u=0;u<taille;u++){

    sommet_set_poids(graphe,u,PLUS_INF);
  }
  sommet_set_poids(graphe,depart,0);
  
  //Précédent départ = départ et reste a -1
  for(u=0;u<taille;u++){
    table_predecesseurs[u] = -1;
  }
  table_predecesseurs[depart] = depart;

  u = cherche_sec_sommet_min(graphe);
  while(u!=-1){
    

    for(v=0;v<taille;v++){
      if(get_arc(graphe,u,v) && !mouille(graphe,v)){
        relax(graphe,table_predecesseurs,u,v);
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
    {/* +/- 10 lignes. Il faudra retourner une valeur convenable. */
     return( 0 ) ; 
    }

void relax_maximise_le_min ( t_gra graphe , int table_predecesseurs[ ] ,
			     int pred , int sommet , int depart )
     {
	/* +/- 10 lignes */
     }

void dijkstra_maximise_le_min ( int depart , t_gra graphe , int table_predecesseurs[ ] )
     {
	/* +/- 20 lignes */
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
	/* +/- 10 lignes */
     }

void adapte_flot ( t_gra graphe_flot , int depuis , int vers , int valeur )
     {
	/* +/- 20 lignes */
     }

void ford_et_fulkerson ( void ) 
     {int i , j , sommet , taille , continuer , table_predecesseurs[ N ] ;
      definir_couleur( NOIR ) ;
      taille = taille_graphe( G_9_flot ) ;

      /* Vérification de la forme du graphe. */

/* Les 3 lignes suivantes sont à décommenter une fois les fonctions écrites.
      assert( graphe_AR( G_9_flot ) ) ;
      assert( verifie_ponderation( G_9_flot ) ) ;
      parcours_profondeur_niveaux( G_9_flot , Sa ) ;
*/
/* Ces 2 lignes passent en commentaire au moment ou les précédentes sont activées. */
      for ( sommet = 1 ; sommet < taille ; sommet++ )
	  sommet_set_poids( G_9_flot , sommet , 1 ) ;

      for ( sommet = 0 ; sommet < taille ; sommet++ )
	  {assert( ! Sa || sommet_get_poids( G_9_flot , sommet ) > 0 ) ;
	   sommet_unset_poids( G_9_flot , sommet ) ;
	   assert( ! get_arc( G_9_flot , taille - 1 , sommet ) ) ;
	   assert( ! get_arc( G_9_flot , sommet , Sa ) ) ;
	  }

      /* La disposition des sommets est arrêtée et mémorisée. Les graphes de
	 flots et résiduels vont tous être affichés de la même manière. */

      definir_couleur( NOIR ) ;
      memorise_forme_graphe_flot( G_9_flot ) ;

      do {continuer = NON ;

	  /* Chaque itération utilise une nouvelle couleur
	     et alloue un nouveau graphe résiduel. */

          couleur_suivante( ) ;
	  t_gra graphe_residuel = nouveau_graphe_pondere( taille , - 100 , 100 ) ;

	  (void)printf( "Le graphe de flot donné :\n" ) ;
	  imprime_graphe( G_9_flot , DERNIERE_COULEUR , NON ) ;

	  /* Ici, on calcule le graphe résiduel. */

	  for ( i = 0 ; i < taille ; i++ )
	      for ( j = 0 ; j < taille ; j++ )
		  if ( i != j
		      && ( get_arc( G_9_flot , i , j ) || get_arc( G_9_flot , j , i ) ) )
		     calcule_residuel( G_9_flot , graphe_residuel , i , j ) ;

	  /* Ici, on calcule le meilleur chemin augmentant, à savoir celui
	     dont le maillon faible est aussi grand que possible.

	     Le tableau table_predecesseurs donne le prédécesseur de
	     chaque sommet le long du chemin retenu. */

	  for ( sommet = Sb ; sommet < taille ; sommet++ )
	      table_predecesseurs[ sommet ] = - 1 ;
	  table_predecesseurs[ Sa ] = Sa ;
	  dijkstra_maximise_le_min( Sa , graphe_residuel , table_predecesseurs ) ;

	  /* Si le chemin retenu ne permet pas de rejoindre le
	     puits, l'algorithme se termine. */

	  continuer = ( table_predecesseurs[ taille - 1 ] != - 1 ) ;

	  /* Le graphe résiduel est affiché avec le chemin augmentant en bleu. */

	  if ( continuer )
	     {sommet = taille - 1 ;
	      while ( sommet != Sa )
		    {set_couleur_arc( graphe_residuel , table_predecesseurs[ sommet ] ,
				      sommet , BLEU ) ;
		     sommet = table_predecesseurs[ sommet ] ;
		    }
	     }
	  (void)printf( "Le graphe résiduel et son meilleur chemin augmentant :\n" ) ;
	  imprime_graphe( graphe_residuel , DERNIERE_COULEUR , NON ) ;

	  /* Ici, on modifie le graphe de flot en changeant les flots le
	     long du chemin augmentant trouvé dans le graphe résiduel.

	     Le poids de modification poids_modif est la valeur du
	     maillon faible du chemin augmentant. Celle-ci correspond
	     au poids qui a été associé au puits lors du calcul du
	     du chemin augmentant. */

	  if ( continuer )
	     {int poids_modif = sommet_get_poids( graphe_residuel , taille - 1 ) ;
	      sommet = taille - 1 ;
	      while ( sommet != Sa )
		    {adapte_flot( G_9_flot , table_predecesseurs[ sommet ] ,
				 sommet , poids_modif ) ;
		     sommet = table_predecesseurs[ sommet ] ;
		    }
	     }

	  /* On jette le graphe résiduel et on recommence éventuellement. */

	  free( graphe_residuel ) ;
	 }
      while ( continuer ) ;

      /* L'affichage du résultat final. */

      (void)printf( "Le graphe de flot final où les arcs saturés sont en rouge :\n" ) ;
      imprime_graphe( G_9_flot , TOUT_NOIR , NON ) ;
      oublie_forme_graphe_flot( ) ;

     }

/* ------------------------------------------------------------ */
