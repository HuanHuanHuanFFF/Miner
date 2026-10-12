	.section	.text._RNvNtCs2hd9JHJjR4I_9candidate5parse9a_dp_pass,"ax",@progbits
	.prefalign	4, .Lfunc_end56, nop
	.type	_RNvNtCs2hd9JHJjR4I_9candidate5parse9a_dp_pass,@function
_RNvNtCs2hd9JHJjR4I_9candidate5parse9a_dp_pass:
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
	subq	$216, %rsp
	.cfi_def_cfa_offset 272
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	320(%rsp), %rbx
	cmpq	%rbx, 280(%rsp)
	jae	.LBB56_16
	movq	280(%rsp), %r11
	cmpq	%rcx, %r11
	setae	%al
	cmpq	%rsi, %r11
	seta	%r10b
	cmpq	336(%rsp), %r11
	seta	%r11b
	orb	%r10b, %r11b
	orb	%al, %r11b
	jne	.LBB56_16
	movq	312(%rsp), %r15
	movq	280(%rsp), %r14
	leaq	(%r15,%r14,4), %rax
	movq	%r14, %r10
	notq	%r10
	addq	%rbx, %r10
	cmpq	$258, %r10
	movl	$258, %r11d
	cmovbq	%r10, %r11
	movl	%r11d, %r10d
	leaq	4(,%r10,4), %r10
	movq	%rdi, 88(%rsp)
	movq	%rax, %rdi
	movq	%rsi, 24(%rsp)
	xorl	%esi, %esi
	movq	%rdx, 80(%rsp)
	movq	%r10, %rdx
	movq	%rcx, 72(%rsp)
	movq	%r9, 128(%rsp)
	movq	%r8, 200(%rsp)
	callq	*memset@GOTPCREL(%rip)
	movq	320(%rsp), %rsi
	cmpq	272(%rsp), %r14
	jbe	.LBB56_16
	movq	%r15, %r9
	movq	280(%rsp), %rbx
	movq	80(%rsp), %rcx
	movl	(%rcx,%rbx,4), %r10d
	leaq	1(%rbx), %rcx
	movq	%rcx, 152(%rsp)
	leaq	2(%rbx), %rcx
	leal	509(%rbx), %edx
	movl	%edx, 60(%rsp)
	leaq	20(%r15), %rdx
	movq	%rdx, 64(%rsp)
	movl	$2, %edx
	subq	%rbx, %rdx
	movq	%rdx, 40(%rsp)
	movdqa	.LCPI56_0(%rip), %xmm0
	movdqa	.LCPI56_1(%rip), %xmm1
	movdqa	.LCPI56_2(%rip), %xmm2
	movdqa	.LCPI56_3(%rip), %xmm3
	movq	%rcx, 192(%rsp)
	movq	%rcx, 96(%rsp)
	movq	$0, 32(%rsp)
	xorl	%r15d, %r15d
	xorl	%r13d, %r13d
	jmp	.LBB56_4
	.p2align	4
.LBB56_15:
	incq	32(%rsp)
	incq	40(%rsp)
	decq	96(%rsp)
	movq	%rdi, %rbx
	movq	%rdx, %r10
	cmpq	272(%rsp), %rdi
	jbe	.LBB56_16
.LBB56_4:
	leaq	-1(%rbx), %rdi
	cmpq	72(%rsp), %rdi
	jae	.LBB56_54
	cmpq	%rsi, %rbx
	jae	.LBB56_55
	movq	%r13, 184(%rsp)
	cmpq	24(%rsp), %rdi
	jae	.LBB56_17
	movq	%r15, 176(%rsp)
	movq	80(%rsp), %rax
	movl	(%rax,%rdi,4), %r8d
	movl	(%r9,%rbx,4), %edx
	movl	$1048576, %eax
	subl	%edx, %eax
	movl	%eax, 12(%rsp)
	movq	88(%rsp), %rax
	movzbl	-1(%rax,%rbx), %r9d
	leaq	1(%rbx), %rax
	movq	288(%rsp), %rcx
	movl	(%rcx,%r9,4), %r11d
	shll	$9, %r11d
	addl	$536870912, %r11d
	movq	128(%rsp), %rcx
	cmpq	%rcx, %r10
	cmovaeq	%rcx, %r10
	movq	%r10, 208(%rsp)
	cmpq	%r8, %r10
	movq	%rdi, 120(%rsp)
	movq	%r8, 104(%rsp)
	movq	%rdx, 168(%rsp)
	movq	%r9, 136(%rsp)
	jbe	.LBB56_8
	movq	280(%rsp), %rcx
	subq	32(%rsp), %rcx
	addl	$509, %ecx
	movq	%rcx, 160(%rsp)
	xorl	%r10d, %r10d
	xorl	%r14d, %r14d
	movq	%rbx, 16(%rsp)
	jmp	.LBB56_39
