.MODEL SMALL
.STACK 100h

.DATA
return DW ?
n2 DW ?
t0 DW ?
t1 DW ?
t2 DW ?
t3 DW ?
i3 DW ?
j3 DW ?
k3 DW ?
count3 DW ?
t4 DW ?
.CODE
main PROC
	MOV AX,5
	PUSH AX
	CALL factorial
	MOV AX, return
	MOV t4,AX
	MOV count3,AX
	call DECIMAL_OUT
	MOV AH,4CH
	INT 21H
main ENDP

factorial PROC
	PUSH BP
	MOV BP,SP
	MOV AX,[BP + 4]
	CMP AX, 1
	JE L0
	MOV t0, 0
	JMP L1
L0:
	MOV t0, 1
L1:
	MOV AX,t0
	CMP AX,0
	JE L2
	MOV AX,1
	MOV return,AX
	JMP L3
L2:
	MOV AX,[BP + 4]
	MOV BX,1
	SUB AX,BX
	MOV t1, AX
	MOV AX,t1
	PUSH AX
	CALL factorial
	MOV AX, return
	MOV t2,AX
	MOV AX,[BP + 4]
	MOV BX,t2
	MUL BX
	MOV t3,AX
	MOV return,AX
L3:
	POP BP
	RET 2
factorial ENDP




DECIMAL_OUT PROC NEAR

	push ax
	push bx
	push cx
	push dx
	or ax,ax
 	jge enddif
	push ax
	mov dl,'-'
	mov ah,2
	int 21h
	pop ax
	neg ax
enddif:
	xor cx,cx
	mov bx,10d
repeat:
	xor dx,dx
	div bx
	 push dx
	inc cx
	or ax,ax
	jne repeat
	mov ah,2
print_loop:
	pop dx
	or dl,30h
	int 21h
	loop print_loop
	pop dx
	pop cx
	pop bx
	pop ax
	ret

DECIMAL_OUT ENDP
