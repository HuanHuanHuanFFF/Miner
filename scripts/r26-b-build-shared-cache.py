"""Build one complete base-owner/SF-consumer experiment from exact public628."""
from pathlib import Path
import argparse
import datetime as dt
import hashlib
import importlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round25-public-628'
OUT=ROOT/'candidates/r26-b-628-shared-cache'
E=ROOT/'evidence/round26/route-b'
EXPECTED={'parse.rs':'784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14',
          'Parse.lean':'7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e'}

OWNED=['Z144','Z185','Z308','Z336','Z180','Z169','Z297','Z303','Z273','Z296',
       'Z313','Z311','Z310','Z312','Z317','Z315','Z316','Z318','Z179','Z183',
       'Z337','Z416','Z462','Z463','Z464','Z465','Z466','SFbase']
OWN_ARGS='cache_mp:&mut Vec<u32>,cache_mb:&mut Vec<u32>,cache_fmt:&mut usize'
READ_ARGS='cache_mp:&[u32],cache_mb:&[u32],cache_fmt:usize'
OWN_NAMES='cache_mp,cache_mb,cache_fmt'
READ_NAMES='cache_mp,cache_mb,cache_fmt'

HELPERS='''
pub fn r26_b_cache_valid(input:&[u8],mp:&[u32],mb:&[u32],fmt:usize)->bool {
 fmt<2&&mp.len()>0&&mp.len().wrapping_sub(1)==input.len()&&(Z168(mp,input.len())as usize)<=mb.len()
}
pub fn r26_b_offer(x:u32,fmt:usize,cap:usize)->(usize,usize) {
 let l=if fmt==0{3+((x>>15)&255)as usize}else{let v=(x>>20)as usize;if v>=512{v-512}else{v}};
 (Z248(Z248(l,258),cap),((x&32767)+1)as usize)
}
pub fn r26_b_small_cached(input:&[u8],prev:&[u32],orig:&[u32],ct:&[u32;1024],a:usize,e:usize,items:&mut Vec<u32>,starts:&mut Vec<u32>,cache_mp:&[u32],cache_mb:&[u32],cache_fmt:usize) {
 if !r26_b_cache_valid(input,cache_mp,cache_mb,cache_fmt){SFsmallmatches(input,prev,orig,ct,a,e,items,starts);return;}
 let mut p=a;
 while p<e {
  Z430(starts,items.len()as u32);let mut best=[0u32;8];let ot=Z168(orig,p.wrapping_sub(a));let mut count=0usize;
  if ot!=0{count=SFsmalladd(&mut best,count,ot);}
  let mut k=Z168(cache_mp,p)as usize;let stop=Z248(Z168(cache_mp,p.wrapping_add(1))as usize,cache_mb.len());
  while k<stop {
   let pair=r26_b_offer(Z168(cache_mb,k),cache_fmt,e.saturating_sub(p));let l=pair.0;let d=pair.1;
   if l>=3&&d>0&&d<=p{count=SFsmalladd(&mut best,count,SFmt(d,l));}k+=1;
  }
  let mut c=0usize;while c<count&&c<4{if SFsmallkeep(&best,count,c,ct){Z430(items,best[c%8]);}c+=1;}p+=1;
 }Z430(starts,items.len()as u32);
}
pub fn r26_b_more_cached(input:&[u8],prev:&[u32],orig:&[u32],ct:&[u32;1024],a:usize,e:usize,items:&mut Vec<u32>,starts:&mut Vec<u32>,cache_mp:&[u32],cache_mb:&[u32],cache_fmt:usize) {
 if !r26_b_cache_valid(input,cache_mp,cache_mb,cache_fmt){SFmorematches(input,prev,orig,ct,a,e,items,starts);return;}
 let mut p=a;
 while p<e {
  Z430(starts,items.len()as u32);let mut best=[0u32;4];let mut codes=[0usize;4];let ot=Z168(orig,p.wrapping_sub(a));let mut count=0usize;
  if ot!=0{count=SFfastadd(&mut best,&mut codes,count,ot);}
  let mut k=Z168(cache_mp,p)as usize;let stop=Z248(Z168(cache_mp,p.wrapping_add(1))as usize,cache_mb.len());
  while k<stop {
   let pair=r26_b_offer(Z168(cache_mb,k),cache_fmt,e.saturating_sub(p));let l=pair.0;let d=pair.1;
   if l>=3&&d>0&&d<=p{count=SFfastadd(&mut best,&mut codes,count,SFmt(d,l));}k+=1;
  }
  let mut c=0usize;while c<count&&c<4{if SFfastkeep(&best,&codes,count,c,ct){Z430(items,best[c%4]);}c+=1;}p+=1;
 }Z430(starts,items.len()as u32);
}
pub fn r26_b_seed_shared(input:&[u8],out:&mut[u32])->usize {
 if !SFenabled(input)||input.len()==40000{return seed_parse(input,out);}
 let mut cache_mp=Vec::new();let mut cache_mb=Vec::new();let mut cache_fmt=2usize;
 let nt=r26_b_SFbase(input,out,&mut cache_mp,&mut cache_mb,&mut cache_fmt);
 let plan=if r26_b_cache_valid(input,&cache_mp,&cache_mb,cache_fmt){r26_b_SFshape(input,out,nt,&cache_mp,&cache_mb,cache_fmt)}else{SFshape(input,out,nt)};
 Z167(input,&plan,out)
}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def signature(body,rename,extra):
    old=re.search(r'pub fn ([A-Za-z0-9_]+)\(',body).group(1)
    body=body.replace('pub fn '+old+'(','pub fn '+rename+'(',1)
    brace=body.index('{');paren=body.rfind(')',0,brace)
    assert paren>=0
    prefix=body[:paren].rstrip()
    if prefix.endswith(','):
        prefix+=' '+extra
    else:
        prefix+=','+extra
    return prefix+body[paren:]


def calls(body,names,extra,prefix='r26_b_'):
    # Rewrite only function invocations; nested calls are processed from right.
    hits=[]
    for m in re.finditer(r'\b('+ '|'.join(sorted(names,key=len,reverse=True))+r')\(',body):
        start=m.end()-1;depth=1;end=start+1
        while depth:
            depth+=(body[end]=='(')-(body[end]==')');end+=1
        hits.append((m.start(),m.group(1),start,end-1))
    for at,name,start,end in reversed(hits):
        body=body[:end]+','+extra+body[end:]
        body=body[:at]+prefix+body[at:]
    return body


def build():
    raw={f:(BASE/f).read_bytes()for f in EXPECTED}
    assert {f:sha(b)for f,b in raw.items()}==EXPECTED
    source=raw['parse.rs'].decode();fn=importlib.import_module('prepare-round24-extract-repro').fn
    additions=[];clones={}
    for name in OWNED:
        original=fn(source,name)
        body=signature(original,'r26_b_'+name,OWN_ARGS)
        body=calls(body,set(OWNED),OWN_NAMES)
        if name in ('Z144','Z185','Z308'):
            tail='\n if cache_mp.len()==0{*cache_mp=mp;*cache_mb=mb;*cache_fmt=0;}\n'
            assert 'let mut mp:'in body and 'let mut mb:'in body
            body=body[:-1]+tail+'}'
        elif name=='Z336':
            tail='\n if cache_mp.len()==0{*cache_mp=mstart;*cache_mb=mc;*cache_fmt=1;}\n'
            assert 'let mut mstart:'in body and 'let mut mc:'in body
            body=body[:-1]+tail+'}'
        additions.append(body);clones[name]={'original_sha256':sha(original.encode()),'clone_sha256':sha(body.encode())}
    for name in ('SFbatch','SFheavy','SFshape'):
        original=fn(source,name)
        body=signature(original,'r26_b_'+name,READ_ARGS)
        body=calls(body,{'SFbatch','SFheavy'},READ_NAMES)
        body=calls(body,{'SFsmallmatches'},READ_NAMES,prefix='r26_replace_')
        body=body.replace('r26_replace_SFsmallmatches(', 'r26_b_small_cached(')
        body=calls(body,{'SFmorematches'},READ_NAMES,prefix='r26_replace_')
        body=body.replace('r26_replace_SFmorematches(', 'r26_b_more_cached(')
        if name=='SFshape':
            old='let prev=SFprev(input);'
            assert body.count(old)==1
            body=body.replace(old,'let prev=if r26_b_cache_valid(input,cache_mp,cache_mb,cache_fmt){Vec::new()}else{SFprev(input)};',1)
        additions.append(body);clones[name]={'original_sha256':sha(original.encode()),'clone_sha256':sha(body.encode())}
    extra='\n// R26 B complete ownership transfer and SF record consumer.\n'+HELPERS+'\n'+'\n\n'.join(additions)+'\n'
    start=source.rindex('pub fn parse(input:&[u8],out:&mut[u32])->usize {')
    body=source[start:]
    old='seed_parse(input,out)';new='r26_b_seed_shared(input,out)'
    assert body.count(old)==1
    rust=source[:start]+body.replace(old,new,1)+extra
    assert rust[:-len(extra)].replace(new,old,1)==source
    # All old functions other than final parse remain exactly preserved.
    assert all(fn(rust,n)==fn(source,n) for n in OWNED+['SFbatch','SFheavy','SFshape'])
    # Every propagation call must contain real owner arguments, never a free stub.
    for body in additions:
        assert not re.search(r'\br26_b_(?:'+ '|'.join(OWNED)+r')\([^)]*\)\s*;',body) or 'cache_mp' in body
    files={'parse.rs':rust.encode(),'Parse.lean':raw['Parse.lean']}
    assert all(0<len(b)<=524288 for b in files.values())
    manifest={'candidate':OUT.name,'parent':'public628','parent_hashes':EXPECTED,
        'hashes':{f:sha(b)for f,b in files.items()},
        'mechanism':'Retain the first original full-position base matching offsets/records through explicit perparse owned Vec transfer. Preserve every original seed search/DP/pass/configuration. SF small/heavy collectors consume those real records with span clipping, same-code longest retention and original price dominance, rather than perform fresh full-position-chain byte matching. Missing cache paths run originalSF. Omit SFprev only for a valid retained cache. OriginalE/RF and validated final emission remain.',
        'difference_from_old_work':'The R18 weak shared seed changed/weakens its first-pass seed or repeats matching to restore strongseed. This version preserves the complete strong original base parser, retaining its already-created vectors until the actualSF consumer. R24 next-actions explicitly left this producer/consumer route unimplemented. Actual cache maintenance, ownership lifetime and consumption are part of this parser; not a free cached oracle.',
        'cache_policy':{'lifetime':'Local to one r26_b_seed_shared call; destroyed afterSF and beforeRF. No mutableglobalstate, no cross-input reuse.',
                        'producer':'First complete generator reached through the unchanged base configuration; Z144/Z185/Z308 transfer mp/mb, Z336 transfers mstart/mc; other paths keep emptycache and originalfallback.',
                        'representation':'Raw original offsets and records; format0 root length3+bits15..22 / distlow15+1, format1 q9 lengthbits20.. / distlow15+1. Eachoffer is clipped to258 and currentSF interval.',
                        'consumer':'Originalseed first, then retained base record order, originalfour-code longest/pricefilter. SFlookup/depth chain removed only on full validcache. This changes the match pool and may changequality.'},
        'attribution':{'source_receipt':'references/round25-public-628/source-receipt.json','author_hotkey':'5DM8HSJ17XPGKYTERQUbQuhqWJm3RtpJqTSUH7Dn8m5MVuJ6',
                       'underlying_seed_source':'references/round24-public-609/source-receipt.json','underlying_seed_author_hotkey':'5DPo51y7zmk2WfnkvU4MxAqw66ouW9KonrUGguLRWtPqiP9t'},
        'proof_status':'INHERITED_LEAN_UNCHANGED_DRAFT_MISSING_NEW_OWNER_AND_CONSUMER_SPECS',
        'semantic_status':'Intentionalmatch pool/tokenchanges; originalstrongseed equivalence, final token validity and originalencoded quality UNKNOWN before cloudexecution.',
        'performance_status':'UNKNOWN; entireproducer/consumer and retainedbuffers included. Extra traversal/larger lifetime may erase savings.',
        'proof_dependency':'Freshclonedfunction extraction, new ownerVec/slice binderstates, looptermination/bounds and finalemission linkage; unchangedLean onlydraft. Originalproof/gate notinherited. Currentproofsize leaves1270B so meaningful declaration pruning/compactfresh proof required without alteringofficiallimits.',
        'source_reversal':'Removeexact extra block and reverse one finalparse seedcall; all public628 source bytes restored.',
        'cloned_functions':clones,'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,indent=2,ensure_ascii=False)+'\n').encode()
    return files,manifest


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    files,manifest=build()
    if args.check:
        assert all((OUT/f).read_bytes()==b for f,b in files.items())
    else:
        OUT.mkdir(exist_ok=False)
        for f,b in files.items():(OUT/f).write_bytes(b)
        plan={'written_utc':dt.datetime.now(dt.timezone.utc).isoformat(),'status':'COMPLETE_SOURCE_PREPARED_NOT_NATIVE_TESTED',
              'gap':'B1SFbase/shape dominate weighted priority model. Actualbase/SF offercoverage remains B2pending; cachecapture is complete strongseed rather than weak sharedseed.',
              'change':'Moveexisting base vectors via explicit ownedparameters through realbaseplanner/route functions, then run realSF collector overretainedrecords with originalpricefilter and fallback.',
              'minimum':'AfterB2coverage, rootnative original28fileencoder/decode, with exact628/R24B references. Require helper/strongseed originalbyte checks on actualrunner before using any timeclaim.',
              'decision':'Nativequality loss/encoderfallback or poorcoverage pauses thisexactvariant; useful twoaxis region earns original pairedtotal-time. No algebraic sums of priorcomponent speeds.',
              'runner_cost_cap_minutes':20,'local_source_preparation_budget_minutes':90,
              'first_valid_test':'Complete producerandconsumer included inoneactualparser; no emptystub/freecache. Original encoder/native before originaltiming, proofs missing and fullgate notready.',
              'evidence':'evidence/round26/route-b/match-sharing-plan.md, futureB2sharing and native originalencoder receipts'}
        (E/'shared-cache-predeclared.json').write_bytes((json.dumps(plan,indent=2,ensure_ascii=False)+'\n').encode())
    print(json.dumps({'status':'VERIFIED_SOURCE_REVERSAL_AND_ORIGINAL_FUNCTION_PRESERVATION_ONLY','candidate':OUT.name,
                      'hashes':manifest['hashes'],'rust_bytes':len(files['parse.rs']),'owner_function_clones':len(OWNED),
                      'scope':'No Rustexecution, performance or correctnessproof. Completecandidate remains draft.'},indent=2))


if __name__=='__main__':main()
