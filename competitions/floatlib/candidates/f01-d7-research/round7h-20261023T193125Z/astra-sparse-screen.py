"""Exact-word finite falsification and old-input exposure for sparse columns."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,random
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
OLD=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7'
spec=importlib.util.spec_from_file_location('r11_old_generator',OLD/'public-nonfinite-opportunity.py')
g=importlib.util.module_from_spec(spec);spec.loader.exec_module(g);o=g.O
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
assert digest(OLD/'nonfinite-oracle.py')=='3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
EDGE=[0,0x80000000,1,0x80000001,0x7fffff,0x800000,0x3f800000,0xbf800000,
      0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc00001,0xffc00002,0x7f800001,0xff800002]
def row_summary(A):
    # Only the first two nonfinite positions are needed: one active position may be omitted.
    return [(i,(a|0x400000) if o.nan(a) else 0x7fc00000) for i,a in enumerate(A) if o.exp(a)==255][:2]
def sparse_value(A,B,summary=None):
    active=[i for i,b in enumerate(B) if not o.zero(b)]
    assert len(active)<=1
    summary=row_summary(A) if summary is None else summary
    if not active:return summary[0][1] if summary else 0
    t=active[0];z=o.mul(A[t],B[t])
    bad=next(((i,w) for i,w in summary if i!=t),None)
    if bad is not None and (bad[0]<t or not o.nan(z)):return bad[1]
    if o.nan(z):return z
    return o.add(0,z)
def finite():
    rng=random.Random(20261024012);count=0;trace=hashlib.sha256()
    # Include every pair of special values, all active positions, either sign of inactive zero.
    for a in EDGE:
        for b in EDGE:
            A=[a,b]
            for pos in [None,0,1]:
                for v in EDGE:
                    for z in [0,0x80000000]:
                        B=[z,z]
                        if pos is not None:B[pos]=v
                        want=o.dot(A,B);got=sparse_value(A,B);assert got==want,(A,B,got,want)
                        count+=1;trace.update(got.to_bytes(4,'little'))
    for n in [0,1,3,4,7,16,33,128]:
        for _ in range(1500):
            A=[rng.choice(EDGE) if rng.randrange(2) else rng.getrandbits(32) for _ in range(n)]
            B=[rng.choice([0,0x80000000]) for _ in range(n)]
            if n and rng.randrange(2):B[rng.randrange(n)]=rng.choice(EDGE) if rng.randrange(2) else rng.getrandbits(32)
            got=sparse_value(A,B);want=o.dot(A,B);assert got==want,(A,B,got,want)
            count+=1;trace.update(got.to_bytes(4,'little'))
    A=[0x7f800000,0x7fc00001];B=[0x3f800000,0]
    return {'cases':count,'trace_sha256':trace.hexdigest(),'one_nonfinite_summary_counterexample':
            {'A':[hex(w) for w in A],'B':[hex(w) for w in B],'exact':hex(o.dot(A,B)),
             'incorrect_after_discarding_only_first_nonfinite':hex(o.add(0,o.mul(A[0],B[0])))} }
def exposure():
    inv=json.loads((HERE.parent/'bmm-literature-20261024/opportunity.json').read_text())
    ep,et=inv['inputs'][2:4];pp=ROOT/ep['path'];tp=ROOT/et['path']
    assert digest(pp)==ep['sha256'] and digest(tp)==et['sha256']
    plan=json.loads(pp.read_text());timings=json.loads(tp.read_text());rows=[];checks=0
    for c in plan['cases']:
        if c['kernel']!='bmm' or not c['timed']:continue
        b,m,n,p=(c[k] for k in ['batch','m','n','p'])
        if not n or not p or not m:continue
        B=[g.element(c,i,1,p) for i in range(b*n*p)]
        kinds=[0,0,0];qual_batches=0;sampled=0;total_reads=0
        for batch in range(b):
            good=[]
            for j in range(p):
                col=[B[batch*n*p+k*p+j] for k in range(n)]
                # Exit once two nonzero values occur; the classification still preserves an exact certificate.
                nz=0
                for w in col:
                    total_reads+=1;nz+=not o.zero(w)
                    if nz==2:break
                kinds[nz]+=1
                if nz<2:good.append(col)
            if good:
                qual_batches+=1
                if sampled<8:
                    A=[g.element(c,(batch*m)*n+k,0,n) for k in range(n)]
                    summary=row_summary(A)
                    for col in good[:4]:
                        assert sparse_value(A,col,summary)==o.dot(A,col)
                        checks+=1
                    sampled+=1
        row={'name':c['name'],'shape':[b,m,n,p],'columns':b*p,'zero_columns':kinds[0],
             'one_active_columns':kinds[1],'other_columns':kinds[2],
             'qualifying_outputs':m*(kinds[0]+kinds[1]),'all_outputs':b*m*p,
             'qualifying_batches':qual_batches,'certificate_B_word_reads_with_early_rejection':total_reads,
             'A_summary_word_reads_upper_bound':qual_batches*m*n,
             'source_MACs_in_qualified_outputs':m*n*(kinds[0]+kinds[1]),
             'control_case_best_ns':timings[c['name']]['best_ns']}
        rows.append(row)
        print(json.dumps({k:row[k] for k in ['name','zero_columns','one_active_columns','qualifying_outputs']}),flush=True)
    return {'source_plan':ep,'control':et,'seed':852,'sample_output_word_checks':checks,'cases':rows}
if __name__=='__main__':
    result={'status':'FINITE_WORD_THEOREM_MODEL_AND_HISTORICAL_EXPOSURE_ONLY','at_utc':datetime.now(timezone.utc).isoformat(),
            'finite':finite(),'exposure':exposure(),'script_sha256':digest(Path(__file__)),
            'generator_script_sha256':digest(OLD/'public-nonfinite-opportunity.py'),
            'generator_lean_sha256':digest(OLD/'upstream/BenchSuite.lean'),
            'scope':'No new Lean proof, benchmark or hardware run. Python raw generator/oracle; prior crosschecks are history, not acceptance of this theorem. All data from already-executed discovery seed852, no future confirmation input. Source word counts are not latency predictions.'}
    (HERE/'astra-sparse-screen.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'finite_cases':result['finite']['cases'],'sample_output_word_checks':result['exposure']['sample_output_word_checks']}))
