#------------------------------------------------------------------
# Fichier noyau2-1.s
# Objet : TP Logiciel de base Fiche 4
# Ce fichier est une modification du programme de traitement
# d'exceptions par défaut de spim.
# Ce noyau (traitant des exceptions) traite l'IT clavier en
# affichant le message "IT clavier: " suivi du code du
# caractère tapé
# Pour les autres exceptions on  ne fait qu'afficher
# un message d'erreur et relancer le programme utilisateur.
#--------------------------------------------------------------------
# 1) L'entête original : vous pouvez passer


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

# Define the exception handling code.  This must go first!

	.kdata
# 2.1) Les constantes chaînes de caractères
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



# Table des processus :
# 120 octets par processus :
# 4 pour l'adresse du CO
# 126 pour les registres utilisables par l'utilisateur rangé dans l'odre croissant

process_table:

# Processus 0
PT_state: .word 0 	# Code statut du processus : 0 = Aucun processus ici, 1 = actif/pret, 2 = attente/veille
PT_pc: .word 0
PT_at: .word 0
PT_v0: .word 0
PT_v1: .word 0
PT_a0: .word 0
PT_a1: .word 0
PT_a2: .word 0
PT_a3: .word 0
PT_t0: .word 0
PT_t1: .word 0
PT_t2: .word 0
PT_t3: .word 0
PT_t4: .word 0
PT_t5: .word 0
PT_t6: .word 0
PT_t7: .word 0
PT_t8: .word 0
PT_t9: .word 0
PT_s0: .word 0
PT_s1: .word 0
PT_s2: .word 0
PT_s3: .word 0
PT_s4: .word 0
PT_s5: .word 0
PT_s6: .word 0
PT_s7: .word 0
PT_s8: .word 0
PT_gp: .word 0
PT_sp: .word 0
PT_ra: .word 0

.space 124 # Processus 1
.space 124 # Processus 2
.space 124 # Processus 3
.space 124 # Processus 4


current_process: .word 0
number_of_process: .word 5


# This is the exception handler code that the processor runs when
# an exception occurs. It only prints some information about the
# exception, but scan server as a model of how to write a handler.
#
# Because we are running in the kernel, we can use $k0/$k1 without
# saving their old values.

# 3) Le code du noyau.

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

    beq $t0, 10, process_exit		# break 10 -----> Arret du programme
    beq $t0, 12, process_standby	# break 12 -----> Mise en veille du programme
    beq $t0, 14, process_wakeup		# break 14 -----> Reveil du programme dont l'identifiant est dans $a0

	
	# afficher le message service non supporté
	la $a0, msg_brk_invalide
	li $v0,4
	syscall
	j ret

#------------------------------------------------------------
autres_exceptions:
        bnez $a0 pas_interruption 

interruption: # Forcément IT clavier
	# lire le code de la touche 
	lw $t0, 0xFFFF0004($0)
	beq, $t0, 99, change_current_process	# Si on a appuiyé sur la touche c (code 99), il faut alors passer la main à un autre processus

	la $a0, msgIt
	li $v0, 4
	syscall
	# Afficher le code de la touche
	move $a0, $t0
	li $v0, 1
	syscall
        # Passer à la ligne pour plus de "lisibilité"
	la $a0, alaligne
	li $v0, 4
	syscall
	j int_ret

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

	bne $k0 0x18 ok_pc	# Bad PC exception requires special checks
        nop

	mfc0 $a0, $14		# EPC
	andi $a0, $a0, 0x3	# Is EPC word-aligned?
	beq $a0, 0, ok_pc
        nop

	li $v0 10		# Exit on really bad PC
	syscall

ok_pc:
	li $v0 4		# syscall 4 (print_str)
	la $a0 __m2_
	syscall

	mtc0 $0, $13		# Clear Cause register


# Return from exception. Skip offending
# instruction to avoid infinite loop.
#
ret:	lw $v0 save_v0($0)	# Restore regs
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

# Return from interrupt. Don't skip instruction
# since it has not executed.
#
int_ret:lw $v0, save_v0($0)		# Restore regs
	lw $a0, save_a0($0) 
	lw $t0, save_t0($0)
	lw $t1, save_t1($0)
	mfc0 $k0 $14		# EPC (return to EPC)
	.set noat
	move $at $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0



