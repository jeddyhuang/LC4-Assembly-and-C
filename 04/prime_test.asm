    .CODE
    .ADDR 0x0000

INIT
    CONST R1 #1
    CONST R2 #2
    MUL R3 R2 R2
    ADD R4 R0 #0

MAIN
    CMP R0 R3
    BRn END

LOOP
    SUB R4 R4 R2
    BRp LOOP
    BRn ITER
    CONST R1 #0
    JMP END

ITER
    ADD R2 R2 #1
    MUL R3 R2 R2
    ADD R4 R0 #0
    JMP MAIN

END