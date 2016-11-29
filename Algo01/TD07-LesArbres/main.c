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

int main(void);
tpa cree_feuille(int val);
int val_feuille(tpa a);
int est_feuille(tpa a);
tpa cree_noeud(char tag,tpa left,tpa right);
tpa arbre_fg(tpa a);
tpa arbre_fd(tpa a);
char arbre_etiq(tpa a);
void afficher(tpa a);
int nb_nodes(tpa a);
int nb_sheets(tpa a);
int depth(tpa a);
int sum(tpa a);
tpa mirror(tpa a);

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
	afficher(firstTree);printf("\n");
	printf("nbNodes : %d\n",nb_nodes(firstTree));
	printf("nbSheets : %d\n",nb_sheets(firstTree));
	printf("depth : %d\n",depth(firstTree));
	printf("sum : %d\n",sum(firstTree));
	printf("mirror :");
	afficher(mirror(firstTree));printf("\n");
	
	//num 2
	tpa sadd1 = cree_noeud('+', a, b);
	tpa sadd2 = cree_noeud('+', sadd1, c);
	tpa sadd3 = cree_noeud('+', sadd2, d);
	tpa smul = cree_noeud('*', e, f);
	tpa sadd4 = cree_noeud('+', smul, g);
	tpa secondTree = cree_noeud('+', sadd3, sadd4);
	afficher(secondTree);printf("\n");
	printf("nbNodes : %d\n",nb_nodes(secondTree));
	printf("nbSheets : %d\n",nb_sheets(secondTree));
	printf("depth : %d\n",depth(secondTree));
	printf("sum : %d\n",sum(secondTree));
		printf("mirror :");
	afficher(mirror(secondTree));printf("\n");
	
	//num 3
	tpa tadd1 = cree_noeud('+', f, h);
	tpa tmul1 = cree_noeud('*', e, tadd1);
	tpa tmul2 = cree_noeud('*', i, b);
	tpa tdiv1 = cree_noeud('/', d, b);
	tpa tdiv2 = cree_noeud('/', tmul2, tdiv1);
	tpa thirdTree = cree_noeud('-', tmul1, tdiv2);
	afficher(thirdTree);printf("\n");
	printf("nbNodes : %d\n",nb_nodes(thirdTree));
	printf("nbSheets : %d\n",nb_sheets(thirdTree));
	printf("depth : %d\n",depth(thirdTree));
	printf("sum : %d\n",sum(thirdTree));
	printf("mirror :");
	afficher(mirror(thirdTree));printf("\n");
	
	return 0;
}

void afficher(tpa a){
	if(est_feuille(a)){
		printf("%d",val_feuille(a));
	}else{
		printf("(");
		afficher(arbre_fg(a));
		printf(" %c ",arbre_etiq(a));
		afficher(arbre_fd(a));
		printf(")");
	}
}

tpa cree_feuille(int val){
	tpa sheet;
	sheet = (tpa)malloc(sizeof(t_tree));
	sheet->val = val;
	sheet->type = 1;
	return sheet;
}


int val_feuille(tpa a){
	return a->val;
}
int est_feuille(tpa a){
	return a->type;
}
tpa cree_noeud(char tag,tpa left,tpa right){
	tpa node;
	node = (tpa)malloc(sizeof(t_tree));
	node->tag = tag;
	node->left = left;
	node->right = right;
	node->type = 0;
	return node;
}
tpa arbre_fg(tpa a){
	return a->left;
}

tpa arbre_fd(tpa a){
	return a->right;
}
char arbre_etiq(tpa a){
	return a->tag;
}

int nb_nodes(tpa a){
	if(est_feuille(a)){
		return 0;
	}else{
		return 1+nb_nodes(arbre_fg(a))+nb_nodes(arbre_fd(a));
	}
}
int nb_sheets(tpa a){
	if(est_feuille(a)){
		return 1;
	}else{
		return nb_sheets(arbre_fg(a))+nb_sheets(arbre_fd(a));
	}
}
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
int sum(tpa a){
	if(est_feuille(a)){
		return val_feuille(a);
	}else{
		return sum(arbre_fg(a))+sum(arbre_fd(a));
	}
}
tpa mirror(tpa a){
	if(est_feuille(a)){
		return a;
	}else{
		return cree_noeud(arbre_etiq(a),mirror(arbre_fd(a)) , mirror(arbre_fg(a)));
	}
}
