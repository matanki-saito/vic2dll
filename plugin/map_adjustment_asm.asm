EXTERN _mapAdjustmentProc1ReturnAddress: DWORD

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
mapAdjustmentProc1 PROC

	cmp     byte ptr [ebx+eax], ESCAPE_SEQ_1
	jz		JMP_A
	cmp     byte ptr [ebx+eax], ESCAPE_SEQ_2
	jz		JMP_A
	cmp     byte ptr [ebx+eax], ESCAPE_SEQ_3
	jz		JMP_A
	cmp     byte ptr [ebx+eax], ESCAPE_SEQ_4
	jz		JMP_A
	
	dec		ecx
	jmp		JMP_C

JMP_A:
	sub		ecx, 3
	mov     [esp+100h-30h], ecx
	add		ebx, 2

JMP_C:
	xorps   xmm1, xmm1
	cvtps2pd xmm0, xmm0
	push	_mapAdjustmentProc1ReturnAddress
	ret
mapAdjustmentProc1 ENDP
END