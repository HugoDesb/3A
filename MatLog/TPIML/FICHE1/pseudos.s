#-----------------------------------------------------------------
#-- File name : pseudos.s
#-- Objet : TP Interface Matériel Logiciel - Fiche 1
#--
#-- Exercice 1 - Fiche de td 2 (traduction de pseudo-instructions)
#    Les pseudo instructions mises en commentaires (g et aa) ne 
#    sont pas acceptées par le simulateur (version 6.5 )
#----------------------------------------------------------------

	.text
label1:
	move $7, $20	#a
	li  $5, 0xFFFF	#b
	li  $5, 0x0FFFF	#c
	li  $t0, 0x0182AD #d
	li  $a0, 40000	#e
	li  $s3, -40000 #f
	#addiu $5, $s3, 0x0182AD #g Le simulateur 6.5 ne l'accepte pas
	div $5, $3, $7 #h
	mul $t0, $t1, $t2 #i
        mul $5, $7, 32800 #j
	abs  $a1, $a0 #k
	sge $16, $17, 0x53664 #l
	lw $7, 0x12FFF0($5)#m
	lw  $6, 0xFFFF($5) #n	
	lw  $6, 0x0FFFF($5) #o
	bgt $7, $6, label2  #p) Le simulateur n'accepte pas les déplacements
	                   # en langage d'assemblage (le programmeur ne sait pas
			   # comment les pseudo-instructions seront traduites)
	bge $7, $6, label1 #q) même remarque qu'en p)
	beq $7, $6, label #r) même remarque qu'en p	
    ld $16, 1000	 #s
	ld $16, 1000($s1) #t
    rem $t0, $t1, $t2 #u
	rol $s5, $s0, 11 #v
	la $5, 50($7) #w
    la $a1, label #x
	la   $5, label($7) #y
    lw  $a2, label+20($a1)#z
    # sw  $6, label-20($5) #aa #Mode d'adressage non accepté par xspim 6.5
    li   $5, 0xABCDEF1234 #ab
 	li   $5, 5000000000 #ac
 	
label2:
label:
#------------------------------------------------------------
