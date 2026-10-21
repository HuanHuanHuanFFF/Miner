"""A single exact-source prefix-cache quality-restoration control."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r26-b-628-shared-cache-fix1'
ORIGINAL=ROOT/'references/round25-public-628'
OUT=ROOT/'candidates/r26-b-628-cache-hint'
E=ROOT/'evidence/round26/route-b'
EXPECTED='582c3ea7236dfaa93a801a265713e3c96175d6978d895e62a9bea024fbdd39ac'

KNOWN='''pub fn r26_b_cache_known(input:&[u8],mp:&[u32],mb:&[u32],fmt:usize,p:usize,d:usize,cap:usize,known0:usize)->usize {
 if !r26_b_cache_valid(input,mp,mb,fmt){return known0;}
 let mut known=known0;let mut k=Z168(mp,p)as usize;let end=Z248(Z168(mp,p.wrapping_add(1))as usize,mb.len());
 while k<end&&known<cap {
  let offer=r26_b_offer(Z168(mb,k),fmt,cap);
  if offer.1==d&&offer.0>known{known=offer.0;}k+=1;
 }known
}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def build():
    raw=(BASE/'parse.rs').read_bytes();assert sha(raw)==EXPECTED
    base=raw.decode();orig=(ORIGINAL/'parse.rs').read_text()
    fn=importlib.import_module('prepare-round24-extract-repro').fn
    signature=importlib.import_module('r26-b-build-shared-cache').signature
    audit=importlib.import_module('r26-b-fix-shared-cache')
    copies=[]
    for name in ('SFsmallmatches','SFmorematches'):
        original=fn(orig,name)
        body=signature(original,'r26_b_'+name+'_hint','cache_mp:&[u32],cache_mb:&[u32],cache_fmt:usize')
        old='let known=SFknown(ot,d,cap);'
        new='let known=r26_b_cache_known(input,cache_mp,cache_mb,cache_fmt,p,d,cap,SFknown(ot,d,cap));'
        assert body.count(old)==1
        body=body.replace(old,new,1)
        copies.append(body)
    source=base
    substitutions=[('r26_b_small_cached(input,prev,&orig,&ct,a,e,&mut items,&mut starts,cache_mp,cache_mb,cache_fmt)',
                    'r26_b_SFsmallmatches_hint(input,prev,&orig,&ct,a,e,&mut items,&mut starts,cache_mp,cache_mb,cache_fmt)'),
                   ('r26_b_more_cached(input,prev,&orig,&ct,a,e,&mut items,&mut starts,cache_mp,cache_mb,cache_fmt)',
                    'r26_b_SFmorematches_hint(input,prev,&orig,&ct,a,e,&mut items,&mut starts,cache_mp,cache_mb,cache_fmt)'),
                   ('let prev=if r26_b_cache_valid(input,cache_mp,cache_mb,cache_fmt){Vec::new()}else{SFprev(input)};',
                    'let prev=SFprev(input);')]
    for old,new in substitutions:
        assert source.count(old)==1,old
        source=source.replace(old,new,1)
    addition='\n// R26 B control: original SF match order/pool; only reuse exact-distance verified prefix.\n'+KNOWN+'\n'+'\n'.join(copies)
    source+=addition
    restored=source[:-len(addition)]
    for old,new in substitutions[::-1]:
        at=restored.rfind(new);assert at>=0
        restored=restored[:at]+old+restored[at+len(new):]
    assert restored==base
    spans=audit.spans(source);assert all(n in spans for n in ('r26_b_cache_known','r26_b_SFsmallmatches_hint','r26_b_SFmorematches_hint'))
    files={'parse.rs':source.encode(),'Parse.lean':(BASE/'Parse.lean').read_bytes()}
    assert all(len(b)<=524288 for b in files.values())
    manifest=json.loads((BASE/'manifest.json').read_bytes())
    manifest.update(candidate=OUT.name,parent=BASE.name,hashes={f:sha(b)for f,b in files.items()},
       mechanism='Preserve originalSFprev and exact originalSF chain/depth/order/four-code match pool. On each originalSFmatchlen call, scan retainedbase records for the exactsame distance and raise known only by its clipped verifiedprefix. The originalmatcher performs every remaining byte comparison. Cachelookup, retention and originalchain traversal remain real costs.',
       difference_from_old_work='B3 replaces theSF offerpool and lost524B in all7cachedfiles. This control isolates cross-stage prefix reuse while restoring the complete oldpool. R24 SFchainprefix reused preceding SF-position matches and was negative; this is explicit oldbase vectors on new628 with lookup/lifetime cost, so previousnegative stays relevant and no gain is assumed.',
       semantic_status='Expected strict token/outputidentity with original628 on real28files if retainedprefixes are valid. Full input equivalence notproved; native Z223 integrity and actual equality must test the premise.',
       proof_status='INHERITED_LEAN_UNCHANGED_DRAFT_NEW_CACHE_KNOWN_AND_OWNER_INTERFACE_SPECS_MISSING',
       performance_status='UNKNOWN; exactsource lookup plus rebuiltSFprev may cost more than repeatedbytes. Equality alone doesnotjustify time/fullproof.',
       source_reversal='Remove exactaddition and reverse threeconsumer/SFprev substitutions to restore completefix1source. Fouroriginaltransfer repairs retained; no newcfg/threshold/route change.')
    files['manifest.json']=(json.dumps(manifest,indent=2,ensure_ascii=False)+'\n').encode()
    return files,manifest


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    files,manifest=build()
    if args.check:assert all((OUT/f).read_bytes()==b for f,b in files.items())
    else:
        OUT.mkdir(exist_ok=False)
        for f,b in files.items():(OUT/f).write_bytes(b)
        plan={'gap':'Highretainedoffercoverage didnotpreserveB3quality. Needseparate lostSFpool from prefix-cost reuse, without assuming cachefree oroldnegative irrelevant.',
              'change':'Oneexactdistanceknown hint; completeoldSF chain, budgets, prev and matchpool restored. Originalstrongbase vectorownership unchanged.',
              'minimum':'B4validprefix premise plus actual28file originaltoken/encoderidentity against628. Ifidentityfails diagnoseknown/sourceprefix before timeclaim; ifcostmodel/screen leavesnoheadroom pause standaloneproof.',
              'decision':'Strictidentity confirms the qualityrestoration/control premise only. Reallookup/hitwork and originalpairedtime decide performance. Do not promote countcoverage orstrongseedverification to speed.',
              'runner_cost_cap_minutes':20,'evidence':'evidence/round26/route-b/cache-hint-predeclared.json and future actualnativeidentity/prefixreceipts',
              'proof':'Notadapted/compiled; no formalclaim.'}
        (E/'cache-hint-predeclared.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print(json.dumps({'status':'VERIFIED_SOURCE_REVERSAL_AND_LEXICAL_SPANS_ONLY','candidate':OUT.name,'hashes':manifest['hashes']},indent=2))


if __name__=='__main__':main()
