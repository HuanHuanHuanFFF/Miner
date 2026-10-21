"""Freeze one controlled screen after all component/composite native receipts exist."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def main():
    rows=[('r24-609-route-inline','38092743994','inline-ac-native','once'),('r24-609-child16','38093247713','child-ad-native','once'),('r24-609-root-prune','38093627577','root-ae-native','once'),('r24-609-root-child16','38094682573','tree-ag-native','r24-609-root-prune')]
    s=json.loads((E/'screen-noq.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']];audits=[]
    for name,run,batch,parent in rows:
        path=ROOT/'candidates'/name;m=json.loads((path/'manifest.json').read_bytes());native=E/run/batch/'diagnostics/r13-encoder/encoder.json';d=json.loads(native.read_bytes());assert d['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES' and d['source_hashes'][name]==m['hashes']
        assert all(hashlib.sha256((path/f).read_bytes()).hexdigest()==v for f,v in m['hashes'].items())
        base={r['file']:r for r in d['rows']if r['candidate']=='once'};rr=[r for r in d['rows']if r['candidate']==name];assert len(base)==len(rr)==28 and all(all(r[k]==base[r['file']][k]for k in ['input_sha256','tokens_sha256','output_sha256','output_bytes'])for r in rr)
        s['entries'].append({'name':name,'path':path.relative_to(ROOT).as_posix(),'control':False,'hashes':m['hashes'],'anchor':'public609','comparison_baseline':parent,'native_decode_reference':parent,'expected_equivalent_to':parent})
        audits.append({'candidate':name,'native_receipt':native.relative_to(ROOT).as_posix(),'native_receipt_sha256':hashlib.sha256(native.read_bytes()).hexdigest(),'equal_files':28})
    s.update(r24_expected_candidates=4,r18_role='discovery',description='AI same-run originaltotal-time component/composite test: routewrappers, compactchildren, no-skipstateprune, actualchild+state combination. Two reversed blocks, exactonce parent and609same-source anchors. Four independent hypotheses; no additive speed or inherited gate claim.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('screen-ai',s),('preflight-ai',{'gap':'All4exact Rust implementations preserve28publictokens/output; opcode/layout/working-set changes have no measured original total-time benefit yet.','change':'Measure isolatedcomponents andactualcombination inonefresh runner, both reversedblocks andsameformal/source controls. ActualAEparent used forAGcomparison.','minimum':'Four candidates x2originalpairedblocks plus actualparents/anchors; original generatedequivalence anddecode checks include ring boundaries.','decision':'Recompute eachblock andtwoalias calibrations againstlatestofficialsnapshot. Prefer effects exceeding observedcontrols andtargetgeometry; failureorregression redirects withoutdiscardingraw evidence. Combinationbenefit mustbeobserved.','cost_cap_runner_minutes':65,'native_audits':audits,'evidence':'evidence/round24/<run>/screen-ai/gate','proof':'AHonlyprovidesinterfaces; everyselectedfinalpair requiresitsowncompletegate andfreshconfirmation.'})]:
        p=E/(name+'.json');assert not p.exists();p.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print('AI_NATIVE_AUDITED',len(ns),'methods x2blocks')
if __name__=='__main__':main()
