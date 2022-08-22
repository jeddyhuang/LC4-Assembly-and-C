;;; Code for drawing a horizontal line on the screen
;;; Register utilization R0 = i, R1 = pixel_address, R4 = color

;;; Video memory

OS_VIDEO_MEM 	  .UCONST xC000
OS_VIDEO_NUM_COLS .UCONST #128
OS_VIDEO_NUM_ROWS .UCONST #124		

ROW_OFFSET 	.UCONST #30
COL_OFFSET 	.UCONST #20

RED 		.UCONST x7C00
GREEN		.UCONST x03E0
BLUE		.UCONST x001F

	.CODE			; This is a code segment
	.ADDR  0x0000		; Start filling in instructions at address 0x00

;;; DRAW LINE

;;;  Setup R1 to point to first pixel on the line
	LC R1, ROW_OFFSET
	SLL R1, R1, #7
	LC R3, COL_OFFSET
	ADD R1, R1, R3
	LC R3, OS_VIDEO_MEM
	ADD R1, R1, R3

	LC R4, GREEN		; Load the color into R4
	
	CONST R0, #0		; i = 0
	JMP TEST

LOOP	STR R4, R1, 0		; write the pixel with the color
	ADD R0, R0, #1		; increment i
	ADD R1, R1, #1		; increment the pixel address

TEST	CMPI R0, #60		; if (i < 60) loop
	BRn LOOP
	
END 	NOP
