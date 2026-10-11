"""Controlled composition after measured AQ gain and AT's nonadditive quality result."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def main():
    p=ROOT/'candidates/r24-609-root-word-price-proof1';base=(p/'parse.rs').read_text();lean=(p/'Parse.lean').read_text();assert json.loads((p/'VERIFICATION.json').read_bytes())['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED';entries=[]
    packed=(ROOT/'candidates/r24-609-a-packed/parse.rs').read_text();once=(ROOT/'candidates/r24-609-once/parse.rs').read_text();r=base
    for n in ['Z184','Z307','Z314']:
        assert fn(base,n)==fn(once,n);r=r.replace(fn(r,n),fn(packed,n))
    r+='\n'+fn(packed,'APprices')
    e=w.write_candidate('r24-609-stack-packed',p.name,r,lean,'Add the actualAQpackedcost representation to the gatedfaststack, preserving everyexistinginlineattribute andallothermechanisms.','AQisolatedtwo blocks were1.09/1.16percentfaster but owncontrol variedupto0.98percent. This is oneactualcomposition test, not assumedadditivegain or stable10/15evidence.',{'parent':p.name,'component':'candidates/r24-609-a-packed/manifest.json','evidence':'evidence/round24/feedback-ar.json','proof':'DRAFT; acceptedparent plusAPhelper hasnot beenfreshfullgated.'});e.update(anchor='public609',comparison_baseline='fast-stack',native_decode_reference='fast-stack',expected_equivalent_to='fast-stack');entries.append(e)
    r=base
    for n in ['SFsmallmatches','SFmorematches']:
        old=fn(r,n);part=old
        for a,b in [('let mut k=0usize;','let mut k=0usize;let limit=depth.saturating_add(depth);let mut longest=if ot==0{0}else{SFlen(ot)};'),('while k<depth&&q>0','while k<limit&&(k<depth||longest<8)&&q>0'),('let l=SFmatchlen(input,j,p,cap,known);','let l=SFmatchlen(input,j,p,cap,known);if l>longest{longest=l;}')]:
            assert part.count(a)==1;part=part.replace(a,b)
        r=r.replace(old,part)
    e=w.write_candidate('r24-609-fast-adaptive',p.name,r,lean,'Apply the sameXadaptive shortmatchsearch to the gatedfaststack withoutLoverflowreplacement. Keep the alreadymeasured2x/8bytepolicy andallothermechanisms unchanged.','ATwithLwas8B worse thanXalone, so isolate the observed interaction by comparing X+faststack to X+bufferstack. Not a newthreshold sweep orassumedbytesum; actualparent/exactoutputs andspeed decide.',{'parent':p.name,'comparison':'candidates/r24-609-stack-adaptive/manifest.json','native_interaction':'evidence/round24/38100776877/adaptive-at-native/diagnostics/r13-encoder/encoder.json','proof':'DRAFT; newcapturedlimit/longest states needactualextraction andfreshfullgate.'});e.update(anchor='public609',comparison_baseline='fast-stack',native_decode_reference='fast-stack');entries.append(e)
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']];x=w.control('fast-stack',p.relative_to(ROOT).as_posix(),'609');x.pop('formal_id');x['anchor']='public609';s['entries']+=[x]+entries;s.update(r24_expected_candidates=2,native_encoder_references=['public609','once','fast-stack'],description='AZ actualpositivecostcomposition and controlledremove-L qualityinteraction onthe exactgatedfaststack. Original28filetoken/encoder/decode only; no automaticpromotion fromcomponents.')
    ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('compose-az-native',s),('preflight-az',{'gap':'AQmodesttimegain isclose toobservedaliasvariation, andATquality isworse thanXalone. Needactualcomposition andinteractionisolation beforefinalfreeze.','change':'Two separateRustsources onthe acceptedfaststack: addAQpackedA, oraddexactXwithoutL. No additionalparameters or alteredofficialcode.','minimum':'Full28fileoriginalencoder/decode andprecisefaststack reference. Packedcandidate expectsbitidentity; adaptivecandidate comparedtooldXandATrawreceipts byinput/output hashes.','decision':'Parity/qualitymargin earns oneoriginalpairedscreen; any unexpectedloss investigatesinteraction. Selectexactpairforfullgate/newindependentconfirmation inremainingbudget; no componentgainaddition.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/compose-az-native/diagnostics','proof_status':'DRAFT'})]:
        p=E/(name+'.json');assert not p.exists();p.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print([(e['name'],e['hashes'])for e in entries])
if __name__=='__main__':main()
