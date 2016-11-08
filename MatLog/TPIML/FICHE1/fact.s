#-----------------------------------------------------------------
#-- File name : fact.s
#-- Objet : TP Interface Matériel Logiciel  - Fiche 1
#--
#--     (Voir Cours, chapitre 2 - Langage d'Assemblage
#--                 transparents SPIM : exemple        )
#--  Algorithme SIGMA
# /* produit des 50 premiers entiers non nuls */
#----------------------------------------------------------------
	.data
# variables :
#    PRODUIT, COMPTEUR : entiers 
#    PRODUIT est en memoire et COMPTEUR dans $s0 
     	.align 2  # non necessaire 
PRODUIT : .space 4  # ou .word 0 pour faire PRODUIT <--- 0


	.text
	.globl main
main :
# debut :
debut :

# 	  PRODUIT <---1
	li $t0, 1
	sw $t0, PRODUIT($0)
#	  COMPTEUR <--- 50
	li $s0,50
#boucle: Si COMPTEUR < 1 aller a suite
	li $t1, 1
boucle:	

	blt $s0, $t1, suite
#        sinon 
#          PRODUIT <--- PRODUIT + COMPTEUR
	lw $t2, PRODUIT($0)
	mul $t2,$t2, $s0
	sw  $t2, PRODUIT($0)
#          COMPTEUR <--- COMPTEUR -1 
	addi $s0, $s0, -1
#          aller a boucle
	beq $0, $0, boucle    # ou j boucle
#        finsi
#suite: afficher(PRODUIT)
suite:  
# instructions pour afficher l'entier en mémoire à l'adresse SOMME($0)
	li $v0, 1    # system call code for print_int (see page A.49)
	lw $a0, PRODUIT($0) # integer to print
	syscall      # print
#fin
	jr $ra         # Retour de la procedure main.
#----------------------------------------------------------------------------

