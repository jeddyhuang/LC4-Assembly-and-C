    .CODE
    .FALIGN
main
    ADD R6 R6 #-3
    STR R7 R6 #1
    STR R5 R6 #0
    ADD R5 R6 #0
    CONST R3 #0
    HICONST R3 #112
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #0
    HICONST R3 #12
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    OR R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #235
    HICONST R3 #255
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    NOT R1 R1
    STR R1 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #100
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #255
    HICONST R3 #255
    STR R3 R6 #-1
    ADD R6 R6 #-1
    LDR R1 R6 #0
    ADD R6 R6 #1
    LDR R2 R6 #0
    ADD R6 R6 #1
    AND R1 R1 R2
    STR R1 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #100
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #14
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR lc4_draw_rect
    ADD R6 R6 #-1
    LDR R7 R6 #0
    STR R7 R5 #2
    ADD R6 R5 #0
    LDR R5 R6 #0
    LDR R7 R6 #1
    ADD R6 R6 #3
    JMPR R7
