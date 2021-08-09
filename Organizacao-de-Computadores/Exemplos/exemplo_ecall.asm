	.data
msg_comum:		.asciz "Entre com o valor de "
msg_A:			.asciz "A: "
msg_B:			.asciz "B: "
msg_C:			.asciz "C: "	
msg_resultado:		.asciz  "\n    S = (A + B + C) = "


	.text
main: 
### Valor A
	la 	a0, msg_comum  # imprime mensagem
	li 	a7,4
	ecall

	la 	a0, msg_A  # imprime mensagem
	li 	a7,4
	ecall	
 
	addi 	a7, zero, 5  #lê inteiro
	ecall	
	add 	s0, zero, a0  # carrega valor lido em s0
### Valor B
	la 	a0, msg_comum  # imprime mensagem
	li 	a7, 4
	ecall

	la 	a0, msg_B  # imprime mensagem
	li 	a7, 4
	ecall	
 
	addi 	a7, zero, 5  #lê inteiro
	ecall	
	add 	s1, zero, a0  # carrega valor lido em s1
### Valor C
	la 	a0, msg_comum  # imprime mensagem
	li 	a7, 4
	ecall

	la 	a0, msg_C  # imprime mensagem
	li 	a7, 4
	ecall	
 
	addi 	a7, zero, 5  #lê inteiro
	ecall	
	add 	s2, zero, a0  # carrega valor lido em s2

# Calcula
	add t0, s0, s1
	add t0, t0, s2

	
imprime_resultado:
	la 	a0, msg_resultado  # imprime mensagem
	li 	a7, 4
	ecall	

	mv 	a0, t0  # imprime inteiro
	li 	a7, 1
	ecall	

	
fim: 
	nop
	li a7, 93
	ecall 
