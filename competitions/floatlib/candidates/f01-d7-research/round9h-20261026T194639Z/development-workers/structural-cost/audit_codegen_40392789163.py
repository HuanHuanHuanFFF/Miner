"""Authenticate and inspect completed R19 diagnostic C/ASM. No compile, Git, or CI."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import time
import difflib

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40392789163'
EXPECTED='9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1'
COMMIT='454d9d23d836b211d99fefad27ef9d4845defdb2'
start=time.monotonic()
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
ixp=RUN/'original-artifact-hashes.json'
index=json.loads(ixp.read_text())
assert index['artifact']['workflow_run']['head_sha']==COMMIT
DOWN=RUN/index['directory']
checked=[]
for name,row in index['files'].items():
    p=DOWN/name
    assert p.resolve().is_relative_to(DOWN.resolve())
    assert p.is_file() and p.stat().st_size==row['bytes'] and sha(p)==row['sha256'],name
    checked.append(dict(path=name,sha256=sha(p),bytes=p.stat().st_size))
assert set(index['files'])=={p.relative_to(DOWN).as_posix() for p in DOWN.rglob('*') if p.is_file()}
SUITE=DOWN/'diagnostics/f01-d7-public-suite/public-suite'
DIAG=SUITE/'diagnostics/f01-r19-dev-b2-index1'
for p in (ROOT/'competitions/floatlib/candidates/f01-r19-dev-b2-index1/Kernel.lean',
          HERE/'Kernel-hoisted-b2.draft.lean',SUITE/'inputs/f01-r19-dev-b2-index1/Kernel.lean'):
    assert sha(p)==EXPECTED
ci=json.loads((DIAG/'candidate-c-index.json').read_text())
ai=json.loads((DIAG/'native-assembly-index.json').read_text())
for r in ci:
    assert r['kernel_sha256']==EXPECTED and sha(DIAG/r['file'])==r['sha256']
for r in ai:
    assert sha(DIAG/r['file'])==r['sha256']
    if 'kernel_sha256' in r:assert r['kernel_sha256']==EXPECTED

def parse_c(path):
    text=path.read_text(); lines=text.splitlines(keepends=True); result={}
    # C emitted by the pinned Lean compiler: function braces are balanced by line.
    for i,line in enumerate(lines):
        m=re.match(r'(?:LEAN_EXPORT |static )?[^;\n]*\b([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\{\s*$',line)
        if not m:continue
        depth=0
        for j in range(i,len(lines)):
            depth+=lines[j].count('{')-lines[j].count('}')
            if depth==0:break
        result[m.group(1)]=(i+1,j+1,''.join(lines[i:j+1]))
    return result

cp=DIAG/'candidate-generated-0.c'; mp=DIAG/'candidate-generated-1.c'
f=parse_c(cp)
P='lp_competition_'
selected=['Submission_bmm','Submission_R15PackedB2_dispatch','Submission_R15PackedB2_output',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__4',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__3___redArg',
          'Submission_R15PackedB2_Indexed_wordLoop___redArg',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__2',
          'Submission_R15PackedB2_packB','Submission_R15PackedB2_packB___lam__0',
          'Submission_R15PackedB2_packB___lam__0___boxed','Submission_R15PackedB2_packB___lam__1',
          'Submission_R15PackedB2_packB___lam__1___boxed','Submission_R15PackedB2_tileIndex___redArg',
          'Submission_Packed10_finish','Submission_R15PackedB2_loop',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__1',
          'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__0___redArg',
          'Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0']
tokens=['lean_nat_add','lean_nat_mul','lean_nat_div','lean_nat_mod','lean_nat_dec_lt',
        'lean_array_get_size','lean_array_fget_borrowed','lean_array_uget_borrowed',
        'lean_float32_of_bits','lean_alloc_ctor','lean_alloc_closure','lean_inc','lean_inc_ref',
        'lean_dec','lean_dec_ref','lean_usize_of_nat','lean_usize_add','lean_usize_dec_lt',
        'lean_ctor_get_float32','lean_float32_mul','lean_float32_add','lean_box_float32',
        'lean_unbox_float32','lean_array_push','lean_mk_empty_array_with_capacity','lean_obj_once']
out=HERE/'codegen-40392789163-excerpts';out.mkdir(exist_ok=True)
functions=[]
for s in selected:
    lo,hi,body=f[P+s]
    target=out/(s+'.c.txt');target.write_text(body)
    functions.append(dict(symbol=P+s,line_start=lo,line_end=hi,body_sha256=hashlib.sha256(body.encode()).hexdigest(),
                          excerpt=target.relative_to(ROOT).as_posix(),
                          static_sites={t:body.count(t+'(') for t in tokens},
                          competition_calls=sorted(set(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\(',body)[1:]))))
word=f[P+'Submission_R15PackedB2_Indexed_wordLoop___redArg'][2]
hot=word.split('else\n{',1)[1]
assert hot.count('lean_array_uget_borrowed(')==2
assert hot.count('lean_float32_of_bits(')==1
assert hot.count('lean_ctor_get_float32(')==2
assert hot.count('lean_float32_mul(')==hot.count('lean_float32_add(')==2
for bad in ('lean_nat_','lean_array_get_size','lean_alloc_','lean_inc','lean_dec','lean_apply_',P):
    assert bad not in hot,bad
assert 'lean_alloc_ctor(0, 0, 8)'in word
assert word.count('lean_alloc_ctor(')==1
fastrow=f[P+'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__4'][2]
fastgroup=f[P+'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__3___redArg'][2]
output=f[P+'Submission_R15PackedB2_output'][2]
assert P+'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__3___redArg('in fastrow
assert fastgroup.count(P+'Submission_R15PackedB2_Indexed_wordLoop___redArg(')==1
assert P+'Submission_R15PackedB2_loop(' not in fastgroup
assert 'lean_array_get_size('not in fastrow+fastgroup
assert 'Packed10Index_runDot___closed__0'not in fastrow+fastgroup+word
assert 'lean_alloc_'not in fastrow+fastgroup
assert 'lean_apply_'not in fastrow+fastgroup
assert output.count(P+'Submission_R15PackedB2_packB(')==1
assert output.count('lean_array_get_size(')==1
assert output.count('lean_nat_dec_lt(')==2
assert output.index('Submission_R15PackedB2_packB(')<output.index('lean_nat_dec_lt(')<output.index('output_spec__4(')
assert output.count('lean_mk_empty_array_with_capacity(')==2 # Mutually exclusive fast / fallback arms.

main=mp.read_text().splitlines()
mainrefs=[dict(line=i+1,text=line) for i,line in enumerate(main)
          if 'main___closed__4'in line or 'Submission_bmm'in line or 'Bench_runFull('in line or 'Bench_Suite_run('in line]
assert any('.m_fun = (void*)lp_competition_Submission_bmm'in r['text'] for r in mainrefs)
assert sha(mp)=='94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb'
assert P+'Submission_R15PackedB2_dispatch('in f[P+'Submission_bmm'][2]
assert P+'Submission_R15PackedB2_output('in f[P+'Submission_R15PackedB2_dispatch'][2]

old_audit=json.loads((HERE/'source-cost-audit.json').read_text())
old_c=next(ROOT/r['path'] for r in old_audit['read_only_source_bindings'] if r['path'].endswith('candidate-generated-0.c'))
old_main=next(ROOT/r['path'] for r in old_audit['read_only_source_bindings'] if r['path'].endswith('candidate-generated-1.c'))
for p in (old_c,old_main):
    row=next(r for r in old_audit['read_only_source_bindings'] if ROOT/r['path']==p)
    assert sha(p)==row['sha256']
old=parse_c(old_c)
def normalize(body,self_symbol):
    body=body.replace(self_symbol,'SELF')
    names={}
    def replace(m):
        if m[0] not in names:names[m[0]]=f'v{len(names)}'
        return names[m[0]]
    return re.sub(r'\s+',' ',re.sub(r'\bv_[A-Za-z0-9_]+\b',replace,body)).strip()
compare=[]
for new_s,old_s in [(s,s) for s in ('Submission_bmm','Submission_R15PackedB2_dispatch',
                      'Submission_R15PackedB2_packB','Submission_R15PackedB2_packB___lam__0',
                      'Submission_R15PackedB2_packB___lam__0___boxed','Submission_R15PackedB2_packB___lam__1',
                      'Submission_R15PackedB2_packB___lam__1___boxed','Submission_R15PackedB2_tileIndex___redArg',
                      'Submission_Packed10_finish','Submission_R15PackedB2_loop')]+[
             ('Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__2',
              'Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0')]:
    a,b=f[P+new_s][2],old[P+old_s][2]
    eq=normalize(a,P+new_s)==normalize(b,P+old_s)
    emitter=new_s=='Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__2'
    assert eq or emitter,(new_s,old_s)
    if emitter:
        assert all(a.count(t+'(')==b.count(t+'(')for t in tokens)
        diff=''.join(difflib.unified_diff(b.splitlines(keepends=True),a.splitlines(keepends=True),
                                         fromfile='old-emitter',tofile='new-fast-emitter'))
        (out/'emitter-raw.diff.txt').write_text(diff)
    compare.append(dict(new=P+new_s,old=P+old_s,alpha_equal=eq,
                        normalization='self symbol, first-occurrence C locals, whitespace only; callees/constants/operators unchanged',
                        note='Same relevant call-site counts; the zero constant is materialized after the column address add rather than before. This is not alpha equality.' if emitter and not eq else ''))

def asm_body(path,symbol):
    text=path.read_text()
    m=re.search(r'^0+ <'+re.escape(symbol)+r'>:\s*$',text,re.M)
    assert m
    tail=text[m.start():]
    end=re.search(r'\n(?:Disassembly of section|0+[0-9a-f]* <)',tail)
    return tail[:end.start()] if end else tail
asm_rows=[]
for file,symbol in [('native-loop-3.asm.txt',P+'Submission_R15PackedB2_Indexed_wordLoop___redArg'),
                    ('native-loop-4.asm.txt',P+'Submission_R15PackedB2_loop')]:
    body=asm_body(DIAG/file,symbol)
    p=out/(symbol.removeprefix(P)+'.asm.txt');p.write_text(body)
    instructions=[]
    for line in body.splitlines():
        m=re.match(r'\s*([0-9a-f]+):\s+([a-z][a-z0-9]*)\s*(.*)',line)
        if m:instructions.append(dict(offset=int(m[1],16),mnemonic=m[2],operands=m[3]))
    row=dict(file=file,symbol=symbol,excerpt=p.relative_to(ROOT).as_posix(),instructions=len(instructions),
             instruction_bytes_end=max(r['offset'] for r in instructions),
             total_call_sites=sum(r['mnemonic']=='call' for r in instructions),
             stack_frame_sub=[r['operands'] for r in instructions if r['mnemonic']=='sub' and r['operands'].startswith('rsp')])
    if 'Indexed' in symbol:
        loop=[r for r in instructions if 0x30<=r['offset']<=0x6d]
        assert len(loop)==16 and sum(r['mnemonic']=='call' for r in loop)==1
        assert any(r['mnemonic']=='mulps'for r in loop) and any(r['mnemonic']=='addps'for r in loop)
        assert not any(r['mnemonic'].startswith('vfm') for r in loop)
        row.update(hot_range='0x30..0x6d',hot_instructions=loop,
                   hot_call_sites=1,relocation_targets='UNKNOWN: objdump -d output has no relocation symbol labels',
                   note='Sole per-k C conversion call remains; two live vector values are stored across it. Diagnostic object only.')
    asm_rows.append(row)

raw=(DIAG/'helper-axioms.raw').read_text()
reports=re.findall(r"^'([^']+)' depends on axioms: \[([^\]]*)\]",raw,re.M)
assert len(reports)==15
allowed={'propext','Classical.choice','Quot.sound'}
for name,axioms in reports:
    assert set(a.strip()for a in axioms.split(',')if a.strip())<=allowed
assert 'Unknown constant `Submission.R15PackedB2.Indexed.runDot_eq`'in raw
log=(DIAG/'replay.log').read_text()
assert '[statement] ok'in log and 'Submission replays cleanly'in log and 'VerifyFull replays cleanly'in log
verdict=json.loads((DIAG/'diagnostic-only-verdict.json').read_text())
assert not verdict['passed'] and verdict['stage']=='helper-axioms' and not verdict['rounds']
trace=json.loads((DIAG/'build-trace-5.txt').read_text())
command=trace['log'][0]['message']
assert '-O3'in command and '-ffp-contract=off'in command and 'v4.34.0'in command

record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='SELECTED_FAST_C_PASS_RECOMMEND_COMPLETE_DISCOVERY_AFTER_METADATA_REPAIR',
            run=40392789163,source_commit=COMMIT,kernel_sha256=EXPECTED,
            original_artifact_index_sha256=sha(ixp),original_files_verified=len(checked),
            original_bytes_verified=sum(r['bytes']for r in checked),original_files=checked,
            c_index=ci,assembly_index=ai,functions=functions,mainfull_references=mainrefs,
            selected_route=['MainFull.main___closed__4 -> Submission_bmm','Submission_bmm -> R15PackedB2_dispatch after underflow miss',
                            'R15PackedB2_dispatch -> R15PackedB2_output for unchanged shape domain',
                            'output word-range fast arm -> output_spec__4 -> output_spec__3___redArg',
                            'group -> Indexed_wordLoop___redArg -> output_spec__2 -> Packed10_finish'],
            hot_C=dict(Nat=False,A_size_or_default=False,borrowed_uget=2,of_bits_calls=1,
                       B2_field_reads=2,ordered_mul_add_pairs=2,allocation=False,RC=False,indirect_apply=False,
                       new_competition_call=False,F2_terminal_payload_bytes=8),
            caller_C=dict(B_pack_once=True,range_guard_only_once_at_output=True,
                          output_guard_checks=2,A_size_reads_in_output=1,
                          new_A_preparation=False,new_tile_preparation=False,new_hot_closures=False,
                          new_per_group_usize_of_nat_sites=2,
                          remaining_group_Nat_addressing=True,unchanged_result_release=True,
                          guard_constant='Existing Packed10Index USize.size lazy constant, read once per output; startup cost included in future complete timing'),
            unchanged_C_comparisons=compare,MainFull_identical_to_old=sha(mp)==sha(old_main),
            diagnostic_assembly=asm_rows,build_command=command,
            correctness=dict(statement='PASS',Submission_replay='PASS',VerifyFull_replay='PASS',
                             helper_audit_overall='FAIL_NONEXISTENT_NAME',actual_roots_printed=15,
                             actual_root_axioms='ALL_SUBSET_OF_STANDARD3',
                             missing_name='Submission.R15PackedB2.Indexed.runDot_eq',full_gate='NOT_RUN',timing='NOT_RUN'),
            recommendation='YES: proceed to observer-free original complete D after correcting the nonexistent helper audit name; no source change or extra codegen run needed for this exact hash',
            limitations=['C/ASM are the successful statement/bench-build layer, not the future timed gate object or ELF',
                         'Diagnostic object hash is metadata-authenticated; object binary itself was not retained to independently recompute its SHA',
                         'Hot ASM still has one call and vector stack saves; no claim of conversion/spill elimination',
                         'No stage-time attribution, speed ratio, ten-percent whole gain, or adoption result follows from static C/ASM',
                         'Helper-audit metadata failure remains the raw diagnostic overall result; all original bytes preserved'],
            resources=dict(local_Lean_runs=0,local_compiles=0,CI_jobs=0,Git_mutations=0),
            elapsed_seconds=time.monotonic()-start)
assert time.monotonic()-start<5
(HERE/'codegen-40392789163.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(state=record['state'],files=record['original_files_verified'],bytes=record['original_bytes_verified'],
                     selected_C_functions=len(functions),unchanged_C_comparisons=len(compare),
                     helper_roots=len(reports),seconds=record['elapsed_seconds'],assembly=asm_rows),indent=2))
