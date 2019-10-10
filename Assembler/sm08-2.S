	.text
	.global process
        .global A, B, C, D, R
	.data
A:      .int	0
B:      .int	0
C:	.int	0
D:	.int	0
R:	.int	0
process:
	mov	A, %ecx
	mov	B, %eax
	imull	%ecx
	movl	%eax, %ecx
	mov	C, %edx
	mov	D, %eax
	imull	%edx
	subl	%ecx, %eax
	negl	%eax
	mov	%eax, R
	ret

