[BITS 16];
ORG 0X7C00;
JMP $;
TIMES 510-($-$$) DB 0;
DW 0XAA55;
