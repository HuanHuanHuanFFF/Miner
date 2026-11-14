"""Static harness/frozen-data/checksum audit; never claims Lean/native success."""
from pathlib import Path
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
ROUND=HERE.parent.parent
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    ast.parse((HERE/'build_main.py').read_bytes());ast.parse(Path(__file__).read_bytes())
    text=(HERE/'Main.lean').read_text();barrier=(HERE/'R24DotBarrier.lean').read_text()
    adapter=ROUND/'development-dot-cost/Adapters.lean.inc'
    assert 'structure EagerOperand where' in adapter.read_text()
    assert 'def eagerPrepared (a b : EagerOperand)' in adapter.read_text()
    assert 'R24DotProbe.Eager :=' not in text and 'prepareEager a b' not in text
    specs=[('ExactFull','touchRaw','exactFull'),('EagerFull','touchRaw','eagerFull'),('LazyFull','touchRaw','lazyFull'),
           ('ExactPrepared','touchExact','exactPrepared'),('EagerPrepared','touchEager','eagerPrepared'),('LazyPrepared','touchLazy','lazyPrepared')]
    assert len(re.findall(r'@\[noinline\] def pass',text))==6
    assert len(re.findall(r'@\[noinline\] def bench',text))==6
    for suffix,touch,call in specs:
        match=re.search(r'@\[noinline\] def pass'+suffix+r'\b([\s\S]*?)(?=\n@\[noinline\] def bench)',text);assert match
        body=match[0];header=body.split(':=',1)[0]
        assert 'Bool' not in header and '→' not in header and 'fun ' not in body
        assert body.count(touch+' remaining p')==1 and body.count('R24DotProbe.'+call+' ')==1
        assert 'pass'+suffix+' p (s + word) remaining' in body
        match=re.search(r'@\[noinline\] def bench'+suffix+r'\b([\s\S]*?)(?=\n@\[noinline\] def pass|\ndef verify)',text);assert match
        body=match[0];assert 'for trial in [0:3]' in body
        start=body.index('let start ← IO.monoNanosNow');end=body.index('let finish ← IO.monoNanosNow')
        timed=body[start:end];assert 'pass'+suffix+' p s iters' in timed
        assert 'IO.println' not in timed and 'checkWord' not in timed and 'prepare' not in timed
        assert body.index('let p :')<start<end<body.index('let keep ← IO.lazyPure')
        assert body.index('let lifeEnd ← IO.monoNanosNow')>body.index('pure (')
    assert barrier.count('@[noinline] def touch')==4 and barrier.count('if i == 1000000007 then (p.1, p.1) else p')==4
    assert 'import R24DotBarrier' in text and 'IO.lazyPure' in text
    assert 'UInt32.ofNat iters * expected' in text and 'for trial in [0:3]' in text
    data=ROUND/'development-broad/cost-harness/merged-dot-fixtures.json'
    assert sha(data)=='f49020bba646e73531940af6b7fa32cd8ad76b05177146dcddf2f95e6642e74b'
    plan=json.loads(data.read_bytes());assert len(plan['cases'])==148 and len(plan['round_cases'])==1049
    counts={}
    for group in ('24282403','24282405'):
        selected=[c for c in plan['cases'] if c['timed'] and c['group'] in (group,'directed') and c['x'] and len(c['x'])==len(c['y']) and all(((w>>23)&255)!=255 for w in c['x']+c['y'])]
        assert len(selected)==49
        for c in selected:
            n=len(c['x']);iters=max(1,(131072+n-1)//n);assert 1<=iters<=1<<24 and iters-1<1000000007
            for trial in range(3):
                seed=(2654435769+1664525*trial)&0xffffffff
                for r in (1,2,3,17):assert sum([c['expected']]*r,seed)&0xffffffff==(seed+r*c['expected'])&0xffffffff
        counts[group]={'cases':len(selected),'raw_samples_per_process':len(selected)*3,'counter_barrier_sentinel_unreachable':True}
    assert sum(c['fast_result'] is not None for c in plan['cases'])==86
    paths=[HERE/'Main.lean',HERE/'R24DotBarrier.lean',HERE/'README.md',HERE/'build_main.py',Path(__file__),data,adapter]
    report={'status':'STATIC_AND_FROZEN_FIXTURE_PREFLIGHT_PASS_LEAN_NATIVE_NOT_RUN',
        'components':[{'path':p.relative_to(ROOT).as_posix(),'bytes':p.stat().st_size,'sha256':sha(p)} for p in paths],
        'passes':6,'typed_IO_benches':6,'external_barriers':4,'two_independent_operands_for_all_prepared':True,
        'full_verification':{'dots':148,'rounds':1049,'known_attempt_results':86,'complete_adapters':6,'also_checks':['frozen128','exact_replay']},
        'measure_group_counts':counts,'samples_per_case':3,'no_inner_function_arg_or_Bool_selector':True,
        'timing_liveness':'Prepared cache built before start; posttimer onecall wrapper witness uses same cache; no printing or checks within timing; cache block exits before lifecycle end.',
        'Lean':'NOT_RUN','native_checksums':'NOT_RUN','actual_C_ASM':'NOT_RUN','cost':'NOT_RUN',
        'scope':'Static source/frozen-input/checksum-law evidence only. Root must compile separate Barrier module without LTO and inspect selected C/ASM. No dynamic IO benchmark function argument.'}
    (HERE/'READY.json').write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({k:report[k] for k in ('status','passes','typed_IO_benches','external_barriers','measure_group_counts')}))
if __name__=='__main__':main()
