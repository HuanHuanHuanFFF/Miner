"""One evidence-backed combination: chain quality with the measured smaller table."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round22'

def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    p=ROOT/'candidates/r22-595-row6-chain'
    r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
    old='pc_run1c::<65536>(input,out,6,0,1000000,4294967295,1,4)';assert r.count(old)==1
    r=r.replace(old,old.replace('65536','32768'))
    en=w.write_candidate('r22-595-chain-halfhead',p.name,r,l,'Combine exactly one older match on route6 with a32768 primary table; preserve original595 skip, lazy, fold and allother routes.','Original two-block chain experiment gave7238B quality gain and small observed speed gains; halfhead gives native parity and mixed speed evidence. Combined collision/chain behavior must be measured and cannot be inferred by adding gains.',{'parent':'candidates/r22-595-row6-chain/manifest.json','component_evidence':['evidence/round22/discovery-c-analysis.json','evidence/round22/discovery-e-analysis.json'],'original_source':'references/round21-public-595/source-receipt.json','ownership':'Inherited generic PC chain machinery and original595 routing retained.'})
    en.update(anchor='public595',comparison_baseline='chain',native_decode_reference='public595')
    s=json.loads((E/'probe-d-native.json').read_bytes())
    s['entries']=[e for e in s['entries'] if e.get('control')]
    chain=w.control('chain',str(p.relative_to(ROOT)).replace('\\','/'),'595');chain.pop('formal_id');chain['anchor']='public595'
    s['entries']+=[chain,en]
    s.update(r22_expected_candidates=1,native_encoder_references=['public595','chain'],description='R22 I single evidence-backed chain/capacity combination, original28file encoder/decode. Actualcollision/quality not additive; standardtime/fullgate only if budget and data warrant.')
    ns=[e['name'] for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (E/'probe-i-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'No stable>=10percent signal. Chain improvesactualsize7238B but only0.008to0.090percent primary timing, below the conditional frontier region; smaller table gives a separate mixed signal.','substantial_change':'One bounded combination of observed components, no broad parameter sweep. Tablecollision pattern can interact with predecessor search, so actual bytes are required.','minimum':'Exact originalencoder+independentdecode of28files,595and actualchainparent comparison; no proxytime promotion.','decision':'Only advance if measuredquality/time offersnew value and collection fits the original17:37:07UTCdeadline. No imaginedadditivegain; no lateuncollectiblegate.','cap_runner_minutes':10,'evidence':'evidence/round22/<run>/probe-i-native/diagnostics'}
    (E/'preflight-i.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print(en)

if __name__=='__main__':main()
