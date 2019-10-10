	.data 
A:	.int	0
B:	.int	0
C:	.int	0
	.text
	.global process, A, B, C
process:
	pushl	%ebp	
	movl	%ebp, %esp	
	pushl	%esi

	movl	A, %eax		
	movl	X, %ecx		
	mull	%ecx		
	mull	%ecx		
	mull	%ecx		
	movl	%eax, %esi	
	
	movl	B, %eax		
	movl	$2, %ecx
	mull	%ecx
	movl	X, %ecx
	mull	%ecx
	mull 	%ecx

	subl	%eax, %esi
	movl	C, %ecx
	addl	%ecx, %esi
	movl	%esi, %eax


	popl	%esi
	popl	%ebp		
	ret
