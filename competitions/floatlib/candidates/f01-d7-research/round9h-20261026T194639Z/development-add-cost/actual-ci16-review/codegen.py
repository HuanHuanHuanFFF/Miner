"""Actual selected Main C/relocation ASM mechanism audit; no recompilation."""
from pathlib import Path
import hashlib,json,re,shlex
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
D=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40436948264/download-2f6165a21e5d4de0b18207e85d2f3b4f/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-add-cost1/add-cost'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def save(n,x):(H/n).write_bytes((json.dumps(x,indent=2)+'\n').encode())
def parse(name):
 text=(H/(name+'.asm.txt')).read_text();instructions=[];relocs=[]
 for line in text.splitlines():
  m=re.match(r'\s*([0-9a-f]+):\s+(R_\S+)\s+(.*)',line)
  if m:relocs.append(dict(address=int(m[1],16),kind=m[2],target=m[3]));continue
  m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
  if m:instructions.append(dict(address=int(m[1],16),op=m[2],args=m[3]))
 return instructions,relocs
P='lp_competition_';control,cr=parse(P+'r19CostControlAdd');guard,gr=parse(P+'r19CostGuardedAdd')
cb,cbr=parse(P+'r19CostControlAdd___boxed');gb,gbr=parse(P+'r19CostGuardedAdd___boxed')
norm=lambda ins:[(x['address'],x['op'],re.sub(r'r19Cost(?:Control|Guarded)Add','<ADD>',x['args']))for x in ins]
assert norm(cb)==norm(gb)
assert [(x['address'],x['kind'],re.sub(r'r19Cost(?:Control|Guarded)Add','<ADD>',x['target']))for x in cbr]==[(x['address'],x['kind'],re.sub(r'r19Cost(?:Control|Guarded)Add','<ADD>',x['target']))for x in gbr]
def select(ins,ranges):return [x for x in ins if any(a<=x['address']<=b for a,b in ranges)]
prefix=[(0,0x25),(0x54,0x75),(0x10a,0x141)]
shared=[(0x17b,0x188),(0x33c,0x348),(0x36f,0x38d),(0x437,0x445)]
success={}
for gap in('le31','ge32'):
 for sign in('same','opposite_nonzero'):
  ranges=prefix+shared+([(0x143,0x178)]if gap=='le31'else[])+([(0x18e,0x191)]if sign=='same'else[(0x333,0x336)])
  ins=select(guard,ranges);calls=[x for x in ins if x['op']=='call'];stack=[x for x in ins if '[rsp' in x['args']]
  assert len(calls)==1 and calls[0]['address']==0x381 and not stack
  assert any(x['address']==0x382 and 'lean_float32_to_bits' in x['target']for x in gr)
  success[gap+'_'+sign]=dict(instruction_count=len(ins),ranges=[[hex(a),hex(b)]for a,b in ranges],call_sites=[hex(x['address'])for x in calls],rsp_memory_sites=0)
normal_control=select(control,[(0,0x29),(0x37,0x7d),(0x94,0xd4)])
assert not any(x['op']=='call'or '[rsp' in x['args']for x in normal_control)
assert any(x['address']==0xd5 and 'lean_float32_to_bits'in x['target']for x in cr)
closure=json.loads((D/'caller-closure-check.json').read_text());assert all(v['static_arity2_zero_captures']for v in closure.values())
c=(D/'actual-new-main.c').read_text();main=(H/'_lean_main.c.txt').read_text()
assert main.count('lp_competition_Bench_Suite_run(')==1
for name in('closed__1','closed__2','closed__3','closed__10','closed__11'):assert 'main___'+name in main
assert 'lean_alloc_closure'not in main and 'diagnosticEntry'not in c and 'R19GRS32Add_guardedAdd('not in c
assert re.search(r'main___closed__4_value[^\n]*\.m_data = "control"',c)
assert re.search(r'main___closed__6_value[^\n]*\.m_data = "guarded"',c)
assert re.search(r'main___closed__5_value[^\n]*main___closed__4_value',c)
assert re.search(r'main___closed__7_value[^\n]*main___closed__6_value',c)
assert c.count('.m_fun = (void*)lp_competition_r19CostControlAdd___boxed, .m_arity = 2, .m_num_fixed = 0')==1
assert c.count('.m_fun = (void*)lp_competition_r19CostGuardedAdd___boxed, .m_arity = 2, .m_num_fixed = 0')==1
cc=(H/(P+'r19CostControlAdd.c.txt')).read_text();gc=(H/(P+'r19CostGuardedAdd.c.txt')).read_text()
counts={}
for name,s in(('control',cc),('guarded',gc)):
 counts[name]={n:len(re.findall(r'\b'+n+r'\(',s))for n in('lean_float32_of_bits','lean_float32_to_bits','lean_uint32_to_float32','lean_alloc_ctor','lean_alloc_closure','lean_apply_2')}
 assert counts[name]['lean_alloc_ctor']==counts[name]['lean_alloc_closure']==counts[name]['lean_apply_2']==0
