#/*
#-------------------------------------------------------------------
#Nom du fichier : main.s
#Auteur :
#Objet : Module principale 
#--------------------------------------------------------------------
#*/
#
##include <stdio.h>
##include "arbres.h"
# Voir arbres.s pour la representation des types Arbre et Noeud.
##include "interface.h"
##include "memoire.h"
#
#/*
#cette fonction affiche un menu qui donne les commandes disponibles
#pour effectuer les operations sur les arbres  
#*/
#static void menu(void)
	.text
menu :
# menu appelle la fonction afficher_chaine.
# on sauvegarde l'adresse de retour de menu ($ra) sur la pile
	sw $ra, -4($sp)
	addiu $sp, $sp, -4
#
#	afficher_chaine("\n------------------Menu-----------------\n");
	la $a0, chmenu # Normalement la $a0, chmenu($0) MAIS SPIM accepte
                       # la $a0, chmenu
	jal afficher_chaine
#	afficher_chaine(" 1 : Creer un arbre vide \n");
	la $a0, ch1
	jal afficher_chaine
#	afficher_chaine(" 2 : Inserer un nouvel element \n");
	la $a0, ch2
	jal afficher_chaine
#	afficher_chaine(" 3 : Afficher l'arbre dans l'ordre croissant \n");
	la $a0, ch3
	jal afficher_chaine
#	afficher_chaine(" 4 : Rechercher un element\n");
	la $a0, ch4
	jal afficher_chaine
#	afficher_chaine(" 5 : Afficher la valeur minimale \n");
	la $a0, ch5
	jal afficher_chaine
#	afficher_chaine(" 6 : Supprimer un element ayant la valeur minimal \n");
	la $a0, ch6
	jal afficher_chaine
#	afficher_chaine(" 0 : Quitter \n");
	la $a0, ch0
	jal afficher_chaine
#	afficher_chaine("\n");
	la $a0, alaligne
	jal afficher_chaine
#	afficher_chaine("choix : \n");
	la $a0, choix
	jal afficher_chaine
#}
#	restauration $ra et retour a l'appelant
	addiu $sp, $sp, 4
	lw $ra, -4($sp)
        jr $ra

#
#int main(void)
	.globl main
main:
# resultat dans $v0 (convention de programmation du MIPS)
#{
#    int choix ;
# la variable locale choix sera  dans le registre $s0 (sauvegarde' 
# par l'appele')
#    int nb ;
# la variable locale nb sera dans le registre $s1 (sauvegarde' 
#  par l'appele')
#    
#
#     Arbre mon_arbre ;
#  la variable locale mon_arbre sera dans le registre $s2 (sauvegarde'
#  par l'appele')
#
	# main appelle d'autres fonctions: on sauvegardera $ra
	# main utilise $s0, $s1, et $s2. Il faudra les sauvegarder
        
	sw $ra, -4($sp)
	sw $s0, -8($sp)
	sw $s1, -12($sp)
	sw $s2, -16($sp)
	addiu $sp, $sp, -16

#    // initialisation des structures de donnees utilisees pour la
#    // gestion de la memoire.
#    init_mem(); 
	jal init_mem 
#    
#    mon_arbre = creer_arbre_vide() ; 
	jal creer_arbre_vide # resultat dans $v0 (decide' en examinant arbres.h) 
        move $s2, $v0
#    menu();    
	jal menu
#    choix = lire_entier() ;
	jal lire_entier # resultat dans $v0 (decide' en examinant inteface.h) 
	move $s0, $v0
#    while (choix != 0)
while: beq $s0, $0, fin_while
#    {
#        switch(choix)
# on traduit le switch en utilisant une jump table.
# valeur min de choix : 1, valeur max : 6, pas de branche default
        # si choix <= 0 aller a fin_switch
	ble $s0, $0, fin_switch
        # si choix > 6 aller a fin_switch
	li $t0, 6
	bgt $s0, $t0, fin_switch
        # aller a JT[choix]
        li $t0, 4
	mul $t0, $s0, $t0
	lw $t0, JT($t0)
	jr $t0
