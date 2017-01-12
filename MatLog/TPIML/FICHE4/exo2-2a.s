#------------------------------------------------------------------
# Fichier exo2-2a.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
#         Exercice 2-(i)
# Le programme de ce fichier ne fonctionne que lorsque un noyau
# (traitant des exceptions) du fichier noyau2-1.s est chargé
#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

	.text # Le programme de test fonctionne en mode utilisateur
	.globl main
main:
	
        #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main:

    #afficher une chaine de caractères
	la $a0, message
	li $v0, 4
	syscall

    #afficher un entier
	move $a0,$t0 
	li $v0, 1
	syscall

    #afficher une chaine de caractères
	la $a0, alaligne
	li $v0, 4
	syscall

	addi $t0,$t0, 1  # compteur + 1
	jal tempo    
	j boucle_main # le programme boucle indéfinimemnt

# ------------------------------------------------------------------
# Procedure tempo : temporisation de quelques secondes
#-------------------------------------------------------------------	
tempo:
	li $t1, 0x300000
boucle_tempo:
	beq $t1, $0, fin_tempo
	addi $t1, $t1, -1
	b boucle_tempo
fin_tempo:
	jr $ra

#-----------------------------------------------------------------
	.data  # Section des données utilisateur
message: .asciiz "J'ai même compris la multiprog : "
alaligne: .asciiz "\n"

#-------------------------------------------------------------