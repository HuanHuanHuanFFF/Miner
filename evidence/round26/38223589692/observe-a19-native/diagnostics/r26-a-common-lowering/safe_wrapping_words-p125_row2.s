
	.section	.text._RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2,"ax",@progbits
	.prefalign	4, .Lfunc_end17, nop
	.type	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2,@function
_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	movq	%rsp, %r11
	subq	$393216, %r11
	.cfi_def_cfa_register %r11
	.cfi_adjust_cfa_offset 393216
.LBB17_1:
	subq	$4096, %rsp
	movq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LBB17_1
	subq	$136, %rsp
	.cfi_def_cfa_register %rsp
	.cfi_def_cfa_offset 393408
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rdx, %r14
	movq	%rsi, %r12
	movq	%rdi, %r15
	movabsq	$-7046029254386353131, %r13
	leaq	131208(%rsp), %rdi
	movq	memset@GOTPCREL(%rip), %rbx
	movl	$262144, %edx
	xorl	%esi, %esi
	callq	*%rbx
	leaq	136(%rsp), %rdi
	movl	$131072, %edx
	xorl	%esi, %esi
	callq	*%rbx
	movq	%r13, %r10
	movq	%r12, 48(%rsp)
	leaq	20(%r12), %rax
	movq	%rax, 96(%rsp)
	movl	$500016, %eax
	movq	%rax, 88(%rsp)
	pxor	%xmm0, %xmm0
	xorl	%r11d, %r11d
	xorl	%ebx, %ebx
	xorl	%r12d, %r12d
	xorl	%r9d, %r9d
	movq	%r14, 16(%rsp)
	jmp	.LBB17_3
.LBB17_133:
	movq	%r9, %r12
.LBB17_141:
	movq	%rsi, %r14
.LBB17_142:
	cmpq	%r12, %r9
	cmovbeq	%r12, %r9
	cmpq	$499991, %r12
	ja	.LBB17_213
.LBB17_212:
	cmpq	$0, 88(%rsp)
	je	.LBB17_213
.LBB17_3:
	movq	%rbx, 56(%rsp)
	movq	%r11, 40(%rsp)
	cmpq	%r12, %r9
	jae	.LBB17_5
	.p2align	4
.LBB17_4:
	movl	(%r15,%r9), %eax
	bswapl	%eax
	imulq	%r10, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %ecx
	movl	%r9d, %edx
	andl	$32767, %edx
	movl	%ecx, 136(%rsp,%rdx,4)
	movl	%r9d, 131208(%rsp,%rax,4)
	incq	%r9
	cmpq	%r9, %r12
	jne	.LBB17_4
.LBB17_5:
	decq	88(%rsp)
	movl	(%r15,%r12), %eax
	movd	%eax, %xmm1
	movdqa	%xmm1, 112(%rsp)
	movzbl	115(%rsp), %esi
	bswapl	%eax
	imulq	%r10, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %r8d
	movl	%r12d, %ecx
	andl	$32767, %ecx
	movl	%r8d, 136(%rsp,%rcx,4)
	movl	%r12d, 131208(%rsp,%rax,4)
	leaq	1(%r12), %r9
	movl	$500000, %ecx
	subq	%r12, %rcx
	cmpq	$258, %rcx
	movl	$258, %r11d
	cmovbq	%rcx, %r11
	cmpq	$64, %rcx
	movl	$64, %eax
	cmovaeq	%rax, %rcx
	movq	%rcx, 32(%rsp)
	movl	%r11d, %eax
	andl	$504, %eax
	movq	%rax, 24(%rsp)
	leaq	7(%r15), %rax
	leaq	(%rax,%r12), %r14
	movl	$6, %edx
	movl	$3, %ebp
	movq	$0, 8(%rsp)
	.p2align	4
.LBB17_6:
	movq	%r12, %r13
	subq	%r8, %r13
	leaq	-1(%r13), %rax
	cmpq	$32767, %rax
	ja	.LBB17_32
	leaq	(%r8,%rbp), %rax
	cmpq	$499999, %rax
	ja	.LBB17_32
	cmpb	%sil, (%r15,%rax)
	jne	.LBB17_30
	movq	%rbp, %r10
	leaq	7(%r15), %rax
	addq	%r8, %rax
	xorl	%edi, %edi
	jmp	.LBB17_15
	.p2align	4
.LBB17_14:
	xorl	%ebx, %ebx
	cmpq	%rbx, %rbp
	jne	.LBB17_25
.LBB17_15:
	movq	%rdi, %rcx
	addq	$8, %rdi
	cmpq	%r11, %rdi
	ja	.LBB17_18
	leaq	(%r8,%rcx), %rbx
	cmpq	$499992, %rbx
	jbe	.LBB17_11
	xorl	%ebp, %ebp
	jmp	.LBB17_12
	.p2align	4
.LBB17_11:
	movq	-7(%rax,%rcx), %rbp
	bswapq	%rbp
.LBB17_12:
	leaq	(%r12,%rcx), %rbx
	cmpq	$-9, %rbx
	ja	.LBB17_221
	cmpq	$499992, %rbx
	ja	.LBB17_14
	movq	-7(%r14,%rcx), %rbx
	bswapq	%rbx
	cmpq	%rbx, %rbp
	je	.LBB17_15
.LBB17_25:
	xorq	%rbp, %rbx
	bsrq	%rbx, %rax
	xorl	$56, %eax
	shrl	$3, %eax
	orq	%rcx, %rax
	movq	%r10, %rbp
	cmpq	%rbp, %rax
	jbe	.LBB17_30
	jmp	.LBB17_26
	.p2align	4
