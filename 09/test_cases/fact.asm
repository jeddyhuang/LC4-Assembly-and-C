    .CODE
    .FALIGN
fact
    ADD R6 R6 #-3
    STR R7 R6 #1
    STR R5 R6 #0
    ADD R5 R6 #0
    LDR R3 R5 #3
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    STR R1 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #1
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
IF_fact0
    LDR R1 R6 #0
    ADD R6 R6 #1
    CMPI R1 #0
    BRnz ELSE_fact0
    CONST R3 #1
    STR R3 R6 #-1
    ADD R6 R6 #-1
    BRnzp ENDIF_fact0
ELSE_fact0
    LDR R1 R6 #0
    STR R1 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #1
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
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    SUB R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    JSR fact
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    STR R1 R6 #-1
    ADD R6 R6 #-1
    STR R2 R6 #-1
    ADD R6 R6 #-1
    ADD R6 R6 #1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    MUL R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
ENDIF_fact0
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
    CONST R3 #4
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR fact
    ADD R6 R6 #-1
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    CONST R3 #5
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR fact
    ADD R6 R6 #-1
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    CONST R3 #6
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR fact
    ADD R6 R6 #-1
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    CONST R3 #7
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR fact
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
