
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
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	%rsi, %rbx
	movq	%rdi, %r15
	cmpq	$16, %rsi
	movq	%rdx, 8(%rsp)
	jbe	.LBB24_177
	movabsq	$-7046029254386353131, %rbp
	leaq	131240(%rsp), %rdi
	movq	$0, 32(%rsp)
	movq	memset@GOTPCREL(%rip), %r14
	movl	$262144, %edx
	xorl	%esi, %esi
	callq	*%r14
	leaq	168(%rsp), %rdi
	movl	$131072, %edx
	xorl	%esi, %esi
	callq	*%r14
	movq	%rbp, %r8
	leaq	16(%rbx), %r10
	leaq	7(%r15), %rax
	movq	%rax, 96(%rsp)
	leaq	8(%r15), %rax
	movq	%rax, 128(%rsp)
	leaq	20(%r12), %rax
	movq	%rax, 112(%rsp)
	leaq	5(%r15), %rax
	movq	%rax, 104(%rsp)
	movq	%r13, %rax
	negq	%rax
	movq	%rax, 120(%rsp)
	pxor	%xmm0, %xmm0
	movq	$0, 16(%rsp)
	xorl	%r11d, %r11d
	xorl	%ecx, %ecx
	movq	%r13, 48(%rsp)
	jmp	.LBB24_4
.LBB24_146:
	movq	%rcx, %r11
.LBB24_154:
	cmpq	%r11, %rcx
	cmovbeq	%r11, %rcx
	movq	%rax, 32(%rsp)
	leaq	-8(%rbx), %rax
	cmpq	%rax, %r11
	jae	.LBB24_176
.LBB24_175:
	testq	%r10, %r10
	je	.LBB24_176
.LBB24_4:
	cmpq	%r11, %rcx
	jae	.LBB24_6
	.p2align	4
.LBB24_5:
	movl	(%r15,%rcx), %eax
	bswapl	%eax
	imulq	%r8, %rax
	shrq	$48, %rax
	movl	131240(%rsp,%rax,4), %edx
	movl	%ecx, %esi
	andl	$32767, %esi
	movl	%edx, 168(%rsp,%rsi,4)
	movl	%ecx, 131240(%rsp,%rax,4)
	incq	%rcx
	cmpq	%rcx, %r11
	jne	.LBB24_5
.LBB24_6:
	decq	%r10
	movq	%r10, 80(%rsp)
	movl	(%r15,%r11), %eax
	movd	%eax, %xmm1
	movdqa	%xmm1, 144(%rsp)
	movzbl	147(%rsp), %r10d
	bswapl	%eax
	imulq	%r8, %rax
	shrq	$48, %rax
	movl	131240(%rsp,%rax,4), %edx
	movl	%r11d, %ecx
	andl	$32767, %ecx
	movl	%edx, 168(%rsp,%rcx,4)
	movl	%r11d, 131240(%rsp,%rax,4)
	leaq	1(%r11), %rcx
	movq	%rbx, %rsi
	subq	%r11, %rsi
	cmpq	$258, %rsi
	movl	$258, %r14d
	cmovbq	%rsi, %r14
	cmpq	$128, %rsi
	movl	$128, %eax
	cmovaeq	%rax, %rsi
	movq	%rsi, 56(%rsp)
	movl	%r14d, %eax
	andl	$504, %eax
	movq	%rax, 40(%rsp)
	movq	96(%rsp), %rax
	leaq	(%rax,%r11), %rbp
	movl	$12, %r8d
	movl	$3, %edi
	movq	$0, 24(%rsp)
	.p2align	4
.LBB24_7:
	movq	%r11, %r13
	subq	%rdx, %r13
	leaq	-1(%r13), %rax
	cmpq	$32767, %rax
	ja	.LBB24_34
	leaq	(%rdx,%rdi), %rax
	cmpq	%rbx, %rax
	jae	.LBB24_34
	cmpb	%r10b, (%r15,%rax)
	jne	.LBB24_32
	movq	%rdi, %r9
	movq	96(%rsp), %rax
	leaq	(%rax,%rdx), %rsi
	movq	$-8, %rax
	jmp	.LBB24_12
	.p2align	4
.LBB24_11:
	movq	1(%rbp,%rax), %r12
	bswapq	%r12
	addq	$8, %rax
	cmpq	%r12, %rdi
	jne	.LBB24_20
.LBB24_12:
	leaq	16(%rax), %rdi
	cmpq	%r14, %rdi
	ja	.LBB24_21
	leaq	(%rdx,%rax), %rdi
	addq	$8, %rdi
	cmpq	$-9, %rdi
	ja	.LBB24_187
	leaq	(%rdx,%rax), %rdi
	addq	$16, %rdi
	cmpq	%rbx, %rdi
	jbe	.LBB24_16
	xorl	%edi, %edi
	jmp	.LBB24_17
	.p2align	4
