
   0:	push   rbp
   1:	push   r15
   3:	push   r14
   5:	push   r13
   7:	push   r12
   9:	push   rbx
   a:	push   rax
   b:	mov    r13,rcx
   e:	mov    ebx,edx
  10:	mov    r14,rsi
  13:	mov    r15,rdi
  16:	jmp    2e <lp_competition_R24DotBankHarness_sumRemaining+0x2e>
  18:	nop    DWORD PTR [rax+rax*1+0x0]
  20:	mov    r12,QWORD PTR [r15+r12*8+0x18]
  25:	shr    r12,1
  28:	add    ebx,r12d
  2b:	mov    r14,rbp
  2e:	mov    rbp,r13
  31:	test   bpl,0x1
  35:	je     c4 <lp_competition_R24DotBankHarness_sumRemaining+0xc4>
  3b:	cmp    rbp,0x1
  3f:	je     18f <lp_competition_R24DotBankHarness_sumRemaining+0x18f>
  45:	mov    r13d,0x1
  4b:	jbe    54 <lp_competition_R24DotBankHarness_sumRemaining+0x54>
  4d:	add    rbp,0xfffffffffffffffe
  51:	mov    r13,rbp
  54:	test   r14b,0x1
  58:	je     fb <lp_competition_R24DotBankHarness_sumRemaining+0xfb>
  5e:	mov    r12,r14
  61:	shr    r12,1
  64:	mov    rax,r12
  67:	inc    rax
  6a:	js     124 <lp_competition_R24DotBankHarness_sumRemaining+0x124>
  70:	lea    rbp,[rax*2+0x1]
  78:	cmp    r12,QWORD PTR [r15+0x8]
  7c:	jb     20 <lp_competition_R24DotBankHarness_sumRemaining+0x20>
  7e:	mov    rax,QWORD PTR [rip+0x0]        # 85 <lp_competition_R24DotBankHarness_sumRemaining+0x85>
			81: R_X86_64_REX_GOTPCRELX	lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1-0x4
  85:	mov    rdi,QWORD PTR [rax]
  88:	test   dil,0x1
  8c:	jne    9c <lp_competition_R24DotBankHarness_sumRemaining+0x9c>
  8e:	mov    eax,DWORD PTR [rdi]
  90:	test   eax,eax
  92:	jle    145 <lp_competition_R24DotBankHarness_sumRemaining+0x145>
  98:	inc    eax
  9a:	mov    DWORD PTR [rdi],eax
  9c:	call   a1 <lp_competition_R24DotBankHarness_sumRemaining+0xa1>
			9d: R_X86_64_PLT32	lean_array_get_panic-0x4
  a1:	mov    r12,rax
  a4:	test   r14b,0x1
  a8:	jne    25 <lp_competition_R24DotBankHarness_sumRemaining+0x25>
  ae:	mov    eax,DWORD PTR [r14]
  b1:	cmp    eax,0x2
  b4:	jl     158 <lp_competition_R24DotBankHarness_sumRemaining+0x158>
  ba:	dec    eax
  bc:	mov    DWORD PTR [r14],eax
  bf:	jmp    25 <lp_competition_R24DotBankHarness_sumRemaining+0x25>
  c4:	mov    esi,0x1
  c9:	mov    rdi,rbp
  cc:	call   d1 <lp_competition_R24DotBankHarness_sumRemaining+0xd1>
			cd: R_X86_64_PLT32	lean_nat_big_eq-0x4
  d1:	test   al,al
  d3:	jne    182 <lp_competition_R24DotBankHarness_sumRemaining+0x182>
  d9:	mov    esi,0x3
  de:	mov    rdi,rbp
  e1:	call   e6 <lp_competition_R24DotBankHarness_sumRemaining+0xe6>
			e2: R_X86_64_PLT32	lean_nat_big_sub-0x4
  e6:	mov    r13,rax
  e9:	mov    eax,DWORD PTR [rbp+0x0]
  ec:	cmp    eax,0x2
  ef:	jl     16d <lp_competition_R24DotBankHarness_sumRemaining+0x16d>
  f1:	dec    eax
  f3:	mov    DWORD PTR [rbp+0x0],eax
  f6:	jmp    54 <lp_competition_R24DotBankHarness_sumRemaining+0x54>
  fb:	mov    esi,0x3
 100:	mov    rdi,r14
 103:	call   108 <lp_competition_R24DotBankHarness_sumRemaining+0x108>
			104: R_X86_64_PLT32	lean_nat_big_add-0x4
 108:	mov    rbp,rax
 10b:	mov    rax,QWORD PTR [rip+0x0]        # 112 <lp_competition_R24DotBankHarness_sumRemaining+0x112>
			10e: R_X86_64_REX_GOTPCRELX	lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1-0x4
 112:	mov    rdi,QWORD PTR [rax]
 115:	test   dil,0x1
 119:	je     8e <lp_competition_R24DotBankHarness_sumRemaining+0x8e>
 11f:	jmp    9c <lp_competition_R24DotBankHarness_sumRemaining+0x9c>
 124:	movabs rdi,0x8000000000000000
 12e:	call   133 <lp_competition_R24DotBankHarness_sumRemaining+0x133>
			12f: R_X86_64_PLT32	lean_big_usize_to_nat-0x4
 133:	mov    rbp,rax
 136:	cmp    r12,QWORD PTR [r15+0x8]
 13a:	jb     20 <lp_competition_R24DotBankHarness_sumRemaining+0x20>
 140:	jmp    7e <lp_competition_R24DotBankHarness_sumRemaining+0x7e>
 145:	cmp    eax,0x90000001
 14a:	jb     9c <lp_competition_R24DotBankHarness_sumRemaining+0x9c>
 150:	lock dec DWORD PTR [rdi]
 153:	jmp    9c <lp_competition_R24DotBankHarness_sumRemaining+0x9c>
 158:	test   eax,eax
 15a:	je     25 <lp_competition_R24DotBankHarness_sumRemaining+0x25>
 160:	mov    rdi,r14
 163:	call   168 <lp_competition_R24DotBankHarness_sumRemaining+0x168>
			164: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 168:	jmp    25 <lp_competition_R24DotBankHarness_sumRemaining+0x25>
 16d:	test   eax,eax
 16f:	je     54 <lp_competition_R24DotBankHarness_sumRemaining+0x54>
 175:	mov    rdi,rbp
 178:	call   17d <lp_competition_R24DotBankHarness_sumRemaining+0x17d>
			179: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 17d:	jmp    54 <lp_competition_R24DotBankHarness_sumRemaining+0x54>
 182:	mov    eax,DWORD PTR [rbp+0x0]
 185:	cmp    eax,0x2
 188:	jl     1c1 <lp_competition_R24DotBankHarness_sumRemaining+0x1c1>
 18a:	dec    eax
 18c:	mov    DWORD PTR [rbp+0x0],eax
 18f:	test   r14b,0x1
 193:	jne    1a2 <lp_competition_R24DotBankHarness_sumRemaining+0x1a2>
 195:	mov    eax,DWORD PTR [r14]
 198:	cmp    eax,0x2
 19b:	jl     1b3 <lp_competition_R24DotBankHarness_sumRemaining+0x1b3>
 19d:	dec    eax
 19f:	mov    DWORD PTR [r14],eax
 1a2:	mov    eax,ebx
 1a4:	add    rsp,0x8
 1a8:	pop    rbx
 1a9:	pop    r12
 1ab:	pop    r13
 1ad:	pop    r14
 1af:	pop    r15
 1b1:	pop    rbp
 1b2:	ret
 1b3:	test   eax,eax
 1b5:	je     1a2 <lp_competition_R24DotBankHarness_sumRemaining+0x1a2>
 1b7:	mov    rdi,r14
 1ba:	call   1bf <lp_competition_R24DotBankHarness_sumRemaining+0x1bf>
			1bb: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 1bf:	jmp    1a2 <lp_competition_R24DotBankHarness_sumRemaining+0x1a2>
 1c1:	test   eax,eax
 1c3:	je     18f <lp_competition_R24DotBankHarness_sumRemaining+0x18f>
 1c5:	mov    rdi,rbp
 1c8:	call   1cd <lp_competition_R24DotBankHarness_sumRemaining+0x1cd>
			1c9: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 1cd:	jmp    18f <lp_competition_R24DotBankHarness_sumRemaining+0x18f>

Disassembly of section .text.lp_competition_R24DotBankHarness_sumRemaining___boxed:
