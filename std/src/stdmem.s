.section .text
    .global memcpy, memset

memcpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi

	movl	8(%ebp), %esi
	movl	16(%ebp), %edx
	movl	12(%ebp), %edi

	rep movsb

	nop
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

memset:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	subl	$4, %esp

	movl	12(%ebp), %eax
	movb	%al, -8(%ebp)
	movl	8(%ebp), %edx
	movb	-8(%ebp), %al
	movl	16(%ebp), %ecx
	movl	%edx, %edi

	rep stosb

	nop
	addl	$4, %esp
	popl	%edi
	popl	%ebp
	ret