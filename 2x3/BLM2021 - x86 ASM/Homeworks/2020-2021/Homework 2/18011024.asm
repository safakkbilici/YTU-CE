myds		SEGMENT PARA 'veri'
    n			DW 10
    RES         DB 10 DUP ('$')	
myds		ENDS

myss		SEGMENT PARA STACK 'yigin'
			DW 500 DUP(?)
myss		ENDS

mycs2       SEGMENT PARA 'kod2'
            ASSUME CS:mycs2 , DS:myds , SS:myss
            
CONWAY		PROC FAR 
			PUSH BP
			PUSH BX
			PUSH DI
			PUSH SI
			
			
			MOV BP, SP			;SP BP'YE ATAMA
			MOV DI, [BP+12]			;YIĞIN ÜZERİNDEN GİRİŞ PARAMETRESİNE ERİŞME
			MOV AX, DI				
			
			CMP AX,0			;MEVCUT PARAMETRENİN 0,1,2 OLMA DURUMUNU KONTROL
			JE SIFIR
			CMP AX,1
			JE BIR
			CMP AX,2
			JE BIR				
			
			DEC AX				;GİRİŞ DEĞERİ 3 VE ÜZERİ OLUNCA RECURSIVE 
			PUSH AX				;OLARAK İSTENEN DEĞERİ HESAPLAMA
			CALL CONWAY
			CALL CONWAY
			POP SI
			MOV CX, DI
			DEC CX
			PUSH CX
			CALL CONWAY
			POP CX
			MOV DX,DI
			SUB DX,CX
			PUSH DX
			CALL CONWAY
			POP DX
			ADD SI,DX
			MOV [BP+12], SI			;ELDE EDİLEN DEĞERİ YIĞINA ATAMA
									
			JMP DONUS
			
SIFIR:		MOV  AX, 0
			MOV  [BP+12], AX					
			JMP DONUS
BIR:		MOV  AX, 1		
			MOV  [BP+12], AX
			
DONUS:		POP SI
			POP DI
			POP BX
			POP BP
			RETF 
CONWAY		ENDP   
mycs2       ENDS    


mycs		SEGMENT PARA 'kod'
			ASSUME CS:mycs, SS:myss, DS:myds 

PRINTINT	PROC NEAR
			
			MOV BP, SP
			MOV AX, [BP+2]			;CONWAY YORDAMINDAN ELDE EDİLEN 
							;DEĞERE YIĞIN ÜZERİNDEN ERİŞME
			
			LEA SI, RES				
			MOV CX, 0
			MOV BX, 10

L2: 		MOV DX,0
			DIV BX
			ADD DL,30H
			PUSH DX
			INC CX
			CMP AX,9
			JG L2
     
			ADD AL,30H
			MOV [SI],AL
     
L3: 		POP AX
			INC SI
			MOV [SI],AL
			LOOP L3			
			
			LEA DX,RES
			MOV AH,9
			INT 21H 
            
			MOV AH,4CH
			INT 21H 
			
			RET 2
PRINTINT	ENDP


MAIN		PROC FAR
            PUSH DS
			XOR AX, AX
			PUSH AX
			MOV AX, myds
			MOV DS, AX			
			
			
			PUSH n 
			CALL CONWAY
			CALL PRINTINT
			
			
			RETF
MAIN		ENDP
mycs		ENDS
			END MAIN
