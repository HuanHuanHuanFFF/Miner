	.file	"native_cost_probe.c"
	.text
	.p2align 4
	.type	ordered, @function
ordered:
.LFB40:
	.cfi_startproc
	endbr64
	leaq	4000(%rdi), %rax
	pxor	%xmm1, %xmm1
	.p2align 4,,10
	.p2align 3
.L2:
	movdqu	(%rdi), %xmm0
	addq	$16, %rdi
	addss	%xmm0, %xmm1
	movaps	%xmm0, %xmm2
	shufps	$85, %xmm0, %xmm2
	addss	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	unpckhps	%xmm0, %xmm1
	shufps	$255, %xmm0, %xmm0
	addss	%xmm2, %xmm1
	addss	%xmm0, %xmm1
	cmpq	%rdi, %rax
	jne	.L2
	movd	%xmm1, %eax
	ret
	.cfi_endproc
.LFE40:
	.size	ordered, .-ordered
	.p2align 4
	.type	ordered_skip_zero, @function
ordered_skip_zero:
.LFB41:
	.cfi_startproc
	endbr64
	leaq	4000(%rdi), %rax
	pxor	%xmm0, %xmm0
	.p2align 4,,10
	.p2align 3
.L7:
	movl	(%rdi), %edx
	testl	$2147483647, %edx
	je	.L6
	movd	%edx, %xmm1
	addss	%xmm1, %xmm0
.L6:
	addq	$4, %rdi
	cmpq	%rdi, %rax
	jne	.L7
	movd	%xmm0, %eax
	ret
	.cfi_endproc
.LFE41:
	.size	ordered_skip_zero, .-ordered_skip_zero
	.p2align 4
	.type	guarded_branchless, @function
guarded_branchless:
.LFB44:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xorl	%r11d, %r11d
	pxor	%xmm0, %xmm0
	pxor	%xmm2, %xmm2
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	%r11d, %r8d
	xorl	%r15d, %r15d
	movq	%rdi, %r11
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rdx
	movq	%rdx, 56(%rsp)
	xorl	%edx, %edx
.L24:
	movd	%xmm0, %r13d
	movl	$1000, %r9d
	movl	$32, %edx
	movl	%r8d, %edi
	movl	%r13d, %eax
	subl	%r8d, %r9d
	andl	$2147483647, %eax
	movl	%eax, %r14d
	shrl	$23, %r14d
	cmpl	%edx, %r9d
	cmova	%edx, %r9d
	leal	-1(%r14), %edx
	cmpl	$252, %edx
	jbe	.L57
