			PUBLIC ALAN_BUL
mycode		SEGMENT PARA 'kod'
			ASSUME CS:mycode
ALAN_BUL	PROC FAR
			
			PUSH BX
			PUSH CX
			PUSH DI
			PUSH BP
			PUSH DX
			MOV BP, SP
			
			XOR AX, AX
			ADD AX, [BP+18]
			ADD AX, [BP+16]
			ADD AX, [BP+14]
			SHR AX, 1
			MOV BX, AX
			SUB BX, [BP+14]
			MOV CX, AX
			SUB CX, [BP+16]
			MOV DI, AX
			SUB DI, [BP+18]
			MUL BX
			MUL CX
			MUL DI
			POP DX
			POP BP
			POP DI
			POP CX
			POP BX
			RETF 6
ALAN_BUL	ENDP
mycode		ENDS
			END