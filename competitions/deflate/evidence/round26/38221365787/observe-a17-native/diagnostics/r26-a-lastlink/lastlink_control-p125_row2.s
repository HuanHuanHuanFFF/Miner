
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
	movq	%rdx, %r13
	movq	%rsi, %r14
	movq	%rdi, %r15
	movabsq	$-7046029254386353131, %r12
	leaq	131208(%rsp), %rdi
	movq	$0, 8(%rsp)
	movq	memset@GOTPCREL(%rip), %rbx
	movl	$262144, %edx
	xorl	%esi, %esi
	callq	*%rbx
	leaq	136(%rsp), %rdi
	movl	$131072, %edx
	xorl	%esi, %esi
	callq	*%rbx
	movq	%r14, %r10
	leaq	20(%r14), %rax
	movq	%rax, 88(%rsp)
	movl	$500016, %ebx
	pxor	%xmm0, %xmm0
	xorl	%r14d, %r14d
	xorl	%edx, %edx
	xorl	%r9d, %r9d
	movq	%r13, 48(%rsp)
	movq	%r10, 32(%rsp)
	jmp	.LBB17_3
.LBB17_138:
	movq	%r9, %rdx
.LBB17_146:
	cmpq	%rdx, %r9
	cmovbeq	%rdx, %r9
	movq	%rax, 8(%rsp)
	cmpq	$499991, %rdx
	ja	.LBB17_216
.LBB17_215:
	testq	%rbx, %rbx
	je	.LBB17_216
.LBB17_3:
	movq	%r14, 56(%rsp)
	cmpq	%rdx, %r9
	jae	.LBB17_5
	.p2align	4
.LBB17_4:
	movl	(%r15,%r9), %eax
	bswapl	%eax
	imulq	%r12, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %ecx
	movl	%r9d, %esi
	andl	$32767, %esi
	movl	%ecx, 136(%rsp,%rsi,4)
	movl	%r9d, 131208(%rsp,%rax,4)
	incq	%r9
	cmpq	%r9, %rdx
	jne	.LBB17_4
.LBB17_5:
	decq	%rbx
	movq	%rbx, 80(%rsp)
	movl	(%r15,%rdx), %eax
	movd	%eax, %xmm1
	movdqa	%xmm1, 112(%rsp)
	movzbl	115(%rsp), %r11d
	bswapl	%eax
	imulq	%r12, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %esi
	movl	%edx, %ecx
	andl	$32767, %ecx
	movl	%esi, 136(%rsp,%rcx,4)
	movl	%edx, 131208(%rsp,%rax,4)
	leaq	1(%rdx), %r9
	movl	$500000, %ecx
	subq	%rdx, %rcx
	cmpq	$258, %rcx
	movl	$258, %ebx
	cmovbq	%rcx, %rbx
	cmpq	$64, %rcx
	movl	$64, %eax
	cmovaeq	%rax, %rcx
	movq	%rcx, 24(%rsp)
	movl	%ebx, %eax
	andl	$504, %eax
	movq	%rax, 40(%rsp)
	leaq	7(%r15), %rax
	leaq	(%rax,%rdx), %r13
	movl	$6, %ebp
	movl	$3, %r14d
	movq	$0, 16(%rsp)
	.p2align	4
.LBB17_6:
	movq	%rdx, %r8
	subq	%rsi, %r8
	leaq	-1(%r8), %rax
	cmpq	$32767, %rax
	ja	.LBB17_33
	leaq	(%rsi,%r14), %rax
	cmpq	$499999, %rax
	ja	.LBB17_33
	cmpb	%r11b, (%r15,%rax)
	jne	.LBB17_26
	movq	%r14, %r10
	leaq	7(%r15), %rax
	leaq	(%rax,%rsi), %rdi
	xorl	%r12d, %r12d
	jmp	.LBB17_15
	.p2align	4
.LBB17_14:
	xorl	%r14d, %r14d
	cmpq	%r14, %rcx
	jne	.LBB17_28
.LBB17_15:
	movq	%r12, %rax
	addq	$8, %r12
	cmpq	%rbx, %r12
	ja	.LBB17_19
	leaq	(%rsi,%rax), %rcx
	cmpq	$-9, %rcx
	ja	.LBB17_224
	cmpq	$499992, %rcx
	jbe	.LBB17_11
	xorl	%ecx, %ecx
	jmp	.LBB17_12
	.p2align	4
.LBB17_11:
	movq	-7(%rdi,%rax), %rcx
	bswapq	%rcx
.LBB17_12:
	leaq	(%rdx,%rax), %r14
	cmpq	$-9, %r14
	ja	.LBB17_224
	cmpq	$499992, %r14
	ja	.LBB17_14
	movq	-7(%r13,%rax), %r14
	bswapq	%r14
	cmpq	%r14, %rcx
	je	.LBB17_15
.LBB17_28:
	xorq	%rcx, %r14
	bsrq	%r14, %r12
	xorl	$56, %r12d
	shrl	$3, %r12d
	orq	%rax, %r12
	movq	%r10, %r14
	cmpq	%r14, %r12
	ja	.LBB17_29
	.p2align	4
.LBB17_26:
	cmpq	$1, %rbp
	je	.LBB17_33