.LBB24_16:
	movq	1(%rsi,%rax), %rdi
	bswapq	%rdi
.LBB24_17:
	leaq	(%r11,%rax), %r12
	addq	$8, %r12
	cmpq	$-9, %r12
	ja	.LBB24_187
	leaq	(%r11,%rax), %r12
	addq	$16, %r12
	cmpq	%rbx, %r12
	jbe	.LBB24_11
	xorl	%r12d, %r12d
	addq	$8, %rax
	cmpq	%r12, %rdi
	je	.LBB24_12
.LBB24_20:
	xorq	%rdi, %r12
	bsrq	%r12, %rsi
	xorl	$56, %esi
	shrl	$3, %esi
	orq	%rax, %rsi
	jmp	.LBB24_27
	.p2align	4
.LBB24_21:
	movq	40(%rsp), %rax
	movq	%rax, %rsi
	cmpq	%r14, %rax
	je	.LBB24_27
	.p2align	4
.LBB24_22:
	leaq	(%rsi,%rdx), %rdi
	cmpq	%rbx, %rdi
	jae	.LBB24_188
	movq	%rsi, %rax
	addq	%r11, %rax
	jb	.LBB24_189
	cmpq	%rbx, %rax
	jae	.LBB24_190
	movzbl	(%r15,%rdi), %edi
	movzbl	(%r15,%rax), %eax
	xorl	%r12d, %r12d
	cmpb	%al, %dil
	sete	%r12b
	addq	%r12, %rsi
	cmpb	%al, %dil
	jne	.LBB24_27
	cmpq	%r14, %rsi
	jb	.LBB24_22
	.p2align	4
.LBB24_27:
	movq	%r9, %rdi
	cmpq	%r9, %rsi
	jbe	.LBB24_32
	cmpq	56(%rsp), %rsi
	jae	.LBB24_138
	movq	%rsi, %rax
	addq	%r11, %rax
	jb	.LBB24_200
	cmpq	%rbx, %rax
	jae	.LBB24_138
	movzbl	(%r15,%rax), %r10d
	movq	%r13, 24(%rsp)
	movq	%rsi, %rdi
.LBB24_32:
	cmpq	$1, %r8
	je	.LBB24_34
	movl	%edx, %eax
	andl	$32767, %eax
	movl	168(%rsp,%rax,4), %eax
	decq	%r8
	cmpq	%rax, %rdx
	cmovaeq	%rax, %rdx
	ja	.LBB24_7
.LBB24_34:
	movq	24(%rsp), %rdx
	testq	%rdx, %rdx
	movq	8(%rsp), %rsi
	je	.LBB24_139
.LBB24_35:
	cmpq	$63, %rdi
	movq	48(%rsp), %r13
	movq	32(%rsp), %r9
	ja	.LBB24_86
	movq	128(%rsp), %rax
	addq	%r11, %rax
	movq	%rax, 56(%rsp)
	movq	%r11, %r12
	notq	%r12
	addq	%rbx, %r12
	leaq	-8(%rbx), %rax
	cmpq	%rcx, %rax
	movq	%rcx, %r8
	cmovaq	%rax, %r8
	movq	%r8, 72(%rsp)
	cmpq	%r13, %r9
	movq	%r13, %rax
	cmovaq	%r9, %rax
	movq	%rax, 88(%rsp)
.LBB24_37:
	leaq	1(%r11), %rbp
	cmpq	$258, %r12
	movl	$258, %r8d
	cmovbq	%r12, %r8
	leaq	-8(%rbx), %rax
	cmpq	%rax, %rbp
	jae	.LBB24_157
	movq	%rdx, 24(%rsp)
	movl	1(%r15,%r11), %eax
	bswapl	%eax
	movabsq	$-7046029254386353131, %rdx
	imulq	%rdx, %rax
	shrq	$48, %rax
	movl	131240(%rsp,%rax,4), %edx
	movl	%ebp, %esi
	andl	$32767, %esi
	movl	%edx, 168(%rsp,%rsi,4)
	leaq	-1(%rdi), %r13
	cmpq	$4, %r13
	movl	$3, %esi
	cmovbq	%rsi, %r13
	movl	%ebp, 131240(%rsp,%rax,4)
	movq	%rbx, %r14
	subq	%rbp, %r14
	cmpq	$258, %r14
	movl	$258, %esi
	cmovbq	%r14, %rsi
	cmpq	$128, %r14
	movl	$128, %eax
	cmovaeq	%rax, %r14
	movq	%r13, %rax
	addq	%rbp, %rax
	cmpq	%rbx, %rax
	movq	%rdi, 16(%rsp)
	jae	.LBB24_40
	movzbl	(%r15,%rax), %eax
	jmp	.LBB24_41
	.p2align	4
