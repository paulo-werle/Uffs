.data
  # Inicia dados
  erro: .space 4
  operacao: .space 4
  quantidade_de_barcos: .space 4

  tiros: .space 4
  acertos: .space 4
  afundados: .space 4
  tiros_record: .space 4
  acertos_record: .space 4
  afundados_record: .space 4
  
  board: .space  400
  board_size: .word 10

  navios: .asciz "3\n1 1 1 1\n0 1 2 2\n0 1 6 4"

  # Impressões
  vencedor: .asciz "Temos um VENCEDOR\n"
  menu_info: .asciz "Informe qual ação deseja fazer: \n"
  menu_0: .asciz "0: Sair do jogo \n"
  menu_1: .asciz "1: Fazer uma nova jogada \n"
  menu_2: .asciz "2: Mostrar navios \n"
  menu_3: .asciz "3: Reiniciar jogo \n"

  jogada_linha: .asciz "Informe a Linha:\n"
  jogada_coluna: .asciz "Informe a Coluna:\n"

  jogada_feita: .asciz "Esta jogada já foi feita anteriormente \n"

  destruido_1: .asciz "O navio "
  destruido_2: .asciz " foi totalmente destruido\n"

  placar_record: .asciz "Record: --------\n"
  placar_voce: .asciz "Voce: ----------\n"
  placar_fim: .asciz "----------------\n"
  placar_tiros: .asciz "- Tiros: "
  placar_acertos: .asciz "- Acertos: "
  placar_afundados: .asciz "- Afundados: "

  tiro_errado:  .asciz " ø "
  tiro_agua:  .asciz " o "
  tiro_navio:  .asciz " x "

  espaco: .asciz " "
  barra_n: .asciz "\n"
  barra_t: .asciz "\t"
  barra_0: .asciz "\0"

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
    # Inicia dados
    la s6, tiros                                  # shots -> s6 = tiros
    sw zero, (s6)                                 # s6 = 0
    la s6, acertos                                # hits -> s6 = acertos
    sw zero, (s6)                                 # s6 = 0
    la s6, afundados                              # sunk -> s6 = afundados
    sw zero, (s6)                                 # s6 = 0
    la s6, tiros_record                           # shots_record -> s6 = tiros_record
    addi a7, zero, 100                            # a7 = 100
    sw a7, (s6)                                   # s6 = a7
    la s6, acertos_record                         # hits_record -> s6 = acertos_record
    sw zero, (s6)                                 # s6 = 0
    la s6, afundados_record                       # sunk_record -> s6 = afundados_record
    sw zero, (s6)                                 # s6 = 0

    la s0, board                                  # Board -> a2 = board[][]

    la s11, erro                                  # error -> s11 = error
    la s10, operacao                              # operation -> s10 = operation
    la s9, quantidade_de_barcos                   # quantity_ships -> s9 = quantity_ships 
    addi a6, zero, 3                              # a6 = 3
    sw a6, (s10)                                  # s9 = a6

    # Chama a primeira vez as funções
    la a2, board                                  # Board -> a2 = board[][]
    jal novoTabuleiro                             # novoTabuleiro(a2)

    la a2, board                                  # Board -> a2 = board[][]
    jal insereEmbarcacoes                         # insereEmbarcacoes(a2, s11, s9)

  mainWhile:
    lw s11, erro                                  # -> s11 = error
    lw s10, operacao                              # -> s10 = operation
    lw s9, quantidade_de_barcos                   # -> s9 = quantity_ships 

    bne s11, zero, mainFimWhile                   # if (s11 != 0)
    beq s10, zero, mainFimWhile                   # if (s10 == 0)
    beq s9, zero, mainFimWhile                    # if (s9 == 0)
  mainCorpoWhile:
    jal menu                                      # menu()
    la s10, operacao                              # s10 = &operacao
    sw a0, (s10)                                  # s10 = a0
    lw s10, operacao                              # s10 = operacao
  mainSwitch:
    addi t0, zero, 1                              # t0 = 1
    beq s10, t0, mainCase1                        # if (s10 == 1)
    addi t0, zero, 2                              # t0 = 2
    beq s10, t0, mainCase2                        # if (s10 == 2)
    addi t0, zero, 3                              # t0 = 3
    beq s10, t0, mainCase3                        # if (s10 == 3)
    j mainFimSwitch                               # Vai para o fim
  mainCase1:
    la a2, board                                  # Board -> a2 = board[][]
    la a3, tiros
    la a4, acertos
    la a5, afundados
    jal novaJogada                                # novaJogada(a2, a3, a4, a5)

    lw a1, tiros                                  # tiros -> a1 = &tiros
    lw a2, acertos                                # acertos -> a2 = &acertos
    lw a3, afundados                              # afundados -> a3 = &afundados
    lw a4, tiros_record                           # tiros_record -> a4 = &tiros_record
    lw a5, acertos_record                         # acertos_record -> a5 = &acertos_record
    lw a6, afundados_record                       # afundados_record -> a6 = &afundados_record
    jal imprimeDados                              # imprimeDados(a2, a3, a4, a5, a6, a7)
    
    j mainFimSwitch                               # Vai para o fim 
  mainCase2:
    la a2, board                                  # Board -> a2 = board[][]
    jal imprimeBarcos                             # imprimeBarcos(a2)
    j mainFimSwitch                               # Vai para o fim
  mainCase3:
    la a2, board                                  # Board -> a2 = board[][]
    jal novoTabuleiro                             # novoTabuleiro(a2)
    
    la s11, erro                                  # error -> s11 = error
    la s9, quantidade_de_barcos                   # quantity_ships -> s9 = quantity_ships 
    la a2, board                                  # Board -> a2 = board[][]
    jal insereEmbarcacoes                         # insereEmbarcacoes(a2, s11, s9)
    
    la s6, tiros                                  # shots -> s6 = tiros
    sw zero, (s6)                                 # s6 = 0
    la s6, acertos                                # hits -> s6 = acertos
    sw zero, (s6)                                 # s6 = 0
    la s6, afundados                              # sunk -> s6 = afundados
    sw zero, (s6)                                 # s6 = 0

    j mainFimSwitch                               # Vai para o fim

  mainFimSwitch:
    la a2, board                                  # Board -> a2 = board[][]
    la a5, quantidade_de_barcos                   # a5 = 0
    add a6, zero, zero                            # a6 = 0
    jal confereBarcos                             # confereBarcos(a2, a5, a6)
  mainIf:
    bne a4, zero, mainFimIf
    li a7, 4                                      # Define paramentro do ecall
    la a0, vencedor                               # Define mensagem
    ecall                                         # Chama SO
  mainIf2:
    lw t1, tiros                                  # tiros -> t1 = &tiros
    lw t2, tiros_record                           # tiros -> t2 = &tiros
    bge t1, t2 mainFimIf2
    lw s5, tiros                                  # shots -> s6 = tiros
    la s6, tiros_record                           # shots_record -> s6 = tiros_record
    sw s5, (s6)                                   # tiros_record = tiros
    lw s5, acertos                                # shots -> s6 = acertos
    la s6, acertos_record                         # shots_record -> s6 = acertos_record
    sw s5, (s6)                                   # acertos_record = acertos
    lw s5, afundados                              # shots -> s6 = afundados
    la s6, afundados_record                       # shots_record -> s6 = afundados_record
    sw s5, (s6)                                   # afundados_record = afundados
  mainFimIf2:
    la a2, board                                  # Board -> a2 = board[][]
    jal novoTabuleiro                             # novoTabuleiro(a2)
    
    la s11, erro                                  # error -> s11 = error
    la s9, quantidade_de_barcos                   # quantity_ships -> s9 = quantity_ships 
    la a2, board                                  # Board -> a2 = board[][]
    jal insereEmbarcacoes                         # insereEmbarcacoes(a2, s11, s9)
    
    la s6, tiros                                  # shots -> s6 = tiros
    sw zero, (s6)                                 # s6 = 0
    la s6, acertos                                # hits -> s6 = acertos
    sw zero, (s6)                                 # s6 = 0
    la s6, afundados                              # sunk -> s6 = afundados
    sw zero, (s6)                                 # s6 = 0
  mainFimIf:
    j mainWhile                                   # Retorna para o while
  mainFimWhile:

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

  ########## inserirTabuleiro ##########
    # Parametros
      # a2 - int board[BOARD_SIZE][BOARD_SIZE]
      # a4 - int angle
      # a5 - int length
      # a6 - int row
      # a7 - int col
      # a3 - int current
    # Retorno
      # -
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
    # Parametros
      # a2 -> int board[BOARD_SIZE][BOARD_SIZE]
    # Retorno
      # -
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
      la a0, barra_t                              # Define mensagem
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
      la a0, barra_n                              # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      ret
  ########## imprimeBarcos ##########
  
  ########## imprimeTiros ##########
    # Parametros
      # a2 -> int board[BOARD_SIZE][BOARD_SIZE]
    # Retorno
      # -
    imprimeTiros:
      lw t2, board_size                           # BoardSize -> t2 = board_size
      add t3, zero, zero                          # boardRow -> t3 = 0
    imprimeTirosWhile1:
      blt t3, t2, imprimeTirosCorpoWhile1         # boardRow < BoardSize
      j imprimeTirosFimWhile1
    imprimeTirosCorpoWhile1:
      add t4, zero, zero                          # boardCol -> t4 = 0
    imprimeTirosWhile2:
      blt t4, t2, imprimeTirosCorpoWhile2         # boardCol < BoardSize
      j imprimeTirosFimWhile2
    imprimeTirosCorpoWhile2:
      add s0, zero, a2                            # board[0][0]
      addi t5, zero, 4                            # t5 = 4
      mul a1, t3, t2                              # a1 = boardRow * BoardSize
      add a1, a1, t4                              # a1 = a1 + boardCol
      mul a1, a1, t5                              # a1 = a1 * 4
      add s0, s0, a1                              # Origem + Deslocamento
      lw a0, (s0)                                 # &a0 = &(Origem + Deslocamento)
    imprimeTirosIf:
      addi t0, zero, -1                           # t0 = -1
      bne a0, t0, imprimeTirosElseIf              # if(a0 != t0)
      la a0, tiro_errado                          # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      j imprimeTirosFimIf                         # Vai para o fim do if
    imprimeTirosElseIf:
      addi t0, zero, 0                            # t0 = 0
      blt a0, t0, imprimeTirosElse                # if ( board[row][col] < t0 )
      addi t0, zero, 11                           # t0 = 11
      bge a0, t0, imprimeTirosElse                # if ( board[row][col] >= t0 )
      la a0, tiro_agua                            # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      j imprimeTirosFimIf                         # Vai para o fim do if
    imprimeTirosElse:
      la a0, tiro_navio                           # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
    imprimeTirosFimIf:
      addi t4, t4, 1                              # boardCol++
      j imprimeTirosWhile2                        # Volta para laço interno
    imprimeTirosFimWhile2:
      la a0, barra_n                              # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      addi t3, t3, 1                              # boardRow++
      j imprimeTirosWhile1                        # Volta para laço externo
    imprimeTirosFimWhile1:
      la a0, barra_n                              # Define mensagem
      li a7, 4                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      ret
  ########## imprimeTiros ##########

  ########## imprimeDados ##########
    # Parametros
      # a1 - int shots
      # a2 - int hits
      # a3 - int sunk
      # a4 - int shots_record
      # a5 - int hits_record
      # a6 - int sunk_record
    # Retorno
      # -
    imprimeDados:
      li a7, 4                                    # Define paramentro do ecall

      la a0, placar_record                        # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_tiros                         # Define mensagem
      ecall                                       # Chama SO
      li a7, 1                                    # Define paramentro do ecall
      add a0, zero, a4                            # Define mensagem
      ecall                                       # Chama SO
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_acertos                       # Define mensagem
      ecall                                       # Chama SO
      li a7, 1                                    # Define paramentro do ecall
      add a0, zero, a5                            # Define mensagem
      ecall                                       # Chama SO
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_afundados                     # Define mensagem
      ecall                                       # Chama SO
      li a7, 1                                    # Define paramentro do ecall
      add a0, zero, a6                            # Define mensagem
      ecall                                       # Chama SO
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_fim                           # Define mensagem
      ecall                                       # Chama SO

      la a0, placar_voce                          # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_tiros                         # Define mensagem
      ecall                                       # Chama SO
      li a7, 1                                    # Define paramentro do ecall
      add a0, zero, a1                            # Define mensagem
      ecall                                       # Chama SO
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_acertos                       # Define mensagem
      ecall                                       # Chama SO
      li a7, 1                                    # Define paramentro do ecall
      add a0, zero, a2                            # Define mensagem
      ecall                                       # Chama SO
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_afundados                     # Define mensagem
      ecall                                       # Chama SO
      li a7, 1                                    # Define paramentro do ecall
      add a0, zero, a3                            # Define mensagem
      ecall                                       # Chama SO
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      la a0, placar_fim                           # Define mensagem
      ecall                                       # Chama SO

      ret
  ########## imprimeDados ##########

  ########## confereBarcos ##########
    # Parametros
      # a2 - int board[BOARD_SIZE][BOARD_SIZE]
      # a5 - int *sunk
      # a6 - int ships
    # Retorno
      # a4 - int 
    confereBarcos:
      lw t2, board_size                           # BoardSize -> t2 = board_size
      add t3, zero, zero                          # boardRow -> t3 = 0
      add a4, zero, zero                          # quantidade -> a4 = 0
    confereBarcosWhile1:
      blt t3, t2, confereBarcosCorpoWhile1        # boardRow < BoardSize
      j confereBarcosFimWhile1
    confereBarcosCorpoWhile1:
      add t4, zero, zero                          # boardCol -> t4 = 0
    confereBarcosWhile2:
      blt t4, t2, confereBarcosCorpoWhile2        # boardCol < BoardSize
      j confereBarcosFimWhile2
    confereBarcosCorpoWhile2:

      add s0, zero, a2                            # board[0][0]
      addi t5, zero, 4                            # t5 = 4
      mul a1, t3, t2                              # a1 = boardRow * BoardSize
      add a1, a1, t4                              # a1 = a1 + boardCol
      mul a1, a1, t5                              # a1 = a1 * 4
      add s0, s0, a1                              # Origem + Deslocamento
      lw a1, (s0)                                 # &a1 = &(Origem + Deslocamento)
    
    confereBarcosIf:
      beq a6, zero, confereBarcosElse             # if(a6 == 0)
    confereBarcosIfIf2:
      bne a1, a6, confereBarcosIfFimIf2           # if ( board[boardRow][boardCol] != a6 )
      addi a4, a4, 1                              # a4 += 1
    confereBarcosIfFimIf2:
      j confereBarcosFimIf                        # Vai para o fim do if
    confereBarcosElse:
    confereBarcosElseIf2:
      addi t0, zero, 1                            # t0 = 1
      blt a1, t0, confereBarcosElseFimIf2         # if ( board[row][col] < t0 )
      addi t0, zero, 11                           # t0 = 11
      bge a1, t0, confereBarcosElseFimIf2         # if ( board[row][col] >= t0 )
      addi a4, a4, 1                              # a4 += 1
    confereBarcosElseFimIf2:
    confereBarcosFimIf:
      addi t4, t4, 1                              # boardCol++
      j confereBarcosWhile2                       # Volta para laço interno
    confereBarcosFimWhile2:
      addi t3, t3, 1                              # boardRow++
      j confereBarcosWhile1                       # Volta para laço externo
    confereBarcosFimWhile1:
    confereBarcosIf2:
      bne a4, zero, confereBarcosFimIf2           # if ( quantity != 0 )
      beq a6, zero, confereBarcosFimIf2           # if ( ships == 0 )
      li a7, 4                                    # Define paramentro do ecall
      la a0, destruido_1                          # Define mensagem
      ecall                                       # Chama SO
      li a7, 1                                    # Define paramentro do ecall
      add a0, zero, a6                            # Define mensagem
      ecall                                       # Chama SO
      li a7, 4                                    # Define paramentro do ecall
      la a0, destruido_2                          # Define mensagem
      ecall                                       # Chama SO
      lw t0, (a5)                                 # t0 = *sunk
      addi t0, t0, 1                              # t0 += 1
      sw t0, (a5)                                 # *sunk = t0
    confereBarcosFimIf2:
      ret
  ########## confereBarcos ##########

  ########## validaInsercoes ##########
    # Parametros
      # a2 - int board[BOARD_SIZE][BOARD_SIZE]
      # a4 - int angle
      # a5 - int length
      # a6 - int row
      # a7 - int col
    # Retorno
      # s11 - int
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

  ########## converterInteiro ##########
    # Parametros
      # s11 - int *error
      # s2  - char current
      # s3  - char next
    # Retorno
      # a0 - int
    converterInteiro:
      lb, s4, (s2)                                # s4 = &current
      lb, s5, (s3)                                # s4 = &next
      lb, t2, espaco                              # t2 = ' '
      lb, t3, barra_n                             # t3 = '\n'
      lb, t4, barra_0                             # t4 = '\0'

      bne s11, zero, converterInteiroFim          # if (error != 0)
      beq s5, t2, converterInteiroIf              # if (next == ' ')
      beq s5, t3, converterInteiroIf              # if (next == '\n')
      beq s5, t4, converterInteiroIf              # if (next == '\0')
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

  ########## insereEmbarcacoes ##########
    # Parametros
      # a2 -> int board[BOARD_SIZE][BOARD_SIZE]
      # s11 -> int *error
      # s9 -> int *quantity_ships
    # Retorno
      # -
    insereEmbarcacoes:
      add t6, zero, ra                            # Salva endereço de retorno atual
      addi t0, zero, 1                            # current -> t0 = 1

      sw zero, (s11)                              # error -> s11 = 0
      sw zero, (s9)                               # quantity_ships -> s9 = 0
      lw s11, (s11)                               # s11 = erro                  

      la s2, navios                               # navios -> s2  = navios[0]
      addi s3, s2, 1                              # s3  = navios[1]
      jal converterInteiro                        # Converte para inteiro
      add t1, zero, a0                            # quantity -> t1 = a0

      bne s11, zero, insereEmbarcacoesError       # if (error != 0)
    insereEmbarcacoesWhile:
      bge t1, t0, insereEmbarcacoesCorpoWhile     # quantity >= current
      j insereEmbarcacoesFimWhile
    insereEmbarcacoesCorpoWhile:

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
      
      bne s11, zero, insereEmbarcacoesError       # if (error != 0)
      jal validaInsercoes                         # Faz validações

      bne s11, zero, insereEmbarcacoesError       # if (error != 0)
      add a3, zero, t0                            # Monta parametro current
      jal inserirTabuleiro                        # Insere no tabuleiro
      lw t2, (s9)                                 # t2 = *s9
      addi t2, t2, 1                              # t2 = t2 + 1
      sw t2, (s9)                                 # *s9 = t2

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
  
  ########## novaJogada ##########
    # Parametros
      # a2 - int board[BOARD_SIZE][BOARD_SIZE]
      # a3 - int *shots
      # a4 - int *hits
      # a5 - int *sunk
    # Retorno
      # -
    novaJogada:
      add t6, zero, ra                            # Salva endereço de retorno atual
      li a7, 4                                    # Define paramentro do ecall
      la a0, jogada_linha                         # Define mensagem
      ecall                                       # Chama SO
      li a7, 5                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      add t0, zero, a0                            # t0 = a0
      li a7, 4                                    # Define paramentro do ecall
      la a0, jogada_coluna                        # Define mensagem
      ecall                                       # Chama SO
      li a7, 5                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      add t1, zero, a0                            # t1 = a0
      lw t2, board_size                           # t2 = board_size
      add a6, zero, zero                          # a6 = board[row][col]

      add t3, zero, a2                            # board[0][0]
      addi t4, zero, 4                            # t4 = 4
      mul t5, t0, t2                              # t5 = boardRow * BoardSize
      add t5, t5, t1                              # t5 = t5 + boardCol
      mul t5, t5, t4                              # t5 = t5 * 4
      add t3, t3, t5                              # Origem + Deslocamento
      lw t4, (t3)                                 # board[row][col]

    novaJogadaIf:
      addi t5, zero, 0                            # t5 = 0
      blt t4, t5, novaJogadaElse                  # if ( board[row][col] < t5 )
      addi t5, zero, 11                           # t5 = 11
      bge t4, t5, novaJogadaElse                  # if ( board[row][col] >= t5 )
    novaJogadaCorpoIf:
    novaJogadaIf2:
      beq t4, zero, novaJogadaElse2               # if( board[row][col] == 0)
    novaJogadaCorpoIf2:
      add a6, zero, t4                            # a6 = board[row][col]
      addi t5, t4, 10                             # t5 = t4 + 10
      sw t5, (t3)                                 # t3 = t5
      lw t5, (a4)                                 # t5 = *a4
      addi t5, t5, 1                              # t5 += 1
      sw t5, (a4)                                 # a4 = t5
      j novaJogadaFimIf2                          # Vai para o fim do if
    novaJogadaElse2:
      addi t5, zero, -1                           # t5 = -1
      sw t5, (t3)                                 # t3 = t5
    novaJogadaFimIf2:
      j novaJogadaFimIf                           # Vai para o fim do if
    novaJogadaElse:
      li a7, 4                                    # Define paramentro do ecall
      la a0, jogada_feita                         # Define mensagem
      ecall                                       # Chama SO
    novaJogadaFimIf:
      jal imprimeTiros                            # imprimeTiros(a2)

      lw t5, (a3)                                 # t5 = *a3
      addi t5, t5, 1                              # t5 += 1
      sw t5, (a3)                                 # a3 = t5
      jal confereBarcos                           # confereBarcos(a2, a6, a5)
      add ra, zero, t6                            # Ajusta retorno
      ret

  ########## novaJogada ##########

  ########## menu ##########
    # Parametros
      # -
    # Retorno
      # a0 - int
    menu:
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      la a0, menu_info                            # Define mensagem
      ecall                                       # Chama SO
      la a0, menu_0                               # Define mensagem
      ecall                                       # Chama SO
      la a0, menu_1                               # Define mensagem
      ecall                                       # Chama SO
      la a0, menu_2                               # Define mensagem
      ecall                                       # Chama SO
      la a0, menu_3                               # Define mensagem
      ecall                                       # Chama SO
      li a7, 5                                    # Define paramentro do ecall
      ecall                                       # Chama SO
      add t0, zero, a0                            # t0 = a0
      li a7, 4                                    # Define paramentro do ecall
      la a0, barra_n                              # Define mensagem
      ecall                                       # Chama SO
      add a0, zero, t0                            # a0 = t0

      ret
  ########## menu ##########

  end:
    nop