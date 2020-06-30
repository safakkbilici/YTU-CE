		PUBLIC SAY
mycs	SEGMENT BYTE PUBLIC 'kd'
		ASSUME CS:mycs
SAY		PROC FAR
		PUSH CX
		PUSH DI
		PUSH BX
		MOV BP, SP
		MOV BX, [BP+14]
		MOV CX, [BP+12]
		MOV DI, [BP+10]
		XOR AX, AX
L1:		CMP BX, [DI]
		JNE atla
		INC AX
atla:	ADD DI, 2
		LOOP L1
		POP BX
		POP DI
		POP CX
		RETF 6
SAY 	ENDP
mycs	ENDS
		END