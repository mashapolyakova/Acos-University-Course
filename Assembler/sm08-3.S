.text
	.global main
main:
	call	readi32
	movl	%eax, %ecx
	cmpl	$0, %eax
	jle	end
answer:
	movl 	%ecx, %eax
	movl	%ecx, %esi
	call	writei32
	call 	nl
	movl 	%esi, %ecx
	loop	answer
	movl	$0, %eax
	call	writei32
	call	nl
end:
	cmpl	$0, %eax
	jne	not_equal
	call	writei32
	call	nl
not_equal:	
	call	finish