.LBB24_40:
	xorl	%eax, %eax
.LBB24_41:
	leaq	1(%rcx), %r10
	movq	%rbp, %rdi
	subq	%rdx, %rdi
	movq	%rdi, 40(%rsp)
	decq	%rdi
	cmpq	$32768, %rdi
	jae	.LBB24_89
	leaq	(%rdx,%r13), %rdi
	cmpq	%rbx, %rdi
	jae	.LBB24_89
	cmpb	%al, (%r15,%rdi)
	jne	.LBB24_89
	movq	%r12, 64(%rsp)
	movq	%r9, 32(%rsp)
	andl	$504, %r8d
	movq	96(%rsp), %rax
	leaq	(%rax,%rdx), %rdi
	movq	$-8, %rax
	jmp	.LBB24_46
	.p2align	4
.LBB24_45:
	movq	56(%rsp), %r9
	movq	1(%r9,%rax), %r9
	bswapq	%r9
	addq	$8, %rax
	cmpq	%r9, %r12
	jne	.LBB24_54
.LBB24_46:
	leaq	16(%rax), %r9
	cmpq	%rsi, %r9
	ja	.LBB24_55
	leaq	(%rdx,%rax), %r9
	addq	$16, %r9
	cmpq	%rbx, %r9
	jbe	.LBB24_49
	xorl	%r12d, %r12d
	jmp	.LBB24_50
	.p2align	4
.LBB24_49:
	movq	1(%rdi,%rax), %r12
	bswapq	%r12
.LBB24_50:
	cmpq	%r11, %rcx
	jbe	.LBB24_191
	leaq	(%r11,%rax), %r9
	addq	$9, %r9
	cmpq	$-9, %r9
	ja	.LBB24_187
	leaq	(%r11,%rax), %r9
	addq	$17, %r9
	cmpq	%rbx, %r9
	jbe	.LBB24_45
	xorl	%r9d, %r9d
	addq	$8, %rax
	cmpq	%r9, %r12
	je	.LBB24_46
.LBB24_54:
	xorq	%r12, %r9
	bsrq	%r9, %r8
	xorl	$56, %r8d
	shrl	$3, %r8d
	orq	%rax, %r8
	movq	32(%rsp), %r9
	jmp	.LBB24_62
	.p2align	4
.LBB24_55:
	cmpq	%rsi, %r8
	movq	32(%rsp), %r9
	jae	.LBB24_62
	.p2align	4
.LBB24_56:
	movq	%r8, %rdi
	addq	%rdx, %rdi
	jb	.LBB24_192
	cmpq	%rbx, %rdi
	jae	.LBB24_188
	leaq	(%r8,%rbp), %rax
	cmpq	%r11, %rax
	jbe	.LBB24_189
	cmpq	%rbx, %rax
	jae	.LBB24_190
	movzbl	(%r15,%rdi), %ecx
	movzbl	(%r15,%rax), %eax
	xorl	%edi, %edi
	cmpb	%al, %cl
	sete	%dil
	addq	%rdi, %r8
	cmpb	%al, %cl
	jne	.LBB24_62
	cmpq	%rsi, %r8
	jb	.LBB24_56
	.p2align	4
.LBB24_62:
	cmpq	%r13, %r8
	jbe	.LBB24_89
	leaq	-11(%r8), %rcx
	movl	$168, %edx
	cmpq	$247, %rcx
	movq	48(%rsp), %r13
	movq	16(%rsp), %rdi
	jae	.LBB24_64
	leal	-3(%r8), %eax
	movl	$63, %esi
	bsrl	%eax, %esi
	xorl	$31, %esi
	shll	$4, %esi
	movl	$632, %edx
	subl	%esi, %edx
	movq	40(%rsp), %rax
	cmpq	$4, %rax
	movq	64(%rsp), %r12
	ja	.LBB24_67
.LBB24_65:
	leal	-33554432(%r8), %eax
	cmpl	$-67108864, %eax
	jae	.LBB24_68
	jmp	.LBB24_203
	.p2align	4
.LBB24_64:
	movq	40(%rsp), %rax
	cmpq	$4, %rax
	movq	64(%rsp), %r12
	jbe	.LBB24_65
.LBB24_67:
	decl	%eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	shll	$4, %eax
	subl	%eax, %edx
	addl	$480, %edx
	leal	-33554432(%r8), %eax
	cmpl	$-67108864, %eax
	jb	.LBB24_203
.LBB24_68:
	movl	%r8d, %eax
	shll	$6, %eax
	movl	%eax, %esi
	subl	%edx, %esi
	jo	.LBB24_201
	cmpl	$-999999, %esi
	jl	.LBB24_158
	cmpq	%r14, %r8
	jae	.LBB24_72
	leaq	(%r8,%rbp), %rdx
	cmpq	%r11, %rdx
	jbe	.LBB24_200