.LBB56_53:
	movq	312(%rsp), %rdx
	addl	(%rdx,%r15,4), %ebp
	movq	296(%rsp), %rdx
	addl	12(%rdx,%rcx,4), %ebp
	addq	$3, %rcx
	shll	$9, %ebp
	orl	%ecx, %ebp
	movl	%ebp, %r9d
	.p2align	4
.LBB56_40:
	andl	$32767, %ebx
	cmpl	%r11d, %r9d
	movq	48(%rsp), %r10
	cmovbl	%ebx, %r10d
	cmovbl	%r9d, %r11d
	incq	%rbx
	cmpq	%rax, %r15
	cmovaq	%rbx, %r14
	cmovaq	%r15, %rax
	incq	%r8
	cmpq	208(%rsp), %r8
	movq	16(%rsp), %rbx
	leaq	-1(%rbx), %rdi
	je	.LBB56_9
.LBB56_39:
	movq	%r10, 48(%rsp)
	movq	200(%rsp), %rcx
	movl	(%rcx,%r8,4), %ebx
	movl	%ebx, %r13d
	shrl	$15, %r13d
	movzbl	%r13b, %ecx
	leaq	(%rdi,%rcx), %r15
	addq	$3, %r15
	movl	$-1, %r9d
	cmpq	%rsi, %r15
	jae	.LBB56_40
	movl	%ebx, %edx
	shrl	$21, %edx
	andl	$124, %edx
	movq	304(%rsp), %r10
	movl	(%r10,%rdx), %ebp
	addl	12(%rsp), %ebp
	testl	%ebx, %ebx
	js	.LBB56_53
	cmpq	%r15, %rax
	jae	.LBB56_40
	leaq	1(%rax), %rdx
	movl	%edx, %ecx
	movq	16(%rsp), %rdi
	decq	%rdi
	subl	%edi, %ecx
	movzbl	%r13b, %r12d
	movq	192(%rsp), %r9
	leaq	(%r9,%r12), %rdi
	movq	32(%rsp), %r9
	leaq	(%r9,%rax), %r10
	subq	%r10, %rdi
	movl	$-1, %r9d
	cmpq	$8, %rdi
	jae	.LBB56_45
	movq	296(%rsp), %r12
	movq	312(%rsp), %r13
	jmp	.LBB56_51
.LBB56_45:
	movq	%rdi, 112(%rsp)
	movzbl	%r13b, %edi
	addq	152(%rsp), %rdi
	subq	%r10, %rdi
	movl	%edi, %r10d
	andl	$511, %r10d
	movq	160(%rsp), %rsi
	movl	%esi, %r13d
	subl	%eax, %r13d
	andl	$511, %r13d
	cmpw	%r10w, %r13w
	jb	.LBB56_46
	cmpq	$511, %rdi
	ja	.LBB56_46
	movq	112(%rsp), %rsi
	andq	$-8, %rsi
	addq	%rsi, %rdx
	movd	%ebp, %xmm4
	pshufd	$0, %xmm4, %xmm4
	movd	%ecx, %xmm5
	movq	%rsi, 144(%rsp)
	addl	%esi, %ecx
	pshufd	$0, %xmm5, %xmm6
	paddd	%xmm0, %xmm6
	movq	64(%rsp), %rsi
	leaq	(%rsi,%rax,4), %r9
	movq	40(%rsp), %rsi
	leaq	(%rsi,%rax), %rdi
	addq	96(%rsp), %r12
	subq	%rax, %r12
	andq	$-8, %r12
	pcmpeqd	%xmm5, %xmm5
	xorl	%r10d, %r10d
	pcmpeqd	%xmm7, %xmm7
	movq	296(%rsp), %rsi
	.p2align	4
.LBB56_49:
	movdqa	%xmm6, %xmm9
	paddd	%xmm1, %xmm9
	leal	(%rdi,%r10), %r13d
	andl	$511, %r13d
	movdqu	-16(%r9,%r10,4), %xmm10
	movdqu	(%r9,%r10,4), %xmm8
	movdqu	(%rsi,%r13,4), %xmm11
	movdqu	16(%rsi,%r13,4), %xmm12
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
	addq	$8, %r10
	paddd	%xmm3, %xmm6
	cmpq	%r10, %r12
	jne	.LBB56_49
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
	movd	%xmm7, %edi
	pshufd	$85, %xmm7, %xmm4
	movd	%xmm4, %r9d
	cmpl	%r9d, %edi
	cmovbl	%edi, %r9d
	movq	144(%rsp), %rdi
	cmpq	%rdi, 112(%rsp)
	movq	%rsi, %r12
	movq	320(%rsp), %rsi
	movq	312(%rsp), %r13
	je	.LBB56_40
	jmp	.LBB56_51
