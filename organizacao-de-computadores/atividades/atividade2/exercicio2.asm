.data
	vector_A:	.word 2, 59, 39, 48, 25, 67, 19, 76, 52, 65, 18, 99
	vector_length: .word	12

.text

main:
	add t0, zero, zero      # T0, Contador
	addi t1, zero, 1        # T1, Utilizado o valor

	add a0, zero, zero      # A0, Soma dos pares
	add a1, zero, zero      # A1, Soma dos inpares
	la a2, vector_A		    	# A2, Vetor_A
	lw a3, vector_length    # A3, Tamanho do vetor

condicao_laco:
	blt t0, a3, corpo_laco  # T0 < A3
	j fim                   # Fim

corpo_laco:
	lw t4, (a2)             # Vetor_A[A2]
	andi t5, t4, 1          # Vetor_A[A2] && 1
	beq t5, t1, impar       # if Vetor_A[A2] == 1 é impar
par:
	add a0, a0, t4					# # A0 += Vetor_A[A2] impar
	j fim_if								# Fim do if
impar:
	add a1, a1, t4					# A1 += Vetor_A[A2] impar
fim_if:
	addi a2, a2, 4		    	# &vector_A = &vector_A + 4
	addi t0, t0, 1          # T0 = T0 + 1
	j condicao_laco         # Retorna para o loop

fim:
	nop