.LBB17_27:
	movl	%esi, %eax
	andl	$32767, %eax
	movl	136(%rsp,%rax,4), %eax
	decq	%rbp
	cmpq	%rax, %rsi
	cmovaeq	%rax, %rsi
	ja	.LBB17_6
	jmp	.LBB17_33
	.p2align	4
.LBB17_19:
	movq	40(%rsp), %rax
	movq	%rax, %r12
	cmpq	%rbx, %rax
	movq	%r10, %r14
	je	.LBB17_25
	.p2align	4
.LBB17_20:
	leaq	(%r12,%rsi), %rdi
	cmpq	$499999, %rdi
	ja	.LBB17_225
	movq	%r12, %rax
	addq	%rdx, %rax
	jb	.LBB17_227
	cmpq	$500000, %rax
	jae	.LBB17_226
	movzbl	(%r15,%rdi), %ecx
	movzbl	(%r15,%rax), %eax
	xorl	%edi, %edi
	cmpb	%al, %cl
	sete	%dil
	addq	%rdi, %r12
	cmpb	%al, %cl
	jne	.LBB17_25
	cmpq	%rbx, %r12
	jb	.LBB17_20
	.p2align	4
.LBB17_25:
	cmpq	%r14, %r12
	jbe	.LBB17_26
.LBB17_29:
	cmpq	24(%rsp), %r12
	jae	.LBB17_130
	movq	%r12, %rax
	addq	%rdx, %rax
	jb	.LBB17_238
	cmpq	$500000, %rax
	jae	.LBB17_130
	movzbl	(%r15,%rax), %r11d
	movq	%r8, 16(%rsp)
	movq	%r12, %r14
	cmpq	$1, %rbp
	jne	.LBB17_27
	.p2align	4
.LBB17_33:
	movq	16(%rsp), %r12
	testq	%r12, %r12
	movq	32(%rsp), %r10
	je	.LBB17_131
.LBB17_34:
	movq	%rdx, %rbp
	movq	%r14, %rsi
	cmpq	$31, %r14
	movq	48(%rsp), %r13
	movq	8(%rsp), %r11
	ja	.LBB17_150
.LBB17_35:
	leaq	1(%rdx), %rbp
	cmpq	$499992, %rbp
	jae	.LBB17_147
	movzbl	1(%r15,%rdx), %eax
	movl	%eax, 64(%rsp)
	shll	$24, %eax
	movzbl	2(%r15,%rdx), %edi
	movl	%edi, %ecx
	shll	$16, %ecx
	orl	%eax, %ecx
	movzbl	3(%r15,%rdx), %ebx
	movl	%ebx, %eax
	shll	$8, %eax
	orl	%ecx, %eax
	movq	%r14, %rsi
	movzbl	4(%r15,%rdx), %r14d
	orq	%r14, %rax
	movabsq	$-7046029254386353131, %rcx
	imulq	%rcx, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %r9d
	movl	%ebp, %ecx
	andl	$32767, %ecx
	movl	%r9d, 136(%rsp,%rcx,4)
	movq	%rsi, 24(%rsp)
	leaq	-1(%rsi), %rcx
	cmpq	$4, %rcx
	movl	$3, %r8d
	cmovaeq	%rcx, %r8
	movl	%ebp, 131208(%rsp,%rax,4)
	movl	$499999, %r13d
	subq	%rdx, %r13
	cmpq	$258, %r13
	movl	$258, %r12d
	cmovbq	%r13, %r12
	cmpq	$64, %r13
	movl	$64, %eax
	cmovaeq	%rax, %r13
	leaq	(%r8,%rbp), %rax
	cmpq	$500000, %rax
	movq	%r11, 8(%rsp)
	movq	%rdi, 56(%rsp)
	movq	%rcx, 72(%rsp)
	jae	.LBB17_38
	movzbl	(%r15,%rax), %eax
	jmp	.LBB17_39
	.p2align	4
.LBB17_38:
	xorl	%eax, %eax
.LBB17_39:
	leaq	2(%rdx), %r11
	movq	%rbp, %rcx
	subq	%r9, %rcx
	movq	%rcx, 40(%rsp)
	decq	%rcx
	cmpq	$32768, %rcx
	jae	.LBB17_82
	leaq	(%r8,%r9), %rcx
	cmpq	$500000, %rcx
	jae	.LBB17_82
	cmpb	%al, (%r15,%rcx)
	jne	.LBB17_82
	movl	%r12d, %esi
	andl	$504, %esi
	leaq	7(%r15), %rax
	addq	%r9, %rax
	movq	%rax, 104(%rsp)
	leaq	8(%r15), %rax
	addq	%rdx, %rax
	movq	%rax, 96(%rsp)
	xorl	%r10d, %r10d
	jmp	.LBB17_44
	.p2align	4
.LBB17_43:
	movq	96(%rsp), %rcx
	movq	-7(%rcx,%rax), %rcx
	bswapq	%rcx
	cmpq	%rcx, %rdi
	jne	.LBB17_52
.LBB17_44:
	movq	%r10, %rax
	addq	$8, %r10
	cmpq	%r12, %r10
	ja	.LBB17_53
	leaq	(%r9,%rax), %rcx
	cmpq	$499992, %rcx
	jbe	.LBB17_47
	xorl	%edi, %edi
	jmp	.LBB17_48
	.p2align	4
.LBB17_47:
	movq	104(%rsp), %rcx
	movq	-7(%rcx,%rax), %rdi
	bswapq	%rdi
