"""Compare counted scan work with already-poison-stopping replay, never convert it to time."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,time
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[3]
sp=importlib.util.spec_from_file_location('opportunity',HERE/'public-nonfinite-opportunity.py');P=importlib.util.module_from_spec(sp);sp.loader.exec_module(P);O=P.O
base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39840672791/download-81e3479e9e2b47249bf76c8d44eb2e62/diagnostics/f01-d7-public-suite/public-suite'
plan=json.loads((base/'public-drawn-plan.json').read_text());anchorpath=ROOT/'competitions/floatlib/candidates/f01-d7-research/nonnan-input-nan-output-807.json';anchors={r['name']:r for r in json.loads(anchorpath.read_text())['cases']};rows=[];started=time.monotonic()
keys=['outputs','nan_outputs','eligible_outputs','eligible_full_old_steps','eligible_quiet_prefix_steps','eligible_scan_pairs','eligible_scan_words','rejected_outputs','rejected_extra_scan_pairs','rejected_extra_scan_words','rejected_existing_quiet_prefix_steps','first_event_inputs_nonnan_outputs','first_event_inputs_nonnan_prefix_steps']
for c in plan['cases']:
    if c['kernel']!='bmm':continue
    batch,m,n,p=(c[k] for k in ['batch','m','n','p']);A=[P.element(c,i,0,n) for i in range(batch*m*n)];B=[P.element(c,i,1,p) for i in range(batch*n*p)];v={k:0 for k in keys};v.update(name=c['name'],timed=c['timed'],n=n,checksum32=0);trace=hashlib.sha256()
    for b in range(batch):
        for i in range(m):
            for j in range(p):
                aa=(b*m+i)*n;bb=b*n*p+j;q=0;first=None
                for k in range(n):
                    q=O.add(q,O.mul(A[aa+k],B[bb+k*p]))
                    if O.nan(q):first=k;break
                v['outputs']+=1;v['checksum32']=((v['checksum32'] ^ q)*16777619)&0xffffffff;trace.update(q.to_bytes(4,'little'))
                if first is None:continue
                v['nan_outputs']+=1;pairs=words=0;eligible=True
                for k in range(n):
                    pairs+=1;words+=1
                    if O.nan(A[aa+k]):eligible=False;break
                    words+=1
                    if O.nan(B[bb+k*p]):eligible=False;break
                if eligible:
                    assert q==0x7fc00000
                    v['eligible_outputs']+=1;v['eligible_full_old_steps']+=n;v['eligible_quiet_prefix_steps']+=first+1;v['eligible_scan_pairs']+=pairs;v['eligible_scan_words']+=words
                else:
                    v['rejected_outputs']+=1;v['rejected_extra_scan_pairs']+=pairs;v['rejected_extra_scan_words']+=words;v['rejected_existing_quiet_prefix_steps']+=first+1
                if not O.nan(A[aa+first]) and not O.nan(B[bb+first*p]):
                    assert q==0x7fc00000
                    v['first_event_inputs_nonnan_outputs']+=1;v['first_event_inputs_nonnan_prefix_steps']+=first+1
    anchor=anchors[c['name']]
    assert v['checksum32']==anchor['checksum32']
    assert trace.hexdigest()==anchor['output_words_le_sha256']
    assert v['eligible_outputs']==anchor['nan_outputs_without_any_raw_input_nan']
    assert v['eligible_full_old_steps']==anchor['current_raw_replay_steps_on_those_outputs']
    v['source_model_and_actual_checksum_anchor_match']=True;rows.append(v)
    print(json.dumps({k:v[k] for k in ['name','nan_outputs','eligible_outputs','eligible_quiet_prefix_steps','eligible_scan_pairs']}),flush=True)
totals={str(t):{k:sum(r[k] for r in rows if r['timed']==t) for k in keys} for t in [True,False]}
out={'completed_at_utc':datetime.now(timezone.utc).isoformat(),'analysis_seconds':time.monotonic()-started,'source_plan_sha256':hashlib.sha256((base/'public-drawn-plan.json').read_bytes()).hexdigest(),'D_anchor_sha256':hashlib.sha256(anchorpath.read_bytes()).hexdigest(),'analysis_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'totals':totals,'cases':rows,'scope':'Shared exact word model/public generator, checked against D source-word SHA and actual 4-process checksum anchors. Counts only, not timings or private input prevalence. Full no-rawNaN scan and native-prefix/event-local conditions are alternatives with overlap, not additive gains; no extra runtime variant created.'}
(HERE/'cold-scan-cost-807.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(totals,indent=2))
