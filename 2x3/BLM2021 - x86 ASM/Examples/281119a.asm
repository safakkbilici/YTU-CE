myss	SEGMENT PARA STACK 'yigin'
		DW 20 DUP(?)
myss	ENDS
myds	SEGMENT PARA 'veri'
sayi	DB 2
ust		DW 10
sonuc 	DW ?
myds	ENDS
mycs	SEGMENT PARA 'kod'
		ASSUME CS:mycs, SS:myss, DS:myds
ANA		PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, myds
		MOV DS, AX
		XOR BH, BH
		MOV BL, sayi
		MOV CX, ust
		CALL USTAL
		MOV sonuc, AX
		RETF
ANA		ENDP
USTAL	PROC NEAR
		PUSH DX
		MOV AX, 1
L1:		MUL BX
		LOOP L1
		POP DX
		RET
USTAL	ENDP
mycs	ENDS
		END ANA