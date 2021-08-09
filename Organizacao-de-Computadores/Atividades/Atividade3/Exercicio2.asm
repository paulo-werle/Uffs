.data
  # Inicia dados
  vetor: .space  40
  vetor_len: .word 10

  helper_virgula: .asciz ", "
  helper_barra_n: .asciz "\n"

  msg_preencher: .asciz "Digite um valor para colocar no vetor: "

.text
  main:

    la s1, vetor                          # Vetor -> s1 = vetor[]
    lw s2, vetor_len                      # num_elementos -> s2 = vetor_len
    
    add a2, zero, s1                      # Monta parametro da função
    add a3, zero, s2                      # Monta parametro da função
    jal preencheVetor                     # Chama a função

    add a2, zero, s1                      # Monta parametro da função
    add a3, zero, s2                      # Monta parametro da função
    jal imprimeVetor                      # Chama a função

    add a2, zero, s1                      # Monta parametro da função
    add a3, zero, s2                      # Monta parametro da função
    jal ordenaVetor                       # Chama a função

    add a2, zero, s1                      # Monta parametro da função
    add a3, zero, s2                      # Monta parametro da função
    jal imprimeVetor                      # Chama a função

    j end


  ########## preencheVetor ##########
  preencheVetor:
    add t0, zero, zero                    # I -> t0 = 0
  preencheVetorWhile:
    blt t0, a3, preencheVetorCorpoWhile   # I < num_elementos
    j preencheVetorFimWhile               # Vai para o fim do while
  preencheVetorCorpoWhile:
    la a0, msg_preencher                  # Define mensagem
    li a7, 4                              # Define paramentro do ecall
    ecall                                 # Chama SO
    add a0, zero, a2                      # *a0 = &a2
    li a7, 5                              # Define paramentro do ecall
    ecall                                 # Chama SO
    sw a0, (a2)
    addi a2, a2, 4                        # a2 = a2 + 4
    addi t0, t0, 1                        # t0++
    j preencheVetorWhile                  # Volta para o while
  preencheVetorFimWhile:
    ret
  ########## preencheVetor ##########



  ########## imprimeVetor ##########
  imprimeVetor:
    add t0, zero, zero                    # I -> t0 = 0
  imprimeVetorWhile:
    blt t0, a3, imprimeVetorCorpoWhile    # I < num_elementos
    j imprimeVetorFimWhile                # Vai para o fim do while
  imprimeVetorCorpoWhile:
    lw a0, (a2)                           # Define mensagem
    li a7, 1                              # Define paramentro do ecall
    ecall                                 # Chama SO
    la a0, helper_virgula                 # Define mensagem
    li a7, 4                              # Define paramentro do ecall
    ecall                                 # Chama SO
    addi a2, a2, 4                        # a2 = a2 + 4
    addi t0, t0, 1                        # t0++
    j imprimeVetorWhile                   # Volta para o while
  imprimeVetorFimWhile:
    la a0, helper_barra_n                 # Define mensagem
    li a7, 4                              # Define paramentro do ecall
    ecall                                 # Chama SO
    ret
  ########## imprimeVetor ##########



  ########## ordenaVetor ##########
  ordenaVetor:
    add t2, zero, a2                      # t2 = vetor[inicio]
    add t0, zero, zero                    # I -> t0 = 0
  ordenaVetorWhile1:
    blt t0, a3, ordenaVetorCorpoWhile1    # I < num_elementos
    j ordenaVetorFimWhile1                # Vai para o fim do while
  ordenaVetorCorpoWhile1:
    add t1, zero, zero                    # J -> t1 = 0
    add t3, zero, a2                      # t3 = vetor[inicio]
  ordenaVetorWhile2:
    blt t1, a3, ordenaVetorCorpoWhile2    # J < num_elementos
    j ordenaVetorFimWhile2                # Vai para o fim do while2
  ordenaVetorCorpoWhile2:
    lw t4, (t2)                           # t4 = &vetor[i]
    lw t5, (t3)                           # t4 = &vetor[j]
    blt t5, t4, ordenaVetorCorpoIf        # if (&vetor[j] < &vetor[i])
    j ordenaVetorFimIf                    # Vai para o fim do if
  ordenaVetorCorpoIf:
    lw s3, (t2)                           # aux = vetor[i]
    lw s4, (t3)                           # aux = vetor[i]
    sw s3, (t3)                           # vetor[i] = vetor[j]
    sw s4, (t2)                           # vetor[j] = aux
  ordenaVetorFimIf:
    addi t3, t3, 4                        # vector[] + 4
    addi t1, t1, 1                        # J++
    j ordenaVetorWhile2                   # Volta para laço interno
  ordenaVetorFimWhile2:
    addi t2, t2, 4                        # vector[] + 4
    addi t0, t0, 1                        # I++
    j ordenaVetorWhile1                   # Volta para laço interno
  ordenaVetorFimWhile1:
  ret
  ########## ordenaVetor ##########

  end:
    nop