sizes={}
for line in(D/'own-object-0-nm.txt').read_text().splitlines():
 m=re.fullmatch(r'[0-9a-f]+ ([0-9a-f]+) \w (\S+)',line)
 if m and m[2]in(P+'r19CostControlAdd',P+'r19CostGuardedAdd',P+'r19CostControlAdd___boxed',P+'r19CostGuardedAdd___boxed'):sizes[m[2]]=int(m[1],16)
def command(p):
 x=json.loads(p.read_text());assert x['synthetic']is False
 rows=[r['message'][3:]for r in x['log']if r['message'].startswith('.> ')];assert len(rows)==1;return shlex.split(rows[0])
def norm_flags(argv):
 return [re.sub(r'(?<=/)(?:MainFull|R19AddCostMain)(?=\.)','<MAIN>',re.sub(r'(?<=/)(?:benchFull|r19AddCost)(?=\.|$)','<BIN>',v))for v in argv]
flags={}
for kind in('compile','link','link_response'):
 a,b=[D/(role+'-'+kind+'.raw')for role in('original','new')]
 av,bv=(shlex.split(a.read_text()),shlex.split(b.read_text()))if kind=='link_response'else(command(a),command(b))
 assert norm_flags(av)==norm_flags(bv);flags[kind]=dict(argument_count=len(av),equal_after_root_target_paths_only=True,original_sha256=sha(a),new_sha256=sha(b))
prepare=json.loads((D/'prepare.json').read_text());result=json.loads((D/'result.json').read_text())
assert result['official_originals_unchanged']is True and result['new_target_is_original_gate_admissible']is False
assert result['execution_config']['build_memory_mb']==4096 and result['execution_config']['benchmark_memory_mb']==512
save('codegen.json',dict(
 actual_entry=dict(control='closed__11 -> r19CostControlAdd___boxed -> typed r19CostControlAdd',guarded='closed__10 -> r19CostGuardedAdd___boxed -> typed r19CostGuardedAdd',arity=2,captures=0,Suite_calls=1,shared_MUL_SUM_BMM='closed__1/closed__2/closed__3 in common join'),
 boxed_wrappers_identical_after_only_call_target_rename=True,typed_sizes=sizes,typed_static_instruction_count=dict(control=len(control),guarded=len(guard)),
 guarded_normal_nonzero_success=success,control_R2_numeric_ordinary_nonNaN=dict(instruction_count=len(normal_control),call_sites=0,tail_jump_to_codec='0xd4 -> lean_float32_to_bits',rsp_memory_sites=0),
 prologue=dict(control=dict(callee_save_registers=['rbp','r14','rbx'],local_alignment_bytes=16,total_below_entry_rsp_bytes=40),guarded=dict(callee_save_registers=['rbp','r15','r14','r13','r12','rbx'],local_alignment_bytes=8,total_below_entry_rsp_bytes=56)),
 success_mechanism='D3 input normal guards, magnitude cmov ordering, <=31 variable-shift/sticky arm or >=32 sticky1, sign add/sub and zero branch, pre-guard25..253, cvtsi2ss, one non-tail codec call, integer bias and return. No temporary [rsp] memory on nonzero accepted path.',
 fallback_mechanism='Failed input-normal guard or failed pre-guard uses inlined original B2 native ADD/cold software fallback; retains scaleTable numeric conversions/ofBits calls and conditional xmm spill/reload. C has three fallback softwareAdd sites, LLVM shares some bodies; not three calls per input.',
 allocation='No explicit ctor/closure/apply in either typed ADD. Success has no heap allocation. Boxed return is immediate lea tag, common generic input RC slow branches identical. Cold software helper may allocate internally; not measured.',
 C_static_sites=counts,flags=flags,identities=result['build_identities'],original_build_before=prepare['original_build_before'],
 evidence_limits='C/ASM are saved bytes from measured new object; raw ELF not exported. Identity unchanged is remote recorded assertion. Static path instruction counts are not cycle costs or observed path weights; eligible fractions UNKNOWN.'))
print(json.dumps(dict(sizes=sizes,success_paths=success,control_normal_instructions=len(normal_control),C_static_sites=counts,flags=flags),indent=2))
