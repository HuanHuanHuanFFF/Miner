"""Use the retained seed's same-distance-code length to reject redundant SF scans."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')

def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
    helper='''#[inline(always)]
pub fn SFcanextend(input:&[u8],j:usize,p:usize,cap:usize,ot:u32)->bool {
 if ot==0 {return true;}
 let d=p.wrapping_sub(j);
 if Z353(d)!=Z353(SFdist(ot)) {return true;}
 let l=SFlen(ot);
 if l>=cap {return false;}
 Z332(input,j.wrapping_add(l))==Z332(input,p.wrapping_add(l))
}

'''
    marker='pub fn SFsmallmatches(';assert r.count(marker)==1
    r=r.replace(marker,helper+marker)
    old='let l=SFmatchlen(input,j,p,cap,known);'
    assert r.count(old)==2
    r=r.replace(old,'let l=if SFcanextend(input,j,p,cap,ot){SFmatchlen(input,j,p,cap,known)}else{0};')
    # Keep the draft explicit; helper termination is cheap but only a fresh
    # extraction + original obligation can establish full gate acceptance.
    proof='''@[local step]
theorem SFcanextend_spec (input : Slice Std.U8) (j p cap : Std.Usize) (ot : Std.U32) :
 slot.SFcanextend input j p cap ot ⦃ fun _ => True ⦄ := by
 rw [slot.SFcanextend]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
    # Place the helper before the existing small-matcher proof declarations.
    pos=l.index('theorem SFsmallmatches')
    pos=l.rfind('@[local step]',0,pos)
    assert pos>=0
    l=l[:pos]+proof+l[pos:]
    e=w.write_candidate('r24-609-seedtail','r24-609-once',r,l,
        'In both SF matching collectors, the seed already occupies its distance-code slot. For another source of that code, skip matching when its cap cannot exceed seed length or its byte at seed length differs. Original insertion order, capacity, distinct codes and all retained quality choices remain unchanged.',
        'R19 shared-prefix work transferred a base cache and paid cache lookup costs. This uses only the already-live seed token and one tail byte; no new cache, hash structure, search budget or quality acceptance rule. New609 measured matching cost provides the opportunity.',
        {'parent':'candidates/r24-609-once/manifest.json','source':'references/round24-public-609/source-receipt.json','profile':'evidence/round24/38080823460/profile-c-native/diagnostics/r18-functions/functions.json','prior_related':'docs/rounds/round19.md'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'quality-b-native.json').read_bytes());s['entries']=[x for x in s['entries'] if x['control'] and x['name']!='public607']
    parent=w.control('once','candidates/r24-609-once','609');parent.pop('formal_id');parent['anchor']='public609';s['entries'] += [parent,e]
    s.update(native_encoder_references=['public609','once'],description='R24 D seed-distance-code tail rejection, expected finite token/output parity; same exact complete609quality retained. No global-state observer in submitted candidate.')
    names=[x['name'] for x in s['entries']];s['screen_orders']=[names,names[::-1]]
    (E/'seedtail-d-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    rng=random.Random(2404);checks=0
    for _ in range(20000):
        cap=rng.randint(3,258);oldlen=rng.randint(3,258);actual=rng.randint(0,cap)
        # The filter can only remove a same-code candidate no longer than the
        # seeded entry; it cannot alter the 4-slot capacity or insertion order.
        reject=oldlen>=cap or actual<=oldlen
        old=max(oldlen,actual) if actual>=3 else oldlen
        new=oldlen if reject else old
        assert old==new;checks+=1
    plan={'gap':'Measured native observer spends substantial inclusive time in SFsmallmatches; no established whole-time speed gain. Two frozen original timing screens are still running.',
        'change':'Same-distance-code seed domination filter with cap/tail-byte test, no expensive state transfer. At most same-code candidates already unable to update the occupied slot are skipped.',
        'minimum':'All28files original byte/token/decode comparison, then finite generated token equality if preserved. Examine surviving source/control time only with original protocol.',
        'decision':'Any byte difference triggers diagnosis of seed/cap/distance-class logic before proof or timing promotion. Exact parity earns paired total-time comparison against actualonce parent and609shadow.',
        'model_checks':checks,'model_scope':'Only abstract same-code selection identity; not Rust, complete parser equivalence, proof or timing.',
        'cost_cap_runner_minutes':15,'proof':'One new helper and two altered collectors remain DRAFT until exact original gate.',
        'evidence':'evidence/round24/<run>/seedtail-d-native/diagnostics'}
    (E/'preflight-d.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e)
if __name__=='__main__':main()
