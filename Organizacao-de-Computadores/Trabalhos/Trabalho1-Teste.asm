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
  erro_1: .asciz "A posição do navio é invalida\n"
  erro_2: .asciz "O navio extrapola as dimenções da matriz\n"
  erro_3: .asciz "Ocorre sobreposição dos navios\n"
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

.text
  main:
    la s6, tiros                              # tiros = 0
    sw zero, (s6)
    la s6, acertos                            # acertos = 0
    sw zero, (s6)
    la s6, afundados                          # afundados = 0
    sw zero, (s6)
    la s6, tiros_record                       # tiros_record = 100
    addi a7, zero, 100
    sw a7, (s6) 
    la s6, acertos_record                     # acertos_record = 0 
    sw zero, (s6)
    la s6, afundados_record                   # afundados_record = 0
    sw zero, (s6)

    la a2, board                              # a2 = &board[][]
    jal novoTabuleiro                         # novoTabuleiro(a2)

    la a2, board                              # a2 = &board[][]
    la s11, erro                              # s11 = &erro
    la s10, operacao                          # s11 = &operacao
    la s9, quantidade_de_barcos               # s9 = &quantidade_de_barcos
    addi a6, zero, 3
    sw a6, (s10)                              # quantidade_de_barcos = 3
    jal insereEmbarcacoes                     # insereEmbarcacoes(a2, s11, s9)

  mainWhile:
    lw s11, erro                              # s11 = error
    lw s10, operacao                          # s10 = operation
    lw s9, quantidade_de_barcos               # s9 = quantity_ships

    bne s11, zero, mainFimWhile               # if ( s11 != 0 )
    beq s10, zero, mainFimWhile               # if ( s10 == 0 )
    beq s9, zero, mainFimWhile                # if ( s9 == 0 )
  mainCorpoWhile:
    jal menu                                  # menu()
    la s10, operacao                          # s10 = &operacao
    sw a0, (s10)
    lw s10, operacao
  mainSwitch:
    addi t0, zero, 1
    beq s10, t0, mainCase1                    # if ( operacao == 1 )
    addi t0, zero, 2
    beq s10, t0, mainCase2                    # if ( operacao == 2 )
    addi t0, zero, 3
    beq s10, t0, mainCase3                    # if ( operacao == 3 )
    j mainFimSwitch
  mainCase1:
    la a2, board                              # a2 = &board[][]
    la a3, tiros                              # a3 = &tiros
    la a4, acertos                            # a4 = &acertos
    la a5, afundados                          # a5 = &afundados
    jal novaJogada                            # novaJogada(a2, a3, a4, a5)

    lw a1, tiros                              # a1 = &tiros
    lw a2, acertos                            # a2 = &acertos
    lw a3, afundados                          # a3 = &afundados
    lw a4, tiros_record                       # a4 = &tiros_record
    lw a5, acertos_record                     # a5 = &acertos_record
    lw a6, afundados_record                   # a6 = &afundados_record
    jal imprimeDados                          # imprimeDados(a2, a3, a4, a5, a6, a7)
    
    j mainFimSwitch
  mainCase2:
    la a2, board                              # a2 = &board[][]
    jal imprimeBarcos                         # imprimeBarcos(a2)
    j mainFimSwitch
  mainCase3:
    la a2, board                              # a2 = &board[][]
    jal novoTabuleiro                         # novoTabuleiro(a2)
    
    la a2, board                              # a2 = &board[][]
    la s11, erro                              # s11 = &error
    la s9, quantidade_de_barcos               # s9 = &quantity_ships 
    jal insereEmbarcacoes                     # insereEmbarcacoes(a2, s11, s9)
    
    la s6, tiros
    sw zero, (s6)                             # tiros = 0
    la s6, acertos
    sw zero, (s6)                             # acertos = 0
    la s6, afundados
    sw zero, (s6)                             # afundados = 0

    j mainFimSwitch

  mainFimSwitch:
    la a2, board                              # a2 = &board[][]
    la a5, quantidade_de_barcos               # a5 = &quantidade_de_barcos
    add a6, zero, zero                        # a6 = 0
    jal confereBarcos                         # confereBarcos(a2, a5, a6)
  mainIf:
    bne a4, zero, mainFimIf                   # if ( a4 == 0 )
    li a7, 4
    la a0, vencedor
    ecall                                     # Imprime string
  mainIf2:
    lw t1, tiros                              # t1 = &tiros
    lw t2, tiros_record                       # t2 = &tiros_record
    bge t1, t2 mainFimIf2                     # if ( tiros >= tiros_record)
    lw s5, tiros
    la s6, tiros_record
    sw s5, (s6)                               # tiros_record = tiros
    lw s5, acertos
    la s6, acertos_record
    sw s5, (s6)                               # acertos_record = acertos
    lw s5, afundados
    la s6, afundados_record
    sw s5, (s6)                               # afundados_record = afundados
  mainFimIf2:
    la a2, board                              # a2 = &board[][]
    jal novoTabuleiro                         # novoTabuleiro(a2)
    
    la s11, erro                              # s11 = &error
    la s9, quantidade_de_barcos               # s9 = &quantity_ships 
    la a2, board                              # a2 = &board[][]
    jal insereEmbarcacoes                     # insereEmbarcacoes(a2, s11, s9)
    
    la s6, tiros
    sw zero, (s6)                             # tiros = 0
    la s6, acertos
    sw zero, (s6)                             # acertos = 0
    la s6, afundados
    sw zero, (s6)                             # afundados = 0
  mainFimIf:
    j mainWhile
  mainFimWhile:
    j end

  ########## novoTabuleiro ##########
    # Parametros
      # a2 - int board[BOARD_SIZE][BOARD_SIZE]
    # Retorno
      # -
    novoTabuleiro:
      lw t0, board_size                       # t0 = board_size
      add t1, zero, zero                      # row = 0
    novoTabuleiroWhile1:
      blt t1, t0, novoTabuleiroCorpoWhile1    # if ( row < board_size )
      j novoTabuleiroFimWhile1
    novoTabuleiroCorpoWhile1:
      add t2, zero, zero                      # col = 0
    novoTabuleiroWhile2:
      blt t2, t0, novoTabuleiroCorpoWhile2    # if ( col < board_size )
      j novoTabuleiroFimWhile2
    novoTabuleiroCorpoWhile2:
      add t3, zero, a2
      addi t4, zero, 4
      mul t5, t1, t0
      add t5, t5, t2
      mul t5, t5, t4
      add t3, t3, t5                          # board[][] + (( row * board_size ) + col ) * 4
      sw zero, (t3)                           # origem + deslocamento
      addi t2, t2, 1                          # col++
      j novoTabuleiroWhile2
    novoTabuleiroFimWhile2:
      addi t1, t1, 1                          # col++
      j novoTabuleiroWhile1
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
      add t3, zero, zero                      # insercoes = 0
    inserirTabuleiroTesteWhile:
      blt t3, a5, inserirTabuleiroWhile       # insercoes < length
      j inserirTabuleiroWhileFim
    inserirTabuleiroWhile:
      addi t4, zero, 4                        # t4 = 4
      beq a4, zero, inserirTabuleiroAngulo    # if angle == 0
      add t5, a6, t3
      mul t5, t5, t2
      add t5, t5, a7
      mul t5, t5, t4
      add s1, zero, a2
      add s1, s1, t5                          # board[][] + (( row * insercoes ) + col ) * 4
      sw a3, (s1)                             # origem + deslocamento
      j inserirTabuleiroAnguloFim
    inserirTabuleiroAngulo:
      mul t5, a6, t2
      add s1, a7, t3
      add t5, t5, s1
      mul t5, t5, t4
      add s1, zero, a2
      add s1, s1, t5                          # board[][] + (( row * board_size ) + ( col + insercoes ) * 4
      sw a3, (s1)                             # origem + deslocamento
    inserirTabuleiroAnguloFim:
      addi t3, t3, 1                          # insercoes++
      j inserirTabuleiroTesteWhile
    inserirTabuleiroWhileFim:
      ret
  ########## inserirTabuleiro ##########

  ########## imprimeBarcos ##########
    # Parametros
      # a2 -> int board[BOARD_SIZE][BOARD_SIZE]
    # Retorno
      # -
    imprimeBarcos:
      lw t2, board_size                       # t2 = board_size
      add t3, zero, zero                      # row = 0
    imprimeBarcosWhile1:
      blt t3, t2, imprimeBarcosCorpoWhile1    # if ( row < board_size )
      j imprimeBarcosFimWhile1
    imprimeBarcosCorpoWhile1:
      add t4, zero, zero                      # col = 0
    imprimeBarcosWhile2:
      blt t4, t2, imprimeBarcosCorpoWhile2    # if ( col < board_size )
      j imprimeBarcosFimWhile2
    imprimeBarcosCorpoWhile2:
      la a0, barra_t
      li a7, 4
      ecall                                   # Imprime string
      add s0, zero, a2
      addi t5, zero, 4
      mul a1, t3, t2
      add a1, a1, t4
      mul a1, a1, t5
      add s0, s0, a1                          # board[][] + (( row * board_size ) + col ) * 4
      lw a0, (s0)                             # origem + deslocamento
      li a7, 1
      ecall                                   # Imprime inteiro
      la a0, espaco
      li a7, 4
      ecall                                   # Imprime string
      addi t4, t4, 1                          # col++
      j imprimeBarcosWhile2
    imprimeBarcosFimWhile2:
      la a0, barra_n
      li a7, 4
      ecall                                   # Imprime string
      addi t3, t3, 1                          # row++
      j imprimeBarcosWhile1
    imprimeBarcosFimWhile1:
      la a0, barra_n
      li a7, 4
      ecall                                   # Imprime string
      ret
  ########## imprimeBarcos ##########
  
  ########## imprimeTiros ##########
    # Parametros
      # a2 -> int board[BOARD_SIZE][BOARD_SIZE]
    # Retorno
      # -
    imprimeTiros:
      lw t2, board_size                       # t2 = board_size
      add t3, zero, zero                      # row = 0
    imprimeTirosWhile1:
      blt t3, t2, imprimeTirosCorpoWhile1     # if ( row < board_size )
      j imprimeTirosFimWhile1
    imprimeTirosCorpoWhile1:
      add t4, zero, zero                      # col = 0
    imprimeTirosWhile2:
      blt t4, t2, imprimeTirosCorpoWhile2     # if ( col < board_size )
      j imprimeTirosFimWhile2
    imprimeTirosCorpoWhile2:
      add s0, zero, a2
      addi t5, zero, 4
      mul a1, t3, t2
      add a1, a1, t4
      mul a1, a1, t5
      add s0, s0, a1                          # board[][] + (( row * board_size ) + col ) * 4
      lw a0, (s0)                             # origem + deslocamento
    imprimeTirosIf:
      addi t0, zero, -1
      bne a0, t0, imprimeTirosElseIf          # if ( board[row][col] != -1 )
      la a0, tiro_errado
      li a7, 4
      ecall                                   # Imprime string
      j imprimeTirosFimIf
    imprimeTirosElseIf:
      addi t0, zero, 0
      blt a0, t0, imprimeTirosElse            # if ( board[row][col] < 0 )
      addi t0, zero, 11
      bge a0, t0, imprimeTirosElse            # if ( board[row][col] >= 11 )
      la a0, tiro_agua
      li a7, 4
      ecall                                   # Imprime string
      j imprimeTirosFimIf
    imprimeTirosElse:
      la a0, tiro_navio
      li a7, 4
      ecall                                   # Imprime string
    imprimeTirosFimIf:
      addi t4, t4, 1                          # col++
      j imprimeTirosWhile2
    imprimeTirosFimWhile2:
      la a0, barra_n
      li a7, 4
      ecall                                   # Imprime string
      addi t3, t3, 1                          # row++
      j imprimeTirosWhile1
    imprimeTirosFimWhile1:
      la a0, barra_n
      li a7, 4
      ecall                                   # Imprime string
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
      li a7, 4                                
      la a0, placar_record                    
      ecall                                   # Imprime string
      la a0, placar_tiros
      ecall                                   # Imprime string
      li a7, 1
      add a0, zero, a4
      ecall                                   # Imprime inteiro
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      la a0, placar_acertos
      ecall                                   # Imprime string
      li a7, 1
      add a0, zero, a5
      ecall                                   # Imprime inteiro
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      la a0, placar_afundados
      ecall                                   # Imprime string
      li a7, 1
      add a0, zero, a6
      ecall                                   # Imprime inteiro
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      la a0, placar_fim
      ecall                                   # Imprime string

      la a0, placar_voce
      ecall                                   # Imprime string
      la a0, placar_tiros
      ecall                                   # Imprime string
      li a7, 1
      add a0, zero, a1
      ecall                                   # Imprime inteiro
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      la a0, placar_acertos
      ecall                                   # Imprime string
      li a7, 1
      add a0, zero, a2
      ecall                                   # Imprime inteiro
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      la a0, placar_afundados
      ecall                                   # Imprime string
      li a7, 1
      add a0, zero, a3
      ecall                                   # Imprime inteiro
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      la a0, placar_fim
      ecall                                   # Imprime string

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
      lw t2, board_size                       # t2 = board_size
      add t3, zero, zero                      # row = 0
      add a4, zero, zero                      # a4 = 0
    confereBarcosWhile1:
      blt t3, t2, confereBarcosCorpoWhile1    # if ( row < board_size )
      j confereBarcosFimWhile1
    confereBarcosCorpoWhile1:
      add t4, zero, zero                      # col = 0
    confereBarcosWhile2:
      blt t4, t2, confereBarcosCorpoWhile2    # if ( col < board_size )
      j confereBarcosFimWhile2
    confereBarcosCorpoWhile2:

      add s0, zero, a2
      addi t5, zero, 4
      mul a1, t3, t2
      add a1, a1, t4
      mul a1, a1, t5
      add s0, s0, a1                          # board[][] + (( row * board_size ) + col ) * 4
      lw a1, (s0)                             # origem + deslocamento
    
    confereBarcosIf:
      beq a6, zero, confereBarcosElse         # if ( ships == 0 )
    confereBarcosIfIf2:
      bne a1, a6, confereBarcosIfFimIf2       # if ( board[row][col] != ships )
      addi a4, a4, 1                          # a4 += 1
    confereBarcosIfFimIf2:
      j confereBarcosFimIf
    confereBarcosElse:
    confereBarcosElseIf2:
      addi t0, zero, 1
      blt a1, t0, confereBarcosElseFimIf2     # if ( board[row][col] < 1 )
      addi t0, zero, 11
      bge a1, t0, confereBarcosElseFimIf2     # if ( board[row][col] >= 11 )
      addi a4, a4, 1                          # a4 += 1
    confereBarcosElseFimIf2:
    confereBarcosFimIf:
      addi t4, t4, 1                          # col++
      j confereBarcosWhile2
    confereBarcosFimWhile2:
      addi t3, t3, 1                          # row++
      j confereBarcosWhile1
    confereBarcosFimWhile1:
    confereBarcosIf2:
      bne a4, zero, confereBarcosFimIf2       # if ( a4 != 0 )
      beq a6, zero, confereBarcosFimIf2       # if ( ships == 0 )
      li a7, 4
      la a0, destruido_1
      ecall                                   # Imprime string
      li a7, 1
      add a0, zero, a6
      ecall                                   # Imprime inteiro
      li a7, 4
      la a0, destruido_2
      ecall                                   # Imprime string
      lw t0, (a5)
      addi t0, t0, 1
      sw t0, (a5)                             # *sunk++
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
      # s11 - int *error
    # Retorno
      # s11 - int
    validaInsercoes:
      lw t2, board_size                       # t2 = board_size
      blt t2, a6, validaInsercoesReturn1      # if ( board_size < row )
      blt t2, a7, validaInsercoesReturn1      # if ( board_size < col )
      j validaInsercoes2
    validaInsercoesReturn1:
      addi t4, zero, 1
      sw t4, (s11)                            # *error = 1
      ret

    validaInsercoes2:
      beq a4, zero, validaInsercoes2Angulo    # if ( angle == 0 )
      add t3, a6, a5
      blt t2, t3, validaInsercoesReturn2      # if ( board_size < (row + length) )
      j validaInsercoes3
    validaInsercoes2Angulo:
      add t3, a7, a5
      blt t2, t3, validaInsercoesReturn2      # if ( board_size < (col + length) )
      j validaInsercoes3
    validaInsercoesReturn2:
      addi t4, zero, 2
      sw t4, (s11)                            # *error = 2
      ret

    validaInsercoes3:
      add t3, zero, zero                      # insertions = 0
    validaInsercoes3TesteWhile:
      blt t3, a5, validaInsercoes3While       # if ( insertions < length )
      j validaInsercoes3WhileFim
    validaInsercoes3While:
      addi t4, zero, 4
      beq a4, zero, validaInsercoes3Angulo    # if ( angle == 0 )
      add t5, a6, t3
      mul t5, t5, t2
      add t5, t5, a7
      mul t5, t5, t4
      add a0, zero, a2
      add a0, a0, t5                          # board[][] + ((( row + insertions) * board_size ) + col ) * 4
      lw s1, (a0)                             # origem + deslocamento

      bne s1, zero, validaInsercoesReturn3    # if ( board[row + insertions][col] != 0 )
      j validaInsercoesReturn3Fim
    validaInsercoes3Angulo:
      mul t5, a6, t2
      add a0, a7, t3
      add t5, t5, a0
      mul t5, t5, t4
      add a0, zero, a2
      add a0, a0, t5                          # board[][] + (( row * board_size ) + (col + insertions ) * 4
      lw s1, (a0)                             # origem + deslocamento

      bne s1, zero, validaInsercoesReturn3    # if ( board[row][col + insertions] != 0 )     
      j validaInsercoesReturn3Fim
    validaInsercoesReturn3:
      addi t4, zero, 3
      sw t4, (s11)                            # *error = 3
      ret
    validaInsercoesReturn3Fim:
      addi t3, t3, 1                          # insertions++
      j validaInsercoes3TesteWhile

    validaInsercoes3WhileFim:
      add t4, zero, zero
      sw t4, (s11)                            # *error = 0
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
      lb, s4, (s2)                            # s4 = &current
      lb, s5, (s3)                            # s4 = &next

      lw t4, (s11)
      bne t4, zero, converterInteiroFim       # if ( error != 0 )
      lb, t2, espaco
      beq s5, t2, converterInteiroIf          # if ( next == ' ' )
      lb, t3, barra_n
      beq s5, t3, converterInteiroIf          # if ( next == '\n' )
      lb, t4, barra_0
      beq s5, t4, converterInteiroIf          # if ( next == '\0' )
      j converterInteiroIfFim
    converterInteiroIf:
      addi t5, zero, 48
      sub t4, s4, t5
      add a0, zero, t4                        # a0 = current - 48
      ret
    converterInteiroIfFim:
      addi t4, zero, 4
      sw t4, (s11)                            # *error = 4
    converterInteiroFim:
      add a0, zero, zero                      # a0 = 0
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
      add t6, zero, ra                        # Salva endereço de retorno atual
      addi t0, zero, 1                        # current = 1
      sw zero, (s11)                          # *error = 0
      sw zero, (s9)                           # *quantity_ships = 0

      la s2, navios
      addi s3, s2, 1
      jal converterInteiro                    # converterInteiro(s11, s2, s3)
      add t1, zero, a0                        # quantity -> t1 = a0

      lw t2, (s11)
      bne t2, zero, insereEmbarcacoesError    # if (error != 0)
    insereEmbarcacoesWhile:
      bge t1, t0, insereEmbarcacoesCorpoWhile # if ( quantity >= current )
      j insereEmbarcacoesFimWhile
    insereEmbarcacoesCorpoWhile:

      la s2, navios                           # s2 = navios[0]
      addi t2, zero, 1
      sub s10, t0, t2
      addi t2, zero, 8
      mul s10, s10, t2
      addi t2, zero, 2
      add s10, s10, t2
      add s2, s2, s10                         # s2 = navios[ 0 + ( (current - 1) * 8 ) + 2]
      addi s3, s2, 1                          # s3 = navios[ (0 + ( (current - 1) * 8 ) + 2) + 1]
      jal converterInteiro                    # converterInteiro(s11, s2, s3)
      add a4, zero, a0                        # angle = a4

      addi s2, s2, 2                          # s2  = navios[s2 + 2]
      addi s3, s2, 1                          # s3  = navios[s2 + 1]
      jal converterInteiro                    # converterInteiro(s11, s2, s3)
      add a5, zero, a0                        # length = a5

      addi s2, s2, 2                          # s2  = navios[s2 + 2]
      addi s3, s2, 1                          # s3  = navios[s2 + 1]
      jal converterInteiro                    # converterInteiro(s11, s2, s3)
      add a6, zero, a0                        # row = a6

      addi s2, s2, 2                          # s2  = navios[s2 + 2]
      addi s3, s2, 1                          # s3  = navios[s2 + 1]
      jal converterInteiro                    # converterInteiro(s11, s2, s3)
      add a7, zero, a0                        # col = a7
      
      lw t2, (s11)
      bne s11, zero, insereEmbarcacoesError   # if (error != 0)
      jal validaInsercoes                     # validaInsercoes(a2, a4, a5, a6, a7)

      lw t2, (s11)
      bne s11, zero, insereEmbarcacoesError   # if (error != 0)
      add a3, zero, t0
      jal inserirTabuleiro                    # inserirTabuleiro(a2, a4, a5, a6, a7, a3)
      lw t2, (s9)
      addi t2, t2, 1
      sw t2, (s9)                             # *quantity_ships++

      j insereEmbarcacoesErrorFim
    insereEmbarcacoesError:
      lw t2, (s11)
      li a7, 4                                
      addi t3, zero, 1
      beq t2, t3, insereEmbarcacoesError1     # if ( *erro == 1 )
      addi t3, zero, 4
      beq t2, t3, insereEmbarcacoesError1     # if ( *erro == 4 )
      addi t3, zero, 2
      beq t2, t3, insereEmbarcacoesError2     # if ( *erro == 2 )
      addi t3, zero, 3
      beq t2, t3, insereEmbarcacoesError3     # if ( *erro == 3 )
      j insereEmbarcacoesFimError
    insereEmbarcacoesError1:
      la a0, erro_1
      ecall                                   # Imprime string - Erro 1
    insereEmbarcacoesError2:
      la a0, erro_2
      ecall                                   # Imprime string - Erro 2
    insereEmbarcacoesError3:
      la a0, erro_3
      ecall                                   # Imprime string - Erro 3
    insereEmbarcacoesFimError:
      j insereEmbarcacoesFimWhile
    insereEmbarcacoesErrorFim:
      addi t0, t0, 1                          # current++
      j insereEmbarcacoesWhile
    insereEmbarcacoesFimWhile:
      add ra, zero, t6                        # Ajusta retorno
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
      add t6, zero, ra                        # Salva endereço de retorno atual
      li a7, 4
      la a0, jogada_linha
      ecall                                   # Imprime string
      li a7, 5
      ecall                                   # Lê inteiro
      add t0, zero, a0                        # t0 = a0
      li a7, 4
      la a0, jogada_coluna
      ecall                                   # Imprime string
      li a7, 5
      ecall                                   # Lê inteiro
      add t1, zero, a0                        # t1 = a0
      lw t2, board_size
      add a6, zero, zero

      add t3, zero, a2
      addi t4, zero, 4
      mul t5, t0, t2
      add t5, t5, t1
      mul t5, t5, t4
      add t3, t3, t5                          # board[][] + (( row * board_size ) + col) * 4
      lw t4, (t3)                             # origem + deslocamento

    novaJogadaIf:
      addi t5, zero, 0
      blt t4, t5, novaJogadaElse              # if ( board[row][col] < 0 )
      addi t5, zero, 11
      bge t4, t5, novaJogadaElse              # if ( board[row][col] >= 11 )
    novaJogadaCorpoIf:
    novaJogadaIf2:
      beq t4, zero, novaJogadaElse2           # if ( board[row][col] == 0 )
    novaJogadaCorpoIf2:
      add a6, zero, t4
      addi t5, t4, 10
      sw t5, (t3)                             # origem + deslocamento = *( origem + deslocamento ) + 10
      lw t5, (a4)
      addi t5, t5, 1
      sw t5, (a4)                             # *hits++
      j novaJogadaFimIf2
    novaJogadaElse2:
      addi t5, zero, -1
      sw t5, (t3)                             # origem + deslocamento = -1
    novaJogadaFimIf2:
      j novaJogadaFimIf
    novaJogadaElse:
      li a7, 4
      la a0, jogada_feita
      ecall                                   # Imprime string
    novaJogadaFimIf:
      jal imprimeTiros                        # imprimeTiros(a2)

      lw t5, (a3)
      addi t5, t5, 1
      sw t5, (a3)                             # *shots++
      jal confereBarcos                       # confereBarcos(a2, a6, a5)
      add ra, zero, t6                        # Ajusta retorno
      ret

  ########## novaJogada ##########

  ########## menu ##########
    # Parametros
      # -
    # Retorno
      # a0 - int
    menu:
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      la a0, menu_info
      ecall                                   # Imprime string
      la a0, menu_0
      ecall                                   # Imprime string
      la a0, menu_1
      ecall                                   # Imprime string
      la a0, menu_2
      ecall                                   # Imprime string
      la a0, menu_3
      ecall                                   # Imprime string
      li a7, 5
      ecall                                   # Lê inteiro
      add t0, zero, a0                        # t0 = a0
      li a7, 4
      la a0, barra_n
      ecall                                   # Imprime string
      add a0, zero, t0                        # a0 = t0

      ret
  ########## menu ##########

  end:
    nop