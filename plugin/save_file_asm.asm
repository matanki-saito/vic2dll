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

.CODE
saveFileProc1 PROC
	add     esp, 4;

	PUSHAD;

	mov		ecx, eax;
	call	_saveFileProc1InjectionFunctionAddress;

	POPAD;

	mov     dword ptr [esp+120h-110h], eax;
	mov     dword ptr [esp+120h-114h], eax;
	cmp     [eax], ebx;

	push	_saveFileProc1ReturnAddress;
	ret;
saveFileProc1 ENDP

END