;;; USER Code
	.DATA
	.ADDR x4000
	
name_array
	.STRINGZ "Enter characters : Jerry Wang"
	
	.CODE
	.ADDR x0000
	LEA R0, name_array	; Initialize R0

	TRAP x08

END_PROGRAM
