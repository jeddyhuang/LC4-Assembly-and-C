    .CODE
    .FALIGN
gcd
    ADD R6 R6 #-3
    STR R7 R6 #1
    STR R5 R6 #0
    ADD R5 R6 #0
    LDR R3 R5 #4
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #0
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    CMP R1 R2
    BRz eq_0
    CONST R0 #0
    STR R0 R6 #-1
    ADD R6 R6 #-1
    JMP END_eq_0
eq_0
    CONST R0 #1
    STR R0 R6 #-1
    ADD R6 R6 #-1
END_eq_0
IF_gcd0
    LDR R1 R6 #0
    ADD R6 R6 #1
    CMPI R1 #0
    BRnz ELSE_gcd0
    LDR R3 R5 #3
    STR R3 R6 #-1
    ADD R6 R6 #-1
    BRnzp ENDIF_gcd0
ELSE_gcd0
    LDR R3 R5 #4
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R3 R5 #3
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    MOD R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    LDR R3 R5 #4
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR gcd
    ADD R6 R6 #-1
ENDIF_gcd0
    LDR R7 R6 #0
    STR R7 R5 #2
    ADD R6 R5 #0
    LDR R5 R6 #0
    LDR R7 R6 #1
    ADD R6 R6 #3
    JMPR R7
    .CODE
    .FALIGN
main
    ADD R6 R6 #-3
    STR R7 R6 #1
    STR R5 R6 #0
    ADD R5 R6 #0
    CONST R3 #206
    HICONST R3 #1
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #47
    HICONST R3 #4
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR gcd
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
