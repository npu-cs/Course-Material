TITLE   Encode and decode
PAGE    60,132
		.MODEL SMALL	
		.STACK 64
		;--------------------------	
		.DATA	
        DIC_ENCODE DB ' qwertyuiopasdfghjklzxcvbnm$'
        STR_SOR     DB 24,'t morrow morning in nwpu','$'
        STR_DEST    DB 0 50 DUP(0)
        STR_DEST2   DB 0, 50 DUP(0)
        STR_NEWLINE	DB 0DH,0AH,'$' ;define 'next line' 
        ;--------------------------
		.CODE	
MAIN	PROC FAR	;this is the program entry point
		MOV AX, @DATA	;load the data segment address
		MOV DS, AX	;assign value to data segment register
		MOV	ES, AX
		CLD
		;
		MOV	BX, OFFSET DIC_ENCODE;  point BX to dictionary
		MOV SI, OFFSET STR_SOR;
		MOV	DI, OFFSET STR_DEST;
		;print the source string  
		MOV DX, SI
		INC DX
		CALL DISPLAY
		;create a new line 
		MOV DX, OFFSET STR_NEWLINE
		CALL DISPLAY
		;encode the string 
		CALL ENCODE;     
		;print the destnation string
		MOV DX, OFFSET STR_DEST
		INC DX
		CALL DISPLAY
		;create a new line 
		MOV DX, OFFSET STR_NEWLINE
		CALL DISPLAY       
		;print the dictionary
		MOV DX, OFFSET DIC_ENCODE;
		CALL DISPLAY
		MOV DX, OFFSET STR_NEWLINE
		CALL DISPLAY 
		;decode the string     
		MOV SI, OFFSET STR_DEST;    ;use SI address the encoded string
		MOV	DI, OFFSET STR_DEST2;   ;use BX address the decoded string
		MOV BX, OFFSET DIC_ENCODE;    ;use DI address the dictionary 
		CALL DECODE; 
		;print the decoded string
        MOV DX, OFFSET STR_DEST2;
        INC DX
        CALL DISPLAY
		;; return to dos	
		MOV AH, 4CH	
		INT 21H	
MAIN	ENDP	        

;THIS SUBROUTINE DISPLAYS A STRING ON THE SCREEN    
;It requires that DX points to the string for output
DISPLAY PROC    
        PUSH AX
		MOV	AH, 09			;DISPLAY STRING FUNCTION
		;MOV	DX, OFFSET DATAREA	;DX POINTS TO BUFFER
		INT	21H            
		POP AX
		RET
DISPLAY	ENDP  
        ;                          
;This sub-routine encode the source string
;it requires that SI and DI to be initialized   
; and BX points to the dictionary
ENCODE PROC
        PUSH CX
        PUSH AX
        ;step1: load the length of the string
        XOR CH,CH
        MOV CL, [SI]
        MOV [DI], CX
        INC SI      ;point to the first char
        INC DI
        MOV AL, '$'   
        PUSH BX   
        MOV BX, DI
        ADD BX, CX
        MOV [BX], AL ;add a '$' at the end of the string
        POP BX
        ;step2: convert each char within source
TRANS: MOV AL, [SI]    ;load a char from source string
        SUB AL, 60H     ;  
        JNC DOTRANS
        MOV AL, 00H
DOTRANS:XLAT
        MOV [DI], AL
        INC SI
        INC DI
        LOOP TRANS
        POP AX
        POP CX 
        RET
ENCODE ENDP 
;
;This sub-routing decodes the dest string by SCASB  
;it requires that SI and DI to be initialized   
; and BX points to the dictionary
DECODE PROC
        ;         
        PUSH CX
        PUSH AX
        ;step1: load the length of the string
        XOR AH,AH
        MOV AH, [SI]
        MOV [DI], AH
        INC SI      ;point to the first char
        INC DI
        MOV AL, '$'   
        PUSH BX   
        MOV BX, DI
        ADD BX, CX
        MOV [BX], AL ;add a '$' at the end of the string
        POP BX
        ;step2, lookup dic for each char
        PUSH DI
        MOV DI, BX
        POP BX  ; now, DI points to dic, and BX points to STR_DEST2
REPEAT: MOV AL, [SI]
        MOV CX, 27  ;there are 26 chars and a space within dic 
        PUSH DI  
        REPNE SCASB  ;lookup the dictionary 扫描DI指向的字符串，遇到字节等于AL或者CX计数为0，则结束扫描
        POP DI
        PUSH AX     ;store AX
        MOV AX, 27
        SUB AX, CX   
        SUB AX, 1   
        JZ ISSPACE
        ADD AX, 40H ;convert it into ASCII by adds up 40H+20H
ISSPACE:ADD AX, 20H; force to be space
        MOV [BX], AL
        INC BX 
        INC SI
        POP AX      ;restor AX
        DEC AH      ;AH为字符串长度
        JNZ REPEAT 
        POP AX
        POP CX
        RET
DECODE ENDP
;
		END MAIN	;this is the program exit point
