"""Read completed statement C/ASM only; never inspect40407333869 or future inputs."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,time

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
C=ROOT/'competitions/floatlib/candidates'
RUN=C/'f01-mul-log2-proof1/ci-runs/40404258098'
SHA='f84ea2dbffbf0406f453bbc20b4335288ba5d77bb787ae33db203665016ac384'
JAM='b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff'
P='lp_competition_';start=time.monotonic();sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
ixp=RUN/'original-artifact-hashes.json';ix=json.loads(ixp.read_text());DOWN=RUN/ix['directory']
original=[]
for name,row in ix['files'].items():
    p=DOWN/name
    assert p.resolve().is_relative_to(DOWN.resolve())
    assert p.stat().st_size==row['bytes'] and sha(p)==row['sha256'],name
    original.append(dict(path=name,sha256=sha(p),bytes=p.stat().st_size))
assert set(ix['files'])=={p.relative_to(DOWN).as_posix()for p in DOWN.rglob('*')if p.is_file()}
SUITE=DOWN/'diagnostics/f01-d7-public-suite/public-suite'
out=HERE/'codegen-40404258098-excerpts';out.mkdir(exist_ok=True)

def c_functions(path):
    lines=path.read_text().splitlines(keepends=True);result={}
    for i,line in enumerate(lines):
        m=re.match(r'(?:LEAN_EXPORT |static )?[^;\n]*\b([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\{\s*$',line)
        if not m:continue
        depth=0
        for j in range(i,len(lines)):
            depth+=lines[j].count('{')-lines[j].count('}')
            if depth==0:break
        result[m[1]]=(i+1,j+1,''.join(lines[i:j+1]))
    return result
def normalize(body,self_symbol):
    body=body.replace(self_symbol,'SELF');names={}
    def repl(m):
        if m[0]not in names:names[m[0]]=f'v{len(names)}'
        return names[m[0]]
    return re.sub(r'\s+',' ',re.sub(r'\bv_[A-Za-z0-9_]+\b',repl,body)).strip()
def normalize_typed_executable(body,self_symbol):
    # Ignore local declaration placement, retain canonical variable C types.
    typ=r'(lean_object\*|uint8_t|uint16_t|uint32_t|uint64_t|int32_t|int64_t|size_t|float|double|int)'
    types={m[2]:m[1]for m in re.finditer(typ+r'\s+(v_[A-Za-z0-9_]+)',body)}
    body=re.sub(typ+r'\s+v_[A-Za-z0-9_]+\s*;','',body.replace(self_symbol,'SELF'))
    names={}
    def repl(m):
        if m[0]not in names:names[m[0]]=f'v{len(names)}'
        return names[m[0]]
    result=re.sub(r'\s+',' ',re.sub(r'\bv_[A-Za-z0-9_]+\b',repl,body)).strip()
    c_types={name:types.get(original,'label')for original,name in names.items()}
    return result,c_types
def digest(name,entry,label):
    lo,hi,body=entry;p=out/(label+'.c.txt');p.write_text(body)
    calls={x:len(re.findall(r'\b'+re.escape(x)+r'\(',body))for x in (
        'lean_float32_of_bits','lean_uint32_to_float32','lean_float32_mul','lean_float32_add',
        'lean_array_uget_borrowed','lean_array_fget_borrowed','lean_array_get_size','lean_alloc_ctor',
        'lean_alloc_closure','lean_dec','lean_inc','lean_dec_ref','lean_apply_2')}
    return dict(symbol=name,line_start=lo,line_end=hi,body_sha256=hashlib.sha256(body.encode()).hexdigest(),
                excerpt=p.relative_to(ROOT).as_posix(),static_sites=calls,
                competition_calls=sorted(set(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\(',body)[1:])))
def bind_candidate(name,expected):
    d=SUITE/'diagnostics'/name
    kernel=SUITE/'inputs'/name/'Kernel.lean';assert sha(kernel)==expected
    ci=json.loads((d/'candidate-c-index.json').read_text());ai=json.loads((d/'native-assembly-index.json').read_text())
    for r in ci:assert r['kernel_sha256']==expected and sha(d/r['file'])==r['sha256']
    for r in ai:
        assert sha(d/r['file'])==r['sha256']
        if 'kernel_sha256'in r:assert r['kernel_sha256']==expected
    return d,ci,ai
def asm(d,ai,symbol,label):
    row=next(r for r in ai if r.get('symbol')==symbol)
    text=(d/row['file']).read_text();m=re.search(r'^0+ <'+re.escape(symbol)+r'>:\s*$',text,re.M);assert m
    tail=text[m.start():];end=re.search(r'\n(?:Disassembly of section|0+[0-9a-f]* <)',tail)
    body=tail[:end.start()]if end else tail
    target=out/(label+'.asm.txt');target.write_text(body)
    ins=[]
    for line in body.splitlines():
        m=re.match(r'\s*([0-9a-f]+):\s+([a-z][a-z0-9]*)\s*(.*)',line)
        if m:ins.append(dict(offset=int(m[1],16),mnemonic=m[2],operands=m[3]))
    return row,body,ins,target

d,ci,ai=bind_candidate('f01-r19-dev-b2-index-inline1',SHA)
assert sha(HERE/'Kernel-index-inline-convert.draft.lean')==SHA
cp=d/'candidate-generated-0.c';mp=d/'candidate-generated-1.c';f=c_functions(cp)
selected=['Submission_bmm','Submission_R15PackedB2_dispatch','Submission_R15PackedB2_output',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__4',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__3___redArg',
          'Submission_R15PackedB2_Indexed_wordLoop___redArg',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__2',
          'Submission_R15PackedB2_packB','Submission_R15PackedB2_packB___lam__0',
          'Submission_R15PackedB2_packB___lam__1','Submission_Packed10_finish']
rows=[digest(P+s,f[P+s],'inline-'+s)for s in selected]
word=f[P+'Submission_R15PackedB2_Indexed_wordLoop___redArg'][2]
assert word.count('lean_array_uget_borrowed(')==2
assert word.count('lean_float32_of_bits(')==word.count('lean_uint32_to_float32(')==1
assert word.count('lean_float32_mul(')==3 and word.count('lean_float32_add(')==2
assert word.count('lean_array_fget_borrowed(')==1 and 'lp_competition_R2W01b_scaleTable'in word
assert 'lp_competition_R2W01b_convert('not in word
assert 'lean_obj_once('not in word and 'lean_array_get_size('not in word
assert 'lean_alloc_closure('not in word and 'lean_apply_'not in word
assert word.count('lean_alloc_ctor(')==1 and 'lean_alloc_ctor(0, 0, 8)'in word
fast=f[P+'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__3___redArg'][2]
assert P+'Submission_R15PackedB2_Indexed_wordLoop___redArg('in fast
assert P+'Submission_R15PackedB2_loop('not in fast
output=f[P+'Submission_R15PackedB2_output'][2]
assert output.count(P+'Submission_R15PackedB2_packB(')==1 and output.count('lean_array_get_size(')==1
assert output.count('lean_nat_dec_lt(')==2
mainrefs=[dict(line=i+1,text=line)for i,line in enumerate(mp.read_text().splitlines())
          if 'main___closed__4'in line or 'Bench_runFull('in line or 'Bench_Suite_run('in line]
assert any('.m_fun = (void*)lp_competition_Submission_bmm'in r['text']for r in mainrefs)
assert sha(mp)=='94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb'
assert P+'Submission_R15PackedB2_dispatch('in f[P+'Submission_bmm'][2]
assert P+'Submission_R15PackedB2_output('in f[P+'Submission_R15PackedB2_dispatch'][2]
assert P+'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__3___redArg('in f[P+'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__4'][2]

old_report=json.loads((HERE/'codegen-40392789163.json').read_text())
old_run=C/'f01-mul-log2-proof1/ci-runs/40392789163';old_ix=json.loads((old_run/'original-artifact-hashes.json').read_text())
old_down=old_run/old_ix['directory']
old_d=old_down/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-b2-index1'
for name,row in old_ix['files'].items():assert sha(old_down/name)==row['sha256']and(old_down/name).stat().st_size==row['bytes']
old_f=c_functions(old_d/'candidate-generated-0.c')
unchanged=[]
for s in selected:
    if s=='Submission_R15PackedB2_Indexed_wordLoop___redArg':continue
    a,b=f[P+s][2],old_f[P+s][2]
    eq=normalize(a,P+s)==normalize(b,P+s)
    assert eq,s
    unchanged.append(dict(symbol=P+s,alpha_equal=True))
ar,abody,ins,ap=asm(d,ai,P+'Submission_R15PackedB2_Indexed_wordLoop___redArg','inline-selected-wordLoop')
old_ai=json.loads((old_d/'native-assembly-index.json').read_text())
_,_,old_ins,old_ap=asm(old_d,old_ai,P+'Submission_R15PackedB2_Indexed_wordLoop___redArg','index9f7-selected-wordLoop')
byoff={r['offset']:r for r in ins}
gate=[r for r in ins if 0x86<=r['offset']<=0xb2]
eligible=[r for r in ins if 0x40<=r['offset']<=0x84]
cold=[r for r in ins if 0xb4<=r['offset']<=0xc1]
assert len(gate)==13 and len(eligible)==17
assert not any(r['mnemonic']=='call'or'rsp'in r['operands']for r in gate+eligible)
assert sum(r['mnemonic']=='call'for r in cold)==1
assert sum('rsp'in r['operands']for r in cold)==2
assert byoff[0xb2]['mnemonic']=='jne'and'40 <'in byoff[0xb2]['operands']
assert byoff[0xc1]['mnemonic']=='jmp'and'6a <'in byoff[0xc1]['operands']
old_hot=[r for r in old_ins if 0x30<=r['offset']<=0x6d]
assert len(old_hot)==16 and sum(r['mnemonic']=='call'for r in old_hot)==1
old_stack=[r for r in old_hot if'rsp'in r['operands']]
assert len(old_stack)==6
audit=json.loads((d/'helper-audit.json').read_text());assert audit['accepted']and audit['expected_count']==15
v=json.loads((d/'diagnostic-only-verdict.json').read_text());assert v['passed']and not v['rounds']
log=(d/'replay.log').read_text()
assert '[statement] ok'in log and 'Submission replays cleanly'in log and 'VerifyFull replays cleanly'in log
trace_row=next(r for r in ai if r.get('kind')=='trace'and r['source'].endswith('Submission.c.o.export.trace'))
trace=json.loads((d/trace_row['file']).read_text());build_command=trace['log'][0]['message']
assert '-O3'in build_command and '-ffp-contract=off'in build_command

# Optional engineering-only identity check of Jam17's actual public MainFull caller.
jd,jci,jai=bind_candidate('f01-r19-dev-jam17-public1',JAM)
jcp=jd/'candidate-generated-0.c';jmp=jd/'candidate-generated-1.c'
jf=c_functions(jcp);jmf=c_functions(jmp)
jname=P+'Submission_mul';diagnostic=P+'R19Base_R19Jam17_diagnosticEntry';selected_name=P+'main___lam__3'
public=jf[jname];diag=jf[diagnostic];selected_jam=jmf[selected_name]
jcomp=[]
for name,entry in ((jname,public),(diagnostic,diag)):
    left,right=normalize(selected_jam[2],selected_name),normalize(entry[2],name)
    equal=left==right
    mismatch=next((i for i,(a,b)in enumerate(zip(left,right))if a!=b),min(len(left),len(right)))
    executable_left,left_types=normalize_typed_executable(selected_jam[2],selected_name)
    executable_right,right_types=normalize_typed_executable(entry[2],name)
    executable_equal=executable_left==executable_right and left_types==right_types
    em=next((i for i,(a,b)in enumerate(zip(executable_left,executable_right))if a!=b),min(len(executable_left),len(executable_right)))
    jcomp.append(dict(left=selected_name,right=name,alpha_equal=equal,
                      first_difference_offset=mismatch if not equal else None,
                      left_context=left[max(0,mismatch-90):mismatch+180]if not equal else '',
                      right_context=right[max(0,mismatch-90):mismatch+180]if not equal else '',
                      typed_executable_equal=executable_equal,canonical_C_types_equal=left_types==right_types,
                      executable_first_difference=em if not executable_equal else None,
                      executable_left_context=executable_left[max(0,em-70):em+160]if not executable_equal else '',
                      executable_right_context=executable_right[max(0,em-70):em+160]if not executable_equal else '',
                      typed_normalization='Ignore local declaration placement; preserve canonical variable C types, constants, callees, operators and statement order'))
normal_core_name=P+'R19Base_R19Jam17_normalCore'
normal_core=jf[normal_core_name]
core_calls=re.findall(r'\b(lean_[A-Za-z0-9_]+)\(',normal_core[2])
main_call_matches=list(re.finditer(r'\b(lean_[A-Za-z0-9_]+)\(',selected_jam[2]))
main_calls=[m[1]for m in main_call_matches]
core_locations=[i for i in range(len(main_calls)-len(core_calls)+1)if main_calls[i:i+len(core_calls)]==core_calls]
core_fingerprints=[]
for i in core_locations:
    lo_pos=main_call_matches[i].start();hi_pos=main_call_matches[i+len(core_calls)-1].end()
    lo_line=selected_jam[0]+selected_jam[2][:lo_pos].count('\n')
    hi_line=selected_jam[0]+selected_jam[2][:hi_pos].count('\n')
    excerpt=selected_jam[2][max(0,lo_pos-150):hi_pos+200]
    core_fingerprints.append(dict(line_start=lo_line,line_end=hi_line,ordered_runtime_calls=core_calls,
                                  includes_shift17='17ULL'in excerpt,includes_mask131071='131071ULL'in excerpt))
core_verified=len(core_fingerprints)==1 and core_fingerprints[0]['includes_shift17']and core_fingerprints[0]['includes_mask131071']
assert core_verified
legacy_name=P+'main___lam__1';legacy=jmf[legacy_name]
legacy_matches=list(re.finditer(r'\b(lean_[A-Za-z0-9_]+)\(',legacy[2]));legacy_calls=[m[1]for m in legacy_matches]
legacy_locations=[i for i in range(len(legacy_calls)-len(core_calls)+1)if legacy_calls[i:i+len(core_calls)]==core_calls]
legacy_core=[]
for i in legacy_locations:
    lo_pos=legacy_matches[i].start();hi_pos=legacy_matches[i+len(core_calls)-1].end()
    legacy_core.append(dict(line_start=legacy[0]+legacy[2][:lo_pos].count('\n'),
                            line_end=legacy[0]+legacy[2][:hi_pos].count('\n')))
assert len(legacy_core)==1
jam_rows=[digest(jname,public,'jam17-public-mul'),digest(diagnostic,diag,'jam17-diagnosticEntry'),
          digest(normal_core_name,normal_core,'jam17-normalCore'),
          digest(selected_name,selected_jam,'jam17-selected-main-mul'),
          digest(P+'main___lam__3___boxed',jmf[P+'main___lam__3___boxed'],'jam17-selected-main-mul-boxed')]
jrefs=[dict(line=i+1,text=line)for i,line in enumerate(jmp.read_text().splitlines())
       if 'main___closed__2'in line or 'main___closed__5'in line or 'Bench_Suite_run('in line or 'Bench_runFull('in line]
assert any('.m_fun = (void*)lp_competition_main___lam__3___boxed'in r['text']for r in jrefs)
assert P+'main___lam__3('in jmf[P+'main___lam__3___boxed'][2]
main_body=jmf['_lean_main'][2];benchmark_bindings=[]
for closed,bench in [('main___closed__5','Bench_Suite_run'),('main___closed__2','Bench_runFull')]:
    descriptor=P+closed
    match=re.search(r'(v_[A-Za-z0-9_]+) = \(\(lean_object\*\)\('+re.escape(descriptor)+r'\)\);',main_body)
    assert match,descriptor
    call=re.search(re.escape(P+bench)+r'\(([^;]*)\);',main_body)
    assert call and call[1].split(',')[1].strip()==match[1]
    benchmark_bindings.append(dict(descriptor=descriptor,local=match[1],benchmark=P+bench,argument_1based=2))
source=(SUITE/'inputs/f01-r19-dev-jam17-public1/Kernel.lean').read_text()
assert '@[inline] def mul (x y : Binary32) : Binary32 := R19Base.R19Jam17.guardedMul R19Base.mul x y'in source
jam_inline=all(r['typed_executable_equal']for r in jcomp)
jam=dict(kernel_sha256=JAM,c_index=jci,mainfull_references=jrefs,functions=jam_rows,
         selected_vs_public_and_diagnostic=jcomp,
         exact_normalCore_call_sequence_matches=core_fingerprints,
         selected_expected_fast_core_present=core_verified,legacy_Bench_runFull_core=legacy_core,
         benchmark_parameter_bindings=benchmark_bindings,
         conclusion='Expected Jam17 normalCore is inlined in actual selected MainFull lambda; no named Jam17 call boundary. Whole-function alpha identity is not established; first differences are local/phi ordering.',
         source_wrapper='Submission.mul := R19Base.R19Jam17.guardedMul R19Base.mul',
         direct_named_Jam17_calls=bool(re.search(r'\blp_competition_R19Base_R19Jam17_[A-Za-z0-9_]+\(',selected_jam[2])),
         scope='Engineering identity only; no mathematical investigation or speed claim')

record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='ELIGIBLE_B2_PATH_CALL_AND_SPILL_REMOVED_DIAGNOSTIC_ONLY',
            run=40404258098,source_commit=ix['artifact']['workflow_run']['head_sha'],kernel_sha256=SHA,
            original_index_sha256=sha(ixp),original_files_verified=len(original),
            original_bytes_verified=sum(r['bytes']for r in original),original_files=original,
            prior_run=40392789163,prior_original_files_reverified=len(old_ix['files']),
            c_index=ci,MainFull_unchanged_sha256=sha(mp),MainFull_refs=mainrefs,
            selected_C_functions=rows,unchanged_vs_9f7=unchanged,
            diagnostic_build_command=build_command,
            selected_ASM=dict(index_entry=ar,excerpt=ap.relative_to(ROOT).as_posix(),gate=gate,
                              eligible_body=eligible,cold_body=cold,
                              gate_instructions=len(gate),eligible_body_instructions=len(eligible),
                              eligible_loop_path_instructions=len(gate)+len(eligible),
                              eligible_calls=0,eligible_stack_accesses=0,cold_calls=1,cold_vector_stack_accesses=2,
                              frame_sub='0x10',saved_GPRs=5,
                              remaining_call_target='UNKNOWN_SYMBOL_LABEL: same one of_bits C arm; no relocation names in disassembly'),
            prior_selected_ASM=dict(excerpt=old_ap.relative_to(ROOT).as_posix(),hot_instructions=len(old_hot),
                                    hot_calls=1,hot_vector_stack_accesses=len(old_stack),frame_sub='0x28',saved_GPRs=4),
            costs_added=['Qualification logic within a13-instruction raw-A-load/gate block, which also includes original raw load/unbox work',
                         'mantissa mask/or, integer-to-Float32 cast, shared-table pointer+entry loads',
                         'one exact scalar Float32 scaling multiplication before original two-lane MAC',
                         'one additional saved GPR in prologue; qualified path retains accumulators in xmm2'],
            costs_preserved=['off-domain of_bits call','one off-domain accumulator-vector store/reload',
                             'original B packing, outer address arithmetic, output/finish/replay'],
            verification=dict(statement='PASS',module_replay='PASS',helper_roots=15,helper_axioms='PASS_STANDARD3',
                              complete_timing='NOT_READ_NOT_ESTABLISHED'),
            Jam17=jam,
            limits=['These are statement/bench-build C and diagnostic object ASM, not40407333869 timed objects/ELF',
                    'Object SHA is retained index metadata; object binary is unavailable for independent hashing',
                    'Instruction counts include a removed call but exclude its callee work; they are not cycle ratios',
                    'No40407333869 input/performance/result or future confirmation was read',
                    'No new source, model, compiler, Git, push, CI or agent was run'],
            elapsed_seconds=time.monotonic()-start)
assert time.monotonic()-start<8
(HERE/'codegen-40404258098.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(state=record['state'],files=record['original_files_verified'],bytes=record['original_bytes_verified'],
                     selected_C=len(rows),eligible_calls=0,eligible_stack=0,old_stack=len(old_stack),
                     Jam17_expected_core=core_verified,Jam17_full_alpha_identity=jam_inline,
                     Jam17_legacy_core=legacy_core,seconds=record['elapsed_seconds']),indent=2))
