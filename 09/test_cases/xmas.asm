    .CODE
    .FALIGN
main
    ADD R6 R6 #-3
    STR R7 R6 #1
    STR R5 R6 #0
    ADD R5 R6 #0
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
    CONST R3 #0
    HICONST R3 #51
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #80
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #80
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #24
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR lc4_draw_rect
    ADD R6 R6 #-1
    CONST R3 #0
    HICONST R3 #124
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #60
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #60
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #34
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR lc4_draw_rect
    ADD R6 R6 #-1
    CONST R3 #0
    HICONST R3 #51
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #40
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #40
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #44
    STR R3 R6 #-1
    ADD R6 R6 #-1
    JSR lc4_draw_rect
    ADD R6 R6 #-1
    CONST R3 #240
    HICONST R3 #127
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #20
    STR R3 R6 #-1
    ADD R6 R6 #-1
    CONST R3 #54
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
