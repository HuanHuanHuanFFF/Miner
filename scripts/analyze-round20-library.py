"""Recompute the frozen equal-repetition ordering diagnostic from raw bytes."""
from pathlib import Path
import argparse,hashlib,json,statistics as st

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('folder',type=Path);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args()
    inv=json.loads((a.folder/'raw-artifact-files.json').read_bytes())
    for n,v in inv['files'].items():
        raw=(a.folder/n).read_bytes();assert len(raw)==v['bytes'] and hashlib.sha256(raw).hexdigest()==v['sha256']
    p=a.folder/'r20-library';d=json.loads((p/'order.json').read_bytes());assert d['status']=='COMPLETE_DIAGNOSTIC_LIBRARY_COMPARISON';obs=[];identities={}
    names=['public539','public539-shadow','r20-539-csv-singlehead','r20-539-csv-singlehead-shadow']
    for b in d['blocks']:
        raw=(p/b['raw_file']).read_bytes();assert hashlib.sha256(raw).hexdigest()==b['raw_sha256'];records=[json.loads(l)for l in raw.splitlines()];meta=records[0];fs=[r for r in records if r['kind']=='file'];assert len(fs)==28 and meta['measured_rounds']==20 and meta['warmup_rounds']==1
        axes={n:[]for n in ['incumbent']+names};load=b['method_load_order'];expected=[[load[i]for i in d['orders'][j%10]]for j in range(20)]if b['protocol'].startswith('balanced_')else[load]*20
        for f in fs:
            med={};orders=[]
            for n in axes:
                v=f['methods'][n];assert v['deterministic'] and not v['errors'];rr=[r for r in v['reps']if r['phase']=='measured'];assert len(rr)==20;med[n]=st.median(r['total_s']for r in rr)
                key=meta['methods'][n]['source_sha256'],f['file'];ident=f['sha256'],v['tokens_sha256'],v['output_sha256'];assert identities.setdefault(key,ident)==ident
            for j in range(20):orders.append(sorted(load,key=lambda n:[r for r in f['methods'][n]['reps']if r['phase']=='measured'][j]['order_index']))
            assert orders==expected
            for n in axes:axes[n].append(med[n]/med['incumbent'])
        means={n:st.mean(v)for n,v in axes.items()};assert all(abs(means[n]-b['axes'][n])<1e-12 for n in means)
        paths=b['library_paths']
        shared=b['protocol']=='balanced_shared'
        assert (paths[names[0]]==paths[names[1]])==shared and (paths[names[2]]==paths[names[3]])==shared
        process=json.loads((p/(b['raw_file'].removesuffix('.jsonl')+'-process.json')).read_bytes());assert len(process['affinity_before_exec'])==1
        assert meta['methods'][names[0]]['lib_sha256']==meta['methods'][names[1]]['lib_sha256'] and meta['methods'][names[2]]['lib_sha256']==meta['methods'][names[3]]['lib_sha256']
        obs.append({'protocol':b['protocol'],'block':b['block'],'actual_affinity':process['affinity_before_exec'],'reference_shadow_gap_pct':100*(means[names[1]]/means[names[0]]-1),'candidate_shadow_gap_pct':100*(means[names[3]]/means[names[2]]-1),'candidate_vs_reference_pct':100*(means[names[2]]/means[names[0]]-1),'two_copy_average_change_pct':100*((means[names[2]]+means[names[3]])/(means[names[0]]+means[names[1]])-1)})
    summary={}
    for protocol in ['balanced_distinct','balanced_shared']:
        rs=[r for r in obs if r['protocol']==protocol];summary[protocol]={k:{'values':[r[k]for r in rs],'median':st.median(r[k]for r in rs),'median_absolute':st.median(abs(r[k])for r in rs)}for k in ['reference_shadow_gap_pct','candidate_shadow_gap_pct','candidate_vs_reference_pct','two_copy_average_change_pct']}
    report={'status':'VERIFIED_RAW_DIAGNOSTIC_BALANCED_LIBRARY_PATH_COMPARISON','run_id':d['run_id'],'summary':summary,'observations':obs,'original_engine_sha256':d['original_engine_sha256'],'balanced_engine_sha256':d['balanced_engine_sha256'],'limits':['Diagnostic only: balanced20 andexplicitpin. Distinct versus sharedphysicalDSOpaths; no directCPUaddresscausalproof.','One fresh runner and two blocks percondition; doesnotestablishunbiasedformalperformance orprivategeneralization.','No correctedscore substitutes originalJ/Kconfirmation.']};a.output.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(summary,indent=2))
if __name__=='__main__':main()
