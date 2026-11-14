"""Order-preserving structural-remaining frontend model only, never native cost."""
from pathlib import Path
import hashlib,importlib.util,json,random,sys
HERE=Path(__file__).resolve().parent
def load(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sum_remaining(a,b,index,acc,remaining):
    if remaining==0:return acc
    return sum_remaining(a,b,index+1,acc+a[index]*b[index],remaining-1)
def attempt_tail(m,x,y):
    n=len(x['raw'])
    if n==0 or n!=len(y['raw']):return 0,{'reason':'empty_or_mismatch'}
    if n>1<<30 or not(x['valid'] and y['valid']):return 0,{'reason':'invalid_input'}
    s=sum_remaining(x['values'],y['values'],0,0.0,n)
    L=(n-1).bit_length();H=x['maxIndex']+y['maxIndex'];B=m.tofloat((H+2*L+720)<<52)
    sw=m.tobits(s);q=m.proposal(sw);ok,reason,detail=m.certify(s,B,sw,q)
    return (q if ok else 0),{'reason':reason,'sum_word':hex(sw),'radius_word':hex(m.tobits(B)),'H':H,'L':L,'details':detail,'sum':s,'radius':B}
def main():
    sys.setrecursionlimit(max(10000,sys.getrecursionlimit()))
    m=load('frozen_original_fp',HERE/'portable-f64-dot-model.py');ref=m.load_ref()
    freeze={
        HERE/'PortableF64Dot.lean.inc':'dd775683cade6e575dc6f0684f9216742e1c772c3cf7460b0c53c54e4e3eff04',
        HERE/'cost-harness/Main.lean':'254a106f9d1a6a1a1d222c2452811daf03ee963c5388f6ea84368859ce39403e',
        HERE/'cost-harness/R24DotBarrier.lean':'3d374250064461959646c0cecc101fba7ddb22ecae2e80ee132ca6412711717f',
        HERE/'portable-f64-dot-fixtures.json':'b146a148a8fed7eb528e42d8ce1388ed7e7ca4a5e6cf8b4b55b75f1503c5e1ac'}
    sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
    for p,h in freeze.items():assert sha(p)==h
    fixture=json.loads((HERE/'portable-f64-dot-fixtures.json').read_bytes());groups={'frozen86':fixture['cases'],'extra128':[]};rng=random.Random(24282541)
    for i in range(128):
        n=rng.choice((0,1,2,3,4,7,16,31,64,128));lo,hi=rng.choice(((0,254),(115,140),(0,8),(240,254)))
        a=[m.random_word(rng,lo,hi) for _ in range(n)];b=[m.random_word(rng,lo,hi) for _ in range(n)]
        if i%31==0:b.append(0)
        groups['extra128'].append({'name':f'order-model-{i}','x':a,'y':b})
    trace=hashlib.sha256();summary={}
    for group,cases in groups.items():
        accepted=0;with_sum=0
        for c in cases:
            x,y=m.prepare(c['x']),m.prepare(c['y']);q0,o0=m.attempt(x,y);q1,o1=attempt_tail(m,x,y)
            assert q0==q1 and o0==o1,c['name']
            if 'sum_word' in o0:
                assert o0['sum_word']==o1['sum_word'] and o0['radius_word']==o1['radius_word'];with_sum+=1
            oracle,_=m.exact_dot(c['x'],c['y'],ref)
            if q1:assert q1==oracle,c['name'];accepted+=1
            if 'fast_result'in c:assert q1==c['fast_result']
            trace.update(f'{group},{c["name"]},{q0},{q1},{o0.get("sum_word")}\n'.encode())
        summary[group]={'cases':len(cases),'bitwise_equal_sums_and_endpoints':with_sum,'same_attempt_and_rejection_result':len(cases),'accepted':accepted}
    source=HERE/'PortableF64Tail.lean.inc';body=source.read_text()
    assert 'match remaining with' in body and 'acc : Float' in body and ': Float :=' in body
    assert 'while ' not in body and 'Id.run' not in body and 'termination_by' not in body
    assert all('R24PortableF64.'+n in body for n in ('Prepared','proposal','certify','prepare','ceilLog2'))
    for p,h in freeze.items():assert sha(p)==h
    report={'status':'CONDITIONAL_TAIL_FRONTEND_MODEL_PASS_NO_NATIVE_TEST_REQUEST','source_sha256':sha(source),'source_bytes':source.stat().st_size,
        'original_fp_sha256':freeze[HERE/'PortableF64Dot.lean.inc'],'groups':summary,'trace_sha256':trace.hexdigest(),
        'order_refinement':'Short Lean sumRemaining_eq_foldl uses structural remaining induction and the exact same indexed product readings; no associativity/accuracy premise. Typing NOT_RUN.',
        'activation_condition':'Only consider compilation/cost if actual selected original C exhibits boxed Float/state overhead. If original already unboxed, PARK; no variant grid or shape heuristic.',
        'source_freeze_unchanged':[{'path':str(p.relative_to(HERE)).replace('\\','/'),'sha256':h}for p,h in freeze.items()],
        'Lean':'NOT_RUN','native_model_equivalence':'NOT_RUN','native_cost':'NOT_RUN','CI':'NOT_REQUESTED'}
    (HERE/'PortableF64Tail.READY.json').write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({k:report[k] for k in ('status','source_sha256','source_bytes','groups')}))
if __name__=='__main__':main()
