#------------------------------------------------------------------
# Fichier exo1-2c.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
#         Exercice 1-(ii)-c)
# Le programme de ce fichier ne fonctionne que lorsque un noyau
# (traitant des exceptions) rendant les services "saisie d'un 
# caractère au clavier" (break 5) et "affichage d'une chaine de
# caractères (break 16) est chargée conjointement.
#-----------------------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------

	.text # Le programme de test fonctionne en mode utilisateur
	.globl main
main:
	
        #$t0 contiendra l'indice du caractère lu
	move $t0, $0	
saisie:
    #Appel système pour demander la lecture d'un caractère au clavier
    break 5 # caractère lu dans $v0

	beq $v0, 13, fin_saisie
	sb $v0, chaine_lu($t0)
	addiu $t0,$t0, 1
	b saisie
fin_saisie: 
	li $v0, '\n'
	sb $v0, chaine_lu($t0) 
	addiu $t0,$t0, 1
	sb $0, chaine_lu($t0)

	la $a0, chaine_lu
	# Appel système pour demander l'affichage de la chaine de 
        # caractère dont l'adresse est dans $v0
    break 16 

	j main # le programme boucle indéfinimemnt

#-----------------------------------------------------------------
	.data  # Section des données utilisateur
chaine_lu: .space 100 # Place pour ranger la chaine saisie
                      # avant de l'afficher

#-------------------------------------------------------------

