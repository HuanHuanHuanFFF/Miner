
	.section	.text._RNvNtCs2hd9JHJjR4I_9candidate5parse10bulk_parse,"ax",@progbits
	.prefalign	4, .Lfunc_end3, nop
	.type	_RNvNtCs2hd9JHJjR4I_9candidate5parse10bulk_parse,@function
_RNvNtCs2hd9JHJjR4I_9candidate5parse10bulk_parse:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%r13
	.cfi_def_cfa_offset 32
	pushq	%r12
	.cfi_def_cfa_offset 40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	subq	$1024, %rsp
	.cfi_def_cfa_offset 1072
	.cfi_offset %rbx, -48
	.cfi_offset %r12, -40
	.cfi_offset %r13, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	cmpq	$499999, %rsi
	jle	.LBB3_1
	cmpq	$999999, %rsi
	jg	.LBB3_34
	cmpq	$699999, %rsi
	jle	.LBB3_18
	cmpq	$700000, %rsi
	je	.LBB3_37
	cmpq	$800000, %rsi
	je	.LBB3_74
	cmpq	$900000, %rsi
	jne	.LBB3_11
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row7
.LBB3_1:
	.cfi_def_cfa_offset 1072
	cmpq	$249999, %rsi
	jle	.LBB3_2
	cmpq	$349999, %rsi
	jle	.LBB3_9
	cmpq	$350000, %rsi
	je	.LBB3_20
	cmpq	$400000, %rsi
	je	.LBB3_20
	cmpq	$450000, %rsi
	jne	.LBB3_11
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row13
.LBB3_34:
	.cfi_def_cfa_offset 1072
	cmpq	$1299999, %rsi
	jle	.LBB3_35
	cmpq	$1300000, %rsi
	je	.LBB3_7
	cmpq	$1400000, %rsi
	je	.LBB3_37
	cmpq	$1500000, %rsi
	jne	.LBB3_11
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row10
.LBB3_2:
	.cfi_def_cfa_offset 1072
	cmpq	$39999, %rsi
	jg	.LBB3_5
	cmpq	$12000, %rsi
	je	.LBB3_76
	cmpq	$28000, %rsi
	je	.LBB3_7
	jmp	.LBB3_11
.LBB3_5:
	cmpq	$40000, %rsi
	je	.LBB3_75
	cmpq	$150000, %rsi
	je	.LBB3_7
	jmp	.LBB3_11
.LBB3_9:
	cmpq	$250000, %rsi
	je	.LBB3_20
	cmpq	$300000, %rsi
	je	.LBB3_20
	jmp	.LBB3_11
.LBB3_18:
	cmpq	$500000, %rsi
	je	.LBB3_20
	cmpq	$600000, %rsi
	je	.LBB3_20
	jmp	.LBB3_11
.LBB3_35:
	cmpq	$1000000, %rsi
	je	.LBB3_20
	cmpq	$1100000, %rsi
	je	.LBB3_37
	jmp	.LBB3_11
.LBB3_20:
	movq	%rdx, %rbx
	movq	%rcx, %r14
	movq	%rsp, %rax
	xorl	%r15d, %r15d
	movl	$1024, %edx
	movq	%rdi, %r12
	movq	%rax, %rdi
	movq	%rsi, %r13
	xorl	%esi, %esi
	callq	*memset@GOTPCREL(%rip)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movq	%r13, %rcx
	shrq	$12, %rcx
	orq	$1, %rcx
	xorl	%edx, %edx
	.p2align	4
.LBB3_21:
	movzbl	(%rdi,%rdx), %eax
	movl	(%rsp,%rax,4), %r8d
	cmpl	$-1, %r8d
	je	.LBB3_67
	incl	%r8d
	movl	%r8d, (%rsp,%rax,4)
	leal	1(%r15), %eax
	addq	%rcx, %rdx
	cmpq	%rsi, %rdx
	jae	.LBB3_24
	cmpl	$4096, %r15d
	movl	%eax, %r15d
	jb	.LBB3_21
.LBB3_24:
	cmpq	$399999, %rsi
	jle	.LBB3_25
	cmpq	$599999, %rsi
	movq	%r14, %rcx
	movq	%rbx, %rdx
	jg	.LBB3_49
	cmpq	$400000, %rsi
	je	.LBB3_68
	cmpq	$500000, %rsi
	jne	.LBB3_11
	cmpl	$0, (%rsp)
	je	.LBB3_70
	movl	8(%rsp), %r8d
	addl	4(%rsp), %r8d
	jb	.LBB3_66
	movl	%eax, %eax
	imulq	$1374389535, %rax, %rax
	shrq	$35, %rax
	cmpl	%eax, %r8d
	jbe	.LBB3_69
	jmp	.LBB3_48
