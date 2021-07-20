.data

.text

main:
	addi t0, zero, 11		# T0, Contador
	addi t1, zero, 100	# T1, Quantidade do laço
	add a0, zero, zero	# A0, Soma

while:
	blt t0, t1, corpo  	# T0 < T1
	j fim              	# Fim
	
corpo:
	add a0, a0, t0			# A0 = A0 + T0
	addi t0, t0, 2			# T0 = T0 + 2
	j while							# Volta para while

fim:
	nop