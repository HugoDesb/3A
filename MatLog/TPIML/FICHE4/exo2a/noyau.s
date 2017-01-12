#------------------------------------------------------------------
# Fichier noyau2-1.s
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

# On crée une table des processus contenant le contexte des registres
TCP:
# ici on declare les registres du processus 0 
process_state: .word 0 # 0 = aucun processus
					   # 1 = processus
process_pc: .word 0
process_at: .word 0
process_v0: .word 0
process_v1: .word 0
process_a0: .word 0
process_a1: .word 0
process_a2: .word 0
process_a3: .word 0
process_t0: .word 0
process_t1: .word 0
process_t2: .word 0
process_t3: .word 0
process_t4: .word 0
process_t5: .word 0
process_t6: .word 0
process_t7: .word 0
process_t8: .word 0
process_t9: .word 0
process_s0: .word 0
process_s1: .word 0
process_s2: .word 0
process_s3: .word 0
process_s4: .word 0
process_s5: .word 0
process_s6: .word 0
process_s7: .word 0
process_s8: .word 0
process_gp: .word 0
process_sp: .word 0
process_ra: .word 0

#On réserve de la place pour le processus suivant
.space 124 # Processus 1
.space 124 # Processus 2
.space 124 # Processus 3
.space 124 # Processus 4
.space 124 # Processus 5

current_process: .word 0  # contient le nb du processus courant 
						  # (celui qui a été interrompu)
number_of_process: .word 6







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
	
	# afficher le message service non supporté
	la $a0, msg_brk_invalide
	li $v0,4
	syscall
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
	move $a0, $t0
	li $v0, 1
	syscall
        # Passer à la ligne pour plus de "lisibilité"
	la $a0, alaligne
	li $v0, 4
	syscall

	#Cas ou $t0 = 115 (touche 's')
	beq $t0,115, swap_process

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


swap_process:
#-----SAUVEGARDE DES REGISTRES ET PC

#calcul de l'offset
lw $t0, current_process($0)
li $t1, 124
mul $t0, $t0, $t1

# sauvegarde de tous les registres
mfc0 $t1, $14
sw $t1, process_pc($t0)
sw $k1, process_at($t0)

lw $t1, save_v0($0)
sw $t1, process_v0($t0)

sw $v1, process_v1($t0)

lw $t1, save_a0($0)
sw $t1, process_a0($t0)

sw $a1, process_a1($t0)
sw $a2, process_a2($t0)
sw $a3, process_a3($t0)

lw $t1, save_t0($0)
sw $t1, process_t0($t0)

lw $t1, save_t1($0)
sw $t1, process_t1($t0)

sw $t2, process_t2($t0)
sw $t3, process_t3($t0)
sw $t4, process_t4($t0)
sw $t5, process_t5($t0)
sw $t6, process_t6($t0)
sw $t7, process_t7($t0)
sw $t8, process_t8($t0)
sw $t9, process_t9($t0)

sw $s0, process_s0($t0)
sw $s1, process_s1($t0)
sw $s2, process_s2($t0)
sw $s3, process_s3($t0)
sw $s4, process_s4($t0)
sw $s5, process_s5($t0)
sw $s6, process_s6($t0)
sw $s7, process_s7($t0)
sw $s8, process_s8($t0)

sw $gp, process_gp($t0)
sw $ra, process_ra($t0)

#-----FIN DE LA SAUVEGARDE DES REGISTRES ET PC

