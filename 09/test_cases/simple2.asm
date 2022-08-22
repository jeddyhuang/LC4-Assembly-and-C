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
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    CMP R1 R2
    BRp gt_0
    CONST R0 #0
    STR R0 R6 #-1
    ADD R6 R6 #-1
    JMP END_gt_0
gt_0
    CONST R0 #1
    STR R0 R6 #-1
    ADD R6 R6 #-1
END_gt_0
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    CONST R3 #88
    HICONST R3 #27
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #190
    HICONST R3 #252
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    CMP R1 R2
    BRn lt_1
    CONST R0 #0
    STR R0 R6 #-1
    ADD R6 R6 #-1
    JMP END_lt_1
lt_1
    CONST R0 #1
    STR R0 R6 #-1
    ADD R6 R6 #-1
END_lt_1
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