.LBB17_48:
	cmpq	$-1, %rdx
	je	.LBB17_236
	leaq	(%rdx,%rax), %rcx
	incq	%rcx
	cmpq	$-9, %rcx
	ja	.LBB17_224
	cmpq	$499992, %rcx
	jbe	.LBB17_43
	xorl	%ecx, %ecx
	cmpq	%rcx, %rdi
	je	.LBB17_44
.LBB17_52:
	xorq	%rdi, %rcx
	bsrq	%rcx, %rsi
	xorl	$56, %esi
	shrl	$3, %esi
	orq	%rax, %rsi
	movq	32(%rsp), %r10
	jmp	.LBB17_59
.LBB17_53:
	cmpq	%r12, %rsi
	movq	32(%rsp), %r10
	je	.LBB17_59
	.p2align	4
.LBB17_54:
	leaq	(%rsi,%r9), %rdi
	cmpq	$499999, %rdi
	ja	.LBB17_225
	leaq	(%rsi,%rbp), %rax
	cmpq	%rdx, %rax
	jbe	.LBB17_227
	cmpq	$500000, %rax
	jae	.LBB17_226
	movzbl	(%r15,%rdi), %ecx
	movzbl	(%r15,%rax), %eax
	xorl	%edi, %edi
	cmpb	%al, %cl
	sete	%dil
	addq	%rdi, %rsi
	cmpb	%al, %cl
	jne	.LBB17_59
	cmpq	%r12, %rsi
	jb	.LBB17_54
.LBB17_59:
	cmpq	%r8, %rsi
	jbe	.LBB17_82
	leaq	-11(%rsi), %rdi
	movl	$168, %r9d
	cmpq	$247, %rdi
	jae	.LBB17_61
	leal	-3(%rsi), %eax
	movl	$63, %ecx
	bsrl	%eax, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	movl	$632, %r9d
	subl	%ecx, %r9d
	movq	40(%rsp), %rax
	cmpq	$4, %rax
	ja	.LBB17_64
.LBB17_62:
	leal	-33554432(%rsi), %eax
	cmpl	$-67108864, %eax
	jae	.LBB17_65
	jmp	.LBB17_239
.LBB17_61:
	movq	40(%rsp), %rax
	cmpq	$4, %rax
	jbe	.LBB17_62
.LBB17_64:
	decl	%eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	shll	$4, %eax
	subl	%eax, %r9d
	addl	$480, %r9d
	leal	-33554432(%rsi), %eax
	cmpl	$-67108864, %eax
	jb	.LBB17_239
.LBB17_65:
	movl	%esi, %eax
	shll	$6, %eax
	movl	%eax, %ecx
	subl	%r9d, %ecx
	jo	.LBB17_237
	cmpl	$-999999, %ecx
	jl	.LBB17_82
	cmpq	%r13, %rsi
	setae	%cl
	leaq	(%rsi,%rbp), %r9
	cmpq	%rdx, %r9
	seta	%r9b
	orb	%cl, %r9b
	je	.LBB17_238
	cmpq	$0, 40(%rsp)
	je	.LBB17_82
	movl	$168, %r9d
	cmpq	$247, %rdi
	jae	.LBB17_70
	leal	-3(%rsi), %ecx
	movl	$63, %edi
	bsrl	%ecx, %edi
	xorl	$31, %edi
	shll	$4, %edi
	movl	$632, %r9d
	subl	%edi, %r9d
	movq	40(%rsp), %rcx
	cmpq	$4, %rcx
	ja	.LBB17_73
.LBB17_71:
	subl	%r9d, %eax
	jno	.LBB17_74
	jmp	.LBB17_237
.LBB17_70:
	movq	40(%rsp), %rcx
	cmpq	$4, %rcx
	jbe	.LBB17_71
.LBB17_73:
	decl	%ecx
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %r9d
	addl	$480, %r9d
	subl	%r9d, %eax
	jo	.LBB17_237
.LBB17_74:
	movq	24(%rsp), %rcx
	addq	$-11, %rcx
	movl	$168, %edi
	cmpq	$247, %rcx
	jae	.LBB17_76
	movq	24(%rsp), %rcx
	addl	$-3, %ecx
	movl	$63, %r9d
	bsrl	%ecx, %r9d
	xorl	$31, %r9d
	shll	$4, %r9d
	movl	$632, %edi
	subl	%r9d, %edi
.LBB17_76:
	movq	16(%rsp), %rcx
	cmpq	$4, %rcx
	jbe	.LBB17_79
	decl	%ecx
	cmpl	$1, %ecx
	jbe	.LBB17_242
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %edi
	addl	$480, %edi
.LBB17_79:
	movq	24(%rsp), %rcx
	shll	$6, %ecx
	subl	%edi, %ecx
	cmpl	%ecx, %eax
	jle	.LBB17_82
	movq	48(%rsp), %r13
	movq	8(%rsp), %rdi
	cmpq	%r13, %rdi
	jae	.LBB17_235
	movzbl	(%r15,%rdx), %ecx
	movl	$1, %eax
	movq	%r11, %r9
	movq	40(%rsp), %r12
	jmp	.LBB17_128
	.p2align	4
