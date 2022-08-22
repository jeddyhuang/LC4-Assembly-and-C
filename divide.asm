;; Division program
;; C = A / B
;; R2 = A, R3 = B, R4 = C

	.CODE		; This is a code segment
	.ADDR  0x0000	; Start filling in instructions at address 0x00

	CONST R4, #0    ; Initialize C to 0

LOOP

	ADD R4, R4, #1		; C = C + 1
	SUB R2, R2, R3		; A = A - B
	BRzp LOOP		; while (A >= 0) LOOP

	ADD R4, R4, #-1		; C = C - 1

INFINITE_LOOP
	BRnzp INFINITE_LOOP

END
