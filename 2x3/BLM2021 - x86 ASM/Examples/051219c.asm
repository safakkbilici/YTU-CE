		EXTRN SAY:FAR
myss	SEGMENT PARA STACK 's'
		DB 40 DUP(?)
myss	ENDS
myds	SEGMENT PARA 'd'
dizi	DW 12, 12, 12, 12, 12, 12, 13, 14, 15, 16, 17
n		DW 11
aranan	DB 12
sonuc	DW 0
myds	ENDS
mycs	SEGMENT BYTE PUBLIC 'kod'
		ASSUME CS:mycs, DS:myds, SS:myss
MAIN	PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, myds
		MOV DS, AX
		XOR AX, AX
		MOV AL, aranan
		PUSH AX
		PUSH n
		LEA AX, dizi
		PUSH AX
		CALL SAY
		MOV sonuc, AX
		RETF
MAIN 	ENDP
mycs	ENDS
		END MAIN