.LBB17_82:
	cmpq	$499992, %r11
	jae	.LBB17_148
	movq	56(%rsp), %rax
	shll	$24, %eax
	shll	$16, %ebx
	orl	%eax, %ebx
	shll	$8, %r14d
	orl	%ebx, %r14d
	movzbl	5(%r15,%rdx), %eax
	orq	%r14, %rax
	movabsq	$-7046029254386353131, %rcx
	imulq	%rcx, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %ebx
	movl	%r11d, %ecx
	andl	$32767, %ecx
	movl	%ebx, 136(%rsp,%rcx,4)
	movl	%r11d, 131208(%rsp,%rax,4)
	leaq	3(%rdx), %r9
	movl	$499998, %r14d
	subq	%rdx, %r14
	cmpq	%r14, 72(%rsp)
	jae	.LBB17_149
	cmpq	$258, %r14
	movl	$258, %eax
	cmovaeq	%rax, %r14
	leaq	(%r8,%r11), %rax
	cmpq	$500000, %rax
	movq	48(%rsp), %r13
	jae	.LBB17_86
	movzbl	(%r15,%rax), %eax
	jmp	.LBB17_87
	.p2align	4
.LBB17_86:
	xorl	%eax, %eax
.LBB17_87:
	movq	%r11, %rsi
	subq	%rbx, %rsi
	leaq	-1(%rsi), %rcx
	cmpq	$32768, %rcx
	jae	.LBB17_129
	leaq	(%r8,%rbx), %rcx
	cmpq	$499999, %rcx
	ja	.LBB17_129
	cmpb	%al, (%r15,%rcx)
	jne	.LBB17_129
	movq	%rsi, %rbp
	movl	%r14d, %esi
	andl	$504, %esi
	leaq	7(%r15), %rax
	leaq	(%rax,%rbx), %rdi
	leaq	9(%r15), %rax
	leaq	(%rax,%rdx), %r10
	movq	$-8, %rax
	jmp	.LBB17_92
	.p2align	4
.LBB17_91:
	movq	1(%r10,%rax), %rcx
	bswapq	%rcx
	addq	$8, %rax
	cmpq	%rcx, %r12
	jne	.LBB17_99
.LBB17_92:
	leaq	16(%rax), %rcx
	cmpq	%r14, %rcx
	ja	.LBB17_100
	leaq	(%rbx,%rax), %rcx
	addq	$8, %rcx
	cmpq	$499992, %rcx
	jbe	.LBB17_95
	xorl	%r12d, %r12d
	jmp	.LBB17_96
	.p2align	4
.LBB17_95:
	movq	1(%rdi,%rax), %r12
	bswapq	%r12
.LBB17_96:
	leaq	(%rdx,%rax), %rcx
	addq	$10, %rcx
	cmpq	$-9, %rcx
	ja	.LBB17_224
	cmpq	$499992, %rcx
	jbe	.LBB17_91
	xorl	%ecx, %ecx
	addq	$8, %rax
	cmpq	%rcx, %r12
	je	.LBB17_92
.LBB17_99:
	xorq	%r12, %rcx
	bsrq	%rcx, %rsi
	xorl	$56, %esi
	shrl	$3, %esi
	orq	%rax, %rsi
	movq	32(%rsp), %r10
	movq	%rbp, %r12
	jmp	.LBB17_105
	.p2align	4
.LBB17_100:
	cmpq	%r14, %rsi
	movq	32(%rsp), %r10
	movq	%rbp, %r12
	je	.LBB17_105
	.p2align	4
.LBB17_101:
	leaq	(%rsi,%rbx), %rdi
	cmpq	$500000, %rdi
	jae	.LBB17_225
	leaq	(%rsi,%r11), %rax
	cmpq	$499999, %rax
	ja	.LBB17_226
	movzbl	(%r15,%rdi), %ecx
	movzbl	(%r15,%rax), %eax
	xorl	%edi, %edi
	cmpb	%al, %cl
	sete	%dil
	addq	%rdi, %rsi
	cmpb	%al, %cl
	jne	.LBB17_105
	cmpq	%r14, %rsi
	jb	.LBB17_101
	.p2align	4
.LBB17_105:
	cmpq	%r8, %rsi
	jbe	.LBB17_129
	leaq	-11(%rsi), %rdi
	movl	$168, %r8d
	cmpq	$247, %rdi
	movq	24(%rsp), %rbx
	jae	.LBB17_107
	leal	-3(%rsi), %eax
	movl	$63, %ecx
	bsrl	%eax, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	movl	$632, %r8d
	subl	%ecx, %r8d
	cmpq	$4, %r12
	ja	.LBB17_110
.LBB17_108:
	leal	-33554432(%rsi), %eax
	cmpl	$-67108864, %eax
	jae	.LBB17_111
	jmp	.LBB17_239
	.p2align	4
.LBB17_107:
	cmpq	$4, %r12
	jbe	.LBB17_108
.LBB17_110:
	leal	-1(%r12), %eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	shll	$4, %eax
	subl	%eax, %r8d
	addl	$480, %r8d
	leal	-33554432(%rsi), %eax
	cmpl	$-67108864, %eax
	jb	.LBB17_239
.LBB17_111:
	movl	%esi, %eax
	shll	$6, %eax
	movl	%eax, %ecx
	subl	%r8d, %ecx
	jo	.LBB17_237
	cmpl	$-999999, %ecx
	jl	.LBB17_196
	testq	%r12, %r12
	je	.LBB17_196
	movl	$168, %r8d
	cmpq	$247, %rdi
	jae	.LBB17_115
	leal	-3(%rsi), %ecx
	movl	$63, %edi
	bsrl	%ecx, %edi
	xorl	$31, %edi
	shll	$4, %edi
	movl	$632, %r8d
	subl	%edi, %r8d
	cmpq	$4, %r12
	movq	16(%rsp), %r14
	ja	.LBB17_118
