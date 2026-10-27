from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,random
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
MASK=(1<<32)-1
def stream(n,seed):
    for _ in range(n):
        seed=(seed*1664525+1013904223)&MASK
        yield seed
def gen(name,i,w):
    base=w&0x807fffff
    if name=='near-one': e=124+(w>>23)%7
    elif name=='spread': e=1+(w>>23)%254
    elif name=='tiny': e=55+(w>>23)%11 if i%2==0 else 60-(w>>23)%11
    elif name=='wide-gap': e=127 if i%2==0 else 107-(w>>23)%11
    return base|(e<<23)
counts={}
for name,salt in [('near-one',0x11),('spread',0x12),('tiny',0x13),('wide-gap',2)]:
    old=None
    c={'pairs':0,'mul_low_path':0,'mul_normal_word_path':0,'mul_product_leading46':0,'mul_product_leading47':0,'add_gap_ge25':0,'add_gap_ge26':0}
    for i,w in enumerate(stream(500001,0x9e3779b9^((salt*0x9e3779b9)&MASK))):
        word=gen(name,i,w)
        if old is not None:
            x,y=old,word
            ex,ey=(x>>23)&255,(y>>23)&255
            c['pairs']+=1
            c['add_gap_ge25']+=abs(ex-ey)>=25
            c['add_gap_ge26']+=abs(ex-ey)>=26
            if ex+ey<128:c['mul_low_path']+=1
            else:
                c['mul_normal_word_path']+=1
                p=((x&0x7fffff)|0x800000)*((y&0x7fffff)|0x800000)
                assert (1<<46)<=p<(1<<48)
                c['mul_product_leading46' if p<(1<<47) else 'mul_product_leading47']+=1
        old=word
    counts[name]=c
vpath=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39767698381/download-32ae89957cfa4e0bb4235f025a013e92/f01-d5-stream-pack-verdict.json'
v=json.loads(vpath.read_text())
total=sum(x['submission_ns'] for x in v['classes'].values())
shares={k:x['submission_ns']/total for k,x in v['classes'].items()}
out={'completed_at_utc':datetime.now(timezone.utc).isoformat(),'status':'VERIFIED_FINITE_GENERATOR_COVERAGE','scope':'Reimplementation of pinned official generators and overlapping consecutive-pair sweep at stated seed. Counts are not probabilities or timings. All timed domains analytically normal.','bench_sha256':hashlib.sha256((HERE/'upstream/Bench.lean').read_bytes()).hexdigest(),'bench_seed':0x9e3779b9,'pairs':500000,'counts':counts,'timing_source_run':39767698381,'timing_verdict_sha256':hashlib.sha256(vpath.read_bytes()).hexdigest(),'same_source_608_class_shares':shares,'candidate_exposure':{'R_normal_add':sum(shares[k] for k in shares if k.startswith('add:')),'R_normal_mul_affected_classes_upper':shares['mul:near-one']+shares['mul:spread'],'web_low_affected_classes_upper':shares['mul:tiny']+shares['mul:spread'],'web_gap_affected_class_upper':shares['add:wide-gap']},'expected_actual_reduction':'UNKNOWN; exposure ceilings do not deduct guards/other-route cost and are not predicted gains'}
(HERE/'route-coverage.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
