.data
  # Inicia dados
  board: .space  400
  board_size: .word 10
  quantity: .asciz "Informe a quantidade de embarações: "
  data: .asciz "Informe os dados do barco: "

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

    la s0, board                          # Board -> s0 = board[][]

    # add a2, zero, s0                      # Parametro da função (board[][])
    # jal novoTabuleiro                     # Chama a função

    add a2, zero, s0                      # Parametro da função (board[][])
    jal insereEmbarcacoes                 # Chama a função

    j end

  ########## novoTabuleiro ##########
    novoTabuleiro:
      lw t0, board_size                     # BoardSize -> t0 = board_size
      add t1, zero, zero                    # boardRow -> t1 = 0
    novoTabuleiroWhile1:
      blt t1, t0, novoTabuleiroCorpoWhile1  # boardRow < BoardSize
      j novoTabuleiroFimWhile1
    novoTabuleiroCorpoWhile1:
      add t2, zero, zero                    # boardCol -> t2 = 0
    novoTabuleiroWhile2:
      blt t2, t0, novoTabuleiroCorpoWhile2  # boardCol < BoardSize
      j novoTabuleiroFimWhile2
    novoTabuleiroCorpoWhile2:
      add t3, zero, a2                      # board[0][0]
      addi t4, zero, 4                      # t4 = 4
      mul t5, t1, t0                        # t5 = boardRow * BoardSize
      add t5, t5, t2                        # t5 = t5 + boardCol
      mul t5, t5, t4                        # t5 = t5 * 4
      add t3, t3, t5                        # Origem + Deslocamento
      sw zero, (t3)
      addi t2, t2, 1                        # boardCol++
      j novoTabuleiroWhile2
    novoTabuleiroFimWhile2:
      addi t1, t1, 1                        # boardRow++
      j novoTabuleiroWhile1                 # Volta para laço interno
    novoTabuleiroFimWhile1:
      ret
  ########## novoTabuleiro ##########

  ########## insereEmbarcacoes ##########
    insereEmbarcacoes:
      addi t0, zero, 1                          # current -> t0 = 1
      addi t1, zero, 1                          # quantity -> t1 = 1
    insereEmbarcacoesWhile:
      bge t1, t0, insereEmbarcacoesCorpoWhile   # quantity >= current
      j insereEmbarcacoesFimWhile
    insereEmbarcacoesCorpoWhile:
      addi a4, zero, 0                          # angle -> a4 = 1
      addi a5, zero, 4                          # length -> a5 = 5
      addi a6, zero, 2                          # row -> a6 = 5
      addi a7, zero, 7                          # col -> a7 = 5

      add t6, zero, ra                          # Salva endereço de retorno atual
      jal validaInsercoes                       # Faz validações
      add ra, zero, t6                          # Ajusta retorno

      addi t0, t0, 1                            # current++
      j insereEmbarcacoesWhile                  # Vai para condição
    insereEmbarcacoesFimWhile:
      ret

  ########## insereEmbarcacoes ##########

  ########## validaInsercoes ##########
    validaInsercoes:
      lw t2, board_size                         # board_size -> t2
      blt t2, a6, validaInsercoesReturn1        # if board_size < row
      blt t2, a7, validaInsercoesReturn1        # if board_size < col
      j validaInsercoes2
    validaInsercoesReturn1:
      addi a0, zero, 1                          # return 1 -> a0 = 1
      ret

    validaInsercoes2:
      beq a4, zero, validaInsercoes2Angulo      # if angle == 0  
      add t3, a6, a5                            # t3 = row + length
      blt t2, t3, validaInsercoesReturn2        # board_size < (row + length)
      j validaInsercoes3
    validaInsercoes2Angulo:
      add t3, a7, a5                            # t3 = col + length
      blt t2, t3, validaInsercoesReturn2        # board_size < (col + length)
      j validaInsercoes3
    validaInsercoesReturn2:
      addi a0, zero, 2                          # return 2 -> a0 = 2
      ret

    validaInsercoes3:
      add t3, zero, zero                        # insertions -> t3 = 0
      blt t3, a5, validaInsercoes3While         # insertions < length
      j validaInsercoes3WhileFim
    validaInsercoes3While:
      addi t4, zero, 4                          # t4 = 4
      beq a4, zero, validaInsercoes3Angulo      # if angle == 0
      add t5, a6, t3                            # t5 = boardRow + insertions
      mul t5, t5, t2                            # t5 = (boardRow + insertions) * BoardSize
      add t5, t5, a7                            # t5 = ( (boardRow + insertions) * BoardSize) + boardCol
      mul t5, t5, t4                            # t5 = t5 * 4
      add t6, zero, a2                          # board[0][0]  
      add t6, t6, t5                            # board[0][0] + Deslocamento
      lw s1, (t6)                               # board[row + insertions][col] -> s1 = &t6
      bne s1, zero, validaInsercoesReturn3      # if board[row + insertions][col] != 0
      j validaInsercoesReturn3Fim
    validaInsercoes3Angulo:
      mul t5, a6, t2                            # t5 = boardRow * BoardSize
      add t6, a7, t3                            # t6 = boardCol + insertions
      add t5, t5, a6                            # t5 = ( boardRow * BoardSize) + (boardCol + insertions)
      mul t5, t5, t4                            # t5 = t5 * 4
      add t6, zero, a2                          # board[0][0] -> t6
      add t6, t6, t5                            # board[0][0] + Deslocamento
      lw s1, (t6)                               # board[row + insertions][col] -> s1 = &t6
      bne s1, zero, validaInsercoesReturn3      # if board[row + insertions][col] != 0      
      j validaInsercoesReturn3Fim
    validaInsercoesReturn3:
      addi a0, zero, 3                          # return 3 -> a0 = 3
      ret
    validaInsercoesReturn3Fim:
      addi t3, t3, 1                            # insertions++

    validaInsercoes3WhileFim:
      addi a0, zero, zero                       # return 0 -> a0 = 0
      ret

  ########## validaInsercoes ##########
  
  end:
    nop