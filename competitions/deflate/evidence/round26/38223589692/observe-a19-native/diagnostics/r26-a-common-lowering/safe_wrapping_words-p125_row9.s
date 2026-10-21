
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
	subq	$136, %rsp
	.cfi_def_cfa_register %rsp
	.cfi_def_cfa_offset 393408
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rcx, %r13
	movq	%rdx, %rbp
	movq	%rsi, %rbx
	movq	%rdi, %rdx
	cmpq	$16, %rsi
	jbe	.LBB24_170
	movabsq	$-7046029254386353131, %r15
	leaq	131208(%rsp), %rdi
	xorl	%r12d, %r12d
	movq	memset@GOTPCREL(%rip), %r14
	movq	%rdx, 48(%rsp)
	movl	$262144, %edx
	xorl	%esi, %esi
	callq	*%r14
	leaq	136(%rsp), %rdi
	movl	$131072, %edx
	xorl	%esi, %esi
	callq	*%r14
	movq	48(%rsp), %rdx
	movq	%r15, %r9
	leaq	16(%rbx), %r11
	leaq	20(%rbp), %rax
	movq	%rax, 72(%rsp)
	movq	%r13, %rax
	negq	%rax
	movq	%rax, 80(%rsp)
	pxor	%xmm0, %xmm0
	movq	$0, 16(%rsp)
	xorl	%r15d, %r15d
	xorl	%r10d, %r10d
	movq	%r13, 24(%rsp)
	movq	%rbp, 32(%rsp)
	jmp	.LBB24_4
.LBB24_96:
	movq	%r10, %r15
.LBB24_104:
	cmpq	%r15, %r10
	cmovbeq	%r15, %r10
	movq	%rax, %r12
	leaq	-8(%rbx), %rax
	cmpq	%rax, %r15
	jae	.LBB24_169
.LBB24_168:
	testq	%r11, %r11
	je	.LBB24_169
.LBB24_4:
	movq	%r12, 8(%rsp)
	cmpq	%r15, %r10
	jae	.LBB24_6
	.p2align	4
.LBB24_5:
	movl	(%rdx,%r10), %eax
	bswapl	%eax
	imulq	%r9, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %ecx
	movl	%r10d, %esi
	andl	$32767, %esi
	movl	%ecx, 136(%rsp,%rsi,4)
	movl	%r10d, 131208(%rsp,%rax,4)
	incq	%r10
	cmpq	%r10, %r15
	jne	.LBB24_5
.LBB24_6:
	decq	%r11
	movq	%r11, 64(%rsp)
	movl	(%rdx,%r15), %eax
	movd	%eax, %xmm1
	movdqa	%xmm1, 112(%rsp)
	movzbl	115(%rsp), %r13d
	bswapl	%eax
	imulq	%r9, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %r11d
	movl	%r15d, %ecx
	andl	$32767, %ecx
	movl	%r11d, 136(%rsp,%rcx,4)
	movl	%r15d, 131208(%rsp,%rax,4)
	leaq	1(%r15), %r10
	movq	%rbx, %rcx
	subq	%r15, %rcx
	cmpq	$258, %rcx
	movl	$258, %r12d
	cmovbq	%rcx, %r12
	cmpq	$128, %rcx
	movl	$128, %eax
	cmovaeq	%rax, %rcx
	movq	%rcx, 40(%rsp)
	movl	%r12d, %eax
	andl	$504, %eax
	movq	%rax, 56(%rsp)
	leaq	7(%rdx), %rax
	leaq	(%rax,%r15), %r9
	movl	$12, %ebp
	movl	$3, %edi
	movq	$0, (%rsp)
	.p2align	4
.LBB24_7:
	movq	%r15, %r8
	subq	%r11, %r8
	leaq	-1(%r8), %rax
	cmpq	$32767, %rax
	ja	.LBB24_33
	leaq	(%r11,%rdi), %rax
	cmpq	%rbx, %rax
	jae	.LBB24_33
	cmpb	%r13b, (%rdx,%rax)
	jne	.LBB24_31
	movq	%rdi, %r14
	leaq	7(%rdx), %rax
	leaq	(%rax,%r11), %rsi
	movq	$-8, %rax
	jmp	.LBB24_12
	.p2align	4
.LBB24_11:
	movq	1(%r9,%rax), %rcx
	bswapq	%rcx
	addq	$8, %rax
	cmpq	%rcx, %rdi
	jne	.LBB24_19
.LBB24_12:
	leaq	16(%rax), %rcx
	cmpq	%r12, %rcx
	ja	.LBB24_20
	leaq	(%r11,%rax), %rcx
	addq	$16, %rcx
	cmpq	%rbx, %rcx
	jbe	.LBB24_15
	xorl	%edi, %edi
	jmp	.LBB24_16
	.p2align	4
