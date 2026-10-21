	.section	.text._RNvCsera0HrlzTQN_14r26_a_original9a_dp_pass,"ax",@progbits
	.globl	_RNvCsera0HrlzTQN_14r26_a_original9a_dp_pass
	.prefalign	4, .Lfunc_end135, nop
	.type	_RNvCsera0HrlzTQN_14r26_a_original9a_dp_pass,@function
_RNvCsera0HrlzTQN_14r26_a_original9a_dp_pass:
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
	subq	$264, %rsp
	.cfi_def_cfa_offset 320
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	344(%rsp), %rbx
	movq	16(%rbx), %r11
	cmpq	%r11, %r9
	jae	.LBB135_50
	movq	16(%rdx), %rax
	movq	%rax, 104(%rsp)
	cmpq	%rax, %r9
	setae	%al
	cmpq	%rsi, %r9
	seta	%r10b
	orb	%al, %r10b
	jne	.LBB135_50
	movq	352(%rsp), %r12
	movq	16(%r12), %rax
	movq	%rax, 176(%rsp)
	cmpq	%rax, %r9
	ja	.LBB135_50
	leaq	(,%r9,4), %rax
	addq	8(%rbx), %rax
	movq	%r9, %r10
	notq	%r10
	addq	%r11, %r10
	cmpq	$258, %r10
	movl	$258, %r14d
	cmovaeq	%r14, %r10
	movl	%r10d, %r10d
	leaq	4(,%r10,4), %r10
	movq	%rdi, 112(%rsp)
	movq	%rax, %rdi
	movq	%rsi, 32(%rsp)
	xorl	%esi, %esi
	movq	%rdx, %r13
	movq	%r10, %rdx
	movq	%r9, %r14
	movq	%r8, %r15
	movq	%r11, 40(%rsp)
	movq	%rcx, %rbp
	callq	*memset@GOTPCREL(%rip)
	movq	40(%rsp), %rsi
	movq	%r15, 168(%rsp)
	movq	%r14, 88(%rsp)
	cmpq	%r15, %r14
	jbe	.LBB135_50
	movq	8(%r13), %rdx
	movq	88(%rsp), %rcx
	movq	%rdx, 160(%rsp)
	movl	(%rdx,%rcx,4), %r8d
	movq	%r12, %rdi
	movq	8(%rbx), %r12
	movq	8(%rbp), %rdx
	movq	%rdx, 248(%rsp)
	movq	16(%rbp), %rax
	movq	%rax, 152(%rsp)
	movq	8(%rdi), %rax
	movq	%rax, 144(%rsp)
	leaq	1(%rcx), %rax
	movq	%rax, 200(%rsp)
	leaq	2(%rcx), %rax
	leal	509(%rcx), %edx
	movl	%edx, 84(%rsp)
	leaq	20(%r12), %rdx
	movq	%rdx, 96(%rsp)
	movl	$2, %edx
	subq	%rcx, %rdx
	movq	%rdx, 64(%rsp)
	leaq	-1(%rcx), %rdi
	movdqa	.LCPI135_0(%rip), %xmm0
	movdqa	.LCPI135_1(%rip), %xmm1
	movdqa	.LCPI135_2(%rip), %xmm2
	movdqa	.LCPI135_3(%rip), %xmm3
	movq	%rax, 240(%rsp)
	movq	%rax, 120(%rsp)
	movq	$0, 56(%rsp)
	movq	%rcx, %rax
	xorl	%r9d, %r9d
	xorl	%r14d, %r14d
	movq	%r12, 16(%rsp)
	jmp	.LBB135_6
	.p2align	4
.LBB135_5:
	incq	56(%rsp)
	incq	64(%rsp)
	decq	120(%rsp)
	decq	%rdi
	movq	%rbx, %rax
	cmpq	168(%rsp), %rbx
	jbe	.LBB135_50