.LBB24_72:
	cmpq	$0, 40(%rsp)
	movq	8(%rsp), %rsi
	movq	24(%rsp), %r14
	je	.LBB24_156
	movl	$168, %edx
	cmpq	$247, %rcx
	jae	.LBB24_74
	leal	-3(%r8), %ecx
	movl	$63, %esi
	bsrl	%ecx, %esi
	xorl	$31, %esi
	shll	$4, %esi
	movl	$632, %edx
	subl	%esi, %edx
	movq	8(%rsp), %rsi
	movq	40(%rsp), %rcx
	cmpq	$4, %rcx
	ja	.LBB24_77
.LBB24_75:
	subl	%edx, %eax
	jno	.LBB24_78
	jmp	.LBB24_201
	.p2align	4
.LBB24_74:
	movq	40(%rsp), %rcx
	cmpq	$4, %rcx
	jbe	.LBB24_75
.LBB24_77:
	decl	%ecx
	bsrl	%ecx, %ecx
	xorl	$31, %ecx
	shll	$4, %ecx
	subl	%ecx, %edx
	addl	$480, %edx
	subl	%edx, %eax
	jo	.LBB24_201
.LBB24_78:
	leaq	-11(%rdi), %rdx
	movl	$168, %ecx
	cmpq	$247, %rdx
	jae	.LBB24_80
	leal	-3(%rdi), %ecx
	movl	$63, %edx
	bsrl	%ecx, %edx
	xorl	$31, %edx
	shll	$4, %edx
	movl	$632, %ecx
	subl	%edx, %ecx
.LBB24_80:
	cmpq	$4, %r14
	jbe	.LBB24_83
	leal	-1(%r14), %edx
	cmpl	$1, %edx
	jbe	.LBB24_207
	bsrl	%edx, %edx
	xorl	$31, %edx
	shll	$4, %edx
	subl	%edx, %ecx
	addl	$480, %ecx
.LBB24_83:
	movl	%edi, %edx
	shll	$6, %edx
	subl	%ecx, %edx
	cmpl	%edx, %eax
	jle	.LBB24_156
	cmpq	88(%rsp), %r9
	je	.LBB24_204
	movzbl	(%r15,%r11), %eax
	movl	%eax, (%rsi,%r9,4)
	incq	%r9
	decq	%r12
	incq	56(%rsp)
	movq	%r10, %rcx
	movq	%r8, %rdi
	movq	40(%rsp), %rax
	movq	%rax, %rdx
	movq	%rbp, %r11
	cmpq	$64, %r8
	jb	.LBB24_37
	jmp	.LBB24_90
	.p2align	4
.LBB24_86:
	movq	%rcx, %r10
.LBB24_87:
	movq	%r11, %rbp
	movq	%rdx, %rax
.LBB24_88:
	movq	%rdi, %r8
	movq	%rax, 40(%rsp)
	leaq	-1(%r9), %r12
	cmpq	%r13, %r12
	jb	.LBB24_91
.LBB24_159:
	movq	%rbp, %r11
.LBB24_160:
	movq	40(%rsp), %rcx
	jmp	.LBB24_161
.LBB24_89:
	movq	%r11, %rbp
	movq	24(%rsp), %rax
	movq	16(%rsp), %r8
	movq	48(%rsp), %r13
	movq	8(%rsp), %rsi
.LBB24_90:
	movq	%rax, 40(%rsp)
	leaq	-1(%r9), %r12
	cmpq	%r13, %r12
	jae	.LBB24_159
.LBB24_91:
	cmpq	$257, %r8
	movq	40(%rsp), %rcx
	ja	.LBB24_155
	cmpq	%rbp, %rcx
	jae	.LBB24_155
	movq	%rcx, %rax
	negq	%rax
	movq	%rax, 72(%rsp)
	movq	%r15, %rax
	subq	%rcx, %rax
	movq	%rax, 136(%rsp)
	xorl	%r14d, %r14d
	movq	%rbp, %r11
	.p2align	4
.LBB24_94:
	movl	(%rsi,%r12,4), %edi
	cmpq	$256, %rdi
	jae	.LBB24_99
	leaq	-1(%r11), %rdi
	cmpq	%rbx, %rdi
	jae	.LBB24_195
	movq	%rdi, %rax
	subq	%rcx, %rax
	cmpq	%rbx, %rax
	jae	.LBB24_194
	movzbl	(%r15,%rdi), %ecx
	cmpb	(%r15,%rax), %cl
	jne	.LBB24_129
	incq	%r8
	incq	%r14
	movq	%rdi, %r11
	movq	%r14, %rax
	movq	%r12, %r9
	jmp	.LBB24_130
	.p2align	4
