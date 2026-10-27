"""Exact runtime-only direct-bias diagnostic C/ASM audit. No Lean/Git/CI."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,time

H=Path(__file__).resolve().parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
C=R/'competitions/floatlib/candidates';R19=C/'f01-d7-research/round9h-20261026T194639Z'
RUN=C/'f01-mul-log2-proof1/ci-runs/40420540388';S='74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
start=time.monotonic();sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest();P='lp_competition_'
ixp=RUN/'original-artifact-hashes.json';ix=json.loads(ixp.read_text());down=RUN/ix['directory'];checked=[]
assert ix['artifact']['workflow_run']['head_sha']=='ce3e26f9c6efaf3a7435570d46a13db93cf8c463'
for name,row in ix['files'].items():
    p=down/name;assert p.resolve().is_relative_to(down.resolve())
    assert p.stat().st_size==row['bytes']and sha(p)==row['sha256'],name
    checked.append(dict(path=name,sha256=sha(p),bytes=p.stat().st_size))
assert len(checked)==83 and set(ix['files'])=={p.relative_to(down).as_posix()for p in down.rglob('*')if p.is_file()}
suite=down/'diagnostics/f01-d7-public-suite/public-suite';d=suite/'diagnostics/f01-r19-dev-direct-bias-runtime1'
source=C/'f01-r19-dev-direct-bias-runtime1/Kernel.lean';ci_source=suite/'inputs/f01-r19-dev-direct-bias-runtime1/Kernel.lean'
producer=R19/'astra-direct-bias-runtime-only.lean';base=C/'f01-r15-dev-packed-b2-1/Kernel.lean'
for path in(source,ci_source,producer):assert sha(path)==S and path.stat().st_size==228187
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert source.read_bytes().startswith(base.read_bytes())
ci=json.loads((d/'candidate-c-index.json').read_text());ai=json.loads((d/'native-assembly-index.json').read_text())
for item in ci:assert item['kernel_sha256']==S and sha(d/item['file'])==item['sha256']
for item in ai:
    assert sha(d/item['file'])==item['sha256']
    if 'kernel_sha256'in item:assert item['kernel_sha256']==S
cp=d/'candidate-generated-0.c';mp=d/'candidate-generated-1.c'
assert sha(mp)=='94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb'
assert 'R19DirectBias'not in mp.read_text()

def parse_c(path):
    lines=path.read_text().splitlines(keepends=True);f={}
    for i,line in enumerate(lines):
        m=re.match(r'(?:LEAN_EXPORT |static )?[^;\n]*\b([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\{\s*$',line)
        if not m:continue
        depth=0
        for j in range(i,len(lines)):
            depth+=lines[j].count('{')-lines[j].count('}')
            if depth==0:break
        f[m[1]]=(i+1,j+1,''.join(lines[i:j+1]))
    return f
f=parse_c(cp);functions=[]
for name in ('normalCore','guardedMul','diagnosticEntry'):
    sym=P+'Submission_R19DirectBias_'+name;lo,hi,body=f[sym]
    target=H/(name+'.c.txt');target.write_bytes(body.encode())
    functions.append(dict(symbol=sym,line_start=lo,line_end=hi,sha256=hashlib.sha256(body.encode()).hexdigest(),
                          excerpt=target.relative_to(R).as_posix(),
                          runtime_sites={s:body.count(s+'(')for s in ('lean_uint64_mul','lean_uint64_shift_right','lean_float32_of_bits',
                              'lean_uint32_to_float32','lean_float32_to_uint32','lean_float32_to_bits','lean_alloc_ctor','lean_apply_2')}))
core=f[P+'Submission_R19DirectBias_normalCore'][2]
assert core.count('lean_uint64_mul(')==1 and not any(t in core for t in ('lean_float','to_float','scaleTable','lean_alloc_','lean_apply_'))

def parse_asm(path,symbol):
    text=path.read_text();m=re.search(r'^0+ <'+re.escape(symbol)+r'>:\s*$',text,re.M);assert m
    tail=text[m.start():];end=re.search(r'\n(?:Disassembly of section|0+[0-9a-f]* <)',tail)
    body=tail[:end.start()]if end else tail;ins=[]
    for line in body.splitlines():
        m=re.match(r'\s*([0-9a-f]+):\s+([a-z][a-z0-9]*)\s*(.*)',line)
        if m:ins.append(dict(address=int(m[1],16),hex=m[1],op=m[2],operands=m[3]))
    return body,ins
asm=[]
for name in ('normalCore','diagnosticEntry'):
    symbol=P+'Submission_R19DirectBias_'+name;item=next(r for r in ai if r.get('symbol')==symbol)
    body,ins=parse_asm(d/item['file'],symbol);(H/(name+'.asm.txt')).write_bytes(body.encode())
    asm.append(dict(name=name,index=item,instructions=ins,whole_symbol_call_sites=sum(i['op']=='call'for i in ins)))
entry=next(a for a in asm if a['name']=='diagnosticEntry');ins=entry['instructions'];by={i['address']:i for i in ins}
# Accepted normal/S128..380 branch: all taken targets are checked in actual object.
assert by[0x2d]['op']=='ja'and'74 <'in by[0x2d]['operands']
assert by[0x86]['op']=='ja'and'266 <'in by[0x86]['operands']
assert by[0x272]['op']=='ja'and'45b <'in by[0x272]['operands']
assert by[0x4bd]['op']=='jmp'and'b47 <'in by[0x4bd]['operands']
segments=[(0,0x2d),(0x74,0x86),(0x266,0x272),(0x45b,0x4bd),(0xb47,0xb53)]
path=[i for lo,hi in segments for i in ins if lo<=i['address']<=hi]
assert path[-1]['op']=='ret'and len(path)==58
fast=[i for i in path if 0x45b<=i['address']<=0x4bd]
interior=[i for i in path if i['op']not in ('push','pop','ret')and not(i['op']in('add','sub')and i['operands'].startswith('rsp'))]
assert sum(i['op']=='imul'for i in fast)==1
assert sum(i['op']=='bt'for i in fast)==sum(i['op']=='adc'for i in fast)==1
assert not any(i['op'].startswith(('j','cmov'))for i in fast[:-1])
assert not any(i['op']=='call'or'xmm'in i['operands']or'rsp'in i['operands']for i in interior)
assert by[0x48e]['op']=='bt'and by[0x491]['op']=='adc'
assert by[0x47c]['op']==by[0x497]['op']=='shr'and by[0x49e]['op']=='shr'and'cl'in by[0x49e]['operands']
normal=next(a for a in asm if a['name']=='normalCore')['instructions']
assert len(normal)==28 and normal[-1]['op']=='ret'and not any(i['op']in('push','pop','call')or'rsp'in i['operands']for i in normal)
all_cold=[i for i in ins if i['address']not in {j['address']for j in path}]
audit=json.loads((d/'helper-audit.json').read_text());assert audit['accepted']and audit['expected_count']==7
assert len(audit['reports'])==7 and all(set(v)<={'propext','Quot.sound','Classical.choice'}for v in audit['reports'].values())
v=json.loads((d/'diagnostic-only-verdict.json').read_text());assert v['passed']and not v['rounds']
log=(d/'replay.log').read_text();assert '[statement] ok'in log and'Submission replays cleanly'in log and'VerifyFull replays cleanly'in log

# Finite mechanism comparison only: actual b271 MainFull success path from prior audit.
frame_p=R19/'astra-workers/runtime-representation/jam-frame-frontier/frame-evidence.json'
frame=json.loads(frame_p.read_text());jam_path=frame['success_path'];jam_asm=R/frame['ASM_binding']['path']
assert sha(jam_asm)==frame['ASM_binding']['sha256']=='cf1dddbac80911f00da6f546cdba1b4549d701403b60a9b63557d0cd945c1388'
jam_diag=jam_asm.parent
jam_ci=json.loads((jam_diag/'candidate-c-index.json').read_text())
jam_ai=json.loads((jam_diag/'native-assembly-index.json').read_text())
for item in jam_ci:assert item['kernel_sha256']==frame['kernel_sha256']and sha(jam_diag/item['file'])==item['sha256']
jam_item=next(i for i in jam_ai if i.get('symbol')==P+'main___lam__3')
assert jam_item['sha256']==sha(jam_asm)and jam_item['object_sha256']==frame['object_sha256_recorded']
assert jam_item['kernel_sha256']==frame['kernel_sha256']
jbody,jins=parse_asm(jam_asm,P+'main___lam__3');jby={i['address']:i for i in jins}
assert len(jam_path)==62
for row in jam_path:
    actual=jby[row['address']];assert actual['op']==row['op']and actual['operands']==row['operands']
(H/'Jam17-selected-MainFull.asm.txt').write_bytes(jbody.encode())
request=dict(normal_path_instructions=58,normal_core_instructions_including_ret=28,
             normal_path_calls=0,normal_path_FP_instructions=0,normal_path_spill_refs=0,
             saved_registers=[i['operands']for i in path if i['op']=='push'],local_frame_bytes=16,
             literal_selection='Neither branch nor cmov: P>>47 builds bias and BT index; BT/ADC consumes parity',
             product_multiplies=1,postbias_carry='Second >>47 on biased product; one variable SHR by23+postbias_high',
             joint_guards='Three accepted unsigned conditional branches: u normal, v normal, sum128..380',
             no_FP_table_codec_foreigncall=True)
aliases={'rbp':['rbp','ebp','bp','bpl'],'r15':['r15','r15d','r15w','r15b'],
         'r14':['r14','r14d','r14w','r14b'],'r12':['r12','r12d','r12w','r12b'],'rbx':['rbx','ebx','bx','bl']}
live_uses={reg:[i for i in interior if any(re.search(r'\b'+a+r'\b',i['operands'])for a in names)]for reg,names in aliases.items()}
assert not live_uses['r14']
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='COST_PREMISE_REALIZED_BOUNDED_MATH_CONTINUATION_JUSTIFIED',
            run=40420540388,source_commit=ix['artifact']['workflow_run']['head_sha'],kernel_sha256=S,kernel_bytes=source.stat().st_size,
            original_index_sha256=sha(ixp),original_files_verified=len(checked),original_bytes_verified=sum(x['bytes']for x in checked),original_files=checked,
            exact_B2_prefix_unchanged=True,public_MainFull_sha256=sha(mp),public_MUL='UNCHANGED_B2_NOT_DIRECT_BIAS',
            c_index=ci,functions=functions,assembly=asm,accepted_segments=segments,accepted_path=path,cost=request,
            saved_register_success_uses=live_uses,
            cold_paths=dict(retained_in_full_C_and_ASM=True,instructions_outside_success=len(all_cold),
                            call_sites_outside_success=sum(i['op']=='call'for i in all_cold),
                            boundary='Old native/table/codec/software fallback remains; no hit-rate or miss-cost timing inferred'),
            Jam17_comparison=dict(source_sha256=frame['kernel_sha256'],run=40404258098,symbol=P+'main___lam__3',
                                  frame_evidence_sha256=sha(frame_p),actual_ASM_sha256=sha(jam_asm),
                                  C_index_sha256=sha(jam_diag/'candidate-c-index.json'),assembly_index_sha256=sha(jam_diag/'native-assembly-index.json'),
                                  success_path_reverified=62,saved_registers=[i['operands']for i in jam_path if i['op']=='push'],frame_bytes=16,
                                  FP_ops=[i for i in jam_path if'xmm'in i['operands']],
                                  limit='Different symbols, source wrappers and objects; static mechanism contrast only, never same-binary timing'),
            verification=dict(statement='PASS',Submission_replay='PASS',VerifyFull_replay='PASS',roots=7,root_audit='PASS_STANDARD3',
                              new_MUL_equivalence_proof='ABSENT_RUNTIME_ONLY',new_public_MUL='NOT_CONNECTED',speed='UNKNOWN'),
            decision='Continue one bounded mathematical closure attempt: actual accepted caller retains one P and has no FP/table/codec/foreigncall. Relative to Jam17, real deletion is FP roundtrip and its clamp work; Jam17 success already has no table/codec/foreigncall. Shared5-save/16B overhead remains; no large-gain or speed claim.',
            limits=['This successful path belongs to diagnosticEntry; future public caller can lower differently',
                    'Global CI failure does not negate the separately passing runtime-only item; no reason for other failure inferred',
                    'Object SHA is authenticated index metadata; raw object binary unavailable for independent rehash',
                    'No1180 proof repair, numeric testing, local Lean, compilation, CI, Git, or new agent'],
            elapsed_seconds=time.monotonic()-start)
assert time.monotonic()-start<6
(H/'audit.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps(dict(state=record['state'],originals=len(checked),accepted_instructions=len(path),core_instructions=len(normal),
                     cost=request,Jam17_path=len(jam_path),seconds=record['elapsed_seconds']),indent=2))