.LBB17_18:
	movq	24(%rsp), %rcx
	movq	%rcx, %rax
	cmpq	%r11, %rcx
	movq	%r10, %rbp
	je	.LBB17_24
	.p2align	4
.LBB17_19:
	leaq	(%rax,%r8), %rdi
	cmpq	$499999, %rdi
	ja	.LBB17_222
	movq	%rax, %rcx
	addq	%r12, %rcx
	jb	.LBB17_224
	cmpq	$500000, %rcx
	jae	.LBB17_223
	movzbl	(%r15,%rdi), %edi
	movzbl	(%r15,%rcx), %ecx
	xorl	%ebx, %ebx
	cmpb	%cl, %dil
	sete	%bl
	addq	%rbx, %rax
	cmpb	%cl, %dil
	jne	.LBB17_24
	cmpq	%r11, %rax
	jb	.LBB17_19
	.p2align	4
.LBB17_24:
	cmpq	%rbp, %rax
	jbe	.LBB17_30
.LBB17_26:
	cmpq	32(%rsp), %rax
	jae	.LBB17_126
	movq	%rax, %rcx
	addq	%r12, %rcx
	jb	.LBB17_232
	cmpq	$500000, %rcx
	jae	.LBB17_126
	movzbl	(%r15,%rcx), %esi
	movq	%r13, 8(%rsp)
	movq	%rax, %rbp
.LBB17_30:
	movl	%r8d, %eax
	andl	$32767, %eax
	movl	136(%rsp,%rax,4), %eax
	cmpq	%rax, %r8
	jbe	.LBB17_32
	movq	%rax, %r8
	decq	%rdx
	jne	.LBB17_6
	.p2align	4
.LBB17_32:
	movq	8(%rsp), %rax
	testq	%rax, %rax
	je	.LBB17_127
.LBB17_33:
	movq	%r12, %r10
	movq	%rax, %rdx
	movq	%rbp, %r8
	cmpq	$31, %rbp
	movq	16(%rsp), %rsi
	movq	40(%rsp), %r11
	ja	.LBB17_149
.LBB17_34:
	cmpq	$499991, %r12
	jae	.LBB17_144
	movq	%rax, 8(%rsp)
	leaq	1(%r12), %r10
	movzbl	1(%r15,%r12), %eax
	movl	%eax, 56(%rsp)
	shll	$24, %eax
	movzbl	2(%r15,%r12), %r9d
	movl	%r9d, %ecx
	shll	$16, %ecx
	orl	%eax, %ecx
	movzbl	3(%r15,%r12), %ebx
	movl	%ebx, %eax
	shll	$8, %eax
	orl	%ecx, %eax
	movzbl	4(%r15,%r12), %r14d
	orq	%r14, %rax
	movabsq	$-7046029254386353131, %rcx
	imulq	%rcx, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %r13d
	movl	%r10d, %ecx
	andl	$32767, %ecx
	movl	%r13d, 136(%rsp,%rcx,4)
	leaq	-1(%rbp), %rcx
	cmpq	$4, %rcx
	movl	$3, %edx
	movq	%rcx, 40(%rsp)
	cmovaeq	%rcx, %rdx
	movl	%r10d, 131208(%rsp,%rax,4)
	movl	$499999, %eax
	subq	%r12, %rax
	cmpq	$258, %rax
	movl	$258, %ecx
	cmovaeq	%rcx, %rax
	leaq	(%rdx,%r10), %rcx
	cmpq	$499999, %rcx
	ja	.LBB17_37
	movzbl	(%r15,%rcx), %ecx
	jmp	.LBB17_38
	.p2align	4
.LBB17_37:
	xorl	%ecx, %ecx
.LBB17_38:
	leaq	2(%r12), %rdi
	movq	%rdi, 64(%rsp)
	movq	%r10, %rdi
	subq	%r13, %rdi
	movq	%rdi, 32(%rsp)
	decq	%rdi
	cmpq	$32767, %rdi
	movq	%rbp, 24(%rsp)
	ja	.LBB17_79
	leaq	(%rdx,%r13), %rdi
	cmpq	$499999, %rdi
	ja	.LBB17_79
	cmpb	%cl, (%r15,%rdi)
	jne	.LBB17_79
	movl	%eax, %ecx
	andl	$504, %ecx
	movq	%rcx, %rsi
	leaq	7(%r15), %rcx
	addq	%r13, %rcx
	movq	%rcx, 80(%rsp)
	leaq	8(%r15), %rcx
	addq	%r12, %rcx
	movq	%rcx, 72(%rsp)
	xorl	%edi, %edi
	movq	%r9, 104(%rsp)
	jmp	.LBB17_43
	.p2align	4
.LBB17_42:
	movq	72(%rsp), %r8
	movq	-7(%r8,%rcx), %r8
	bswapq	%r8
	cmpq	%r8, %rbp
	jne	.LBB17_50
.LBB17_43:
	movq	%rdi, %rcx
	addq	$8, %rdi
	cmpq	%rax, %rdi
	ja	.LBB17_51
	leaq	(%rcx,%r13), %r8
	cmpq	$499992, %r8
	jbe	.LBB17_46
	xorl	%ebp, %ebp
	jmp	.LBB17_47
	.p2align	4
.LBB17_46:
	movq	80(%rsp), %r8
	movq	-7(%r8,%rcx), %rbp
	bswapq	%rbp
