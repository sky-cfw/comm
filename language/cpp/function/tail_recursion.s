	.file	"tail_recursion.cpp"
	.text
	.p2align 4,,15
	.globl	_Z10factorial1i
	.type	_Z10factorial1i, @function
_Z10factorial1i:
.LFB12:
	.cfi_startproc
	cmpl	$1, %edi
	jbe	.L10
	leal	-2(%rdi), %eax
	leal	-1(%rdi), %ecx
	cmpl	$6, %eax
	jbe	.L8
	movl	%edi, -12(%rsp)
	movd	-12(%rsp), %xmm5
	movl	%ecx, %edx
	xorl	%eax, %eax
	movdqa	.LC0(%rip), %xmm0
	movdqa	.LC2(%rip), %xmm4
	shrl	$2, %edx
	pshufd	$0, %xmm5, %xmm2
	paddd	.LC1(%rip), %xmm2
	.p2align 4,,10
	.p2align 3
.L5:
	movdqa	%xmm2, %xmm3
	movdqa	%xmm2, %xmm1
	paddd	%xmm4, %xmm2
	addl	$1, %eax
	pmuludq	%xmm0, %xmm3
	psrlq	$32, %xmm1
	psrlq	$32, %xmm0
	pmuludq	%xmm0, %xmm1
	pshufd	$8, %xmm3, %xmm0
	pshufd	$8, %xmm1, %xmm1
	punpckldq	%xmm1, %xmm0
	cmpl	%edx, %eax
	jne	.L5
	movdqa	%xmm0, %xmm2
	movdqa	%xmm0, %xmm1
	movl	%ecx, %edx
	psrldq	$8, %xmm2
	psrlq	$32, %xmm0
	andl	$-4, %edx
	pmuludq	%xmm2, %xmm1
	psrlq	$32, %xmm2
	subl	%edx, %edi
	pmuludq	%xmm2, %xmm0
	pshufd	$8, %xmm1, %xmm1
	pshufd	$8, %xmm0, %xmm0
	punpckldq	%xmm0, %xmm1
	movdqa	%xmm1, %xmm0
	psrldq	$4, %xmm1
	pmuludq	%xmm1, %xmm0
	movd	%xmm0, %eax
	cmpl	%edx, %ecx
	je	.L1
	leal	-1(%rdi), %ecx
.L3:
	imull	%edi, %eax
	cmpl	$1, %ecx
	jbe	.L1
	imull	%ecx, %eax
	leal	-2(%rdi), %edx
	cmpl	$1, %edx
	jbe	.L1
	imull	%edx, %eax
	leal	-3(%rdi), %ecx
	cmpl	$1, %ecx
	jbe	.L1
	imull	%ecx, %eax
	leal	-4(%rdi), %edx
	cmpl	$1, %edx
	jbe	.L1
	imull	%edx, %eax
	leal	-5(%rdi), %ecx
	cmpl	$1, %ecx
	jbe	.L1
	subl	$6, %edi
	imull	%ecx, %eax
	cmpl	$1, %edi
	jbe	.L1
	imull	%edi, %eax
.L1:
	ret
	.p2align 4,,10
	.p2align 3
.L10:
	movl	$1, %eax
	ret
.L8:
	movl	$1, %eax
	jmp	.L3
	.cfi_endproc
.LFE12:
	.size	_Z10factorial1i, .-_Z10factorial1i
	.p2align 4,,15
	.globl	_Z10factorial2ii
	.type	_Z10factorial2ii, @function
_Z10factorial2ii:
.LFB13:
	.cfi_startproc
	testl	%edi, %edi
	je	.L37
	leal	-1(%rdi), %edx
	movl	%edi, %r8d
	cmpl	$6, %edx
	jbe	.L18
	movl	%edi, -12(%rsp)
	movd	-12(%rsp), %xmm5
	movl	%edi, %ecx
	xorl	%edx, %edx
	movdqa	.LC0(%rip), %xmm0
	movdqa	.LC2(%rip), %xmm4
	shrl	$2, %ecx
	pshufd	$0, %xmm5, %xmm2
	paddd	.LC1(%rip), %xmm2
	.p2align 4,,10
	.p2align 3
.L15:
	movdqa	%xmm2, %xmm3
	movdqa	%xmm2, %xmm1
	paddd	%xmm4, %xmm2
	addl	$1, %edx
	pmuludq	%xmm0, %xmm3
	psrlq	$32, %xmm1
	psrlq	$32, %xmm0
	pmuludq	%xmm0, %xmm1
	pshufd	$8, %xmm3, %xmm0
	pshufd	$8, %xmm1, %xmm1
	punpckldq	%xmm1, %xmm0
	cmpl	%ecx, %edx
	jne	.L15
	movdqa	%xmm0, %xmm2
	movdqa	%xmm0, %xmm1
	movl	%edi, %edx
	psrldq	$8, %xmm2
	psrlq	$32, %xmm0
	andl	$-4, %edx
	pmuludq	%xmm2, %xmm1
	psrlq	$32, %xmm2
	subl	%edx, %edi
	pmuludq	%xmm2, %xmm0
	pshufd	$8, %xmm1, %xmm1
	pshufd	$8, %xmm0, %xmm0
	punpckldq	%xmm0, %xmm1
	movdqa	%xmm1, %xmm0
	psrldq	$4, %xmm1
	pmuludq	%xmm1, %xmm0
	movd	%xmm0, %eax
	imull	%esi, %eax
	cmpl	%edx, %r8d
	je	.L11
	leal	-1(%rdi), %edx
.L13:
	imull	%edi, %eax
	testl	%edx, %edx
	je	.L11
	imull	%edx, %eax
	movl	%edi, %edx
	subl	$2, %edx
	je	.L11
	imull	%edx, %eax
	movl	%edi, %edx
	subl	$3, %edx
	je	.L11
	imull	%edx, %eax
	movl	%edi, %edx
	subl	$4, %edx
	je	.L11
	imull	%edx, %eax
	movl	%edi, %edx
	subl	$5, %edx
	je	.L11
	imull	%edx, %eax
	subl	$6, %edi
	je	.L11
	imull	%edi, %eax
.L11:
	ret
	.p2align 4,,10
	.p2align 3
.L37:
	movl	%esi, %eax
	ret
.L18:
	movl	%esi, %eax
	jmp	.L13
	.cfi_endproc
.LFE13:
	.size	_Z10factorial2ii, .-_Z10factorial2ii
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"non tail recursion, 5! = %d\n"
.LC4:
	.string	"tail recursion, 5! = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB14:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$120, %esi
	movl	$.LC3, %edi
	xorl	%eax, %eax
	call	printf
	movl	$120, %esi
	movl	$.LC4, %edi
	xorl	%eax, %eax
	call	printf
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE14:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1
	.long	1
	.long	1
	.long	1
	.align 16
.LC1:
	.long	0
	.long	-1
	.long	-2
	.long	-3
	.align 16
.LC2:
	.long	-4
	.long	-4
	.long	-4
	.long	-4
	.ident	"GCC: (GNU) 8.3.1 20191121 (Red Hat 8.3.1-5)"
	.section	.note.GNU-stack,"",@progbits
