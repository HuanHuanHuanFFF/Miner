
	.section	.text._RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9,"ax",@progbits
	.prefalign	4, .Lfunc_end24, nop
	.type	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9,@function
_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9:
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
.LBB24_1:
	subq	$4096, %rsp
	movq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LBB24_1
	subq	$168, %rsp
	.cfi_def_cfa_register %rsp
	.cfi_def_cfa_offset 393440
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rcx, %r9
	movq	%rdx, %r13
	movq	%rsi, %r10
	movq	%rdi, %r12
	cmpq	$16, %rsi
	jbe	.LBB24_174
	movabsq	$-7046029254386353131, %rbp
	leaq	131240(%rsp), %rdi
	xorl	%r14d, %r14d
	movq	memset@GOTPCREL(%rip), %rbx
	movl	$262144, %edx
	xorl	%esi, %esi
	movq	%r9, (%rsp)
	movq	%r10, 56(%rsp)
	callq	*%rbx
	leaq	168(%rsp), %rdi
	movl	$131072, %edx
	xorl	%esi, %esi
	callq	*%rbx
	movq	56(%rsp), %r10
	movq	%rbp, %r11
	leaq	16(%r10), %r8
	leaq	7(%r12), %rax
	movq	%rax, 96(%rsp)
	leaq	8(%r12), %rax
	movq	%rax, 128(%rsp)
	leaq	20(%r13), %rax
	movq	%rax, 112(%rsp)
	leaq	5(%r12), %rax
	movq	%rax, 104(%rsp)
	movq	(%rsp), %rax
	negq	%rax
	movq	%rax, 120(%rsp)
	pxor	%xmm0, %xmm0
	movq	$0, 16(%rsp)
	xorl	%r15d, %r15d
	xorl	%ecx, %ecx
	movq	%r12, 24(%rsp)
	movq	%r13, 40(%rsp)
	jmp	.LBB24_4
.LBB24_144:
	movq	%rcx, %r15
.LBB24_152:
	cmpq	%r15, %rcx
	cmovbeq	%r15, %rcx
	movq	%rax, %r14
	leaq	-8(%r10), %rax
	cmpq	%rax, %r15
	jae	.LBB24_173
.LBB24_172:
	testq	%r8, %r8
	je	.LBB24_173
.LBB24_4:
	movq	%r14, 32(%rsp)
	cmpq	%r15, %rcx
	jae	.LBB24_6
	.p2align	4
.LBB24_5:
	movl	(%r12,%rcx), %eax
	bswapl	%eax
	imulq	%r11, %rax
	shrq	$48, %rax
	movl	131240(%rsp,%rax,4), %edx
	movl	%ecx, %esi
	andl	$32767, %esi
	movl	%edx, 168(%rsp,%rsi,4)
	movl	%ecx, 131240(%rsp,%rax,4)
	incq	%rcx
	cmpq	%rcx, %r15
	jne	.LBB24_5
.LBB24_6:
	decq	%r8
	movq	%r8, 88(%rsp)
	movl	(%r12,%r15), %eax
	movd	%eax, %xmm1
	movdqa	%xmm1, 144(%rsp)
	movzbl	147(%rsp), %r8d
	bswapl	%eax
	imulq	%r11, %rax
	shrq	$48, %rax
	movl	131240(%rsp,%rax,4), %r9d
	movl	%r15d, %ecx
	andl	$32767, %ecx
	movl	%r9d, 168(%rsp,%rcx,4)
	movl	%r15d, 131240(%rsp,%rax,4)
	leaq	1(%r15), %rcx
	movq	%r10, %r11
	subq	%r15, %r11
	cmpq	$258, %r11
	movl	$258, %r14d
	cmovbq	%r11, %r14
	cmpq	$128, %r11
	movl	$128, %eax
	cmovaeq	%rax, %r11
	movl	%r14d, %eax
	andl	$504, %eax
	movq	%rax, 48(%rsp)
	movq	96(%rsp), %rax
	leaq	(%rax,%r15), %rdx
	movl	$12, %ebp
	movl	$3, %esi
	movq	$0, 8(%rsp)
	.p2align	4
.LBB24_7:
	movq	%r15, %r13
	subq	%r9, %r13
	leaq	-1(%r13), %rax
	cmpq	$32767, %rax
	ja	.LBB24_35
	leaq	(%r9,%rsi), %rax
	cmpq	%r10, %rax
	jae	.LBB24_35
	cmpb	%r8b, (%r12,%rax)
	jne	.LBB24_31
	movq	96(%rsp), %rax
	leaq	(%rax,%r9), %rdi
	movq	$-8, %rax
	jmp	.LBB24_12
	.p2align	4
.LBB24_11:
	movq	1(%rdx,%rax), %r12
	bswapq	%r12
	addq	$8, %rax
	cmpq	%r12, %rbx
	jne	.LBB24_19
.LBB24_12:
	leaq	16(%rax), %rbx
	cmpq	%r14, %rbx
	ja	.LBB24_20
	leaq	(%r9,%rax), %rbx
	addq	$16, %rbx
	cmpq	%r10, %rbx
	jbe	.LBB24_15
	xorl	%ebx, %ebx
	jmp	.LBB24_16
	.p2align	4
.LBB24_15:
	movq	1(%rdi,%rax), %rbx
	bswapq	%rbx
.LBB24_16:
	leaq	(%r15,%rax), %r12
	addq	$8, %r12
	cmpq	$-9, %r12
	ja	.LBB24_183
	leaq	(%r15,%rax), %r12
	addq	$16, %r12
	cmpq	%r10, %r12
	jbe	.LBB24_11
	xorl	%r12d, %r12d
	addq	$8, %rax
	cmpq	%r12, %rbx
	je	.LBB24_12
.LBB24_19:
	xorq	%rbx, %r12
	bsrq	%r12, %rbx
	xorl	$56, %ebx
	shrl	$3, %ebx
	orq	%rax, %rbx
	movq	24(%rsp), %r12
	cmpq	%rsi, %rbx
	ja	.LBB24_27
	jmp	.LBB24_31
	.p2align	4
.LBB24_20:
	movq	48(%rsp), %rax
	movq	%rax, %rbx
	cmpq	%r14, %rax
	movq	24(%rsp), %r12
	je	.LBB24_26
	.p2align	4
.LBB24_21:
	leaq	(%rbx,%r9), %rdi
	cmpq	%r10, %rdi
	jae	.LBB24_186
	movq	%rbx, %rax
	addq	%r15, %rax
	jb	.LBB24_185
	cmpq	%r10, %rax
	jae	.LBB24_184
	movzbl	(%r12,%rdi), %edi
	movzbl	(%r12,%rax), %eax
	xorl	%r12d, %r12d
	cmpb	%al, %dil
	sete	%r12b
	addq	%r12, %rbx
	cmpb	%al, %dil
	jne	.LBB24_33
	cmpq	%r14, %rbx
	movq	24(%rsp), %r12
	jb	.LBB24_21
	.p2align	4
.LBB24_26:
	cmpq	%rsi, %rbx
	jbe	.LBB24_31
.LBB24_27:
	cmpq	%r11, %rbx
	jae	.LBB24_34
	movq	%rbx, %rax
	addq	%r15, %rax
	jb	.LBB24_197
	cmpq	%r10, %rax
	jae	.LBB24_34
	movzbl	(%r12,%rax), %r8d
	movq	%r13, 8(%rsp)
	movq	%rbx, %rsi
.LBB24_31:
	movl	%r9d, %eax
	andl	$32767, %eax
	movl	168(%rsp,%rax,4), %eax
	cmpq	%rax, %r9
	jbe	.LBB24_35
	movq	%rax, %r9
	decq	%rbp
	jne	.LBB24_7
	jmp	.LBB24_35
.LBB24_33:
	movq	24(%rsp), %r12
	cmpq	%rsi, %rbx
	ja	.LBB24_27
	jmp	.LBB24_31
.LBB24_34:
	movq	%rbx, %rsi
	movq	%r13, 8(%rsp)
	.p2align	4
.LBB24_35:
	movq	8(%rsp), %rdi
	testq	%rdi, %rdi
	je	.LBB24_85
	cmpq	$63, %rsi
	movq	(%rsp), %r9
	movq	40(%rsp), %r13
	movq	32(%rsp), %r14
	ja	.LBB24_91
	movq	128(%rsp), %rax
	addq	%r15, %rax
	movq	%rax, 48(%rsp)
	movq	%r15, %rbp
	notq	%rbp
	addq	%r10, %rbp
	leaq	-8(%r10), %rax
	cmpq	%rcx, %rax
	movq	%rcx, %rdx
	cmovaq	%rax, %rdx
	movq	%rdx, 72(%rsp)
	cmpq	%r9, %r14
	movq	%r9, %rax
	cmovaq	%r14, %rax
	movq	%rax, 80(%rsp)
