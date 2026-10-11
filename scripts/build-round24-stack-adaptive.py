"""Recover measured quality margin on the positive composition with the actual X mechanism."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def main():
    p=ROOT/'candidates/r24-609-root-word-price-buffer';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    for name in ['SFsmallmatches','SFmorematches']:
        old=fn(r,name);part=old
        for a,b in [('let mut k=0usize;','let mut k=0usize;let limit=depth.saturating_add(depth);let mut longest=if ot==0{0}else{SFlen(ot)};'),('while k<depth&&q>0','while k<limit&&(k<depth||longest<8)&&q>0'),('let l=SFmatchlen(input,j,p,cap,known);','let l=SFmatchlen(input,j,p,cap,known);if l>longest{longest=l;}')]:
            assert part.count(a)==1;part=part.replace(a,b)
        r=r.replace(old,part)
    e=w.write_candidate('r24-609-stack-adaptive',p.name,r,l,'Add the exact already-measured X adaptive short-match budget to the actualpositivecomponent composition withLbufferpolicy. Keep its2xmaximum and8byte stopping condition unchanged.','Observed607/609size-transfer error0.000222pp exceedsL-onlyquality shift. Xgained69publicbytes at measuredtime cost; this tests whether the positivebase mechanisms retain a more substantial quality displacement, rather than discarding X merely for being slower. Actual combination, no added gains or newparameter sweep.',{'parent':p.name,'components':['r24-609-root-word-price-buffer','r24-609-adaptive-search'],'quality':'evidence/round24/38090884260/adaptive-x-native/diagnostics/r13-encoder/encoder.json','time':'evidence/round24/analysis-am.json','transfer_gap':'evidence/round24/calibration-b-29638.json','proof':'DRAFT; combines realword/root/buffer proofs with newadaptive loopinterfaces onlyafter actualextraction andfreshfullgate.'});e.update(anchor='public609',comparison_baseline='buffer-stack',native_decode_reference='buffer-stack')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]
    for alias,path in [('buffer-stack',p),('adaptive-x',ROOT/'candidates/r24-609-adaptive-search')]:
        x=w.control(alias,path.relative_to(ROOT).as_posix(),'609');x.pop('formal_id');x['anchor']='public609';s['entries'].append(x)
    s['entries'].append(e);s.update(native_encoder_references=['public609','once','buffer-stack','adaptive-x'],description='AT exactXshortmatchadaptive search onactualpositivequalitycomposition. Measure actual interaction/quality margin, retain bothtruebufferstack andXreferences, no claimedscore or proofinheritance.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('adaptive-at-native',s),('preflight-at',{'gap':'AMcompositions provideonlyabout3.4percentconditionalshare. Lqualityshift is smaller than observedrelated-anchor sizeerror. Xhasmorequality butslower; no evidence yet aboutactualcomposition.','change':'Apply the same measuredadaptive SFmechanism topositiveN/Y/AE/AC+L composition; no newthresholds or fileidentity routing.','minimum':'Original28filebyte/token/decode, exactcomponent references and perfiledifference.','decision':'Usefulquality displacement earns same-run timing under609primary/shadow and607alternative. Keep slowertradeoffs withrealsharepotential, but final10/15requiresactualobservedstableblocks andgates.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/adaptive-at-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'])
if __name__=='__main__':main()