.LBB24_15:
	movq	1(%rsi,%rax), %rdi
	bswapq	%rdi
.LBB24_16:
	leaq	(%r15,%rax), %rcx
	addq	$8, %rcx
	cmpq	$-9, %rcx
	ja	.LBB24_179
	leaq	(%r15,%rax), %rcx
	addq	$16, %rcx
	cmpq	%rbx, %rcx
	jbe	.LBB24_11
	xorl	%ecx, %ecx
	addq	$8, %rax
	cmpq	%rcx, %rdi
	je	.LBB24_12
.LBB24_19:
	xorq	%rdi, %rcx
	bsrq	%rcx, %rsi
	xorl	$56, %esi
	shrl	$3, %esi
	orq	%rax, %rsi
	jmp	.LBB24_26
	.p2align	4
.LBB24_20:
	movq	56(%rsp), %rax
	movq	%rax, %rsi
	cmpq	%r12, %rax
	je	.LBB24_26
	.p2align	4
.LBB24_21:
	leaq	(%rsi,%r11), %rdi
	cmpq	%rbx, %rdi
	jae	.LBB24_181
	movq	%rsi, %rax
	addq	%r15, %rax
	jb	.LBB24_180
	cmpq	%rbx, %rax
	jae	.LBB24_182
	movzbl	(%rdx,%rdi), %ecx
	movzbl	(%rdx,%rax), %eax
	xorl	%edi, %edi
	cmpb	%al, %cl
	sete	%dil
	addq	%rdi, %rsi
	cmpb	%al, %cl
	jne	.LBB24_26
	cmpq	%r12, %rsi
	jb	.LBB24_21
	.p2align	4
.LBB24_26:
	movq	%r14, %rdi
	cmpq	%r14, %rsi
	jbe	.LBB24_31
	cmpq	40(%rsp), %rsi
	jae	.LBB24_86
	movq	%rsi, %rax
	addq	%r15, %rax
	jb	.LBB24_191
	cmpq	%rbx, %rax
	jae	.LBB24_86
	movzbl	(%rdx,%rax), %r13d
	movq	%r8, (%rsp)
	movq	%rsi, %rdi
.LBB24_31:
	movl	%r11d, %eax
	andl	$32767, %eax
	movl	136(%rsp,%rax,4), %eax
	cmpq	%rax, %r11
	jbe	.LBB24_33
	movq	%rax, %r11
	decq	%rbp
	jne	.LBB24_7
	.p2align	4
.LBB24_33:
	movq	(%rsp), %rsi
	testq	%rsi, %rsi
	movq	32(%rsp), %rbp
	je	.LBB24_87
.LBB24_34:
	cmpq	$63, %rdi
	movq	24(%rsp), %r13
	movq	8(%rsp), %r12
	ja	.LBB24_85
	leaq	8(%rdx), %rax
	addq	%r15, %rax
	movq	%rax, 56(%rsp)
	movq	%r15, %r14
	notq	%r14
	addq	%rbx, %r14
	leaq	-8(%rbx), %rax
	cmpq	%r10, %rax
	cmovaq	%rax, %r10
	cmpq	%r13, %r12
	movq	%r13, %rax
	cmovaq	%r12, %rax
	movq	%rax, 16(%rsp)
.LBB24_36:
	movq	%r15, %r8
	cmpq	$258, %r14
	movl	$258, %r11d
	cmovbq	%r14, %r11
	incq	%r15
	leaq	-8(%rbx), %rax
	cmpq	%rax, %r15
	jae	.LBB24_106
	movl	1(%rdx,%r8), %eax
	bswapl	%eax
	movabsq	$-7046029254386353131, %rcx
	imulq	%rcx, %rax
	shrq	$48, %rax
	movl	131208(%rsp,%rax,4), %r13d
	movl	%r15d, %ecx
	andl	$32767, %ecx
	movl	%r13d, 136(%rsp,%rcx,4)
	leaq	-1(%rdi), %r9
	cmpq	$4, %r9
	movl	$3, %ecx
	cmovbq	%rcx, %r9
	movl	%r15d, 131208(%rsp,%rax,4)
	movq	%rbx, %rbp
	subq	%r15, %rbp
	cmpq	$258, %rbp
	movl	$258, %eax
	cmovaeq	%rax, %rbp
	leaq	(%r9,%r15), %rax
	cmpq	%rbx, %rax
	jae	.LBB24_39
	movzbl	(%rdx,%rax), %eax
	jmp	.LBB24_40
	.p2align	4
