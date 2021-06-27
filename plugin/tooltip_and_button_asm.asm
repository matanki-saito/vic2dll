EXTERN _tooltipAndButtonProc1SrcAddress: DWORD
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
	mov		ecx, [_tooltipAndButtonProc1SrcAddress]
	add		eax, ecx
	mov		al, byte ptr [eax]
	movzx	ecx, al
	mov		edi, [ebx+ecx*4+94h]
	test	edi, edi

	push	_tooltipAndButtonProc1ReturnAddress
	ret
tooltipAndButtonProc1 ENDP
END