.LBB24_38:
	leaq	1(%r15), %rdx
	cmpq	$258, %rbp
	movl	$258, %r11d
	cmovbq	%rbp, %r11
	leaq	-8(%r10), %rax
	cmpq	%rax, %rdx
	jae	.LBB24_154
	movq	%rbp, 64(%rsp)
	movq	%rdi, 8(%rsp)
	movl	1(%r12,%r15), %eax
	bswapl	%eax
	movabsq	$-7046029254386353131, %rdi
	imulq	%rdi, %rax
	shrq	$48, %rax
	movl	131240(%rsp,%rax,4), %r13d
	movl	%edx, %edi
	andl	$32767, %edi
	movl	%r13d, 168(%rsp,%rdi,4)
	leaq	-1(%rsi), %rbp
	cmpq	$4, %rbp
	movl	$3, %edi
	cmovbq	%rdi, %rbp
	movl	%edx, 131240(%rsp,%rax,4)
	movq	%r10, %rbx
	subq	%rdx, %rbx
	cmpq	$258, %rbx
	movl	$258, %eax
	cmovaeq	%rax, %rbx
	leaq	(%rdx,%rbp), %rax
	cmpq	%r10, %rax
	jae	.LBB24_41
	movzbl	(%r12,%rax), %eax
	jmp	.LBB24_42
	.p2align	4
.LBB24_41:
	xorl	%eax, %eax
.LBB24_42:
	leaq	1(%rcx), %r8
	movq	%rdx, %rdi
	subq	%r13, %rdi
	movq	%rdi, 16(%rsp)
	decq	%rdi
	cmpq	$32767, %rdi
	ja	.LBB24_94
	movq	%rbp, %rdi
	addq	%r13, %rdi
	cmpq	%r10, %rdi
	jae	.LBB24_94
	cmpb	%al, (%r12,%rdi)
	jne	.LBB24_94
	movq	%r14, 32(%rsp)
	andl	$504, %r11d
	movq	96(%rsp), %rax
	leaq	(%rax,%r13), %rdi
	movq	$-8, %rax
	jmp	.LBB24_47
	.p2align	4
.LBB24_46:
	movq	48(%rsp), %r9
	movq	1(%r9,%rax), %r12
	bswapq	%r12
	addq	$8, %rax
	cmpq	%r12, %r14
	jne	.LBB24_55
.LBB24_47:
	leaq	16(%rax), %r9
	cmpq	%rbx, %r9
	ja	.LBB24_56
	leaq	(%rax,%r13), %r9
	addq	$16, %r9
	cmpq	%r10, %r9
	jbe	.LBB24_50
	xorl	%r14d, %r14d
	jmp	.LBB24_51
	.p2align	4
.LBB24_50:
	movq	1(%rdi,%rax), %r14
	bswapq	%r14
.LBB24_51:
	cmpq	%r15, %rcx
	jbe	.LBB24_187
	leaq	(%r15,%rax), %r9
	addq	$9, %r9
	cmpq	$-9, %r9
	ja	.LBB24_183
	leaq	(%r15,%rax), %r9
	addq	$17, %r9
	cmpq	%r10, %r9
	jbe	.LBB24_46
	xorl	%r12d, %r12d
	addq	$8, %rax
	cmpq	%r12, %r14
	je	.LBB24_47
.LBB24_55:
	xorq	%r14, %r12
	bsrq	%r12, %r11
	xorl	$56, %r11d
	shrl	$3, %r11d
	orq	%rax, %r11
	movq	(%rsp), %r9
	movq	24(%rsp), %r12
	movq	32(%rsp), %r14
	jmp	.LBB24_63
	.p2align	4
.LBB24_56:
	cmpq	%rbx, %r11
	movq	(%rsp), %r9
	movq	24(%rsp), %r12
	movq	32(%rsp), %r14
	jae	.LBB24_63
	.p2align	4
.LBB24_57:
	movq	%r11, %rdi
	addq	%r13, %rdi
	jb	.LBB24_188
	cmpq	%r10, %rdi
	jae	.LBB24_186
	leaq	(%r11,%rdx), %rax
	cmpq	%r15, %rax
	jbe	.LBB24_185
	cmpq	%r10, %rax
	jae	.LBB24_184
	movzbl	(%r12,%rdi), %ecx
	movzbl	(%r12,%rax), %eax
	xorl	%edi, %edi
	cmpb	%al, %cl
	sete	%dil
	addq	%rdi, %r11
	cmpb	%al, %cl
	jne	.LBB24_63
	cmpq	%rbx, %r11
	jb	.LBB24_57
	.p2align	4
.LBB24_63:
	cmpq	%rbp, %r11
	jbe	.LBB24_94
	leaq	-11(%r11), %rcx
	movl	$168, %edi
	cmpq	$247, %rcx
	movq	40(%rsp), %r13
	movq	8(%rsp), %rbp
	jae	.LBB24_65
	leal	-3(%r11), %eax
	movl	$63, %r9d
	bsrl	%eax, %r9d
	xorl	$31, %r9d
	shll	$4, %r9d
	movl	$632, %edi
	subl	%r9d, %edi
	movq	16(%rsp), %rbx
	cmpq	$4, %rbx
	ja	.LBB24_68
.LBB24_66:
	leal	-33554432(%r11), %eax
	cmpl	$-67108864, %eax
	jae	.LBB24_69
	jmp	.LBB24_199
	.p2align	4
