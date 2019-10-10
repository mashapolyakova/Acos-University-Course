	.text
	.global process
process:
	push	%ebp
	movl	%esp, %ebp
	push	%esi

	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	$5, %esi
	jo	finish
	imull	%esi
	movl	%eax, %esi
	movl	%ecx, %eax
	movl	%esi, %ecx
	movl	$4, %esi
	imull	%esi
	jo	finish
	subl	%eax, %ecx
	jo	finish

	movl	8(%ebp), %eax
	movl	%ecx, (%eax)
	movl	$0, %eax

	pop     %esi
        pop     %ebp
        ret
	
finish:
	movl	$1, %eax
	pop	%esi
	pop	%ebp
	ret
	
