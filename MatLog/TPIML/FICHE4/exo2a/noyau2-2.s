#------------------------------------------------------------------
# Fichier noyau2-2.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
# Ce fichier est une modification du programme de traitement
# d'exceptions par défaut de spim.
# Ce noyau (traitant des exceptions) traite l'IT clavier en
# affichant le message "IT clavier: " suivi du code du
# caractère tapé
# Pour les autres exceptions on  ne fait qu'afficher
# un message d'erreur et relancer le programme utilisateur.
#--------------------------------------------------------------------
# 1) L'entête original : vous pouvez passer
#------------------------------------------

# SPIM S20 MIPS simulator.
# The default trap handler for spim.
#
# Copyright (C) 1990-2003 James Larus, larus@cs.wisc.edu.
# ALL RIGHTS RESERVED.
#
# SPIM is distributed under the following conditions:
#
# You may make copies of SPIM for your own use and modify those copies.
#
# All copies of SPIM must retain my name and copyright notice.
#
# You may not sell SPIM or distributed SPIM in conjunction with a commerical
# product or service without the expressed written consent of James Larus.
#
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.
#

# $Header: $


# 2) Les données du noyau :
#--------------------------

# Define the exception handling code.  This must go first!

	.kdata
# 2.1) Les constantes chaînes de caractères
#------------------------------------------
msgBreak: .asciiz "Break "
msg_brk_invalide: .asciiz "Service systeme non implante\n"
alaligne: .asciiz "\n"
msgIt: .asciiz "IT clavier: "


__m1_:	.asciiz "  Exception "
__m2_:	.asciiz " occurred and ignored\n"
__e0_:	.asciiz "  [Interrupt] "
__e1_:	.asciiz	""
__e2_:	.asciiz	""
__e3_:	.asciiz	""
__e4_:	.asciiz	"  [Unaligned address in inst/data fetch] "
__e5_:	.asciiz	"  [Unaligned address in store] "
__e6_:	.asciiz	"  [Bad address in text read] "
__e7_:	.asciiz	"  [Bad address in data/stack read] "
__e8_:	.asciiz	"  [Error in syscall] "
__e9_:	.asciiz	"  [Breakpoint] "
__e10_:	.asciiz	"  [Reserved instruction] "
__e11_:	.asciiz	""
__e12_:	.asciiz	"  [Arithmetic overflow] "
__e13_:	.asciiz	"  [Inexact floating point result] "
__e14_:	.asciiz	"  [Invalid floating point result] "
__e15_:	.asciiz	"  [Divide by 0] "
__e16_:	.asciiz	"  [Floating point overflow] "
__e17_:	.asciiz	"  [Floating point underflow] "
# On range les adresses des divers message dans un tableau indexé
# pour pouvoir les afficher en utilisant le même "bout de code"
__excp:	.word __e0_,__e1_,__e2_,__e3_,__e4_,__e5_,__e6_,__e7_,__e8_,__e9_
	.word __e10_,__e11_,__e12_,__e13_,__e14_,__e15_,__e16_,__e17_
#les 4 mots ci-dessous sont utilisés pour sauvegarder 5 registres $v0, $a0,
# $t0, et $t1
# le registre $at est sauvegardé dans le registre $k1
save_v0:.word 0
save_a0:.word 0
save_t0:.word 0
save_t1:.word 0

#Table des processus
#sauvegarde des valeurs
sv_v0:.word 0
sv_a0:.word 0
sv_ra:.word 0
sv_at:.word 0
sv_t0:.word 0
sv_t1:.word 0
sv_pc:.word 0 #compteur
sv_etat:.word 0 #code statut du processus (0 marche pas) (1 marche) (2 veille) (3 pause envoi) (4 pause recep)

message:.word 0

#entrée 1
.space 36
#entrée 2
.space 36
#entrée 3
.space 36
#entrée 4
.space 36
#entrée 5
.space 36
#entrée 6
.space 36
#entrée 7
.space 36

sv_elu:.word 0
nb_processus:.word 8



# This is the exception handler code that the processor runs when
# an exception occurs. It only prints some information about the
# exception, but scan server as a model of how to write a handler.
#
# Because we are running in the kernel, we can use $k0/$k1 without
# saving their old values.

# 3) Le code du noyau.
#---------------------
	.ktext 0x80000080
	.set noat
	move $k1 $at		# Save $at
	.set at
	sw $v0, save_v0($0)	# Not re-entrent and we can't trust $sp
	sw $a0, save_a0($0)	# But, we need to use these registers
	sw $t0, save_t0($0)
	sw $t1, save_t1($0)

	mfc0 $k0 $13		# Cause register
        srl $a0 $k0 2		# Extract ExcCode Field
	andi $a0 $a0 0xf

        # Test si appel système break, et  on laisse tel quel le traitement
        # des autres exceptions.
        bne $a0, 9, autres_exceptions
