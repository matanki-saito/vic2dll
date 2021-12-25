EXTERN _saveFileProc1ReturnAddress: DWORD
EXTERN _saveFileProc1InjectionFunctionAddress: DWORD
EXTERN _saveFileProc3ReturnAddress: DWORD
EXTERN _saveFileProc5ReturnAddress: DWORD
EXTERN _saveFileProc5InjectionFunctionAddress: DWORD

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
tmp3	DD		0
tmp5	DD		0

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

;----------------------------------;

saveFileProc3 PROC
	PUSHAD;

	mov		ecx, eax;
	call	_saveFileProc1InjectionFunctionAddress;
	mov		tmp3, eax;

	POPAD;

	mov		eax, tmp3;

	push    0FFFFFFFFh;
	push    ebx;
	push    eax;
	lea		ecx, [esp+13Ch-0C0h];
	mov     byte ptr [esp+13Ch-04h], 13h

	push	_saveFileProc3ReturnAddress;
	ret;
saveFileProc3 ENDP

;----------------------------------;

saveFileProc5 PROC

	mov     edi, dword ptr [ebp+0Ch]

	PUSHAD;
	mov		ecx, edi;
	call	_saveFileProc5InjectionFunctionAddress;
	mov		tmp5, eax;
	POPAD;

	mov		edi, tmp5;

	cmp     dword ptr [edi+14h], 10h;
	jb JMP_A;

	mov     edx, [edi]
	jmp		JMP_B;

JMP_A:
	mov     edx, edi;

JMP_B:

	push	_saveFileProc5ReturnAddress;
	ret;
saveFileProc5 ENDP

END