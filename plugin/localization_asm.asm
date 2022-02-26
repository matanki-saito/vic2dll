EXTERN _localizationProc1ReturnAddress: DWORD

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
DATE_TEMPLATE	DB	'y ',15,' mw d ',14,0

.CODE
localizationProc1 PROC
	push    0Ch
	push	OFFSET DATE_TEMPLATE
	lea     ecx, [esp+0D8h-64h]
	mov     dword ptr [esp+0D8h-50h], esi
	mov     dword ptr [esp+0D8h-54h], ebx
	mov     byte ptr [esp+0D8h-64h], bl

	push	_localizationProc1ReturnAddress
	ret
localizationProc1 ENDP

END