.LBB17_47:
	leaq	(%r10,%rcx), %r8
	cmpq	$-9, %r8
	ja	.LBB17_221
	cmpq	$499992, %r8
	jbe	.LBB17_42
	xorl	%r8d, %r8d
	cmpq	%r8, %rbp
	je	.LBB17_43
.LBB17_50:
	xorq	%rbp, %r8
	bsrq	%r8, %r9
	xorl	$56, %r9d
	shrl	$3, %r9d
	orq	%rcx, %r9
	movq	16(%rsp), %rsi
	movq	24(%rsp), %rbp
	movq	%r9, %r13
	cmpq	%rdx, %r9
	movq	104(%rsp), %r9
	ja	.LBB17_57
	jmp	.LBB17_79
.LBB17_51:
	movq	%rsi, %r9
	cmpl	%eax, %r9d
	movq	16(%rsp), %rsi
	movq	24(%rsp), %rbp
	je	.LBB17_56
	.p2align	4
.LBB17_52:
	leaq	(%r9,%r13), %rdi
	cmpq	$500000, %rdi
	jae	.LBB17_222
	leaq	(%r9,%r10), %rcx
	cmpq	$499999, %rcx
	ja	.LBB17_223
	movzbl	(%r15,%rdi), %edi
	movzbl	(%r15,%rcx), %ecx
	xorl	%r8d, %r8d
	cmpb	%cl, %dil
	sete	%r8b
	addq	%r8, %r9
	cmpb	%cl, %dil
	jne	.LBB17_68
	cmpq	%rax, %r9
	movq	16(%rsp), %rsi
	jb	.LBB17_52
.LBB17_56:
	movq	%r9, %r13
	cmpq	%rdx, %r9
	movq	104(%rsp), %r9
	jbe	.LBB17_79
.LBB17_57:
	leaq	-11(%r13), %rcx
	movl	$168, %edi
	cmpq	$247, %rcx
	jae	.LBB17_58
	leal	-3(%r13), %eax
	movl	$63, %r8d
	bsrl	%eax, %r8d
	xorl	$31, %r8d
	shll	$4, %r8d
	movl	$632, %edi
	subl	%r8d, %edi
	movq	32(%rsp), %rax
	cmpq	$4, %rax
	ja	.LBB17_61
.LBB17_59:
	leal	-33554432(%r13), %eax
	cmpl	$-67108864, %eax
	jae	.LBB17_62
	jmp	.LBB17_234
.LBB17_58:
	movq	32(%rsp), %rax
	cmpq	$4, %rax
	jbe	.LBB17_59
.LBB17_61:
	decl	%eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	shll	$4, %eax
	subl	%eax, %edi
	addl	$480, %edi
	leal	-33554432(%r13), %eax
	cmpl	$-67108864, %eax
	jb	.LBB17_234
.LBB17_62:
	movq	%r13, %rsi
	movl	%esi, %eax
	shll	$6, %eax
	movl	%eax, %r8d
	subl	%edi, %r8d
	jo	.LBB17_233
	cmpl	$-999999, %r8d
	movq	16(%rsp), %rsi
	jl	.LBB17_79
	cmpq	$0, 32(%rsp)
	je	.LBB17_79
	movl	$168, %edi
	cmpq	$247, %rcx
	jae	.LBB17_66
	leal	-3(%r13), %ecx
	movl	$63, %r8d
	bsrl	%ecx, %r8d
	xorl	$31, %r8d
	shll	$4, %r8d
	movl	$632, %edi
	subl	%r8d, %edi
	movq	16(%rsp), %rsi
	movq	32(%rsp), %rcx
	cmpq	$4, %rcx
	ja	.LBB17_70
.LBB17_67:
	movq	8(%rsp), %r8
	subl	%edi, %eax
	jno	.LBB17_71
	jmp	.LBB17_233
.LBB17_66:
	movq	32(%rsp), %rcx
	cmpq	$4, %rcx
	jbe	.LBB17_67
.LBB17_70:
	decl	%ecx
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %edi
	addl	$480, %edi
	movq	8(%rsp), %r8
	subl	%edi, %eax
	jo	.LBB17_233
.LBB17_71:
	leaq	-11(%rbp), %rdi
	movl	$168, %ecx
	cmpq	$247, %rdi
	jae	.LBB17_73
	leal	-3(%rbp), %ecx
	movl	$63, %edi
	bsrl	%ecx, %edi
	xorl	$31, %edi
	shll	$4, %edi
	movl	$632, %ecx
	subl	%edi, %ecx
.LBB17_73:
	cmpq	$4, %r8
	jbe	.LBB17_76
	leal	-1(%r8), %edi
	cmpl	$1, %edi
	jbe	.LBB17_240
	bsrl	%edi, %edi
	xorl	$31, %edi
	shll	$4, %edi
	subl	%edi, %ecx
	addl	$480, %ecx
.LBB17_76:
	movl	%ebp, %edi
	shll	$6, %edi
	subl	%ecx, %edi
	cmpl	%edi, %eax
	jle	.LBB17_79
	cmpq	%rsi, %r11
	jae	.LBB17_235
	movzbl	(%r15,%r12), %ecx
	movl	$1, %eax
	movq	%r11, %rdi
	movq	64(%rsp), %r9
	movq	%r13, %r8
	jmp	.LBB17_125
.LBB17_68:
	movq	16(%rsp), %rsi
	movq	%r9, %r13
	cmpq	%rdx, %r9
	movq	104(%rsp), %r9
	ja	.LBB17_57
	.p2align	4