.LBB24_99:
	movl	$16, %eax
	cmpl	$16777215, %edi
	jbe	.LBB24_130
	movzbl	%dil, %edx
	leaq	(%r8,%rdx), %rbp
	addq	$3, %rbp
	movq	%rbp, 88(%rsp)
	cmpq	$258, %rbp
	ja	.LBB24_130
	addq	$3, %rdx
	movq	%r11, %rbp
	subq	%rdx, %rbp
	jb	.LBB24_130
	movq	%rbp, 16(%rsp)
	subq	%rcx, %rbp
	movq	%rbp, 64(%rsp)
	jb	.LBB24_130
	movl	%edx, %ecx
	andl	$-8, %ecx
	movq	72(%rsp), %rax
	addq	%r11, %rax
	movzbl	%dil, %esi
	subq	%rsi, %rax
	movq	%r11, %rdi
	subq	%rsi, %rdi
	movq	136(%rsp), %rsi
	addq	%rdi, %rsi
	movq	%rsi, 56(%rsp)
	leaq	(%r15,%rdi), %rsi
	movq	%rsi, 24(%rsp)
	movl	$8, %r13d
	jmp	.LBB24_106
	.p2align	4
.LBB24_104:
	movq	24(%rsp), %rsi
	movq	-11(%rsi,%r13), %rsi
	bswapq	%rsi
.LBB24_105:
	addq	$8, %r13
	cmpq	%rsi, %r9
	movq	%r15, %r9
	movq	%rbp, %r15
	jne	.LBB24_128
.LBB24_106:
	cmpq	%rdx, %r13
	ja	.LBB24_114
	leaq	(%rax,%r13), %rsi
	addq	$-11, %rsi
	cmpq	$-9, %rsi
	ja	.LBB24_187
	movq	%r15, %rbp
	movq	%r9, %r15
	leaq	(%rax,%r13), %rsi
	addq	$-3, %rsi
	cmpq	%rbx, %rsi
	jbe	.LBB24_110
	xorl	%r9d, %r9d
	jmp	.LBB24_111
	.p2align	4
.LBB24_110:
	movq	56(%rsp), %rsi
	movq	-11(%rsi,%r13), %r9
	bswapq	%r9
.LBB24_111:
	leaq	(%rdi,%r13), %rsi
	addq	$-11, %rsi
	cmpq	$-9, %rsi
	ja	.LBB24_187
	leaq	(%rdi,%r13), %rsi
	addq	$-3, %rsi
	cmpq	%rbx, %rsi
	jbe	.LBB24_104
	xorl	%esi, %esi
	jmp	.LBB24_105
.LBB24_114:
	cmpl	%edx, %ecx
	movq	48(%rsp), %r13
	movq	8(%rsp), %rsi
	je	.LBB24_136
	movq	%rcx, %rax
	addq	64(%rsp), %rax
	jb	.LBB24_209
	cmpq	$-9, %rax
	ja	.LBB24_209
	movq	%r9, 32(%rsp)
	leaq	8(%rax), %rsi
	cmpq	%rbx, %rsi
	ja	.LBB24_121
	movq	%rcx, %rdi
	addq	16(%rsp), %rdi
	jb	.LBB24_211
	cmpq	$-9, %rdi
	ja	.LBB24_211
	leaq	8(%rdi), %rsi
	cmpq	%rbx, %rsi
	jbe	.LBB24_134
	.p2align	4
.LBB24_121:
	movq	%rcx, %rdi
	addq	64(%rsp), %rdi
	jb	.LBB24_197
	cmpq	%rbx, %rdi
	movq	16(%rsp), %rsi
	jae	.LBB24_198
	movq	%rcx, %rax
	addq	%rsi, %rax
	jb	.LBB24_196
	cmpq	%rbx, %rax
	jae	.LBB24_199
	movzbl	(%r15,%rdi), %edi
	movzbl	(%r15,%rax), %eax
	xorl	%r9d, %r9d
	cmpb	%al, %dil
	sete	%sil
	jne	.LBB24_127
	movb	%sil, %r9b
	addq	%r9, %rcx
	cmpq	%rdx, %rcx
	jb	.LBB24_121
.LBB24_127:
	cmpb	%al, %dil
	movq	8(%rsp), %rsi
	movq	32(%rsp), %r9
	movl	$16, %eax
	jne	.LBB24_130
	jmp	.LBB24_136
.LBB24_128:
	movq	48(%rsp), %r13
	movq	8(%rsp), %rsi
	.p2align	4
.LBB24_129:
	movl	$16, %eax
.LBB24_130:
	cmpq	$15, %rax
	ja	.LBB24_160
	leaq	-1(%r9), %r12
	cmpq	%r13, %r12
	movq	40(%rsp), %rcx
	jae	.LBB24_161
	cmpq	$257, %r8
	ja	.LBB24_161
	movq	%rax, %r14
	cmpq	%r11, %rcx
	jb	.LBB24_94
	jmp	.LBB24_161
