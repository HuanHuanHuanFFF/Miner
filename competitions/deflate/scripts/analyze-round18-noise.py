"""Audit protocol-separated diagnostics; never promote diagnostic axes as scores."""
from pathlib import Path
import hashlib,json,statistics as st
from round10_payability import load_official_scorer

ROOT=Path(__file__).resolve().parents[1]

def main():
    folder=ROOT/'evidence/round18/37970399568/noise-g-diagnostic/diagnostics'
    inv=json.loads((folder/'raw-artifact-files.json').read_bytes())
    for n,v in inv['files'].items():
        p=folder/n;assert p.stat().st_size==v['bytes'] and hashlib.sha256(p.read_bytes()).hexdigest()==v['sha256']
    d=folder/'r18-noise';data=json.loads((d/'noise.json').read_bytes());groups={};inputs={};outputs={}
    for r in data['blocks']:
        p=d/r['raw_file'];assert hashlib.sha256(p.read_bytes()).hexdigest()==r['raw_sha256']
        raw=[json.loads(s)for s in p.read_text().splitlines()];meta=raw[0];fs=[f for f in raw if f['kind']=='file'];assert len(fs)==28
        for n in r['order']:
            ratios=[]
            for f in fs:
                assert inputs.setdefault(f['file'],f['sha256'])==f['sha256'];med={}
                for m in set((n,'incumbent')):
                    v=f['methods'][m];assert v['deterministic'] and not v['errors'];reps=[x['total_s'] for x in v['reps'] if x['phase']=='measured'];assert len(reps)==11
                    med[m]=st.median(reps);key=(meta['methods'][m]['source_sha256'],f['file']);ident=(v['tokens_sha256'],v['output_sha256'],v['output_bytes']);assert outputs.setdefault(key,ident)==ident
                ratios.append(med[n]/med['incumbent'])
            assert abs(st.mean(ratios)-r['axes'][n])<1e-12
        g=groups.setdefault((r['protocol'],r['block']),{'axes':{},'sizes':{},'libraries':{}})
        for k in ('axes','sizes','libraries'):g[k].update(r[k])
    pages=json.loads((ROOT/'evidence/round18/official-start-live/pareto-pages.json').read_bytes());rows={r['id']:r for p in pages for r in p['items']};sc=load_official_scorer();fm=rows['514']['metrics']
    front=[sc.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct']) for r in rows.values() if (r.get('score')or{}).get('on_frontier')]
    def projected(g,anchor):
        x=fm['balanced_time_ratio']*g['axes']['dna582']/g['axes'][anchor];y=fm['mean_file_compression_pct']*g['sizes']['dna582']/g['sizes'][anchor]
        w=sc.local_global_improvement_space_log_weights(sc.pareto_front(front+[sc.Point('__dna__',x,y)]));return {'time':x,'size':y,'conditional_pool_pct':100*w.get('__dna__',0)}
    observations=[]
    for (protocol,block),g in sorted(groups.items()):
        for a,b in [('public514','public514-shadow'),('dna582','dna582-shadow')]:assert g['libraries'][a]==g['libraries'][b]
        observations.append({'protocol':protocol,'block':block,'public514_shadow_gap_pct':100*(g['axes']['public514-shadow']/g['axes']['public514']-1),'dna582_shadow_gap_pct':100*(g['axes']['dna582-shadow']/g['axes']['dna582']-1),'dna582_vs514_pct':100*(g['axes']['dna582']/g['axes']['public514']-1),'primary_514_projection':projected(g,'public514'),'shadow_514_projection':projected(g,'public514-shadow')})
    summary={}
    for p in sorted({r['protocol']for r in observations}):
        rr=[r for r in observations if r['protocol']==p];entry={}
        for k in ('public514_shadow_gap_pct','dna582_shadow_gap_pct','dna582_vs514_pct'):
            vals=[r[k]for r in rr];entry[k]={'values':vals,'median':st.median(vals),'range':[min(vals),max(vals)],'median_abs':st.median(abs(v)for v in vals)}
        entry['primary_514_shares_pct']=[r['primary_514_projection']['conditional_pool_pct']for r in rr]
        entry['shadow_514_shares_pct']=[r['shadow_514_projection']['conditional_pool_pct']for r in rr]
        summary[p]=entry
    contexts=[]
    for p in d.glob('*-actual-process.json'):
        v=json.loads(p.read_bytes());contexts.append({'file':p.name,'request':v['explicit_affinity_request'],'initial':v['affinity_initial'],'actual':v['affinity_before_exec']})
        if v['explicit_affinity_request']!='observe':assert v['affinity_before_exec']==[int(v['explicit_affinity_request'])]
    report={'status':'VERIFIED_PROTOCOL_SEPARATED_RAW_RECOMPUTATION','run_id':data['run_id'],'snapshot':pages[0]['context'],'summary':summary,'observations':observations,'actual_process_contexts':contexts,
            'limits':['One fresh host; blocks within each protocol are not independent runners.','Observed and pinned multimethod/isolated-pinned values are diagnostics, not original official protocol scores.','Even lower control disagreement does not establish unbiased transfer or explain all noise.','DNA582 is already formally dominated; these replays illustrate calibration sensitivity, not a new submission forecast.','Current official-frontier geometry is conditional and sample target counts are not success probabilities.']}
    (ROOT/'evidence/round18/noise-g-analysis.json').write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({'summary':summary,'process_contexts':len(contexts)},indent=2))

if __name__=='__main__':main()
