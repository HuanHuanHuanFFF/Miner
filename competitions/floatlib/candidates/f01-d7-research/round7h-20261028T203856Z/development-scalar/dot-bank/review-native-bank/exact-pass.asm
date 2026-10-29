
   0:	push   rbp
   1:	push   r15
   3:	push   r14
   5:	push   r13
   7:	push   r12
   9:	push   rbx
   a:	push   rax
   b:	mov    ebx,esi
   d:	mov    r14,rdi
  10:	test   dl,0x1
  13:	je     ff <lp_competition_R24DotBankHarness_passExact+0xff>
  19:	nop    DWORD PTR [rax+0x0]
  20:	cmp    rdx,0x1
  24:	je     1c4 <lp_competition_R24DotBankHarness_passExact+0x1c4>
  2a:	mov    r15d,0x1
  30:	jbe    39 <lp_competition_R24DotBankHarness_passExact+0x39>
  32:	add    rdx,0xfffffffffffffffe
  36:	mov    r15,rdx
  39:	mov    rdi,r15
  3c:	mov    rsi,r14
  3f:	call   44 <lp_competition_R24DotBankHarness_passExact+0x44>
			40: R_X86_64_PLT32	lp_competition_R24DotBarrier_touchBank-0x4
  44:	mov    r14,rax
  47:	mov    r12,QWORD PTR [rax+0x8]
  4b:	test   r12b,0x1
  4f:	jne    63 <lp_competition_R24DotBankHarness_passExact+0x63>
  51:	mov    eax,DWORD PTR [r12]
  55:	test   eax,eax
  57:	jle    14d <lp_competition_R24DotBankHarness_passExact+0x14d>
  5d:	inc    eax
  5f:	mov    DWORD PTR [r12],eax
  63:	mov    rbp,QWORD PTR [r14+0x10]
  67:	test   bpl,0x1
  6b:	jne    a0 <lp_competition_R24DotBankHarness_passExact+0xa0>
  6d:	mov    eax,DWORD PTR [rbp+0x0]
  70:	test   eax,eax
  72:	jle    162 <lp_competition_R24DotBankHarness_passExact+0x162>
  78:	inc    eax
  7a:	mov    DWORD PTR [rbp+0x0],eax
  7d:	mov    rdi,r12
  80:	mov    rsi,rbp
  83:	call   88 <lp_competition_R24DotBankHarness_passExact+0x88>
			84: R_X86_64_PLT32	lp_competition_Submission_R24GenericDotBank_exactBank-0x4
  88:	mov    r13,rax
  8b:	mov    eax,DWORD PTR [rbp+0x0]
  8e:	cmp    eax,0x2
  91:	jl     176 <lp_competition_R24DotBankHarness_passExact+0x176>
  97:	dec    eax
  99:	mov    DWORD PTR [rbp+0x0],eax
  9c:	jmp    ae <lp_competition_R24DotBankHarness_passExact+0xae>
  9e:	xchg   ax,ax
  a0:	mov    rdi,r12
  a3:	mov    rsi,rbp
  a6:	call   ab <lp_competition_R24DotBankHarness_passExact+0xab>
			a7: R_X86_64_PLT32	lp_competition_Submission_R24GenericDotBank_exactBank-0x4
  ab:	mov    r13,rax
  ae:	test   r12b,0x1
  b2:	jne    c7 <lp_competition_R24DotBankHarness_passExact+0xc7>
  b4:	mov    eax,DWORD PTR [r12]
  b8:	cmp    eax,0x2
  bb:	jl     18b <lp_competition_R24DotBankHarness_passExact+0x18b>
  c1:	dec    eax
  c3:	mov    DWORD PTR [r12],eax
  c7:	mov    rax,QWORD PTR [r13+0x8]
  cb:	lea    rcx,[rax*2+0x1]
  d3:	mov    esi,0x1
  d8:	mov    rdi,r13
  db:	xor    edx,edx
  dd:	call   e2 <lp_competition_R24DotBankHarness_passExact+0xe2>
			de: R_X86_64_PLT32	lp_competition_R24DotBankHarness_sumRemaining-0x4
  e2:	mov    ecx,DWORD PTR [r13+0x0]
  e6:	cmp    ecx,0x2
  e9:	jl     13b <lp_competition_R24DotBankHarness_passExact+0x13b>
  eb:	dec    ecx
  ed:	mov    DWORD PTR [r13+0x0],ecx
  f1:	add    ebx,eax
  f3:	mov    rdx,r15
  f6:	test   dl,0x1
  f9:	jne    20 <lp_competition_R24DotBankHarness_passExact+0x20>
  ff:	mov    esi,0x1
 104:	mov    r12,rdx
 107:	mov    rdi,rdx
 10a:	call   10f <lp_competition_R24DotBankHarness_passExact+0x10f>
			10b: R_X86_64_PLT32	lean_nat_big_eq-0x4
 10f:	test   al,al
 111:	jne    1b5 <lp_competition_R24DotBankHarness_passExact+0x1b5>
 117:	mov    esi,0x3
 11c:	mov    rdi,r12
 11f:	call   124 <lp_competition_R24DotBankHarness_passExact+0x124>
			120: R_X86_64_PLT32	lean_nat_big_sub-0x4
 124:	mov    r15,rax
 127:	mov    eax,DWORD PTR [r12]
 12b:	cmp    eax,0x2
 12e:	jl     1a0 <lp_competition_R24DotBankHarness_passExact+0x1a0>
 130:	dec    eax
 132:	mov    DWORD PTR [r12],eax
 136:	jmp    39 <lp_competition_R24DotBankHarness_passExact+0x39>
 13b:	test   ecx,ecx
 13d:	je     f1 <lp_competition_R24DotBankHarness_passExact+0xf1>
 13f:	mov    rdi,r13
 142:	mov    ebp,eax
 144:	call   149 <lp_competition_R24DotBankHarness_passExact+0x149>
			145: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 149:	mov    eax,ebp
 14b:	jmp    f1 <lp_competition_R24DotBankHarness_passExact+0xf1>
 14d:	cmp    eax,0x90000001
 152:	jb     63 <lp_competition_R24DotBankHarness_passExact+0x63>
 158:	lock dec DWORD PTR [r12]
 15d:	jmp    63 <lp_competition_R24DotBankHarness_passExact+0x63>
 162:	cmp    eax,0x90000001
 167:	jb     7d <lp_competition_R24DotBankHarness_passExact+0x7d>
 16d:	lock dec DWORD PTR [rbp+0x0]
 171:	jmp    7d <lp_competition_R24DotBankHarness_passExact+0x7d>
 176:	test   eax,eax
 178:	je     ae <lp_competition_R24DotBankHarness_passExact+0xae>
 17e:	mov    rdi,rbp
 181:	call   186 <lp_competition_R24DotBankHarness_passExact+0x186>
			182: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 186:	jmp    ae <lp_competition_R24DotBankHarness_passExact+0xae>
 18b:	test   eax,eax
 18d:	je     c7 <lp_competition_R24DotBankHarness_passExact+0xc7>
 193:	mov    rdi,r12
 196:	call   19b <lp_competition_R24DotBankHarness_passExact+0x19b>
			197: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 19b:	jmp    c7 <lp_competition_R24DotBankHarness_passExact+0xc7>
 1a0:	test   eax,eax
 1a2:	je     39 <lp_competition_R24DotBankHarness_passExact+0x39>
 1a8:	mov    rdi,r12
 1ab:	call   1b0 <lp_competition_R24DotBankHarness_passExact+0x1b0>
			1ac: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 1b0:	jmp    39 <lp_competition_R24DotBankHarness_passExact+0x39>
 1b5:	mov    eax,DWORD PTR [r12]
 1b9:	cmp    eax,0x2
 1bc:	jl     1f0 <lp_competition_R24DotBankHarness_passExact+0x1f0>
 1be:	dec    eax
 1c0:	mov    DWORD PTR [r12],eax
 1c4:	mov    eax,DWORD PTR [r14]
 1c7:	cmp    eax,0x2
 1ca:	jl     1e2 <lp_competition_R24DotBankHarness_passExact+0x1e2>
 1cc:	dec    eax
 1ce:	mov    DWORD PTR [r14],eax
 1d1:	mov    eax,ebx
 1d3:	add    rsp,0x8
 1d7:	pop    rbx
 1d8:	pop    r12
 1da:	pop    r13
 1dc:	pop    r14
 1de:	pop    r15
 1e0:	pop    rbp
 1e1:	ret
 1e2:	test   eax,eax
 1e4:	je     1d1 <lp_competition_R24DotBankHarness_passExact+0x1d1>
 1e6:	mov    rdi,r14
 1e9:	call   1ee <lp_competition_R24DotBankHarness_passExact+0x1ee>
			1ea: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 1ee:	jmp    1d1 <lp_competition_R24DotBankHarness_passExact+0x1d1>
 1f0:	test   eax,eax
 1f2:	je     1c4 <lp_competition_R24DotBankHarness_passExact+0x1c4>
 1f4:	mov    rdi,r12
 1f7:	call   1fc <lp_competition_R24DotBankHarness_passExact+0x1fc>
			1f8: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 1fc:	jmp    1c4 <lp_competition_R24DotBankHarness_passExact+0x1c4>

Disassembly of section .text.lp_competition_R24DotBankHarness_passExact___boxed:
