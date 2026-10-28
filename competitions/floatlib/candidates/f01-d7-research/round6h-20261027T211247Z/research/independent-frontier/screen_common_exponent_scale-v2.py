"""Early-exit complete domain classification for paper common-exponent scale hoisting."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util, json, hashlib, time, argparse
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py')
M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);run=ap.parse_args().run
    assert run in [40168687803,40169957447,40171180249]
    start=time.monotonic();reads=0;trace=hashlib.sha256()
    def summary(c,base,stride,n,role,width):
        nonlocal reads
        exponent=None
        for k in range(n):
            w=M.E['element'](c,base+stride*k,role,width);reads+=1
            trace.update(w.to_bytes(4,'little'))
            if reads%8192==0 and (reads>4000000 or time.monotonic()-start>18):
                raise RuntimeError('bounded screen incomplete; do not report complete')
            if not w&0x7fffffff:continue
            e=(w>>23)&255
            if e==0 or e==255 or (exponent is not None and e!=exponent):return False,None
            exponent=e
        return True,exponent
    base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    index=json.loads((base/'original-artifact-hashes.json').read_bytes());pre='diagnostics/f01-d7-public-suite/public-suite/'
    plan,ph=M.load_checked(base,index,pre+'public-drawn-plan.json')
    verdict,vh=M.load_checked(base,index,pre+'f01-r15-dev-packed-b2-1-verdict.json')
    work,wh=M.load_checked(base,index,pre+'public-cell-work.json')
    costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};total=sum(costs.values());rows=[]
    for c in plan['cases']:
        if not c['timed'] or c['kernel'] not in ['sum','bmm']:continue
        before=reads;hits=zero=outputs=0;whole=True
        if c['kernel']=='sum':
            n=c['length'];outputs=c['batch']
            for b in range(c['batch']):
                valid,e=summary(c,b*n,1,n,0,n)
                z=valid and e is None
                h=valid and e is not None and 24<=e<=200 and n<=2**20
                zero+=z;hits+=h;whole&=h or z
            dimensions=[c['batch'],n]
        else:
            batch,m,n,p=(c[k] for k in ['batch','m','n','p']);outputs=batch*m*p
            for b in range(batch):
                aa=[summary(c,(b*m+r)*n,1,n,0,n) for r in range(m)]
                bb=[summary(c,b*n*p+j,p,n,1,p) for j in range(p)]
                for va,ea in aa:
                    for vb,eb in bb:
                        z=va and vb and (ea is None or eb is None)
                        h=va and vb and ea is not None and eb is not None and 174<=ea+eb<=320 and n<=2**20
                        zero+=z;hits+=h;whole&=h or z
            dimensions=[batch,m,n,p]
        cell=':'.join(c['name'].split(':')[:2])
        rows.append({'name':c['name'],'kernel':c['kernel'],'dimensions':dimensions,'outputs':outputs,
                     'nonzero_input_summary_hits':hits,'zero_summary_hits':zero,'whole_cert':whole,
                     'early_summary_words':reads-before,'whole_cell_share':costs[cell]/total,'cell':cell})
    nonzero=[r for r in rows if r['nonzero_input_summary_hits']]
    cells=sorted({r['cell'] for r in nonzero})
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'COMPLETE_DOMAIN_SOURCE_SCREEN_PAPER_CERTIFICATE',
         'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'reads':reads,
         'early_read_trace_sha256':trace.hexdigest(),'elapsed_seconds':time.monotonic()-start,
         'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'helper_sha256':hashlib.sha256((D/'same_exponent_add.py').read_bytes()).hexdigest(),
         'op_shares':{op:sum(v for k,v in costs.items() if k.startswith(op+':'))/total for op in ['add','mul','sum','bmm']},
         'nonzero_affected_cells':cells,'affected_entire_cell_share_ceiling':sum(costs[k] for k in cells)/total,
         'whole_nonzero_cases':[r['name'] for r in rows if r['whole_cert'] and r['nonzero_input_summary_hits']],
         'cases':rows,'scope':'Every SUM row and BMM row/column classified; invalid summaries stop at first witness. Exact generator inputs from old exposed plans, no float arithmetic/proof/performance. Nonzero summaries do not prove a nonzero dot product. All full-cell shares overcount partially eligible cells; do not assign whole-cell time to certified outputs.',
         'cost':'Summary pass plus mantissa conversion, final per-output scale, fallback and packing all required; no runtime/CI.'}
    (D/f'common-exponent-scale-{run}.json').write_text(json.dumps(out,indent=2)+'\n')
    print(json.dumps({k:out[k] for k in ['run','reads','elapsed_seconds','op_shares','nonzero_affected_cells','affected_entire_cell_share_ceiling','whole_nonzero_cases']}))
if __name__=='__main__':main()