.LBB135_6:
	leaq	-1(%rax), %rbx
	cmpq	104(%rsp), %rbx
	jae	.LBB135_53
	cmpq	%rsi, %rax
	jae	.LBB135_52
	movq	%r14, 48(%rsp)
	cmpq	32(%rsp), %rbx
	jae	.LBB135_51
	movq	%r9, 232(%rsp)
	movq	%rdi, 128(%rsp)
	movq	160(%rsp), %rcx
	movl	(%rcx,%rbx,4), %r9d
	movl	(%r12,%rax,4), %ecx
	movl	$1048576, %edx
	movq	%rcx, 216(%rsp)
	subl	%ecx, %edx
	movl	%edx, 12(%rsp)
	movq	112(%rsp), %rcx
	movzbl	-1(%rcx,%rax), %edx
	movq	320(%rsp), %rcx
	movq	%rdx, 184(%rsp)
	movl	(%rcx,%rdx,4), %edx
	shll	$9, %edx
	addl	$536870912, %edx
	incq	%rax
	movq	152(%rsp), %rcx
	cmpq	%rcx, %r8
	cmovaeq	%rcx, %r8
	movq	%r8, 256(%rsp)
	cmpq	%r9, %r8
	movq	%rbx, 24(%rsp)
	movq	%r9, 224(%rsp)
	jbe	.LBB135_26
	movq	88(%rsp), %rcx
	subq	56(%rsp), %rcx
	addl	$509, %ecx
	movq	%rcx, 208(%rsp)
	xorl	%r10d, %r10d
	xorl	%r14d, %r14d
	jmp	.LBB135_13
.LBB135_11:
	movq	16(%rsp), %rcx
	addl	(%rcx,%r15,4), %edi
	movq	328(%rsp), %rcx
	addl	12(%rcx,%r8,4), %edi
	addq	$3, %r8
	shll	$9, %edi
	orl	%r8d, %edi
	movl	%edi, %ecx
	.p2align	4
.LBB135_12:
	andl	$32767, %r13d
	cmpl	%edx, %ecx
	movq	72(%rsp), %r10
	cmovbl	%r13d, %r10d
	cmovbl	%ecx, %edx
	incq	%r13
	cmpq	%rax, %r15
	cmovaq	%r13, %r14
	cmovaq	%r15, %rax
	incq	%r9
	cmpq	256(%rsp), %r9
	movq	24(%rsp), %rbx
	je	.LBB135_27
.LBB135_13:
	movq	248(%rsp), %rcx
	movl	(%rcx,%r9,4), %r13d
	movl	%r13d, %r11d
	shrl	$15, %r11d
	movzbl	%r11b, %r8d
	leaq	(%rbx,%r8), %r15
	addq	$3, %r15
	movl	$-1, %ecx
	cmpq	%rsi, %r15
	movq	%r10, 72(%rsp)
	jae	.LBB135_12
	movl	%r13d, %edi
	shrl	$21, %edi
	andl	$124, %edi
	movq	336(%rsp), %r10
	movl	(%r10,%rdi), %edi
	addl	12(%rsp), %edi
	testl	%r13d, %r13d
	js	.LBB135_11
	cmpq	%r15, %rax
	jae	.LBB135_12
	leaq	1(%rax), %r12
	movl	%r12d, %r10d
	subl	24(%rsp), %r10d
	movzbl	%r11b, %r8d
	movq	240(%rsp), %rcx
	leaq	(%rcx,%r8), %rbp
	movq	56(%rsp), %rcx
	leaq	(%rcx,%rax), %rbx
	subq	%rbx, %rbp
	movl	$-1, %ecx
	cmpq	$8, %rbp
	jb	.LBB135_23
	movq	%rbp, 136(%rsp)
	movzbl	%r11b, %r11d
	addq	200(%rsp), %r11
	subq	%rbx, %r11
	movl	%r11d, %ebx
	andl	$511, %ebx
	movq	208(%rsp), %rsi
	movl	%esi, %ebp
	subl	%eax, %ebp
	andl	$511, %ebp
	cmpw	%bx, %bp
	jb	.LBB135_22
	cmpq	$511, %r11
	ja	.LBB135_22
	movq	136(%rsp), %rcx
	andq	$-8, %rcx
	addq	%rcx, %r12
	movd	%edi, %xmm4
	pshufd	$0, %xmm4, %xmm4
	movd	%r10d, %xmm5
	movq	%rcx, 192(%rsp)
	addl	%ecx, %r10d
	pshufd	$0, %xmm5, %xmm6
	paddd	%xmm0, %xmm6
	movq	96(%rsp), %rcx
	leaq	(%rcx,%rax,4), %rsi
	movq	64(%rsp), %rcx
	addq	%rax, %rcx
	addq	120(%rsp), %r8
	subq	%rax, %r8
	andq	$-8, %r8
	pcmpeqd	%xmm5, %xmm5
	xorl	%r11d, %r11d
	pcmpeqd	%xmm7, %xmm7
	movq	328(%rsp), %rbx
	.p2align	4