.LBB17_79:
	cmpq	$499990, %r12
	je	.LBB17_145
	movq	%r11, %r13
	shll	$24, %r9d
	shll	$16, %ebx
	orl	%r9d, %ebx
	shll	$8, %r14d
	orl	%ebx, %r14d
	movzbl	5(%r15,%r12), %eax
	orq	%r14, %rax
	movabsq	$-7046029254386353131, %rcx
	imulq	%rcx, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %r11d
	leaq	2(%r12), %rsi
	movl	%esi, %ecx
	andl	$32767, %ecx
	movl	%r11d, 136(%rsp,%rcx,4)
	movl	%esi, 131208(%rsp,%rax,4)
	leaq	3(%r12), %r9
	movl	$499998, %eax
	subq	%r12, %rax
	cmpq	%rax, 40(%rsp)
	jae	.LBB17_147
	cmpq	$258, %rax
	movl	$258, %ecx
	cmovaeq	%rcx, %rax
	leaq	(%rdx,%rsi), %rcx
	cmpq	$499999, %rcx
	ja	.LBB17_83
	movzbl	(%r15,%rcx), %ecx
	subq	%r11, %rsi
	leaq	-1(%rsi), %rdi
	cmpq	$32767, %rdi
	jbe	.LBB17_84
	jmp	.LBB17_134
	.p2align	4
.LBB17_83:
	xorl	%ecx, %ecx
	subq	%r11, %rsi
	leaq	-1(%rsi), %rdi
	cmpq	$32767, %rdi
	ja	.LBB17_134
.LBB17_84:
	leaq	(%rdx,%r11), %rdi
	cmpq	$499999, %rdi
	ja	.LBB17_134
	cmpb	%cl, (%r15,%rdi)
	jne	.LBB17_134
	movq	%rsi, %rbp
	movl	%eax, %r10d
	andl	$504, %r10d
	leaq	7(%r15), %rcx
	leaq	(%rcx,%r11), %rdi
	leaq	9(%r15), %rcx
	leaq	(%rcx,%r12), %rbx
	movq	$-8, %rcx
	jmp	.LBB17_88
	.p2align	4
.LBB17_87:
	movq	1(%rbx,%rcx), %r8
	bswapq	%r8
	addq	$8, %rcx
	cmpq	%r8, %r14
	jne	.LBB17_95
.LBB17_88:
	leaq	16(%rcx), %r8
	cmpq	%rax, %r8
	ja	.LBB17_96
	leaq	(%r11,%rcx), %r8
	addq	$8, %r8
	cmpq	$499992, %r8
	jbe	.LBB17_91
	xorl	%r14d, %r14d
	jmp	.LBB17_92
	.p2align	4
.LBB17_91:
	movq	1(%rdi,%rcx), %r14
	bswapq	%r14
.LBB17_92:
	leaq	(%r12,%rcx), %r8
	addq	$10, %r8
	cmpq	$-9, %r8
	ja	.LBB17_221
	cmpq	$499992, %r8
	jbe	.LBB17_87
	xorl	%r8d, %r8d
	addq	$8, %rcx
	cmpq	%r8, %r14
	je	.LBB17_88
.LBB17_95:
	xorq	%r14, %r8
	bsrq	%r8, %r10
	xorl	$56, %r10d
	shrl	$3, %r10d
	orq	%rcx, %r10
	leaq	2(%r12), %r14
	jmp	.LBB17_101
	.p2align	4
.LBB17_96:
	cmpl	%eax, %r10d
	leaq	2(%r12), %r14
	je	.LBB17_101
	.p2align	4
.LBB17_97:
	leaq	(%r10,%r11), %rdi
	cmpq	$500000, %rdi
	jae	.LBB17_222
	leaq	(%r10,%r14), %rcx
	cmpq	$499999, %rcx
	ja	.LBB17_223
	movzbl	(%r15,%rdi), %edi
	movzbl	(%r15,%rcx), %ecx
	xorl	%r8d, %r8d
	cmpb	%cl, %dil
	sete	%r8b
	addq	%r8, %r10
	cmpb	%cl, %dil
	jne	.LBB17_101
	cmpq	%rax, %r10
	jb	.LBB17_97
	.p2align	4
.LBB17_101:
	cmpq	%rdx, %r10
	jbe	.LBB17_134
	leaq	-11(%r10), %rcx
	movl	$168, %eax
	cmpq	$247, %rcx
	movq	16(%rsp), %rsi
	movq	%r13, %r11
	jae	.LBB17_103
	leal	-3(%r10), %eax
	movl	$63, %ecx
	bsrl	%eax, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	movl	$632, %eax
	subl	%ecx, %eax
	cmpq	$4, %rbp
	movq	8(%rsp), %rbx
	ja	.LBB17_106
.LBB17_104:
	leal	-33554432(%r10), %ecx
	cmpl	$-67108864, %ecx
	jae	.LBB17_107
	jmp	.LBB17_234
	.p2align	4
.LBB17_103:
	cmpq	$4, %rbp
	movq	8(%rsp), %rbx
	jbe	.LBB17_104
.LBB17_106:
	leal	-1(%rbp), %ecx
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %eax
	addl	$480, %eax
	leal	-33554432(%r10), %ecx
	cmpl	$-67108864, %ecx
	jb	.LBB17_234