.LBB17_116:
	subl	%r8d, %eax
	jno	.LBB17_119
	jmp	.LBB17_237
	.p2align	4
.LBB17_115:
	cmpq	$4, %r12
	movq	16(%rsp), %r14
	jbe	.LBB17_116
.LBB17_118:
	leal	-1(%r12), %ecx
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %r8d
	addl	$480, %r8d
	subl	%r8d, %eax
	jo	.LBB17_237
.LBB17_119:
	leaq	-11(%rbx), %rcx
	movl	$168, %edi
	cmpq	$247, %rcx
	jae	.LBB17_121
	leal	-3(%rbx), %ecx
	movl	$63, %r8d
	bsrl	%ecx, %r8d
	xorl	$31, %r8d
	shll	$4, %r8d
	movl	$632, %edi
	subl	%r8d, %edi
.LBB17_121:
	cmpq	$4, %r14
	jbe	.LBB17_124
	leal	-1(%r14), %ecx
	cmpl	$1, %ecx
	jbe	.LBB17_242
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %edi
	addl	$480, %edi
.LBB17_124:
	movl	%ebx, %ecx
	shll	$6, %ecx
	orl	$40, %ecx
	subl	%edi, %ecx
	cmpl	%ecx, %eax
	jle	.LBB17_197
	movq	8(%rsp), %rdi
	cmpq	%r13, %rdi
	jae	.LBB17_235
	movzbl	(%r15,%rdx), %eax
	movl	%eax, (%r10,%rdi,4)
	incq	%rdi
	movl	$2, %eax
	cmpq	%r13, %rdi
	jae	.LBB17_235
	movq	%r11, %rbp
	movl	64(%rsp), %ecx
.LBB17_128:
	movzbl	%cl, %ecx
	movl	%ecx, (%r10,%rdi,4)
	movq	8(%rsp), %r11
	addq	%rax, %r11
	movq	%rsi, %r14
	movq	%r12, 16(%rsp)
	movq	%rbp, %rdx
	cmpq	$32, %rsi
	jb	.LBB17_35
	jmp	.LBB17_150
.LBB17_129:
	movq	%rdx, %rbp
	movq	16(%rsp), %r12
	movq	24(%rsp), %rsi
	jmp	.LBB17_199
.LBB17_130:
	movq	%r12, %r14
	movq	%r8, 16(%rsp)
	movq	16(%rsp), %r12
	testq	%r12, %r12
	movq	32(%rsp), %r10
	jne	.LBB17_34
	.p2align	4
.LBB17_131:
	movq	48(%rsp), %r13
	movq	8(%rsp), %rdi
	cmpq	%r13, %rdi
	movq	80(%rsp), %rbx
	jae	.LBB17_235
	movd	%xmm1, %eax
	movzbl	%al, %eax
	movl	%eax, (%r10,%rdi,4)
	movq	56(%rsp), %r14
	incq	%r14
	movabsq	$-7046029254386353131, %r12
	je	.LBB17_243
	movq	%r14, %rcx
	shrq	$5, %rcx
	leaq	1(%rdi), %rax
	testq	%rcx, %rcx
	je	.LBB17_138
	cmpq	$499990, %rdx
	ja	.LBB17_138
	cmpq	$1000000, %rcx
	movl	$1000000, %esi
	cmovaeq	%rsi, %rcx
	leaq	-1(%rcx), %rsi
	movl	$499990, %r8d
	subq	%rdx, %r8
	cmpq	%r8, %rsi
	cmovbq	%rsi, %r8
	movq	%rdi, %r11
	notq	%r11
	addq	%r13, %r11
	cmpq	%r11, %r8
	cmovbq	%r8, %r11
	incq	%r11
	cmpq	$8, %r11
	ja	.LBB17_139
	movq	%r9, %rsi
	jmp	.LBB17_142
.LBB17_139:
	movl	%r11d, %esi
	andl	$7, %esi
	movl	$8, %r8d
	cmoveq	%r8, %rsi
	subq	%rsi, %r11
	addq	%r11, %rax
	leaq	(%r9,%r11), %rsi
	subq	%r11, %rcx
	movq	88(%rsp), %r8
	leaq	(%r8,%rdi,4), %r8
	leaq	5(%r15), %rdi
	addq	%rdi, %rdx
	xorl	%r10d, %r10d
	.p2align	4
.LBB17_140:
	movd	-4(%rdx,%r10), %xmm1
	movd	(%rdx,%r10), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%r8,%r10,4)
	movdqu	%xmm2, (%r8,%r10,4)
	addq	$8, %r10
	cmpq	%r10, %r11
	jne	.LBB17_140
	movq	32(%rsp), %r10
.LBB17_142:
	decq	%rcx
	.p2align	4
.LBB17_143:
	cmpq	%rax, %r13
	je	.LBB17_228
	movzbl	(%r15,%rsi), %edx
	movl	%edx, (%r10,%rax,4)
	leaq	1(%rsi), %rdx
	incq	%rax
	addq	$-1, %rcx
	jae	.LBB17_146
	cmpq	$499991, %rsi
	movq	%rdx, %rsi
	jb	.LBB17_143
	jmp	.LBB17_146
