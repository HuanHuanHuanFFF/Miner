"""Bounded second-route preflight: ordered zero-B packet compaction, no candidate."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib,time
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
st=time.monotonic();reads=0;cap=600000;runs=[]
for run in [40168687803,40169957447,40171180249]:
    base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());prefix='diagnostics/f01-d7-public-suite/public-suite/'
    plan,ph=M.load_checked(base,idx,prefix+'public-drawn-plan.json');verdict,vh=M.load_checked(base,idx,prefix+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,prefix+'public-cell-work.json')
    costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};tot=sum(costs.values());rows=[]
    for c in plan['cases']:
        if c['kernel']!='bmm' or not c['timed']:continue
        m,n,p=(c[k] for k in ['m','n','p']);g=(p+1)//2;bs=sorted(set([0,c['batch']//2,c['batch']-1]));samples=[]
        for b in bs:
            rids=sorted(set([0,m//2,m-1]));need=n*p+len(rids)*n
            if reads+need>cap or time.monotonic()-st>4.5:break
            bb=[M.E['element'](c,b*n*p+i,1,p) for i in range(n*p)]
            aa=[[M.E['element'](c,(b*m+r)*n+k,0,n) for k in range(n)] for r in rids]
            reads+=need
            finite=[all(((x>>23)&255)<255 for x in a) for a in aa]
            zero_b=sum((x&0x7fffffff)==0 for x in bb)
            zero_pairs=sum(all((bb[k*p+j]&0x7fffffff)==0 for j in range(2*q,min(2*q+2,p))) for k in range(n) for q in range(g))
            samples.append({'batch_index':b,'B_words':len(bb),'B_zero_words':zero_b,'B_pair_packets':n*g,'B_all_zero_pair_packets':zero_pairs,'A_sampled_rows':rids,'A_sampled_row_allfinite':finite,'candidate_removed_MAC_fraction_if_all_finite':zero_b/max(1,len(bb)),'candidate_removed_pair_fraction_if_all_finite':zero_pairs/max(1,n*g)})
        cell=':'.join(c['name'].split(':')[:2])
        rows.append({'name':c['name'],'shape':[c['batch'],m,n,p],'base_B2_shape_domain':2<=p<=8 and n>1 and m>=4,'cell':cell,'zeroPct':c['zeroPct'],'zeroKind':c['zeroKind'],'specRate':c['specRate'],'mag':c['mag'],'lengths_per_batch':{'A':m*n,'B':n*p,'outputs':m*p,'original_MACs':m*n*p},'samples':samples,'scope':'Sampled batches/rows only, not whole-matrix finite certificate or actual route trace'})
    groups={}
    for row in rows:
        cell=row['cell'];g=groups.setdefault(cell,{'cell_share_whole':costs[cell]/tot,'sampled_B_words':0,'sampled_B_zeros':0,'sampled_pair_packets':0,'sampled_zero_pairs':0,'sampled_A_rows':0,'sampled_finite_A_rows':0})
        for s in row['samples']:
            g['sampled_B_words']+=s['B_words'];g['sampled_B_zeros']+=s['B_zero_words'];g['sampled_pair_packets']+=s['B_pair_packets'];g['sampled_zero_pairs']+=s['B_all_zero_pair_packets'];g['sampled_A_rows']+=len(s['A_sampled_rows']);g['sampled_finite_A_rows']+=sum(s['A_sampled_row_allfinite'])
    runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'BMM_cell_share_ceiling':sum(v for k,v in costs.items() if k.startswith('bmm:'))/tot,'groups':groups,'cases':rows})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'BOUNDED_SOURCE_TRANSCRIPTION_ONLY','mechanism':'Compact zero B entries/packets once, scan each A row for finiteness, evaluate retained k indices in original order; exact zero-step and reachable-accumulator proof required. No implementation.','reads':reads,'cap':cap,'elapsed_seconds':time.monotonic()-st,'runs':runs,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'limitations':'Samples are not weighted timings or all-input safety guards. Exposed plans only, no future confirmation. Constructor/index/prepass/emit/miss cost unknown; current UnderflowZero route overlap not subtracted. Family labels do not authorize specialization.'}
(D/'sparse-b-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({'reads':reads,'elapsed_seconds':out['elapsed_seconds'],'runs':[{'run':r['run'],'groups':r['groups']} for r in runs]}))
