EXTERN _maintTextProc1SrcAddress: DWORD
EXTERN _maintTextProc1ReturnAddress: DWORD
EXTERN _maintTextProc2SrcAddress: DWORD
EXTERN _maintTextProc2DstAddress: DWORD
EXTERN _maintTextProc3ReturnAddress: DWORD
EXTERN _maintTextProc4ReturnAddress1: DWORD
EXTERN _maintTextProc4ReturnAddress2: DWORD

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
doubleByteFlag	DD		0

.CODE
mainTextProc1 PROC
	mov		ecx, [_maintTextProc1SrcAddress]
	add		eax, ecx

	cmp		byte ptr[eax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax], ESCAPE_SEQ_4;
	jz		JMP_D;
	mov		al, byte ptr [eax];	
	movzx	ecx, al
	jmp		JMP_E;

JMP_A:
	movzx	ecx, word ptr[eax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	ecx, word ptr[eax + 1];
	sub		ecx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	ecx, word ptr[eax + 1];
	add		ecx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	ecx, word ptr[eax + 1];
	add		ecx, SHIFT_4;

JMP_F:
	mov		doubleByteFlag, 1
	movzx	ecx, cx;
	mov		edi, [esp + 530h - 514h]
	add		edi, 2;
	mov		[esp + 530h - 514h], edi
	cmp		ecx, NO_FONT;
	ja		JMP_E;
	mov		ecx, NOT_DEF;

JMP_E:
	mov		edi, [ebx+ecx*4+94h]
	test	edi, edi

	push	_maintTextProc1ReturnAddress
	ret
mainTextProc1 ENDP

;---------------------------------------------;

mainTextProc3 PROC
	mov		ecx, [_maintTextProc2SrcAddress]
	add		eax, ecx

	cmp		byte ptr[eax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	ecx, byte ptr[eax]
	jmp		JMP_E;

JMP_A:
	movzx	ecx, word ptr[eax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	ecx, word ptr[eax + 1];
	sub		ecx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	ecx, word ptr[eax + 1];
	add		ecx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	ecx, word ptr[eax + 1];
	add		ecx, SHIFT_4;

JMP_F:
	movzx	ecx, cx;
	mov		edi, [esp + 530h - 514h]
	add		edi, 2;
	mov		[esp + 530h - 514h], edi
	cmp		ecx, NO_FONT;
	ja		JMP_G;
	mov		ecx, NOT_DEF;

JMP_G:
	; copy character
	mov		ax, word ptr[eax + 1];
	mov		edi, [_maintTextProc2DstAddress]
	add		edi, esi
	mov		word ptr[edi], ax
	add		esi,2

JMP_E:
	mov		ecx, [ebx+ecx*4+94h]
	test	ecx, ecx

	push	_maintTextProc3ReturnAddress
	ret
mainTextProc3 ENDP

;---------------------------------------------;

mainTextProc4 PROC
	cmp		doubleByteFlag, 1
	jz		JMP_A

	cmp		dword ptr [esp + 530h - 4E8h], 0
	mov		doubleByteFlag, 0
	push	_maintTextProc4ReturnAddress1
	ret

JMP_A:
	mov		doubleByteFlag, 0
	push	_maintTextProc4ReturnAddress2
	ret
mainTextProc4 ENDP
END