.L13:
	leaq	(%r11,%rdi,4), %rax
	movl	%r9d, %edx
	movdqu	(%rax), %xmm3
	shrl	$2, %edx
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm1, %xmm0
	movaps	%xmm3, %xmm1
	unpckhps	%xmm3, %xmm1
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	movdqu	16(%rax), %xmm1
	addss	%xmm3, %xmm0
	movaps	%xmm1, %xmm3
	shufps	$85, %xmm1, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm3
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm3, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$2, %edx
	je	.L23
	movdqu	32(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm3, %xmm0
	unpckhps	%xmm3, %xmm0
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	movdqu	48(%rax), %xmm1
	addss	%xmm3, %xmm0
	movaps	%xmm1, %xmm3
	shufps	$85, %xmm1, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm3
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm3, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$4, %edx
	je	.L23
	movdqu	64(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm3, %xmm0
	unpckhps	%xmm3, %xmm0
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	movdqu	80(%rax), %xmm1
	addss	%xmm3, %xmm0
	movaps	%xmm1, %xmm3
	shufps	$85, %xmm1, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm3
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm3, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$6, %edx
	je	.L23
	movdqu	96(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm3, %xmm0
	unpckhps	%xmm3, %xmm0
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm3, %xmm0
	cmpl	$8, %edx
	jne	.L23
	movdqu	112(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm3, %xmm0
	unpckhps	%xmm3, %xmm0
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm3, %xmm0
.L23:
	addl	%r9d, %r8d
	movd	%xmm0, %ebx
.L22:
	cmpl	$999, %r8d
	jbe	.L24
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L58
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L57:
	.cfi_restore_state
	movl	%r13d, %ebx
	leaq	(%r11,%rdi,4), %r10
	leal	-2(%r14), %edx
	xorl	%ecx, %ecx
	movl	%edx, 4(%rsp)
	andl	$-2147483648, %ebx
	movq	%r10, %rsi
	jmp	.L15
	.p2align 4,,10
	.p2align 3
.L59:
	cmpl	$3, %ecx
	ja	.L26
.L15:
	movl	(%rsi), %edx
	movl	%edx, %ebp
	andl	$2147483647, %ebp
	je	.L14
	movl	%edx, %r12d
	andl	$-2147483648, %r12d
	cmpl	%r12d, %ebx
	jne	.L13
	shrl	$23, %ebp
	je	.L13
	cmpl	$255, %ebp
	je	.L13
	andl	$1, %edx
	je	.L13
	movl	4(%rsp), %edx
	subl	%ebp, %edx
	cmpl	$22, %edx
	ja	.L13
.L14:
	addl	$1, %ecx
	addq	$4, %rsi
	cmpl	%r9d, %ecx
	jb	.L59
.L26:
	movl	%r8d, 4(%rsp)
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %r12d
	movl	%r13d, 8(%rsp)
	movl	%eax, 12(%rsp)
	movq	%r11, 16(%rsp)
	movq	%rdi, 24(%rsp)
	movaps	%xmm2, 32(%rsp)
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L60:
	movl	%esi, %eax
	andl	$3, %eax
	movl	32(%rsp,%rax,4), %edx
.L20:
	movl	(%r10), %eax
	movl	%r14d, %edi
	movl	%eax, %ebp
	movl	%eax, %r8d
	andl	$2147483647, %ebp
	movl	%ebp, %ecx
	setne	%r11b
	andl	$-2147483648, %r8d
	shrl	$23, %ecx
	subl	%ecx, %edi
	cmpl	%ebx, %r8d
	leal	-2(%rdi), %r13d
	sete	%r8b
	cmpl	$22, %r13d
	setbe	%r13b
	andl	%r13d, %r8d
	testl	%ecx, %ecx
	setne	%r13b
	cmpl	$255, %ecx
	setne	%cl
	movzbl	%cl, %ecx
	andl	%r13d, %ecx
	andl	%eax, %ecx
	andl	%r8d, %ecx
	testl	%ebp, %ebp
	movl	$1, %ebp
	sete	%r8b
	andl	$8388607, %eax
	orl	%ecx, %r8d
	leal	-1(%rdi), %ecx
	orl	$8388608, %eax
	andl	%r8d, %r12d
	movl	%esi, %r8d
	sall	%cl, %ebp
	movl	%edi, %ecx
	andl	$3, %r8d
	testb	%r11b, %r11b
	cmove	%r15d, %eax
	addl	%ebp, %eax
	shrl	%cl, %eax
	testb	%r11b, %r11b
	cmove	%r15d, %eax
	addl	$1, %esi
	addq	$4, %r10
	addl	%edx, %eax
	movl	%eax, 32(%rsp,%r8,4)
	cmpl	%esi, %r9d
	jne	.L60
	movl	36(%rsp), %edx
	movl	4(%rsp), %r8d
	addl	32(%rsp), %edx
	movl	8(%rsp), %r13d
	addl	40(%rsp), %edx
	movl	12(%rsp), %eax
	movq	16(%rsp), %r11
	movq	24(%rsp), %rdi
	addl	44(%rsp), %edx
	testl	%r12d, %r12d
	je	.L13
	andl	$8388607, %r13d
	movl	$8388608, %ecx
	subl	%r13d, %ecx
	cmpl	%edx, %ecx
	jb	.L13
	addl	%edx, %eax
	addl	%r9d, %r8d
	orl	%eax, %ebx
	movd	%ebx, %xmm0
	jmp	.L22
.L58:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE44:
	.size	guarded_branchless, .-guarded_branchless
	.p2align 4
	.type	guarded_anchor, @function
guarded_anchor:
.LFB45:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %rsi
	pxor	%xmm0, %xmm0
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	xorl	%ebp, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	.p2align 4,,10
	.p2align 3
.L70:
	movd	%xmm0, %r13d
	movl	$1000, %r9d
	movl	$32, %eax
	movl	%ebp, %r14d
	movl	%r13d, %ecx
	subl	%ebp, %r9d
	andl	$2147483647, %ecx
	movl	%ecx, %edx
	shrl	$23, %edx
	cmpl	%eax, %r9d
	cmova	%eax, %r9d
	leal	-3(%rdx), %eax
	cmpl	$250, %eax
	jbe	.L99
.L62:
	leaq	(%rsi,%r14,4), %rax
	movl	%r9d, %edx
	movdqu	(%rax), %xmm2
	shrl	$2, %edx
	addss	%xmm2, %xmm0
	movaps	%xmm2, %xmm1
	shufps	$85, %xmm2, %xmm1
	addss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	unpckhps	%xmm2, %xmm1
	shufps	$255, %xmm2, %xmm2
	addss	%xmm1, %xmm0
	movdqu	16(%rax), %xmm1
	addss	%xmm2, %xmm0
	movaps	%xmm1, %xmm2
	shufps	$85, %xmm1, %xmm2
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm2
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$2, %edx
	je	.L69
	movdqu	32(%rax), %xmm2
	addss	%xmm2, %xmm0
	movaps	%xmm2, %xmm1
	shufps	$85, %xmm2, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm2, %xmm0
	unpckhps	%xmm2, %xmm0
	shufps	$255, %xmm2, %xmm2
	addss	%xmm1, %xmm0
	movdqu	48(%rax), %xmm1
	addss	%xmm2, %xmm0
	movaps	%xmm1, %xmm2
	shufps	$85, %xmm1, %xmm2
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm2
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$4, %edx
	je	.L69
	movdqu	64(%rax), %xmm2
	addss	%xmm2, %xmm0
	movaps	%xmm2, %xmm1
	shufps	$85, %xmm2, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm2, %xmm0
	unpckhps	%xmm2, %xmm0
	shufps	$255, %xmm2, %xmm2
	addss	%xmm1, %xmm0
	movdqu	80(%rax), %xmm1
	addss	%xmm2, %xmm0
	movaps	%xmm1, %xmm2
	shufps	$85, %xmm1, %xmm2
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm2
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$6, %edx
	je	.L69
	movdqu	96(%rax), %xmm2
	addss	%xmm2, %xmm0
	movaps	%xmm2, %xmm1
	shufps	$85, %xmm2, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm2, %xmm0
	unpckhps	%xmm2, %xmm0
	shufps	$255, %xmm2, %xmm2
	addss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	cmpl	$8, %edx
	jne	.L69
	movdqu	112(%rax), %xmm2
	addss	%xmm2, %xmm0
	movaps	%xmm2, %xmm1
	shufps	$85, %xmm2, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm2, %xmm0
	unpckhps	%xmm2, %xmm0
	shufps	$255, %xmm2, %xmm2
	addss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
.L69:
	addl	%r9d, %ebp
	movd	%xmm0, %eax
.L68:
	cmpl	$999, %ebp
	jbe	.L70
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L99:
	.cfi_restore_state
	movl	%r13d, %eax
	sall	$23, %edx
	leaq	(%rsi,%r14,4), %rdi
	xorl	%r8d, %r8d
	andl	$-2147483648, %eax
	leal	-8388609(%rdx), %r11d
	movq	%rdi, %r10
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L100:
	cmpl	$3, %r8d
	ja	.L66
.L64:
	movl	(%r10), %edx
	movl	%edx, %ebx
	andl	$2147483647, %ebx
	je	.L63
	movl	%edx, %r12d
	andl	$-2147483648, %r12d
	cmpl	%eax, %r12d
	jne	.L62
	cmpl	%ebx, %r11d
	jb	.L62
	andl	$1, %edx
	je	.L62
.L63:
	addl	$1, %r8d
	addq	$4, %r10
	cmpl	%r9d, %r8d
	jb	.L100
.L66:
	movl	%r13d, %ebx
	movl	%r9d, %edx
	movl	%r13d, -12(%rsp)
	xorl	%r8d, %r8d
	andl	$2139095040, %ebx
	addq	%r14, %rdx
	movl	$1, %r10d
	movd	%ebx, %xmm1
	leaq	(%rsi,%rdx,4), %r12
	.p2align 4,,10
	.p2align 3
.L67:
	movl	(%rdi), %edx
	movl	%edx, %r13d
	andl	$-2147483648, %r13d
	cmpl	%eax, %r13d
	sete	%r15b
	andl	%edx, %r15d
	andl	$2147483647, %edx
	movd	%edx, %xmm3
	sete	%r13b
	addss	%xmm1, %xmm3
	orl	%r15d, %r13d
	xorl	%r15d, %r15d
	cmpl	%edx, %r11d
	setnb	%r15b
	addq	$4, %rdi
	andl	%r15d, %r13d
	movd	%xmm3, %edx
	andl	%r13d, %r10d
	subl	%ebx, %edx
	addl	%edx, %r8d
	cmpq	%rdi, %r12
	jne	.L67
	movl	-12(%rsp), %r13d
	testl	%r10d, %r10d
	je	.L62
	andl	$8388607, %r13d
	movl	$8388608, %edx
	subl	%r13d, %edx
	cmpl	%r8d, %edx
	jb	.L62
	addl	%ecx, %r8d
	addl	%r9d, %ebp
	orl	%r8d, %eax
	movd	%eax, %xmm0
	jmp	.L68
	.cfi_endproc
.LFE45:
	.size	guarded_anchor, .-guarded_anchor
	.p2align 4
	.type	measure, @function
measure:
.LFB47:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rsi, %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	%edx, %r14d
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	xorl	%r13d, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	leaq	400000(%r15), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movl	$1, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	xorl	%ebx, %ebx
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%rsi, 8(%rsp)
	leaq	32(%rsp), %rsi
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	movq	%rsi, 24(%rsp)
	call	clock_gettime@PLT
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	32(%rsp), %xmm0
	mulsd	.LC2(%rip), %xmm0
	cvtsi2sdq	40(%rsp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, 16(%rsp)
	testl	%r14d, %r14d
	je	.L103
.L102:
	movq	8(%rsp), %r15
	.p2align 4,,10
	.p2align 3
.L104:
	movq	%r15, %rdi
	addq	$4000, %r15
	call	*%rbp
	xorl	%ebx, %eax
	imull	$16777619, %eax, %ebx
	cmpq	%r15, %r12
	jne	.L104
	addl	$1, %r13d
	cmpl	%r13d, %r14d
	jne	.L102
.L103:
	movq	24(%rsp), %rsi
	movl	$1, %edi
	call	clock_gettime@PLT
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	movl	%ebx, sink(%rip)
	cvtsi2sdq	32(%rsp), %xmm0
	mulsd	.LC2(%rip), %xmm0
	cvtsi2sdq	40(%rsp), %xmm1
	addsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	subsd	16(%rsp), %xmm0
	cvtsi2sdq	%r14, %xmm1
	mulsd	.LC3(%rip), %xmm1
	mulsd	.LC4(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L113
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L113:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE47:
	.size	measure, .-measure
	.p2align 4
	.type	guarded, @function
guarded:
.LFB43:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xorl	%r9d, %r9d
	pxor	%xmm0, %xmm0
	pxor	%xmm2, %xmm2
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L121:
	movd	%xmm0, %ebx
	movl	$1000, %esi
	movl	$32, %eax
	movl	%r9d, %ebp
	movl	%ebx, %r11d
	subl	%r9d, %esi
	andl	$2147483647, %r11d
	movl	%r11d, %r12d
	shrl	$23, %r12d
	cmpl	%eax, %esi
	cmova	%eax, %esi
	leal	-1(%r12), %eax
	cmpl	$252, %eax
	ja	.L115
	movl	%ebx, %eax
	movl	%r9d, %ebp
	movaps	%xmm2, 16(%rsp)
	movl	%esi, %r10d
	andl	$-2147483648, %eax
	leaq	(%r14,%rbp,4), %r8
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L118:
	movl	(%r8,%rdx,4), %ecx
	movl	%edx, %edi
	movl	%ecx, %r13d
	andl	$2147483647, %r13d
	je	.L116
	movl	%ecx, %r15d
	andl	$-2147483648, %r15d
	cmpl	%r15d, %eax
	je	.L148
.L115:
	leaq	(%r14,%rbp,4), %rax
	movl	%esi, %edx
	movdqu	(%rax), %xmm3
	shrl	$2, %edx
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm1, %xmm0
	movaps	%xmm3, %xmm1
	unpckhps	%xmm3, %xmm1
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	movdqu	16(%rax), %xmm1
	addss	%xmm3, %xmm0
	movaps	%xmm1, %xmm3
	shufps	$85, %xmm1, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm3
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm3, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$2, %edx
	je	.L120
	movdqu	32(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm3, %xmm0
	unpckhps	%xmm3, %xmm0
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	movdqu	48(%rax), %xmm1
	addss	%xmm3, %xmm0
	movaps	%xmm1, %xmm3
	shufps	$85, %xmm1, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm0, %xmm3
	movaps	%xmm1, %xmm0
	unpckhps	%xmm1, %xmm0
	shufps	$255, %xmm1, %xmm1
	addss	%xmm3, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$4, %edx
	je	.L120
	movdqu	64(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm1, %xmm0
	movaps	%xmm3, %xmm1
	unpckhps	%xmm3, %xmm1
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	movdqu	80(%rax), %xmm1
	addss	%xmm3, %xmm0
	movaps	%xmm1, %xmm3
	shufps	$85, %xmm1, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm3, %xmm0
	movaps	%xmm1, %xmm3
	unpckhps	%xmm1, %xmm3
	shufps	$255, %xmm1, %xmm1
	addss	%xmm3, %xmm0
	addss	%xmm1, %xmm0
	cmpl	$6, %edx
	je	.L120
	movdqu	96(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm1, %xmm0
	movaps	%xmm3, %xmm1
	unpckhps	%xmm3, %xmm1
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm3, %xmm0
	cmpl	$8, %edx
	jne	.L120
	movdqu	112(%rax), %xmm3
	addss	%xmm3, %xmm0
	movaps	%xmm3, %xmm1
	shufps	$85, %xmm3, %xmm1
	addss	%xmm0, %xmm1
	movaps	%xmm3, %xmm0
	unpckhps	%xmm3, %xmm0
	shufps	$255, %xmm3, %xmm3
	addss	%xmm1, %xmm0
	addss	%xmm3, %xmm0
.L120:
	addl	%esi, %r9d
	movd	%xmm0, %eax
.L119:
	cmpl	$999, %r9d
	jbe	.L121
	movq	40(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L149
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L148:
	.cfi_restore_state
	shrl	$23, %r13d
	je	.L115
	cmpl	$255, %r13d
	je	.L115
	testb	$1, %cl
	je	.L115
	movl	%r12d, %r15d
	subl	%r13d, %r15d
	leal	-2(%r15), %r13d
	cmpl	$22, %r13d
	ja	.L115
	andl	$8388607, %ecx
	movl	$1, %r13d
	movl	%ecx, 12(%rsp)
	leal	-1(%r15), %ecx
	sall	%cl, %r13d
	movl	%r13d, %ecx
	movl	12(%rsp), %r13d
	leal	8388608(%r13,%rcx), %r13d
	movl	%r15d, %ecx
	shrl	%cl, %r13d
.L116:
	movl	%edi, %ecx
	addq	$1, %rdx
	andl	$3, %ecx
	addl	%r13d, 16(%rsp,%rcx,4)
	cmpq	%r10, %rdx
	jne	.L118
	andl	$8388607, %ebx
	movl	$8388608, %ecx
	movl	20(%rsp), %edx
	addl	16(%rsp), %edx
	subl	%ebx, %ecx
	addl	24(%rsp), %edx
	addl	28(%rsp), %edx
	cmpl	%edx, %ecx
	jb	.L115
	addl	%edx, %r11d
	addl	%esi, %r9d
	orl	%r11d, %eax
	movd	%eax, %xmm0
	jmp	.L119
.L149:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE43:
	.size	guarded, .-guarded
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC5:
	.string	"relu"
.LC6:
	.string	"dense"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC7:
	.string	"class,round,native_ns_per_element,skip_zero_ns_per_element,guarded_ns_per_element,guarded_over_native,branchless_ns_per_element,branchless_over_native,anchor_ns_per_element,anchor_over_native"
	.align 8
.LC8:
	.string	"mismatch kind=%u v=%u %08x %08x\n"
	.align 8
.LC9:
	.string	"branchless mismatch kind=%u v=%u\n"
	.section	.rodata.str1.1
.LC10:
	.string	"anchor mismatch kind=%u v=%u\n"
	.section	.rodata.str1.8
	.align 8
.LC11:
	.string	"%s,%u,%.9f,%.9f,%.9f,%.6f,%.9f,%.6f,%.9f,%.6f\n"
	.section	.rodata.str1.1
.LC12:
	.string	"wide"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB48:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$1000, %r15d
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	cmpl	$1, %edi
	jle	.L151
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtoul@PLT
	movl	%eax, %r15d
.L151:
	movl	$400000, %edi
	call	malloc@PLT
	testq	%rax, %rax
	movq	%rax, (%rsp)
	je	.L174
	leaq	.LC7(%rip), %rdi
	call	puts@PLT
	movq	(%rsp), %rcx
	movq	state(%rip), %rax
	movabsq	$2685821657736338717, %r8
	leaq	400000(%rcx), %r10
	movq	%rcx, %rdi
	.p2align 4,,10
	.p2align 3
.L153:
	movq	%rax, %rdx
	addq	$4, %rdi
	shrq	$12, %rdx
	xorq	%rdx, %rax
	movq	%rax, %rdx
	salq	$25, %rdx
	xorq	%rax, %rdx
	movq	%rdx, %rax
	shrq	$27, %rax
	xorq	%rdx, %rax
	movq	%rax, %rdx
	imulq	%r8, %rdx
	movq	%rdx, %r9
	shrq	$55, %rdx
	movl	%edx, %r11d
	movl	%edx, %esi
	shrq	$32, %r9
	imulq	$613566757, %r11, %r11
	andl	$-2139095041, %r9d
	shrq	$32, %r11
	subl	%r11d, %esi
	shrl	%esi
	addl	%r11d, %esi
	shrl	$2, %esi
	leal	0(,%rsi,8), %r11d
	subl	%esi, %r11d
	subl	%r11d, %edx
	addl	$124, %edx
	sall	$23, %edx
	orl	%r9d, %edx
	movl	%edx, -4(%rdi)
	cmpq	%r10, %rdi
	jne	.L153
	xorl	%r14d, %r14d
.L167:
	movq	%rax, state(%rip)
	movq	%rcx, %rbx
	xorl	%r12d, %r12d
	movq	%rcx, (%rsp)
	movq	%r10, 8(%rsp)
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L156:
	movq	%rbx, %rdi
	call	guarded_branchless
	movl	%eax, %r13d
	cmpl	%ebp, %eax
	jne	.L183
	movq	%rbx, %rdi
	call	guarded_anchor
	cmpl	%r13d, %eax
	jne	.L184
	addl	$1, %r12d
	addq	$4000, %rbx
	cmpl	$100, %r12d
	je	.L185
.L159:
	movq	%rbx, %rdi
	call	ordered
	movq	%rbx, %rdi
	movl	%eax, %ebp
	call	guarded
	cmpl	%eax, %ebp
	je	.L156
	pushq	%rdx
	.cfi_def_cfa_offset 120
	movq	stderr(%rip), %rdi
	movl	%r14d, %ecx
	movl	$2, %esi
	pushq	%rax
	.cfi_def_cfa_offset 128
	movl	%ebp, %r9d
	movl	%r12d, %r8d
	leaq	.LC8(%rip), %rdx
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	popq	%rcx
	.cfi_def_cfa_offset 120
	movl	$2, %eax
	popq	%rsi
	.cfi_def_cfa_offset 112
.L150:
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L183:
	.cfi_restore_state
	movq	stderr(%rip), %rdi
	movl	%r12d, %r8d
	movl	%r14d, %ecx
	xorl	%eax, %eax
	leaq	.LC9(%rip), %rdx
	movl	$2, %esi
	call	__fprintf_chk@PLT
	movl	$3, %eax
	jmp	.L150
.L184:
	movq	stderr(%rip), %rdi
	movl	%r12d, %r8d
	movl	%r14d, %ecx
	xorl	%eax, %eax
	leaq	.LC10(%rip), %rdx
	movl	$2, %esi
	call	__fprintf_chk@PLT
	movl	$4, %eax
	jmp	.L150
.L185:
	movq	(%rsp), %rcx
	movq	8(%rsp), %r10
	xorl	%r12d, %r12d
	leaq	guarded(%rip), %rbp
	movl	$10, %edx
	movq	%rbp, %rdi
	leaq	ordered(%rip), %rbx
	movq	%rcx, %rsi
	movq	%r10, 16(%rsp)
	leaq	guarded_branchless(%rip), %r13
	call	measure
	movq	(%rsp), %rcx
	movl	$10, %edx
	movq	%rbx, %rdi
	movq	%rcx, %rsi
	movq	%rcx, 8(%rsp)
	call	measure
	movq	16(%rsp), %r10
	movl	%r14d, (%rsp)
	movl	%r12d, %r14d
	movq	8(%rsp), %r12
	movq	%r10, 40(%rsp)
.L165:
	movl	%r15d, %edx
	movq	%r12, %rsi
	testb	$1, %r14b
	je	.L160
	leaq	guarded_anchor(%rip), %rdi
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	movq	%r13, %rdi
	movsd	%xmm0, 32(%rsp)
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movsd	%xmm0, 24(%rsp)
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	leaq	ordered_skip_zero(%rip), %rdi
	movsd	%xmm0, 16(%rsp)
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	movsd	%xmm0, 8(%rsp)
	call	measure
	movsd	8(%rsp), %xmm1
	movsd	16(%rsp), %xmm2
	movsd	24(%rsp), %xmm4
	movsd	32(%rsp), %xmm6
	movapd	%xmm0, %xmm8
.L161:
	movl	(%rsp), %eax
	movapd	%xmm6, %xmm7
	movapd	%xmm4, %xmm5
	movapd	%xmm2, %xmm3
	divsd	%xmm8, %xmm7
	divsd	%xmm8, %xmm5
	divsd	%xmm8, %xmm3
	testl	%eax, %eax
	je	.L175
	subl	$1, %eax
	leaq	.LC5(%rip), %rdx
	je	.L162
	movl	%r14d, %ecx
	movapd	%xmm8, %xmm0
	addl	$1, %r14d
	movl	$2, %edi
	leaq	.LC12(%rip), %rdx
	leaq	.LC11(%rip), %rsi
	movl	$8, %eax
	call	__printf_chk@PLT
	cmpl	$5, %r14d
	jne	.L165
	movq	%r12, %rdi
	call	free@PLT
	xorl	%eax, %eax
	jmp	.L150
.L160:
	movq	%rbx, %rdi
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	leaq	ordered_skip_zero(%rip), %rdi
	movsd	%xmm0, 32(%rsp)
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movsd	%xmm0, 24(%rsp)
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	movq	%r13, %rdi
	movsd	%xmm0, 16(%rsp)
	call	measure
	movl	%r15d, %edx
	movq	%r12, %rsi
	leaq	guarded_anchor(%rip), %rdi
	movsd	%xmm0, 8(%rsp)
	call	measure
	movsd	32(%rsp), %xmm8
	movsd	24(%rsp), %xmm1
	movsd	16(%rsp), %xmm2
	movsd	8(%rsp), %xmm4
	movapd	%xmm0, %xmm6
	jmp	.L161
.L175:
	leaq	.LC6(%rip), %rdx
.L162:
	movl	%r14d, %ecx
	movapd	%xmm8, %xmm0
	movl	$2, %edi
	movl	$8, %eax
	leaq	.LC11(%rip), %rsi
	addl	$1, %r14d
	call	__printf_chk@PLT
	cmpl	$5, %r14d
	jne	.L165
	movl	(%rsp), %r14d
	movq	40(%rsp), %r10
	movq	%r12, %rcx
	movq	state(%rip), %rax
	subl	$1, %r14d
	je	.L176
	movabsq	$2685821657736338717, %r8
	movq	%r12, %rsi
	.p2align 4,,10
	.p2align 3
.L166:
	movq	%rax, %rdx
	shrq	$12, %rdx
	xorq	%rdx, %rax
	movq	%rax, %rdx
	salq	$25, %rdx
	xorq	%rax, %rdx
	movq	%rdx, %rax
	shrq	$27, %rax
	xorq	%rdx, %rax
	movq	%rax, %rdx
	imulq	%r8, %rdx
	shrq	$32, %rdx
	testb	$1, %dl
	je	.L168
	movl	%edx, %edi
	andl	$8388607, %edx
	addq	$4, %rsi
	shrl	$23, %edi
	movl	%edi, %r11d
	movl	%edi, %r9d
	imulq	$613566757, %r11, %r11
	shrq	$32, %r11
	subl	%r11d, %r9d
	shrl	%r9d
	addl	%r11d, %r9d
	shrl	$2, %r9d
	leal	0(,%r9,8), %r11d
	subl	%r9d, %r11d
	subl	%r11d, %edi
	addl	$124, %edi
	sall	$23, %edi
	orl	%edi, %edx
	movl	%edx, -4(%rsi)
	cmpq	%r10, %rsi
	jne	.L166
.L170:
	movl	$1, %r14d
	jmp	.L167
	.p2align 4,,10
	.p2align 3
.L168:
	movl	$0, (%rsi)
	addq	$4, %rsi
	cmpq	%rsi, %r10
	jne	.L166
	jmp	.L170
.L176:
	movabsq	$2685821657736338717, %r8
	movq	%rcx, %rdi
	.p2align 4,,10
	.p2align 3
.L154:
	movq	%rax, %rdx
	addq	$4, %rdi
	shrq	$12, %rdx
	xorq	%rdx, %rax
	movq	%rax, %rdx
	salq	$25, %rdx
	xorq	%rax, %rdx
	movq	%rdx, %rax
	shrq	$27, %rax
	xorq	%rdx, %rax
	movq	%rax, %rdx
	imulq	%r8, %rdx
	movq	%rdx, %r9
	shrq	$55, %rdx
	movl	%edx, %esi
	shrq	$32, %r9
	imulq	$1374389535, %rsi, %rsi
	andl	$-2139095041, %r9d
	shrq	$36, %rsi
	imull	$50, %esi, %esi
	subl	%esi, %edx
	addl	$102, %edx
	sall	$23, %edx
	orl	%r9d, %edx
	movl	%edx, -4(%rdi)
	cmpq	%rdi, %r10
	jne	.L154
	movl	$2, %r14d
	jmp	.L167
.L174:
	movl	$1, %eax
	jmp	.L150
	.cfi_endproc
.LFE48:
	.size	main, .-main
	.data
	.align 8
	.type	state, @object
	.size	state, 8
state:
	.quad	2957046932322768507
	.local	sink
	.comm	sink,4,4
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	0
	.long	1104006501
	.align 8
.LC3:
	.long	0
	.long	1079574528
	.align 8
.LC4:
	.long	0
	.long	1083129856
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
