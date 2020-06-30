		EXTRN SIRALIMI:FAR
		PUBLIC dizi, n
myss	SEGMENT PARA STACK 's'
		DW 20 DUP(?)
myss	ENDS
myds	SEGMENT PARA 'd'
dizi	DB 12, 14, 16, 18, 20, 22, 21
n		DW 7
sonuc	DB 0
myds	ENDS
mycs	SEGMENT PARA 'c'
		ASSUME CS:mycs, DS:myds, SS:myss
ANA		PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, myds
		MOV DS, AX
		CALL SIRALIMI
		CMP AL, 0
		JE sirali
		MOV sonuc, 1
sirali:	RETF
ANA		ENDP
mycs	ENDS
		END ANA