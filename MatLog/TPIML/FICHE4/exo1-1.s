#------------------------------------------------------------------
# Fichier exo1-1.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
# Exercice 1-(i)
#-----------------------------------------------------------------
        
	.ktext  # Le programme sera rangé dans la partie code du 
                # noyau
	.globl __start
__start:

# Configurer le transmitter et le receiver en mode polling (mettre 0 dans
# le bit interrupt enable des registres de controle du transmitter 
# -adresse Oxffff0008-, et du receiver -adresse 0xffff0000)
	sw $0, 0xffff0008($0) # transmitter en mode polling
	sw $0, 0xffff0000($0) # receiver en mode polling
# Lancer le programme de test à l'étiquette main
	jal main
# Terminer l'exécution du programme : service système exit
	li $v0 10
	syscall			# syscall 10 (exit)

#-------------------------------------------------------------
# Procédure printp
# $a0 contient l'adresse de la chaîne à afficher
#-------------------------------------------------------------

printp:
   # Afficher la chaîne caractère par caractere
boucle_chaine:
	lb $t0, 0($a0)
	beq $t0, $0, fin_printp
	# afficher le caractère dans $t0
	# Pour cela on attend que le transmitter soit prêt avant
        # d'écrire le caractère dans le registre de données
boucle_transmitter:
#	lw $t1, 0xFFFF0008($0)
#    beq $t1, $0, boucle_transmitter
    sw $t0, 0xFFFF000C($0)
    # passer au caractère suivant
	addiu $a0,$a0, 1
    b boucle_chaine
fin_printp:
 	jr $ra

#-------------------------------------------------------------
# Procédure getcharp : saisie d'un caractère au clavier
#                      par polling
# $v0 contiendra le contiendra le caractère lu
#-------------------------------------------------------------
getcharp:
	# attendre un caractère
boucle_receiver:
	lw $t0, 0xFFFF0000($0)
    beq $t0, $0, boucle_receiver
	lw $v0, 0xFFFF0004($0)
	jr $ra
#-------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

main:
	
        #$s0 contiendra l'indice du caractère lu
	move $s0, $0	
saisie:
	jal getcharp
	beq $v0, 13, fin_saisie
	sb $v0, chaine_lu($s0)
	addiu $s0,$s0, 1
	b saisie
fin_saisie: 
	li $v0, '\n'
	sb $v0, chaine_lu($s0) 
	addiu $s0,$s0, 1
	sb $0, chaine_lu($s0)

	la $a0, chaine_lu
	jal printp
	j main # le programme boucle indéfinimemnt

#-----------------------------------------------------------------
	.kdata  # Section des données rangés dans la partie noyau
chaine_lu: .space 100 # Place pour ranger la chaine saisie
                      # avant de l'afficher

#-------------------------------------------------------------

