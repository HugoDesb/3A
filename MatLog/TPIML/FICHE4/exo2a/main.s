#------------------------------------------------------------------
# Fichier exo2-1.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
#         Exercice 2-(i)
# Le programme de ce fichier ne fonctionne que lorsque un noyau
# (traitant des exceptions) du fichier noyau2-1.s est chargé
#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

	.text # Le programme de test fonctionne en mode utilisateur
	.globl main0
main0:
	
        #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main0:
	la $a0, message0
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo
	j boucle_main0 # le programme boucle indéfinimemnt

#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------
	.globl main1
main1:
	
        #$t0 contiendra le compteur
	move $t0, $0
	
boucle_main1:

    #afficher une chaine de caractères
	la $a0, message1
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
	j boucle_main1 # le programme boucle indéfinimemnt


#-----------------------------------------------------------------
# programme de test : Se met en veille
#------------------------------------------------------------
	.globl main2
main2:
	
        #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main2:
	la $a0, message2
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo

	break 12


#-----------------------------------------------------------------
# programme de test : Se ferme
#------------------------------------------------------------
	.globl main3
main3:
	
        #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main3:
	la $a0, message3
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo

	break 10

#-----------------------------------------------------------------
# programme de test : Reveille le processus 2
#------------------------------------------------------------
	.globl main4
main4:
	
        #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main4:
	la $a0, message4
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo

	# réveille processus 2
	li $a0, 2
	break 12


#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------
	.globl main5
main5:
	
        #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main5:
	la $a0, message5
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo
	j boucle_main5 # le programme boucle indéfinimemnt


#-----------------------------------------------------------------
# programme de test : Emetteur
#------------------------------------------------------------
	.globl main6
main6:
	
boucle_main6:
	la $a0, message6
	li $v0, 4
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	jal tempo

    li $a0, 7
    li $v0, 42
    break 16

	j boucle_main6 # le programme boucle indéfinimemnt


#-----------------------------------------------------------------
# programme de test : Receveur
#------------------------------------------------------------
	.globl main7
main7:
	
        #$t0 contiendra le compteur
	move $t0, $0	
boucle_main7:
	la $a0, message7
	li $v0, 4
	syscall
	
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo

	#bne $t0, 10, boucle_main7
	# après le break, le msg est dans $s0
    li $a0, 6
    break 18

	#la $a0, message72
	#li $v0, 4
	#syscall
	#li $a0,42
	#li $v0, 1
	#syscall
	#la $a0, alaligne
	#li $v0, 4
	#syscall

	#li $t0, 0


	j boucle_main7 # le programme boucle indéfinimemnt

    
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
message0: .asciiz "Ca marche! "
message1: .asciiz "J'ai meme compris la multiprog : "
message2: .asciiz "Processus 2 "
message3: .asciiz "Processus 3 "
message4: .asciiz "Processus 4 "
message5: .asciiz "Processus 5 "
message6: .asciiz "Processus 6 - envoyeur "
message7: .asciiz "Processus 7"
message72: .asciiz "Message recu = "
alaligne: .asciiz "\n"

#-------------------------------------------------------------

