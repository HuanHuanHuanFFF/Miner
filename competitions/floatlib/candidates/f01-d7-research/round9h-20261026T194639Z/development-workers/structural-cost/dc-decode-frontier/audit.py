"""Source/raw-receipt audit only. No Git, Lean, compiler or CI invocation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re

H=Path(__file__).resolve().parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
C=R/'competitions/floatlib/candidates';RESEARCH=C/'f01-d7-research'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def bind(p):return dict(path=p.relative_to(R).as_posix(),bytes=p.stat().st_size,sha256=sha(p))
def verify(run):
    root=C/'f01-mul-log2-proof1/ci-runs'/str(run); idx=root/'original-artifact-hashes.json'
    x=json.loads(idx.read_text());d=root/x['directory']; total=0
    for name,row in x['files'].items():
        p=d/name;assert sha(p)==row['sha256'] and p.stat().st_size==row['bytes'];total+=row['bytes']
    assert {p.relative_to(d).as_posix() for p in d.rglob('*') if p.is_file()}==set(x['files'])
    return d,dict(run=run,index=bind(idx),files=len(x['files']),bytes=total)
oldD,oldAudit=verify(39961709177)
curD,curAudit=verify(40425497337)
lowD,lowAudit=verify(39992610090)
diag=curD/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-route-profile1'
base=C/'f01-r15-dev-packed-b2-1/Kernel.lean';old=C/'f01-d9-bmm-direct-decode-proof2/Kernel.lean'
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(old)=='d5e3512f95dc938db6d41f63745d8bf777cb1f6865c7b4b83a8b9055db2b5b09'
oldInput=oldD/'diagnostics/f01-d7-public-suite/public-suite/inputs/f01-d9-bmm-direct-decode-proof2/Kernel.lean'
assert old.read_bytes()==oldInput.read_bytes()
oldText=old.read_text();baseText=base.read_text()
def dotbody(s):
    a=s.index('def dotLoop ',s.index('namespace NativeFinal'));b=s.index('theorem dotLoop_eq',a)
    return s[a:b]
reversedOld=dotbody(oldText).replace('directDecode','ExecFloat.Binary.toFloat32')
assert reversedOld==dotbody(baseText)
def namespace(s,name):
    a=s.index('namespace '+name);b=s.index('end '+name,a)+len('end '+name);return s[a:b]
def runtime_declarations(s):
    ns=namespace(s,'R2W01b'); starts=list(re.finditer(r'^(?:@\[[^\n]+\] )?(def|theorem) (\w+)',ns,re.M))
    return {m.group(2):ns[m.start():(starts[i+1].start() if i+1<len(starts) else ns.index('end R2W01b'))].strip()
            for i,m in enumerate(starts) if m.group(1)=='def'}
assert runtime_declarations(oldText)==runtime_declarations(baseText)
f65=C/'f01-r15-dev-shortn-inline-decode1/Kernel.lean'
f84=C/'f01-r19-dev-b2-index-inline1/Kernel.lean'
assert dotbody(f65.read_text())==dotbody(baseText)
assert dotbody(f84.read_text())==dotbody(baseText)
low=C/'f01-d10-bmm-low-word-typed/Kernel.lean'
lowText=low.read_text();assert 'acc + directProduct x y' in dotbody(lowText)
assert 'ExecFloat.Binary.toFloat32 (LowScale.mul x y)' in lowText
history_paths=[
 RESEARCH/'round1h-20261023T125752Z/discovery-decisions.json',
 RESEARCH/'round2h-20261023T170031Z/result-841-f01-d10-bmm-low-word-typed.json',
 RESEARCH/'round9h-20261026T194639Z/result-1927005-f01-r19-dev-b2-index-inline1-vs-f01-r15-dev-packed-b2-1.json',
 RESEARCH/'round9h-20261026T194639Z/development-workers/structural-cost/inline-convert-history.json',
 RESEARCH/'round1h-20261023T110107Z/runtime-boundary/object.cpp.raw',
 RESEARCH/'round6h-20261024T051445Z/scalar-mainfull-analysis.md']
f84result=json.loads(history_paths[2].read_text())
assert f84result['sha256']==sha(f84) and f84result['baseline_sha256']==sha(base)
assert sha(low)=='6ba7f0354345b4107c84f83a90d9e4f963d67b6b2c1ab342b61ac27fcc0b5345'
assert sha(f65)=='f65e4aa5baf0b38a808f1e57e0ded26d71870d8b61b993a80ab92aeef77e8d8c'
cpath=diag/'candidate-generated-0.c';mpath=diag/'candidate-generated-1.c';ct=cpath.read_text();mt=mpath.read_text()
index=json.loads((diag/'candidate-c-index.json').read_text())
assert all(sha(diag/r['file'])==r['sha256'] and r['kernel_sha256']==sha(base) for r in index)
def body(symbol):
    m=re.search(r'^LEAN_EXPORT[^\n;]*\b'+re.escape(symbol)+r'\([^\n]*\)\{',ct,re.M);assert m,symbol
    a=m.start();i=ct.index('{',m.start());depth=1;j=i+1
    while depth:
        depth+=(ct[j]=='{')-(ct[j]=='}');j+=1
    return dict(symbol=symbol,start_line=ct.count('\n',0,a)+1,end_line=ct.count('\n',0,j)+1,text=ct[a:j])
P='lp_competition_';names=[
'Submission_bmm','Submission_R15PackedB2_dispatch',
'Submission_R14ThinBCache_dispatch','Submission_bmmBeforeR11Cross','Submission_DirectContinuous_output',
'Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__1',
'Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__0','Submission_NativeFinal_dot','Submission_NativeFinal_dotLoop']
parts=[body(P+n) for n in names]
for n,p in zip(names,parts):(H/(n+'.c.txt')).write_bytes((p['text']+'\n').encode())
for i in range(len(parts)-1):assert parts[i+1]['symbol']+'(' in parts[i]['text'],(names[i],names[i+1])
assert 'lp_competition_Submission_bmm' in mt.split('main___closed__4_value')[1].split('\n')[0]
loop=parts[-1]['text']
counts={name:len(re.findall(r'\b'+name+r'\(',loop))for name in(
'lean_float32_of_bits','lean_nat_add','lean_nat_mul','lean_nat_dec_lt','lean_array_get_size',
'lean_array_fget_borrowed','lean_float32_mul','lean_float32_add','lean_alloc_ctor','lean_apply_1')}
assert counts['lean_float32_of_bits']==2 and counts['lean_array_get_size']==2
asm=json.loads((diag/'native-assembly-index.json').read_text())
assert not any('NativeFinal_dotLoop' in r.get('symbol','') for r in asm)
resPath=diag/'route-profile/result-1927003.json';res=json.loads(resPath.read_text())
planPath=diag/'route-profile/seen-1927003-plan.json';plan=json.loads(planPath.read_text())
cases={c['name']:c for c in plan['cases']};rows=res['complete_case_rows'];timing=res['timing']
assert len(rows)==2
mean={name:sum(r[name]['best_ns']for r in rows)/2 for name,v in rows[0].items() if v['timed']}
whole=sum(mean.values());bmm=sum(v for n,v in mean.items()if n.startswith('bmm:'))
dc=[dict(name=name,shape=[cases[name][k]for k in('batch','m','n','p')],mean_ns=mean[name],
         whole_share=mean[name]/whole,old_R9_direct_domain=(cases[name]['n']<=4 or cases[name]['p']<=2))
    for name,v in res['labels'].items()if v['route']=='DirectContinuous']
assert len(dc)==12 and all(x['shape'][2]>1 and 1<=x['shape'][1]<=3 and 1<=x['shape'][3]<=8 for x in dc)
dcNs=sum(x['mean_ns']for x in dc);pairNs=sum(x['mean_ns']for x in dc if x['shape'][3]>=2)
overlapNs=sum(x['mean_ns']for x in dc if x['old_R9_direct_domain'])
result=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STOP_SAME_DUAL_CONVERTER_RAW_PAIR_ALTERNATIVE_UNCOMPILED',
 originals=[oldAudit,curAudit,lowAudit],bindings=[bind(p)for p in(base,old,f65,f84,low,cpath,mpath,resPath,planPath,*history_paths)],
 historical_direct_converter=dict(run=39961709177,full_gate=True,whole_normalized=1.040345439125485,
 bmm_normalized=1.1731272144011824,exact_same_R2W01b_runtime_declarations=True,
 exact_same_dotLoop_after_reversing_two_converter_calls=True,old_route='n<=4 or p<=2; DirectSmall writer'),
 other_history=dict(R10_low_word='6ba7f035 uses LowScale.mul and toFloat32 on low-product arm; not numeric dual decoder; full gate BMM1.093503/whole1.032933',
 f65='B1 A-only converter; NativeFinal.dotLoop unchanged; prior bound history retained',
 f84='B2 Indexed A-only converter; NativeFinal.dotLoop unchanged; prior selected C removes eligible call/spill but D below adoption',
 f84_result_sha256=sha(history_paths[2]),bitcast='Pinned runtime of_bits bitcasts then canonicalizes NaN; cannot substitute an unchecked arbitrary raw bitcast',
 old_scalar='Existing scalar decoding/scalar native repacks have different caller arithmetic; not evidence that a new DC dual converter is faster'),
 selected_c=[{k:v for k,v in p.items() if k!='text'}for p in parts],selected_loop_static_sites=counts,
 selected_dc_asm='NOT_CAPTURED; no stack/spill/cycle claim',
 seen_cost_snapshot=dict(seed=1927003,processes=2,whole_ns=whole,bmm_ns=bmm,
 dc_ns=dcNs,dc_whole_share=dcNs/whole,dc_bmm_share=dcNs/bmm,
 raw_pair_p_ge2_whole_share=pairNs/whole,raw_pair_needed_local_drop_for3pct_whole=.03/(pairNs/whole),
 old_R9_domain_overlap_cases=sum(x['old_R9_direct_domain']for x in dc),old_R9_domain_overlap_whole_share=overlapNs/whole,
 new_domain_cases=sum(not x['old_R9_direct_domain']for x in dc),new_domain_whole_share=(dcNs-overlapNs)/whole,
 units='mean of two complete original per-case best_ns timers, summed directly; no MAC weighting; not score',cases=dc),
 limitations='Original raw ns belong to full case timer; conversion share UNKNOWN. New code Lean/C/ASM/D NOT_RUN.')
(H/'audit.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
print(json.dumps({k:v for k,v in result.items() if k not in('selected_c','bindings','seen_cost_snapshot')},indent=2))
print(json.dumps({k:v for k,v in result['seen_cost_snapshot'].items() if k!='cases'},indent=2))
