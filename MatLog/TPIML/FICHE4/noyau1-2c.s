#------------------------------------------------------------------
# Fichier noyau1-2c.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
# Ce fichier est une modification du programme de traitement
# d'exceptions par défaut de spim.
# Ce noyau (traitant des exceptions) rend les services :
# - saisie d'un  caractère au clavier (break 5): Le caractère lu est dans $v0
# - affichage d'une chaine de  caractères (break 16) : L'adresse de la chaine 
#    à afficher doit être dans $a0
# Pour les autres exceptions, on  ne fait qu'afficher
# un message d'erreur et relancer le programme utilisateur.
#--------------------------------------------------------------------
# 1) L'entête original : vous pouvez passer
#---------------------------------------------


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

# This is the exception handler code that the processor runs when
# an exception occurs. It only prints some information about the
# exception, but scan server as a model of how to write a handler.
#
# Because we are running in the kernel, we can use $k0/$k1 without
# saving their old values.

# 3) Le code du noyau.
#-------------------------

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
	    lw $t0, 0($t0) # Code de l'instruction break
	    srl $t0, $t0, 11
        #Ecrire le numéro du break
        move $a0,$t0
        li  $v0, 1
        syscall
      	la  $a0, alaligne
        li  $v0,  4
        syscall
	
	beq $t0, 5, getcharp
	beq $t0, 16, printp
	# Code de service non supporté
	la $a0, msg_brk_invalide
	li $v0,4
	syscall
	j ret

#-------------------------------------------------------------
# Service getcharp : saisie d'un caractère au clavier
#                      par polling
# $v0 contiendra le contiendra le caractère lu
#-------------------------------------------------------------
getcharp:
	# attendre un caractère
boucle_receiver:
	lw $t0, 0xFFFF0000($0)
    beq $t0, $0, boucle_receiver
	lw $v0, 0xFFFF0004($0)
	sw $v0, save_v0($0) # Le caractère lu remplace le $v0
                        # qui a été sauvegardé à l'entrée du noyau
	j ret
#-------------------------------------------------------------

#-------------------------------------------------------------
# Service printp
# $a0 contient l'adresse de la chaîne à afficher
#-------------------------------------------------------------
printp:
	lw $a0, save_a0($0) # On recupère la valeur de $a0
                            # sauvegardé à l'entree du noyau
   # Afficher la chaîne caractère par caractere
boucle_chaine:
	lb $t0, 0($a0)
	beq $t0, $0, fin_printp
	# afficher le caractère dans $t0
	# Pour cela on attend que le transmitter soit prêt avant
        # d'écrire le caractère dans le registre de données
boucle_transmitter:
	lw $t1, 0xFFFF0008($0)
    beq $t1, $0, boucle_transmitter
    sw $t0, 0xFFFF000C($0)
    #passer au caractere suivant
	addiu $a0,$a0, 1
    b boucle_chaine
fin_printp:
	j ret
#------------------------------------------------------------
autres_exceptions:
    blez $a0 int_ret	# Don't print interrupts

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

#-----------------------------------------------------------------
# Point d'entrée 
#----------------------------------------------------------------

	.globl __start
__start:

# Configurer le transmitter et le receiver en mode polling (mettre 0 dans
# le bit interrupt enable des registres de controle du transmitter 
# -adresse Oxffff0008-, et du receiver -adresse 0xffff0000)
	sw $0, 0xffff0008($0) # transmitter en mode polling
	sw $0, 0xffff0000($0) # receiver en mode polling
# Lancer le programme de test à l'étiquette main 
# Le programme de test fonctionne en mode utilisateur
	# On modifie le registre status en lui affectant la valeur
        # 0x0000000C. On reste donc en mode maître interruptions
        # masquées (les 2 bits de poids faibles sont à 0)
	li $k0, 0xC
	mtc0 $k0, $12
	# mettre l'adresse du point d'entrée du programme de test dans $k0
	la $k0, main
	# Commutation de contextes (changer status et PC de façon atomique
        # avec les 2 instructions suivantes)
	rfe # Au prochain jr, status aura la valeur 0x3, et on sera donc
        # en mode utilisateur/interruptions démasquées (masque général)
	jr $k0

#----------------------------------------------------------------------------