appel_systeme_break:
        mtc0 $0, $13    # Clear Cause register

        #affiche "Break"
        la  $a0,  msgBreak
        li  $v0, 4
        syscall

	#$t0 <- numero du service
	mfc0 $t0, $14 # EPC : adresse de l'instruction break
	lw $t0, 0($t0) # Code de l'instruction breakA
	srl $t0, $t0, 11
        #Ecrire le numéro du break
        move $a0,$t0
        li  $v0, 1
        syscall
      	la  $a0, alaligne
        li  $v0,  4
        syscall

	beq $t0, 10, quitter_processus		# break 10 : Arret du programme
	beq $t0, 12, pause_processus	# break 12 : Mise en veille du programme
	beq $t0, 14, reveil_processus		# break 14 : Reveil du programme dont l'identifiant est dans $a0

	beq $t0, 16, envoi_pause # break 16 : Mise en attente du programme  de reception
	beq $t0, 18, recev_pause# break 18 : Mise en attente du programme d'envoie



	# afficher le message service non supporté
	la $a0, msg_brk_invalide
	li $v0,4
	syscall
	j ret

#arrete un processus
quitter_processus:
	lw $t0, sv_elu($0)
	li $t1, 36
	mul $t0,$t0,$t1

	li $t1, 0

	sw $t1, sv_etat($t0)

	j choix_process

#met en pause un processus
pause_processus:
	lw $t0, sv_elu($0)
	li $t1, 36
	mul $t0, $t0, $t1

	li $t1, 2

	sw $t1, sv_elu($t0)

	mfc0 $t1, $14
	addiu $t1, $t1, 4
	mtc0 $t1, $14

	j changement_processus

#reveil un processus
reveil_processus:
	lw $t0, save_a0($0)
	li $t1, 36
	mul $t0, $t0, $t1

	lw $t1, sv_elu($t0)

	addi $t1, $t1, -2
	bnez $t1, pasdeveille
	li $t1, 1
	sw $t1, sv_elu($t0)

pasdeveille:

	j ret




#------------------------------------------------------------
autres_exceptions:
        bnez $a0 pas_interruption
interruption: # Forcément IT clavier
	la $a0, msgIt
	li $v0, 4
	syscall
	# lire le code de la touche et l'afficher
	lw $t0, 0xFFFF0004($0)
	beq $t0, 115, changement_processus
	# regarder la touche sur la quelle on appuie
	# si on a appuiyé sur s (115) changement de processus
	move $a0, $t0
	li $v0, 1
	syscall
        # Passer à la ligne pour plus de "lisibilité"
	la $a0, alaligne
	li $v0, 4
	syscall

	j int_ret


changement_processus:
  #processus permettant de changer de processus en cours

	lw $t0, sv_elu($0)
	li $t1, 36
	mul $t0, $t0, $t1

	mfc0 $t1 $14
	sw $t1,sv_pc($t0) #sauvegarde du compteur
	sw $k1, sv_at($t0) #sauvegarde at
	lw $t1, save_v0($0) #sauvegarde v0
	sw $t1, sv_v0($t0)
	lw $t1, save_a0($0) #sauvegarde a0
	sw $t1, sv_a0($t0)
	lw $t1, save_t0($0) #sauvegarde t0
	sw $t1, sv_t0($t0)
	lw $t1, save_t1($0) #sauvegarde t1
	sw $t1, sv_t1($t0)
	sw  $ra, sv_ra($t0) #sauvegarde ra


choix_process:

	lw $t0, sv_elu($0)
	lw $t1, nb_processus($0)

	addi	$t0, $t0, 1			# proccess_suivant = processus_actuel + 1
	rem $t0, $t0, $t1				# mod 8
	sw $t0, sv_elu($0)
	#move $t2, $t0

	lw $t0, sv_elu($0)
	li $k0, 36
	mul $k0, $t0, $k0

	#on compare la valeur etat du processus
	li $t3, 1
	lw $t4, sv_etat($k0)

	bne $t3, $t4, choix_process

	#restauration des régistres
	lw $k1, sv_at($k0)
	lw $a0, sv_a0($k0)
	#lw $v0, sv_v0($v0)
	lw $t0, sv_t0($k0)
	lw $t1, sv_t1($k0)
	lw $ra, sv_ra($k0)
	lw $k0, sv_pc($k0)


	.set noat
	move $at $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0

pas_interruption:
	# Print information about exception.
	#
	li $v0 4		# syscall 4 (print_str)
	la $a0 __m1_
	syscall

	li $v0 1		# syscall 1 (print_int)
        srl $a0 $k0 2		# Extract ExcCode Field
	andi $a0 $a0 0xf
	syscall

	li $v0 4		# syscall 4 (print_str)
	lw $a0 __excp($k0)
	syscall

	li $v0 10		# Exit
	syscall


ret:
# Return from exception. Skip offending
# instruction to avoid infinite loop.
#
	lw $v0 save_v0($0)	# Restore regs
	lw $a0 save_a0($0)
	lw $t0 save_t0($0)
	lw $t1 save_t1($0)

	mfc0 $k0 $14		# EPC
	addiu $k0 $k0 4		# Return to next instruction
	.set noat
	move $at $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0

