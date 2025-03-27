[BITS 16];
[ORG 0X7C00];
MOV SI,STRING;
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
	OR AL,AL
	JZ Exit
	CALL PrintCharacter;
	INC SI;
	JMP PrintString;
	Exit:
	RET;

STRING DB "Yashvanth is a good boy",0;
TIMES 510-($-$$) DB 0;
DW 0xAA55;
