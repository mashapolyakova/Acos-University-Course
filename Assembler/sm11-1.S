	.global _start
_start:
read:
	movl    $__NR_read, %eax
        movl    $0, %ebx
        movl    $c, %ecx
        movl    $1, %edx
        int     $0x80
	cmpl	
write:

exit:
	movl    $__NR_exit, %eax
        xorl    %ebx, %ebx
        int     $0x80
