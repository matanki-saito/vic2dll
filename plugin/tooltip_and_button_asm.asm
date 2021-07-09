EXTERN _tooltipAndButtonProc1ReturnAddress: DWORD
EXTERN _tooltipAndButtonProc2ReturnAddress: DWORD
EXTERN _tooltipAndButtonProc3ReturnAddress: DWORD
EXTERN _tooltipAndButtonProc4ReturnAddress: DWORD
EXTERN _tooltipAndButtonProc4CallAddress: DWORD

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

.DATA
tmp1	DW		0

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

;------------------------------;

tooltipAndButtonProc2 PROC

	cmp		byte ptr[eax + esi], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr [eax + esi];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[eax + esi + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[eax + esi + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[eax + esi + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[eax + esi + 1];
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		esi, 2;
	cmp		eax, NO_FONT;

	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	
	mov		edi, [edi+eax*4 + 94h]
	test	edi, edi
	push	_tooltipAndButtonProc2ReturnAddress
	ret
tooltipAndButtonProc2 ENDP


;------------------------------;

tooltipAndButtonProc3 PROC

	cmp		byte ptr[eax + esi], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr [eax + esi];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[eax + esi + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[eax + esi + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[eax + esi + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[eax + esi + 1];
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		esi, 2;
	cmp		eax, NO_FONT;

	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	
	mov		eax, [edi+eax*4 + 94h]
	test	eax, eax
	push	_tooltipAndButtonProc3ReturnAddress
	ret
tooltipAndButtonProc3 ENDP

;------------------------------;

tooltipAndButtonProc4 PROC

	mov     cl, [eax+esi]
	mov     byte ptr [esp + 400h - 370h], cl
	mov     dword ptr [esp + 400h - 33Ch], 0Fh
	mov     dword ptr [esp + 400h - 340h], 0
	mov     byte ptr [esp + 400h - 350h], 0
	mov     edx, [esp + 400h - 370h]
	push    edx

	cmp		cl, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		cl, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		cl, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		cl, ESCAPE_SEQ_4;
	jz		JMP_A;
	jmp		JMP_B;

JMP_A:
	push	3
	mov		ax, word ptr [eax+esi+1]
	mov		tmp1, ax
	jmp		JMP_C
JMP_B:
	mov		tmp1, 0
	push	1

JMP_C:
	lea     ecx, [esp + 408h - 350h]
	mov     byte ptr [esp + 408h - 4h], 3
	call	_tooltipAndButtonProc4CallAddress

	cmp		tmp1, 0
	jz		JMP_D

	mov		cx, tmp1
	mov		word ptr [esp + 400h - 350h + 1], cx
	lea		ecx, [esp + 400h - 350h]

JMP_D:
	push	_tooltipAndButtonProc4ReturnAddress
	ret

tooltipAndButtonProc4 ENDP

END