.LBB24_65:
	movq	16(%rsp), %rbx
	cmpq	$4, %rbx
	jbe	.LBB24_66
.LBB24_68:
	leal	-1(%rbx), %eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	shll	$4, %eax
	subl	%eax, %edi
	addl	$480, %edi
	leal	-33554432(%r11), %eax
	cmpl	$-67108864, %eax
	jb	.LBB24_199
.LBB24_69:
	movl	%r11d, %eax
	shll	$6, %eax
	movl	%eax, %r9d
	subl	%edi, %r9d
	jo	.LBB24_196
	cmpl	$-999999, %r9d
	jl	.LBB24_156
	testq	%rbx, %rbx
	movq	(%rsp), %r9
	je	.LBB24_153
	movl	$168, %edi
	cmpq	$247, %rcx
	jae	.LBB24_73
	leal	-3(%r11), %ecx
	movl	$63, %r9d
	bsrl	%ecx, %r9d
	xorl	$31, %r9d
	shll	$4, %r9d
	movl	$632, %edi
	subl	%r9d, %edi
	movq	(%rsp), %r9
	cmpq	$4, %rbx
	ja	.LBB24_76
.LBB24_74:
	subl	%edi, %eax
	jno	.LBB24_77
	jmp	.LBB24_196
	.p2align	4
.LBB24_73:
	cmpq	$4, %rbx
	jbe	.LBB24_74
.LBB24_76:
	leal	-1(%rbx), %ecx
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %edi
	addl	$480, %edi
	subl	%edi, %eax
	jo	.LBB24_196
.LBB24_77:
	leaq	-11(%rsi), %rdi
	movl	$168, %ecx
	cmpq	$247, %rdi
	jae	.LBB24_79
	leal	-3(%rsi), %ecx
	movl	$63, %edi
	bsrl	%ecx, %edi
	xorl	$31, %edi
	shll	$4, %edi
	movl	$632, %ecx
	subl	%edi, %ecx
.LBB24_79:
	cmpq	$4, %rbp
	jbe	.LBB24_82
	leal	-1(%rbp), %edi
	cmpl	$1, %edi
	jbe	.LBB24_203
	bsrl	%edi, %edi
	xorl	$31, %edi
	shll	$4, %edi
	subl	%edi, %ecx
	addl	$480, %ecx
.LBB24_82:
	movl	%esi, %edi
	shll	$6, %edi
	subl	%ecx, %edi
	cmpl	%edi, %eax
	jle	.LBB24_153
	cmpq	80(%rsp), %r14
	je	.LBB24_200
	movzbl	(%r12,%r15), %eax
	movl	%eax, (%r13,%r14,4)
	incq	%r14
	movq	64(%rsp), %rbp
	decq	%rbp
	incq	48(%rsp)
	movq	%r8, %rcx
	movq	%r11, %rsi
	movq	%rbx, %rdi
	movq	%rdx, %r15
	cmpq	$64, %r11
	jb	.LBB24_38
	jmp	.LBB24_95
	.p2align	4
.LBB24_85:
	movq	(%rsp), %r9
	movq	32(%rsp), %rdi
	cmpq	%r9, %rdi
	movq	40(%rsp), %r13
	movabsq	$-7046029254386353131, %r11
	movq	88(%rsp), %r8
	jae	.LBB24_198
	movd	%xmm1, %eax
	movzbl	%al, %eax
	movl	%eax, (%r13,%rdi,4)
	movq	16(%rsp), %rdx
	incq	%rdx
	leaq	-8(%r10), %r14
	je	.LBB24_204
	movq	%rdx, 16(%rsp)
	shrq	$6, %rdx
	leaq	1(%rdi), %rax
	testq	%rdx, %rdx
	je	.LBB24_144
	cmpq	%r14, %rcx
	jae	.LBB24_144
	cmpq	$1000000, %rdx
	movl	$1000000, %esi
	cmovaeq	%rsi, %rdx
	leaq	-10(%r10), %rsi
	subq	%r15, %rsi
	leaq	-1(%rdx), %r8
	cmpq	%r8, %rsi
	cmovaeq	%r8, %rsi
	movq	%rdi, %r11
	notq	%r11
	addq	%r9, %r11
	cmpq	%r11, %rsi
	cmovbq	%rsi, %r11
	incq	%r11
	cmpq	$8, %r11
	ja	.LBB24_145
	movq	%rcx, %rsi
	jmp	.LBB24_147
	.p2align	4
.LBB24_91:
	movq	%rcx, %r8
.LBB24_92:
	movq	%r15, %rdx
	movq	%rdi, %rbx
.LBB24_93:
	movq	%rsi, %r11
	leaq	-1(%r14), %r12
	cmpq	%r9, %r12
	jb	.LBB24_96
	jmp	.LBB24_157
