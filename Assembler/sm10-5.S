	.global mul64p
	.data
str_1:
        .asciz  "%x\n"

str_2:
	.asciz "%x"
str_3:
	.asciz "%08x\n"

str_0:	
	.asciz  "%08x"
        .text

mul64p:
	push    %ebp
        mov     %esp, %ebp
	
        movl	$0, %eax
	push	%eax
	push    %eax
	push    %eax
	push    %eax

	/*младшие 32 бита*/
	movl	8(%ebp), %eax
	movl	16(%ebp), %ecx
	mull	%ecx
	add	%eax, (%esp)
	adc	%edx, 4(%esp)

        /*средние 64 бита*/
	movl    12(%ebp), %eax
        movl    16(%ebp), %ecx
        mull    %ecx
        add     %eax, 4(%esp)
        adc     %edx, 8(%esp)
	adc	$0, 12(%esp)

	movl    8(%ebp), %eax
        movl    20(%ebp), %ecx
        mull    %ecx
        add     %eax, 4(%esp)
        adc     %edx, 8(%esp)
	adc	$0, 12(%esp) 

	/*старшие 32 бита*/
	movl    12(%ebp), %eax
        movl    20(%ebp), %ecx
        mull    %ecx
        add     %eax, 8(%esp)
	adcl	%edx, 12(%esp)


	cmpl	$0, 12(%esp)
	jne	circle1
	cmpl	$0, 8(%esp)
	jne	circle2
	cmpl	$0, 4(%esp)
	jne	circle3
	push	str_1
	call	printf
	call	end

circle1:
	push    12(%esp)
        push    str_2
        call    printf	

	/*push    16(%esp)
        push    str_0
        call    printf

        push    20(%esp)
        push    str_0
        call    printf

        push    24(%esp)
        push    str_3
        call    printf*/
	call    end

circle2:
	push	8(%esp)
	push	str_2
	call	printf

	push    12(%esp)
        push    str_0
        call    printf

        push    16(%esp)
        push    str_3
        call    printf
	call    end

circle3:
	push	4(%esp)
	push	str_2
	call	printf

	push	8(%esp)
	push	str_3
	call	printf
	call    end

end:
	movl	%ebp, %esp
	pop	%ebp
	ret
