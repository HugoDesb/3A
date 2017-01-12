#------------------------------------------------------------------
# Fichier exo2-1.s
# Objet : TP Logiciel de base Fiche 4
#         Exercice 2-(i)
# Le programme de ce fichier ne fonctionne que lorsque un noyau
# (traitant des exceptions) du fichier noyau2-1.s est chargé
#-----------------------------------------------------------------

#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

	.text # Le programme de test fonctionne en mode utilisateur
	.globl main0
main0:
	
    #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main0:
	la $a0, str_camarche
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, str_sautligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo0
	j boucle_main0 # le programme boucle indéfinimemnt


# Procedure tempo1 : temporisation de quelques secondes
tempo0:
	li $t1, 0x300000
boucle_tempo0:
	beq $t1, $0, fin_tempo0
	addi $t1, $t1, -1
	b boucle_tempo0
fin_tempo0:
	jr $ra

#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

	.globl main1
main1:
	
    #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main1:
	la $a0, str_multiprog
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, str_sautligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo1
	j boucle_main1 # le programme boucle indéfinimemnt


# Procedure tempo2 : temporisation de quelques secondes
tempo1:
	li $t1, 0x300000
boucle_tempo1:
	beq $t1, $0, fin_tempo1
	addi $t1, $t1, -1
	b boucle_tempo1
fin_tempo1:
	jr $ra


#-----------------------------------------------------------------
# programme de test : Ce programme boucle et se termine quand le compteur arrive à 0
#------------------------------------------------------------

	.globl main2
main2:
	
    #$t0 contiendra le compteur
	li $t0, 5
	
boucle_main2:
	la $a0, str_selfdestruct
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, str_sautligne
	li $v0, 4
	syscall
	addi $t0, $t0, -1
	jal tempo2
	bnez $t0, boucle_main2 # le programme boucle indéfinimemnt

	break 10 # Arret du programme

# Procedure tempo2 : temporisation de quelques secondes
tempo2:
	li $t1, 0x300000
boucle_tempo2:
	beq $t1, $0, fin_tempo2
	addi $t1, $t1, -1
	b boucle_tempo2
fin_tempo2:
	jr $ra


#-----------------------------------------------------------------
# programme de test : Ce programme boucle et se met en veille quand le compteur arrive à 0
#------------------------------------------------------------

	.globl main3
main3:
	
    #$t0 contiendra le compteur
	li $t0, 5
	
boucle_main3:
	la $a0, str_miseenveille
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, str_sautligne
	li $v0, 4
	syscall
	addi $t0, $t0, -1
	jal tempo3
	bnez $t0, boucle_main3 # le programme boucle indéfinimemnt

	break 12 # Mise en veille du programme

	j main3

# Procedure tempo3 : temporisation de quelques secondes
tempo3:
	li $t1, 0x300000
boucle_tempo3:
	beq $t1, $0, fin_tempo3
	addi $t1, $t1, -1
	b boucle_tempo3
fin_tempo3:
	jr $ra



#-----------------------------------------------------------------
# programme de test : Ce programme boucle et réveille le processus numéro 3
#------------------------------------------------------------

	.globl main4
main4:
	
	
boucle_main4:
	la $a0, str_reveil
	li $v0, 4
	syscall

	la $a0, str_sautligne
	li $v0, 4
	syscall
	jal tempo4

	li $a0, 3 
	break 14 # réveil du processus dont le numéro est dans le registre $a0

	j boucle_main4 # le programme boucle indéfinimemnt



# Procedure tempo4 : temporisation de quelques secondes
tempo4:
	li $t1, 0x300000
boucle_tempo4:
	beq $t1, $0, fin_tempo4
	addi $t1, $t1, -1
	b boucle_tempo4
fin_tempo4:
	jr $ra




#-----------------------------------------------------------------
	.data  # Section des données utilisateur
str_camarche: .asciiz "Ca marche! \o/ "
str_multiprog: .asciiz "J'ai compris la multiprogrammation! <3 "
str_selfdestruct: .asciiz "Autodestruction dans  "
str_miseenveille: .asciiz "Mise en veille du processus dans  "
str_reveil: .asciiz "Demande de reveil du processus 3! "
str_sautligne: .asciiz "\n"

#-------------------------------------------------------------