.LBB135_20:
	movdqa	%xmm6, %xmm9
	paddd	%xmm1, %xmm9
	leal	(%rcx,%r11), %ebp
	andl	$511, %ebp
	movdqu	-16(%rsi,%r11,4), %xmm10
	movdqu	(%rsi,%r11,4), %xmm8
	movdqu	(%rbx,%rbp,4), %xmm11
	movdqu	16(%rbx,%rbp,4), %xmm12
	paddd	%xmm4, %xmm10
	paddd	%xmm11, %xmm10
	paddd	%xmm4, %xmm8
	paddd	%xmm12, %xmm8
	pslld	$9, %xmm10
	pslld	$9, %xmm8
	por	%xmm9, %xmm8
	por	%xmm6, %xmm10
	movdqa	%xmm10, %xmm9
	pxor	%xmm2, %xmm9
	movdqa	%xmm5, %xmm11
	pxor	%xmm2, %xmm11
	pcmpgtd	%xmm9, %xmm11
	pand	%xmm11, %xmm10
	pandn	%xmm5, %xmm11
	movdqa	%xmm11, %xmm5
	por	%xmm10, %xmm5
	movdqa	%xmm8, %xmm9
	pxor	%xmm2, %xmm9
	movdqa	%xmm7, %xmm10
	pxor	%xmm2, %xmm10
	pcmpgtd	%xmm9, %xmm10
	pand	%xmm10, %xmm8
	pandn	%xmm7, %xmm10
	movdqa	%xmm10, %xmm7
	por	%xmm8, %xmm7
	addq	$8, %r11
	paddd	%xmm3, %xmm6
	cmpq	%r11, %r8
	jne	.LBB135_20
	movdqa	%xmm5, %xmm4
	pxor	%xmm2, %xmm4
	movdqa	%xmm7, %xmm6
	pxor	%xmm2, %xmm6
	pcmpgtd	%xmm4, %xmm6
	pand	%xmm6, %xmm5
	pandn	%xmm7, %xmm6
	por	%xmm5, %xmm6
	movdqa	%xmm6, %xmm4
	pxor	%xmm2, %xmm4
	pshufd	$238, %xmm6, %xmm5
	movdqa	%xmm5, %xmm7
	pxor	%xmm2, %xmm7
	pcmpgtd	%xmm4, %xmm7
	pand	%xmm7, %xmm6
	pandn	%xmm5, %xmm7
	por	%xmm6, %xmm7
	movd	%xmm7, %esi
	pshufd	$85, %xmm7, %xmm4
	movd	%xmm4, %ecx
	cmpl	%ecx, %esi
	cmovbl	%esi, %ecx
	movq	192(%rsp), %rsi
	cmpq	%rsi, 136(%rsp)
	movq	40(%rsp), %rsi
	movq	%rbx, %r8
	movq	16(%rsp), %rbp
	je	.LBB135_12
	jmp	.LBB135_24
.LBB135_22:
	movq	40(%rsp), %rsi
.LBB135_23:
	movq	328(%rsp), %r8
	movq	16(%rsp), %rbp
.LBB135_24:
	decq	%r12
	.p2align	4
.LBB135_25:
	movl	%ecx, %ebx
	movl	%r10d, %r11d
	andl	$511, %r11d
	movl	4(%rbp,%r12,4), %ecx
	addl	%edi, %ecx
	addl	(%r8,%r11,4), %ecx
	shll	$9, %ecx
	orl	%r10d, %ecx
	cmpl	%ebx, %ecx
	cmovael	%ebx, %ecx
	incl	%r10d
	incq	%r12
	cmpq	%r15, %r12
	jb	.LBB135_25
	jmp	.LBB135_12
	.p2align	4
.LBB135_26:
	xorl	%r14d, %r14d
	xorl	%r10d, %r10d
.LBB135_27:
	movq	232(%rsp), %rdi
	leaq	1(%rdi), %r9
	cmpq	$258, %r9
	movl	$258, %ecx
	cmovaeq	%rcx, %r9
	cmpq	$3, %rdi
	movq	16(%rsp), %r12
	movq	48(%rsp), %r13
	jb	.LBB135_37
	leaq	-1(%r13), %rcx
	cmpq	%rbx, %rcx
	jae	.LBB135_37
	leaq	(%rbx,%r9), %r15
	cmpq	%rax, %r15
	jbe	.LBB135_37
	movq	%rbx, %rcx
	subq	%r13, %rcx
	cmpq	32(%rsp), %rcx
	jae	.LBB135_54
	movq	112(%rsp), %rdi
	movq	184(%rsp), %r8
	cmpb	(%rdi,%rcx), %r8b
	jne	.LBB135_37
	movq	%r10, 72(%rsp)
	leal	-1(%r13), %ecx
	movl	%ecx, %r10d
	cmpl	$4, %ecx
	jb	.LBB135_34
	bsrl	%ecx, %r8d
	xorl	$31, %r8d
	movb	$30, %dil
	subb	%r8b, %dil
	movzbl	%dil, %edi
	xorl	%r10d, %r10d
	btl	%edi, %ecx
	setb	%r10b
	andl	$15, %r8d
	leal	(%r10,%r8,2), %r10d
	xorl	$30, %r10d
