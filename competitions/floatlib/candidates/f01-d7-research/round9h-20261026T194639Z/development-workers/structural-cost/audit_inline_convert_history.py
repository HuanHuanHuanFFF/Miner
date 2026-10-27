"""Old R15 mechanism/cost boundary and pre-D9f7 diagnostic feasibility only."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,time
from collections import deque

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
C=ROOT/'competitions/floatlib/candidates'
R15=C/'f01-d7-research/round3h-20261025T043928Z'
start=time.monotonic();sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
bindings=[]
def bind(p):
    r=dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(p),bytes=p.stat().st_size)
    bindings.append(r);return r
def verify_run(run):
    folder=C/f'f01-mul-log2-proof1/ci-runs/{run}'
    ixp=folder/'original-artifact-hashes.json';ix=json.loads(ixp.read_text())
    down=folder/ix['directory'];count=total=0
    for name,row in ix['files'].items():
        p=down/name
        assert p.resolve().is_relative_to(down.resolve())
        assert p.stat().st_size==row['bytes'] and sha(p)==row['sha256'],name
        count+=1;total+=row['bytes']
    return down,dict(run=run,index=bind(ixp),files_verified=count,bytes_verified=total)
def c_function(path,symbol):
    lines=path.read_text().splitlines(keepends=True)
    for i,line in enumerate(lines):
        if re.match(r'(?:LEAN_EXPORT |static )?[^;\n]*\b'+re.escape(symbol)+r'\([^;\n]*\)\{\s*$',line):
            depth=0
            for j in range(i,len(lines)):
                depth+=lines[j].count('{')-lines[j].count('}')
                if depth==0:return i+1,j+1,''.join(lines[i:j+1])
    raise AssertionError(symbol)

inline=C/'f01-r15-dev-shortn-inline-decode1/Kernel.lean'
combo=C/'f01-r15-dev-shortn-decode-cutoff1/Kernel.lean'
old_parent=C/'f01-r15-dev-shortn-bcache1/Kernel.lean'
assert sha(inline)=='f65e4aa5baf0b38a808f1e57e0ded26d71870d8b61b993a80ab92aeef77e8d8c'
assert sha(combo)=='cb7f1099cdee33837f66bb7cc015e73c9e21e97dee964d570daac77dbd20380c'
assert sha(old_parent)=='cb1bc62b2be91b52b45090af1f53ef8270b510b1f24264c667ec1308f094d152'
for p in (inline,combo,old_parent):bind(p)
def B1block(p):
    t=p.read_text();s=t.index('namespace Submission.R14ThinBCache');e=t.index('end Submission.R14ThinBCache',s)
    return t[s:e]
assert B1block(inline)==B1block(combo)
assert 'R15PackedB2'not in inline.read_text()+combo.read_text()
assert B1block(inline).count('let fa := R2W01b.convert (A.getD (baseA + k) posZero).raw.1')==1
assert 'if 4 ≤ m ∧ 1 < n ∧ 0 < p ∧ (p ≤ 2 ∨ n ≤ 4)'in B1block(inline)
freeze_p=R15/'development-runtime-freeze.json';freeze=json.loads(freeze_p.read_text());bind(freeze_p)
entry=next(r for r in freeze['candidates']if r['candidate']=='f01-r15-dev-shortn-inline-decode1')
assert entry['sha256']==sha(inline) and entry['decision']=='COMPONENT_PROTOTYPE_NOT_SELECTED_STANDALONE'

old_c_down,old_c_receipt=verify_run(40164630534)
old_diag=old_c_down/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r15-dev-shortn-decode-cutoff1'
ci_p=old_diag/'candidate-c-index.json';ci=json.loads(ci_p.read_text());bind(ci_p)
cp=old_diag/next(r['file']for r in ci if r['module']=='Submission')
for r in ci:assert r['kernel_sha256']==sha(combo)and sha(old_diag/r['file'])==r['sha256']
bind(cp)
main_cp=old_diag/next(r['file']for r in ci if r['module']=='MainFull');bind(main_cp)
main_refs=[dict(line=i+1,text=line)for i,line in enumerate(main_cp.read_text().splitlines())
           if '.m_fun = (void*)lp_competition_Submission_bmm'in line or 'Bench_Suite_run('in line]
assert any('.m_fun = (void*)lp_competition_Submission_bmm'in r['text']for r in main_refs)
old_input=old_c_down/'diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r15-dev-shortn-decode-cutoff1/Kernel.lean'
assert sha(old_input)==sha(combo);bind(old_input)
symbol='lp_competition_Submission_R14ThinBCache_loop'
lo,hi,body=c_function(cp,symbol)
assert 'LEAN_EXPORT float '+symbol in body and 'float v_acc_'in body
assert body.count('lean_float32_of_bits(')==1
assert body.count('lean_uint32_to_float32(')==1
assert body.count('lp_competition_R2W01b_scaleTable')==1
assert 'lp_competition_R2W01b_convert('not in body
assert 'lean_alloc_closure('not in body and 'lean_alloc_ctor('not in body
(HERE/'inline-convert-old-B1-caller.c.txt').write_text(body)
# Follow only functions reachable in the captured public bmm's static graph.
lines=cp.read_text().splitlines(keepends=True);functions={}
for i,line in enumerate(lines):
    m=re.match(r'(?:LEAN_EXPORT |static )?[^;\n]*\b([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\{\s*$',line)
    if not m:continue
    depth=0
    for j in range(i,len(lines)):
        depth+=lines[j].count('{')-lines[j].count('}')
        if depth==0:break
    functions[m[1]]=(i+1,j+1,''.join(lines[i:j+1]))
q=deque([['lp_competition_Submission_bmm']]);seen=set();selected_path=None
while q:
    path=q.popleft();last=path[-1]
    if last in seen:continue
    seen.add(last)
    if last==symbol:selected_path=path;break
    for callee in sorted(set(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\(',functions[last][2])[1:])):
        if callee in functions:q.append(path+[callee])
assert selected_path
selected_nodes=[dict(symbol=s,line_start=functions[s][0],line_end=functions[s][1],
                     body_sha256=hashlib.sha256(functions[s][2].encode()).hexdigest())for s in selected_path]

full_down,full_receipt=verify_run(40165220696)
full_suite=full_down/'diagnostics/f01-d7-public-suite/public-suite'
vp=full_suite/'f01-r15-dev-shortn-decode-cutoff1-verdict.json';v=json.loads(vp.read_text());bind(vp)
assert v['passed']and v['stage']=='score'and len(v['rounds'])==25
fp=full_suite/'inputs/f01-r15-dev-shortn-decode-cutoff1/Kernel.lean';assert sha(fp)==sha(combo);bind(fp)
result_p=R15/'result-1526003-f01-r15-dev-shortn-decode-cutoff1-vs-f01-d12-scalar-combined.json'
result=json.loads(result_p.read_text());bind(result_p)
assert result['sha256']==sha(combo)and result['full_gate_both']and not result['local_discovery_screen_passed']
assert sha(vp)==result['evidence']['verdict_sha256']['f01-r15-dev-shortn-decode-cutoff1']

header=R15/'astra-workers/public-source-runtime/sources/lean-header.txt'
assert sha(header)=='982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13';bind(header)
ht=header.read_text();cast='static inline float lean_uint32_to_float32(uint32_t a) { return (float) a; }'
assert cast in ht and 'LEAN_EXPORT float lean_float32_of_bits(uint32_t u);'in ht
diag=C/'f01-mul-log2-proof1/ci-runs/40392789163/download-dc489ad2bddf4d63a9a323b2871c34b6/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-b2-index1'
parent_cp=diag/'candidate-generated-0.c'
assert sha(parent_cp)=='1fe7b77589af8952ec0da9da3cf33831b9f6ad4bbaeee76e7ce6767d72051b42';bind(parent_cp)
root_symbol='lp_competition_R2W01b_convert';rlo,rhi,rootbody=c_function(parent_cp,root_symbol)
assert rootbody.count('lean_float32_of_bits(')==1 and rootbody.count('lean_uint32_to_float32(')==1
assert 'lp_competition_R2W01b_scaleTable'in rootbody and 'lean_obj_once('not in rootbody
(HERE/'inline-convert-existing-root-converter.c.txt').write_text(rootbody)

record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='OLD_B1_MECHANISM_NEGATIVE_SCREEN_PRESERVED_NEW_B2_NOT_TESTED',
            bindings=bindings,original_run_verification=[old_c_receipt,full_receipt],
            standalone=dict(sha256=sha(inline),frozen_decision=entry['decision'],
                            scope='One accumulator, Array Float32 B cache, Nat/getD reads; no B2 packet/layout or USize loop',
                            full_standalone_measurement='NOT_FOUND_IN_CHECKED_R15_FREEZE_AND_RECEIPTS; historical prototype status preserved'),
            combined_test=dict(sha256=sha(combo),full_run=40165220696,seed=1526003,full_gate='PASS',rounds=25,
                               whole_vs_DF=result['relative_normalized_ratio'],bmm_vs_DF=result['per_operation_normalized']['bmm'],
                               gain_p05=result['gain_p05'],first_discovery_qualifies=False,
                               other_changes=['expanded short-n B1 guard','scalar MUL cutoff84'],
                               attribution='The combined first-D failure does not isolate inline conversion cost; BMM was faster than DF on this sample. It is not a paired B2 or9f7 experiment.'),
            old_selected_B1_C=dict(path=cp.relative_to(ROOT).as_posix(),symbol=symbol,line_start=lo,line_end=hi,
                                   body_sha256=hashlib.sha256(body.encode()).hexdigest(),converter_inlined=True,
                                   of_bits_sites=1,uint32_to_float32_sites=1,eligible_branch='table load + inline uint32 cast + multiply; of_bits is on the rejected eligibility arm',
                                   extra_preparation_allocation=False,timed_object='UNKNOWN_NOT_RETAINED',
                                   static_selected_path=selected_nodes,MainFull_refs=main_refs,
                                   dynamic_route_counts='UNKNOWN'),
            parent_root_converter_C=dict(path=parent_cp.relative_to(ROOT).as_posix(),symbol=root_symbol,
                                         line_start=rlo,line_end=rhi,uses_shared_table_global=True,per_step_table_once=False,
                                         boundary='Existing leaf feasibility only; not evidence for the new B2 selected caller'),
            runtime_interface=dict(uint32_to_float32=cast,float32_of_bits='Exported function declaration',
                                   source='Pinned Lean293d header, no local compilation'),
            decision='CONTINUE exact two-edit B2 draft: no checked identical B2/USize full negative; require selected caller C/ASM before complete-cost claim',
            no_future_reads='Did not open40398675395 or any later D/A/B plan, timing, input, or result',
            elapsed_seconds=time.monotonic()-start)
assert record['elapsed_seconds']<5
(HERE/'inline-convert-history.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(state=record['state'],old_runs=record['original_run_verification'],old_C_lines=[lo,hi],
                     whole=result['relative_normalized_ratio'],BMM=result['per_operation_normalized']['bmm'],
                     seconds=record['elapsed_seconds']),indent=2))