.LBB24_39:
	xorl	%eax, %eax
.LBB24_40:
	movq	%r15, %rsi
	subq	%r13, %rsi
	leaq	-1(%rsi), %rcx
	cmpq	$32767, %rcx
	ja	.LBB24_93
	leaq	(%r9,%r13), %rcx
	cmpq	%rbx, %rcx
	jae	.LBB24_93
	cmpb	%al, (%rdx,%rcx)
	jne	.LBB24_93
	movq	%r14, 40(%rsp)
	movq	%rdi, 8(%rsp)
	movq	%rsi, %r14
	movq	%r12, %rsi
	andl	$504, %r11d
	leaq	7(%rdx), %rax
	leaq	(%rax,%r13), %rdi
	movq	$-8, %rax
	jmp	.LBB24_45
	.p2align	4
.LBB24_44:
	movq	56(%rsp), %rcx
	movq	1(%rcx,%rax), %rcx
	bswapq	%rcx
	addq	$8, %rax
	cmpq	%rcx, %r12
	jne	.LBB24_52
.LBB24_45:
	leaq	16(%rax), %rcx
	cmpq	%rbp, %rcx
	ja	.LBB24_53
	leaq	(%rax,%r13), %rcx
	addq	$16, %rcx
	cmpq	%rbx, %rcx
	jbe	.LBB24_48
	xorl	%r12d, %r12d
	jmp	.LBB24_49
	.p2align	4
.LBB24_48:
	movq	1(%rdi,%rax), %r12
	bswapq	%r12
.LBB24_49:
	leaq	(%r8,%rax), %rcx
	addq	$9, %rcx
	cmpq	$-9, %rcx
	ja	.LBB24_179
	leaq	(%r8,%rax), %rcx
	addq	$17, %rcx
	cmpq	%rbx, %rcx
	jbe	.LBB24_44
	xorl	%ecx, %ecx
	addq	$8, %rax
	cmpq	%rcx, %r12
	je	.LBB24_45
.LBB24_52:
	xorq	%r12, %rcx
	bsrq	%rcx, %r11
	xorl	$56, %r11d
	shrl	$3, %r11d
	orq	%rax, %r11
	movq	%rsi, %r12
	movq	%r14, %rsi
	cmpq	%r9, %r11
	ja	.LBB24_61
	jmp	.LBB24_84
	.p2align	4
.LBB24_53:
	cmpq	%rbp, %r11
	movq	%rsi, %r12
	movq	%r14, %rsi
	jae	.LBB24_60
	.p2align	4
.LBB24_54:
	movq	%r11, %rdi
	addq	%r13, %rdi
	jb	.LBB24_183
	cmpq	%rbx, %rdi
	jae	.LBB24_181
	leaq	(%r11,%r15), %rax
	cmpq	%r8, %rax
	jbe	.LBB24_180
	cmpq	%rbx, %rax
	jae	.LBB24_182
	movzbl	(%rdx,%rdi), %ecx
	movzbl	(%rdx,%rax), %eax
	xorl	%esi, %esi
	cmpb	%al, %cl
	sete	%sil
	addq	%rsi, %r11
	cmpb	%al, %cl
	jne	.LBB24_83
	cmpq	%rbp, %r11
	movq	%r14, %rsi
	jb	.LBB24_54
.LBB24_60:
	cmpq	%r9, %r11
	jbe	.LBB24_84
.LBB24_61:
	leaq	-11(%r11), %rdi
	movl	$168, %r9d
	cmpq	$247, %rdi
	movq	24(%rsp), %r13
	movq	32(%rsp), %rbp
	jae	.LBB24_62
	leal	-3(%r11), %eax
	movl	$63, %ecx
	bsrl	%eax, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	movl	$632, %r9d
	subl	%ecx, %r9d
	cmpq	$4, %rsi
	ja	.LBB24_65
.LBB24_63:
	leal	-33554432(%r11), %eax
	cmpl	$-67108864, %eax
	jae	.LBB24_66
	jmp	.LBB24_194
	.p2align	4
.LBB24_62:
	cmpq	$4, %rsi
	jbe	.LBB24_63
.LBB24_65:
	leal	-1(%rsi), %eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	shll	$4, %eax
	subl	%eax, %r9d
	addl	$480, %r9d
	leal	-33554432(%r11), %eax
	cmpl	$-67108864, %eax
	jb	.LBB24_194
