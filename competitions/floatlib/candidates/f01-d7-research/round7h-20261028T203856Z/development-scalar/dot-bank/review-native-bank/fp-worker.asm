
   0:	push   rbp
   1:	push   r15
   3:	push   r14
   5:	push   r13
   7:	push   r12
   9:	push   rbx
   a:	push   rax
   b:	mov    rbx,rsi
   e:	movabs r14,0x8000000000000000
  18:	jmp    6b <lp_competition_Submission_R24PortableF64_sumRemaining+0x6b>
  1a:	movsd  QWORD PTR [rsp],xmm0
  1f:	mov    r12,rcx
  22:	mov    r13,rdi
  25:	mov    esi,0x3
  2a:	mov    rdi,rdx
  2d:	mov    r15,rdx
  30:	call   35 <lp_competition_Submission_R24PortableF64_sumRemaining+0x35>
			31: R_X86_64_PLT32	lean_nat_big_add-0x4
  35:	mov    edx,DWORD PTR [r15]
  38:	cmp    edx,0x2
  3b:	jl     186 <lp_competition_Submission_R24PortableF64_sumRemaining+0x186>
  41:	dec    edx
  43:	mov    DWORD PTR [r15],edx
  46:	xorpd  xmm2,xmm2
  4a:	xorpd  xmm1,xmm1
  4e:	mov    rdi,r13
  51:	mov    rcx,r12
  54:	movsd  xmm0,QWORD PTR [rsp]
  59:	nop    DWORD PTR [rax+0x0]
  60:	mulsd  xmm2,xmm1
  64:	addsd  xmm0,xmm2
  68:	mov    rdx,rax
  6b:	mov    r15,rcx
  6e:	test   r15b,0x1
  72:	je     ca <lp_competition_Submission_R24PortableF64_sumRemaining+0xca>
  74:	cmp    r15,0x1
  78:	je     1c5 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1c5>
  7e:	mov    ecx,0x1
  83:	jbe    8c <lp_competition_Submission_R24PortableF64_sumRemaining+0x8c>
  85:	add    r15,0xfffffffffffffffe
  89:	mov    rcx,r15
  8c:	test   dl,0x1
  8f:	je     1a <lp_competition_Submission_R24PortableF64_sumRemaining+0x1a>
  91:	shr    rdx,1
  94:	mov    rax,rdx
  97:	inc    rax
  9a:	js     120 <lp_competition_Submission_R24PortableF64_sumRemaining+0x120>
  a0:	lea    rax,[rax*2+0x1]
  a8:	xorpd  xmm2,xmm2
  ac:	xorpd  xmm1,xmm1
  b0:	cmp    rdx,QWORD PTR [rdi+0x8]
  b4:	jae    bc <lp_competition_Submission_R24PortableF64_sumRemaining+0xbc>
  b6:	movsd  xmm1,QWORD PTR [rdi+rdx*8+0x18]
  bc:	cmp    rdx,QWORD PTR [rbx+0x8]
  c0:	jae    60 <lp_competition_Submission_R24PortableF64_sumRemaining+0x60>
  c2:	movsd  xmm2,QWORD PTR [rbx+rdx*8+0x18]
  c8:	jmp    60 <lp_competition_Submission_R24PortableF64_sumRemaining+0x60>
  ca:	movsd  QWORD PTR [rsp],xmm0
  cf:	mov    r13,rdi
  d2:	mov    r12,rdx
  d5:	mov    esi,0x1
  da:	mov    rdi,r15
  dd:	call   e2 <lp_competition_Submission_R24PortableF64_sumRemaining+0xe2>
			de: R_X86_64_PLT32	lean_nat_big_eq-0x4
  e2:	test   al,al
  e4:	jne    1b0 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1b0>
  ea:	mov    esi,0x3
  ef:	mov    rdi,r15
  f2:	call   f7 <lp_competition_Submission_R24PortableF64_sumRemaining+0xf7>
			f3: R_X86_64_PLT32	lean_nat_big_sub-0x4
  f7:	mov    rcx,rax
  fa:	mov    eax,DWORD PTR [r15]
  fd:	cmp    eax,0x2
 100:	jl     15b <lp_competition_Submission_R24PortableF64_sumRemaining+0x15b>
 102:	dec    eax
 104:	mov    DWORD PTR [r15],eax
 107:	mov    rdx,r12
 10a:	mov    rdi,r13
 10d:	movsd  xmm0,QWORD PTR [rsp]
 112:	test   dl,0x1
 115:	jne    91 <lp_competition_Submission_R24PortableF64_sumRemaining+0x91>
 11b:	jmp    1a <lp_competition_Submission_R24PortableF64_sumRemaining+0x1a>
 120:	mov    r15,rdi
 123:	mov    rdi,r14
 126:	mov    r12,rdx
 129:	mov    r13,rcx
 12c:	movsd  QWORD PTR [rsp],xmm0
 131:	call   136 <lp_competition_Submission_R24PortableF64_sumRemaining+0x136>
			132: R_X86_64_PLT32	lean_big_usize_to_nat-0x4
 136:	movsd  xmm0,QWORD PTR [rsp]
 13b:	mov    rcx,r13
 13e:	mov    rdi,r15
 141:	mov    rdx,r12
 144:	xorpd  xmm2,xmm2
 148:	xorpd  xmm1,xmm1
 14c:	cmp    rdx,QWORD PTR [rdi+0x8]
 150:	jb     b6 <lp_competition_Submission_R24PortableF64_sumRemaining+0xb6>
 156:	jmp    bc <lp_competition_Submission_R24PortableF64_sumRemaining+0xbc>
 15b:	mov    rbp,rcx
 15e:	test   eax,eax
 160:	je     16a <lp_competition_Submission_R24PortableF64_sumRemaining+0x16a>
 162:	mov    rdi,r15
 165:	call   16a <lp_competition_Submission_R24PortableF64_sumRemaining+0x16a>
			166: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 16a:	mov    rdx,r12
 16d:	mov    rdi,r13
 170:	mov    rcx,rbp
 173:	movsd  xmm0,QWORD PTR [rsp]
 178:	test   dl,0x1
 17b:	jne    91 <lp_competition_Submission_R24PortableF64_sumRemaining+0x91>
 181:	jmp    1a <lp_competition_Submission_R24PortableF64_sumRemaining+0x1a>
 186:	mov    rbp,rax
 189:	test   edx,edx
 18b:	je     195 <lp_competition_Submission_R24PortableF64_sumRemaining+0x195>
 18d:	mov    rdi,r15
 190:	call   195 <lp_competition_Submission_R24PortableF64_sumRemaining+0x195>
			191: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 195:	xorpd  xmm1,xmm1
 199:	mov    rdi,r13
 19c:	mov    rcx,r12
 19f:	mov    rax,rbp
 1a2:	movsd  xmm0,QWORD PTR [rsp]
 1a7:	xorpd  xmm2,xmm2
 1ab:	jmp    60 <lp_competition_Submission_R24PortableF64_sumRemaining+0x60>
 1b0:	mov    eax,DWORD PTR [r15]
 1b3:	cmp    eax,0x2
 1b6:	mov    rdx,r12
 1b9:	jl     1fc <lp_competition_Submission_R24PortableF64_sumRemaining+0x1fc>
 1bb:	dec    eax
 1bd:	mov    DWORD PTR [r15],eax
 1c0:	movsd  xmm0,QWORD PTR [rsp]
 1c5:	test   dl,0x1
 1c8:	jne    1d5 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1d5>
 1ca:	mov    eax,DWORD PTR [rdx]
 1cc:	cmp    eax,0x2
 1cf:	jl     1e4 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1e4>
 1d1:	dec    eax
 1d3:	mov    DWORD PTR [rdx],eax
 1d5:	add    rsp,0x8
 1d9:	pop    rbx
 1da:	pop    r12
 1dc:	pop    r13
 1de:	pop    r14
 1e0:	pop    r15
 1e2:	pop    rbp
 1e3:	ret
 1e4:	test   eax,eax
 1e6:	je     1d5 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1d5>
 1e8:	mov    rdi,rdx
 1eb:	movsd  QWORD PTR [rsp],xmm0
 1f0:	call   1f5 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1f5>
			1f1: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 1f5:	movsd  xmm0,QWORD PTR [rsp]
 1fa:	jmp    1d5 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1d5>
 1fc:	test   eax,eax
 1fe:	movsd  xmm0,QWORD PTR [rsp]
 203:	je     1c5 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1c5>
 205:	mov    rdi,r15
 208:	call   20d <lp_competition_Submission_R24PortableF64_sumRemaining+0x20d>
			209: R_X86_64_PLT32	lean_dec_ref_cold-0x4
 20d:	movsd  xmm0,QWORD PTR [rsp]
 212:	mov    rdx,r12
 215:	jmp    1c5 <lp_competition_Submission_R24PortableF64_sumRemaining+0x1c5>

Disassembly of section .text.lp_competition_Submission_R24PortableF64_sumRemaining___boxed:
