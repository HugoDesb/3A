/** 
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr>
 */


/**
 * @file exercice.c
 * 
 * File for all exercices of the fifth TP
 */

#include <stdio.h>
#include <assert.h>
#include <malloc.h>


typedef struct tree{
	int type;
	int val;
	struct tree * left;
	struct tree * right;
	char tag;
} t_tree, * tpa;

typedef struct list{
	tpa val;
	struct list *  next;
} t_list, * tpl;


int main(void);
tpa cree_feuille(int val);
int val_feuille(tpa a);
int est_feuille(tpa a);
tpa cree_noeud(char tag,tpa left,tpa right);
tpa arbre_fg(tpa a);
tpa arbre_fd(tpa a);
char arbre_etiq(tpa a);
int nb_nodes(tpa a);
int nb_sheets(tpa a);
int depth(tpa a);
int sum(tpa a);
tpa mirror(tpa a);
void print_infixe(tpa a);
void print_prefixe(tpa a);
void print_suffixe(tpa a);
void print_infixe_enum(tpa a);
void print_prefixe_enum(tpa a);
void print_suffixe_enum(tpa a);
void print_width(tpa a);

tpl cree_vide(void);
int est_vide(tpl l);
tpl ajout_liste(tpa val, tpl l);
tpa tete_liste(tpl l);
tpl queue_liste(tpl l);
int length(tpl l);
tpl copieInverse(tpl l);

int main(void){
	/*Question 2 - Trois arbres*/

	//values
	tpa a = cree_feuille(1);
	tpa b = cree_feuille(2);
	tpa c = cree_feuille(3);
	tpa d = cree_feuille(4);
	tpa e = cree_feuille(5);
	tpa f = cree_feuille(6);
	tpa g = cree_feuille(7);
	tpa h = cree_feuille(9);
	tpa i = cree_feuille(16);

	//num 1
	tpa fadd = cree_noeud('+', a, b);
	tpa fmul1 = cree_noeud('*', e, f);
	tpa fmul2 = cree_noeud('*', fadd, c);
	tpa fmul3 = cree_noeud('*', d, fmul1);
	tpa firstTree = cree_noeud('+', fmul2, fmul3);
	printf("Affichage infixe : ");print_infixe(firstTree);printf("\n");
	printf("Affichage infixe enum : ");print_infixe_enum(firstTree);printf("\n");
	printf("Affichage utilisant un parcours en largeur :\n");
	print_width(firstTree);printf("\n");
	printf("nbNodes : %d\n",nb_nodes(firstTree));
	printf("nbSheets : %d\n",nb_sheets(firstTree));
	printf("depth : %d\n",depth(firstTree));
	printf("sum : %d\n",sum(firstTree));
	printf("mirror :");
	print_infixe(mirror(firstTree));printf("\n");

	printf("----------------------------------------\n");
	
	//num 2
	tpa sadd1 = cree_noeud('+', a, b);
	tpa sadd2 = cree_noeud('+', sadd1, c);
	tpa sadd3 = cree_noeud('+', sadd2, d);
	tpa smul = cree_noeud('*', e, f);
	tpa sadd4 = cree_noeud('+', smul, g);
	tpa secondTree = cree_noeud('+', sadd3, sadd4);
	printf("Affichage préfixe : ");print_prefixe(secondTree);printf("\n");
	printf("Affichage préfixe enum : ");print_prefixe_enum(secondTree);printf("\n");
	printf("Affichage utilisant un parcours en largeur :\n");
	print_width(secondTree);printf("\n");
	printf("nbNodes : %d\n",nb_nodes(secondTree));
	printf("nbSheets : %d\n",nb_sheets(secondTree));
	printf("depth : %d\n",depth(secondTree));
	printf("sum : %d\n",sum(secondTree));
	printf("mirror :");
	print_infixe(mirror(secondTree));printf("\n");

	printf("----------------------------------------\n");
		
	//num 3
	tpa tadd1 = cree_noeud('+', f, h);
	tpa tmul1 = cree_noeud('*', e, tadd1);
	tpa tmul2 = cree_noeud('*', i, b);
	tpa tdiv1 = cree_noeud('/', d, b);
	tpa tdiv2 = cree_noeud('/', tmul2, tdiv1);
	tpa thirdTree = cree_noeud('-', tmul1, tdiv2);
	printf("Affichage suffixe : ");print_suffixe(thirdTree);printf("\n");
	printf("Affichage suffixe enum : ");print_suffixe_enum(thirdTree);printf("\n");
	printf("Affichage utilisant un parcours en largeur :\n");
	print_width(thirdTree);printf("\n");
	printf("nbNodes : %d\n",nb_nodes(thirdTree));
	printf("nbSheets : %d\n",nb_sheets(thirdTree));
	printf("depth : %d\n",depth(thirdTree));
	printf("sum : %d\n",sum(thirdTree));
	printf("mirror :");
	print_infixe(mirror(thirdTree));printf("\n");

	
	
	return 0;
}
/**
 * Cree une feuille
 */