.LBB135_34:
	movl	$-1, %edi
	cmpq	%rsi, %r15
	movl	12(%rsp), %r11d
	jae	.LBB135_49
	movl	%r10d, %edi
	movq	%rbx, %r8
	leaq	1(%rax), %rbx
	movl	%ebx, %ebp
	subl	%r8d, %ebp
	movq	336(%rsp), %r8
	addl	(%r8,%rdi,4), %r11d
	movl	%r11d, 12(%rsp)
	cmpq	%rbx, %r15
	movq	%rbx, %r14
	cmovaq	%r15, %r14
	subq	%rax, %r14
	movl	$-1, %edi
	cmpq	$8, %r14
	jae	.LBB135_40
	movq	%rbx, %r10
	movq	328(%rsp), %r8
	movq	24(%rsp), %rbx
	jmp	.LBB135_46
	.p2align	4
.LBB135_37:
	subq	%rbx, %rax
	movq	%rax, %r9
.LBB135_38:
	movl	%edx, %eax
	shrl	$9, %eax
	movq	216(%rsp), %rcx
	addl	%ecx, %eax
	addl	$-1048576, %eax
	movl	%eax, (%r12,%rbx,4)
	cmpq	176(%rsp), %rbx
	movq	128(%rsp), %rdi
	movq	224(%rsp), %r8
	jae	.LBB135_5
	andl	$511, %edx
	shll	$9, %r10d
	cmpl	$3, %edx
	leal	512(%r10,%rdx), %eax
	movl	$0, %ecx
	cmovbl	%ecx, %eax
	movq	144(%rsp), %rcx
	movl	%eax, (%rcx,%rbx,4)
	jmp	.LBB135_5
.LBB135_40:
	cmpq	%rbx, %r15
	movq	%rbx, %r11
	cmovaq	%r15, %r11
	movq	%rax, %r10
	notq	%r10
	addq	%r11, %r10
	movl	%r10d, %r11d
	andl	$511, %r11d
	movq	56(%rsp), %r8
	movl	84(%rsp), %r13d
	subl	%r8d, %r13d
	subl	%eax, %r13d
	andl	$511, %r13d
	cmpw	%r11w, %r13w
	movq	328(%rsp), %r8
	jb	.LBB135_45
	cmpq	$511, %r10
	ja	.LBB135_45
	movq	%r14, %r12
	andq	$-8, %r12
	leaq	(%rbx,%r12), %r10
	movd	12(%rsp), %xmm4
	pshufd	$0, %xmm4, %xmm4
	movd	%ebp, %xmm5
	addl	%r12d, %ebp
	pshufd	$0, %xmm5, %xmm5
	paddd	%xmm0, %xmm5
	movq	96(%rsp), %rdi
	leaq	(%rdi,%rax,4), %rdi
	movq	64(%rsp), %r11
	leaq	(%rax,%r11), %r13
	movq	128(%rsp), %r11
	addq	%r9, %r11
	cmpq	%rbx, %r11
	cmovaq	%r11, %rbx
	subq	%rax, %rbx
	andq	$-8, %rbx
	pcmpeqd	%xmm6, %xmm6
	xorl	%eax, %eax
	pcmpeqd	%xmm7, %xmm7
	.p2align	4
