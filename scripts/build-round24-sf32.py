"""Guarded32bit SF cost/stamp representation with explicit circular tie order."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
HELPERS='''
pub fn S32eligible(ct:&[u32;1024],n:usize,lambda:usize)->bool {
 if lambda!=0 || n>524287 {return false;}
 let mut j=0usize;while j<1024 {let v=ct[j];if v&15!=0 || v>512 || (j>=768 && v>240){return false;}j+=1;}
 true
}
#[inline(always)]
pub fn S32min(a:u32,b:u32)->u32 {if a<b{a}else{b}}
#[inline(always)]
pub fn S32put(rm:&mut[u32;2560],i:usize,c:u32) {
 let s=i%512;let v=(c<<9)|(s as u32);rm[s]=v;
 let m2=S32min(v,rm[i.wrapping_add(1)%512]);rm[512+s]=m2;
 let m4=S32min(m2,rm[512+i.wrapping_add(2)%512]);rm[1024+s]=m4;
 let m8=S32min(m4,rm[1024+i.wrapping_add(4)%512]);rm[1536+s]=m8;
 let m16=S32min(m8,rm[1536+i.wrapping_add(8)%512]);rm[2048+s]=m16;
}
#[inline(always)]
pub fn S32linear(rm:&[u32;2560],a:usize,b:usize)->u32 {
 if a>b || b>=512 || b-a>=32 {return 4294967295;}
 let span=b-a+1;let k=Z396(span);let p=1usize<<((k%8)as u32);let base=k.wrapping_mul(512);
 S32min(rm[base.wrapping_add(a)%2560],rm[base.wrapping_add(b.wrapping_add(1).wrapping_sub(p))%2560])
}
#[inline(always)]
pub fn S32relative(v:u32,i:usize)->u32 {(v&0xfffffe00)|((v&511).wrapping_sub((i%512)as u32)&511)}
#[inline(always)]
pub fn S32range(rm:&[u32;2560],i:usize,lo:usize,hi:usize)->u32 {
 if lo>hi || hi-lo>=32 {return 4294967295;}
 let a=i.wrapping_add(lo)%512;let b=i.wrapping_add(hi)%512;
 if a<=b{S32relative(S32linear(rm,a,b),i)}else{S32min(S32relative(S32linear(rm,a,511),i),S32relative(S32linear(rm,0,b),i))}
}
#[inline(always)]
pub fn S32add(v:u32,lc:u32,dc:u32)->u32 {
 let c=(v>>9).wrapping_add(lc>>4).wrapping_add(dc>>4);
 if c<8388608{(c<<9)|(v&511)}else{4294967295}
}
pub fn S32short(rm:&[u32;2560],ct:&[u32;1024],i:usize,hi:usize,dc:u32,best0:u32)->u32 {
 let mut best=best0;let mut x=3usize;
 while x<=hi && x<11 {let v=rm[i.wrapping_add(x)%512];let rel=(v&0xfffffe00)|(x as u32);best=S32min(best,S32add(rel,ct[x%1024],dc));x+=1;}best
}
pub fn S32long(rm:&[u32;2560],ct:&[u32;1024],bend:&[u32;512],i:usize,hi:usize,dc:u32,best0:u32)->u32 {
 let mut best=best0;let mut x=11usize;let mut it=0usize;
 while it<32 && x<=hi && x<259 {let e=Z248(Z457(bend[x%512]as usize,x),hi);let v=S32range(rm,i,x,e);best=S32min(best,S32add(v,ct[x%1024],dc));x=e.wrapping_add(1);it+=1;}best
}
pub fn SFsolve32(input:&[u8],a:usize,e:usize,items:&[u32],starts:&[u32],ct:&[u32;1024])->Vec<u32> {
 let n=e.wrapping_sub(a);let mut ch=Z182(n);let mut i=n;let mut rm=[0u32;2560];let mut bend=[0u32;512];Z330(&mut bend);S32put(&mut rm,n,0);
 while i>0 {i-=1;let lit=Z332(input,a.wrapping_add(i))as u32;
  let c=(rm[i.wrapping_add(1)%512]>>9).wrapping_add(ct[(lit as usize).wrapping_add(768)%1024]>>4);let mut bc=(c<<9)|1;let mut bt=lit;
  let mut k=Z168(starts,i)as usize;let end=Z168(starts,i.wrapping_add(1))as usize;
  while k<end {let t=Z168(items,k);let l=SFlen(t);let d=SFdist(t);let dc=ct[Z353(d).wrapping_add(512)%1024];
   let v=S32short(&rm,ct,i,Z248(10,l),dc,bc);let v=S32long(&rm,ct,&bend,i,l,dc,v);
   if v<bc {bc=v;bt=SFmt(d,(v&511)as usize);}k+=1;
  }S32put(&mut rm,i,bc>>9);Z304(&mut ch,i,bt);
 }ch
}
pub fn SFsolve(input:&[u8],a:usize,e:usize,seam:usize,items:&[u32],starts:&[u32],ct:&[u32;1024],lambda:usize)->Vec<u32> {
 if S32eligible(ct,e.wrapping_sub(a),lambda){SFsolve32(input,a,e,items,starts,ct)}else{SFsolve64(input,a,e,seam,items,starts,ct,lambda)}
}
'''
def model():
    rng=random.Random(243232);count=0
    for n in [1,31,258,511,512,513,1023,2049,4097,8193]:
        costs=[rng.choice([rng.randrange(8388608),rng.randrange(8)])for _ in range(n+1)];rm=[0]*2560
        def put(i,c):
            s=i%512;v=c*512+s;rm[s]=v
            for k in range(1,5):v=min(v,rm[(k-1)*512+(i+2**(k-1))%512]);rm[k*512+s]=v
        def linear(a,b):
            k=min(4,(b-a+1).bit_length()-1);return min(rm[k*512+a],rm[k*512+b+1-2**k])
        def rel(v,i):return v&0xfffffe00|(((v&511)-(i%512))&511)
        put(n,costs[n])
        for i in range(n-1,-1,-1):
            for _ in range(8):
                lo=rng.randint(1,min(258,n-i));hi=rng.randint(lo,min(lo+31,n-i,258));a=(i+lo)%512;b=(i+hi)%512
                got=rel(linear(a,b),i)if a<=b else min(rel(linear(a,511),i),rel(linear(0,b),i))
                expect=min((costs[i+x]<<9)|x for x in range(lo,hi+1));assert got==expect,(i,lo,hi,got,expect);count+=1
            put(i,costs[i])
    return count
def main():
    count=model();p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();needle='pub fn SFsolve(';assert r.count(needle)==1;r=r.replace(needle,'pub fn SFsolve64(',1)+HELPERS
    e=w.write_candidate('r24-609-sf32',p.name,r,l,'For lambda0 and explicitly bounded16-unit cost tables, scale costs to bits and pack23costbits+9circular-positionbits in a2560xU32 range-min table. Split queries at the circular boundary and convert stamps to relative lengths before comparing, preserving absolute tie order. All ineligible cases use originalSFsolve64; SFheavy seed/prefix unchanged.','A representation change in the ordinary SF solver, not altered prices or larger query groups. The guard checks lambda, span and cost-table bounds/divisibility. Cost/state footprint drops32KiBallocated/20KiBused to10KiB. Range-boundary model precedes realtoken/encoder checks; no inferred speed from size.',{'parent':p.name,'profile':'evidence/round24/38080823460/profile-c-native/diagnostics/r18-functions/functions.json','proof':'DRAFT: new guarded solver and helpers need exact extraction/termination proofs/fullgate. Finite model is not a complete equivalence proof.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_sf32_counts=True,description='AJ guarded32bit ordinarySFsolver. Finite circularstamp/tie model, actualeligibility coverage and original28fileparity before timing; heavytrial solver remains64bit.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('sf32-aj-native',s),('preflight-aj',{'gap':'OrdinarySFsolver remains measuredcost after matcher work. Its generic64bit state includes an absolute position and16scaledcosts; a bounded lambda0subdomain may use smaller state without losingchoices.','change':'23bit integerbitcost+9bitcircularstamp, explicitwrap split andrelative tie comparison, guardedfallback. No routebyfilename or changedpricing objective.','minimum':f'{count}finite randomized RMQ queries across wraps/ties/extreme23bitcosts, actualeligiblecalls/positions, original28fileencoder/token/decode.','decision':'Any token difference diagnoses scaling, circular tie or bounds before performance. Usefulcoverage with parity earns originaltotal-time; fullgate only on exactpairs.','model_cases':count,'model_scope':'RMQrepresentation/query only, not endtoendRust correctness or all-inputequivalence.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/sf32-aj-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'],count)
if __name__=='__main__':main()
