"""Inline single SF tokens and reserve indexed storage for positions with multiple matches."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
HELPERS='''#[inline(always)]
pub fn SFslot_encode(count:usize,first:u32,begin:usize)->u32 {
 if count<2 || begin>=536870912 {first}
 else {0x80000000u32 | (((count.wrapping_sub(2)%4) as u32)<<29) | (begin as u32)}
}

#[inline(always)]
pub fn SFrelax_token(rm:&[u64;4096],ct:&[u32;1024],bend:&[u32;512],i:usize,t:u32,bc:u64,bt:u32)->(u64,u32) {
 let l=SFlen(t);let d=SFdist(t);let dcs=(ct[Z353(d).wrapping_add(512)%1024] as u64)<<32;
 let v=Z440(rm,ct,i,3,Z248(10,l),dcs,bc);let v=Z437(rm,ct,bend,i,11,l,dcs,v);
 if v<bc {(v,SFmt(d,((v as u32) as usize).wrapping_sub(i)))}else{(bc,bt)}
}

'''
def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    for name,nextname,keep,mod in [('SFsmallmatches','SFpriced','SFsmallkeep(&best,count,c,ct)',8),('SFmorematches','SFheavy','SFfastkeep(&best,&codes,count,c,ct)',4)]:
        a=r.index('pub fn '+name+'(');b=r.index('pub fn '+nextname+'(',a);part=r[a:b]
        first='Z430(starts,items.len() as u32);';assert part.count(first)==2
        part=part.replace(first,'',1)
        old=f'let mut c=0usize;while c<count&&c<4{{if {keep}{{Z430(items,best[c%{mod}]);}}c+=1;}}p+=1;'
        assert part.count(old)==1
        new=f'''let begin=items.len();let mut seen=0usize;let mut first=0u32;
  let mut c=0usize;while c<count&&c<4{{if {keep}{{let t=best[c%{mod}];if seen==0{{first=t;}}else{{if seen==1{{Z430(items,first);}}Z430(items,t);}}seen=seen.wrapping_add(1);}}c+=1;}}
  Z430(starts,SFslot_encode(seen,first,begin));p+=1;'''
        part=part.replace(old,new);assert part.count(first)==1;part=part.replace(first,'Z430(starts,0);');r=r[:a]+part+r[b:]
    for name,nextname,rm,bend in [('SFsolve','SFpatch','&rm','&bend'),('SFseed','SFprefix','rm','bend'),('SFprefix',None,'&rm','bend')]:
        a=r.index('pub fn '+name+'(');b=r.index('pub fn '+nextname+'(',a) if nextname else r.index('pub const SFTOKDEPTH',a);part=r[a:b]
        start='let mut k=Z168(starts,i) as usize;';assert part.count(start)==1
        ia=part.index(start);ib=part.index('}let c=',ia)+1
        old=part[ia:ib];assert old.count('Z437(')==1 and old.count('k+=1;')==1
        new=f'''let slot=Z168(starts,i);
  if slot<0x80000000u32 {{
   if slot>=16777216 {{let z=SFrelax_token({rm},ct,{bend},i,slot,bc,bt);bc=z.0;bt=z.1;}}
  }}else{{
   let mut k=(slot&0x1fffffffu32) as usize;let end=k.wrapping_add((((slot>>29)&3) as usize).wrapping_add(2));
   while k<end{{let t=Z168(items,k);let z=SFrelax_token({rm},ct,{bend},i,t,bc,bt);bc=z.0;bt=z.1;k+=1;}}
  }}'''
        part=part[:ia]+new+part[ib:];r=r[:a]+part+r[b:]
    at=r.index('pub fn SFsmallmatches(');r=r[:at]+HELPERS+r[at:]
    e=w.write_candidate('r24-609-inline-slot',p.name,r,l,
        'Store a single retained match token directly in each SF position slot; use a tagged offset and packed count only for2-4 matches. Keep exact match order and the original cost relaxation. Empty and single positions avoid the old second offset read and single-item storage.',
        'N observed65.8percentof solver-position visits with one match, plus emptypositions. Earlier R10packed records savedspacebutadded decode work; this representation intentionally removes decoding/indirection for the common single case while keepingmulti-casecost explicit. No claim from bytes alone.',
        {'parent':p.name,'source':'references/round24-public-609/source-receipt.json','cardinality_evidence':'evidence/round24/38085691541/groups-n-native/diagnostics/r24-groups/receipt.json','prior_negative':'docs/research/optimization-methods.md','proof':'Producer and consumer representations changed together. Old Lean file is DRAFT until exact new extraction and helper/loop migration.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]+[e];s['description']='R24 O real inline-single slot representation on frozen609quality. Native full28file token/output equality first; no packing-only microbenchmark or inherited proof claim.'
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]];(E/'slot-o-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    rng=random.Random(2425);checks=0
    for count in range(5):
        for _ in range(10000):
            ts=[16777216+rng.randrange(8388608) for _ in range(count)];begin=rng.randrange(536870912);first=ts[0] if ts else 0
            slot=first if count<2 else 0x80000000|((count-2)<<29)|begin
            if slot<0x80000000:decoded=[]if slot==0 else[slot]
            else:
                assert (slot&0x1fffffff)==begin and ((slot>>29)&3)+2==count;decoded=ts[:]
            assert decoded==ts;checks+=1
    plan={'gap':'SF consumers spend work loading two offsets and then an item even for a single match; actualcounts show65.8percent single and9.7percent empty visits.',
        'change':'One-word inline common case with tagged multi offset/count. Search, token order, cost arithmetic and encoder preserved; additional multi decode overhead is a risk to measure.',
        'minimum':'50000 finite encoding/decoding layout models, then actual28-file native full token/encoder/decode parity; only after parity perform original full paired timing and generated boundary cases.',
        'decision':'Any changedtoken or decode failure blocks equivalence claims and triggers producer/consumer diagnosis. True whole-time gain justifies proofmigration; lower memory alone does not.',
        'cost_cap_runner_minutes':15,'model_checks':checks,'large_index_behavior':'If multi storage offset reaches2^29, preserve the first candidate instead of truncating a pointer; universal token equivalence is not claimed. Output still passes through original validated emitter, whose full proof must be rerun.',
        'evidence':'evidence/round24/<run>/slot-o-native/diagnostics'}
    (E/'preflight-o.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e['name'],checks)
if __name__=='__main__':main()
