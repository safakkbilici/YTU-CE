myss	SEGMENT PARA 'kod'
		ORG 100H
		ASSUME DS:myss, CS:myss, SS:myss
kaynak	PROC NEAR
		XOR BX, BX
		MOV AL, k_esik
		MOV AH, b_esik
ilk:	CMP AL, dizi[BX]
		JA ic_don
		CMP AH, dizi[BX]
		JAE cikis
ic_don:	INC BX
		JMP ilk
cikis:	MOV sira, BL
		RET
kaynak	ENDP
dizi	DB 14, 11, 54, 62, 11, 3, 8, 63, 81, 16, 14
k_esik	DB 15
b_esik	DB 50
sira	DB ?
myss	ENDS
		END kaynak