/*
 * @Author: sky
 * @Date: 2021-12-24 22:26:43
 * @LastEditTime: 2022-05-03 00:13:30
 * @LastEditors: sky wcf0118@gmail.com
 * @Description: 指针操作（取地址 & 与解引用 *)对应的汇编指令
 * @FilePath: /comm/language/cpp/pointer/pointer.cpp
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n = 10;
    const int* const npA = &n;
    int* npB = &n;
    *npB = 20;
	printf( "the address of n: [%p]\n", npB );
    printf( "The value n is [%d]\n", n );
    printf( "Are They npA npB is the same [%d]\n", (npA == npB) );

    return 0;
}

/*
1）intel x86_64架构；
2）gcc version 8.3.1 20191121 (Red Hat 8.3.1-5) (GCC)
gcc -S -o pointer.s pointer.cpp
	.file	"pointer.cpp"
	.text
	.section	.rodata
.LC0:
	.string	"The value n is [%d]\n"
	.align 8
.LC1:
	.string	"Are They npA npB is the same [%d]\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$10, -20(%rbp)
	leaq	-20(%rbp), %rax
	movq	%rax, -8(%rbp)
	leaq	-20(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	$20, (%rax)
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rax
	cmpq	-16(%rbp), %rax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.3.1 20191121 (Red Hat 8.3.1-5)"
	.section	.note.GNU-stack,"",@progbits
*/
