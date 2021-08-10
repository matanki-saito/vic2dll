EXTERN _loadingTextProc1ReturnAddress : DWORD
EXTERN _loadingTextProc1DataAddress : DWORD
EXTERN _loadingTextProc1HookFuncAddress : DWORD

ESCAPE_SEQ_1 = 10h
ESCAPE_SEQ_2 = 11h
ESCAPE_SEQ_3 = 12h
ESCAPE_SEQ_4 = 13h
LOW_SHIFT = 0Fh
HIGH_SHIFT = 9h
SHIFT_2 = LOW_SHIFT
SHIFT_3 = 900h
SHIFT_4 = 8F1h
NO_FONT = 98Fh
NOT_DEF = 2026h

.MODEL FLAT, C

.CODE
loadingTextProc1 PROC

	push	ecx
	push	eax

	call	_loadingTextProc1HookFuncAddress ;call	edx

	mov		eax, dword ptr [_loadingTextProc1DataAddress]
	mov		eax, [eax]

	push	_loadingTextProc1ReturnAddress
	ret
loadingTextProc1 ENDP

END