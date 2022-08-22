;;;;;;;;;;;;;;;;;;;;;;;;;;;;memset;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		.CODE
		.FALIGN
memset
	;; prologue
	STR R7, R6, #-2	;; save return address
	STR R5, R6, #-3	;; save base pointer
	ADD R6, R6, #-3
	ADD R5, R6, #0
	ADD R6, R6, #-1	;; allocate stack space for local variables
	;; function body
	CONST R7, #0
	STR R7, R5, #-1
	JMP L5_new
L2_new
	LDR R7, R5, #3
	LDR R3, R5, #5
	STR R3, R7, #0
L3_new
	LDR R7, R5, #-1
	ADD R7, R7, #1
	STR R7, R5, #-1
	LDR R7, R5, #3
	ADD R7, R7, #1
	STR R7, R5, #3
L5_new
	LDR R7, R5, #-1
	LDR R3, R5, #4
	CMP R7, R3
	BRn L2_new
L1_new
	;; epilogue
	ADD R6, R5, #0	;; pop locals off stack
	ADD R6, R6, #3	;; free space for return address, base pointer, and return value
	STR R7, R6, #-1	;; store return value
	LDR R5, R6, #-3	;; restore base pointer
	LDR R7, R6, #-2	;; restore return address
	RET

