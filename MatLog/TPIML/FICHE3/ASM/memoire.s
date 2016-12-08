#/*
#-------------------------------------------------------------------
#Nom du fichier : memoire.s
#Auteur :
#Objet : Module implantant les fonctions d'allocation et de liberation
#        de la memoire  
#--------------------------------------------------------------------
#*/
##include <stdlib.h>
##include "arbres.h" 
##include "memoire.h" //pour verification de la coherence
#
#
#/*
#Code des fonctions definies dans le module (entetes dans memoire.h):
# - init_mem, my_malloc et my_free
#
#Pour simplifier on alloue la memoire par blocs de taille fixe (la taille
#d'un noeud). Les blocs libres sont stockees dans une pile.
#*/
#
##define MAX 400 // nombre maximum de blocs
#
#static Noeud memoire[MAX] ; // On reserve MAX blocs

# Le type Noeud est defini dans arbres.h. Comme indiqué dans arbres.s,
# un élément de type Noeud sera represente'
# dans une zone 16 octets (4 pour le champ info,
# 4 pour le champ fils_gauche, 4 pour le champ fils_droit, 
# et 4 pour le champ pere).
# Le champ info est a un deplacement 0 par rapport
# au debut de cette zone, le champ fils_gauche a un deplacement de 4,
# le champ fils_droit a un deplacement de 8, 
# et le champ pere a un deplacement de 12.
	.data
	.align 2	
memoire:
	.space 6400 # ON NE RESPECTE PAS LA SEMANTIQUE DU C QUI DIT
		    # QUE TOUTES LES VARIABLES GLOBALES SONT INITIALISEES
                    # A ZERO 
#static Arbre blocs_libres ; // Sommet de la pile des blocs libres
#Le type Arbre est defini dans arbres.h. Un Arbre est un pointeur
#sur un Noeud. Un élément de type Arbre occupe 4 octets en mémoire
# ou dans un registre (cf arbres.s).
blocs_libres:
	.word 0

#
#/* init_mem : Initialise les structures de donnees utilisees pour gerer
#              l'allocation et la liberation de la memoire 
#              On met tous les blocs libre sur une pile. 
#*/
#
#void init_mem(void)
	.text
	.globl init_mem
init_mem: 
#{
	#   int i ; #Sera stocké dans $s0
#   
	#   i=0 ;
	li $s0, $0	
	#   do
corps_while:
#   {
#       memoire[i].pere = (Noeud *)(&memoire[i+1]);
#       i=i+1;
	addi $s0, $s0, 1
#   } while (i<MAX-1);
	sub
apres_while:	
#   memoire[MAX-1].pere = NULL ; 
#   blocs_libres = memoire ;
#
	#}
	jr $ra #fin de fonction, retour a l'appelant
#/* my_malloc : alloue un bloc de taille TAILLE_NOEUD (fixe: cf arbres.h) et 
#               retourne l'adresse du bloc (retourne NULL si allocation 
#               impossible)
#*/
#void *my_malloc(void)
	.globl my_malloc
my_malloc:
	jr $ra  # A REMPLACER PAR LA TRADUCTION DU CODE C CI-DESSOUS
#{  
#   Arbre p;
#
#   p =  blocs_libres ;
#   if (p!=NULL)
#   {
#       blocs_libres = blocs_libres->pere ;
#   } 
#   return((void *)p);
#}
#
#/* my_free : libere le bloc passe en parametre.
#     ajoute le bloc au sommet de la pile des blocs
#     libres
#*/
#void my_free(void *bloc)
# Parametre bloc dans $a0
	.globl	my_free
my_free:
	jr $ra # A REMPLACER PAR LA TRADUCTION DU CODE C CI-DESSOUS 
#{
#   ((Arbre)bloc)->pere = blocs_libres ;
#   blocs_libres = (Arbre)bloc ;
#}
#/*----------------fin memoire.s--------------------------------------*/
#
