[BITS 16];
ORG 0X7C00;
MOV AL,89;
CALL PrintCharacter;
JMP $;

PrintCharacter:
	MOV AH,0x0E;
	MOV BH,0x00;
	MOV BL,0x07;
	INT 0x10;
	RET;

TIMES 510-($-$$) DB 0;
DW 0xAA55;
