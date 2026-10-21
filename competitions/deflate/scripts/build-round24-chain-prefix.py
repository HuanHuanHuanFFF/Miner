"""Carry short exact LCPs along the existing SF predecessor chain."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
PREV='''pub fn SFprev(input:&[u8])->Vec<u32> {
 let mut v=Z182(input.len());let mut head=[0u32;65536];let mut p=0usize;
 while p<input.len() {let h=SFhash(input,p)%65536;let old=head[h]as usize;let mut item=0u32;
  if old>0&&old<=p {let j=old-1;let d=p-j;if d<=32768 {let cap=Z248(8,input.len()-p);let hint=SFmatchlen(input,j,p,cap,0);item=(d as u32)|(((hint as u32)&15)<<16);}}
  Z304(&mut v,p,item);head[h]=(p as u32).wrapping_add(1);p+=1;
 }v
}
'''
HELPERS='''#[inline(always)]
pub fn SFparent(prev:&[u32],p:usize)->u32 {
 let d=(Z168(prev,p)&65535)as usize;
 if d>0&&d<=p{(p-d+1)as u32}else{0}
}
#[inline(always)]
pub fn SFchainlen(input:&[u8],prev:&[u32],from:usize,j:usize,p:usize,cap:usize,prior:usize,seed:usize)->usize {
 let hint=((Z168(prev,from)>>16)&15)as usize;let low=Z248(prior,hint);
 if prior!=hint&&low<8&&low<cap{low}else{SFmatchlen(input,j,p,cap,Z457(seed,Z248(cap,low)))}
}
'''
def model():
    rng=random.Random(2461);count=0
    for case in range(20000):
        n=rng.randrange(3,700);alphabet=rng.choice([1,2,4,16,256]);s=bytes(rng.randrange(alphabet)for _ in range(n));p=rng.randrange(2,n);frm=p if case%3==0 else rng.randrange(1,p);j=rng.randrange(frm);cap=rng.randrange(1,min(258,n-p)+1)
        def lcp(a,b,limit):
            k=0
            while k<limit and b+k<n and a+k<n and s[a+k]==s[b+k]:k+=1
            return k
        prior=258 if frm==p else lcp(frm,p,cap);hint=lcp(j,frm,8);low=min(prior,hint);expect=lcp(j,p,cap);seed=rng.randrange(expect+1)
        if prior!=hint and low<8 and low<cap:got=low
        else:
            known=max(seed,min(cap,low));assert s[j:j+known]==s[p:p+known];got=known+lcp(j+known,p+known,cap-known)
        assert got==expect,(case,prior,hint,cap,got,expect);count+=1
    return count
def main():
    count=model();p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();r=r.replace(fn(r,'SFprev'),PREV)
    old=fn(r,'SFlookup');assert old.count('Z168(prev,p)')==1;r=r.replace(old,old.replace('Z168(prev,p)','SFparent(prev,p)'))
    for name in ['SFsmallmatches','SFmorematches']:
        old=fn(r,name);part=old;needle='let mut k=0usize;';assert part.count(needle)==1;part=part.replace(needle,needle+'let mut from=p;let mut prior=258usize;')
        needle='let l=SFmatchlen(input,j,p,cap,known);';assert part.count(needle)==1;part=part.replace(needle,'let l=SFchainlen(input,prev,from,j,p,cap,prior,known);from=j;prior=l;')
        assert part.count('q=Z168(prev,j) as usize;')==1;part=part.replace('q=Z168(prev,j) as usize;','q=SFparent(prev,j) as usize;');r=r.replace(old,part)
    old=fn(r,'SFtinytokens');part=old
    for at in ['p','j']:
        assert part.count('Z168(&prev,'+at+')')==1;part=part.replace('Z168(&prev,'+at+')','SFparent(&prev,'+at+')')
    r=r.replace(old,part)+'\n'+HELPERS
    e=w.write_candidate('r24-609-chain-lcp8',p.name,r,l,'Store a16bitbackwarddistance and capped8byte LCP in the existing32bitSFpredecessor entry. Along achain, unequal knownLCPs belowthecap give the next exactlength; otherwise theirminimum is a verifiedprefix for the originalmatcher. Decode tinytoken consumers too; expiredlinks becomeabsent because no latercurrentposition can use them.','R21relative16storage andR24per-distancecache didnotconfirmgains. Herethe representation enablesa different LCPtransitivity mechanism, withoutlarger cache or globalstate. Precompute costs onunusedpositions may erasequerysavings, so actualper-query equality/counts andtotal-time decide.',{'parent':p.name,'prior_negative':['docs/rounds/round21.md','evidence/round24/analysis-u.json'],'proof':'DRAFT: newhelpers, SFprev dependency order andcapturedchainstate requireactualextraction andfreshfullgate. Finitemodel isnotuniversalRust equivalence.'});e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_chain_prefix_counts=True,description='BD fixed8byte predecessorLCP metadata andtriangle reuse; allconsumers audited includingtinytokens. Eachobservedquery comparedtooriginalmatcher; full28filetoken/encoder/decode beforetime.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('chain-bd-native',s),('preflight-bd',{'gap':'SFquery work stillmaterial; localdistancecache andrangepruning overhead erasedsavings. Existingchain relations offer exacttransitiveprefix information withoutscanningbase-cache vectors.','change':'Same32bitentry storeswindowdistance pluscapped8byteLCP. Unequalunsaturated LCPs yield exactlength; equallowerbounds extendwithoriginalmatcher. Fixedcap isone representation choice, notthresholdsweep.','minimum':f'{count}finite strings/chains/caps/seeds cases, actualeveryquery originalmatcher equality andprecompute/query/shortcut counts, original28filetoken/encoder/decode.','decision':'Any inequality stops timing. Usefulcoverage withparity earns oneoriginaltotal-time screen; ifprecompute ordecodeoverhead erasesgain, stop. Do notclaimdeadline-ready withoutnewgate/frozenconfirmation.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/chain-bd-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'],count)
if __name__=='__main__':main()