tpa cree_feuille(int val){
	tpa sheet;
	sheet = (tpa)malloc(sizeof(t_tree));
	sheet->val = val;
	sheet->type = 1;
	return sheet;
}
/**
 * Retourne la valeur de la feuille
 */
int val_feuille(tpa a){
	return a->val;
}
/**
 * Renvoie si l'arbre donné est une feuille
 */
int est_feuille(tpa a){
	return a->type;
}
/**
 * Cree un noeud et ajoute les deux arbres donnés respectivement a
 * gauche puis a droite
 */
tpa cree_noeud(char tag,tpa left,tpa right){
	tpa node;
	node = (tpa)malloc(sizeof(t_tree));
	node->tag = tag;
	node->left = left;
	node->right = right;
	node->type = 0;
	return node;
}
/**
 * Renvoie l'arbre gauche
 */
tpa arbre_fg(tpa a){
	return a->left;
}
/**
 * Renvoie l'arbre droite
 */
tpa arbre_fd(tpa a){
	return a->right;
}
/**
 * Renvoie l'étiquette de l'arbre
 */
char arbre_etiq(tpa a){
	return a->tag;
}
/**
 * Compte le nb de noeuds dans la programme
 */
int nb_nodes(tpa a){
	if(est_feuille(a)){
		return 0;
	}else{
		return 1+nb_nodes(arbre_fg(a))+nb_nodes(arbre_fd(a));
	}
}
/**
 * Compte le nb de feuilles dans la programme
 */
int nb_sheets(tpa a){
	if(est_feuille(a)){
		return 1;
	}else{
		return nb_sheets(arbre_fg(a))+nb_sheets(arbre_fd(a));
	}
}
/**
 * Renvoie la profondeur max de l'arbre
 */
int depth(tpa a){
	int depthLeft, depthRight;
	if(est_feuille(a)){
		return 1;
	}else{
		depthLeft = depth(arbre_fg(a));
		depthRight = depth(arbre_fd(a));
		if(depthLeft>=depthRight){
			return 1+depthLeft;
		}{
			return 1+depthRight;
		}
	}
}
/**
 * Renvoie la somme des nombres de l'arbre
 */
int sum(tpa a){
	if(est_feuille(a)){
		return val_feuille(a);
	}else{
		return sum(arbre_fg(a))+sum(arbre_fd(a));
	}
}
/**
 * Renvoie l'arbre symétrique a celui donné en paramètre
 */
tpa mirror(tpa a){
	if(est_feuille(a)){
		return a;
	}else{
		return cree_noeud(arbre_etiq(a),mirror(arbre_fd(a)), mirror(arbre_fg(a)));
	}
}
/**
 * Affichage infixe
 */
void print_infixe(tpa a){
	if(est_feuille(a)){
		printf("%d",val_feuille(a));
	}else{
		printf("(");
		print_infixe(arbre_fg(a));
		printf(" %c ",arbre_etiq(a));
		print_infixe(arbre_fd(a));
		printf(")");
	}
}
/**
 * Affichage préfixe
 */
void print_prefixe(tpa a){
	if(est_feuille(a)){
		printf("%d",val_feuille(a));
	}else{
		printf("(%c ",arbre_etiq(a));
		print_prefixe(arbre_fg(a));
		printf(" ");
		print_prefixe(arbre_fd(a));
		printf(")");
	}
}
/**
 * Affichage suffixe
 */