change_current_process:
	# Il est temps de changer de processus en cours d'éxécution!

	# On va d'abord sauvegarder le compteur ordinal & les registres 

	# Calcul de l'ofset pour intéragir avec la bonne entrée de la table des processus
	lw $t0, current_process($0)
	li $t1, 124
	mul $t0, $t0, $t1

	mfc0 $t1 $14
	sw $t1, PT_pc($t0)	# Sauvegarde compteur Ordinal

	sw $k1, PT_at($t0)	# Sauvegarde $at

	lw $t1, save_v0($0)
	sw $t1, PT_v0($t0)

	sw $v1, PT_v1($t0)

	lw $t1, save_a0($0)
	sw $t1, PT_a0($t0)

	sw $a1, PT_a1($t0)
	sw $a2, PT_a2($t0)
	sw $a3, PT_a3($t0)


	lw $t1, save_t0($0)
	sw $t1, PT_t0($t0)

	lw $t1, save_t1($0)
	sw $t1, PT_t1($t0)

	sw $t2, PT_t2($t0)
	sw $t3, PT_t3($t0)
	sw $t4, PT_t4($t0)
	sw $t5, PT_t5($t0)
	sw $t6, PT_t6($t0)
	sw $t7, PT_t7($t0)
	sw $t8, PT_t8($t0)
	sw $t9, PT_t9($t0)

	sw $s0, PT_s0($t0)
	sw $s1, PT_s1($t0)
	sw $s2, PT_s2($t0)
	sw $s3, PT_s3($t0)
	sw $s4, PT_s4($t0)
	sw $s5, PT_s5($t0)
	sw $s6, PT_s6($t0)
	sw $s7, PT_s7($t0)
	sw $s8, PT_s8($t0)


	sw $gp, PT_gp($t0)
	sw $ra, PT_ra($t0)

select_process:
	# Maintenant, on sélectionne le processus suivant à exécuter
	lw $t0, current_process($0)
	lw $t1, number_of_process($0)

select_process_while:
	# Processus_suivant = ( processus_actuel + 1 ) % nombre_de_processus
	addi $t0, $t0, 1
	div $t0, $t1
	mfhi $t0

	mul $t2, $t0, 124

	# On continue que si le processus est pret, sinon on en choisit un autre
	li $t3, 1
	lw $t4, PT_state($t2)

	bne $t3, $t4, select_process_while

# On a sélectionné notre processus, on va alors charger ses registres et lui donner la main!
	move $t1, $t2
	sw $t0, current_process($0)

	lw $k0, PT_pc($t1)	# récupération compteur Ordinal
	lw $k1, PT_at($t1)	# Récupération de $at

	lw $v0, PT_v0($t1)
	lw $v1, PT_v1($t1)

	lw $a0, PT_a0($t1)
	lw $a1, PT_a1($t1)
	lw $a2, PT_a2($t1)
	lw $a3, PT_a3($t1)

	lw $t0, PT_t0($t1)
	sw $t0, save_t0($0)

	lw $t0, PT_t1($t1)
	sw $t0, save_t1($0)


	lw $t2, PT_t2($t1)
	lw $t3, PT_t3($t1)
	lw $t4, PT_t4($t1)
	lw $t5, PT_t5($t1)
	lw $t6, PT_t6($t1)
	lw $t7, PT_t7($t1)
	lw $t8, PT_t8($t1)
	lw $t9, PT_t9($t1)

	lw $s0, PT_s0($t1)
	lw $s1, PT_s1($t1)
	lw $s2, PT_s2($t1)
	lw $s3, PT_s3($t1)
	lw $s4, PT_s4($t1)
	lw $s5, PT_s5($t1)
	lw $s6, PT_s6($t1)
	lw $s7, PT_s7($t1)
	lw $s8, PT_s8($t1)

	lw $gp, PT_gp($t1)
	lw $ra, PT_ra($t1)

	lw $t0, save_t0($0)
	lw $t1, save_t1($0)

	.set noat
	move $at $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0


# le programme nous préviens de son arret, on prend acte et on passe au processus suivant
process_exit:
	lw $t0, current_process($0)
	li $t1, 124
	mul $t0, $t0, $t1

	sw $0, PT_state($t0) # On passe le 'code' etat du processus à 0 

# Maintenant, on peut passer au programme suivant (sans s'embetter à sauvegarder les registres du programme qui s'est arreté)
	j select_process