.LBB24_94:
	movq	%r15, %rdx
	movq	8(%rsp), %rbx
	movq	%rsi, %r11
	movq	40(%rsp), %r13
.LBB24_95:
	leaq	-1(%r14), %r12
	cmpq	%r9, %r12
	jae	.LBB24_157
.LBB24_96:
	cmpq	$257, %r11
	ja	.LBB24_157
	cmpq	%rdx, %rbx
	jae	.LBB24_157
	movq	%rbx, %rax
	negq	%rax
	movq	%rax, 80(%rsp)
	movq	24(%rsp), %rax
	subq	%rbx, %rax
	movq	%rax, 72(%rsp)
	xorl	%esi, %esi
	movq	%rdx, %r15
	movq	%rbx, 16(%rsp)
	.p2align	4
.LBB24_99:
	movl	(%r13,%r12,4), %edi
	cmpq	$256, %rdi
	jae	.LBB24_104
	leaq	-1(%r15), %rdi
	cmpq	%r10, %rdi
	jae	.LBB24_191
	movq	%rdi, %rax
	subq	%rbx, %rax
	cmpq	%r10, %rax
	jae	.LBB24_190
	movq	24(%rsp), %rbx
	movzbl	(%rbx,%rdi), %ecx
	movl	$16, %edx
	cmpb	(%rbx,%rax), %cl
	jne	.LBB24_109
	incq	%r11
	incq	%rsi
	movq	%rdi, %r15
	movq	%rsi, %rdx
	movq	%r12, %rbp
	movq	16(%rsp), %rbx
	jmp	.LBB24_137
	.p2align	4
.LBB24_104:
	movq	%r14, %rbp
	movl	$16, %edx
	cmpl	$16777215, %edi
	jbe	.LBB24_137
	movzbl	%dil, %r14d
	leaq	(%r11,%r14), %rax
	addq	$3, %rax
	cmpq	$258, %rax
	ja	.LBB24_137
	addq	$3, %r14
	movq	%r15, %r10
	subq	%r14, %r10
	jb	.LBB24_110
	movq	%r10, %rcx
	subq	%rbx, %rcx
	movq	%rcx, 32(%rsp)
	jae	.LBB24_111
.LBB24_110:
	movq	56(%rsp), %r10
	jmp	.LBB24_137
	.p2align	4
.LBB24_109:
	movq	%r14, %rbp
	movq	16(%rsp), %rbx
.LBB24_137:
	cmpq	$15, %rdx
	ja	.LBB24_155
	movq	%rbp, %r14
	leaq	-1(%rbp), %r12
	cmpq	%r9, %r12
	jae	.LBB24_158
	cmpq	$257, %r11
	ja	.LBB24_158
	movq	%rdx, %rsi
	cmpq	%r15, %rbx
	jb	.LBB24_99
	jmp	.LBB24_158
.LBB24_111:
	movq	%r10, 64(%rsp)
	movq	%rax, 136(%rsp)
	movl	%r14d, %ecx
	andl	$-8, %ecx
	movq	80(%rsp), %rax
	addq	%r15, %rax
	movzbl	%dil, %r9d
	subq	%r9, %rax
	movq	%r15, %rdi
	subq	%r9, %rdi
	movq	72(%rsp), %r9
	addq	%rdi, %r9
	movq	%r9, 48(%rsp)
	movq	24(%rsp), %r9
	addq	%rdi, %r9
	movq	%r9, 8(%rsp)
	movl	$8, %ebx
	movq	56(%rsp), %r10
	jmp	.LBB24_113
	.p2align	4
.LBB24_112:
	movq	8(%rsp), %r9
	movq	-11(%r9,%rbx), %r9
	bswapq	%r9
	addq	$8, %rbx
	cmpq	%r9, %r13
	movq	40(%rsp), %r13
	jne	.LBB24_121
.LBB24_113:
	cmpq	%r14, %rbx
	ja	.LBB24_122
	leaq	(%rax,%rbx), %r9
	addq	$-11, %r9
	cmpq	$-9, %r9
	ja	.LBB24_183
	leaq	(%rax,%rbx), %r9
	addq	$-3, %r9
	cmpq	%r10, %r9
	jbe	.LBB24_117
	xorl	%r13d, %r13d
	jmp	.LBB24_118
	.p2align	4
.LBB24_117:
	movq	48(%rsp), %r9
	movq	-11(%r9,%rbx), %r13
	bswapq	%r13
.LBB24_118:
	leaq	(%rdi,%rbx), %r9
	addq	$-11, %r9
	cmpq	$-9, %r9
	ja	.LBB24_183
	leaq	(%rdi,%rbx), %r9
	addq	$-3, %r9
	cmpq	%r10, %r9
	jbe	.LBB24_112
	xorl	%r9d, %r9d
	addq	$8, %rbx
	cmpq	%r9, %r13
	movq	40(%rsp), %r13
	je	.LBB24_113
