.section .text
    .global disable_cursor

disable_cursor:
	pushfl
	pushl %eax
	pushl %edx
 
	movw 0x3D4, %dx
	movb 0xA, %al	/* low cursor shape register */
	outb %al, %dx
 
	incw %dx
	movb 0x20, %al	/* bits 6-7 unused, bit 5 disables the cursor, bits 0-4 control the cursor shape */
	outb %al, %dx
 
	popl %edx
	popl %eax
	popfl
	ret