.LBB17_107:
	movl	%r10d, %ecx
	shll	$6, %ecx
	subl	%eax, %ecx
	jo	.LBB17_233
	cmpl	$-999999, %ecx
	movl	$0, %eax
	cmovlq	%rax, %rbp
	cmovgeq	%r10, %rdx
	movq	%rbp, 32(%rsp)
	testq	%rbp, %rbp
	je	.LBB17_196
	cmpq	$4, %rdx
	movq	24(%rsp), %r8
	jb	.LBB17_143
	leaq	-11(%rdx), %rax
	movl	$168, %ecx
	cmpq	$247, %rax
	jae	.LBB17_111
	leal	-3(%rdx), %eax
	movl	$63, %edi
	bsrl	%eax, %edi
	xorl	$31, %edi
	shll	$4, %edi
	movl	$632, %ecx
	subl	%edi, %ecx
	movq	32(%rsp), %rax
	cmpq	$4, %rax
	ja	.LBB17_114
.LBB17_112:
	leal	-33554432(%rdx), %eax
	cmpl	$-67108864, %eax
	jae	.LBB17_115
	jmp	.LBB17_234
	.p2align	4
.LBB17_111:
	movq	32(%rsp), %rax
	cmpq	$4, %rax
	jbe	.LBB17_112
.LBB17_114:
	decl	%eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	shll	$4, %eax
	subl	%eax, %ecx
	addl	$480, %ecx
	leal	-33554432(%rdx), %eax
	cmpl	$-67108864, %eax
	jb	.LBB17_234
.LBB17_115:
	movl	%edx, %eax
	shll	$6, %eax
	subl	%ecx, %eax
	jo	.LBB17_233
	leaq	-11(%r8), %rdi
	movl	$168, %ecx
	cmpq	$247, %rdi
	jae	.LBB17_118
	leal	-3(%r8), %ecx
	movl	$63, %edi
	bsrl	%ecx, %edi
	xorl	$31, %edi
	shll	$4, %edi
	movl	$632, %ecx
	subl	%edi, %ecx
.LBB17_118:
	cmpq	$4, %rbx
	jbe	.LBB17_121
	leal	-1(%rbx), %edi
	cmpl	$1, %edi
	jbe	.LBB17_240
	bsrl	%edi, %edi
	xorl	$31, %edi
	shll	$4, %edi
	subl	%edi, %ecx
	addl	$480, %ecx
.LBB17_121:
	movl	%r8d, %edi
	shll	$6, %edi
	orl	$40, %edi
	subl	%ecx, %edi
	cmpl	%edi, %eax
	jle	.LBB17_143
	cmpq	%rsi, %r11
	jae	.LBB17_235
	movzbl	(%r15,%r12), %eax
	movq	48(%rsp), %rcx
	movl	%eax, (%rcx,%r11,4)
	leaq	1(%r11), %rdi
	movl	$2, %eax
	cmpq	%rsi, %rdi
	jae	.LBB17_236
	movq	%r14, %r10
	movq	%rdx, %r8
	movl	56(%rsp), %ecx
.LBB17_125:
	movzbl	%cl, %ecx
	movq	48(%rsp), %rdx
	movl	%ecx, (%rdx,%rdi,4)
	addq	%rax, %r11
	movq	%r8, %rbp
	movq	32(%rsp), %rdx
	movq	%rdx, %rax
	movq	%r10, %r12
	cmpq	$32, %r8
	jb	.LBB17_34
	jmp	.LBB17_149
.LBB17_126:
	movq	%rax, %rbp
	movq	%r13, 8(%rsp)
	movq	8(%rsp), %rax
	testq	%rax, %rax
	jne	.LBB17_33
	.p2align	4
.LBB17_127:
	movq	16(%rsp), %rax
	movq	40(%rsp), %r8
	movq	%rax, %rsi
	cmpq	%rax, %r8
	jae	.LBB17_241
	movd	%xmm1, %eax
	movzbl	%al, %eax
	movq	48(%rsp), %rcx
	movl	%eax, (%rcx,%r8,4)
	movq	56(%rsp), %rbx
	incq	%rbx
	movabsq	$-7046029254386353131, %r10
	je	.LBB17_242
	movq	%rbx, %rcx
	shrq	$5, %rcx
	leaq	1(%r8), %r11
	testq	%rcx, %rcx
	je	.LBB17_133
	cmpq	$499990, %r12
	ja	.LBB17_133
	cmpq	$1000000, %rcx
	movl	$1000000, %edx
	cmovaeq	%rdx, %rcx
	leaq	-1(%rcx), %rdx
	movl	$499990, %edi
	subq	%r12, %rdi
	cmpq	%rdi, %rdx
	cmovbq	%rdx, %rdi
	movq	%r8, %r10
	notq	%r10
	addq	%rsi, %r10
	cmpq	%r10, %rdi
	cmovbq	%rdi, %r10
	incq	%r10
	cmpq	$8, %r10
	ja	.LBB17_135
	movq	%r9, %rdx
	jmp	.LBB17_137
.LBB17_134:
	movq	%r12, %r10
	movq	8(%rsp), %rdx
	movq	24(%rsp), %r8
	jmp	.LBB17_148
.LBB17_135:
	movl	%r10d, %edx
	andl	$7, %edx
	movl	$8, %edi
	cmoveq	%rdi, %rdx
	subq	%rdx, %r10
	addq	%r10, %r11
	leaq	(%r9,%r10), %rdx
	subq	%r10, %rcx
	movq	96(%rsp), %rdi
	leaq	(%rdi,%r8,4), %rdi
	leaq	5(%r15), %r8
	addq	%r8, %r12
	xorl	%r8d, %r8d
	.p2align	4
