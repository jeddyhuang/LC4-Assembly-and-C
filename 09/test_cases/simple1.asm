    .CODE
    .FALIGN
main
    ADD R6 R6 #-3
    STR R7 R6 #1
    STR R5 R6 #0
    ADD R5 R6 #0
    CONST R3 #5
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #3
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #2
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    MUL R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    ADD R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    CONST R3 #3
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #4
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #5
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    LDR R3 R6 #0
    ADD R6 R6 #1
    STR R2 R6 #-1
    ADD R6 R6 #-1
    STR R1 R6 #-1
    ADD R6 R6 #-1
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    MUL R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    ADD R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    LDR R7 R6 #0
    STR R7 R5 #2
    ADD R6 R5 #0
    LDR R5 R6 #0
    LDR R7 R6 #1
    ADD R6 R6 #3
    JMPR R7
