"""Compact only backward tree child edges, preserving full root timestamps."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
HELPERS='''#[inline(always)]
pub fn Achild(kid:&[u16;65536],node:usize,side:usize)->u32 {
 let d=kid[(node%32768).wrapping_mul(2).wrapping_add(side)%65536]as usize;
 if d>0 && d<=node {(node-d).wrapping_add(1)as u32}else{0}
}
#[inline(always)]
pub fn Asetchild(kid:&mut[u16;65536],at:usize,now:usize,child:u32) {
 let parent=now.wrapping_sub(now.wrapping_sub((at/2)%32768)%32768);
 let c=child as usize;let delta=parent.wrapping_add(1).wrapping_sub(c);
 kid[at%65536]=if c>0 && delta>0 && delta<32768 {delta as u16}else{0};
}

'''
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    for name in ['Z162','Z189']:
        old=fn(r,name);s=old;assert s.count('kid: &mut [u32; 65536]')==1;s=s.replace('kid: &mut [u32; 65536]','kid: &mut [u16; 65536]')
        changes={
            'kid[lo_at % 65536] = kid[pk % 65536];':'let left=Achild(kid,p,0);Asetchild(kid,lo_at,pos,left);',
            'kid[hi_at % 65536] = kid[(pk + 1) % 65536];':'let right=Achild(kid,p,1);Asetchild(kid,hi_at,pos,right);',
            'kid[lo_at % 65536] = cur as u32;':'Asetchild(kid,lo_at,pos,cur as u32);',
            'kid[hi_at % 65536] = cur as u32;':'Asetchild(kid,hi_at,pos,cur as u32);',
            'cur = kid[lo_at % 65536] as usize;':'cur = Achild(kid,p,1) as usize;',
            'cur = kid[hi_at % 65536] as usize;':'cur = Achild(kid,p,0) as usize;'}
        for a,b in changes.items():assert s.count(a)==1,(name,a);s=s.replace(a,b)
        assert r.count(old)==1;r=r.replace(old,s)
    old='let mut kid = [0u32; 65536];';assert r.count(old)==2;r=r.replace(old,'let mut kid = [0u16; 65536];')
    at=r.index('pub fn Z162(');r=r[:at]+HELPERS+r[at:]
    e=w.write_candidate('r24-609-child16',p.name,r,l,'Store A binary-tree children as positive parent-relative distances below32768, zero for absent/expired edges; retain all full32bit root/near/short timestamps. Decode relative to the actual live parent, not the query position, to avoid stale-window aliasing. This halves the65536-entry child array.','Prior compact heads/predecessors in fast and SF families did not guarantee speed. This targets a different large child working set and preserves root age checks/hash/search depth. Links outside the window are only discarded when already unusable in all later queries; finite/public parity and measured timing must test the implementation.',{'parent':p.name,'profile':'evidence/round24/weighted-stage-priority.json','prior_compact_negative':'docs/research/optimization-methods.md','proof':'DRAFT: child array types and two new total helpers require fresh extraction and complete gate. No all-input equivalence claimed from finite model.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(description='AD parent-relative U16tree children with fulltimestamp roots preserved. Finite edge/window model and original28file token/encoder/decode before total-time and proof.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    rng=random.Random(241616);cases=0
    for _ in range(100000):
        now=rng.randrange(0,1<<26);parent=rng.randrange(max(0,now-32767),now+1);side=rng.randrange(2);at=2*(parent%32768)+side
        recovered=now-((now-(at//2)%32768)%32768);assert recovered==parent
        child=rng.randrange(parent+1) # zero, or an older position plus1
        delta=parent+1-child;stored=delta if child>0 and 0<delta<32768 else 0
        decoded=parent-stored+1 if stored>0 and stored<=parent else 0
        expect=child if child>0 and 0<delta<32768 else 0;assert decoded==expect
        future=now+rng.randrange(0,32768);oldest=max(0,future-32767)
        assert (child if child>oldest and child<=future else 0)==(decoded if decoded>oldest and decoded<=future else 0)
        cases+=1
    for name,d in [('child-ad-native',s),('preflight-ad',{'gap':'A matching remains material; changing long hash keys lost1505B. Preserve the search graph while reducing a separate large working-set component.','change':'Only binary-tree children become parent-relativeU16; roots retain absoluteU32.65536entries shrink256KiBto128KiB.','minimum':'100000finite live-parent reconstruction/edge/window checks and actual28file originaltoken/encoder/decode parity.','decision':'Any token difference first diagnoses edge age, ring reuse or parent identity. Parity earns controlled total-time screen; memory reduction itself is not speed or reward evidence.','model_cases':cases,'model_scope':'Finite intended edge/window invariants, not complete Rust equivalence or proof.','cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/child-ad-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'],cases)
if __name__=='__main__':main()