.LBB17_147:
	movq	%rdx, %rbp
	movq	16(%rsp), %r12
	movq	%r14, %rsi
	leaq	-1(%r11), %rbx
	cmpq	%r13, %rbx
	movq	%r12, 40(%rsp)
	jb	.LBB17_151
	jmp	.LBB17_200
.LBB17_148:
	movq	%r11, %r9
.LBB17_149:
	movq	%rdx, %rbp
	movq	16(%rsp), %r12
	movq	24(%rsp), %rsi
	movq	48(%rsp), %r13
	movq	8(%rsp), %r11
	.p2align	4
.LBB17_150:
	leaq	-1(%r11), %rbx
	cmpq	%r13, %rbx
	movq	%r12, 40(%rsp)
	jb	.LBB17_151
	jmp	.LBB17_200
.LBB17_196:
	movq	%rdx, %rbp
	movq	16(%rsp), %r12
	jmp	.LBB17_198
.LBB17_197:
	movq	%r14, %r12
	movq	%rdx, %rbp
.LBB17_198:
	movq	%rbx, %rsi
.LBB17_199:
	movq	8(%rsp), %r11
	leaq	-1(%r11), %rbx
	cmpq	%r13, %rbx
	movq	%r12, 40(%rsp)
	jae	.LBB17_200
.LBB17_151:
	cmpq	$257, %rsi
	ja	.LBB17_200
	cmpq	%rbp, %r12
	jae	.LBB17_200
	movq	%r12, %rax
	negq	%rax
	movq	%rax, 56(%rsp)
	leaq	-3(%r15), %rax
	subq	%r12, %rax
	movq	%rax, 72(%rsp)
	xorl	%r14d, %r14d
	movq	%rbp, %rdx
	.p2align	4
.LBB17_154:
	movl	(%r10,%rbx,4), %eax
	cmpq	$256, %rax
	jae	.LBB17_159
	leaq	-1(%rdx), %rdi
	cmpq	$499999, %rdi
	ja	.LBB17_230
	movq	%rdi, %rax
	subq	%r12, %rax
	cmpq	$500000, %rax
	jae	.LBB17_229
	movzbl	(%r15,%rdi), %ecx
	movl	$16, %ebp
	cmpb	(%r15,%rax), %cl
	jne	.LBB17_190
	incq	%rsi
	incq	%r14
	movq	%rdi, %rdx
	movq	%r14, %rbp
.LBB17_189:
	movq	%rbx, %r11
	jmp	.LBB17_190
	.p2align	4
.LBB17_159:
	movl	$16, %ebp
	cmpl	$16777215, %eax
	jbe	.LBB17_190
	movzbl	%al, %r12d
	leaq	(%rsi,%r12), %rcx
	addq	$3, %rcx
	cmpq	$258, %rcx
	ja	.LBB17_190
	addq	$3, %r12
	movq	%rdx, %rdi
	subq	%r12, %rdi
	jb	.LBB17_190
	movq	%rdi, %r8
	subq	40(%rsp), %r8
	movq	%r8, 8(%rsp)
	jb	.LBB17_190
	movq	%rdi, 24(%rsp)
	movq	%rcx, 64(%rsp)
	movl	%r12d, %ecx
	andl	$-8, %ecx
	movzbl	%al, %edi
	movq	%rdx, %rax
	subq	%rdi, %rax
	movq	72(%rsp), %r8
	addq	%rax, %r8
	movq	%r8, 16(%rsp)
	movq	56(%rsp), %r8
	leaq	(%r8,%rdx), %r13
	subq	%rdi, %r13
	movl	$8, %r10d
	movq	%r11, %r8
	jmp	.LBB17_165
	.p2align	4
.LBB17_164:
	leaq	(%r15,%rax), %r11
	movq	-11(%r11,%r10), %r11
	bswapq	%r11
	addq	$8, %r10
	cmpq	%r11, %rdi
	jne	.LBB17_173
.LBB17_165:
	cmpq	%r12, %r10
	ja	.LBB17_174
	leaq	(%r10,%r13), %rdi
	addq	$-11, %rdi
	cmpq	$-9, %rdi
	ja	.LBB17_224
	cmpq	$499992, %rdi
	jbe	.LBB17_169
	xorl	%edi, %edi
	jmp	.LBB17_170
	.p2align	4
.LBB17_169:
	movq	16(%rsp), %rdi
	movq	-8(%rdi,%r10), %rdi
	bswapq	%rdi
.LBB17_170:
	leaq	(%rax,%r10), %r11
	addq	$-11, %r11
	cmpq	$-9, %r11
	ja	.LBB17_224
	cmpq	$499992, %r11
	jbe	.LBB17_164
	xorl	%r11d, %r11d
	addq	$8, %r10
	cmpq	%r11, %rdi
	je	.LBB17_165
.LBB17_173:
	movq	%r8, %r11
	movq	48(%rsp), %r13
	movq	32(%rsp), %r10
	.p2align	4
.LBB17_190:
	cmpq	$15, %rbp
	ja	.LBB17_201
	leaq	-1(%r11), %rbx
	cmpq	%r13, %rbx
	movq	40(%rsp), %r12
	jae	.LBB17_201
	cmpq	$257, %rsi
	ja	.LBB17_201
	movq	%rbp, %r14
	cmpq	%rdx, %r12
	jb	.LBB17_154
	jmp	.LBB17_201
