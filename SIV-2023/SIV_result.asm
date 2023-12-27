.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib

ExitProcess PROTO:DWORD 
SYSPAUSE PROTO 
soutl PROTO : BYTE 
noutl PROTO : SDWORD 
_pow PROTO  : SDWORD, : SDWORD 
_abs PROTO  : SDWORD 

.STACK 4096

.CONST
	null_division BYTE 'ERROR: DIVISION BY ZERO', 0
	OVER_FLOW BYTE 'ERROR: OVERFLOW', 0
	true BYTE 'true', 0
	false BYTE 'false', 0
	empty_string BYTE 0
	short0 SDWORD -1
	short1 SDWORD 0
	str2 BYTE "Hello there!", 0
	str3 BYTE "Арифм. операции:", 0
	short4 SDWORD 2
	short5 SDWORD 2
	short6 SDWORD 5
	str7 BYTE "Контрольный пример выражения: ", 0
	short8 SDWORD 5
	short9 SDWORD 11
	short10 SDWORD 2
	short11 SDWORD 178
	short12 SDWORD 19
	short13 SDWORD 255
	short14 SDWORD 19
	str15 BYTE "FFH + 23O = ", 0
	str16 BYTE "Вызов функции:", 0
	short17 SDWORD -4
	short18 SDWORD 3
	str19 BYTE "Условный оператор:", 0
	short20 SDWORD 0
	str21 BYTE "positive", 0
	short22 SDWORD 1
	str23 BYTE "negative", 0
	short24 SDWORD -1
.DATA
	res10 SDWORD 0
	str163 DWORD empty_string
	i63 SDWORD 0
	asd63 SDWORD 0
	num63 SDWORD 0
	c63 SDWORD 0
	flag63 DWORD 0

.CODE

func1 PROC b1 : SDWORD, a1 : SDWORD
	push short0
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov res10, eax
	mov eax, a1
	cmp eax, short1
	jl ifi1
	jge else1
ifi1:
	push a1
	call _abs
	push eax
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov res10, eax
	jmp ifEnd1
else1:
	push a1
	push b1
	call _pow
	push eax
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov res10, eax
ifEnd1:
	push res10
	jmp local0
local0:
	pop eax
	ret
func1 ENDP

setstring2 PROC s2 : DWORD
	push s2
	jmp local1
local1:
	pop eax
	ret
setstring2 ENDP

main PROC
	push offset str2
	call setstring2
	push eax
	pop str163


push str163
call soutl

push offset str3
call soutl
	push short4
	push short5
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov i63, eax
	push short6
	push i63
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push eax
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov asd63, eax

push i63
call noutl

push offset str7
call soutl
	push short8
	push short9
	push short10
	call _pow
	push eax
	push short11
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	push short12
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov i63, eax

push i63
call noutl
	push short13
	push short14
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov i63, eax

push offset str15
call soutl

push i63
call noutl

push offset str16
call soutl
	push short17
	push short18
	call func1
	push eax
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov num63, eax

push num63
call noutl

push offset str19
call soutl
	mov eax, i63
	cmp eax, short20
	jge ifi2
	jl else2
ifi2:

push offset str21
call soutl
	push short22
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov c63, eax
	jmp ifEnd2
else2:

push offset str23
call soutl
	push short24
	pop eax
	cmp eax, 32767
	jg overflow
	cmp eax, -32768
	jl overflow
	mov c63, eax
ifEnd2:

push c63
call noutl
	call SYSPAUSE
	push 0
	call ExitProcess
SOMETHINGWRONG::
	push offset null_division
	call soutl
jmp THEEND
overflow::
	push offset OVER_FLOW
	call soutl
THEEND:
	call SYSPAUSE
	push -1
	call ExitProcess
main ENDP
end main