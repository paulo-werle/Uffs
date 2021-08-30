.data
  # Inicia dados
  board: .space  400
  board_size: .word 10
  quantity: .asciz "Informe a quantidade de embarações: "
  data: .asciz "Informe os dados do %d° barco: " 

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

    la a0, quantity                           # Define mensagem de quantidade
    li a7, 4                                  # Define paramentro do ecall
    ecall                                     # Chama SO
    li a7, 5                                  # Define paramentro do ecall
    ecall                                     # Chama SO
    add t0, zero, a0                          # quantity -> t0

    addi t1, zero 1                           # current -> t1 = 1

    
  insereEmbarcacoesWhile:
    bge t0, t1, insereEmbarcacoesCorpoWhile   # quantity >= current
    j insereEmbarcacoesFimWhile
  insereEmbarcacoesCorpoWhile:
    la a0, data                               # Define mensagem de quantidade
    li a7, 4                                  # Define paramentro do ecall
    ecall                                     # Chama SO

    li a7, 5                                  # Define paramentro do ecall
    ecall                                     # Chama SO
    add t1, zero, a0                          # angle -> t0
    
    j insereEmbarcacoesWhile                  # Vai para condição
  insereEmbarcacoesFimWhile:

    ret

  ########## insereEmbarcacoes ##########
  
  end:
    nop