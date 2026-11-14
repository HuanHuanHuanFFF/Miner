"""Small prerequisite screen only. No new runtime, proof/correctness enumeration or CI."""
from pathlib import Path
import importlib.util,json,hashlib,time
from datetime import datetime,timezone
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('domain',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
st=time.monotonic();runs=[]
for run in [40168687803,40169957447,40171180249]:
    base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());prefix='diagnostics/f01-d7-public-suite/public-suite/'
    plan,ph=M.load_checked(base,idx,prefix+'public-drawn-plan.json');verdict,vh=M.load_checked(base,idx,prefix+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,prefix+'public-cell-work.json')
    costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};tot=sum(costs.values());groups={}
    for c in plan['cases']:
        if c['kernel']!='add' or not c['timed']:continue
        cell=':'.join(c['name'].split(':')[:2]);g=groups.setdefault(cell,{'samples':0,'opposite_same_e':0,'new_nonzero_normal':0,'same_e_both_sign_union':0,'zero':0,'low_e01_nonzero':0,'log2_source_iterations':0,'binary_search_stage16_taken':0})
        for j in range(256):
            lo,hi=j*c['work']//256,(j+1)*c['work']//256;i=lo+M.E['word'](c['seed'],j,63)%(hi-lo)
            u=M.E['element'](c,i,0,31);v=M.partner(c,i,u);eu=(u>>23)&255;ev=(v>>23)&255
            h=eu==ev and eu<255 and bool((u^v)&0x80000000)
            g['samples']+=1;g['opposite_same_e']+=h;g['same_e_both_sign_union']+=h or M.guard(u,v)
            if h:
                n=abs((u&0x7fffff)-(v&0x7fffff))
                g['zero']+=n==0
                g['low_e01_nonzero']+=n!=0 and eu<=1
                if n and eu>=2:
                    g['new_nonzero_normal']+=1;g['log2_source_iterations']+=n.bit_length()-1;g['binary_search_stage16_taken']+=n>=65536
    for cell,g in groups.items():
        g['cell_share_whole']=costs[cell]/tot
        for key in ['opposite_same_e','new_nonzero_normal','same_e_both_sign_union','zero','low_e01_nonzero']:
            g[key+'_equal_cost_proxy']=g[key]/g['samples']*g['cell_share_whole']
    runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'groups':groups,'proxy_NOT_speed_or_upper_bound':{k:sum(g[k+'_equal_cost_proxy'] for g in groups.values()) for k in ['opposite_same_e','new_nonzero_normal','same_e_both_sign_union','zero','low_e01_nonzero']},'source_loop_iterations_mean':sum(g['log2_source_iterations'] for g in groups.values())/max(1,sum(g['new_nonzero_normal'] for g in groups.values()))})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'PREREQUISITE_SCREEN_ONLY','runs':runs,'elapsed_seconds':time.monotonic()-st,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'scope':'Exposed R15 inputs and existing transcription; frequencies are not costs; source loop iterations are not machine cycles. No new model correctness enumeration or runtime built.'}
(D/'sterbenz-same-e-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({'runs':[{'run':r['run'],**r['proxy_NOT_speed_or_upper_bound'],'loop_mean':r['source_loop_iterations_mean']} for r in runs],'elapsed_seconds':out['elapsed_seconds']}))