.LBB24_121:
	movq	(%rsp), %r9
	movq	16(%rsp), %rbx
	jmp	.LBB24_137
.LBB24_122:
	cmpl	%r14d, %ecx
	movq	(%rsp), %r9
	movq	16(%rsp), %rbx
	je	.LBB24_136
	movq	%rcx, %rax
	addq	32(%rsp), %rax
	jb	.LBB24_205
	cmpq	$-9, %rax
	ja	.LBB24_205
	leaq	8(%rax), %rdi
	cmpq	%r10, %rdi
	ja	.LBB24_129
	movq	%rcx, %rdi
	addq	64(%rsp), %rdi
	jb	.LBB24_207
	cmpq	$-9, %rdi
	ja	.LBB24_207
	leaq	8(%rdi), %r9
	cmpq	%r10, %r9
	jbe	.LBB24_141
	.p2align	4
.LBB24_129:
	movq	%rcx, %rdi
	addq	32(%rsp), %rdi
	jb	.LBB24_193
	cmpq	%r10, %rdi
	jae	.LBB24_194
	movq	%rcx, %rax
	addq	64(%rsp), %rax
	jb	.LBB24_192
	cmpq	%r10, %rax
	jae	.LBB24_195
	movq	24(%rsp), %r9
	movzbl	(%r9,%rdi), %edi
	movzbl	(%r9,%rax), %eax
	xorl	%ebx, %ebx
	cmpb	%al, %dil
	sete	%r9b
	jne	.LBB24_135
	movb	%r9b, %bl
	addq	%rbx, %rcx
	cmpq	%r14, %rcx
	jb	.LBB24_129
.LBB24_135:
	cmpb	%al, %dil
	movq	(%rsp), %r9
	movq	16(%rsp), %rbx
	jne	.LBB24_137
	jmp	.LBB24_136
.LBB24_141:
	leal	(,%r14,8), %ecx
	andl	$56, %ecx
	je	.LBB24_208
	movq	24(%rsp), %r9
	movq	(%r9,%rdi), %rdi
	xorq	(%r9,%rax), %rdi
	bswapq	%rdi
	negb	%cl
	shrq	%cl, %rdi
	testq	%rdi, %rdi
	movq	(%rsp), %r9
	movq	16(%rsp), %rbx
	jne	.LBB24_137
.LBB24_136:
	incq	%rsi
	movq	64(%rsp), %r15
	movq	%rsi, %rdx
	movq	136(%rsp), %r11
	movq	%r12, %rbp
	jmp	.LBB24_137
.LBB24_145:
	movl	%r11d, %esi
	andl	$7, %esi
	movl	$8, %r8d
	cmoveq	%r8, %rsi
	subq	%rsi, %r11
	addq	%r11, %rax
	leaq	(%rcx,%r11), %rsi
	subq	%r11, %rdx
	movq	112(%rsp), %r8
	leaq	(%r8,%rdi,4), %r8
	addq	104(%rsp), %r15
	xorl	%r9d, %r9d
	.p2align	4
.LBB24_146:
	movd	-4(%r15,%r9), %xmm1
	movd	(%r15,%r9), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%r8,%r9,4)
	movdqu	%xmm2, (%r8,%r9,4)
	addq	$8, %r9
	cmpq	%r9, %r11
	jne	.LBB24_146
.LBB24_147:
	leaq	(,%rax,4), %rdi
	addq	%r13, %rdi
	movq	120(%rsp), %r8
	addq	%rax, %r8
	leaq	(%r12,%rsi), %r9
	decq	%rdx
	xorl	%r10d, %r10d
	.p2align	4
.LBB24_148:
	movq	%r8, %r11
	addq	%r10, %r11
	je	.LBB24_189
	movzbl	(%r9,%r10), %r11d
	movl	%r11d, (%rdi,%r10,4)
	leaq	1(%r10), %r11
	cmpq	%r10, %rdx
	je	.LBB24_151
	leaq	(%r10,%rsi), %rbx
	incq	%rbx
	movq	%r11, %r10
	cmpq	%r14, %rbx
	jb	.LBB24_148
.LBB24_151:
	addq	%r11, %rax
	addq	%r11, %rsi
	movq	%rsi, %r15
	movq	(%rsp), %r9
	movabsq	$-7046029254386353131, %r11
	movq	88(%rsp), %r8
	movq	56(%rsp), %r10
	jmp	.LBB24_152
.LBB24_153:
	movq	%r15, %rdx
	movq	%rbp, %rbx
	jmp	.LBB24_93
.LBB24_154:
	movq	72(%rsp), %r8
	jmp	.LBB24_92
.LBB24_155:
	movq	%rbp, %r14
	jmp	.LBB24_158