#        {
#            case 1 : 
case1:
#                   mon_arbre = creer_arbre_vide() ; 
         jal creer_arbre_vide
         move $s2, $v0
#                   break;
         j fin_switch 
#            case 2 : 
case2:
#                   afficher_chaine("nombre a inserer ? ");
	la $a0, saisieinserer # constante stockee dans la section .data
	jal afficher_chaine
#                   nb = lire_entier();
	jal lire_entier
	move $s1, $v0
#                   mon_arbre = inserer(mon_arbre, nb);
	move $a0, $s2
	move $a1, $s1
	jal inserer # resultat dans $v0
	move $s2, $v0

#                   break ;
         j fin_switch 
#
#            case 3 : 
case3:
#                   if (mon_arbre !=NULL)
          beq $s2,$0, elsemain1
#                        afficher_arbre_croissant(mon_arbre);
	move $a0, $s2
	jal afficher_arbre_croissant
	j finifmain1
#                   else
elsemain1:
#                       afficher_chaine(" arbre vide! \n");
         la $a0, arbrevide
         jal afficher_chaine
finifmain1:
#                   break ;
         j fin_switch 
#            case 4 : 
case4:
#                   afficher_chaine("nombre a rechercher ? ");
         la $a0, saisierechercher
         jal afficher_chaine
#                   nb = lire_entier();
         jal lire_entier
         move $s1, $v0
#                   if(rechercher(mon_arbre, nb) !=0)
	move $a0, $s2
	move $a1, $s1,
	jal rechercher # resultat dans $v0
	beq $v0, $0, elsemain2
#                        afficher_chaine (" present!\n");
	la $a0, present
	jal afficher_chaine
	b finifmain2
#                   else 
elsemain2:
#                        afficher_chaine(" absent!\n");
	la $a0, absent
	jal afficher_chaine
finifmain2:
#                   break;
         j fin_switch  
#           
#            case 5 : 
case5:
#                   afficher_min(mon_arbre);
	move $a0, $s2
	jal afficher_min
#                   break ;
         j fin_switch 
#           
#            case 6:
case6:
#                   mon_arbre = supprimer_min(mon_arbre); 
	move $a0, $s2
	jal supprimer_min
	move $s2, $v0 
#                   break ;
         j fin_switch 
#            
#         }
fin_switch:
#         menu();
         jal menu
#    choix = lire_entier() ;
        jal lire_entier 
        move $s0, $v0
#    }
        j while
fin_while:
#
#return(0);
	li $v0, 0
	# restauration $si et $ra puis retour a l'appelant
	addiu $sp, $sp, 16
	lw $ra, -4($sp)
	lw $s0, -8($sp)
	lw $s1, -12($sp)
	lw $s2, -16($sp)
	jr $ra
#}


	.data
# constantes chaines de caracteres utilisees dans la fonction menu
chmenu:	.asciiz "\n------------------Menu-----------------\n"
ch1:	.asciiz " 1 : Creer un arbre vide \n" 
ch2: 	.asciiz " 2 : Inserer un nouvel element \n"
ch3:	.asciiz " 3 : Afficher l'arbre dans l'ordre croissant \n"
ch4:	.asciiz " 4 : Rechercher un element\n"
ch5:	.asciiz " 5 : Afficher la valeur minimale \n"
ch6:	.asciiz " 6 : Supprimer un element ayant la valeur minimal \n"
ch0:	.asciiz " 0 : Quitter \n"
alaligne: .asciiz "\n"
choix :	.asciiz "choix : \n"

#constantes chaines de caracteres utilisees dans main
saisieinserer: .asciiz  "nombre a inserer ? "
saisierechercher: .asciiz "nombre a rechercher ? "
present: .asciiz " present!\n"
absent: .asciiz " absent!\n"
arbrevide: .asciiz " arbre vide! \n"

# jump table
	.align 2
	JT :
	.word 0 # mot perdu car choix=0 n'est pas une branche du switch	
	.word case1
	.word case2
	.word case3
	.word case4
	.word case5
	.word case6
	
#/*------------------------fin main.s------------------------------*/

