"""Measured in isolation first: combine the two native-equal tree state changes."""
from pathlib import Path
import importlib,json,hashlib
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');child=importlib.import_module('build-round24-child16')
def main():
    original=(ROOT/'candidates/r24-609-once/parse.rs').read_text();assert child.transform(original).encode()==(ROOT/'candidates/r24-609-child16/parse.rs').read_bytes()
    p=ROOT/'candidates/r24-609-root-prune';r=child.transform((p/'parse.rs').read_text(),('Z162','Z189','Aroot162','Aroot189'),4);l=(p/'Parse.lean').read_text()
    e=w.write_candidate('r24-609-root-child16',p.name,r,l,'Apply parent-relativeU16 children to both specialized no-skip trees and their unchanged-policy fallback, alongside removal of the unused recent-head table on eligible paths.','AD andAE each preserve all28publictokens/output; AE covers all11observed A finder calls. Their combined table footprint may interact with caches, so actual combined bytes and a controlled component/composite time screen are required; savings are not added.',{'parent':p.name,'component':'candidates/r24-609-child16/manifest.json','AD_native':'evidence/round24/38093247713/child-ad-native/diagnostics/r13-encoder/encoder.json','AE_native':'evidence/round24/38093627577/root-ae-native/diagnostics/r13-encoder/encoder.json','cache_topology':'evidence/round24/38093627577/root-ae-native/diagnostics/r24-root/cache-topology.log','proof':'DRAFT: all exact new extracted interfaces/fullgate still required.'})
    e.update(anchor='public609',comparison_baseline='root-prune',native_decode_reference='root-prune',expected_equivalent_to='root-prune')
    s=json.loads((E/'child-ad-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]
    for alias,path in [('child16','candidates/r24-609-child16'),('root-prune','candidates/r24-609-root-prune')]:
        c=w.control(alias,path,'609');c.pop('formal_id');c['anchor']='public609';s['entries'].append(c)
    s['entries'].append(e);s.update(native_encoder_references=['public609','once','child16','root-prune'],description='AG actual compactchildren plus no-skipstateprune composite. Original28fileparity against actualcomponents first; no assumed additive speed or proof inheritance.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('tree-ag-native',s),('preflight-ag',{'gap':'AD andAE individual nativeparity is established; combined memory layout and code may differ. AE actually applies to all11observed finder calls,8.428M invocationbytes.','change':'Compose the two specific tree-state mechanisms, preserve fallback and original search choices.','minimum':'Actualoriginalencoder28files with once,AD,AEandcomposite, finite currentcomponent transform identity checked locally.','decision':'Parity permits one same-run controlled component/composite originaltime comparison. Any mismatch diagnoses composition before timing; no addition of isolated gains.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/tree-ag-native/diagnostics','proof_status':'DRAFT','memory_scope':'Oneligiblepath, namedtree/head/short arrays total512KiB; otherworkingdata alsoexists. Runner reportsL2one-size512K. Matchingtable size alone doesnot prove wholeworkingset fit or speed.'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'])
if __name__=='__main__':main()