.LBB17_136:
	movd	-4(%r12,%r8), %xmm1
	movd	(%r12,%r8), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%rdi,%r8,4)
	movdqu	%xmm2, (%rdi,%r8,4)
	addq	$8, %r8
	cmpq	%r8, %r10
	jne	.LBB17_136
.LBB17_137:
	decq	%rcx
	movabsq	$-7046029254386353131, %r10
	movq	%rsi, %r14
	.p2align	4
.LBB17_138:
	cmpq	%r11, %r14
	je	.LBB17_225
	movzbl	(%r15,%rdx), %edi
	movq	48(%rsp), %r8
	movl	%edi, (%r8,%r11,4)
	leaq	1(%rdx), %r12
	incq	%r11
	addq	$-1, %rcx
	jae	.LBB17_141
	cmpq	$499991, %rdx
	movq	%r12, %rdx
	movq	%rsi, %r14
	jb	.LBB17_138
	jmp	.LBB17_142
.LBB17_143:
	movq	%r12, %r10
	movq	%rbx, %rdx
	leaq	-1(%r11), %rbx
	cmpq	%rsi, %rbx
	jb	.LBB17_150
	jmp	.LBB17_197
.LBB17_144:
	movq	%r12, %r10
	movq	%rax, %rdx
	jmp	.LBB17_146
.LBB17_145:
	movl	$499990, %r10d
	movq	64(%rsp), %r9
	movq	8(%rsp), %rdx
.LBB17_146:
	movq	%rbp, %r8
	leaq	-1(%r11), %rbx
	cmpq	%rsi, %rbx
	jb	.LBB17_150
	jmp	.LBB17_197
.LBB17_147:
	movq	%r12, %r10
	movq	8(%rsp), %rdx
	movq	%rbp, %r8
.LBB17_148:
	movq	16(%rsp), %rsi
	movq	%r13, %r11
.LBB17_149:
	leaq	-1(%r11), %rbx
	cmpq	%rsi, %rbx
	jae	.LBB17_197
.LBB17_150:
	cmpq	$257, %r8
	ja	.LBB17_197
	cmpq	%r10, %rdx
	jae	.LBB17_197
	movq	%rdx, %rax
	negq	%rax
	movq	%rax, 80(%rsp)
	leaq	-3(%r15), %rax
	subq	%rdx, %rax
	movq	%rax, 72(%rsp)
	xorl	%r14d, %r14d
	movq	%r10, %r12
	movq	%rdx, 32(%rsp)
	.p2align	4
.LBB17_153:
	movq	48(%rsp), %rax
	movl	(%rax,%rbx,4), %eax
	cmpq	$256, %rax
	jae	.LBB17_158
	leaq	-1(%r12), %rdi
	cmpq	$499999, %rdi
	ja	.LBB17_227
	movq	%rdi, %rcx
	subq	%rdx, %rcx
	cmpq	$500000, %rcx
	jae	.LBB17_226
	movzbl	(%r15,%rdi), %eax
	movl	$16, %r10d
	cmpb	(%r15,%rcx), %al
	jne	.LBB17_192
	incq	%r8
	incq	%r14
	movq	%rdi, %r12
	movq	%r14, %r10
.LBB17_191:
	movq	%rbx, %r11
	jmp	.LBB17_192
	.p2align	4
.LBB17_158:
	movl	$16, %r10d
	cmpl	$16777215, %eax
	jbe	.LBB17_192
	movzbl	%al, %r13d
	leaq	(%r8,%r13), %rcx
	addq	$3, %rcx
	cmpq	$258, %rcx
	ja	.LBB17_192
	addq	$3, %r13
	movq	%r12, %rdi
	subq	%r13, %rdi
	jb	.LBB17_192
	movq	%rdi, %rbp
	subq	%rdx, %rbp
	movq	%rbp, 24(%rsp)
	jb	.LBB17_192
	movq	%rdi, 40(%rsp)
	movq	%rcx, 64(%rsp)
	movq	%r8, 56(%rsp)
	movl	%r13d, %ebp
	andl	$-8, %ebp
	movzbl	%al, %edi
	movq	%r12, %rcx
	subq	%rdi, %rcx
	movq	72(%rsp), %rax
	addq	%rcx, %rax
	movq	%rax, 8(%rsp)
	movq	80(%rsp), %rax
	addq	%r12, %rax
	subq	%rdi, %rax
	movl	$8, %edi
	movq	%r11, %rdx
	jmp	.LBB17_165
	.p2align	4
.LBB17_163:
	leaq	(%r15,%rcx), %rsi
	movq	-11(%rsi,%rdi), %r11
	bswapq	%r11
.LBB17_164:
	addq	$8, %rdi
	cmpq	%r11, %r8
	movq	16(%rsp), %rsi
	movq	%rdx, %r11
	jne	.LBB17_187
.LBB17_165:
	cmpq	%r13, %rdi
	ja	.LBB17_173
	leaq	(%rax,%rdi), %r8
	addq	$-11, %r8
	cmpq	$-9, %r8
	ja	.LBB17_221
	cmpq	$499992, %r8
	jbe	.LBB17_169
	xorl	%r8d, %r8d
	jmp	.LBB17_170
	.p2align	4
.LBB17_169:
	movq	8(%rsp), %rsi
	movq	-8(%rsi,%rdi), %r8
	bswapq	%r8
.LBB17_170:
	leaq	(%rcx,%rdi), %r11
	addq	$-11, %r11
	cmpq	$-9, %r11
	ja	.LBB17_221
	cmpq	$499992, %r11
	jbe	.LBB17_163
	xorl	%r11d, %r11d
	jmp	.LBB17_164
