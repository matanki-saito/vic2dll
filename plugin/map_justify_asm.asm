EXTERN _mapJustifyProc1ReturnAddress1: DWORD
EXTERN _mapJustifyProc1ReturnAddress2: DWORD
EXTERN _mapJustifyProc1CallAddress   : DWORD
EXTERN _mapJustifyProc2ReturnAddress : DWORD
EXTERN _mapJustifyProc3ReturnAddress : DWORD

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
JOINTER		DB	16,24,152,00

.CODE
mapJustifyProc1 PROC
; 
	mov     cl, byte ptr [eax+esi]
	mov     byte ptr [ebp+18h], cl

	cmp		cl, ESCAPE_SEQ_1
	jz		JMP_B
	cmp		cl, ESCAPE_SEQ_2
	jz		JMP_B
	cmp		cl, ESCAPE_SEQ_3
	jz		JMP_B
	cmp		cl, ESCAPE_SEQ_4
	jz		JMP_B
	lea     eax, dword ptr [ebp+18h] ; arg_10
	lea     edx, dword ptr [eax+1]

JMP_A:
	mov     cl, byte ptr [eax]
	inc     eax
	test    cl, cl
	jnz		JMP_A
	jmp		JMP_C

JMP_B:
	mov		ax, word ptr [eax + esi + 1]
	mov		word ptr[ebp + 18h + 1], ax
	add		esi, 2
	mov		edx, 0
	mov		eax, 3

JMP_C:
	sub     eax, edx
	push    eax
	lea     edx, [ebp + 18h]
	push    edx
	lea     ecx, [ebp - 0C0h] ; lpsz
	call	_mapJustifyProc1CallAddress

	cmp		esi, ebx
	jz		JMP_D
	push	_mapJustifyProc1ReturnAddress1
	ret

JMP_D:
	push	_mapJustifyProc1ReturnAddress2
	ret

mapJustifyProc1 ENDP

;----------;


mapJustifyProc2 PROC

	cvtpd2ps xmm0, xmm0
	comiss  xmm1, xmm0

	push	_mapJustifyProc2ReturnAddress
	ret

mapJustifyProc2 ENDP

;----------;


mapJustifyProc3 PROC

	push    3
	lea		ecx,JOINTER
	push	ecx
	lea     ecx, [ebp + -94h]
	mov     dword ptr [ebp - 80h], 0Fh
	mov     dword ptr [ebp - 88h + 4], edi
	mov     byte ptr [ebp - 94h], 0

	push	_mapJustifyProc3ReturnAddress
	ret

mapJustifyProc3 ENDP

END