.LBB24_134:
	leal	(,%rdx,8), %ecx
	andl	$56, %ecx
	je	.LBB24_212
	movq	(%r15,%rdi), %rdx
	xorq	(%r15,%rax), %rdx
	bswapq	%rdx
	negb	%cl
	shrq	%cl, %rdx
	testq	%rdx, %rdx
	movq	8(%rsp), %rsi
	movq	32(%rsp), %r9
	movl	$16, %eax
	jne	.LBB24_130
.LBB24_136:
	incq	%r14
	movq	16(%rsp), %r11
	movq	%r14, %rax
	movq	88(%rsp), %r8
	movq	%r12, %r9
	jmp	.LBB24_130
	.p2align	4
.LBB24_155:
	movq	%rbp, %r11
.LBB24_161:
	cmpq	%r13, %r9
	jae	.LBB24_205
	shll	$8, %ecx
	leal	(%rcx,%r8), %eax
	addl	$16776957, %eax
	movl	%eax, (%rsi,%r9,4)
	addq	%r8, %r11
	jb	.LBB24_206
	leaq	16(%r10), %rax
	cmpq	%rax, %r11
	cmovbq	%r11, %rax
	leaq	-8(%rbx), %rcx
	cmpq	%rcx, %rax
	cmovaeq	%rcx, %rax
	cmpq	%rax, %r10
	movabsq	$-7046029254386353131, %r8
	jae	.LBB24_166
	.p2align	4
.LBB24_164:
	movl	(%r15,%r10), %ecx
	bswapl	%ecx
	imulq	%r8, %rcx
	shrq	$48, %rcx
	movl	131240(%rsp,%rcx,4), %edx
	movl	%r10d, %esi
	andl	$32767, %esi
	movl	%edx, 168(%rsp,%rsi,4)
	movl	%r10d, 131240(%rsp,%rcx,4)
	incq	%r10
	cmpq	%r10, %rax
	jne	.LBB24_164
	movq	%rax, %r10
.LBB24_166:
	movq	%r11, %rcx
	subq	$8, %rcx
	movl	$0, %eax
	cmovaeq	%rcx, %rax
	leaq	-8(%rbx), %rcx
	cmpq	%rcx, %rax
	cmovaeq	%rcx, %rax
	cmpq	%rax, %r10
	jae	.LBB24_169
	.p2align	4
.LBB24_167:
	leaq	4(%r10), %rcx
	movl	(%r15,%r10), %edx
	bswapl	%edx
	imulq	%r8, %rdx
	shrq	$48, %rdx
	movl	131240(%rsp,%rdx,4), %esi
	movl	%r10d, 131240(%rsp,%rdx,4)
	andl	$32767, %r10d
	movl	%esi, 168(%rsp,%r10,4)
	movq	%rcx, %r10
	cmpq	%rax, %rcx
	jb	.LBB24_167
	leaq	4(%rcx), %rax
	cmpq	%r11, %rax
	movq	80(%rsp), %r10
	jb	.LBB24_170
	jmp	.LBB24_172
	.p2align	4
.LBB24_169:
	movq	%r10, %rcx
	leaq	4(%rcx), %rax
	cmpq	%r11, %rax
	movq	80(%rsp), %r10
	jae	.LBB24_172
.LBB24_170:
	cmpq	$4, %r11
	jb	.LBB24_210
	leaq	-4(%r11), %rcx
.LBB24_172:
	leaq	-8(%rbx), %rax
	cmpq	%rax, %r11
	cmovbq	%r11, %rax
	cmpq	%rax, %rcx
	jae	.LBB24_174
	.p2align	4
.LBB24_173:
	movl	(%r15,%rcx), %edx
	bswapl	%edx
	imulq	%r8, %rdx
	shrq	$48, %rdx
	movl	131240(%rsp,%rdx,4), %esi
	movl	%ecx, %edi
	andl	$32767, %edi
	movl	%esi, 168(%rsp,%rdi,4)
	movl	%ecx, 131240(%rsp,%rdx,4)
	incq	%rcx
	cmpq	%rax, %rcx
	jb	.LBB24_173
.LBB24_174:
	incq	%r9
	movq	%r9, 32(%rsp)
	cmpq	%r11, %rcx
	cmovbeq	%r11, %rcx
	movq	$0, 16(%rsp)
	movq	8(%rsp), %rsi
	leaq	-8(%rbx), %rax
	cmpq	%rax, %r11
	jb	.LBB24_175
	jmp	.LBB24_176
.LBB24_138:
	movq	%rsi, %rdi
	movq	%r13, 24(%rsp)
	movq	24(%rsp), %rdx
	testq	%rdx, %rdx
	movq	8(%rsp), %rsi
	jne	.LBB24_35
	.p2align	4
