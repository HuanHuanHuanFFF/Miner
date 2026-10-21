"""Coalesce equal actual length prices within the existing 32-value RMQ coverage."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
HELPER='''pub fn SFprice_bend(ct:&[u32;1024],bend:&mut[u32;512]) {
 let mut i=259usize;let mut last=258usize;
 while i>0 {i-=1;if i==258 || ct[i%1024]!=ct[i.wrapping_add(1)%1024]{last=i;}
  bend[i%512]=Z248(last,i.wrapping_add(31)) as u32;
 }
}

'''
def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    a=r.index('pub fn SFsolve(');b=r.index('pub fn SFpatch(',a);part=r[a:b];assert part.count('Z330(&mut bend)')==1;part=part.replace('Z330(&mut bend)','SFprice_bend(ct,&mut bend)');r=r[:a]+HELPER+part+r[b:]
    a=r.index('pub fn SFheavy(');b=r.index('pub fn SFweak(',a);part=r[a:b];assert part.count('Z330(&mut bend)')==1;part=part.replace('Z330(&mut bend)','SFprice_bend(&ct,&mut bend)');r=r[:a]+part+r[b:]
    proof='''@[local step]
theorem SFprice_bend_loop_spec (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i last : Std.Usize) :
 slot.SFprice_bend_loop ct bend i last ⦃ fun _ => True ⦄ := by
 rw [slot.SFprice_bend_loop]
 apply Std.loop.spec_decr_nat (measure := fun q => q.2.1.val) (inv := fun _ => True)
 · rintro ⟨bend1,i1,last1⟩ _
   simp only [slot.SFprice_bend_loop.body]
   step*
   repeat' (split <;> step*)
   all_goals scalar_tac
 · trivial
@[local step]
theorem SFprice_bend_spec (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) :
 slot.SFprice_bend ct bend ⦃ fun _ => True ⦄ := by
 rw [slot.SFprice_bend]
 step*

'''
    at=l.index('theorem SFsolve');at=l.rfind('@[local step]',0,at);assert at>=0;l=l[:at]+proof+l[at:]
    e=w.write_candidate('r24-609-price-groups',p.name,r,l,
        'Build SF query endpoints from consecutive equal actual length prices, capped at32 covered values, instead of always ending at a DEFLATE length-code boundary. Existing two16-range minima already cover any interval up to32, so no added per-position RMQ levels are needed.',
        'R11 groups optimized D gap filling and failed independent timing; this is SF minimum-query partitioning using the current block cost table. It does not batch writes, enlarge RMQ or change prices/search. Whole-output equality and actual query counts are checked before performance claims.',
        {'parent':p.name,'source':'references/round24-public-609/source-receipt.json','prior_different_mechanism':'docs/rounds/round11.md','proof':'New endpoint-builder totality draft; exact extracted signature and original gate still required.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]+[e]
    s.update(r24_group_counts=True,description='R24 N equal-price interval coalescing in SF only, with existing32-range RMQ coverage. Observe old/new query partitions and per-position match cardinality on unchangedsource; candidate tokens/output tested separately.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]];(E/'groups-n-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    bases=[3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258];rng=random.Random(2424);checks=0
    for _ in range(100):
        ct=[0]*259;ends=list(range(259))
        for j,base in enumerate(bases):
            hi=bases[j+1]-1 if j+1<len(bases) else 258;price=rng.randrange(5,14)
            for k in range(base,hi+1):ct[k]=price;ends[k]=hi
        bend=[0]*259;last=258
        for i in range(258,-1,-1):
            if i==258 or ct[i]!=ct[i+1]:last=i
            bend[i]=min(last,i+31)
        for lo in range(11,259):
            hi=rng.randrange(lo,259);dp=[rng.getrandbits(32) for _ in range(259)];truth=min((dp[x]+ct[x],x)for x in range(lo,hi+1));values=[];x=lo
            while x<=hi:
                end=min(bend[x],hi);assert 1<=end-x+1<=32 and len(set(ct[x:end+1]))==1
                values.append(min((dp[v]+ct[x],v)for v in range(x,end+1)));x=end+1
            assert min(values)==truth;checks+=1
    plan={'gap':'SFsolve/seed/prefix remain meaningful measured cost; constant DEFLATE code boundaries can split adjacent equal actual prices into redundant queries.',
        'change':'Coalesce actual equal prices up to32 values, which the existing two16-minima query supports. No new per-position data structure or changed optimization objective.',
        'minimum':'24800 finite piecewise-code-price interval/minimum checks; native old-path query/cardinality counts and actual28-file token/encoder/decode equality.',
        'decision':'If old/new query counts materially differ and output stays identical, measure original total time. If overhead erases savings or parity fails, diagnose/stop this exactimplementation. Counts alone are not performance.',
        'finite_model_checks':checks,'finite_model_scope':'Partition/argmin model only; not Rust equivalence or proof. Full candidate gate remains mandatory.',
        'cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/groups-n-native/diagnostics'}
    (E/'preflight-n.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e['name'],checks)
if __name__=='__main__':main()
