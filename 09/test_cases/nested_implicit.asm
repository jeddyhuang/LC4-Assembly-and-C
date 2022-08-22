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
    CONST R3 #6
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #10
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #244
    HICONST R3 #1
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    CMP R1 R2
    BRzp ge_0
    CONST R0 #0
    STR R0 R6 #-1
    ADD R6 R6 #-1
    JMP END_ge_0
ge_0
    CONST R0 #1
    STR R0 R6 #-1
    ADD R6 R6 #-1
END_ge_0
IF_main0
    LDR R1 R6 #0
    ADD R6 R6 #1
    CMPI R1 #0
    BRnz ELSE_main0
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    CMP R1 R2
    BRzp ge_1
    CONST R0 #0
    STR R0 R6 #-1
    ADD R6 R6 #-1
    JMP END_ge_1
ge_1
    CONST R0 #1
    STR R0 R6 #-1
    ADD R6 R6 #-1
END_ge_1
IF_main1
    LDR R1 R6 #0
    ADD R6 R6 #1
    CMPI R1 #0
    BRnz ELSE_main1
    CONST R3 #0
    HICONST R3 #124
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #100
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #100
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #14
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR lc4_draw_rect
    ADD R6 R6 #-1
ELSE_main1
ENDIF_main1
    BRnzp ENDIF_main0
ELSE_main0
    CONST R3 #0
    HICONST R3 #51
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #100
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    STR R1 R6 #-1
    ADD R6 R6 #-1
    STR R2 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #100
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #14
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR lc4_draw_rect
    ADD R6 R6 #-1
ENDIF_main0
    LDR R7 R6 #0
    STR R7 R5 #2
    ADD R6 R5 #0
    LDR R5 R6 #0
    LDR R7 R6 #1
    ADD R6 R6 #3
    JMPR R7