.LBB56_46:
	movq	320(%rsp), %rsi
	movq	312(%rsp), %r13
	movq	296(%rsp), %r12
.LBB56_51:
	decq	%rdx
	.p2align	4
.LBB56_52:
	movl	%r9d, %edi
	movl	%ecx, %r10d
	andl	$511, %r10d
	movl	4(%r13,%rdx,4), %r9d
	addl	%ebp, %r9d
	addl	(%r12,%r10,4), %r9d
	shll	$9, %r9d
	orl	%ecx, %r9d
	cmpl	%edi, %r9d
	cmovael	%edi, %r9d
	incl	%ecx
	incq	%rdx
	cmpq	%r15, %rdx
	jb	.LBB56_52
	jmp	.LBB56_40
	.p2align	4
.LBB56_8:
	xorl	%r14d, %r14d
	xorl	%r10d, %r10d
.LBB56_9:
	movq	176(%rsp), %rcx
	cmpq	$257, %rcx
	movl	$257, %r15d
	cmovbq	%rcx, %r15
	cmpq	$3, %rcx
	movq	184(%rsp), %r13
	jb	.LBB56_11
	leaq	-1(%r13), %rcx
	cmpq	%rdi, %rcx
	jae	.LBB56_11
	addq	%r15, %rbx
	cmpq	%rax, %rbx
	jbe	.LBB56_11
	movq	%rdi, %r8
	subq	%r13, %r8
	cmpq	24(%rsp), %r8
	jae	.LBB56_25
	movq	88(%rsp), %rcx
	movq	136(%rsp), %rdx
	cmpb	(%rcx,%r8), %dl
	jne	.LBB56_11
	movq	%r10, 48(%rsp)
	leal	-1(%r13), %r8d
	movl	%r8d, %ecx
	cmpl	$4, %r8d
	jb	.LBB56_23
	bsrl	%r8d, %ecx
	xorl	$31, %ecx
	movb	$30, %dl
	subb	%cl, %dl
	movzbl	%dl, %edx
	xorl	%r9d, %r9d
	btl	%edx, %r8d
	setb	%r9b
	andl	$15, %ecx
	leal	(%r9,%rcx,2), %ecx
	xorl	$30, %ecx
.LBB56_23:
	movl	$-1, %r12d
	cmpq	%rsi, %rbx
	movl	12(%rsp), %r14d
	movq	312(%rsp), %rsi
	jae	.LBB56_24
	movl	%ecx, %ecx
	leaq	1(%rax), %r10
	movl	%r10d, %r9d
	subl	%edi, %r9d
	movq	304(%rsp), %rdx
	addl	(%rdx,%rcx,4), %r14d
	cmpq	%r10, %rbx
	movq	%r10, %rdx
	cmovaq	%rbx, %rdx
	subq	%rax, %rdx
	cmpq	$8, %rdx
	jae	.LBB56_29
	movq	%r10, %rcx
	movq	296(%rsp), %rbp
.LBB56_36:
	decq	%rcx
	.p2align	4
.LBB56_37:
	movl	%r12d, %edx
	movl	%r9d, %r10d
	andl	$511, %r10d
	movl	4(%rsi,%rcx,4), %r12d
	addl	%r14d, %r12d
	addl	(%rbp,%r10,4), %r12d
	shll	$9, %r12d
	orl	%r9d, %r12d
	cmpl	%edx, %r12d
	cmovael	%edx, %r12d
	incl	%r9d
	incq	%rcx
	cmpq	%rbx, %rcx
	jb	.LBB56_37
.LBB56_24:
	incq	%r15
	cmpl	%r11d, %r12d
	movq	48(%rsp), %r10
	cmovbl	%r8d, %r10d
	cmovbl	%r12d, %r11d
	movq	104(%rsp), %rdx
	movq	%rsi, %r9
	movq	320(%rsp), %rsi
	jmp	.LBB56_13
	.p2align	4
.LBB56_11:
	subq	%rdi, %rax
	jb	.LBB56_26
	movq	%r14, %r13
	movq	%rax, %r15
	movq	104(%rsp), %rdx
	movq	312(%rsp), %r9
