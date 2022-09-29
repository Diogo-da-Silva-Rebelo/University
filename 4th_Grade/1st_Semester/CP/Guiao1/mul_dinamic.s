	.file	"mul_dinamic.c"
	.text
.Ltext0:
	.file 0 "/home/purp/CLionProjects/University/4th_Grade/1st_Semester/CP/Guiao1" "mul_dinamic.c"
	.globl	createM
	.type	createM, @function
createM:
.LFB6:
	.file 1 "mul_dinamic.c"
	.loc 1 7 33
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	.loc 1 9 14
	movl	-36(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
.LBB2:
	.loc 1 10 13
	movl	$0, -28(%rbp)
	.loc 1 10 5
	jmp	.L2
.L3:
	.loc 1 11 21 discriminator 3
	movl	-40(%rbp), %eax
	cltq
	salq	$2, %rax
	.loc 1 11 15 discriminator 3
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	movq	-24(%rbp), %rdx
	leaq	(%rcx,%rdx), %rbx
	.loc 1 11 21 discriminator 3
	movq	%rax, %rdi
	call	malloc@PLT
	.loc 1 11 19 discriminator 3
	movq	%rax, (%rbx)
	.loc 1 10 32 discriminator 3
	addl	$1, -28(%rbp)
.L2:
	.loc 1 10 23 discriminator 1
	movl	-28(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L3
.LBE2:
	.loc 1 12 12
	movq	-24(%rbp), %rax
	.loc 1 13 1
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	createM, .-createM
	.globl	initM
	.type	initM, @function
initM:
.LFB7:
	.loc 1 16 56
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movq	%rcx, -40(%rbp)
	.loc 1 18 12
	movl	$0, -8(%rbp)
	.loc 1 18 5
	jmp	.L6
.L9:
	.loc 1 19 16
	movl	$0, -4(%rbp)
	.loc 1 19 9
	jmp	.L7
.L8:
	.loc 1 20 33 discriminator 3
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -28(%rbp)
	.loc 1 20 19 discriminator 3
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	movq	-40(%rbp), %rdx
	addq	%rcx, %rdx
	movq	(%rdx), %rcx
	.loc 1 20 22 discriminator 3
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rcx, %rdx
	.loc 1 20 26 discriminator 3
	movl	%eax, (%rdx)
	.loc 1 19 31 discriminator 3
	addl	$1, -4(%rbp)
.L7:
	.loc 1 19 23 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L8
	.loc 1 18 27 discriminator 2
	addl	$1, -8(%rbp)
.L6:
	.loc 1 18 19 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L9
	.loc 1 22 1
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	initM, .-initM
	.globl	multM
	.type	multM, @function
multM:
.LFB8:
	.loc 1 25 76
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	.loc 1 27 12
	movl	$0, -12(%rbp)
	.loc 1 27 5
	jmp	.L11
.L16:
	.loc 1 28 16
	movl	$0, -8(%rbp)
	.loc 1 28 9
	jmp	.L12
.L15:
	.loc 1 29 16
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	.loc 1 29 19
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	%rdx, %rax
	.loc 1 29 23
	movl	$0, (%rax)
	.loc 1 30 20
	movl	$0, -4(%rbp)
	.loc 1 30 13
	jmp	.L13
.L14:
	.loc 1 31 20 discriminator 3
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	.loc 1 31 27 discriminator 3
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	.loc 1 31 32 discriminator 3
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	.loc 1 31 35 discriminator 3
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	.loc 1 31 43 discriminator 3
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rsi
	movq	-48(%rbp), %rax
	addq	%rsi, %rax
	movq	(%rax), %rsi
	.loc 1 31 46 discriminator 3
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	%rsi, %rax
	movl	(%rax), %eax
	.loc 1 31 39 discriminator 3
	imull	%eax, %edx
	.loc 1 31 20 discriminator 3
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rsi
	movq	16(%rbp), %rax
	addq	%rsi, %rax
	movq	(%rax), %rsi
	.loc 1 31 27 discriminator 3
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	%rsi, %rax
	addl	%ecx, %edx
	movl	%edx, (%rax)
	.loc 1 30 34 discriminator 3
	addl	$1, -4(%rbp)
.L13:
	.loc 1 30 27 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L14
	.loc 1 28 30 discriminator 2
	addl	$1, -8(%rbp)
.L12:
	.loc 1 28 23 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L15
	.loc 1 27 26 discriminator 2
	addl	$1, -12(%rbp)
.L11:
	.loc 1 27 19 discriminator 1
	movl	-12(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L16
	.loc 1 35 1
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	multM, .-multM
	.globl	free2Darray
	.type	free2Darray, @function
free2Darray:
.LFB9:
	.loc 1 37 41
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 39 12
	movl	$0, -4(%rbp)
	.loc 1 39 5
	jmp	.L18
.L19:
	.loc 1 40 20 discriminator 3
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 40 9 discriminator 3
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	.loc 1 39 27 discriminator 3
	addl	$1, -4(%rbp)
.L18:
	.loc 1 39 19 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L19
	.loc 1 41 5
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	.loc 1 42 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	free2Darray, .-free2Darray
	.section	.rodata
.LC0:
	.string	"%d "
	.text
	.globl	print
	.type	print, @function
print:
.LFB10:
	.loc 1 44 44
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	.loc 1 46 12
	movl	$0, -8(%rbp)
	.loc 1 46 5
	jmp	.L21
.L24:
	.loc 1 47 16
	movl	$0, -4(%rbp)
	.loc 1 47 9
	jmp	.L22
.L23:
	.loc 1 48 33 discriminator 3
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	.loc 1 48 36 discriminator 3
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	%rdx, %rax
	.loc 1 48 13 discriminator 3
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 47 31 discriminator 3
	addl	$1, -4(%rbp)
.L22:
	.loc 1 47 23 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L23
	.loc 1 50 9 discriminator 2
	movl	$10, %edi
	call	putchar@PLT
	.loc 1 46 27 discriminator 2
	addl	$1, -8(%rbp)
.L21:
	.loc 1 46 19 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L24
	.loc 1 52 1
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	print, .-print
	.globl	main
	.type	main, @function
main:
.LFB11:
	.loc 1 54 11
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	.loc 1 58 9
	movl	$512, -32(%rbp)
	.loc 1 58 20
	movl	$512, -28(%rbp)
	.loc 1 59 10
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	createM
	movq	%rax, -24(%rbp)
	.loc 1 60 10
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	createM
	movq	%rax, -16(%rbp)
	.loc 1 61 11
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	createM
	movq	%rax, -8(%rbp)
	.loc 1 63 5
	movq	-24(%rbp), %rdx
	movl	-28(%rbp), %esi
	movl	-32(%rbp), %eax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	%eax, %edi
	call	initM
	.loc 1 64 5
	movq	-16(%rbp), %rdx
	movl	-28(%rbp), %esi
	movl	-32(%rbp), %eax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	%eax, %edi
	call	initM
	.loc 1 66 5
	movq	-16(%rbp), %r8
	movq	-24(%rbp), %rdi
	movl	-28(%rbp), %ecx
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %esi
	movl	-32(%rbp), %eax
	subq	$8, %rsp
	pushq	-8(%rbp)
	movq	%r8, %r9
	movq	%rdi, %r8
	movl	%eax, %edi
	call	multM
	addq	$16, %rsp
	.loc 1 70 5
	movl	-32(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2Darray
	.loc 1 71 5
	movl	-32(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2Darray
	.loc 1 72 5
	movl	-32(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2Darray
	.loc 1 76 12
	movl	$0, %eax
	.loc 1 77 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
.Letext0:
	.file 2 "/usr/include/stdio.h"
	.file 3 "/usr/include/stdlib.h"
	.file 4 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x359
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0xa
	.long	.LASF22
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0xb
	.long	.LASF23
	.byte	0x4
	.byte	0xd1
	.byte	0x17
	.long	0x3a
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0xc
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF3
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF4
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF5
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF6
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF7
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF8
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF9
	.uleb128 0xd
	.byte	0x8
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0xe
	.long	0x7b
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF11
	.uleb128 0x7
	.long	.LASF12
	.byte	0x2
	.value	0x164
	.byte	0xc
	.long	0x41
	.long	0xa6
	.uleb128 0x5
	.long	0xa6
	.uleb128 0xf
	.byte	0
	.uleb128 0x6
	.long	0x82
	.uleb128 0x10
	.long	.LASF24
	.byte	0x3
	.value	0x22b
	.byte	0xd
	.long	0xbe
	.uleb128 0x5
	.long	0x79
	.byte	0
	.uleb128 0x7
	.long	.LASF13
	.byte	0x3
	.value	0x21c
	.byte	0xe
	.long	0x79
	.long	0xd5
	.uleb128 0x5
	.long	0x2e
	.byte	0
	.uleb128 0x11
	.long	.LASF14
	.byte	0x1
	.byte	0x36
	.byte	0x5
	.long	0x41
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0x13c
	.uleb128 0x1
	.string	"m1"
	.byte	0x39
	.byte	0xb
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"m2"
	.byte	0x39
	.byte	0x11
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1
	.string	"res"
	.byte	0x39
	.byte	0x17
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"row"
	.byte	0x3a
	.byte	0x9
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1
	.string	"col"
	.byte	0x3a
	.byte	0x14
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.byte	0
	.uleb128 0x6
	.long	0x141
	.uleb128 0x6
	.long	0x41
	.uleb128 0x8
	.long	.LASF15
	.byte	0x2c
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0x1a5
	.uleb128 0x4
	.long	.LASF16
	.byte	0x2c
	.byte	0x12
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"row"
	.byte	0x2c
	.byte	0x1e
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"col"
	.byte	0x2c
	.byte	0x27
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1
	.string	"i"
	.byte	0x2d
	.byte	0x9
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"j"
	.byte	0x2d
	.byte	0xc
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x8
	.long	.LASF17
	.byte	0x25
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x1ea
	.uleb128 0x4
	.long	.LASF16
	.byte	0x25
	.byte	0x18
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"row"
	.byte	0x25
	.byte	0x24
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1
	.string	"i"
	.byte	0x26
	.byte	0x9
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x9
	.long	.LASF18
	.byte	0x19
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x287
	.uleb128 0x2
	.string	"r1"
	.byte	0x19
	.byte	0x11
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2
	.string	"r2"
	.byte	0x19
	.byte	0x19
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"c1"
	.byte	0x19
	.byte	0x21
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"c2"
	.byte	0x19
	.byte	0x29
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"m1"
	.byte	0x19
	.byte	0x33
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x2
	.string	"m2"
	.byte	0x19
	.byte	0x3d
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x2
	.string	"res"
	.byte	0x19
	.byte	0x48
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1
	.string	"i"
	.byte	0x1a
	.byte	0x9
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x1
	.string	"j"
	.byte	0x1a
	.byte	0xc
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"k"
	.byte	0x1a
	.byte	0xf
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x9
	.long	.LASF19
	.byte	0x10
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x2f4
	.uleb128 0x2
	.string	"row"
	.byte	0x10
	.byte	0x11
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2
	.string	"col"
	.byte	0x10
	.byte	0x1a
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x4
	.long	.LASF20
	.byte	0x10
	.byte	0x23
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x4
	.long	.LASF16
	.byte	0x10
	.byte	0x31
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1
	.string	"i"
	.byte	0x11
	.byte	0x9
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"j"
	.byte	0x11
	.byte	0xc
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x12
	.long	.LASF21
	.byte	0x1
	.byte	0x7
	.byte	0x7
	.long	0x13c
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x2
	.string	"row"
	.byte	0x7
	.byte	0x14
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x2
	.string	"col"
	.byte	0x7
	.byte	0x1d
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x13
	.long	.LASF16
	.byte	0x1
	.byte	0x8
	.byte	0xb
	.long	0x13c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x14
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x1
	.string	"i"
	.byte	0xa
	.byte	0xd
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF23:
	.string	"size_t"
.LASF20:
	.string	"value"
.LASF18:
	.string	"multM"
.LASF21:
	.string	"createM"
.LASF5:
	.string	"unsigned char"
.LASF2:
	.string	"long unsigned int"
.LASF6:
	.string	"short unsigned int"
.LASF19:
	.string	"initM"
.LASF14:
	.string	"main"
.LASF7:
	.string	"unsigned int"
.LASF11:
	.string	"long long unsigned int"
.LASF17:
	.string	"free2Darray"
.LASF22:
	.string	"GNU C17 11.2.0 -mtune=generic -march=x86-64 -g -O0 -fno-omit-frame-pointer -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection"
.LASF24:
	.string	"free"
.LASF4:
	.string	"long long int"
.LASF10:
	.string	"char"
.LASF16:
	.string	"matrix"
.LASF15:
	.string	"print"
.LASF12:
	.string	"printf"
.LASF9:
	.string	"short int"
.LASF3:
	.string	"long int"
.LASF8:
	.string	"signed char"
.LASF13:
	.string	"malloc"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/purp/CLionProjects/University/4th_Grade/1st_Semester/CP/Guiao1"
.LASF0:
	.string	"mul_dinamic.c"
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
