[BITS 16];
[ORG 0X7C00];
MOV SI,string;
CALL PrintString;
JMP $;

PrintCharacter:
	MOV AH,0x0E;
	MOV BH,0x00;
	MOV BL,0x07;
	INT 0x10;
	RET;
	
PrintString:
	MOV AL,[SI];
	OR AL,AL;
	JZ EXIT;
	CALL PrintCharacter;
	INC SI;
	JMP PrintString;
	EXIT:
	RET;
	
string DB 'Yashvanth',0;
TIMES 510-($-$$) DB 0;
DW 0xAA55;
