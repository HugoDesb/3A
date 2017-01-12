#------------------------------------------------------------------
# Fichier exo1-2a.s
# Objet : TP Logiciel de base Fiche 4
#	  exercice 1-(ii)-a)
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
	lw $t1, 0xFFFF0008($0)
        beq $t1, $0, boucle_transmitter
        sw $t0, 0xFFFF000C($0)

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
# programme de test  : Ce programme boucle indéfiniment
#------------------------------------------------------------

	.text # Le programme de test fonctionne en mode utilisateur

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
	.data  # Section des données utilisateur
chaine_lu: .space 100 # Place pour ranger la chaine saisie
                      # avant de l'afficher

#-------------------------------------------------------------

