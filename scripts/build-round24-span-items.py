"""Remove already-cheaper overlap once while retaining SF match items."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
HELPERS='''#[inline(always)]
pub fn SFspanitem(t:u32,lo:usize)->u32 {(t.wrapping_sub(16777216)&8388607)|(((lo as u32)&511)<<23)}
#[inline(always)]
pub fn SFsmallspan(best:&[u32;8],count:usize,j:usize,ct:&[u32;1024],allow:bool)->usize {
 let t=best[j%8];let price=ct[(best[(j%4).wrapping_add(4)%8]as usize).wrapping_add(512)%1024];let l=SFlen(t);let mut k=0usize;let mut low=3usize;
 while k<count&&k<4 {let v=best[k%8];let vp=ct[(best[(k%4).wrapping_add(4)%8]as usize).wrapping_add(512)%1024];let vl=SFlen(v);
  if k!=j&&vp<=price&&vl>=l&&(vp<price||vl>l||k<j){return 0;}
  if allow&&vp<price&&vl<259 {low=Z457(low,vl+1);}k+=1;
 }low
}
#[inline(always)]
pub fn SFfastspan(best:&[u32;4],codes:&[usize;4],count:usize,j:usize,ct:&[u32;1024],allow:bool)->usize {
 let price=ct[codes[j%4].wrapping_add(512)%1024];let l=SFlen(best[j%4]);let mut k=0usize;let mut low=3usize;
 while k<count&&k<4 {let vp=ct[codes[k%4].wrapping_add(512)%1024];let vl=SFlen(best[k%4]);
  if k!=j&&vp<=price&&vl>=l&&(vp<price||vl>l||k<j){return 0;}
  if allow&&vp<price&&vl<259 {low=Z457(low,vl+1);}k+=1;
 }low
}
'''
def model():
    rng=random.Random(2450)
    for case in range(12000):
        n=rng.randrange(1,5);ls=[rng.randrange(3,259)for _ in range(n)];ps=[16*rng.randrange(0,30)for _ in range(n)];cost=[rng.randrange(0,4096)for _ in range(259)];lc=[16*rng.randrange(0,21)for _ in range(259)]
        alive=[j for j in range(n)if not any(k!=j and ps[k]<=ps[j]and ls[k]>=ls[j]and(ps[k]<ps[j]or ls[k]>ls[j]or k<j)for k in range(n))]
        before=[];after=[]
        for j in alive:
            lo=max([3]+[ls[k]+1 for k in range(n)if ps[k]<ps[j]])
            a=min((((cost[x]+lc[x]+ps[j])<<32)|x,j)for x in range(3,ls[j]+1));before.append(a)
            if lo<=ls[j]:after.append(min((((cost[x]+lc[x]+ps[j])<<32)|x,j)for x in range(lo,ls[j]+1)))
        assert min(before)==min(after),(case,ls,ps,alive)
    return 12000
def main():
    cases=model();p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    for name,mod,call in [('SFsmallmatches',8,'SFsmallspan(&best,count,c,ct,allow)'),('SFmorematches',4,'SFfastspan(&best,&codes,count,c,ct,allow)')]:
        old=fn(r,name);part=old;needle='let mut p=a;';assert part.count(needle)==1;part=part.replace(needle,'let allow=e.wrapping_sub(a)<=4194303;'+needle)
        needle=f'if SF{"smallkeep(&best,count,c,ct)"if mod==8 else"fastkeep(&best,&codes,count,c,ct)"}{{Z430(items,best[c%{mod}]);}}';assert part.count(needle)==1
        part=part.replace(needle,f'let low={call};if low>0{{Z430(items,SFspanitem(best[c%{mod}],low));}}');r=r.replace(old,part)
    for name in ['SFsolve','SFseed','SFprefix']:
        old=fn(r,name);part=old;needle='let t=Z168(items,k);let l=SFlen(t);';assert part.count(needle)==1;part=part.replace(needle,'let item=Z168(items,k);let t=(item&8388607).wrapping_add(16777216);let low=Z457(3,(item>>23)as usize);let l=SFlen(t);')
        assert part.count('Z440(&rm,ct,i,3,')==1 if name!='SFseed' else part.count('Z440(rm,ct,i,3,')==1
        part=part.replace('ct,i,3,Z248(10,l)','ct,i,low,Z248(10,l)').replace('i,11,l,dcs','i,Z457(11,low),l,dcs');assert part!=old;r=r.replace(old,part)
    r+='\n'+HELPERS
    e=w.write_candidate('r24-609-span-items',p.name,r,l,'At the existing per-position dominance-filter pass, attach the first length not covered by any strictlycheaper retainedoffer. Store this lower bound in9sparebits afterremoving the redundanttoken tag, then query only the remaininglengthspan inordinary/seed/prefix SFsolvers. Preserve originalitemorder andfull-matchdominance ties.','Unlike later perquery cache/sorting or RFspan work, the lowerbound is computed in the alreadyexisting4slotfilter and reused acrossSFtrials. Windows above4194303retainlo3; the boundedproducer price/path reasoning avoids relying on cost-addition monotonicity acrossU32wrap. Actualtokens/finitechecks still required; no universal equality claim.',{'parent':p.name,'prior_different':'evidence/round18/rf-ag-ah-decision.json','query_counts':'evidence/round24/38085691541/groups-n-native/diagnostics/r24-groups/receipt.json','proof':'DRAFT; newloopaccumulator andencodeditems need actualextraction andfullgate.'});e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_span_counts=True,description='AX lower-lengthdomain reuse computed insideexistingSFdominancefilter. Finiteorder/tie model, actualencodedbounds/coverage, whole28filetoken/encoder/decode. No extraperquery sorting or assumedtimegain.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('span-ax-native',s),('preflight-ax',{'gap':'ActualSFqueries overlaplengthdomains when two ormore non-dominateddistances survive. Existing53.1Mpricegroups/18.3Mitemuses still repeat cheapercoveredprefixes; maintenance-heavy caches regressed.','change':'Fuse lowerboundcalculation withcurrentdominancefilter, store9bitlo inmatchitem, retainexistingmatchorder andshortestties. Keep lo3forlargewindows where modular-cost monotonicity cannotbe assumed.','minimum':f'{cases}finite randomizedprice/length/tie comparisons plusactualruntimebounds/counts andoriginal28filetoken/encoder/decode parity.','decision':'Counterexample stops timing and diagnoseswrap/tie/consumerinterface. Sufficientactualdomainreduction andparity earn originalpairedtime; recordcounts alone notpromotion.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/span-ax-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'],cases)
if __name__=='__main__':main()
