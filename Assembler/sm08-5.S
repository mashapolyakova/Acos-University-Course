	.data
	.global main
main:
	movl	$0, %ecx
	movl	$0, %ebx
circle:
	movl	%ecx, %edi
	call	readi32
	movl	%edi, %ecx
	jc	end
	movl	$1, %esi
	andl	%eax, %esi
	cmpl	$0, %esi
	jne	not_equal
	addl	%eax, %ecx
	call	circle
not_equal:
	addl	%eax, %ebx
	call	circle
end:
	movl	%ecx, %eax
	call	writei32
	call	nl
	movl	%ebx, %eax
	call    writei32
        call    nl
	call	finish

