		EXTRN ALAN_BUL:FAR
datas	SEGMENT PARA 'veri'
kenar	DW 6, 8, 5, 9, 4, 8, 2, 2, 3
n		DW 3
enbykA	DW 0
datas	ENDS
stacks	SEGMENT PARA STACK 'yigin'
		DW 20 DUP(?)
stacks	ENDS
codes	SEGMENT PARA 'kod'
		ASSUME CS:codes, DS:datas, SS:stacks
ANA		PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, datas
		MOV DS, AX
		
		MOV CX, n
		LEA SI, kenar
L1:		PUSH [SI]
		PUSH [SI+2]
		PUSH [SI+4]
		CALL ALAN_BUL
		CMP AX, enbykA
		JBE L2
		MOV enbykA, AX
L2:		ADD SI, 6
		LOOP L1	
		
		RETF
ANA		ENDP
codes	ENDS
		END ANA