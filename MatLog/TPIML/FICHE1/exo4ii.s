#-----------------------------------------------------------------
#-- File name : somme.s
#-- Objet : TP Interface Matériel Logiciel  - Fiche 1
#--
#--     (Voir Cours, chapitre 2 - Langage d'Assemblage
#--                 transparents SPIM : exemple        )
#--  Algorithme SIGMA
# /* Somme des 50 premiers entiers non nuls */
#----------------------------------------------------------------
	.data
# variables :
#    SOMME, COMPTEUR : entiers 
#    SOMME est en memoire et VALEUR dans $s0 
     	.align 2  # non necessaire 
SOMME : .space 4  # ou .word 0 pour faire SOMME <--- 0


	.text
	.globl main
main :
# debut :
debut :

# 	  SOMME <---0
	sw $0, SOMME($0)
#	  VALEUR <--- 50
	li $s0,0
#boucle: Si VALEUR < 1 aller a suite
	li $t1, 1
boucle:	

	blt $s0, $0, suite
#        sinon 
#          SOMME <--- SOMME + VALEUR
	lw $t2, SOMME($0)
	add $t2,$t2, $s0
	sw  $t2, SOMME($0)
#          COMPTEUR <--- VALEUR -1 
	addi $s0, $s0, -1
#          aller a boucle
	beq $0, $0, boucle    # ou j boucle
#        finsi
#suite: afficher(SOMME)
suite:  
# instructions pour afficher l'entier en mémoire à l'adresse SOMME($0)
	li $v0, 1    # system call code for print_int (see page A.49)
	lw $a0, SOMME($0) # integer to print
	syscall      # print
#fin
	jr $ra         # Retour de la procedure main.
#----------------------------------------------------------------------------

