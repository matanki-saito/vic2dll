EXTERN _inputProc1ReturnAddress1: DWORD
EXTERN _inputProc1ReturnAddress2: DWORD
EXTERN _DefWindowProcHookAddress: DWORD

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
DEFAULT_JOINTER		DB		20,00

.CODE
inputProc1 PROC
	mov     eax, dword ptr [ebp+14h] ; lParam
	mov     ecx, dword ptr [ebp+8h] ; hWnd
	push    eax ; lParam
	push    edx ; wParam
	push    esi ; Msg
	push    ecx ; hWnd

	call	_DefWindowProcHookAddress;

	push	_inputProc1ReturnAddress2;
	ret;
inputProc1 ENDP

END