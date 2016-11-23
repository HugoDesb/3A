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
tpl creation_liste_ptr(tpl l);
void afficher(tpl l);
void afficher_liste(tpl l);
int length(tpl l);
int lengthWhile(tpl l);
int length_ptr(tpl l);
int lengthWhile_ptr(tpl l);
tpl copie(tpl l);
tpl searchFor(int x, tpl l);
tpl copie_ptr(tpl l);
tpl searchFor_ptr(int x, tpl l);
tpl deleteFirst(int x, tpl l);
tpl deleteAll(int x, tpl l);
tpl copieInverse(tpl l);
tpl copieInverse_ptr(tpl l);
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
	/* printf("Longueur de la liste (recur_ptr) : %d\n",length_ptr(l)); */
	/* printf("Longueur de la liste (while_ptr) : %d\n",lengthWhile_ptr(l)); */

	//Tests 5éme question
	/* tpl newL,newL_ptr; */
	/* l=creation_liste(l); */
	/* newL = copie(l); */
	/* newL_ptr = copie_ptr(l); */
	/* printf("l : "); */
	/* afficher(l); */
	/* printf("newL : "); */
	/* afficher(newL); */
	/* printf("newL (ptr) : "); */
	/* afficher(newL_ptr); */

	//Tests 6éme question
	/* l=creation_liste(l); */
	/* int searchValue = 5; */
	/* printf("Item found ? %d\n",!est_vide(searchFor(searchValue,l))); */
	/* printf("Item found ? %d\n",!est_vide(searchFor_ptr(searchValue,l))); */

	//Tests 7éme question a)
	/* l=creation_liste(l); */
	/* afficher(l); */
	/* int searchValue = 5; */
	/* afficher(deleteFirst(searchValue, l)); */

	//Tests 7éme question b)
	/* l=creation_liste(l); */
	/* afficher(l); */
	/* int searchValue = 5; */
	/* afficher(deleteAll(searchValue, l)); */

	//Tests 8ème question
	/* l=creation_liste(l); */
	/* afficher(l); */
	/* tpl newL = copieInverse(l); */
	/* tpl newL_ptr = copieInverse_ptr(l); */
	/* printf("Copie : "); */
	/* afficher(newL); */
	/* printf("Copie (ptr): "); */
	/* afficher(newL); */
	
	return 0;
}
/**
 * Fonction qui affiche l'ensemble de la liste
 */
void afficher(tpl l){
	printf("(");
	afficher_liste(l);
	printf(")\n");
}
/**
 * Fonction qui est utilisée par afficher(tpl l). NE PAS APPELER
 */
void afficher_liste(tpl l){
	if(est_vide(queue_liste(l))){
		printf("%d",tete_liste(l));
	}else{
		printf("%d,",tete_liste(l));
		afficher_liste(queue_liste(l));
	}
}
/**
 * Fonction qui créé et rempli une liste selon les entrées
 * de l'utilisateur.
 * Un nombre négatif termine les entrées
 */
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
/**
 * Fonction qui créé et rempli une liste selon les entrées
 * de l'utilisateur.
 * Un nombre négatif termine les entrées
 * 
 * Utilise les pointeurs
 */
tpl creation_liste_ptr(tpl l){
	int val;
	tpl newL;
	do{
		printf("Entrez une valeur : ");
		scanf("%d",&val);
			if(val>=0){
				newL = (tpl)malloc(sizeof(t_list));
				newL->val = val;
				newL->next = l;
				l = newL;
		}
	}while(val>=0);
	return l;
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
tpl ajout_liste(int val, tpl l){
	tpl newL;
	newL = (tpl)malloc(sizeof(t_list));
	newL->val = val;
	newL->next = l;
	return newL;
}
/**
 * Renvoie la première valeur de la liste
 */
int tete_liste(tpl l){
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
 * Retourne la longueur de la liste
 * Utilise les pointeurs
 */
int length_ptr(tpl l){
	if(l==(tpl)NULL){
		return 0;
	}else{
		return 1+length(l->next);
	}
}
/**
 * Retourne la longueur de la liste
 */
int lengthWhile(tpl l){
	int length = 0;
	while(!est_vide(l)){
		length++;
		l = queue_liste(l);
	}
	return length;
}
/**
 * Retourne la longueur de la liste
 * Utilise les pointeurs
 */
int lengthWhile_ptr(tpl l){
	int length = 0;
	while(l==(tpl)NULL){
		length++;
		l = l->next;
	}
	return length;
}
/**
 * Copie une liste en respectant l'ordre
 */
tpl copie(tpl l){
	if(est_vide(l)){
		return cree_vide();
	}else{
		return ajout_liste(tete_liste(l), copie(queue_liste(l)));
	}
}
/**
 * Copie une liste en respectant l'ordre
 * Utilise les pointeurs
 */
tpl copie_ptr(tpl l){
	tpl queueListe;
	tpl newL;
	if(l==(tpl)NULL){
		return (tpl)NULL;
	}else{
		//copie de la queue de la liste
		queueListe = copie_ptr(l->next);
		//Ajout du premier element a la copie du reste
		newL = (tpl)malloc(sizeof(t_list));
		newL->val = l->val;
		newL->next = queueListe;
		return newL;
	}
}
/**
 * Recherche et renvoie l'adresse de l'élément de la liste dont la
 * valeur est égale a X
 * Si aucun élément trouvé, renvoie le pointeur NULL
 */
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
/**
 * Recherche et renvoie l'adresse de l'élément de la liste dont la
 * valeur est égale a X
 * Si aucun élément trouvé, renvoie le pointeur NULL
 * Utilise les pointeurs
 */
tpl searchFor_ptr(int x, tpl l){
	if(l==(tpl)NULL){
		return (tpl)NULL;
	}else{
		if(l->val==x){
			return l;
		}else{
			return searchFor_ptr(x, l->next);
		}
	}
}
/**
 * Recherche et supprime la 1ère occurrence de l'élément de la liste
 * dont la valeur est égale a X
 * Renvoie la liste moins cette éléments
 */
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
/**
 * Recherche et supprime toutes les occurrences de l'élément de la liste
 * dont la valeur est égale a X
 * Renvoie la liste moins ces éléments
 */
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
/**
 * Effectue une copie de la liste donnée en inversant l'ordre des valeurs
 * de cette dernière
 * Utilise les pointeurs
 */
tpl copieInverse_ptr(tpl l){
	tpl copie = (tpl)NULL;
	tpl curr = l;
	tpl newL;
	while(curr!=(tpl)NULL){
		//Ajout de l'élément dans copie
		newL = (tpl)malloc(sizeof(t_list));
		newL->val = l->val;
		newL->next = copie;
		copie = newL;

		curr = curr->next;
	}
	return copie;
}