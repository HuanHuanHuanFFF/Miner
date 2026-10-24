"""90s source-model replay counts on exposed007/009 BMM specials/extremes only."""
from pathlib import Path
import hashlib,importlib.util,json,time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def main():
    spec=importlib.util.spec_from_file_location('r12_count_ast',HERE/'scalar-none-scalar-counts.py')
    H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
    rp=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7'
    gr,G=H.functions(rp/'public-nonfinite-opportunity.py',('word','ctz','element'),('M64','M32'))
    ora,O=H.functions(rp/'nonfinite-oracle.py',('exp','frac','nan','snan','inf','zero','choose','unpack','rounded','add','mul'),())
    start=time.monotonic();deadline=start+90;rows=[];finished=True
    try:
        for run_id in (40072436647,40073100983):
            run=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run_id}'
            idx=json.loads((run/'original-artifact-hashes.json').read_bytes());base=run/idx['directory']
            relative='diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
            raw=(base/relative).read_bytes();assert sha(raw)==idx['files'][relative]['sha256']
            plan=json.loads(raw)
            for c in plan['cases']:
                if not c['timed']or c['kernel']!='bmm'or c['name'].split(':')[1]not in ('specials','extremes'):
                    continue
                if time.monotonic()>deadline:raise TimeoutError('90second replay model limit')
                batch,m,n,p=(c[k]for k in ('batch','m','n','p'))
                A=[G['element'](c,i,0,n)for i in range(batch*m*n)]
                B=[G['element'](c,i,1,p)for i in range(batch*n*p)]
                r={'run':run_id,'plan_sha256':sha(raw),'name':c['name'],'outputs':batch*m*p,'nan_endpoints':0,
                    'replay_prefix_steps':0,'add_Some':0,'mul_Some':0,'add_None_invalid':0,'mul_None_invalid':0}
                trace=hashlib.sha256();checksum=0
                for q in range(batch*m*p):
                    if q%128==0 and time.monotonic()>deadline:raise TimeoutError('90second replay model limit')
                    j=q%p;i=(q//p)%m;b=q//(m*p);ba=(b*m+i)*n;bb=b*n*p+j
                    acc=0;counts={k:0 for k in ('add_Some','mul_Some','add_None_invalid','mul_None_invalid')}
                    steps=0
                    for k in range(n):
                        a,z=A[ba+k],B[bb+k*p];product=O['mul'](a,z)
                        if O['nan'](product):
                            counts['mul_Some'if O['choose'](a,z)is not None else'mul_None_invalid']+=1
                        output=O['add'](acc,product)
                        if O['nan'](output):
                            counts['add_Some'if O['choose'](acc,product)is not None else'add_None_invalid']+=1
                        acc=output;steps+=1
                        if O['nan'](acc):break
                    assert not O['snan'](acc)
                    if O['nan'](acc):
                        r['nan_endpoints']+=1;r['replay_prefix_steps']+=steps
                        for key,v in counts.items():r[key]+=v
                    trace.update(acc.to_bytes(4,'little'));checksum=((checksum^acc)*16777619)&0xffffffff
                r.update(model_output_le_sha256=trace.hexdigest(),model_checksum32=checksum)
                rows.append(r)
    except TimeoutError:
        finished=False
    totals={}
    for run in (40072436647,40073100983):
        totals[str(run)]={k:sum(r[k]for r in rows if r['run']==run)for k in ('outputs','nan_endpoints','replay_prefix_steps','add_Some','mul_Some','add_None_invalid','mul_None_invalid')}
    report={'state':'COMPLETE_SOURCE_MODEL_SCOPE'if finished else'PARTIAL_TIME_BOUNDED_SOURCE_MODEL','seconds':time.monotonic()-start,
        'budget_seconds':90,'generator_sha256':sha(gr),'oracle_sha256':sha(ora),'cases':rows,'totals':totals,
        'scope':'Only exposed007/009 timed BMM specials/extremes. Original native endpoint classification is modeled by exact-word arithmetic and existing canonicalization arguments; raw replay stops at first quiet NaN. Other BMM cells are UNKNOWN. Counts are not actual compiled execution or stage timings.',
        'current_official_checksum_anchor':'UNKNOWN_NOT_SAVED_FOR_THESE_MODEL_CASES; output hashes/checksums retained for future comparison',
        'full_input_proof':'NOT_ESTABLISHED_BY_ENUMERATION','performance':'UNKNOWN','candidate_or_CI_writes':False}
    (HERE/'scalar-none-tensor-counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':report['state'],'seconds':report['seconds'],'completed_cases':len(rows),'totals':totals},indent=2))


if __name__=='__main__':
    main()
