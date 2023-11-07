.data
  # Inicia dados
  string:	.asciz  "i", "s", "t", "o", " ", "e", "h", " ", "u", "m", "a", " ", "s", "t", "r", "i", "n", "g"
  string_len: .word 18
  string_copy:	.space  36

  # Inicia vogais 
  vogalA: .asciz "a"
  vogalE: .asciz "e"
  vogalI: .asciz "i"
  vogalO: .asciz "o"
  vogalU: .asciz "u"

  msg_quantidade: .asciz "Quantidade de vogais: "
  msg_original: .asciz "A string original:\n \t"
  msg_copia: .asciz "A string sem vogais:\n \t"
  barra_n: .asciz "\n"

.text
  main: 
    la s1, string                       # String -> s1 = string[]

    # Imprime mensagem de quantidade
    la 	a0, msg_quantidade              # Define mensagem
    li a7, 4                            # Define paramentro do ecall
    ecall                               # Chama SO
    # Chama função de quantidade
    add a2, zero, s1                    # Parametro das funçoẽs, a2 = string[]
    jal contaVogais                     # Chama a função
    li a7, 1                            # Define paramentro do ecall
    ecall                               # Chama SO
    # Imprime \n
    la 	a0, barra_n                     # Define mensagem
    li a7, 4                            # Define paramentro do ecall
    ecall                               # Chama SO



    ##### Imprime string original #####
    la 	a0, msg_original                # Define mensagem
    ecall                               # Chama SO
    # Percorre laço para imprimir string original
    add s2, zero, s1                    # Faz copia da string
    add t0, zero, zero                  # I -> t0 = 0
    lw t1, string_len                   # StringLenght -> t1 = string_len
  imprimeString:
    blt t0, t1, imprimeStringCorpoWhile # I < StringLenght
    j imprimeStringFim
  imprimeStringCorpoWhile:
    add a0, zero, s2                    # a0 = string[] 
    ecall                               # Chama SO
    addi s2, s2, 2                      # string[] + 2
    addi t0, t0, 1                      # t0++
    j imprimeString                     # Vai para condição
  imprimeStringFim:
    ##### Imprime string original #####

    # Imprime \n
    la 	a0, barra_n                     # Define mensagem
    li a7, 4                            # Define paramentro do ecall
    ecall                               # Chama SO


    ##### Imprime string sem vogais #####
    la a0, msg_copia                    # Define mensagem
    li a7, 4                            # Define paramentro do ecall
    ecall                               # Chama SO
    # Chama funçâo para retirar
    add a2, zero, s1                    # Parametro das funçoẽs, a2 = string[]
    jal eliminaVogais                   # Chama a função
    # Percorre laço para imprimir copia
    add s2, zero, a0                    # Faz copia da stringCopy
    add t0, zero, zero                  # I -> t0 = 0
    lw t1, string_len                   # StringLenght -> t1 = string_len
  imprimeCopy:
    blt t0, t1, imprimeCopyCorpoWhile   # I < StringLenght
    j imprimeCopyFim
  imprimeCopyCorpoWhile:
    add a0, zero, s2                    # a0 = string[] 
    ecall                               # Chama SO
    addi s2, s2, 2                      # string[] + 2
    addi t0, t0, 1                      # t0++
    j imprimeCopy                       # Vai para condição
  imprimeCopyFim:
    ##### Imprime string sem vogais #####

    j end



  ########## contaVogais ##########
  contaVogais:
    add t0, zero, zero                  # I -> t0 = 0
    add t1, zero, zero                  # Count -> t1 = 0
    lw t2, string_len                   # StringLenght -> t2 = string_len

  contaVogaisCondicaoWhile:
    blt t0, t2, contaVogaisCorpoWhile   # I < StringLenght
    j contaVogaisFimWhile               # Fim

  contaVogaisCorpoWhile:
    lb t3, (a2)                         # t3 = &string[]

    lb t4, vogalA                       # t3 = a
    beq t3, t4, contaVogaisTrueIf       # if string[] == a
    lb t4, vogalE                       # t3 = e
    beq t3, t4, contaVogaisTrueIf       # if string[] == e
    lb t4, vogalI                       # t3 = i
    beq t3, t4, contaVogaisTrueIf       # if string[] == i
    lb t4, vogalO                       # t3 = o
    beq t3, t4, contaVogaisTrueIf       # if string[] == o
    lb t4, vogalU                       # t3 = u
    beq t3, t4, contaVogaisTrueIf       # if string[] == u
    j contaVogaisFimIf                  # Pula para o fim do if

  contaVogaisTrueIf:
    addi t1, t1, 1                      # count++

  contaVogaisFimIf:	
    addi t0, t0, 1                      # I++
    addi a2, a2, 2                      # string[] + 2
    j contaVogaisCondicaoWhile          # Volta para a condição

  contaVogaisFimWhile:
    add a0, zero, t1                    # Parametro de retorno   
    ret                                 # Retorna
  ########## contaVogais ##########



  ########## eliminaVogais ##########
  eliminaVogais:
    add t0, zero, zero                  # I -> t0 = 0
    lw t1, string_len                   # StringLenght -> t1 = string_len
    la t2, string_copy                  # stringCopy -> t2 = string_copy

  eliminaVogaisCondicaoWhile:
    blt t0, t1, eliminaVogaisCorpoWhile # I < StringLenght
    j eliminaVogaisFimWhile             # Fim

  eliminaVogaisCorpoWhile:
    lb t3, (a2)                         # t3 = &string[]

    lb t4, vogalA                       # t4 = a
    beq t3, t4, eliminaVogaisFimIf      # if string[] == a
    lb t4, vogalE                       # t4 = e
    beq t3, t4, eliminaVogaisFimIf      # if string[] == e
    lb t4, vogalI                       # t4 = i
    beq t3, t4, eliminaVogaisFimIf      # if string[] == i
    lb t4, vogalO                       # t4 = o
    beq t3, t4, eliminaVogaisFimIf      # if string[] == o
    lb t4, vogalU                       # t4 = u
    beq t3, t4, eliminaVogaisFimIf      # if string[] == u

    sb t3, (t2)                         # stringCopy[] = string[]
    addi t2, t2, 2                      # stringCopy[] + 2

  eliminaVogaisFimIf:	
    addi t0, t0, 1                      # I++
    addi a2, a2, 2                      # string[] + 2
    j eliminaVogaisCondicaoWhile        # Volta para a condição

  eliminaVogaisFimWhile:
    la a0, string_copy                  # Parametro de retorno
    ret                                 # Retorna
  ########## contaVogais ##########



  end:
    nop