.LBB24_66:
	movl	%r11d, %eax
	shll	$6, %eax
	movl	%eax, %ecx
	subl	%r9d, %ecx
	jo	.LBB24_192
	cmpl	$-999999, %ecx
	jl	.LBB24_105
	testq	%rsi, %rsi
	je	.LBB24_105
	movl	$168, %r9d
	cmpq	$247, %rdi
	jae	.LBB24_70
	leal	-3(%r11), %ecx
	movl	$63, %esi
	bsrl	%ecx, %esi
	xorl	$31, %esi
	shll	$4, %esi
	movl	$632, %r9d
	subl	%esi, %r9d
	movq	%r14, %rsi
	cmpq	$4, %rsi
	ja	.LBB24_73
.LBB24_71:
	movq	8(%rsp), %rcx
	subl	%r9d, %eax
	jno	.LBB24_74
	jmp	.LBB24_192
	.p2align	4
.LBB24_70:
	cmpq	$4, %rsi
	jbe	.LBB24_71
.LBB24_73:
	leal	-1(%rsi), %ecx
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %r9d
	addl	$480, %r9d
	movq	8(%rsp), %rcx
	subl	%r9d, %eax
	jo	.LBB24_192
.LBB24_74:
	addq	$-11, %rcx
	movl	$168, %edi
	cmpq	$247, %rcx
	jae	.LBB24_76
	movq	8(%rsp), %rcx
	addl	$-3, %ecx
	movl	$63, %esi
	bsrl	%ecx, %esi
	xorl	$31, %esi
	shll	$4, %esi
	movl	$632, %edi
	subl	%esi, %edi
	movq	%r14, %rsi
.LBB24_76:
	movq	(%rsp), %rcx
	cmpq	$4, %rcx
	jbe	.LBB24_79
	decl	%ecx
	cmpl	$1, %ecx
	movq	40(%rsp), %r14
	jbe	.LBB24_198
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %edi
	addl	$480, %edi
	jmp	.LBB24_80
	.p2align	4
.LBB24_79:
	movq	40(%rsp), %r14
.LBB24_80:
	movq	8(%rsp), %r9
	movl	%r9d, %ecx
	shll	$6, %ecx
	subl	%edi, %ecx
	cmpl	%ecx, %eax
	jle	.LBB24_107
	cmpq	16(%rsp), %r12
	je	.LBB24_195
	movzbl	(%rdx,%r8), %eax
	movl	%eax, (%rbp,%r12,4)
	incq	%r12
	decq	%r14
	incq	56(%rsp)
	movq	%r11, %rdi
	movq	%rsi, (%rsp)
	cmpq	$64, %r11
	jb	.LBB24_36
	jmp	.LBB24_108
.LBB24_83:
	movq	%r14, %rsi
	cmpq	%r9, %r11
	ja	.LBB24_61
.LBB24_84:
	leaq	2(%r8), %r10
	movq	%r8, %r15
	movq	(%rsp), %rsi
	movq	8(%rsp), %r11
	jmp	.LBB24_94
.LBB24_86:
	movq	%rsi, %rdi
	movq	%r8, (%rsp)
	movq	(%rsp), %rsi
	testq	%rsi, %rsi
	movq	32(%rsp), %rbp
	jne	.LBB24_34
	.p2align	4
.LBB24_87:
	movq	24(%rsp), %r13
	movq	8(%rsp), %rdi
	cmpq	%r13, %rdi
	movabsq	$-7046029254386353131, %r9
	movq	64(%rsp), %r11
	jae	.LBB24_193
	movd	%xmm1, %eax
	movzbl	%al, %eax
	movl	%eax, (%rbp,%rdi,4)
	movq	16(%rsp), %rcx
	incq	%rcx
	leaq	-8(%rbx), %r12
	je	.LBB24_199
	movq	%rcx, 16(%rsp)
	shrq	$6, %rcx
	leaq	1(%rdi), %rax
	testq	%rcx, %rcx
	je	.LBB24_96
	cmpq	%r12, %r10
	jae	.LBB24_96
	cmpq	$1000000, %rcx
	movl	$1000000, %esi
	cmovaeq	%rsi, %rcx
	leaq	-10(%rbx), %rsi
	subq	%r15, %rsi
	leaq	-1(%rcx), %r8
	cmpq	%r8, %rsi
	cmovaeq	%r8, %rsi
	movq	%rdi, %r11
	notq	%r11
	addq	%r13, %r11
	cmpq	%r11, %rsi
	cmovbq	%rsi, %r11
	incq	%r11
	cmpq	$8, %r11
	ja	.LBB24_97
	movq	%r10, %rsi
	jmp	.LBB24_99
.LBB24_93:
	leaq	2(%r8), %r10
	movq	%r8, %r15
	movq	(%rsp), %rsi
	movq	%rdi, %r11
