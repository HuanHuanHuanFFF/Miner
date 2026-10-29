"""Static whole-bank frame/protocol and frozen exact-data audit only."""
from pathlib import Path
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if(p/'AGENTS.md').is_file())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    for p in(HERE/'build_harness.py',HERE/'build-fixtures.py',Path(__file__)):ast.parse(p.read_bytes())
    main=(HERE/'Main.lean').read_text();bank=(HERE/'GenericDotBank.lean.inc').read_text();barrier=(HERE/'R24DotBarrier.lean').read_text()
    assert main.count('@[noinline] def pass')==3 and main.count('@[noinline] def bench')==3
    assert main.count('for trial in [0:3]')==3 and main.count('let keep ← IO.lazyPure')==3
    for suffix,method in(('Exact','exactBank'),('Eager','eagerBank'),('Lazy','lazyBank')):
        p=re.search(r'@\[noinline\] def pass'+suffix+r'\b([\s\S]*?)(?=\n@\[noinline\] def bench)',main)[0]
        assert 'fun 'not in p and 'Bool'not in p and p.count('touchBank remaining p')==1
        assert p.count('R24GenericDotBank.'+method+' p.1 p.2')==1
        assert p.index('let out :=')<p.index('let word := hashAll out')<p.index('p (s + word) remaining')
        b=re.search(r'@\[noinline\] def bench'+suffix+r'\b([\s\S]*?)(?=\n@\[noinline\] def pass|\ndef verify)',main)[0]
        start=b.index('let start ← IO.monoNanosNow');end=b.index('let finish ← IO.monoNanosNow')
        assert 'pass'+suffix+' p s iters' in b[start:end] and 'prepare'not in b and 'IO.println'not in b[start:end]
        assert b.index('let keep ← IO.lazyPure')>end
        function=re.search(r'@\[noinline\] def '+method+r'\b([\s\S]*?)(?=\n/--|\nend Submission)',bank)[0]
        assert function.count('for row in rowsA')==1 and function.count('for row in rowsB')==1
        assert function.index('for row in rowsB')<function.index('for left in a')<function.index('for right in b')
    assert 'Array (Array UInt32)'in barrier and 'if i == 1000000007 then (p.1, p.1) else p'in barrier
    assert main.count('checkArray c.name')==3 and 'hashAll expected'in main
    assert 'sumRemaining out (index + 1) (acc + out[index]!) rest'in main
    assert 's + UInt32.ofNat iters * expected'in main
    assert '\\"'not in main and '\\\\t'not in main
    f=json.loads((HERE/'fixtures.json').read_bytes());assert len(f['cases'])==6 and sum(len(c['expected'])for c in f['cases'])==464
    assert sha(HERE/'fixtures.json')=='986eaf0dd77ec19d6f64bed9a1f653da6004f28c3d4968fd31358c98e421d7f1'
    groups={}
    for g in('24282601','24282603'):
        rows=[c for c in f['cases']if c['group']==g];assert len(rows)==3
        for c in rows:
            work=c['rows']*c['cols']*c['inner'];iters=max(1,(131072+work-1)//work)
            assert 1<=iters<=1<<24 and iters-1<1000000007
            assert len(c['rowsA'])==c['rows']and len(c['rowsB'])==c['cols']and len(c['expected'])==c['rows']*c['cols']
            assert all(len(row)==c['inner']for row in c['rowsA']+c['rowsB'])
            expected=sum(c['expected'])&0xffffffff
            for trial in range(3):
                seed=(2654435769+1664525*trial)&0xffffffff
                for n in(1,2,3,17):assert sum([expected]*n,seed)&0xffffffff==(seed+n*expected)&0xffffffff
        groups[g]={'cases':3,'raw_samples_per_process':9}
    paths=[HERE/n for n in('Main.lean','R24DotBarrier.lean','GenericDotBank.lean.inc','fixtures.json','HARNESS.md','README.md','build_harness.py','preflight_harness.py')]
    report={'status':'STATIC_WHOLE_BANK_HARNESS_READY_LEAN_NATIVE_COST_NOT_RUN','components':[{'path':p.relative_to(ROOT).as_posix(),'bytes':p.stat().st_size,'sha256':sha(p)}for p in paths],
        'passes':['R24DotBankHarness.passExact','R24DotBankHarness.passEager','R24DotBankHarness.passLazy'],
        'backend_functions':['Submission.R24GenericDotBank.exactBank','Submission.R24GenericDotBank.eagerBank','Submission.R24GenericDotBank.lazyBank'],
        'barrier':'R24DotBarrier.touchBank; module may be copied asR24DotBarrier.lean; Main may be copied asR24DotCostMain.lean',
        'protocol':{'BANK_SAMPLE':13,'BANK_SETUP':9,'BANK_MEASURE_DONE':6,'BANK_VERIFY':8,'BANK_VERIFY_DONE':4},
        'observer':'Explicit ALL-word structural additiveUInt32 traversal consumes result array; expectedSum computed once, sink=seed+iters*expectedSum modulo2^32. No prebuilt row cache input.',
        'groups':groups,'verify_outputs_per_backend':464,'verify_backends':3,'default_MAC_target':131072,
        'Lean':'NOT_RUN','native':'NOT_RUN','actual_C_ASM':'NOT_RUN','cost':'NOT_RUN','CI':'ROOT_ONLY_IF_AUTHORIZED_BEFORE_03_15',
        'scope':'Generic research caller only; no official BMM/Kernels/rank claim. Static source boundaries must still be verified in actual selected C.'}
    (HERE/'HARNESS-READY.json').write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({'status':report['status'],'main':report['components'][0],'barrier':report['components'][1],'protocol':report['protocol'],'groups':groups},indent=2))
if __name__=='__main__':main()