.LBB24_156:
	movq	%r15, %rdx
	movq	%rbp, %rbx
	movq	%rsi, %r11
	movq	(%rsp), %r9
	leaq	-1(%r14), %r12
	cmpq	%r9, %r12
	jb	.LBB24_96
	.p2align	4
.LBB24_157:
	movq	%rdx, %r15
.LBB24_158:
	cmpq	%r9, %r14
	jae	.LBB24_201
	shll	$8, %ebx
	leal	(%rbx,%r11), %eax
	addl	$16776957, %eax
	movl	%eax, (%r13,%r14,4)
	addq	%r11, %r15
	movq	24(%rsp), %r12
	jb	.LBB24_202
	leaq	16(%r8), %rax
	cmpq	%rax, %r15
	cmovbq	%r15, %rax
	leaq	-8(%r10), %rcx
	cmpq	%rcx, %rax
	cmovaeq	%rcx, %rax
	cmpq	%rax, %r8
	movabsq	$-7046029254386353131, %r11
	jae	.LBB24_163
	.p2align	4
.LBB24_161:
	movl	(%r12,%r8), %ecx
	bswapl	%ecx
	imulq	%r11, %rcx
	shrq	$48, %rcx
	movl	131240(%rsp,%rcx,4), %edx
	movl	%r8d, %esi
	andl	$32767, %esi
	movl	%edx, 168(%rsp,%rsi,4)
	movl	%r8d, 131240(%rsp,%rcx,4)
	incq	%r8
	cmpq	%r8, %rax
	jne	.LBB24_161
	movq	%rax, %r8
.LBB24_163:
	movq	%r15, %rcx
	subq	$8, %rcx
	movl	$0, %eax
	cmovaeq	%rcx, %rax
	leaq	-8(%r10), %rcx
	cmpq	%rcx, %rax
	cmovaeq	%rcx, %rax
	cmpq	%rax, %r8
	jae	.LBB24_166
	.p2align	4
.LBB24_164:
	leaq	4(%r8), %rcx
	movl	(%r12,%r8), %edx
	bswapl	%edx
	imulq	%r11, %rdx
	shrq	$48, %rdx
	movl	131240(%rsp,%rdx,4), %esi
	movl	%r8d, 131240(%rsp,%rdx,4)
	andl	$32767, %r8d
	movl	%esi, 168(%rsp,%r8,4)
	movq	%rcx, %r8
	cmpq	%rax, %rcx
	jb	.LBB24_164
	leaq	4(%rcx), %rax
	cmpq	%r15, %rax
	movq	88(%rsp), %r8
	jb	.LBB24_167
	jmp	.LBB24_169
	.p2align	4
.LBB24_166:
	movq	%r8, %rcx
	leaq	4(%rcx), %rax
	cmpq	%r15, %rax
	movq	88(%rsp), %r8
	jae	.LBB24_169
.LBB24_167:
	cmpq	$4, %r15
	jb	.LBB24_206
	leaq	-4(%r15), %rcx
.LBB24_169:
	leaq	-8(%r10), %rax
	cmpq	%rax, %r15
	cmovbq	%r15, %rax
	cmpq	%rax, %rcx
	jae	.LBB24_171
	.p2align	4
.LBB24_170:
	movl	(%r12,%rcx), %edx
	bswapl	%edx
	imulq	%r11, %rdx
	shrq	$48, %rdx
	movl	131240(%rsp,%rdx,4), %esi
	movl	%ecx, %edi
	andl	$32767, %edi
	movl	%esi, 168(%rsp,%rdi,4)
	movl	%ecx, 131240(%rsp,%rdx,4)
	incq	%rcx
	cmpq	%rax, %rcx
	jb	.LBB24_170
.LBB24_171:
	incq	%r14
	cmpq	%r15, %rcx
	cmovbeq	%r15, %rcx
	movq	$0, 16(%rsp)
	leaq	-8(%r10), %rax
	cmpq	%rax, %r15
	jb	.LBB24_172
.LBB24_173:
	cmpq	%r10, %r15
	jb	.LBB24_175
	jmp	.LBB24_182
.LBB24_174:
	xorl	%r15d, %r15d
	xorl	%r14d, %r14d
	cmpq	%r10, %r15
	jae	.LBB24_182
.LBB24_175:
	cmpq	%r9, %r14
	movq	%r9, %rdi
	cmovaq	%r14, %rdi
	movq	%r15, %rcx
	notq	%rcx
	addq	%r10, %rcx
	movq	%rdi, %rax
	subq	%r14, %rax
	cmpq	%rax, %rcx
	cmovbq	%rcx, %rax
	incq	%rax
	cmpq	$8, %rax
	jbe	.LBB24_178
	movl	%eax, %ecx
	andl	$7, %ecx
	movl	$8, %edx
	cmovneq	%rcx, %rdx
	subq	%rdx, %rax
	leaq	16(,%r14,4), %rcx
	addq	%r13, %rcx
	addq	%rax, %r14
	leaq	(%r15,%r12), %rdx
	addq	$4, %rdx
	addq	%rax, %r15
	xorl	%esi, %esi
	pxor	%xmm0, %xmm0
	.p2align	4