.LBB17_174:
	cmpl	%r12d, %ecx
	movq	48(%rsp), %r13
	movq	32(%rsp), %r10
	je	.LBB17_188
	movq	%rcx, %rax
	addq	8(%rsp), %rax
	jb	.LBB17_244
	cmpq	$-9, %rax
	ja	.LBB17_244
	cmpq	$499993, %rax
	jae	.LBB17_181
	movq	%rcx, %rdi
	addq	24(%rsp), %rdi
	jb	.LBB17_246
	cmpq	$-9, %rdi
	ja	.LBB17_246
	cmpq	$499992, %rdi
	jbe	.LBB17_194
	.p2align	4
.LBB17_181:
	movq	%rcx, %rdi
	addq	8(%rsp), %rdi
	jb	.LBB17_232
	cmpq	$500000, %rdi
	jae	.LBB17_233
	movq	%rcx, %rax
	addq	24(%rsp), %rax
	jb	.LBB17_231
	cmpq	$500000, %rax
	jae	.LBB17_234
	movzbl	(%r15,%rdi), %edi
	movzbl	(%r15,%rax), %eax
	xorl	%r10d, %r10d
	cmpb	%al, %dil
	sete	%r11b
	jne	.LBB17_187
	movb	%r11b, %r10b
	addq	%r10, %rcx
	cmpq	%r12, %rcx
	jb	.LBB17_181
.LBB17_187:
	cmpb	%al, %dil
	movq	32(%rsp), %r10
	movq	%r8, %r11
	jne	.LBB17_190
	jmp	.LBB17_188
.LBB17_194:
	leal	(,%r12,8), %ecx
	andl	$56, %ecx
	je	.LBB17_247
	movq	(%r15,%rdi), %rdi
	xorq	(%r15,%rax), %rdi
	bswapq	%rdi
	negb	%cl
	shrq	%cl, %rdi
	testq	%rdi, %rdi
	movq	32(%rsp), %r10
	movq	%r8, %r11
	jne	.LBB17_190
.LBB17_188:
	incq	%r14
	movq	24(%rsp), %rdx
	movq	%r14, %rbp
	movq	64(%rsp), %rsi
	jmp	.LBB17_189
	.p2align	4
.LBB17_200:
	movq	%rbp, %rdx
.LBB17_201:
	cmpq	%r13, %r11
	movabsq	$-7046029254386353131, %r12
	jae	.LBB17_240
	movq	40(%rsp), %rax
	shll	$8, %eax
	addl	%esi, %eax
	addl	$16776957, %eax
	movl	%eax, (%r10,%r11,4)
	addq	%rsi, %rdx
	movq	80(%rsp), %rbx
	jb	.LBB17_241
	leaq	16(%r9), %rax
	cmpq	%rax, %rdx
	cmovbq	%rdx, %rax
	cmpq	$499992, %rax
	movl	$499992, %ecx
	cmovaeq	%rcx, %rax
	cmpq	%rax, %r9
	jae	.LBB17_206
	.p2align	4
.LBB17_204:
	movl	(%r15,%r9), %ecx
	bswapl	%ecx
	imulq	%r12, %rcx
	shrq	$48, %rcx
	movl	131208(%rsp,%rcx,4), %esi
	movl	%r9d, %edi
	andl	$32767, %edi
	movl	%esi, 136(%rsp,%rdi,4)
	movl	%r9d, 131208(%rsp,%rcx,4)
	incq	%r9
	cmpq	%r9, %rax
	jne	.LBB17_204
	movq	%rax, %r9
.LBB17_206:
	movq	%rdx, %rax
	subq	$8, %rax
	movl	$0, %ecx
	cmovaeq	%rax, %rcx
	cmpq	$499992, %rcx
	movl	$499992, %eax
	cmovaeq	%rax, %rcx
	cmpq	%rcx, %r9
	jae	.LBB17_209
	.p2align	4
.LBB17_207:
	leaq	4(%r9), %rax
	movl	(%r15,%r9), %esi
	bswapl	%esi
	imulq	%r12, %rsi
	shrq	$48, %rsi
	movl	131208(%rsp,%rsi,4), %edi
	movl	%r9d, 131208(%rsp,%rsi,4)
	andl	$32767, %r9d
	movl	%edi, 136(%rsp,%r9,4)
	movq	%rax, %r9
	cmpq	%rcx, %rax
	jb	.LBB17_207
	leaq	4(%rax), %rcx
	cmpq	%rdx, %rcx
	jb	.LBB17_210
	jmp	.LBB17_212
	.p2align	4
.LBB17_209:
	movq	%r9, %rax
	leaq	4(%rax), %rcx
	cmpq	%rdx, %rcx
	jae	.LBB17_212
.LBB17_210:
	cmpq	$4, %rdx
	jb	.LBB17_245
	leaq	-4(%rdx), %rax
.LBB17_212:
	cmpq	$499992, %rdx
	movl	$499992, %ecx
	cmovbq	%rdx, %rcx
	cmpq	%rcx, %rax
	jae	.LBB17_214
	.p2align	4