.LBB135_43:
	movdqa	%xmm5, %xmm9
	paddd	%xmm1, %xmm9
	leal	(%rax,%r13), %r11d
	andl	$511, %r11d
	movdqu	-16(%rdi,%rax,4), %xmm10
	movdqu	(%rdi,%rax,4), %xmm8
	movdqu	(%r8,%r11,4), %xmm11
	movdqu	16(%r8,%r11,4), %xmm12
	paddd	%xmm4, %xmm10
	paddd	%xmm11, %xmm10
	paddd	%xmm4, %xmm8
	paddd	%xmm12, %xmm8
	pslld	$9, %xmm10
	pslld	$9, %xmm8
	por	%xmm9, %xmm8
	por	%xmm5, %xmm10
	movdqa	%xmm10, %xmm9
	pxor	%xmm2, %xmm9
	movdqa	%xmm6, %xmm11
	pxor	%xmm2, %xmm11
	pcmpgtd	%xmm9, %xmm11
	pand	%xmm11, %xmm10
	pandn	%xmm6, %xmm11
	movdqa	%xmm11, %xmm6
	por	%xmm10, %xmm6
	movdqa	%xmm8, %xmm9
	pxor	%xmm2, %xmm9
	movdqa	%xmm7, %xmm10
	pxor	%xmm2, %xmm10
	pcmpgtd	%xmm9, %xmm10
	pand	%xmm10, %xmm8
	pandn	%xmm7, %xmm10
	movdqa	%xmm10, %xmm7
	por	%xmm8, %xmm7
	addq	$8, %rax
	paddd	%xmm3, %xmm5
	cmpq	%rax, %rbx
	jne	.LBB135_43
	movdqa	%xmm6, %xmm4
	pxor	%xmm2, %xmm4
	movdqa	%xmm7, %xmm5
	pxor	%xmm2, %xmm5
	pcmpgtd	%xmm4, %xmm5
	pand	%xmm5, %xmm6
	pandn	%xmm7, %xmm5
	por	%xmm6, %xmm5
	movdqa	%xmm5, %xmm4
	pxor	%xmm2, %xmm4
	pshufd	$238, %xmm5, %xmm6
	movdqa	%xmm6, %xmm7
	pxor	%xmm2, %xmm7
	pcmpgtd	%xmm4, %xmm7
	pand	%xmm7, %xmm5
	pandn	%xmm6, %xmm7
	por	%xmm5, %xmm7
	movd	%xmm7, %eax
	pshufd	$85, %xmm7, %xmm4
	movd	%xmm4, %edi
	cmpl	%edi, %eax
	cmovbl	%eax, %edi
	cmpq	%r12, %r14
	movq	16(%rsp), %r12
	movq	24(%rsp), %rbx
	movq	48(%rsp), %r13
	movl	12(%rsp), %r14d
	jne	.LBB135_47
	jmp	.LBB135_49
.LBB135_45:
	movq	%rbx, %r10
	movq	16(%rsp), %r12
	movq	24(%rsp), %rbx
	movq	48(%rsp), %r13
.LBB135_46:
	movl	12(%rsp), %r14d
.LBB135_47:
	decq	%r10
	.p2align	4
.LBB135_48:
	movl	%edi, %eax
	movl	%ebp, %r11d
	andl	$511, %r11d
	movl	4(%r12,%r10,4), %edi
	addl	%r14d, %edi
	addl	(%r8,%r11,4), %edi
	shll	$9, %edi
	orl	%ebp, %edi
	cmpl	%eax, %edi
	cmovael	%eax, %edi
	incl	%ebp
	incq	%r10
	cmpq	%r15, %r10
	jb	.LBB135_48
.LBB135_49:
	cmpl	%edx, %edi
	movq	72(%rsp), %r10
	cmovbl	%ecx, %r10d
	cmovbl	%edi, %edx
	movq	%r13, %r14
	jmp	.LBB135_38
.LBB135_50:
	addq	$264, %rsp
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
.LBB135_51:
	.cfi_def_cfa_offset 320
	leaq	.Lalloc_ca46e1b1bfeb2b3ad3d0527f2a76cb9d(%rip), %rdx
	movq	%rbx, %rdi
	movq	32(%rsp), %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB135_52:
	leaq	.Lalloc_19c67fa86284eca1bd1317a90cd36415(%rip), %rdx
	movq	%rax, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB135_53:
	leaq	.Lalloc_dc0f0c2638b46b144204a9d85f95981f(%rip), %rdx
	movq	%rbx, %rdi
	movq	104(%rsp), %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB135_54:
	leaq	.Lalloc_fc650c7e3ae0d766b2a9643cadc69347(%rip), %rdx
	movq	%rcx, %rdi
	movq	32(%rsp), %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.Lfunc_end135:
	.size	_RNvCsera0HrlzTQN_14r26_a_original9a_dp_pass, .Lfunc_end135-_RNvCsera0HrlzTQN_14r26_a_original9a_dp_pass
	.cfi_endproc

