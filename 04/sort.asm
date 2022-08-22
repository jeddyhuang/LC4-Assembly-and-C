    .CODE
    .ADDR 0x0000

INIT
    ADD R2 R0 #0
    ADD R3 R1 #-1
    CONST R4 #1

MAIN
    LDR R5 R2 #0
    LDR R6 R2 #1
    CMP R5 R6
    BRp SWAP
RESUME
    ADD R2 R2 #1
    ADD R3 R3 #-1
    BRnz RESET
    JMP MAIN

RESET
    CMPI R4 #0
    BRp END
    JMP INIT

SWAP
	STR R5 R2 #1
    STR R6 R2 #0
    CONST R4 #0
    JMP RESUME

END