.LBB24_94:
	movq	24(%rsp), %r13
	movq	32(%rsp), %rbp
	leaq	-1(%r12), %r14
	cmpq	%r13, %r14
	movq	%r12, 8(%rsp)
	jb	.LBB24_109
	jmp	.LBB24_154
.LBB24_97:
	movl	%r11d, %esi
	andl	$7, %esi
	movl	$8, %r8d
	cmoveq	%r8, %rsi
	subq	%rsi, %r11
	addq	%r11, %rax
	leaq	(%r10,%r11), %rsi
	subq	%r11, %rcx
	movq	72(%rsp), %r8
	leaq	(%r8,%rdi,4), %r8
	leaq	5(%rdx), %rdi
	addq	%rdi, %r15
	xorl	%r9d, %r9d
	.p2align	4
.LBB24_98:
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
	jne	.LBB24_98
.LBB24_99:
	leaq	(,%rax,4), %rdx
	addq	%rbp, %rdx
	movq	80(%rsp), %rdi
	addq	%rax, %rdi
	movq	48(%rsp), %r8
	addq	%rsi, %r8
	decq	%rcx
	xorl	%r9d, %r9d
	.p2align	4
.LBB24_100:
	movq	%rdi, %r11
	addq	%r9, %r11
	je	.LBB24_184
	movzbl	(%r8,%r9), %r11d
	movl	%r11d, (%rdx,%r9,4)
	leaq	1(%r9), %r11
	cmpq	%r9, %rcx
	je	.LBB24_103
	leaq	(%r9,%rsi), %r14
	incq	%r14
	movq	%r11, %r9
	cmpq	%r12, %r14
	jb	.LBB24_100
.LBB24_103:
	addq	%r11, %rax
	addq	%r11, %rsi
	movq	%rsi, %r15
	movabsq	$-7046029254386353131, %r9
	movq	64(%rsp), %r11
	movq	48(%rsp), %rdx
	jmp	.LBB24_104
.LBB24_105:
	leaq	2(%r8), %r10
	movq	%r8, %r15
	movq	(%rsp), %rsi
	movq	8(%rsp), %r11
	leaq	-1(%r12), %r14
	cmpq	%r13, %r14
	movq	%r12, 8(%rsp)
	jb	.LBB24_109
	jmp	.LBB24_154
.LBB24_106:
	movq	%r8, %r15
	movq	(%rsp), %rsi
	.p2align	4
.LBB24_85:
	movq	%rdi, %r11
	leaq	-1(%r12), %r14
	cmpq	%r13, %r14
	movq	%r12, 8(%rsp)
	jae	.LBB24_154
.LBB24_109:
	cmpq	$257, %r11
	ja	.LBB24_154
	cmpq	%r15, %rsi
	jae	.LBB24_154
	movq	%rsi, %rax
	negq	%rax
	movq	%rax, 104(%rsp)
	movq	%rdx, %rax
	subq	%rsi, %rax
	movq	%rax, 96(%rsp)
	xorl	%r12d, %r12d
	movq	%rsi, 16(%rsp)
	.p2align	4
.LBB24_112:
	movl	(%rbp,%r14,4), %edi
	cmpq	$256, %rdi
	jae	.LBB24_117
	leaq	-1(%r15), %rdi
	cmpq	%rbx, %rdi
	jae	.LBB24_186
	movq	%rdi, %rax
	subq	%rsi, %rax
	cmpq	%rbx, %rax
	jae	.LBB24_185
	movzbl	(%rdx,%rdi), %ecx
	movl	$16, %r8d
	cmpb	(%rdx,%rax), %cl
	jne	.LBB24_122
	incq	%r11
	incq	%r12
	movq	%rdi, %r15
	movq	%r12, %r8
	movq	%r14, 8(%rsp)
	jmp	.LBB24_122
	.p2align	4
.LBB24_117:
	movl	$16, %r8d
	cmpl	$16777215, %edi
	jbe	.LBB24_122
	movzbl	%dil, %r9d
	leaq	(%r11,%r9), %rax
	addq	$3, %rax
	cmpq	$258, %rax
	ja	.LBB24_122
	addq	$3, %r9
	movq	%r15, %rdx
	subq	%r9, %rdx
	jb	.LBB24_121
	movq	%rdx, %rcx
	subq	%rsi, %rcx
	movq	%rcx, (%rsp)
	jae	.LBB24_126
.LBB24_121:
	movq	48(%rsp), %rdx
	.p2align	4
.LBB24_122:
	cmpq	$15, %r8
	ja	.LBB24_154
	movq	8(%rsp), %rax
	leaq	-1(%rax), %r14
	cmpq	%r13, %r14
	jae	.LBB24_154
	cmpq	$257, %r11
	ja	.LBB24_154
	movq	%r8, %r12
	cmpq	%r15, %rsi
	jb	.LBB24_112
	jmp	.LBB24_154
