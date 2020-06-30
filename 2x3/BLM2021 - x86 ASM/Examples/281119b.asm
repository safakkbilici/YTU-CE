		EXTRN TOPLAMA:FAR
myss	SEGMENT PARA STACK 'yigin'
		DW 20 DUP(?)
myss	ENDS
myds	SEGMENT PARA 'veri'
sayi1	DB 17
sayi2	DB 29
sonuc	DW ?
myds	ENDS
mycs	SEGMENT PARA 'kod'
		ASSUME CS:mycs, DS:myds, SS:myss
ILK		PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, myds
		MOV DS, AX
		MOV BL, sayi1
		MOV BH, sayi2
		CALL TOPLAMA
		MOV sonuc, AX	
		RETF
ILK		ENDP
mycs	ENDS
		END ILK