.LBB3_25:
	cmpq	$250000, %rsi
	movq	%r14, %rcx
	movq	%rbx, %rdx
	je	.LBB3_53
	cmpq	$300000, %rsi
	je	.LBB3_71
	cmpq	$350000, %rsi
	jne	.LBB3_11
	shrl	$6, %eax
	cmpl	%eax, 240(%rsp)
	jb	.LBB3_37
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row15
.LBB3_49:
	.cfi_def_cfa_offset 1072
	cmpq	$600000, %rsi
	je	.LBB3_72
	cmpq	$1000000, %rsi
	jne	.LBB3_11
	shrl	$8, %eax
	cmpl	%eax, 236(%rsp)
	jbe	.LBB3_37
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row1
.LBB3_37:
	.cfi_def_cfa_offset 1072
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9
.LBB3_11:
	.cfi_def_cfa_offset 1072
	movq	%rsi, %rbx
	callq	_RNvNtCs2hd9JHJjR4I_9candidate5parse8fallback
	movq	%rbx, %rax
	jmp	.LBB3_64
.LBB3_76:
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row12
.LBB3_75:
	.cfi_def_cfa_offset 1072
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row11
.LBB3_74:
	.cfi_def_cfa_offset 1072
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row5
.LBB3_53:
	.cfi_def_cfa_offset 1072
	movl	704(%rsp), %r8d
	addl	192(%rsp), %r8d
	jb	.LBB3_77
	movl	%eax, %r9d
	movl	$3435973837, %r10d
	imulq	%r9, %r10
	shrq	$35, %r10
	cmpl	%r10d, %r8d
	ja	.LBB3_63
	movl	520(%rsp), %r8d
	addl	512(%rsp), %r8d
	jb	.LBB3_65
	addl	528(%rsp), %r8d
	jb	.LBB3_65
	addl	544(%rsp), %r8d
	jb	.LBB3_65
	addl	564(%rsp), %r8d
	jb	.LBB3_65
	addl	568(%rsp), %r8d
	jb	.LBB3_65
	addl	572(%rsp), %r8d
	jb	.LBB3_65
	addl	592(%rsp), %r8d
	jb	.LBB3_65
	shrl	$7, %eax
	cmpl	%eax, %r8d
	jae	.LBB3_48
.LBB3_63:
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	callq	_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row14
	movl	$250000, %eax
.LBB3_64:
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.LBB3_68:
	.cfi_def_cfa_offset 1072
	shrl	$5, %eax
	cmpl	%eax, 136(%rsp)
	jbe	.LBB3_73
.LBB3_69:
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row0
.LBB3_71:
	.cfi_def_cfa_offset 1072
	movl	%eax, %eax
	imulq	$1374389535, %rax, %rax
	shrq	$37, %rax
	cmpl	%eax, 232(%rsp)
	jbe	.LBB3_72
.LBB3_7:
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row6
.LBB3_72:
	.cfi_def_cfa_offset 1072
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row3
.LBB3_48:
	.cfi_def_cfa_offset 1072
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row8
.LBB3_73:
	.cfi_def_cfa_offset 1072
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row4
.LBB3_70:
	.cfi_def_cfa_offset 1072
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	addq	$1024, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2
.LBB3_67:
	.cfi_def_cfa_offset 1072
	leaq	.Lalloc_9c1b18d5eccf76adc061516add2c0cb5(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB3_65:
	leaq	.Lalloc_9d558666582b3dbebd4dba7f4dfd4be0(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB3_77:
	leaq	.Lalloc_8b6ff933d0302ff74dd8b8b707a405ff(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.LBB3_66:
	leaq	.Lalloc_22bac865c928cac69d93dbd78cb85fe2(%rip), %rdi
	callq	*_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow@GOTPCREL(%rip)
.Lfunc_end3:
	.size	_RNvNtCs2hd9JHJjR4I_9candidate5parse10bulk_parse, .Lfunc_end3-_RNvNtCs2hd9JHJjR4I_9candidate5parse10bulk_parse
	.cfi_endproc