.LBB24_139:
	movq	48(%rsp), %r13
	movq	32(%rsp), %rdi
	cmpq	%r13, %rdi
	movabsq	$-7046029254386353131, %r8
	movq	80(%rsp), %r10
	jae	.LBB24_202
	movd	%xmm1, %eax
	movzbl	%al, %eax
	movl	%eax, (%rsi,%rdi,4)
	movq	16(%rsp), %rdx
	incq	%rdx
	je	.LBB24_208
	movq	%rdx, 16(%rsp)
	shrq	$6, %rdx
	leaq	1(%rdi), %rax
	testq	%rdx, %rdx
	je	.LBB24_146
	leaq	-8(%rbx), %r9
	cmpq	%r9, %rcx
	jae	.LBB24_146
	cmpq	$1000000, %rdx
	movl	$1000000, %esi
	cmovaeq	%rsi, %rdx
	leaq	-10(%rbx), %rsi
	subq	%r11, %rsi
	leaq	-1(%rdx), %r8
	cmpq	%r8, %rsi
	cmovaeq	%r8, %rsi
	movq	%rdi, %r10
	notq	%r10
	addq	%r13, %r10
	cmpq	%r10, %rsi
	cmovbq	%rsi, %r10
	incq	%r10
	cmpq	$8, %r10
	ja	.LBB24_147
	movq	%rcx, %rsi
	jmp	.LBB24_149
.LBB24_147:
	movl	%r10d, %esi
	andl	$7, %esi
	movl	$8, %r8d
	cmoveq	%r8, %rsi
	subq	%rsi, %r10
	addq	%r10, %rax
	leaq	(%rcx,%r10), %rsi
	subq	%r10, %rdx
	movq	112(%rsp), %r8
	leaq	(%r8,%rdi,4), %r8
	addq	104(%rsp), %r11
	xorl	%r9d, %r9d
	.p2align	4
.LBB24_148:
	movd	-4(%r11,%r9), %xmm1
	movd	(%r11,%r9), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%r8,%r9,4)
	movdqu	%xmm2, (%r8,%r9,4)
	addq	$8, %r9
	cmpq	%r9, %r10
	jne	.LBB24_148
.LBB24_149:
	movq	8(%rsp), %rdi
	leaq	(%rdi,%rax,4), %rdi
	movq	120(%rsp), %r8
	addq	%rax, %r8
	leaq	(%r15,%rsi), %r9
	decq	%rdx
	xorl	%r10d, %r10d
	.p2align	4
.LBB24_150:
	movq	%r8, %r11
	addq	%r10, %r11
	je	.LBB24_193
	movzbl	(%r9,%r10), %r11d
	movl	%r11d, (%rdi,%r10,4)
	leaq	1(%r10), %r11
	cmpq	%r10, %rdx
	je	.LBB24_153
	leaq	(%r10,%rsi), %r14
	incq	%r14
	movq	%r11, %r10
	leaq	-8(%rbx), %r12
	cmpq	%r12, %r14
	jb	.LBB24_150
.LBB24_153:
	addq	%r11, %rax
	addq	%r11, %rsi
	movq	%rsi, %r11
	movq	8(%rsp), %rsi
	movabsq	$-7046029254386353131, %r8
	movq	80(%rsp), %r10
	jmp	.LBB24_154
.LBB24_156:
	movq	%r11, %rbp
	movq	%r14, %rax
	jmp	.LBB24_88
.LBB24_157:
	movq	72(%rsp), %r10
	jmp	.LBB24_87
.LBB24_158:
	movq	%r11, %rbp
	movq	24(%rsp), %rax
	movq	%rdi, %r8
	movq	8(%rsp), %rsi
	movq	%rax, 40(%rsp)
	leaq	-1(%r9), %r12
	cmpq	%r13, %r12
	jb	.LBB24_91
	jmp	.LBB24_159
.LBB24_177:
	xorl	%r11d, %r11d
	xorl	%eax, %eax
	movq	%r12, %rsi
	cmpq	%rbx, %r11
	jae	.LBB24_186
	jmp	.LBB24_178
.LBB24_176:
	movq	32(%rsp), %rax
	cmpq	%rbx, %r11
	jae	.LBB24_186
.LBB24_178:
	cmpq	%r13, %rax
	movq	%r13, %rdi
	cmovaq	%rax, %rdi
	movq	%r11, %rcx
	notq	%rcx
	addq	%rbx, %rcx
	movq	%rdi, %r8
	subq	%rax, %r8
	cmpq	%r8, %rcx
	cmovbq	%rcx, %r8
	incq	%r8
	cmpq	$8, %r8
	jbe	.LBB24_182
	movl	%r8d, %ecx
	andl	$7, %ecx
	movl	$8, %edx
	cmovneq	%rcx, %rdx
	subq	%rdx, %r8
	leaq	(%rsi,%rax,4), %rcx
	addq	$16, %rcx
	addq	%r8, %rax
	leaq	(%r11,%r15), %rdx
	addq	$4, %rdx
	addq	%r8, %r11
	xorl	%esi, %esi
	pxor	%xmm0, %xmm0
	.p2align	4
