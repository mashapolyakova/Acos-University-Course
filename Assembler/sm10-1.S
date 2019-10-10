	.text
	.global process
process:
	push	%ebp
	push	%esi
	push	%edi
	mov	%esp, %ebp

	mov	A, %eax
	mov	A+4, %edx

	sal	$1, %eax
	rcl	$1, %edx

	mov	B, %esi
	mov	B+4, %edi
	
	shr	$1, %edi
	rcr	$1, %esi

	sub	%esi, %eax
	sbb	%edi, %edx

	push	%eax
	push	%edx
	push	%eax
	push	$L1
	call	printf
	add	$16, %esp

	mov	%ebp, %esp
	pop	%edi
	pop	%esi
	pop	%ebp
	ret
L1:
	.string "%llu\n"
	.align	16
