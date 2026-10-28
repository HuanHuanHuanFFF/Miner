"""Generate exact proof-leaf interface receipt + finite symbolic first falsifier."""
from pathlib import Path
import hashlib
import itertools
import json
import re

HERE=Path(__file__).resolve().parent
sha=lambda b:hashlib.sha256(b).hexdigest()
ZERO=('POS_ZERO',)


def symbolic(n,p,bases,baseC,alen,clen,k):
    g=(p+1)//2
    full=[[[(f'q{r}{c}',)] for c in range(2)] for r in range(4)]
    for j in range(k,n):
        cur=baseC+j*g
        bp=[('B',cur,c) if cur<clen else ZERO for c in range(2)]
        for r in range(4):
            av=('A',bases[r]+j) if bases[r]+j<alen else ZERO
            for c in range(2):full[r][c].append((av,bp[c]))
    pairs=[]
    for r in range(4):
        pair=[[(f'q{r}{c}',)] for c in range(2)]
        for j in range(k,n):
            av=('A',bases[r]+j) if bases[r]+j<alen else ZERO
            cur=baseC+j*g
            for c in range(2):pair[c].append((av,('B',cur,c) if cur<clen else ZERO))
        assert pair==full[r]
        pairs.append(pair)
    return pairs


def main():
    source=(HERE/'Nat8Projection-v1.lean.inc').read_bytes()
    text=source.decode()
    namespace=re.search(r'^namespace\s+(\S+)',text,re.M)[1]
    roots=[namespace+'.'+m for m in re.findall(r'^theorem\s+(\w+)',text,re.M)]
    assert roots==[namespace+'.'+n for n in ('cacheView_get','decode_eq','loop_row','loop_lane')]
    assert re.findall(r'\| [012_] => ⟨q\.(c\d\d), q\.(c\d\d)⟩',text)==[
        (f'c{r}0',f'c{r}1') for r in range(4)]
    assert 'baseC + k.val * R22Pair8.groups p' in text
    assert 'baseC + (k + 1) * R22Pair8.groups p' in text
    assert 'R15PackedB2.loop_s0' in text and 'R15PackedB2.loop_s1' in text
    assert not re.search(r'\b(sorry|axiom|unsafe|extern|implemented_by)\b',text)
    count=0
    for n,p,baseC,alen,clen in itertools.product(range(5),range(6),range(4),(0,2,9),(0,2,12)):
        for bases in ((0,1,2,3),(0,0,0,0),(3,7,11,19)):
            for k in range(n+2):symbolic(n,p,bases,baseC,alen,clen,k);count+=1
    # First interface falsifier: in p3 group1, right padding is not raw column3.
    raw_b=[('raw',i) for i in range(6)]
    cache=[(raw_b[k*3+2*g],raw_b[k*3+2*g+1] if 2*g+1<3 else ZERO)
           for k in range(2) for g in range(2)]
    view=[cache[1+k*2] for k in range(2)]
    valid=[raw_b[2+k*3] for k in range(2)]
    invalid=[raw_b[3+k*3] if 3+k*3<len(raw_b) else ZERO for k in range(2)]
    assert [v[0] for v in view]==valid
    assert [v[1] for v in view]!=invalid
    runtime=(HERE/'KernelIndexed8Cost.lean').read_bytes()
    assert sha(runtime)=='8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
    report={'fragment':'Nat8Projection-v1.lean.inc','sha256':sha(source),'bytes':len(source),
        'runtime_sha256':sha(runtime),'runtime_unchanged':True,
        'append_bytes_in_memory_only':len(runtime)+1+len(source),
        'append_headroom_bytes':256000-len(runtime)-1-len(source),
        'namespace':namespace,'roots':roots,
        'interfaces':{'loop_row':'All four arbitrary row bases, arbitrary8 Float32 seeds, anyNat k; one Fin4 projection into existingR15PackedB2.loop over exactrow-major cacheView.',
            'loop_lane':'One Fin2 selected-field read premise; then existingloop_s0/s1 yieldsNativeFinal.dotLoop. No phantom/raw-B equivalence assumed.'},
        'symbolic_cases':count,'finite_symbolic_projection_pass':True,
        'first_falsifier':{'shape':[1,4,2,3],'group':1,'baseC':1,
            'cache_view':view,'valid_left_raw_reads':valid,'invalid_right_raw_reads':invalid,
            'invalid_right_agreement_rejected':True,
            'Lean_checkpoint':'First compile loop_row with n3,p3,row3,k1 arbitraryseeds; it must normalizeC+kG+G correctly. Then loop_lane requires theactualselected-field hread, never an invalid second-column raw premise.'},
        'dependencies':['Exact8e runtime','R2W01c.convert_eq','Packed10.vector_get_ofFn','R15PackedB2.loop_s0','R15PackedB2.loop_s1'],
        'status':'NOT_COMPILED_NOT_RUN','new_kernel_emitted':False,'local_Lean_native_CI_Git':False,
        'prior_v0':{'path':'Nat8Projection.lean.inc','sha256':sha((HERE/'Nat8Projection.lean.inc').read_bytes()),
            'status':'NOT_RUN; v1 reuses acceptedR13 explicit decoder simp form to avoid possible redundantrfl afterrw'},
        'scope':'Source API/symbolic check only. Not IEEE arithmetic, Lean typing, kernel replay, cache producer or full public correctness.'}
    (HERE/'nat8-projection-manifest.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report))


if __name__=='__main__':main()