.LBB24_126:
	movq	%rdx, 40(%rsp)
	movq	%rax, 88(%rsp)
	movl	%r9d, %ecx
	andl	$-8, %ecx
	movq	104(%rsp), %rax
	addq	%r15, %rax
	movzbl	%dil, %esi
	subq	%rsi, %rax
	movq	%r15, %rdi
	subq	%rsi, %rdi
	movq	96(%rsp), %rsi
	leaq	(%rsi,%rdi), %rdx
	movq	%rdx, 56(%rsp)
	movq	48(%rsp), %rdx
	movl	$8, %r13d
	jmp	.LBB24_128
	.p2align	4
.LBB24_127:
	leaq	(%rdx,%rdi), %rbp
	movq	-11(%rbp,%r13), %rbp
	bswapq	%rbp
	addq	$8, %r13
	cmpq	%rbp, %rsi
	movq	32(%rsp), %rbp
	jne	.LBB24_136
.LBB24_128:
	cmpq	%r9, %r13
	ja	.LBB24_137
	leaq	(%rax,%r13), %rsi
	addq	$-11, %rsi
	cmpq	$-9, %rsi
	ja	.LBB24_179
	leaq	(%rax,%r13), %rsi
	addq	$-3, %rsi
	cmpq	%rbx, %rsi
	jbe	.LBB24_132
	xorl	%esi, %esi
	jmp	.LBB24_133
	.p2align	4
.LBB24_132:
	movq	56(%rsp), %rsi
	movq	-11(%rsi,%r13), %rsi
	bswapq	%rsi
.LBB24_133:
	leaq	(%rdi,%r13), %rbp
	addq	$-11, %rbp
	cmpq	$-9, %rbp
	ja	.LBB24_179
	leaq	(%rdi,%r13), %rbp
	addq	$-3, %rbp
	cmpq	%rbx, %rbp
	jbe	.LBB24_127
	xorl	%ebp, %ebp
	addq	$8, %r13
	cmpq	%rbp, %rsi
	movq	32(%rsp), %rbp
	je	.LBB24_128
.LBB24_136:
	movq	24(%rsp), %r13
	movq	16(%rsp), %rsi
	jmp	.LBB24_122
.LBB24_137:
	cmpl	%r9d, %ecx
	movq	24(%rsp), %r13
	movq	16(%rsp), %rsi
	je	.LBB24_153
	movq	%rcx, %rax
	addq	(%rsp), %rax
	jb	.LBB24_200
	cmpq	$-9, %rax
	ja	.LBB24_200
	leaq	8(%rax), %rsi
	cmpq	%rbx, %rsi
	ja	.LBB24_144
	movq	%rcx, %rsi
	addq	40(%rsp), %rsi
	jb	.LBB24_202
	cmpq	$-9, %rsi
	ja	.LBB24_202
	leaq	8(%rsi), %rdi
	cmpq	%rbx, %rdi
	jbe	.LBB24_151
	.p2align	4
.LBB24_144:
	movq	%rcx, %rdi
	addq	(%rsp), %rdi
	jb	.LBB24_188
	cmpq	%rbx, %rdi
	jae	.LBB24_189
	movq	%rcx, %rax
	addq	40(%rsp), %rax
	jb	.LBB24_187
	cmpq	%rbx, %rax
	jae	.LBB24_190
	movzbl	(%rdx,%rdi), %esi
	movzbl	(%rdx,%rax), %eax
	xorl	%edi, %edi
	cmpb	%al, %sil
	sete	%bpl
	jne	.LBB24_150
	movb	%bpl, %dil
	addq	%rdi, %rcx
	cmpq	%r9, %rcx
	jb	.LBB24_144
.LBB24_150:
	cmpb	%al, %sil
	movq	32(%rsp), %rbp
	movq	16(%rsp), %rsi
	jne	.LBB24_122
	jmp	.LBB24_153
.LBB24_151:
	leal	(,%r9,8), %ecx
	andl	$56, %ecx
	je	.LBB24_203
	movq	(%rdx,%rsi), %rsi
	xorq	(%rdx,%rax), %rsi
	bswapq	%rsi
	negb	%cl
	shrq	%cl, %rsi
	testq	%rsi, %rsi
	movq	32(%rsp), %rbp
	movq	16(%rsp), %rsi
	jne	.LBB24_122
.LBB24_153:
	incq	%r12
	movq	40(%rsp), %r15
	movq	%r12, %r8
	movq	88(%rsp), %r11
	movq	%r14, 8(%rsp)
	jmp	.LBB24_122