int_ret:
# Return from interrupt. Don't skip instruction
# since it has not executed.
#
  lw $v0, save_v0($0)		# Restore regs
	lw $a0, save_a0($0)
	lw $t0, save_t0($0)
	lw $t1, save_t1($0)
	mfc0 $k0 $14		# EPC (return to EPC)
	.set noat
	move $at $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0



envoi_pause:
#message dans v0 et adresse dans a0
	lw $v0, save_v0($0)
	lw $a0, save_a0($0)

	lw $t0, sv_elu($0)
	li $t1, 36
	mul $t0, $t0, $t1
	
	li $t1, 3 #etat 3 pause envoi
	sw $t1, sv_etat($t0)

	sw $v0, message($t0)

	#récupération adresse processus qui recoit (dans notre cas 7*36)
	li $t2, 36
	mul $t2, $t2, $a0 #dans a0 il y a le destinataire
	lw $t3, sv_etat($t2)
	#on regarde si le processus de reception est pret aussi
	beq $t3, 4, test_envoi

	j choix_process


test_envoi:

	#sw $v0, message($t0) #stocke le message dans message du processus 6
	lw $t3, message($t0) #récupère le message de proc 6
	sw $t3, message($t2)#le stocke dans message de processus 7

	#reveil des processus
	li $t3, 1
	sw $t3, sv_etat($t0)
	sw $t3, sv_etat($t2)

	#affichage du message
	la $a0,essai
	li $v0, 4
	syscall
	lw $a0, message($t0)
	li $v0, 1
	syscall
	la $a0, sautligne
	li $v0, 4
	syscall

	j choix_process



recev_pause:
	#adresse dans a0 (6)
	lw $a0, save_a0($0)
	lw $t0, sv_elu($0)
	li $t1, 36
	mul $t0, $t0, $t1
	li $t1, 4 		#etat 4 pause recep
	sw $t1, sv_etat($t0)

	#on regarde si le programme à a0(6)*36 est à l'état 3
	li $t2, 36
	mul $t2, $t2, $a0
	lw $t3, sv_etat($t2)
	#on regarde si le processus d'envoi est pret aussi
	beq $t3, 3, recep_envoi


	j choix_process

recep_envoi:

	lw $t3, message($t2) #récupère le message de proc 6
	sw $t3, message($t0)#le stocke dans message de processus 7

	#reveil des processus
	li $t3, 1
	sw $t3, sv_etat($t0)
	sw $t3, sv_etat($t2)

	#affichage du message
	la $a0,essai
	li $v0, 4
	syscall
	lw $a0, message($t0)
	li $v0, 1
	syscall
	la $a0, sautligne
	li $v0, 4
	syscall

j choix_process


#-----------------------------------------------------------------
# Point d'entrée
#----------------------------------------------------------------

	.globl __start
__start:

#Initialisation table des processus
#processus0
la $k0, main($0)
li $t1, 1
sw $k0, sv_pc($0)
sw $t1, sv_etat($0)

#point d'entrée processus 1
la $k0, main1
li $t1, 1
sw $k0, sv_pc+36($0)
sw $t1, sv_etat+36($0)


#point d'entrée processus 2
la $k0, main2
li $t1, 1
sw $k0, sv_pc+72($0)
sw $t1, sv_etat+72($0)

#point d'entrée processus 3
la $k0, main3
li $t1, 1
sw $k0, sv_pc+108($0)
sw $t1, sv_etat+108($0)

#point d'entrée processus 4
la $k0, main4
li $t1, 1
sw $k0, sv_pc+144($0)
sw $t1, sv_etat+144($0)

#point d'entrée processus 5
la $k0, main5
li $t1, 1
sw $k0, sv_pc+180($0)
sw $t1, sv_etat+180($0)

#point d'entrée processus 6
la $k0, main6
li $t1, 1
sw $k0, sv_pc+216($0)
sw $t1, sv_etat+216($0)

#point d'entrée processus 7
la $k0, main7
li $t1, 1
sw $k0, sv_pc+252($0)
sw $t1, sv_etat+252($0)

# Configurer le receiver en mode interruptions (mettre 2 dans
# le bit interrupt enable du registre de controle du receiver
# -adresse 0xffff0000)
	li $t0, 2
	sw $t0, 0xffff0000($0) # receiver en mode interrupt
# Lancer le programme de test à l'étiquette main
# Le programme de test fonctionne en mode utilisateur
	# On modifie le registre status en lui affectant la valeur
        # 0x0000010C. On reste donc en mode maître interruptions
        # masquées (les 2 bits de poids faibles sont à 0)
	li $k0, 0x10C
	mtc0 $k0, $12
	# mettre l'adresse du point d'entrée du programme de test dans $k0
	la $k0, main
	# Commutation de contextes (changer status et PC de façon atomique
        # avec les 2 instructions suivantes)
	rfe # Au prochain jr, status aura la valeur 0x103, et on sera donc
            # en mode utilisateur/interruptions démasquées (masque général
            # et masque IT receiver)
	jr $k0

# ---------------------------------------------------------------

#-----------------------------------------------------------------
.data  # Section des données utilisateur
essai: .asciiz "Msg recu! : "
sautligne: .asciiz "\n"
