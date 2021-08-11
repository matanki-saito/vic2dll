EXTERN _textWidthProc1ReturnAddress: DWORD
EXTERN _textWidthProc2ReturnAddress: DWORD
EXTERN _textWidthProc3ReturnAddress1: DWORD
EXTERN _textWidthProc3ReturnAddress2: DWORD

ESCAPE_SEQ_1	=	10h
ESCAPE_SEQ_2	=	11h
ESCAPE_SEQ_3	=	12h
ESCAPE_SEQ_4	=	13h
LOW_SHIFT		=	0Fh
HIGH_SHIFT		=	9h
SHIFT_2			=	LOW_SHIFT
SHIFT_3			=	900h
SHIFT_4			=	8F1h
NO_FONT			=	98Fh
NOT_DEF			=	2026h

.MODEL FLAT, C

.DATA
tmp1	DW		0

.CODE
textWidthProc1 PROC

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
	push	_textWidthProc1ReturnAddress
	ret
textWidthProc1 ENDP

;------------------------------;

textWidthProc2 PROC
	mov     al, byte ptr [ebx+edx]

	cmp		byte ptr[ebx+edx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[ebx+edx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[ebx+edx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[ebx+edx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx   ecx, al
	jmp		JMP_E;

JMP_A:
	movzx	ecx, word ptr[ebx+edx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	ecx, word ptr[ebx+edx + 1];
	sub		ecx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	ecx, word ptr[ebx+edx + 1];
	add		ecx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	ecx, word ptr[ebx+edx + 1];
	add		ecx, SHIFT_4;

JMP_F:
	add		ebx,3
	cmp		ebx, [ebp - 0Ch]
	jg		JMP_Z

	dec		ebx
	movzx	ecx, cx;
	cmp		ecx, NO_FONT;
	ja		JMP_E;
	mov		ecx, NOT_DEF;

JMP_E:
	mov     ecx, dword ptr [esi + ecx * 4 + 94h]
	test    ecx, ecx

	push	_textWidthProc2ReturnAddress
	ret

JMP_Z:
	push	_textWidthProc3ReturnAddress2
	ret

textWidthProc2 ENDP

;------------------------------;

textWidthProc3 PROC

	inc		ebx
	cmp		ebx, [ebp - 0Ch]
	jl		JMP_A
	
	;ループから抜ける
	push	_textWidthProc3ReturnAddress2
	ret

JMP_A:
	;再ループ
	push	_textWidthProc3ReturnAddress1
	ret

textWidthProc3 ENDP

END