.LBB17_213:
	movl	(%r15,%rax), %esi
	bswapl	%esi
	imulq	%r12, %rsi
	shrq	$48, %rsi
	movl	131208(%rsp,%rsi,4), %edi
	movl	%eax, %r8d
	andl	$32767, %r8d
	movl	%edi, 136(%rsp,%r8,4)
	movl	%eax, 131208(%rsp,%rsi,4)
	incq	%rax
	cmpq	%rcx, %rax
	jb	.LBB17_213
.LBB17_214:
	incq	%r11
	movq	%r11, 8(%rsp)
	cmpq	%rdx, %rax
	cmovbeq	%rdx, %rax
	movq	%rax, %r9
	xorl	%r14d, %r14d
	cmpq	$499991, %rdx
	jbe	.LBB17_215
.LBB17_216:
	cmpq	$499999, %rdx
	ja	.LBB17_222
	movq	8(%rsp), %rax
	cmpq	%r13, %rax
	movq	%r13, %rdi
	cmovaq	%rax, %rdi
	movq	%rdi, %rcx
	subq	%rax, %rcx
	movl	$499999, %r9d
	subq	%rdx, %r9
	cmpq	%r9, %rcx
	cmovbq	%rcx, %r9
	cmpq	$7, %r9
	jbe	.LBB17_220
	incq	%r9
	movl	%r9d, %ecx
	andl	$7, %ecx
	movl	$8, %esi
	cmovneq	%rcx, %rsi
	subq	%rsi, %r9
	leaq	(%r10,%rax,4), %rcx
	addq	$16, %rcx
	addq	%r9, %rax
	leaq	(%r15,%rdx), %rsi
	addq	$4, %rsi
	addq	%r9, %rdx
	xorl	%r8d, %r8d
	pxor	%xmm0, %xmm0
	.p2align	4
.LBB17_219:
	movd	-4(%rsi,%r8), %xmm1
	movd	(%rsi,%r8), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%rcx,%r8,4)
	movdqu	%xmm2, (%rcx,%r8,4)
	addq	$8, %r8
	cmpq	%r8, %r9
	jne	.LBB17_219
	.p2align	4
.LBB17_220:
	cmpq	%rax, %rdi
	je	.LBB17_235
	movzbl	(%r15,%rdx), %ecx
	movl	%ecx, (%r10,%rax,4)
	incq	%rax
	incq	%rdx
	cmpq	$500000, %rdx
	jne	.LBB17_220
	jmp	.LBB17_223
.LBB17_222:
	movq	8(%rsp), %rax
.LBB17_223:
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
.LBB17_224:
	.cfi_def_cfa_offset 393408
	leaq	.Lalloc_440babfea49fec204c4bfa4556bd23df(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_225:
	leaq	.Lalloc_d0bf91bac5912d1054a41f50a5372dd0(%rip), %rdx
	movl	$500000, %esi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_226:
	leaq	.Lalloc_c7cb404ab9612aded1ce50ca918ced7b(%rip), %rdx
	movl	$500000, %esi
	movq	%rax, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_227:
	leaq	.Lalloc_e58248ce06d86db1620e3928ca18f57a(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_228:
	leaq	.Lalloc_1e808d4a560d2bfb30193cdd1b6f1f95(%rip), %rdx
	movq	%r13, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_229:
	leaq	.Lalloc_3d3fade205e2688424188b5bbd6c946c(%rip), %rdx
	movl	$500000, %esi
	movq	%rax, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_230:
	leaq	.Lalloc_1cb241537ee4f281c00fcbb1bef48ab0(%rip), %rdx
	movl	$500000, %esi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_231:
	leaq	.Lalloc_f89fc433b2ec5f525912d54366fd14b2(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_232:
	leaq	.Lalloc_ec9880852f5ad0b7f675c971d025b4ff(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_233:
	leaq	.Lalloc_c867e779aaf632c8ba08807d62f697ee(%rip), %rdx
	movl	$500000, %esi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_234:
	leaq	.Lalloc_f7486e32a26ebd3f0532d14c194cbf09(%rip), %rdx
	movl	$500000, %esi
	movq	%rax, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_235:
	leaq	.Lalloc_1e808d4a560d2bfb30193cdd1b6f1f95(%rip), %rdx
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_236:
	leaq	.Lalloc_8dedf8bdbae2e7f670fff12535f0d90a(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_237:
	leaq	.Lalloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB17_238:
	leaq	.Lalloc_f7734e5b3c0057e9bae084232237166a(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_239:
	leaq	.Lalloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow@GOTPCREL(%rip)
.LBB17_240:
	leaq	.Lalloc_91bbba7d8bfca8a214cab7fb1cbd8ce3(%rip), %rdx
	movq	%r11, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB17_241:
	leaq	.Lalloc_8c0fdb4f326073e19a6b7eb9b54b4e01(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_242:
	leaq	.Lalloc_9f4d1cf899b26bf5e0e440ccaea53f2f(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB17_243:
	leaq	.Lalloc_3040782d029b4f1f28da9c0a2089856b(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_244:
	leaq	.Lalloc_5988a9c474509aa3e7e55969f6ad663e(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_245:
	leaq	.Lalloc_94a048f0c628dd665e0545a553ca9ebc(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB17_246:
	leaq	.Lalloc_c2b01cdce33609a4161805adc289533f(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB17_247:
	leaq	.Lalloc_0471675f9abe1475b1e41b49769421c8(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow@GOTPCREL(%rip)
.Lfunc_end17:
	.size	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2, .Lfunc_end17-_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2
	.cfi_endproc
