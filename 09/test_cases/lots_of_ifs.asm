    .CODE
    .FALIGN
testIfs
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
    CONST R3 #10
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
IF_testIfs0
    LDR R1 R6 #0
    ADD R6 R6 #1
    CMPI R1 #0
    BRnz ELSE_testIfs0
    LDR R1 R6 #0
    STR R1 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #5
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    CMP R1 R2
    BRp gt_1
    CONST R0 #0
    STR R0 R6 #-1
    ADD R6 R6 #-1
    JMP END_gt_1
gt_1
    CONST R0 #1
    STR R0 R6 #-1
    ADD R6 R6 #-1
END_gt_1
IF_testIfs1
    LDR R1 R6 #0
    ADD R6 R6 #1
    CMPI R1 #0
    BRnz ELSE_testIfs1
    CONST R3 #11
    STR R3 R6 #-1
    ADD R6 R6 #-1
    BRnzp ENDIF_testIfs1
ELSE_testIfs1
    CONST R3 #12
    STR R3 R6 #-1
    ADD R6 R6 #-1
ENDIF_testIfs1
    BRnzp ENDIF_testIfs0
ELSE_testIfs0
    LDR R1 R6 #0
    STR R1 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    CMP R1 R2
    BRp gt_2
    CONST R0 #0
    STR R0 R6 #-1
    ADD R6 R6 #-1
    JMP END_gt_2
gt_2
    CONST R0 #1
    STR R0 R6 #-1
    ADD R6 R6 #-1
END_gt_2
IF_testIfs2
    LDR R1 R6 #0
    ADD R6 R6 #1
    CMPI R1 #0
    BRnz ELSE_testIfs2
    CONST R3 #13
    STR R3 R6 #-1
    ADD R6 R6 #-1
    BRnzp ENDIF_testIfs2
ELSE_testIfs2
    CONST R3 #14
    STR R3 R6 #-1
    ADD R6 R6 #-1
ENDIF_testIfs2
ENDIF_testIfs0
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
    CONST R3 #8
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR testIfs
    ADD R6 R6 #-1
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    CONST R3 #4
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR testIfs
    ADD R6 R6 #-1
    JSR printnum
    ADD R6 R6 #-1
    JSR endl
    ADD R6 R6 #-1
    CONST R3 #45
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR testIfs
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
