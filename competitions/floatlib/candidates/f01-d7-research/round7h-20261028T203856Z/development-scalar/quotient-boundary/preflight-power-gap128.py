"""Source/finite arithmetic falsifiers only; never substitutes for Lean/native CI."""
from pathlib import Path
import ast,hashlib,importlib.util,json,random,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
CAND=PUB/'f01-r24-dev-scalar-power-gap1281'
sha=lambda raw:hashlib.sha256(raw).hexdigest()

def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

def main():
    m=module('power_gap_guard',HERE/'gap-boundary-model.py');r=m.load()
    manifest=json.loads((CAND/'manifest.json').read_bytes());raw=(CAND/'Kernel.lean').read_bytes()
    assert sha(raw)==manifest['candidate_sha256'] and len(raw)==manifest['candidate_bytes']<256000
    assert raw.startswith((PUB/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes())
    for item in manifest['components']:
        b=(ROOT/item['path']).read_bytes();assert sha(b)==item['sha256'] and len(b)==item['bytes']
    extract=manifest['dependency_extractions'];broad=(ROOT/extract['source_path']).read_bytes()
    assert sha(broad)==extract['source_sha256']
    for item in extract['spans']:
        b=broad[item['start']:item['end_exclusive']];assert sha(b)==item['sha256'] and len(b)==item['bytes']
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes()
    assert sha(gate)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate);node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(node.value.args[0])).search(raw.decode()) is None
    own=(HERE/'PowerGap128.lean.inc').read_text()
    assert 'decide (gap < den) && decide (gap ≤ den - gap)' in own
    assert 'halfCheck gap den && decide (gap + gap ≤ den - (gap + gap))' in own
    assert 'if field == 1 then halfCheck residue.lo den else quarterCheck residue.lo den' in own
    assert len(set(manifest['explicit_helper_audit']))==manifest['helper_audit_expected_count']==16
    for p in (HERE/'build-power-gap128.py',Path(__file__)):ast.parse(p.read_bytes())
    trace=hashlib.sha256();count=accepted=0
    def test(n,d,E,sign):
        nonlocal count,accepted
        if not 0<=n<1<<128:return
        a=m.native_guard(n,d,E)
        assert a==r.check(n,d,E-150)
        w=r.actual_word(sign,n,d,E-150);target=(int(sign)<<31)|(E<<23)
        if 1<=E<=254 and d>0:assert a==(w==target),(n,d,E,sign,a,hex(w))
        else:assert not a
        count+=1;accepted+=int(a);trace.update(f'{n},{d},{E},{int(sign)},{int(a)},{w}\n'.encode())
    for E in range(256):
        for d in (0,1,2,3,4,7,(1<<32)-1,(1<<63)-1,1<<63,(1<<63)+1,(1<<64)-1):
            offsets={0,-1,1,-d-1,-d,d,d+1,-(1<<64),1<<64,-(1<<63),1<<63}
            for q in (d//4,d//2):offsets.update((q-1,q,q+1,-q-1,-q,-q+1))
            for delta in sorted(offsets):
                for sign in (False,True):test(m.M*d+delta,d,E,sign)
    rng=random.Random(24282334)
    for _ in range(100000):
        E=rng.randrange(256);d=rng.randrange(1,1<<64)
        test(m.M*d+rng.randrange(-d,d+1),d,E,bool(rng.getrandbits(1)))
    for _ in range(20000):test(rng.getrandbits(128),rng.randrange(1,1<<64),rng.randrange(256),bool(rng.getrandbits(1)))
    mutants=[]
    for label,n,d,E in (('low_only',m.M*4+(1<<64),4,128),
        ('missing_gap_lt_den',m.M+(1<<63),1,128),
        ('quarter_without_half',m.M*((1<<64)-1)-(1<<63),(1<<64)-1,128)):
        assert m.native_guard(n,d,E,label) and not m.native_guard(n,d,E)
        assert r.actual_word(False,n,d,E-150)!=E<<23
        mutants.append(label)
    assert not m.native_guard(0,0,128)
    odd=m.M+1;assert r.actual_word(False,2*odd+1,2,128-150)!=(128<<23|1)
    mutants+=['closed_midpoint_with_odd_candidate','denominator_zero']
    report={'status':'FINITE_MODEL_AND_FROZEN_PACKAGE_PASS_LEAN_NOT_RUN','candidate':CAND.name,
        'source_sha256':manifest['candidate_sha256'],'bytes':len(raw),'roots':16,'cases':count,'accepted':accepted,
        'trace_sha256':trace.hexdigest(),'mutants_rejected':mutants,
        'guard_order':'Full128 abs gap; high=0; g<D; g<=D-g. Only lower side above minnormal doubles g and checks twice<=D-twice.',
        'Lean':'NOT_RUN','original_replay':'NOT_RUN','AX':'NOT_RUN','native_execution':'NOT_RUN','cost':'NOT_RUN',
        'scope':'Finite integer/source model with all256 raw exponent fields, both signs, full64 D, full128 N. No universal proof, runtime result or probability claim.'}
    (HERE/'preflight-power-gap128.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    ready=json.loads((HERE/'READY-power-gap128.json').read_bytes());ready['status']='READY_FOR_PARENT_KEY_REVIEW_AND_ORIGINAL_MATH_GATE'
    ready['preflight']='preflight-power-gap128.json';ready['dependencies']='Frozen power-cell2 and exact broad gap substrate; all new typing pending.'
    (HERE/'READY-power-gap128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({k:report[k] for k in ('status','source_sha256','bytes','roots','cases','accepted','mutants_rejected')}))
if __name__=='__main__':main()
