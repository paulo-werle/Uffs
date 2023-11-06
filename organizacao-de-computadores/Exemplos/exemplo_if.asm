	.data

	.text
main:
	addi t0, zero, 10 # atribui 10 para t0
	addi t1, zero, 1
	add  s1, zero, zero
if:
	blt s0, t0, true
   	addi s1, zero, -1
	j	 fim
true:
   	add s1, s1, t1
   
fim:
	nop
