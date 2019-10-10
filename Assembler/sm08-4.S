	.text
	.global main
main:
        movl    $0, %ebx
circle:
        call    readi32
        jc      end
        addl    %eax, %ebx
        jo      undefined
	call	circle
undefined:
	movl	$0, %eax
	movl	$0, %ebx
	adcl	%ebx, %eax
	movl	%eax, %ecx
	movl	$-2147483648, %esi
	imull	%esi
	movl	%eax, %ebx
	movl	%ecx, %eax
	addl	$1, %eax
	andl	$1, %eax
	movl	$2147483647, %esi
	imull	%esi
	addl	%eax, %ebx
end:
        movl    %ebx, %eax
        call    writei32
	call	nl	
	call	finish
