	.text
	.file	"divide.ll"
	.globl	divide                          # -- Begin function divide
	.p2align	4, 0x90
	.type	divide,@function
divide:                                 # @divide
	.cfi_startproc
# %bb.0:
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	%edi, 20(%rsp)
	movl	%esi, 16(%rsp)
	testl	%esi, %esi
	jne	.LBB0_2
# %bb.1:                                # %L4
	movl	$.L.strlit, %edi
	movl	$.L.str.0, %esi
	xorl	%eax, %eax
	callq	printf@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB0_2:                                # %L5
	.cfi_def_cfa_offset 32
	movl	20(%rsp), %eax
	cltd
	idivl	16(%rsp)
	movl	%eax, 12(%rsp)
	movl	%edx, 8(%rsp)
	movl	$.L.strlit, %edi
	movl	$.L.str.1, %esi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	12(%rsp), %esi
	movl	$.L.int, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	$.L.strlit, %edi
	movl	$.L.str.2, %esi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	8(%rsp), %esi
	movl	$.L.int, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	divide, .Lfunc_end0-divide
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$20, 4(%rsp)
	movl	$2, (%rsp)
	movl	$20, %edi
	movl	$2, %esi
	callq	divide@PLT
	movl	$1, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.L.int,@object                  # @.int
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.int:
	.asciz	"%d\n"
	.size	.L.int, 4

	.type	.L.float,@object                # @.float
.L.float:
	.asciz	"%.08f\n"
	.size	.L.float, 7

	.type	.L.strlit,@object               # @.strlit
.L.strlit:
	.asciz	"%s\n"
	.size	.L.strlit, 4

	.type	.L.true,@object                 # @.true
.L.true:
	.asciz	"true\n"
	.size	.L.true, 6

	.type	.L.false,@object                # @.false
.L.false:
	.asciz	"false\n"
	.size	.L.false, 7

	.type	.L.str.0,@object                # @.str.0
	.section	.rodata.str1.16,"aMS",@progbits,1
	.p2align	4, 0x0
.L.str.0:
	.asciz	"Divis\303\243o por 0 n\303\243o existe"
	.size	.L.str.0, 27

	.type	.L.str.1,@object                # @.str.1
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str.1:
	.asciz	"quotient"
	.size	.L.str.1, 9

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"remainder"
	.size	.L.str.2, 10

	.section	".note.GNU-stack","",@progbits
