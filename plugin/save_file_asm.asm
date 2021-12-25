EXTERN _saveFileProc1ReturnAddress: DWORD
EXTERN _saveFileProc1InjectionFunctionAddress: DWORD

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
tmp1	DD		0

.CODE
saveFileProc1 PROC
	PUSHAD;

	mov		ecx, eax;
	call	_saveFileProc1InjectionFunctionAddress;
	mov		tmp1, eax;

	POPAD;

	mov		eax, tmp1;

	push    0FFFFFFFFh;
	push    0;
	push    eax
	lea     ecx, [ebp - 0C4h];
	mov     byte ptr [ebp - 4h], 0Ah;

	push	_saveFileProc1ReturnAddress;
	ret;
saveFileProc1 ENDP

END