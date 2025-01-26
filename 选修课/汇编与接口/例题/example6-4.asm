;Example 6-4: input a word from keyboard, then convert into ASCII string and display 
		.MODEL SMALL	
		.STACK 64	
		.DATA	
		;	
DATA1	DB 96
DATA2	DB 70
HINT1	DB CR, LF, 'addition result in unsigned formal is : ','$'
HINT2	DB CR, LF, 'addition result in signed formal is : ','$'
BUFINPUT	DW 00H			;buffer to hold source number
BUFUBCD		DB 00, 4 DUP(00H);buffer to hold output unpacked BCD
BUFASCII	DB 00, 8 DUP(00H);buffer to hold ASCII string for display, starting with length

BUFUBCD2		DB 00, 4 DUP(00H);buffer to hold output unpacked BCD
BUFASCII2	DB 00, 8 DUP(00H);buffer to hold ASCII string for display, starting with length
CR		EQU 0DH ; ASCII code for carriage return
LF		EQU 0AH	; ASCII code for line feed
		.CODE	
MAIN	PROC FAR	;this is the program entry point
		MOV AX, @DATA	;load the data segment address
		MOV DS, AX	;assign value to data segment register
		; program segment of example 6-4
		MOV AL, DATA1
		MOV BL, DATA2
		ADD AL, BL
		MOV BYTE PTR BUFINPUT, AL		
		; Display result
		MOV DX, OFFSET HINT1
		CALL DisplayString
		CALL HexToASCII
		CALL DisplayInverted
		; GET 2's complement of AL and display
		MOV DX, OFFSET HINT2
		CALL DisplayString		
		CALL SignedHexToASCII
		CALL DisplayInverted
		;; return to dos	
		MOV AH, 4CH	
		INT 21H	
MAIN	ENDP	
 
;;====================================
;; sub procedure convert a HEX WORD into unpacked BCD ==> ASCII 
;; it takes two buffer in DATA segment to save convert result
;; one for BCD and one for 
HexToASCII PROC NEAR
		MOV CL, 00H
		MOV DI, OFFSET BUFUBCD
		MOV AX, BUFINPUT
		MOV DX, 00H
		MOV BX, 0AH
DIVBYTEN:	
		INC DI      
		DIV BX
		CMP AX, 00H
		JZ DIVOVER
		MOV [DI], DL
		MOV DX, 00H	;CLEAR DX FOR NEXT ROUND OF ITERATION
		INC CL
		JMP DIVBYTEN
DIVOVER:
		MOV [DI], DL
		INC CL
		MOV DI, OFFSET BUFUBCD
		MOV [DI], CL
		; CONVERT INTO ASCII
		MOV SI, OFFSET BUFUBCD
		MOV DI, OFFSET BUFASCII
		MOV CX, 00
		MOV CL, [SI]
		MOV [DI],CL
		INC SI
		INC DI
LOOPHERE:
		MOV AL, [SI]
		OR AL, 30H
		MOV [DI],AL   
		INC SI
		INC DI
		LOOP LOOPHERE
		RET
HexToASCII ENDP

;;====================================
;; sub procedure convert a signed HEX WORD into unpacked BCD ==> ASCII 
;; it takes two buffer in DATA segment to save convert result
;; one for BCD and one for 
SignedHexToASCII PROC NEAR
		MOV CL, 00H
		MOV DI, OFFSET BUFUBCD
		MOV AX, BUFINPUT
		push ax
		NOT AL
		ADD AL, 1		
		MOV DX, 00H
		MOV BX, 0AH
DIVBYTEN2:	
		INC DI      
		DIV BX
		CMP AX, 00H
		JZ DIVOVER2
		MOV [DI], DL
		MOV DX, 00H	;CLEAR DX FOR NEXT ROUND OF ITERATION
		INC CL
		JMP DIVBYTEN2
DIVOVER2:
		MOV [DI], DL
		INC CL
		MOV DI, OFFSET BUFUBCD
		MOV [DI], CL
		; CONVERT INTO ASCII
		MOV SI, OFFSET BUFUBCD
		MOV DI, OFFSET BUFASCII
		MOV CX, 00
		MOV CL, [SI]
		inc cl 
		MOV [DI],CL
		INC SI
		INC DI
		dec cl
LOOPHERE2:
		MOV AL, [SI]
		OR AL, 30H
		MOV [DI],AL   
		INC SI
		INC DI
		LOOP LOOPHERE2
		; append the sign flag
		pop ax
		cmp al, 127
		ja negtive
		mov [DI], '+'
		jmp return
negtive:
		mov [DI], '-'
return:
		RET
SignedHexToASCII ENDP

;;====================================
;; sub procedure that display a string from tail to head
DisplayInverted PROC NEAR
		MOV BX, OFFSET BUFASCII
		MOV CX, 00H
		MOV CL, [BX]
		ADD BX, CX
DISPLAY:
		MOV AH, 02H
		MOV DL, [BX] 
		INT 21H     
		DEC BX
		LOOP DISPLAY
		RET
DisplayInverted endp

;;====================================
;THIS SUBROUTINE DISPLAYS A STRING ON THE SCREEN
;Param: DX points to buffer
;Register: AH, DX
DisplayString PROC NEAR
		PUSH AX
		MOV	AH, 09			;DISPLAY STRING FUNCTION
		;MOV	DX, OFFSET DATAREA	;DX POINTS TO BUFFER
		INT	21H
		POP AX
		RET
DisplayString	ENDP
		END MAIN	;this is the program exit point
      
      