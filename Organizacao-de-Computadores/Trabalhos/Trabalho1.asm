.data
  # Inicia dados
  board: .space  400
  board_size: .word 10
  navios: .asciz "4\n1 5 1 1\n0 5 2 2\n0 4 2 2\n1 3 0 3"

  # Impressões
  espaco: .asciz " "
  barra_n: .asciz "\n"

  # Anotações
  # lw s1, board_size                     # BoardSize -> s1 = board_size

  # a0 - a1   Argumentos/Retorno de função origem
  # a2 - a7   Argumentos de função origem
  # s0 - s11  Registrador Salvo destino
  # t0 - t6   Temporário origem
  # zero      Contém sempre o valor 0 (zero)
  # ra        Endereço de retorno origem
  # sp        Ponteiro de pilha destino
  # gp        Ponteiro global -
  # tp        Ponteiro de thread -

.text
  main:
    la s0, board                                  # Board -> s0 = board[][]

    add a2, zero, s0                              # Parametro da função (board[][])
    jal novoTabuleiro                             # Chama a função novoTabuleiro

    add a2, zero, s0                              # Parametro da função (board[][])
    jal insereEmbarcacoes                         # Chama a função insereEmbarcacoes

    j end                                         # Finaliza o programa

  ########## novoTabuleiro ##########
    novoTabuleiro:
      lw t0, board_size                           # BoardSize -> t0 = board_size
      add t1, zero, zero                          # boardRow -> t1 = 0
    novoTabuleiroWhile1:
      blt t1, t0, novoTabuleiroCorpoWhile1        # boardRow < BoardSize
      j novoTabuleiroFimWhile1
    novoTabuleiroCorpoWhile1:
      add t2, zero, zero                          # boardCol -> t2 = 0
    novoTabuleiroWhile2:
      blt t2, t0, novoTabuleiroCorpoWhile2        # boardCol < BoardSize
      j novoTabuleiroFimWhile2
    novoTabuleiroCorpoWhile2:
      add t3, zero, a2                            # board[0][0]
      addi t4, zero, 4                            # t4 = 4
      mul t5, t1, t0                              # t5 = boardRow * BoardSize
      add t5, t5, t2                              # t5 = t5 + boardCol
      mul t5, t5, t4                              # t5 = t5 * 4
      add t3, t3, t5                              # Origem + Deslocamento
      sw zero, (t3)                               # &t3 = 0
      addi t2, t2, 1                              # boardCol++
      j novoTabuleiroWhile2                       # Volta para laço interno
    novoTabuleiroFimWhile2:
      addi t1, t1, 1                              # boardRow++
      j novoTabuleiroWhile1                       # Volta para laço externo
    novoTabuleiroFimWhile1:
      ret
  ########## novoTabuleiro ##########

  ########## insereEmbarcacoes ##########
    insereEmbarcacoes:
      add t6, zero, ra                            # Salva endereço de retorno atual
      addi t0, zero, 1                            # current -> t0 = 1

      add, s11, zero, zero                        # error -> s11 = 0
      la s2, navios                               # navios -> s2  = navios[0]
      addi s3, s2, 1                              # s3  = navios[1]
      jal converterInteiro                        # Converte para inteiro
      add t1, zero, a0                            # quantity -> t1 = a0

    insereEmbarcacoesWhile:
      bge t1, t0, insereEmbarcacoesCorpoWhile     # quantity >= current
      j insereEmbarcacoesFimWhile
    insereEmbarcacoesCorpoWhile:
      bne s11, zero, insereEmbarcacoesError       # if (error != 0)

      la s2, navios                               # navios -> s2  = navios[0]
      addi t2, zero, 1                            # t2 = 1
      sub s10, t0, t2                             # s10 = current - 1
      addi t2, zero, 8                            # t2 = 8
      mul s10, s10, t2                            # s10 = (current - 1) * 8
      addi t2, zero, 2                            # t2 = 2
      add s10, s10, t2                            # s10 = ( (current - 1) * 8 ) + 2
      add s2, s2, s10                             # Origem + deslocamento -> navios[s2]
      addi s3, s2, 1                              # s3  = navios[s2 + 1]

      jal converterInteiro                        # Converte para inteiro
      add a4, zero, a0                            # angle = a4

      addi s2, s2, 2                              # s2  = navios[s2 + 2]
      addi s3, s2, 1                              # s3  = navios[s2 + 1]
      jal converterInteiro                        # Converte para inteiro
      add a5, zero, a0                            # length = a5

      addi s2, s2, 2                              # s2  = navios[s2 + 2]
      addi s3, s2, 1                              # s3  = navios[s2 + 1]
      jal converterInteiro                        # Converte para inteiro
      add a6, zero, a0                            # row = a6

      addi s2, s2, 2                              # s2  = navios[s2 + 2]
      addi s3, s2, 1                              # s3  = navios[s2 + 1]
      jal converterInteiro                        # Converte para inteiro
      add a7, zero, a0                            # col = a7

      jal validaInsercoes                         # Faz validações

      bne s11, zero, insereEmbarcacoesError       # if (error != 0)
      add a3, zero, t0                            # Monta parametro current
      jal inserirTabuleiro                        # Faz validações

      jal imprimeBarcos                           # Imprime tabuleiro

      j insereEmbarcacoesErrorFim
    insereEmbarcacoesError:
      add a0, zero, s11                           # Define numero do erro
      li a7, 1                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      j insereEmbarcacoesFimWhile                 # break 
    insereEmbarcacoesErrorFim:
      addi t0, t0, 1                              # current++
      j insereEmbarcacoesWhile                    # Vai para condição
    insereEmbarcacoesFimWhile:
      add ra, zero, t6                            # Ajusta retorno
      ret
  ########## insereEmbarcacoes ##########

  ########## validaInsercoes ##########
    validaInsercoes:
      lw t2, board_size                           # board_size -> t2
      blt t2, a6, validaInsercoesReturn1          # if board_size < row
      blt t2, a7, validaInsercoesReturn1          # if board_size < col
      j validaInsercoes2
    validaInsercoesReturn1:
      addi s11, zero, 1                           # return 1 -> s11 = 1
      ret

    validaInsercoes2:
      beq a4, zero, validaInsercoes2Angulo        # if angle == 0  
      add t3, a6, a5                              # t3 = row + length
      blt t2, t3, validaInsercoesReturn2          # board_size < (row + length)
      j validaInsercoes3
    validaInsercoes2Angulo:
      add t3, a7, a5                              # t3 = col + length
      blt t2, t3, validaInsercoesReturn2          # board_size < (col + length)
      j validaInsercoes3
    validaInsercoesReturn2:
      addi s11, zero, 2                           # return 2 -> s11 = 2
      ret

    validaInsercoes3:
      add t3, zero, zero                          # insertions -> t3 = 0
    validaInsercoes3TesteWhile:
      blt t3, a5, validaInsercoes3While           # insertions < length
      j validaInsercoes3WhileFim
    validaInsercoes3While:
      addi t4, zero, 4                            # t4 = 4
      beq a4, zero, validaInsercoes3Angulo        # if angle == 0
      add t5, a6, t3                              # t5 = boardRow + insertions
      mul t5, t5, t2                              # t5 = (boardRow + insertions) * BoardSize
      add t5, t5, a7                              # t5 = ( (boardRow + insertions) * BoardSize) + boardCol
      mul t5, t5, t4                              # t5 = t5 * 4
      add a0, zero, a2                            # board[0][0]  
      add a0, a0, t5                              # board[0][0] + Deslocamento
      lw s1, (a0)                                 # board[row + insertions][col] -> s1 = &a0
      bne s1, zero, validaInsercoesReturn3        # if board[row + insertions][col] != 0
      j validaInsercoesReturn3Fim
    validaInsercoes3Angulo:
      mul t5, a6, t2                              # t5 = boardRow * BoardSize
      add a0, a7, t3                              # a0 = boardCol + insertions
      add t5, t5, a0                              # t5 = ( boardRow * BoardSize) + (boardCol + insertions)
      mul t5, t5, t4                              # t5 = t5 * 4
      add a0, zero, a2                            # board[0][0] -> a0
      add a0, a0, t5                              # board[0][0] + Deslocamento
      lw s1, (a0)                                  # board[row + insertions][col] -> s1 = &a0
      bne s1, zero, validaInsercoesReturn3        # if board[row + insertions][col] != 0      
      j validaInsercoesReturn3Fim
    validaInsercoesReturn3:
      addi s11, zero, 3                           # return 3 -> s11 = 3
      ret
    validaInsercoesReturn3Fim:
      addi t3, t3, 1                              # insertions++
      j validaInsercoes3TesteWhile                # Volta para condição

    validaInsercoes3WhileFim:
      add s11, zero, zero                         # return 0 -> s11 = 0
      ret
  ########## validaInsercoes ##########
  
  ########## inserirTabuleiro ##########
    inserirTabuleiro:
      add t3, zero, zero                          # insertions -> t3 = 0
    inserirTabuleiroTesteWhile:
      blt t3, a5, inserirTabuleiroWhile           # insertions < length
      j inserirTabuleiroWhileFim
    inserirTabuleiroWhile:
      addi t4, zero, 4                            # t4 = 4
      beq a4, zero, inserirTabuleiroAngulo        # if angle == 0
      add t5, a6, t3                              # t5 = boardRow + insertions
      mul t5, t5, t2                              # t5 = (boardRow + insertions) * BoardSize
      add t5, t5, a7                              # t5 = ( (boardRow + insertions) * BoardSize) + boardCol
      mul t5, t5, t4                              # t5 = t5 * 4
      add s1, zero, a2                            # board[0][0]  
      add s1, s1, t5                              # board[0][0] + Deslocamento
      sw a3, (s1)                                 # board[row + insertions][col] = current -> s1 = &a3
      j inserirTabuleiroAnguloFim
    inserirTabuleiroAngulo:
      mul t5, a6, t2                              # t5 = boardRow * BoardSize
      add s1, a7, t3                              # s1 = boardCol + insertions
      add t5, t5, s1                              # t5 = ( boardRow * BoardSize) + (boardCol + insertions)
      mul t5, t5, t4                              # t5 = t5 * 4
      add s1, zero, a2                            # board[0][0] -> s1
      add s1, s1, t5                              # board[0][0] + Deslocamento
      sw a3, (s1)                                 # board[row + insertions][col] -> s1 = &t6
    inserirTabuleiroAnguloFim:
      addi t3, t3, 1                              # insertions++
      j inserirTabuleiroTesteWhile                # Volta para condição
    inserirTabuleiroWhileFim:
      ret
  ########## inserirTabuleiro ##########

  ########## imprimeBarcos ##########
    imprimeBarcos:
      lw t2, board_size                           # BoardSize -> t2 = board_size
      add t3, zero, zero                          # boardRow -> t3 = 0
    imprimeBarcosWhile1:
      blt t3, t2, imprimeBarcosCorpoWhile1        # boardRow < BoardSize
      j imprimeBarcosFimWhile1
    imprimeBarcosCorpoWhile1:
      add t4, zero, zero                          # boardCol -> t4 = 0
    imprimeBarcosWhile2:
      blt t4, t2, imprimeBarcosCorpoWhile2        # boardCol < BoardSize
      j imprimeBarcosFimWhile2
    imprimeBarcosCorpoWhile2:
      la a0, espaco                               # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      add s0, zero, a2                            # board[0][0]
      addi t5, zero, 4                            # t5 = 4
      mul a1, t3, t2                              # a1 = boardRow * BoardSize
      add a1, a1, t4                              # a1 = a1 + boardCol
      mul a1, a1, t5                              # a1 = a1 * 4
      add s0, s0, a1                              # Origem + Deslocamento
      lw a0, (s0)                                 # &a0 = &(Origem + Deslocamento)
      li a7, 1                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      la a0, espaco                               # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      addi t4, t4, 1                              # boardCol++
      j imprimeBarcosWhile2                       # Volta para laço interno
    imprimeBarcosFimWhile2:
      la a0, barra_n                              # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      addi t3, t3, 1                              # boardRow++
      j imprimeBarcosWhile1                       # Volta para laço externo
    imprimeBarcosFimWhile1:
      ecall                                       # Chama SO
      ret
  ########## imprimeBarcos ##########

  ########## converterInteiro ##########
    # s11 - int *error
    # s2  - char current
    # s3  - char next
    converterInteiro:
      lb, s4, (s2)                                # s4 = &current
      lb, s5, (s3)                                # s4 = &next
      lb, t2, espaco                              # t2 = ' '
      lb, t3, barra_n                             # t3 = '\n'

      bne s11, zero, converterInteiroFim          # if (error != 0)
      beq s5, t2, converterInteiroIf              # if (next == ' ')
      beq s5, t3, converterInteiroIf              # if (next == '\n')
      j converterInteiroIfFim
    converterInteiroIf:
      addi t5, zero, 48                           # t5 = 48
      sub t4, s4, t5                              # t4 = current - 48
      add a0, zero, t4                            # a0 = t4
      ret
    converterInteiroIfFim:
      addi s11, zero, 4
    converterInteiroFim:
      add a0, zero, zero
      ret
  ########## converterInteiro ##########
  
  end:
    nop