.LBB17_173:
	cmpl	%r13d, %ebp
	movq	32(%rsp), %rdx
	je	.LBB17_190
	movq	%rbp, %rax
	addq	24(%rsp), %rax
	jb	.LBB17_243
	cmpq	$-9, %rax
	ja	.LBB17_243
	cmpq	$499993, %rax
	jae	.LBB17_180
	movq	%rbp, %rdi
	addq	40(%rsp), %rdi
	jb	.LBB17_245
	cmpq	$-9, %rdi
	ja	.LBB17_245
	cmpq	$499992, %rdi
	jbe	.LBB17_188
	.p2align	4
.LBB17_180:
	movq	%rbp, %rdi
	addq	24(%rsp), %rdi
	jb	.LBB17_229
	cmpq	$500000, %rdi
	jae	.LBB17_230
	movq	%rbp, %rcx
	addq	40(%rsp), %rcx
	jb	.LBB17_228
	cmpq	$500000, %rcx
	jae	.LBB17_231
	movzbl	(%r15,%rdi), %eax
	movzbl	(%r15,%rcx), %ecx
	xorl	%edi, %edi
	cmpb	%cl, %al
	sete	%r8b
	jne	.LBB17_186
	movb	%r8b, %dil
	addq	%rdi, %rbp
	cmpq	%r13, %rbp
	jb	.LBB17_180
.LBB17_186:
	cmpb	%cl, %al
	movq	56(%rsp), %r8
	jne	.LBB17_192
	jmp	.LBB17_190
.LBB17_187:
	movq	32(%rsp), %rdx
	movq	56(%rsp), %r8
	.p2align	4
.LBB17_192:
	cmpq	$15, %r10
	ja	.LBB17_198
	leaq	-1(%r11), %rbx
	cmpq	%rsi, %rbx
	jae	.LBB17_198
	cmpq	$257, %r8
	ja	.LBB17_198
	movq	%r10, %r14
	cmpq	%r12, %rdx
	jb	.LBB17_153
	jmp	.LBB17_198
.LBB17_188:
	leal	(,%r13,8), %ecx
	andl	$56, %ecx
	je	.LBB17_246
	movq	(%r15,%rdi), %rdi
	xorq	(%r15,%rax), %rdi
	bswapq	%rdi
	negb	%cl
	shrq	%cl, %rdi
	testq	%rdi, %rdi
	movq	56(%rsp), %r8
	jne	.LBB17_192
.LBB17_190:
	incq	%r14
	movq	40(%rsp), %r12
	movq	%r14, %r10
	movq	64(%rsp), %r8
	jmp	.LBB17_191
.LBB17_196:
	movq	%r12, %r10
	movq	%rbx, %rdx
	movq	24(%rsp), %r8
	leaq	-1(%r11), %rbx
	cmpq	%rsi, %rbx
	jb	.LBB17_150
	.p2align	4
.LBB17_197:
	movq	%r10, %r12
.LBB17_198:
	cmpq	%rsi, %r11
	movabsq	$-7046029254386353131, %r10
	jae	.LBB17_237
	shll	$8, %edx
	leal	(%rdx,%r8), %eax
	addl	$16776957, %eax
	movq	48(%rsp), %rcx
	movl	%eax, (%rcx,%r11,4)
	addq	%r8, %r12
	jb	.LBB17_238
	leaq	16(%r9), %rax
	cmpq	%rax, %r12
	cmovbq	%r12, %rax
	cmpq	$499992, %rax
	movl	$499992, %ecx
	cmovaeq	%rcx, %rax
	cmpq	%rax, %r9
	jae	.LBB17_203
	.p2align	4
.LBB17_201:
	movl	(%r15,%r9), %ecx
	bswapl	%ecx
	imulq	%r10, %rcx
	shrq	$48, %rcx
	movl	131208(%rsp,%rcx,4), %edx
	movl	%r9d, %edi
	andl	$32767, %edi
	movl	%edx, 136(%rsp,%rdi,4)
	movl	%r9d, 131208(%rsp,%rcx,4)
	incq	%r9
	cmpq	%r9, %rax
	jne	.LBB17_201
	movq	%rax, %r9
.LBB17_203:
	movq	%r12, %rax
	subq	$8, %rax
	movl	$0, %ecx
	cmovaeq	%rax, %rcx
	cmpq	$499992, %rcx
	movl	$499992, %eax
	cmovaeq	%rax, %rcx
	cmpq	%rcx, %r9
	jae	.LBB17_206
	.p2align	4
.LBB17_204:
	leaq	4(%r9), %rax
	movl	(%r15,%r9), %edx
	bswapl	%edx
	imulq	%r10, %rdx
	shrq	$48, %rdx
	movl	131208(%rsp,%rdx,4), %edi
	movl	%r9d, 131208(%rsp,%rdx,4)
	andl	$32767, %r9d
	movl	%edi, 136(%rsp,%r9,4)
	movq	%rax, %r9
	cmpq	%rcx, %rax
	jb	.LBB17_204
	leaq	4(%rax), %rcx
	cmpq	%r12, %rcx
	jb	.LBB17_207
	jmp	.LBB17_209
	.p2align	4
.LBB17_206:
	movq	%r9, %rax
	leaq	4(%rax), %rcx
	cmpq	%r12, %rcx
	jae	.LBB17_209
.LBB17_207:
	cmpq	$4, %r12
	jb	.LBB17_244
	leaq	-4(%r12), %rax
.LBB17_209:
	cmpq	$499992, %r12
	movl	$499992, %ecx
	cmovbq	%r12, %rcx
	cmpq	%rcx, %rax
	jae	.LBB17_211
	.p2align	4
