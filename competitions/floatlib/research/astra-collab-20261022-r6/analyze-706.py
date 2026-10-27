from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
D=HERE/'ci-recovery/706/extracted'
summary=json.loads((D/'summary.json').read_text())
prov=json.loads((D/'provenance.json').read_text())
def load(name):
    p=D/(name+'-verdict.json');v=json.loads(p.read_text())
    assert v['passed'] and v['mode']=='gate' and v['stage']=='score'
    assert len(v['classes'])==12 and len(v['rounds'])==25
    s=next(x for x in summary['results'] if x['candidate']==name)
    assert s['full_gate'] and s['exit_code']==0
    k=(ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean').read_bytes()
    assert hashlib.sha256(k).hexdigest()==s['kernel_sha256']
    log=(D/(name+'-gate.log')).read_text()
    for fragment in ['Submission replays cleanly','VerifyFull replays cleanly',"['Classical.choice', 'Quot.sound', 'propext']"]:assert fragment in log
    return v,s,{'verdict':str(p.relative_to(ROOT)),'verdict_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'gate_log_sha256':hashlib.sha256((D/(name+'-gate.log')).read_bytes()).hexdigest(),'kernel_sha256':s['kernel_sha256']}
pv,ps,pe=load('f01-d5-stream-pack')
def sums(v,prefix):
    cs=[x for k,x in v['classes'].items() if k.startswith(prefix)]
    sub=sum(x['submission_ns'] for x in cs);ref=sum(x['incumbent_ns'] for x in cs)
    return {'sub':sub,'ref':ref,'ratio':sub/ref}
def cfunction(s,name):
    match=re.search(r'^LEAN_EXPORT [^\n;]* '+re.escape(name)+r'\([^\n]*\)\{',s,re.M)
    assert match,name
    a=match.start();pos=s.index('{',match.start());depth=0
    for i in range(pos,len(s)):
        if s[i]=='{':depth+=1
        elif s[i]=='}':
            depth-=1
            if not depth:return s[a:i+1],s[:a].count('\n')+1
def cinfo(name,op):
    d=D/'diagnostics'/name
    idx=json.loads((d/'candidate-c-index.json').read_text())
    entry=next(x for x in idx if x.get('module')=='Submission')
    p=d/entry['file'];b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==entry['sha256']
    f,line=cfunction(b.decode(),'lp_competition_Submission_'+op)
    return {'path':str(p.relative_to(ROOT)),'sha256':entry['sha256'],'line':line,'static_function_lines':len(f.splitlines()),'calls':{k:len(re.findall(re.escape(k)+r'\(',f)) for k in ['lean_uint32_dec_eq','lean_uint32_dec_lt','lean_uint32_dec_le','lean_uint64_dec_lt','lean_uint64_dec_le','lean_float32_of_bits','lean_float32_to_bits','lean_float32_mul','lean_float32_add']},'scope':entry['scope']+'; static sites only, not dynamic counts or timed machine instructions'}
rows=[]
for name,op in [('f01-r6-normal-add-proof1','add'),('f01-r6-web-lowguards','mul')]:
    v,s,e=load(name);ratios={}
    for prefix in ['add:','mul:','sum:','bmm:','']:
        a=sums(pv,prefix);b=sums(v,prefix)
        ratios[prefix or 'whole']={'parent':a,'candidate':b,'raw_new_over_parent':b['sub']/a['sub'],'reference_normalized_new_over_parent':b['ratio']/a['ratio'],'reference_drift':b['ref']/a['ref']}
    rows.append({'candidate':name,'full_gate':'PASS_LEGACY_12_CLASSES_25_ROUNDS','evidence':e,'comparisons':ratios,'classes':v['classes'],'parent_classes':pv['classes'],'generated_c':cinfo(name,op),'parent_generated_c':cinfo('f01-d5-stream-pack',op),'decision':'No material whole-entry gain established in this batch; do not adopt from small component ratio alone. New suite and independent frozen confirmation absent.'})
out={'audited_at_utc':datetime.now(timezone.utc).isoformat(),'run':39791810276,'seed':706,'cpu':next(x.strip() for x in prov['lscpu'].splitlines() if 'Model name:' in x),'official_commit':summary['official_commit'],'source_commit':summary['source_commit'],'artifact_sha256':hashlib.sha256((D.parent/'receipts.zip').read_bytes()).hexdigest(),'artifact_expected_sha256':'2dfda3ea177502a20b6ad068222ebd0df134aba8c1648473a1226ebf53538930','parent_evidence':pe,'results':rows,'scope':'Actual legacy full gates, original replays/three axioms/12 classes/25 rounds. No new suite acceptance or champion inference.'}
(HERE/'first-full-results-706.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'run':out['run'],'cpu':out['cpu'],'results':[{'candidate':x['candidate'],'full_gate':x['full_gate'],'whole':x['comparisons']['whole'],'affected':x['comparisons']['add:' if 'add' in x['candidate'] else 'mul:']} for x in rows]},indent=2))