.LBB56_13:
	movl	%r11d, %ecx
	shrl	$9, %ecx
	movq	168(%rsp), %rax
	addl	%eax, %ecx
	addl	$-1048576, %ecx
	movl	%ecx, (%r9,%rdi,4)
	cmpq	336(%rsp), %rdi
	jae	.LBB56_15
	andl	$511, %r11d
	shll	$9, %r10d
	cmpl	$3, %r11d
	leal	512(%r10,%r11), %eax
	movl	$0, %ecx
	cmovbl	%ecx, %eax
	movq	328(%rsp), %rcx
	movl	%eax, (%rcx,%rdi,4)
	jmp	.LBB56_15
.LBB56_29:
	movl	%r14d, 12(%rsp)
	cmpq	%r10, %rbx
	movq	%rbx, %rcx
	movq	%r10, %rbx
	movq	%rcx, 16(%rsp)
	cmovaq	%rcx, %rbx
	movq	%rax, %rcx
	notq	%rcx
	addq	%rbx, %rcx
	movl	%ecx, %ebx
	andl	$511, %ebx
	movq	32(%rsp), %r14
	leal	(%r14,%rax), %ebp
	movl	60(%rsp), %r14d
	subl	%ebp, %r14d
	andl	$511, %r14d
	cmpw	%bx, %r14w
	jb	.LBB56_30
	cmpq	$511, %rcx
	movl	12(%rsp), %r14d
	ja	.LBB56_32
	movq	%rdx, %rbx
	andq	$-8, %rbx
	leaq	(%r10,%rbx), %rcx
	movd	%r14d, %xmm4
	pshufd	$0, %xmm4, %xmm4
	movd	%r9d, %xmm5
	addl	%ebx, %r9d
	pshufd	$0, %xmm5, %xmm5
	paddd	%xmm0, %xmm5
	movq	64(%rsp), %rdi
	leaq	(%rdi,%rax,4), %rdi
	movq	40(%rsp), %r14
	addq	%rax, %r14
	movq	16(%rsp), %r12
	cmpq	%r10, %r12
	cmovaq	%r12, %r10
	subq	%rax, %r10
	andq	$-8, %r10
	pcmpeqd	%xmm6, %xmm6
	xorl	%eax, %eax
	pcmpeqd	%xmm7, %xmm7
	movq	296(%rsp), %rbp
	.p2align	4
.LBB56_34:
	movdqa	%xmm5, %xmm9
	paddd	%xmm1, %xmm9
	leal	(%r14,%rax), %r12d
	andl	$511, %r12d
	movdqu	-16(%rdi,%rax,4), %xmm10
	movdqu	(%rdi,%rax,4), %xmm8
	movdqu	(%rbp,%r12,4), %xmm11
	movdqu	16(%rbp,%r12,4), %xmm12
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
	cmpq	%rax, %r10
	jne	.LBB56_34
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
	movd	%xmm4, %r12d
	cmpl	%r12d, %eax
	cmovbl	%eax, %r12d
	cmpq	%rbx, %rdx
	movq	120(%rsp), %rdi
	movq	16(%rsp), %rbx
	movl	12(%rsp), %r14d
	movq	312(%rsp), %rsi
	jne	.LBB56_36
	jmp	.LBB56_24
.LBB56_32:
	movq	%r10, %rcx
	movq	296(%rsp), %rbp
	movq	16(%rsp), %rbx
	jmp	.LBB56_36
.LBB56_30:
	movq	%r10, %rcx
	movq	296(%rsp), %rbp
	movq	16(%rsp), %rbx
	movl	12(%rsp), %r14d
	jmp	.LBB56_36
.LBB56_16:
	addq	$216, %rsp
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
.LBB56_17:
	.cfi_def_cfa_offset 272
	leaq	.Lalloc_667468cd33cd001ba36f461d0afddb9d(%rip), %rdx
	movq	24(%rsp), %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB56_55:
	leaq	.Lalloc_435c27114c72307c82cb1103ffa5b8de(%rip), %rdx
	movq	%rbx, %rdi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB56_54:
	leaq	.Lalloc_adca51cd0f56de19797d3a5f631d3ddd(%rip), %rdx
	movq	72(%rsp), %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.LBB56_26:
	leaq	.Lalloc_c7584029baf529d89ee19b9f222ce7d9(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow@GOTPCREL(%rip)
.LBB56_25:
	leaq	.Lalloc_17c6631b50621382366421f98c86995c(%rip), %rdx
	movq	%r8, %rdi
	movq	24(%rsp), %rsi
	callq	*_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check@GOTPCREL(%rip)
.Lfunc_end56:
	.size	_RNvNtCs2hd9JHJjR4I_9candidate5parse9a_dp_pass, .Lfunc_end56-_RNvNtCs2hd9JHJjR4I_9candidate5parse9a_dp_pass
	.cfi_endproc

