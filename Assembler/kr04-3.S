	.text
	.global myexpm2
A:	.double 1
B:	.double -1
C:	.double 0
myexpm2:
	push	%ebp
	movl	%esp, %ebp
	movsd	8(%ebp), %xmm0
	movsd	A, %xmm1
	movsd   A, %xmm2
	movsd   A, %xmm4
	movsd   A, %xmm6
	movsd   A, %xmm5
	movsd   C, %xmm3
	movsd   B, %xmm7
	
circle:
	movsd	%xmm5, %xmm4
	mulsd	%xmm7, %xmm1
	movsd	%xmm2, %xmm5
	mulsd	%xmm1, %xmm5
	addsd	%xmm6, %xmm3
	mulsd	%xmm5, %xmm0
	mulsd   %xmm5, %xmm0
	divsd	%xmm3, %xmm5
	mulsd	%xmm5, %xmm2
	addsd	%xmm4, %xmm5
	comisd	%xmm4, %xmm5
	jne	circle
	
finish:
	movl	16(%ebp), %eax
	movsd	%xmm0, (%eax)
	mov	%ebp, %esp
        pop    	%ebp
	ret
