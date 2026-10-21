"""Two controlled SF mechanisms: exact fixed points and hot-query specialization."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
SAME='''pub fn SFsame(a:&[u32],b:&[u32])->bool {
 if a.len()!=b.len(){return false;}
 let mut i=0usize;let mut equal=true;
 while i<a.len() && equal {if Z168(a,i)!=Z168(b,i){equal=false;}i+=1;}equal
}
'''
def main():
    p=ROOT/'candidates/r24-609-once';base=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();entries=[]
    r=base;names=['Z437','Z440','Z322','Z443']
    for n in names:
        needle='pub fn '+n+'(';assert r.count(needle)==1;r=r.replace(needle,'#[inline(always)]\n'+needle)
    assert all(fn(r,n)==fn(base,n)for n in names)
    e=w.write_candidate('r24-609-query-inline',p.name,r,l,'Force inline only the four nested SF query/update helpers Z437/Z440/Z322/Z443, leaving algorithm, prices, matchers and route wrappers untouched.','Separate hypothesis from AC route specialization and AJ32bit representation. Original-template code identity comes before timing; changed machine code alone does not prove a gain.',{'parent':p.name,'changed_helpers':names,'profile':'evidence/round24/38080823460/profile-c-native/diagnostics/r18-functions/functions.json','proof':'DRAFT until exact fresh complete gate.'});e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once');entries.append(e)
    r=base;old=fn(r,'SFshape');part=old
    needle='let ts=if SFweak(input){let mut ts=Vec::new();SFcopy(out,0,nt,&mut ts);SFheavy(input,&ts,&prev)}else{SFbatch(input,out,nt,&prev)};'
    assert part.count(needle)==1
    part=part.replace(needle,'let mut stalled=false;let ts=if SFweak(input){let mut ts=Vec::new();SFcopy(out,0,nt,&mut ts);let next=SFheavy(input,&ts,&prev);if level==1||level==2{stalled=SFsame(&ts,&next);}next}else{SFbatch(input,out,nt,&prev)};')
    needle='let ts=if level==1||level==2{SFheavy(input,&ts,&prev)}else{ts};';assert part.count(needle)==1
    part=part.replace(needle,'let ts=if (level==1||level==2) && !stalled {let next=SFheavy(input,&ts,&prev);if level==2{stalled=SFsame(&ts,&next);}next}else{ts};')
    needle='let ts=if level==2{SFheavy(input,&ts,&prev)}else{ts};';assert part.count(needle)==1;part=part.replace(needle,'let ts=if level==2 && !stalled {SFheavy(input,&ts,&prev)}else{ts};')
    r=r.replace(old,SAME+'\n'+part)
    e=w.write_candidate('r24-609-heavy-fixedpoint',p.name,r,l,'Skip only a following full SFheavy invocation after a prior SFheavy returned the identical token vector, with the same input and prev. Equality is checked only when a following heavy call exists. Batch-to-heavy is never assumed to share a fixed point.','R24 tiny convergence and R18 exact-price DP repeats found no saved work; this is the distinct SFweak-to-heavy transition, which can call the same full transformation twice. First measure actual equal-state coverage; zero coverage stops timing.',{'parent':p.name,'prior_different_negative':['evidence/round24/38082319463/refine-f-native/diagnostics/r24-tiny-counts/receipt.json','evidence/round18/repeat-e-decision.json'],'proof':'DRAFT; finite parity and fixed-state reasoning do not replace original obligation.'});e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once');entries.append(e)
    s=json.loads((E/'inline-ac-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]+entries;s.update(r24_expected_candidates=2,r24_compile_identity=['once','once-shadow',entries[0]['name']],r24_heavy_fixed_counts=True,native_encoder_references=['public609','once'],description='AP two independentSF hypotheses: four hot-helperinline attributes with exactcompileridentity; skip repeatedfullheavy only after exactfixedstate, recording actualchecks. Both need original28fileparity; no new content or length rule.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('sf-ap-native',s),('preflight-ap',{'gap':'Positive highquality improvements remain too small. SFsolver occupies measured time; inlining boundary is not isolated by AJ. Repeatedheavy transformation may have exactfixedpoints, but current coverage is unknown.','change':'Two independent candidates, only four attributes versus exacttoken equality stopping before another identicalheavy transform. No approximation, route table edits or assumed repeat.','minimum':'Original28file encoder/token/decode parity, same-source compiler shadow and candidatecode sections, actualfixedpoint checks/calls.','decision':'Identicalcode stops inline timing; zero actualfixedpoint stops fixedpoint timing. Usefulcoverage and parity earn one originalpaired screen; nonparity diagnoses before advancement.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/sf-ap-native/diagnostics','historical_rejection':'Exact-price cache remains paused: R18 found zero identical prices and the actual Z308 core is unchanged, per revisit-core-comparison.json. No redundant cache implementation or cloud rerun.'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print([x['name']for x in entries])
if __name__=='__main__':main()
