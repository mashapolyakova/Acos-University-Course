	.global process
	.data
L1:	.asciz "%d\n"
process:
	push    %ebp
        mov     %esp, %ebp
	pushl	$L1
	call	scanf
	popl	%ecx
	movl	%ecx, %ebx
read:
	movl	%ecx, %esi
	push	$L1
	call	scanf
	movl	%esi, %ecx
	loop	read
write:
	movl	%ebx, %ecx
	push	$L1
	call	printf
	popl	%ebx
	loop	write
end:
	pop	%ebp
	ret
	
