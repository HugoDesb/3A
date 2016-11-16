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

#define N1 5


typedef struct list{
	int val;
	struct list *  next;
} t_list, * tpl;


tpl cree_vide(void);
int est_vide(tpl l);
tpl ajout_liste(int val, tpl l);
int tete_liste(tpl l);
tpl queue_liste(tpl l);
tpl creation_liste(tpl l);
void afficher(tpl l);
void afficher_liste(tpl l);
int length(tpl l);
int lengthWhile(tpl l);
tpl copie(tpl l);
tpl searchFor(int x, tpl l);
tpl deleteFirst(int x, tpl l);
tpl deleteAll(int x, tpl l);
tpl copieInverse(tpl l);

int main(void){

	tpl l = cree_vide();

	//Tests première question
	/* int shouldBeEmpty = est_vide(l); */
	/* printf("shouldBeEmpty : %d\n",shouldBeEmpty); */
	/* l = ajout_liste(4,l); */

	/* int headShouldBeFour = (4==tete_liste(l)); */
	/* printf("headShouldBeFour : %d\n",headShouldBeFour); */
	/* int queueShouldBeEmpty = est_vide(queue_liste(l)); */
	/* printf("queueshouldbeempty : %d\n",queueShouldBeEmpty); */
	/* l = ajout_liste(5, l); */

	/* int headShouldBeFive = (5==tete_liste(l)); */
	/* printf("headshouldbefive : %d\n", headShouldBeFive); */
	/* int queueShouldBeFour = (4==tete_liste(queue_liste(l))); */
	/* printf("queueshouldbefour : %d\n", queueShouldBeFour); */

	//Tests 2ème question
	/* l = creation_liste(l); */
	/* afficher(l); */
	
	//Tests 3ème question
	/* l = ajout_liste(5, l); */
	/* l = ajout_liste(4, l); */
	/* l = ajout_liste(3, l); */
	/* l = ajout_liste(2, l); */
	/* l = ajout_liste(1, l); */
	/* afficher(l); */

	//Tests 4éme question
	/* l = creation_liste(l); */
	/* afficher(l); */
	/* printf("Longueur de la liste (recur) : %d\n",length(l)); */
	/* printf("Longueur de la liste (while) : %d\n",lengthWhile(l)); */

	//Tests 5éme question
	/* tpl newL; */
	/* l=creation_liste(l); */
	/* newL = copie(l); */
	/* printf("l : "); */
	/* afficher(l); */
	/* printf("newL : "); */
	/* afficher(newL); */



	//Tests 6éme question
	/* l=creation_liste(l); */
	/* int searchValue = 5; */
	/* printf("Item found ? %d\n",!est_vide(searchFor(searchValue,l)));	 */

	//Tests 7éme question a)
	/* l=creation_liste(l); */
	/* afficher(l); */
	/* int searchValue = 5; */
	/* afficher(deleteFirst(searchValue, l)); */

	//Tests 7éme question b)
	l=creation_liste(l);
	afficher(l);
	int searchValue = 5;
	afficher(deleteAll(searchValue, l));
	
	return 0;
}

void afficher(tpl l){
	printf("(");
	afficher_liste(l);
	printf(")\n");
}
void afficher_liste(tpl l){
	if(est_vide(queue_liste(l))){
		printf("%d",tete_liste(l));
	}else{
		printf("%d,",tete_liste(l));
		afficher_liste(queue_liste(l));
	}
}
tpl creation_liste(tpl l){
	int val;
	do{
		printf("Entrez une valeur : ");
		scanf("%d",&val);
		if(val>=0){
			l = ajout_liste(val, l);
		}
	}while(val>=0);
	return l;
}
tpl cree_vide(void){
	return (tpl)NULL;
}

int est_vide(tpl l){
	return l==cree_vide();
}
tpl ajout_liste(int val, tpl l){
	tpl newL;
	newL = (tpl)malloc(sizeof(t_list));
	newL->val = val;
	newL->next = l;
	return newL;
}
int tete_liste(tpl l){
	assert(l);
	return l->val;
}
tpl queue_liste(tpl l){
	assert(l);
	return l->next;
}
int length(tpl l){
	if(est_vide(l)){
		return 0;
	}else{
		return 1+length(queue_liste(l));
	}
}
int lengthWhile(tpl l){
	int length = 0;
	while(!est_vide(l)){
		length++;
		l = queue_liste(l);
	}
	return length;
}

tpl copie(tpl l){
	if(est_vide(l)){
		return cree_vide();
	}else{
		return ajout_liste(tete_liste(l), copie(queue_liste(l)));
	}
}
tpl searchFor(int x, tpl l){
	if(est_vide(l)){
		return cree_vide();
	}else{
		if(tete_liste(l)==x){
			return l;
		}else{
			return searchFor(x, queue_liste(l));
		}
	}
}
tpl deleteFirst(int x , tpl l){
	tpl curr = l;
	tpl suiv = l->next;
	tpl ret = l;
	int found = 0;
	
	if(l->val != x){
		while(suiv!=(tpl)NULL && !found){
			if(suiv->val == x){
				curr->next = suiv->next;
				free(suiv);
				found = 1;
			}else{
				curr = suiv;
				suiv = suiv->next;
			}
		}
	}else{
		//Cas où l'élément a supprimer est le 1er
		ret = l->next;
		free(l);
	}
	return ret;
}
tpl deleteAll(int x , tpl l){
	tpl curr = l;
	tpl suiv = l->next;
	tpl ret = l;

	
	if(l->val != x){
		while(suiv!=(tpl)NULL){
			if(suiv->val == x){
				curr->next = suiv->next;
				free(suiv);
			}else{
				curr = suiv;
				suiv = suiv->next;
			}
		}
	}else{
		//Cas où l'élément a supprimer est le 1er
		ret = deleteAll(x,l->next);
		free(l);
	}
	return ret;
}
tpl copieInverse(tpl l){
	tpl copie = cree_vide();
	tpl curr = l;
	while(!est_vide(curr)){
		copie = ajout_liste(tete_liste(curr), copie);
		curr = tete_liste(curr);
	}
	return copie;
}
