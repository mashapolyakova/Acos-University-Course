	.text
	.data
	.global print_fib, A, B
L1:
	.asciz	"%d %d %d\n"
print_fib:
	push	%ebp
	mov	%esp, %ebp
	mov	A, %eax
  	addl	B, %eax
  	movl	%eax, %ecx
 	addl	B, %ecx
 	movl	%ecx, %edx
	addl	%eax, %edx
	push	%edx
	push	%ecx
	push	%eax
	push	$L1
	call	printf
	add	$16, %esp
	popl	%ebp
	ret 
