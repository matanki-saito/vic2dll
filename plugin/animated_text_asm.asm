EXTERN _animatedTextProc1ReturnAddress: DWORD
EXTERN _animatedTextProc2ReturnAddress: DWORD
EXTERN _animatedTextProc3ReturnAddress: DWORD
EXTERN _animatedTextProc3CallAddress  : DWORD

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
tmp1		DW 0

.CODE
animatedTextProc1 PROC
	cmp		byte ptr[edx+eax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[edx+eax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[edx+eax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[edx+eax], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr[edx+eax]
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[edx+eax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[edx+eax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[edx+eax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[edx+eax + 1];
	add		eax, SHIFT_4;

JMP_F:
	inc		dword ptr [esp+198h-184h]
	inc		dword ptr [esp+198h-184h]
	inc		dword ptr [esp+198h-180h]
	inc		dword ptr [esp+198h-180h]
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;
	mov		eax, NOT_DEF;	

JMP_E:
	mov     eax, dword ptr [ebx+eax*4+94h]
	test    eax, eax

	push	_animatedTextProc1ReturnAddress
	ret
animatedTextProc1 ENDP

;------------------------;

animatedTextProc2 PROC

	cmp		byte ptr[eax+edx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax+edx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax+edx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax+edx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr[eax+edx]
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[eax+edx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[eax+edx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[eax+edx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[eax+edx + 1];
	add		eax, SHIFT_4;

JMP_F:
	inc		dword ptr [esp+198h-184h]
	inc		dword ptr [esp+198h-184h]
	inc		dword ptr [esp+198h-188h]
	inc		dword ptr [esp+198h-188h]
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;
	mov		eax, NOT_DEF;	

JMP_E:
	mov     ecx, dword ptr[ebx+eax*4+94h]
	test    ecx, ecx

	push	_animatedTextProc2ReturnAddress
	ret
animatedTextProc2 ENDP

;------------------------;

animatedTextProc3 PROC
	mov     edx, dword ptr[esp+198h-184h]

	cmp		byte ptr[eax+edx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax+edx], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr[eax+edx], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr[eax+edx], ESCAPE_SEQ_4;
	jz		JMP_A;
	mov     al, byte ptr[eax+edx]
	mov     byte ptr [esp+198h-170h], al
	mov     dword ptr [esp+198h-0C4h], 0Fh
	mov     dword ptr[esp+198h-0C8h], 0
	mov     byte ptr [esp+198h-0D8h], 0
	mov     ecx, dword ptr[esp+198h-170h]
	push    ecx
	push    1
	lea     ecx, [esp+1A0h-0D8h]
	mov     byte ptr [esp+1A0h-04h], 4
	call	_animatedTextProc3CallAddress

	jmp		JMP_F;

JMP_A:
	mov     cl, byte ptr[eax+edx]
	mov     byte ptr [esp+198h-170h], cl
	mov		cx,  word ptr[eax+edx+1]
	mov		tmp1, cx
	mov     dword ptr [esp+198h-0C4h], 0Fh
	mov     dword ptr[esp+198h-0C8h], 0
	mov     byte ptr [esp+198h-0D8h], 0
	mov     ecx, dword ptr[esp+198h-170h]
	push    ecx
	push    3
	lea     ecx, [esp+1A0h-0D8h]
	mov     byte ptr [esp+1A0h-04h], 4
	call	_animatedTextProc3CallAddress
	mov		dx, tmp1
	mov		word ptr[eax+1], dx
	
JMP_F:

	push	_animatedTextProc3ReturnAddress
	ret
animatedTextProc3 ENDP

END