.LBB24_107:
	leaq	2(%r8), %r10
	movq	%r8, %r15
	movq	(%rsp), %rsi
	movq	%r9, %r11
	leaq	-1(%r12), %r14
	cmpq	%r13, %r14
	movq	%r12, 8(%rsp)
	jb	.LBB24_109
	jmp	.LBB24_154
.LBB24_108:
	addq	$2, %r8
	movq	%r8, %r10
	leaq	-1(%r12), %r14
	cmpq	%r13, %r14
	movq	%r12, 8(%rsp)
	jb	.LBB24_109
	.p2align	4
.LBB24_154:
	movq	8(%rsp), %r12
	cmpq	%r13, %r12
	jae	.LBB24_196
	shll	$8, %esi
	leal	(%rsi,%r11), %eax
	addl	$16776957, %eax
	movl	%eax, (%rbp,%r12,4)
	addq	%r11, %r15
	jb	.LBB24_197
	leaq	16(%r10), %rax
	cmpq	%rax, %r15
	cmovbq	%r15, %rax
	leaq	-8(%rbx), %rcx
	cmpq	%rcx, %rax
	cmovaeq	%rcx, %rax
	cmpq	%rax, %r10
	movabsq	$-7046029254386353131, %r9
	movq	64(%rsp), %r11
	jae	.LBB24_159
	.p2align	4
.LBB24_157:
	movl	(%rdx,%r10), %ecx
	bswapl	%ecx
	imulq	%r9, %rcx
	shrq	$48, %rcx
	movl	131208(%rsp,%rcx,4), %esi
	movl	%r10d, %edi
	andl	$32767, %edi
	movl	%esi, 136(%rsp,%rdi,4)
	movl	%r10d, 131208(%rsp,%rcx,4)
	incq	%r10
	cmpq	%r10, %rax
	jne	.LBB24_157
	movq	%rax, %r10
.LBB24_159:
	movq	%r15, %rax
	subq	$8, %rax
	movl	$0, %ecx
	cmovaeq	%rax, %rcx
	leaq	-8(%rbx), %rax
	cmpq	%rax, %rcx
	cmovaeq	%rax, %rcx
	cmpq	%rcx, %r10
	jae	.LBB24_162
	.p2align	4
.LBB24_160:
	leaq	4(%r10), %rax
	movl	(%rdx,%r10), %esi
	bswapl	%esi
	imulq	%r9, %rsi
	shrq	$48, %rsi
	movl	131208(%rsp,%rsi,4), %edi
	movl	%r10d, 131208(%rsp,%rsi,4)
	andl	$32767, %r10d
	movl	%edi, 136(%rsp,%r10,4)
	movq	%rax, %r10
	cmpq	%rcx, %rax
	jb	.LBB24_160
	leaq	4(%rax), %rcx
	cmpq	%r15, %rcx
	jb	.LBB24_163
	jmp	.LBB24_165
	.p2align	4
.LBB24_162:
	movq	%r10, %rax
	leaq	4(%rax), %rcx
	cmpq	%r15, %rcx
	jae	.LBB24_165
.LBB24_163:
	cmpq	$4, %r15
	jb	.LBB24_201
	leaq	-4(%r15), %rax
.LBB24_165:
	leaq	-8(%rbx), %rcx
	cmpq	%rcx, %r15
	cmovbq	%r15, %rcx
	cmpq	%rcx, %rax
	jae	.LBB24_167
	.p2align	4
.LBB24_166:
	movl	(%rdx,%rax), %esi
	bswapl	%esi
	imulq	%r9, %rsi
	shrq	$48, %rsi
	movl	131208(%rsp,%rsi,4), %edi
	movl	%eax, %r8d
	andl	$32767, %r8d
	movl	%edi, 136(%rsp,%r8,4)
	movl	%eax, 131208(%rsp,%rsi,4)
	incq	%rax
	cmpq	%rcx, %rax
	jb	.LBB24_166
.LBB24_167:
	incq	%r12
	cmpq	%r15, %rax
	cmovbeq	%r15, %rax
	movq	%rax, %r10
	movq	$0, 16(%rsp)
	leaq	-8(%rbx), %rax
	cmpq	%rax, %r15
	jb	.LBB24_168
.LBB24_169:
	cmpq	%rbx, %r15
	jb	.LBB24_171
	jmp	.LBB24_178
.LBB24_170:
	xorl	%r15d, %r15d
	xorl	%r12d, %r12d
	cmpq	%rbx, %r15
	jae	.LBB24_178