#outil qui séléctionne le process suivant (a condition que state=1)
select_process:
	lw $t0, current_process($0)
	lw $t1, number_of_process($0)

	boucle_select_process:
		# suivant = (actuel + 1) % nb_process
		addi $t0, $t0, 1
		div $t0, $t1
		mfhi $t0; 

		# calcul de l'offset
		mul $t2, $t0, 124

		# si state = 0 alors on passe au process suivant
		li $t3, 0
		lw $t4, process_state($t2)
		beq $t3, $t4, boucle_select_process
	
	# on restore le contexte
	move $t1, $t2
	sw $t0, current_process($0)

	lw $k0, process_pc($t1)
	lw $k1, process_at($t1)

	lw $v0, process_v0($t1)
	lw $v1, process_v1($t1)

	lw $a0, process_a0($t1)
	lw $a1, process_a1($t1)
	lw $a2, process_a2($t1)
	lw $a3, process_a3($t1)

	# on stocke $t0 et $t1 dans save_t0 et save_t1
	lw $t0, process_t0($t1)
	sw $t0, save_t0($0)
	lw $t0, process_t1($t1)
	sw $t0, save_t1($0)

	lw $t2, process_t2($t1)
	lw $t3, process_t3($t1)
	lw $t4, process_t4($t1)
	lw $t5, process_t5($t1)
	lw $t6, process_t6($t1)
	lw $t7, process_t7($t1)
	lw $t8, process_t8($t1)
	lw $t9, process_t9($t1)

	lw $s0, process_s0($t1)
	lw $s1, process_s1($t1)
	lw $s2, process_s2($t1)
	lw $s3, process_s3($t1)
	lw $s4, process_s4($t1)
	lw $s5, process_s5($t1)
	lw $s6, process_s6($t1)
	lw $s7, process_s7($t1)
	lw $s8, process_s8($t1)

	lw $gp, process_gp($t1)
	lw $ra, process_ra($t1)

	# on restaure complètement avec $at, $t0, $t1
	lw $t0, save_t0($0)
	lw $t1, save_t1($0)

	.set noat
	move $at $k1		# Restore $at
	.set at
	
	rfe

	jr $k0

# load the the interruption adress
# find out the program interrupted
# Store datas of the prog somewhere 
# j int_ret

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






#-----------------------------------------------------------------
# Point d'entrée 
#----------------------------------------------------------------

	.globl __start
__start:

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

	#----------------------------------------Initialisation des processus

	#on récupère le nombre de processus
	lw $s0, number_of_process($0)
	#numero du process
	li $t1, 0
	#Pour chaque processus (numeroté de 0 a n), on met state = $0
	boucle_init_TCP:
		mul $t2, $t1, 124 # calcul de l'offset nécéssaire pour accéder a tous
						# les processus
		sw $0, process_state($t2)
		addi $t1,$t1,1 # incrémentation n° du processus
		bne $s0, $t1,boucle_init_TCP # si numero de process = nb process
	

	li $t1,1 # val pour state = 1
	li $t2,0 # offset
	#On prépare la TCP avec les deux processus que l'on appelle

	#Processus 0 : 
	la $t0, main0($0)
	sw $t0, process_pc($t2)
	sw $t1, process_state($t2)

	#Processus 1 :
	la $t0, main1($0)
	addi $t2,$t2, 124
	sw $t0, process_pc($t2)
	sw $t1, process_state($t2)

	#Processus 2 :
	la $t0, main2($0)
	addi $t2,$t2, 124
	sw $t0, process_pc($t2)
	sw $t1, process_state($t2)

	#Processus 3 :
	la $t0, main3($0)
	addi $t2,$t2, 124
	sw $t0, process_pc($t2)
	sw $t1, process_state($t2)

	#Processus 4 :
	la $t0, main4($0)
	addi $t2,$t2, 124
	sw $t0, process_pc($t2)
	sw $t1, process_state($t2)

	#Processus 5 :
	la $t0, main5($0)
	addi $t2,$t2, 124
	sw $t0, process_pc($t2)
	sw $t1, process_state($t2)

	#FIN ------------------------------------- Initialisation des processus


	# mettre l'adresse du point d'entrée du programme de test dans $k0
	# ici on met le programme 0
	sw $t0, current_process($0)
	lw $k0, process_pc($0)


	# Commutation de contextes (changer status et PC de façon atomique
        # avec les 2 instructions suivantes)
	rfe # Au prochain jr, status aura la valeur 0x103, et on sera donc
            # en mode utilisateur/interruptions démasquées (masque général
            # et masque IT receiver)
	jr $k0

# ---------------------------------------------------------------

