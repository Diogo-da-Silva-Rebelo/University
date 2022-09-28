	.file	"mul_dinamic.c"
	.text
	.p2align 4
	.globl	createM
	.type	createM, @function
createM:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movslq	%edi, %rdi
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	movq	%rdi, %r13
	salq	$3, %rdi
	pushq	%r12
	.cfi_offset 12, -40
	movslq	%esi, %r12
	pushq	%rbx
	.cfi_offset 3, -48
	call	malloc@PLT
	movq	%rax, %r14
	testl	%r13d, %r13d
	jle	.L1
	movl	%r13d, %r13d
	salq	$2, %r12
	movq	%rax, %rbx
	leaq	(%rax,%r13,8), %r13
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%r12, %rdi
	addq	$8, %rbx
	call	malloc@PLT
	movq	%rax, -8(%rbx)
	cmpq	%r13, %rbx
	jne	.L3
.L1:
	popq	%rbx
	movq	%r14, %rax
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	createM, .-createM
	.p2align 4
	.globl	initM
	.type	initM, @function
initM:
.LFB40:
	.cfi_startproc
	endbr64
	testl	%edi, %edi
	jle	.L7
	leal	-1(%rdi), %eax
	leaq	8(%rcx,%rax,8), %r9
	.p2align 4,,10
	.p2align 3
.L9:
	testl	%esi, %esi
	jle	.L12
	movq	(%rcx), %rax
	leal	(%rsi,%rdx), %r8d
	.p2align 4,,10
	.p2align 3
.L10:
	movl	%edx, %edi
	addl	$1, %edx
	addq	$4, %rax
	movl	%edi, -4(%rax)
	cmpl	%r8d, %edx
	jne	.L10
.L12:
	addq	$8, %rcx
	cmpq	%r9, %rcx
	jne	.L9
.L7:
	ret
	.cfi_endproc
.LFE40:
	.size	initM, .-initM
	.p2align 4
	.globl	multM
	.type	multM, @function
multM:
.LFB41:
	.cfi_startproc
	endbr64
	movslq	%edi, %rax
	testl	%eax, %eax
	jle	.L26
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	xorl	%r11d, %r11d
	movslq	%edx, %r10
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	movq	%r8, %r14
	pushq	%r13
	.cfi_offset 13, -40
	movl	%ecx, %r13d
	pushq	%r12
	.cfi_offset 12, -48
	movl	%edx, %r12d
	pushq	%rbx
	.cfi_offset 3, -56
	movq	%rax, -48(%rbp)
	leal	-1(%rcx), %eax
	leaq	4(,%rax,4), %r15
	.p2align 4,,10
	.p2align 3
.L16:
	testl	%r13d, %r13d
	jle	.L19
	movq	16(%rbp), %rax
	xorl	%edi, %edi
	movq	(%rax,%r11,8), %rsi
	leaq	(%r15,%rsi), %rbx
	.p2align 4,,10
	.p2align 3
.L18:
	movl	$0, (%rsi)
	testl	%r12d, %r12d
	jle	.L21
	movq	(%r14,%r11,8), %r8
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L20:
	movq	(%r9,%rax,8), %rdx
	movl	(%rdx,%rdi), %edx
	imull	(%r8,%rax,4), %edx
	addq	$1, %rax
	addl	%edx, %ecx
	movl	%ecx, (%rsi)
	cmpq	%r10, %rax
	jne	.L20
.L21:
	addq	$4, %rsi
	addq	$4, %rdi
	cmpq	%rsi, %rbx
	jne	.L18
.L19:
	addq	$1, %r11
	cmpq	-48(%rbp), %r11
	jne	.L16
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
.L26:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	ret
	.cfi_endproc
.LFE41:
	.size	multM, .-multM
	.p2align 4
	.globl	free2Darray
	.type	free2Darray, @function
free2Darray:
.LFB42:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	.cfi_offset 13, -24
	movq	%rdi, %r13
	pushq	%r12
	pushq	%rbx
	subq	$8, %rsp
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	testl	%esi, %esi
	jle	.L30
	leal	-1(%rsi), %eax
	movq	%rdi, %rbx
	leaq	8(%rdi,%rax,8), %r12
	.p2align 4,,10
	.p2align 3
.L31:
	movq	(%rbx), %rdi
	addq	$8, %rbx
	call	free@PLT
	cmpq	%r12, %rbx
	jne	.L31
.L30:
	addq	$8, %rsp
	movq	%r13, %rdi
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	jmp	free@PLT
	.cfi_endproc
.LFE42:
	.size	free2Darray, .-free2Darray
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d "
	.text
	.p2align 4
	.globl	print
	.type	print, @function
print:
.LFB43:
	.cfi_startproc
	endbr64
	testl	%esi, %esi
	jle	.L43
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leal	-1(%rsi), %eax
	leaq	8(%rdi,%rax,8), %rax
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	.cfi_offset 15, -24
	movq	%rdi, %r15
	pushq	%r14
	.cfi_offset 14, -32
	movl	%edx, %r14d
	pushq	%r13
	pushq	%r12
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	leaq	.LC0(%rip), %r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -56
	movq	%rax, -56(%rbp)
	leal	-1(%rdx), %eax
	leaq	4(,%rax,4), %r13
	.p2align 4,,10
	.p2align 3
.L36:
	xorl	%ebx, %ebx
	testl	%r14d, %r14d
	jle	.L38
	.p2align 4,,10
	.p2align 3
.L37:
	movq	(%r15), %rax
	movq	%r12, %rsi
	movl	$1, %edi
	movl	(%rax,%rbx), %edx
	xorl	%eax, %eax
	addq	$4, %rbx
	call	__printf_chk@PLT
	cmpq	%rbx, %r13
	jne	.L37
.L38:
	movl	$10, %edi
	addq	$8, %r15
	call	putchar@PLT
	cmpq	-56(%rbp), %r15
	jne	.L36
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
.L43:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	ret
	.cfi_endproc
.LFE43:
	.size	print, .-print
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB44:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$512, %esi
	movl	$512, %edi
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	subq	$8, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	call	createM
	movl	$512, %esi
	movl	$512, %edi
	movq	%rax, %r13
	call	createM
	movl	$512, %esi
	movl	$512, %edi
	movq	%rax, %r12
	call	createM
	movl	$512, %esi
	movq	%r13, %rcx
	movl	$1, %edx
	movl	$512, %edi
	movq	%rax, %r14
	call	initM
	movq	%r12, %rcx
	movl	$1, %edx
	movl	$512, %edi
	call	initM
	subq	$8, %rsp
	movq	%r12, %r9
	movq	%r13, %r8
	pushq	%r14
	movl	$512, %ecx
	movl	$512, %edx
	movl	$512, %edi
	call	multM
	movq	%r13, %rdi
	movl	$512, %esi
	call	free2Darray
	movq	%r12, %rdi
	movl	$512, %esi
	call	free2Darray
	movq	%r14, %rdi
	movl	$512, %esi
	call	free2Darray
	leaq	-24(%rbp), %rsp
	xorl	%eax, %eax
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
