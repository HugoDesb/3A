#------------------------------------------------------------------
# Fichier exo2-2.s
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
la $a0, message
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
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

# Le programme de test fonctionne en mode utilisateur
.globl main1
main1:

      #$t0 contiendra le compteur
move $t0, $0

boucle_main1:
la $a0, multiprogrammation
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
j boucle_main1 # le programme boucle indéfinimemnt




#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

# Le programme de test fonctionne en mode utilisateur
.globl main2
main2:

      #$t0 contiendra le compteur
move $t0, $0

boucle_main2:
la $a0, test2
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
j boucle_main2 # le programme boucle indéfinimemnt



#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

# Le programme de test fonctionne en mode utilisateur
.globl main3
main3:

      #$t0 contiendra le compteur
li $t0, 10

boucle_main3:
la $a0,test3
li $v0, 4
syscall
move $a0,$t0
li $v0, 1
syscall
la $a0, alaligne
li $v0, 4
syscall
addi $t0,$t0, -1
jal tempo
bnez $t0, boucle_main3

break 12 #Mise en veille

j main3




#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

# Le programme de test fonctionne en mode utilisateur
.globl main4
main4:

      #$t0 contiendra le compteur
li $t0, 10

boucle_main4:
la $a0,test4
li $v0, 4
syscall
move $a0,$t0
li $v0, 1
syscall
la $a0, alaligne
li $v0, 4
syscall
addi $t0,$t0, -1
jal tempo
bnez $t0, boucle_main4 # le programme boucle indéfinimemnt

break 10 #arret du programme

j main4




#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

# Le programme de test fonctionne en mode utilisateur
.globl main5
main5:

      #$t0 contiendra le compteur
move $t0, $0

boucle_main5:
la $a0,test5
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

li $a0, 3
break 14 #reveil du proccessus de valeur a0

j boucle_main5 # le programme boucle indéfinimemnt



#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

# Le programme de test fonctionne en mode utilisateur
.globl main6
main6:

      #$t0 contiendra le compteur
move $t0, $0

boucle_main6:
la $a0,test6
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


li $a0, 7
li $v0, 42
break 16 #mise en attente du proccessus d'envoie

j boucle_main6 # le programme boucle indéfinimemnt


#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

# Le programme de test fonctionne en mode utilisateur
.globl main7
main7:

      #$t0 contiendra le compteur
move $t0, $0

boucle_main7:
la $a0,test7
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


li $a0, 6
break 18 #mise en attente du processus de reception


j boucle_main7 # le programme boucle indéfinimemnt





#-----------------------------------------------------------------
.data  # Section des données utilisateur
message: .asciiz "Ca marche! "
multiprogrammation: .asciiz "J'ai meme compris la multiprogrammation :"
test2: .asciiz "2 Ceci est le processus n2 : "
test3: .asciiz "3 Ceci est le processus n3 (qui va se mettre en veille) : "
test4: .asciiz "4 Ceci est le processus n4 ( qui va s'arreter) : "
test5: .asciiz "5 Ceci est le processus n5 (qui reveil n 3) : "
test6: .asciiz "6 Processus 6 qui envoie le message : "
test7: .asciiz "7 Processus 7 qui recoit le message : "
alaligne: .asciiz "\n"

#-------------------------------------------------------------