# le programme demande à être mis en veille, on prend acte et on passe au processus suivant
process_standby:
	lw $t0, current_process($0)
	li $t1, 124
	mul $t0, $t0, $t1

	li $t1, 2

	sw $t1, PT_state($t0) # On passe le 'code' etat du processus à 2

	## Avant d'aller sauvegarder le processus, on va avancer de d'une instruction le compteur ordinal
	mfc0 $t1 $14
	addiu $t1, $t1, 4
	mtc0 $t1 $14


# Maintenant, on peut penser a sauvegarder les registres et passer au programme suivant
	j change_current_process


# On va réveiller un processus dont le numéro est dans le registre $a0
process_wakeup:
	lw $t0, save_a0($0)
	li $t1, 124
	mul $t0, $t0, $t1

	# On vas quand même vérrifier qu'il sagit d'un processus en veille
	lw $t1, PT_state($t0)

	# On s'assure qu'on soit bien en train de "réveiller" un programme en veille uniquement
	addi $t1, $t1, -2
	bnez $t1, processus_pas_en_veille
	li $t1, 1
	sw $t1, PT_state($t0)

processus_pas_en_veille:

# Maintenant, on peut retourner dans le programme qui a fait la demande
	j ret


#-----------------------------------------------------------------
# Point d'entrée 
#----------------------------------------------------------------

	.globl __start
__start:


# ---------------------------------------------
# DEBUT PREPARATION DE LA TABLE DES PROCESSSUS

# On va initialiser la table des processus.
# C'est à dire qu'on va initialiser tous les etat des processus à 0.
lw $s0, number_of_process($0)

li $t1, 0
init_pt:
	mul $t2, $t1, 124 		# On calcule l'ofset necessaire pour mettre le status de tous les processus à 0 (pour aucun)
	sw $0, PT_state($t2)

	addi $t1, $t1, 1
	bne $s0, $t1, init_pt


# Maintenant, on vas charger nos divers programmes (2 pour le moment)
# Pas besoin d'initialiser les registres à 0, c'est au programme de se débrouiller.

# Processus 0 : le programme "ça marche!"
la $t0, main0($0)
li $t1, 1

sw $t0, PT_pc($0)		# On met dans le compteur ordinal le point de départ du programme
sw $t1, PT_state($0)	# On passe l'état du programme à 1 (= actif/pret)


# Processus 1 : le programme "J'ai compris la multiprogrammation!"
la $t0, main1($0)
li $t1, 1
li $t2, 124				# On saisie manuellement l'ofset pour avancer d'une entrée dans la table des processus

sw $t0, PT_pc($t2)		# On met dans le compteur ordinal le point de départ du programme
sw $t1, PT_state($t2)	# On passe l'état du programme à 1 (= actif/pret)

# Processus 2 : le programme "Autodestruction dans...."
la $t0, main2($0)
li $t1, 1
li $t2, 248				# On saisie manuellement l'ofset pour avancer de deux entrées dans la table des processus

sw $t0, PT_pc($t2)		# On met dans le compteur ordinal le point de départ du programme
sw $t1, PT_state($t2)	# On passe l'état du programme à 1 (= actif/pret)

# Processus 3 : le programme "Mise en veille dans...."
la $t0, main3($0)
li $t1, 1
li $t2, 372				# On saisie manuellement l'ofset pour avancer de deux entrées dans la table des processus

sw $t0, PT_pc($t2)		# On met dans le compteur ordinal le point de départ du programme
sw $t1, PT_state($t2)	# On passe l'état du programme à 1 (= actif/pret)

# Processus 4 : le programme "Réveil du processus 3"
la $t0, main4($0)
li $t1, 1
li $t2, 496				# On saisie manuellement l'ofset pour avancer de deux entrées dans la table des processus

sw $t0, PT_pc($t2)		# On met dans le compteur ordinal le point de départ du programme
sw $t1, PT_state($t2)	# On passe l'état du programme à 1 (= actif/pret)


# ---------------------------------------------
# FIN PREPARATION DE LA TABLE DES PROCESSSUS


# Maintenant, on va charger le programme numéro 0.
sw $0, current_process($0)
lw $k1, PT_pc($0)

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

# Commutation de contextes (changer status et PC de façon atomique
# avec les 2 instructions suivantes)
	rfe # Au prochain jr, status aura la valeur 0x103, et on sera donc
            # en mode utilisateur/interruptions démasquées (masque général
            # et masque IT receiver)
	jr $k1

# Terminer l'exécution du programme : service système exit
	li $v0 10
	syscall			# syscall 10 (exit)

# ---------------------------------------------------------------