.LBB24_180:
	movd	-4(%rdx,%rsi), %xmm1
	movd	(%rdx,%rsi), %xmm2
	punpcklbw	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm1
	punpcklbw	%xmm0, %xmm2
	punpcklwd	%xmm0, %xmm2
	movdqu	%xmm1, -16(%rcx,%rsi,4)
	movdqu	%xmm2, (%rcx,%rsi,4)
	addq	$8, %rsi
	cmpq	%rsi, %r8
	jne	.LBB24_180
	movq	8(%rsp), %rsi
.LBB24_182:
	leaq	(%rsi,%rax,4), %r8
	movq	%rax, %rcx
	subq	%rdi, %rcx
	subq	%r11, %rbx
	addq	%r11, %r15
	xorl	%edx, %edx
	.p2align	4
.LBB24_183:
	movq	%rcx, %rsi
	addq	%rdx, %rsi
	je	.LBB24_202
	movzbl	(%r15,%rdx), %esi
	movl	%esi, (%r8,%rdx,4)
	incq	%rdx
	cmpq	%rdx, %rbx
	jne	.LBB24_183
	addq	%rdx, %rax
.LBB24_186:
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
.LBB24_187:
	.cfi_def_cfa_offset 393440
	leaq	.Lalloc_440babfea49fec204c4bfa4556bd23df(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_188:
	leaq	.Lalloc_d0bf91bac5912d1054a41f50a5372dd0(%rip), %rdx
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_189:
	leaq	.Lalloc_e58248ce06d86db1620e3928ca18f57a(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_190:
	leaq	.Lalloc_c7cb404ab9612aded1ce50ca918ced7b(%rip), %rdx
	movq	%rax, %rdi
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_191:
	leaq	.Lalloc_8dedf8bdbae2e7f670fff12535f0d90a(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_192:
	leaq	.Lalloc_68f9c5f1b64c796baf34863c111ebbab(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_193:
	leaq	.Lalloc_1e808d4a560d2bfb30193cdd1b6f1f95(%rip), %rdx
	movq	%r13, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_194:
	leaq	.Lalloc_3d3fade205e2688424188b5bbd6c946c(%rip), %rdx
	movq	%rax, %rdi
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_195:
	leaq	.Lalloc_1cb241537ee4f281c00fcbb1bef48ab0(%rip), %rdx
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_196:
	leaq	.Lalloc_f89fc433b2ec5f525912d54366fd14b2(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_197:
	leaq	.Lalloc_ec9880852f5ad0b7f675c971d025b4ff(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_198:
	leaq	.Lalloc_c867e779aaf632c8ba08807d62f697ee(%rip), %rdx
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_199:
	leaq	.Lalloc_f7486e32a26ebd3f0532d14c194cbf09(%rip), %rdx
	movq	%rax, %rdi
	movq	%rbx, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_200:
	leaq	.Lalloc_f7734e5b3c0057e9bae084232237166a(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_201:
	leaq	.Lalloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_202:
	leaq	.Lalloc_1e808d4a560d2bfb30193cdd1b6f1f95(%rip), %rdx
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_203:
	leaq	.Lalloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow@GOTPCREL(%rip)
.LBB24_204:
	leaq	.Lalloc_1e808d4a560d2bfb30193cdd1b6f1f95(%rip), %rdx
	movq	%r9, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_205:
	leaq	.Lalloc_91bbba7d8bfca8a214cab7fb1cbd8ce3(%rip), %rdx
	movq	%r9, %rdi
	movq	%r13, %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB24_206:
	leaq	.Lalloc_8c0fdb4f326073e19a6b7eb9b54b4e01(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_207:
	leaq	.Lalloc_9f4d1cf899b26bf5e0e440ccaea53f2f(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_208:
	leaq	.Lalloc_3040782d029b4f1f28da9c0a2089856b(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_209:
	leaq	.Lalloc_5988a9c474509aa3e7e55969f6ad663e(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_210:
	leaq	.Lalloc_94a048f0c628dd665e0545a553ca9ebc(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB24_211:
	leaq	.Lalloc_c2b01cdce33609a4161805adc289533f(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB24_212:
	leaq	.Lalloc_0471675f9abe1475b1e41b49769421c8(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow@GOTPCREL(%rip)
.Lfunc_end24:
	.size	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9, .Lfunc_end24-_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9
	.cfi_endproc
