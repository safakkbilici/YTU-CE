myds 		SEGMENT PARA 'data'
dizi		DB 5, 2, 3, 4, 5
n			DW 5
durum		DB ?
myds 		ENDS
myss		SEGMENT PARA STACK 'stack'
			DW 12 DUP(?)
myss		ENDS
mycs		SEGMENT PARA 'code'
			ASSUME CS:mycs, SS:myss, DS:myds
SIRALIMI	PROC FAR
			PUSH DS
			XOR AX, AX
			PUSH AX
			MOV AX, myds
			MOV DS, AX
			MOV BX, 0
			XOR SI, SI
			MOV CX, n
			DEC CX
donme_nok:	CMP BX, 0
			JNE L1
			CMP SI, CX
			JAE L1
			MOV AL, dizi[SI]
			CMP AL, dizi[SI+1]
			JLE L2
			MOV BX, 1
L2:			INC SI
			JMP donme_nok
L1:			CMP BX, 0
			JNE sirasiz
			MOV durum, 0
			JMP L3
sirasiz:	MOV durum, 1
L3:			RET
SIRALIMI	ENDP
mycs		ENDS
			END SIRALIMI
			