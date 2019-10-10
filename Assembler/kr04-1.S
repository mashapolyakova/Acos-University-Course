        .text
        .global forward.args

forward.args:
        push	%ebp
        movl    %esp, %ebp
       	andl	$-16, %esp

	push	8(%ebp)
        movl    16(%ebp), %eax
	cdq
	push	%edx
	push	%eax
        push    20(%ebp)

        call    process
        negl    %eax

        movl    %ebp, %esp
        pop	%ebp
	ret
