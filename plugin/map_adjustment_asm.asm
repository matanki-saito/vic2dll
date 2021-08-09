EXTERN _mapAdjustmentProc1ReturnAddress: DWORD
EXTERN _mapAdjustmentProc2ReturnAddress: DWORD

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

.CODE
mapAdjustmentProc1 PROC
	xorps   xmm0, xmm0
	cvtsi2ss xmm0, ebx

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
	add		ebx, 2
	sub		ecx, 3

JMP_C:
	xorps   xmm1, xmm1
	push	_mapAdjustmentProc1ReturnAddress
	ret
mapAdjustmentProc1 ENDP

;--------------;

mapAdjustmentProc2 PROC
    push    _mapAdjustmentProc2ReturnAddress
    ret
mapAdjustmentProc2 ENDP

END