.LBB24_171:
	cmpq	%r13, %r12
	movq	%r13, %rdi
	cmovaq	%r12, %rdi
	movq	%r15, %rcx
	notq	%rcx
	addq	%rbx, %rcx
	movq	%rdi, %rax
	subq	%r12, %rax
	cmpq	%rax, %rcx
	cmovbq	%rcx, %rax
	incq	%rax
	cmpq	$8, %rax
	jbe	.LBB24_174
	movl	%eax, %ecx
	andl	$7, %ecx
	movl	$8, %esi
	cmovneq	%rcx, %rsi
	subq	%rsi, %rax
	leaq	16(,%r12,4), %rcx
	addq	%rbp, %rcx
	addq	%rax, %r12
	leaq	(%r15,%rdx), %rsi
	addq	$4, %rsi
	addq	%rax, %r15
	xorl	%r8d, %r8d
	pxor	%xmm0, %xmm0
	.p2align	4
.LBB24_173:
	movd	-4(%rsi,%r8), %xmm1
	movd	(%rsi,%r8), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%rcx,%r8,4)
	movdqu	%xmm2, (%rcx,%r8,4)
	addq	$8, %r8
	cmpq	%r8, %rax
	jne	.LBB24_173
.LBB24_174:
	leaq	(,%r12,4), %rax
	addq	%rbp, %rax
	movq	%r12, %rcx
	subq	%rdi, %rcx
	subq	%r15, %rbx
	addq	%r15, %rdx
	movq	%rdx, %r8
	xorl	%edx, %edx
	.p2align	4
.LBB24_175:
	movq	%rcx, %rsi
	addq	%rdx, %rsi
	je	.LBB24_193
	movzbl	(%r8,%rdx), %esi
	movl	%esi, (%rax,%rdx,4)
	incq	%rdx
	cmpq	%rdx, %rbx
	jne	.LBB24_175
	addq	%rdx, %r12
.LBB24_178:
	movq	%r12, %rax
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
.LBB24_179:
	.cfi_def_cfa_offset 393408
	leaq	.Lalloc_bb314acf14069c2fbedf530b060ebd60(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_180:
	leaq	.Lalloc_44247feb933c63f72105b72612a623ee(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_181:
	leaq	.Lalloc_333f7815cbdde125b13aaef2eac5916c(%rip), %rdx
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_182:
	leaq	.Lalloc_c7b835eab7e4664f8dc21896c854bf2b(%rip), %rdx
	movq	%rax, %rdi
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_183:
	leaq	.Lalloc_ff83526048c448fdb7f174b76564f0a2(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_184:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	movq	%r13, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_185:
	leaq	.Lalloc_a470f1791914be2ed9860c28a94823b8(%rip), %rdx
	movq	%rax, %rdi
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_186:
	leaq	.Lalloc_1f28cc27fa9e18e58cef417bee4fd90b(%rip), %rdx
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_187:
	leaq	.Lalloc_0dafef88f4ad7c766190399efdbc2565(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_188:
	leaq	.Lalloc_f491bec5a0814d991fa65b29bceb4569(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_189:
	leaq	.Lalloc_6423c6cb6214cc14d5219f2068f396e1(%rip), %rdx
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_190:
	leaq	.Lalloc_6298bd754cf21e84e6b31996eea28f6b(%rip), %rdx
	movq	%rax, %rdi
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_191:
	leaq	.Lalloc_5082c7ce777234b7475a595bf60db7a2(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_192:
	leaq	.Lalloc_72bac528c0514d634dbb2acaf4e914ed(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_193:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_194:
	leaq	.Lalloc_72bac528c0514d634dbb2acaf4e914ed(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow@GOTPCREL(%rip)
.LBB24_195:
	leaq	.Lalloc_ce72d480401e07b7a290039044612259(%rip), %rdx
	movq	%r12, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_196:
	leaq	.Lalloc_950cb3d32dbfbf973f57d9a20abe6695(%rip), %rdx
	movq	%r12, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_197:
	leaq	.Lalloc_dc5ae93321079a7792fc0613ca37a43e(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_198:
	leaq	.Lalloc_cc8257d2c78dd28d3d4ac89f580613b9(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_199:
	leaq	.Lalloc_6c101138787766aed78cb0daf47995e1(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_200:
	leaq	.Lalloc_410f560b7db958092bd73a0bb4ae0379(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_201:
	leaq	.Lalloc_30e260b757f13d4a959ad3a108dff26e(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_202:
	leaq	.Lalloc_25f0ab118ce3ac29922df37c6b354aae(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_203:
	leaq	.Lalloc_0d9222021d7218fa4f635bbfc4f9297d(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow@GOTPCREL(%rip)
.Lfunc_end24:
	.size	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9, .Lfunc_end24-_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9
	.cfi_endproc
