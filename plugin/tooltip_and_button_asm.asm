EXTERN _tooltipAndButtonProc1ReturnAddress: DWORD

ESCAPE_SEQ_1	=	10h
ESCAPE_SEQ_2	=	11h
ESCAPE_SEQ_3	=	12h
ESCAPE_SEQ_4	=	13h
LOW_SHIFT		=	0Eh
HIGH_SHIFT		=	9h
SHIFT_2			=	LOW_SHIFT
SHIFT_3			=	900h
SHIFT_4			=	8F2h
NO_FONT			=	98Fh
NOT_DEF			=	2026h

.MODEL FLAT, C

.CODE
tooltipAndButtonProc1 PROC

	cmp		byte ptr[eax + ebx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax + ebx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax + ebx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax + ebx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr [eax + ebx];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[eax + ebx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[eax + ebx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[eax + ebx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[eax + ebx + 1];
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	mov		esi, [esp + 400h - 3DCh]
	add		esi, 2;
	mov		[esp + 400h - 3DCh], esi
	cmp		eax, NO_FONT;

	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	
	mov		esi, [edi+eax*4 + 94h]
	test	esi, esi
	push	_tooltipAndButtonProc1ReturnAddress
	ret
tooltipAndButtonProc1 ENDP
END