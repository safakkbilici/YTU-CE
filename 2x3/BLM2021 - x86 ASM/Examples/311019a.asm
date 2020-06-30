myds 		SEGMENT PARA 'veri'
tek_top		DD 0
cift_top	DD 0
tek_say 	DW 0
cift_say	DW 0
n			DW 10
cift_ort	DW ?
tek_ort		DW ?
dizi		DW 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
myds		ENDS
myss		SEGMENT PARA STACK 'yigin'
			DW 20 DUP(?)
myss		ENDS
mycs		SEGMENT PARA 'kod'
			ASSUME DS:myds, SS:myss, CS:mycs
ANA			PROC FAR
			PUSH DS
			XOR AX, AX
			PUSH AX
			MOV AX, myds
			MOV DS, AX
			
			MOV CX, n
			LEA SI, dizi
L1:			MOV AX, [SI]
			TEST AX, 0001h
			JZ cift_label
			ADD WORD PTR [tek_top], AX
			ADC WORD PTR [tek_top+2], 0
			INC tek_say
			JMP artir
cift_label:	ADD WORD PTR [cift_top], AX
			ADC WORD PTR [cift_top+2], 0
			INC cift_say
artir:		ADD SI, 2
			LOOP L1
			
			MOV DX, WORD PTR [cift_top+2]
			MOV AX, WORD PTR [cift_top]
			DIV cift_say
			MOV cift_ort, AX
			MOV DX, WORD PTR [tek_top+2]
			MOV AX, WORD PTR [tek_top]
			DIV tek_say
			MOV tek_ort, AX
			RETF
ANA			ENDP
mycs		ENDS
			END ANA