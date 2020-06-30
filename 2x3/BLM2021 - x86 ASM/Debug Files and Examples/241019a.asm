datasg 	SEGMENT PARA 'veri'
a		DB 12
b		DB 17
c		DB 12
tip 	DB ?
datasg 	ENDS
stacksg	SEGMENT PARA STACK 'yigin'
		DW 12 DUP(?)
stacksg	ENDS
codesg	SEGMENT PARA 'kod'
		ASSUME CS:codesg, SS:stacksg, DS:datasg
ANA		PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, datasg
		MOV DS, AX
		
		MOV AL, a
		MOV BL, b
		MOV CL, c
		
		CMP AL, BL
		JE L1
		CMP BL, CL
		JE L2
		CMP AL, CL
		JE L2
		MOV tip, 3
		JMP Son
L1:		CMP AL, CL
		JNE L2
		MOV tip, 1
		JMP Son
L2:		MOV tip, 2
Son:	RETF
ANA		ENDP
codesg	ENDS
		END ANA