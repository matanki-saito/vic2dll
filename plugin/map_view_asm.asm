EXTERN _mapViewProc1ReturnAddress: DWORD
EXTERN _mapViewProc2ReturnAddress: DWORD
EXTERN _mapViewProc3ReturnAddress: DWORD
EXTERN _mapViewProc4ReturnAddress: DWORD
EXTERN _mapViewProc4CallAddress: DWORD
EXTERN _mapViewProc6ReturnAddress: DWORD
EXTERN _mapViewProc6ReturnAddress2: DWORD
EXTERN _mapViewProc7ReturnAddress: DWORD

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
tmp2	DD		0
tmp3	DD		0

.CODE
mapViewProc1 PROC

	mov     edx, dword ptr [esp + 328h - 318h]

	cmp		byte ptr[eax + edx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax + edx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax + edx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax + edx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx   eax, byte ptr [eax + edx];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[eax + edx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[eax + edx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[eax + edx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[eax + edx + 1];
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		edx, 2;
	mov		dword ptr [esp + 328h - 318h], edx
	cmp		eax, NO_FONT;

	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	mov     edx, dword ptr [ebp + 8] ; arg_0
	mov     edx, dword ptr [edx + eax * 4 + 94h]
	test	edx, edx
	push	_mapViewProc1ReturnAddress
	ret
mapViewProc1 ENDP

;-------------------;

mapViewProc2 PROC

	cmp		byte ptr[edx + ebx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[edx + ebx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[edx + ebx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[edx + ebx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx   edx, byte ptr [edx + ebx];
	jmp		JMP_E;

JMP_A:
	movzx	edx, word ptr[edx + ebx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	edx, word ptr[edx + ebx + 1];
	sub		edx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	edx, word ptr[edx + ebx + 1];
	add		edx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	edx, word ptr[edx + ebx + 1];
	add		edx, SHIFT_4;

JMP_F:
	add		ebx,2
	mov		dword ptr [esp + 328h - 318h], ebx

	movzx	edx, dx;
	cmp		edx, NO_FONT;

	ja		JMP_E;
	mov		edx, NOT_DEF;

JMP_E:
	mov     edi, dword ptr [ebp + 8]
	mov     edx, dword ptr [edi + edx * 4 + 94h]
	test	edx, edx
	push	_mapViewProc2ReturnAddress
	ret
mapViewProc2 ENDP

;-------------------;

mapViewProc3 PROC

	mov		tmp3, 0

	cmp		byte ptr[eax + esi], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[eax + esi], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx   ecx, byte ptr [eax + esi];
	jmp		JMP_E;

JMP_A:
	movzx	ecx, word ptr[eax + esi + 1];
	jmp		JMP_F;

JMP_B:
	movzx	ecx, word ptr[eax + esi + 1];
	sub		ecx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	ecx, word ptr[eax + esi + 1];
	add		ecx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	ecx, word ptr[eax + esi + 1];
	add		ecx, SHIFT_4;

JMP_F:
	mov		tmp3, 1

	movzx	ecx, cx;
	cmp		ecx, NO_FONT;

	ja		JMP_E;
	mov		ecx, NOT_DEF;

	add		esi,3
	cmp		esi, dword ptr [ebp - 18h]
	jg		JMP_Z

JMP_E:
	mov     eax, dword ptr [ebp - 10h]
	mov     ecx, dword ptr [eax + ecx * 4 + 94h]
	test	ecx, ecx
	push	_mapViewProc3ReturnAddress
	ret

JMP_Z:
	push	_mapViewProc6ReturnAddress2
	ret
	
mapViewProc3 ENDP

;-------------------;

mapViewProc4 PROC
	mov     edx, dword ptr [esp + 328h - 318h]
	lea		edx, dword ptr [eax + edx]
	mov		tmp2, edx
	mov     edx, dword ptr [esp + 328h - 318h]

	; 
	mov     al, byte ptr [eax + edx]
	mov     byte ptr [esp + 328h - 300h], al
	mov     dword ptr [esp + 328h - 1D0h], 0Fh
	mov     dword ptr [esp + 328h - 1D4h], ecx
	mov     byte ptr [esp + 328h - 1E4h], 0
	mov     ecx, dword ptr [esp + 328h - 300h]
	push    ecx

	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_A;
	jmp		JMP_B;

JMP_A:
	push	3
	mov		eax, tmp2
	mov		ax, word ptr [eax+1]
	mov		tmp1, ax
	jmp		JMP_C
JMP_B:
	mov		tmp1, 0
	push	1

JMP_C:
	lea     ecx, dword ptr [esp + 330h - 1E4h]
	mov     byte ptr [esp + 330h - 4h], 2
	call	_mapViewProc4CallAddress

	cmp		tmp1, 0
	jz		JMP_D

	mov		cx, tmp1
	mov		word ptr [esp + 328h - 1E4h + 1], cx

JMP_D:
	push	_mapViewProc4ReturnAddress
	ret

mapViewProc4 ENDP

;-------------------;

mapViewProc6 PROC
	mov     eax, dword ptr[edx+10h]
	inc     esi
	cmp		tmp3, 0
	jz		JMP_A
	add		esi,2

JMP_A:
	mov     dword ptr [ebp - 0Ch], esi
	mov     dword ptr [ebp - 18h], eax
	cmp     esi, eax

	push	_mapViewProc6ReturnAddress
	ret

mapViewProc6 ENDP


;-------------------;


mapViewProc7 PROC

	cvtpd2ps xmm0, xmm0
	comiss  xmm1, xmm0

	push	_mapViewProc7ReturnAddress
	ret

mapViewProc7 ENDP

END