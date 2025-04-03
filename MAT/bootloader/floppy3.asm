[BITS 16]
[ORG 0X7C00];

MOV SI, STRING;
CALL PRINTSTRING;
JMP $;

PRINT:
	MOV AH, 0X0E;
	MOV BH, 0X00;
	MOV BL, 0X07;
	INT 0X10;
	RET;

PRINTSTRING:
	MOV AL, [SI];
	OR AL, AL;
	JZ EXIT;
	CALL PRINT;
	INC SI;
	JMP PRINTSTRING;
	EXIT:
	RET;

STRING DB 'DEEPAK',0;
TIMES 510 - ($ -$$) DB 0;
DW 0XAA55;