.LBB17_210:
	movl	(%r15,%rax), %edx
	bswapl	%edx
	imulq	%r10, %rdx
	shrq	$48, %rdx
	movl	131208(%rsp,%rdx,4), %r8d
	movl	%eax, %edi
	andl	$32767, %edi
	movl	%r8d, 136(%rsp,%rdi,4)
	movl	%eax, 131208(%rsp,%rdx,4)
	incq	%rax
	cmpq	%rcx, %rax
	jb	.LBB17_210
.LBB17_211:
	incq	%r11
	cmpq	%r12, %rax
	cmovbeq	%r12, %rax
	movq	%rax, %r9
	xorl	%ebx, %ebx
	movq	%rsi, %r14
	cmpq	$499991, %r12
	jbe	.LBB17_212
.LBB17_213:
	cmpq	$499999, %r12
	ja	.LBB17_220
	cmpq	%r14, %r11
	movq	%r14, %rdi
	cmovaq	%r11, %rdi
	movq	%rdi, %rcx
	subq	%r11, %rcx
	movl	$499999, %eax
	subq	%r12, %rax
	cmpq	%rax, %rcx
	cmovbq	%rcx, %rax
	cmpq	$7, %rax
	jbe	.LBB17_217
	incq	%rax
	movl	%eax, %ecx
	andl	$7, %ecx
	movl	$8, %edx
	cmovneq	%rcx, %rdx
	subq	%rdx, %rax
	movq	48(%rsp), %rcx
	leaq	(%rcx,%r11,4), %rcx
	addq	$16, %rcx
	addq	%rax, %r11
	leaq	(%r15,%r12), %rdx
	addq	$4, %rdx
	addq	%rax, %r12
	xorl	%r8d, %r8d
	pxor	%xmm0, %xmm0
	.p2align	4
.LBB17_216:
	movd	-4(%rdx,%r8), %xmm1
	movd	(%rdx,%r8), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%rcx,%r8,4)
	movdqu	%xmm2, (%rcx,%r8,4)
	addq	$8, %r8
	cmpq	%r8, %rax
	jne	.LBB17_216
.LBB17_217:
	movq	48(%rsp), %rcx
	.p2align	4
.LBB17_218:
	cmpq	%r11, %rdi
	je	.LBB17_239
	movzbl	(%r15,%r12), %eax
	movl	%eax, (%rcx,%r11,4)
	incq	%r11
	incq	%r12
	cmpq	$500000, %r12
	jne	.LBB17_218
.LBB17_220:
	movq	%r11, %rax
	addq	$393352, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.LBB17_221:
	.cfi_def_cfa_offset 393408
	leaq	.Lalloc_bb314acf14069c2fbedf530b060ebd60(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_222:
	leaq	.Lalloc_333f7815cbdde125b13aaef2eac5916c(%rip), %rdx
	movl	$500000, %esi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_223:
	leaq	.Lalloc_c7b835eab7e4664f8dc21896c854bf2b(%rip), %rdx
	movl	$500000, %esi
	movq	%rcx, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_224:
	leaq	.Lalloc_44247feb933c63f72105b72612a623ee(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_225:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	movq	%r14, %rdi
	movq	%r14, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_226:
	leaq	.Lalloc_a470f1791914be2ed9860c28a94823b8(%rip), %rdx
	movl	$500000, %esi
	movq	%rcx, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_227:
	leaq	.Lalloc_1f28cc27fa9e18e58cef417bee4fd90b(%rip), %rdx
	movl	$500000, %esi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_228:
	leaq	.Lalloc_0dafef88f4ad7c766190399efdbc2565(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_229:
	leaq	.Lalloc_f491bec5a0814d991fa65b29bceb4569(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_230:
	leaq	.Lalloc_6423c6cb6214cc14d5219f2068f396e1(%rip), %rdx
	movl	$500000, %esi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_231:
	leaq	.Lalloc_6298bd754cf21e84e6b31996eea28f6b(%rip), %rdx
	movl	$500000, %esi
	movq	%rcx, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_232:
	leaq	.Lalloc_5082c7ce777234b7475a595bf60db7a2(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_233:
	leaq	.Lalloc_72bac528c0514d634dbb2acaf4e914ed(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB17_234:
	leaq	.Lalloc_72bac528c0514d634dbb2acaf4e914ed(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow@GOTPCREL(%rip)
.LBB17_235:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	movq	%r11, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_236:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_237:
	leaq	.Lalloc_950cb3d32dbfbf973f57d9a20abe6695(%rip), %rdx
	movq	%r11, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_238:
	leaq	.Lalloc_dc5ae93321079a7792fc0613ca37a43e(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_239:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	movq	%r14, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_240:
	leaq	.Lalloc_cc8257d2c78dd28d3d4ac89f580613b9(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB17_241:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	movq	%r8, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_242:
	leaq	.Lalloc_6c101138787766aed78cb0daf47995e1(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_243:
	leaq	.Lalloc_410f560b7db958092bd73a0bb4ae0379(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_244:
	leaq	.Lalloc_30e260b757f13d4a959ad3a108dff26e(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB17_245:
	leaq	.Lalloc_25f0ab118ce3ac29922df37c6b354aae(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_246:
	leaq	.Lalloc_0d9222021d7218fa4f635bbfc4f9297d(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow@GOTPCREL(%rip)
.Lfunc_end17:
	.size	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2, .Lfunc_end17-_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2
	.cfi_endproc