.LBB24_177:
	movd	-4(%rdx,%rsi), %xmm1
	movd	(%rdx,%rsi), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%rcx,%rsi,4)
	movdqu	%xmm2, (%rcx,%rsi,4)
	addq	$8, %rsi
	cmpq	%rsi, %rax
	jne	.LBB24_177
.LBB24_178:
	leaq	(,%r14,4), %rax
	addq	%r13, %rax
	movq	%r14, %rcx
	subq	%rdi, %rcx
	subq	%r15, %r10
	addq	%r15, %r12
	xorl	%edx, %edx
	.p2align	4
.LBB24_179:
	movq	%rcx, %rsi
	addq	%rdx, %rsi
	je	.LBB24_198
	movzbl	(%r12,%rdx), %esi
	movl	%esi, (%rax,%rdx,4)
	incq	%rdx
	cmpq	%rdx, %r10
	jne	.LBB24_179
	addq	%rdx, %r14
.LBB24_182:
	movq	%r14, %rax
	addq	$393384, %rsp
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
.LBB24_183:
	.cfi_def_cfa_offset 393440
	leaq	.Lalloc_f431a71fe7fa184932e2f2ca80dd7f47(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_184:
	leaq	.Lalloc_56ecd9016604ef09c80c99432e8fc906(%rip), %rdx
	movq	%rax, %rdi
	movq	%r10, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_185:
	leaq	.Lalloc_c7f8ac24ddf6de96b714aada129d8a33(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_186:
	leaq	.Lalloc_6b1a7f45dfd55c0aebeb6e6d6b0c2ae4(%rip), %rdx
	movq	%r10, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_187:
	leaq	.Lalloc_3f3b038533644865b4c8a352aaff7faf(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_188:
	leaq	.Lalloc_241ca15532e1ec51b67d3b4233ce5ad7(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_189:
	leaq	.Lalloc_3f1979cd14d951e234076c08c927f314(%rip), %rdx
	movq	(%rsp), %rdi
	movq	%rdi, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_190:
	leaq	.Lalloc_3d0d5d4486785f18b0624dab6a01ab30(%rip), %rdx
	movq	%rax, %rdi
	movq	%r10, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_191:
	leaq	.Lalloc_776ab685522d1ef927dd569287a9cae8(%rip), %rdx
	movq	%r10, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_192:
	leaq	.Lalloc_e9a2ebdcf5db95897279517544ac0f54(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_193:
	leaq	.Lalloc_59cc29aaacc6c8c1b4ef15345e05953f(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_194:
	leaq	.Lalloc_072a29a80fec7159394ad63468cbcdd7(%rip), %rdx
	movq	%r10, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_195:
	leaq	.Lalloc_48003f50f4167b7fbab234e09c66fd08(%rip), %rdx
	movq	%rax, %rdi
	movq	%r10, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_196:
	leaq	.Lalloc_8c632a1a41094e638a7e64298e17f2d8(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_197:
	leaq	.Lalloc_e179cad143318dcfd2788168957dfaf7(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_198:
	leaq	.Lalloc_3f1979cd14d951e234076c08c927f314(%rip), %rdx
	movq	%r9, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_199:
	leaq	.Lalloc_8c632a1a41094e638a7e64298e17f2d8(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow@GOTPCREL(%rip)
.LBB24_200:
	leaq	.Lalloc_3f1979cd14d951e234076c08c927f314(%rip), %rdx
	movq	%r14, %rdi
	movq	%r9, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_201:
	leaq	.Lalloc_29dd65baceeed166bb53933fb80ca329(%rip), %rdx
	movq	%r14, %rdi
	movq	%r9, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_202:
	leaq	.Lalloc_9084b2e9fae61601bb63b991933baba7(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_203:
	leaq	.Lalloc_cb4d3210bdab504a628b2e9a91b05589(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_204:
	leaq	.Lalloc_01578fb95574744d1d1ac4707b87233c(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_205:
	leaq	.Lalloc_185f9779b06ab1424a63baa82abc9093(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_206:
	leaq	.Lalloc_0b09b2a6a3862707bdb18274993baf16(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_207:
	leaq	.Lalloc_e7d597e886389bf4929ba3f64374f272(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_208:
	leaq	.Lalloc_7fac7df5e977cd9a082f00789d8d6c46(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow@GOTPCREL(%rip)
.Lfunc_end24:
	.size	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9, .Lfunc_end24-_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9
	.cfi_endproc
