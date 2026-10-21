"""Audit isolated versus shared/pinned diagnostics, never substitute official scores."""
from pathlib import Path
import argparse,hashlib,json,statistics as st
from importlib import import_module
impact=import_module('round20-impact')
ROOT=Path(__file__).resolve().parents[1]
def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('folder',type=Path);ap.add_argument('--capture',type=Path,default=ROOT/'evidence/round20/official-mid');ap.add_argument('--output',type=Path,required=True);a=ap.parse_args()
    inv=json.loads((a.folder/'raw-artifact-files.json').read_bytes())
    for n,v in inv['files'].items():
        raw=(a.folder/n).read_bytes();assert len(raw)==v['bytes'] and hashlib.sha256(raw).hexdigest()==v['sha256']
    p=a.folder/'r18-noise';d=json.loads((p/'noise.json').read_bytes());assert d['status']=='COMPLETE_PROTOCOL_SEPARATED_MEASUREMENT_DIAGNOSTIC'
    names=d['spec']['diagnostic_methods'];ref,ref2,cand,cand2=names;groups={};outputs={}
    for r in d['blocks']:
        raw=(p/r['raw_file']).read_bytes();assert hashlib.sha256(raw).hexdigest()==r['raw_sha256'];records=[json.loads(l)for l in raw.splitlines()];meta=records[0];fs=[v for v in records if v['kind']=='file'];assert len(fs)==28
        for n in r['order']:
            vals=[]
            for f in fs:
                med={}
                for method in set((n,'incumbent')):
                    x=f['methods'][method];assert x['deterministic'] and not x['errors'];reps=[z['total_s']for z in x['reps']if z['phase']=='measured'];assert len(reps)==11;med[method]=st.median(reps)
                    key=meta['methods'][method]['source_sha256'],f['file'];ident=f['sha256'],x['tokens_sha256'],x['output_sha256'],x['output_bytes'];assert outputs.setdefault(key,ident)==ident
                vals.append(med[n]/med['incumbent'])
            assert abs(st.mean(vals)-r['axes'][n])<1e-12
        g=groups.setdefault((r['protocol'],r['block']),{'axes':{},'sizes':{},'libraries':{}})
        for k in g:g[k].update(r[k])
    comp,ctx,rows,s,b,front,top,check=impact.context(a.capture);formal=next(r for r in rows if str(r['id'])=='539')['metrics'];observations=[]
    for (protocol,block),g in sorted(groups.items()):
        assert g['libraries'][ref]==g['libraries'][ref2] and g['libraries'][cand]==g['libraries'][cand2]
        obs={'protocol':protocol,'block':block,'reference_shadow_gap_pct':100*(g['axes'][ref2]/g['axes'][ref]-1),'candidate_shadow_gap_pct':100*(g['axes'][cand2]/g['axes'][cand]-1),'candidate_vs_reference_pct':100*(g['axes'][cand]/g['axes'][ref]-1),'projections':[]}
        for cn in [cand,cand2]:
            for an in [ref,ref2]:
                x=formal['balanced_time_ratio']*g['axes'][cn]/g['axes'][an];y=formal['mean_file_compression_pct']*g['sizes'][cn]/g['sizes'][an]
                points=front+[s.Point('__new__',x,y)] if not any(q.time_s<=x and q.ratio_pct<=y for q in front)else front
                w=s.local_global_improvement_space_log_weights(s.pareto_front(points),b)
                obs['projections'].append({'candidate_view':cn,'anchor_view':an,'time':x,'size':y,'conditional_own_pct':100*w.get('__new__',0),'top1_after_pct':100*w.get(str(top['id']),0),'classification':'original-protocol diagnostic block'if protocol=='official_isolated'else'diagnostic-only; not official performance'})
        observations.append(obs)
    summary={}
    for protocol in sorted({r['protocol']for r in observations}):
        rs=[r for r in observations if r['protocol']==protocol];v={}
        for k in ['reference_shadow_gap_pct','candidate_shadow_gap_pct','candidate_vs_reference_pct']:
            vs=[r[k]for r in rs];v[k]={'values':vs,'median':st.median(vs),'range':[min(vs),max(vs)]}
        for k in ['conditional_own_pct','top1_after_pct']:
            vs=[p[k]for r in rs for p in r['projections']];v[k]={'median':st.median(vs),'range':[min(vs),max(vs)]}
        summary[protocol]=v
    contexts=[]
    for file in p.glob('*-actual-process.json'):
        c=json.loads(file.read_bytes());contexts.append({'file':file.name,'request':c['explicit_affinity_request'],'actual':c['affinity_before_exec']})
        if c['explicit_affinity_request']!='observe':assert c['affinity_before_exec']==[int(c['explicit_affinity_request'])]
    result={'status':'VERIFIED_RAW_PROTOCOL_SEPARATED_DIAGNOSTIC','run_id':d['run_id'],'snapshot':ctx,'policy_validation':check,'summary':summary,'observations':observations,'actual_process_contexts':contexts,'limits':['One runner; protocol blocks are not independent runners.','Only official_isolated uses the original one-candidate protocol. Shared or explicitly pinned measurements are diagnostics, not promotion evidence.','No private-corpus, admission or payment conclusion. Same-source improvements do not by themselves prove the cause of noise.','Four source/control views per block are not four independent observations.']}
    a.output.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(summary,indent=2))
if __name__=='__main__':main()