void print_suffixe(tpa a){
	if(est_feuille(a)){
		printf("%d",val_feuille(a));
	}else{
		printf("(");
		print_suffixe(arbre_fg(a));
		printf(" ");
		print_suffixe(arbre_fd(a));
		printf(" %c)",arbre_etiq(a));
	}
}
/**
 * Affichage infixe avec énumération
 */
void print_infixe_enum(tpa a){
	if(est_feuille(a)){
		printf("%d\n",val_feuille(a));
	}else{
		print_infixe(a);
		printf("\n");
		print_infixe_enum(arbre_fg(a));
		print_infixe_enum(arbre_fd(a));
	}
}
/**
 * Affichage préfixe avec énumération
 */
void print_prefixe_enum(tpa a){
	if(est_feuille(a)){
		printf("%d\n",val_feuille(a));
	}else{
		print_prefixe(a);
		printf("\n");
		print_prefixe_enum(arbre_fg(a));
		print_prefixe_enum(arbre_fd(a));
	}
}
/**
 * Affichage suffixe avec énumération
 */
void print_suffixe_enum(tpa a){
	if(est_feuille(a)){
		printf("%d\n",val_feuille(a));
	}else{
		print_suffixe(a);
		printf("\n");
		print_suffixe_enum(arbre_fg(a));
		print_suffixe_enum(arbre_fd(a));
	}
}
/**
 * Affichage en largeur
 */
void print_width(tpa a){
	//liste des éléments de même niveau
	tpl l = cree_vide();
	l = ajout_liste(a, l);
	//liste des éléments du niveau suivant
	tpl next = cree_vide();

	int hasSons = !est_feuille(a);
	while(hasSons){ //ici une condition d'arrêt sur la HAUTEUR

		hasSons = 0;
		
		//boucle sur tous les noeuds d'un niveau
		while(!est_vide(l)){
			if(est_feuille(tete_liste(l))){
				//si c'est une feuille, on affiche la valeur
				printf("%d ",val_feuille(tete_liste(l)));
			}else{
				//sinon, on affiche le tag et on ajoute les fils
				// a la liste des éléments du niveau suivant
				printf("%c ",arbre_etiq(tete_liste(l)));
				next = ajout_liste(arbre_fg(tete_liste(l)), next);
				next = ajout_liste(arbre_fd(tete_liste(l)), next);
				
				hasSons = 1;
			}
			l = queue_liste(l);
		}
		//fin de ligne
		printf("\n");
		//next devient l :  !A introduire dans le désordre !
		l = copieInverse(next);
		next = cree_vide();
	}
}
	


/**
 * Renvoie le pointeur vide
 */
tpl cree_vide(void){
	return (tpl)NULL;
}
/**
 * T si la liste est égale au pointeur null, F autrement
 */
int est_vide(tpl l){
	return l==cree_vide();
}
/**
 * Ajoute la valeur au début de la liste, renvoie la nouvelle liste
 */
tpl ajout_liste(tpa val, tpl l){
	tpl newL;
	newL = (tpl)malloc(sizeof(t_list));
	newL->val = val;
	newL->next = l;
	return newL;
}
/**
 * Renvoie la première valeur de la liste
 */
tpa tete_liste(tpl l){
	assert(l);
	return l->val;
}
/**
 * Renvoie le ptr vers l'élément suivant de la liste
 */
tpl queue_liste(tpl l){
	assert(l);
	return l->next;
}
/**
 * Retourne la longueur de la liste
 */
int length(tpl l){
	if(est_vide(l)){
		return 0;
	}else{
		return 1+length(queue_liste(l));
	}
}
 /**
 * Effectue une copie de la liste donnée en inversant l'ordre des valeurs
 * de cette dernière
 */
tpl copieInverse(tpl l){
	tpl copie = cree_vide();
	tpl curr = l;
	while(!est_vide(curr)){
		copie = ajout_liste(tete_liste(curr), copie);
		curr = queue_liste(curr);
	}
	return copie;
}



