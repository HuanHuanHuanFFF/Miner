"""Bounded public-only mixture opportunity; not an implementation or payout claim."""
from pathlib import Path
import hashlib,json,statistics as st
from round10_payability import load_official_scorer

ROOT=Path(__file__).resolve().parents[1]
FOLDERS=[
 'evidence/round15/37910359897/high-f/gate',
 'evidence/round15/37916106579/confirm-u/gate',
 'evidence/round15/37912758146/middle-k/gate',
 'evidence/round16/37940690190/confirm-l/gate',
 'evidence/round16/37943408465/confirm-n/gate',
 'evidence/round18/37969976740/screen-f/gate',
]

def main():
    folders=[ROOT/p for p in FOLDERS]
    future=ROOT/'evidence/round18/37971744344/screen-i/gate'
    if (future/'state.json').exists():folders.append(future)
    groups={};identities={};audit={}
    for folder in folders:
        state=json.loads((folder/'state.json').read_bytes());ci=json.loads((folder/'ci-run.json').read_bytes());assert ci['status']=='completed'
        entries={e['name']:e for e in state['spec']['entries']};metrics={(m['candidate'],m['round']):m for m in state['metrics']};inv=json.loads((folder/'raw-artifact-files.json').read_bytes())
        assert 'public514'in entries
        for name,e in entries.items():
            if name.endswith('-shadow') or name=='fast-shadow':continue
            key=e['hashes']['parse.rs'];g=groups.setdefault(key,{'name':name,'rust_sha256':key,'path':e['path'],'runs':{}});blocks=[]
            for n,b in metrics:
                if n!=name:continue
                p=folder/f'round{b}-{name}.jsonl';record=inv['files'][p.name];assert hashlib.sha256(p.read_bytes()).hexdigest()==record['sha256']
                raw=[json.loads(s)for s in p.read_text().splitlines()];assert raw[0]['methods'][name]['source_sha256']==key
                anchor=metrics['public514',b];filedata={}
                for row in raw:
                    if row['kind']!='file':continue
                    assert identities.setdefault(row['file'],row['sha256'])==row['sha256'];med={}
                    for m in (name,'incumbent'):
                        rr=row['methods'][m];assert rr['deterministic'] and not rr['errors'];vs=[v['total_s']for v in rr['reps']if v['phase']=='measured'];assert len(vs)==11;med[m]=st.median(vs)
                    filedata[row['file']]={'x':med[name]/med['incumbent']/anchor['time'],'y':100*row['methods'][name]['output_bytes']/row['raw_bytes'],'output_bytes':row['methods'][name]['output_bytes']}
                assert len(filedata)==28;blocks.append(filedata);audit[str(p.relative_to(ROOT))]=record['sha256']
            assert blocks
            g['runs'][state['run_id']]={f:{k:st.mean(v[f][k]for v in blocks)for k in ('x','y','output_bytes')}for f in blocks[0]}
    choices={f:[]for f in identities};programs=[]
    for g in groups.values():
        files={f:{k:st.median(v[f][k]for v in g['runs'].values())for k in ('x','y','output_bytes')}for f in choices}
        x=st.mean(v['x']for v in files.values());y=st.mean(v['y']for v in files.values());programs.append({'name':g['name'],'rust_sha256':g['rust_sha256'],'x_relative_to514':x,'public_size_pct':y,'runs':len(g['runs'])})
        for f,v in files.items():choices[f].append({'name':g['name'],**v})
    slopes={0.0}
    for opts in choices.values():
        for i,a in enumerate(opts):
            for b in opts[i+1:]:
                if a['y']!=b['y']:
                    z=(b['x']-a['x'])/(a['y']-b['y'])
                    if z>0:slopes.add(z)
    cuts=sorted(slopes);probes=[0.0]+[(a+b)/2 for a,b in zip(cuts,cuts[1:])]+[cuts[-1]*2+1]
    pages=json.loads((ROOT/'evidence/round18/official-start-live/pareto-pages.json').read_bytes());official={r['id']:r for p in pages for r in p['items']};fm=official['514']['metrics'];base=next(g for g in programs if g['name']=='public514');sc=load_official_scorer()
    front=[sc.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in official.values()if(r.get('score')or{}).get('on_frontier')]
    envelope=[];seen=set()
    for slope in probes:
        selected={f:min(opts,key=lambda v:(v['x']+slope*v['y'],v['y'],v['name']))for f,opts in choices.items()};key=tuple(v['name']for f,v in sorted(selected.items()))
        if key in seen:continue
        seen.add(key);x=st.mean(v['x']for v in selected.values());y=st.mean(v['y']for v in selected.values());tx=fm['balanced_time_ratio']*x;sy=fm['mean_file_compression_pct']*y/base['public_size_pct']
        weights=sc.local_global_improvement_space_log_weights(sc.pareto_front(front+[sc.Point('__oracle__',tx,sy)]));share=100*weights.get('__oracle__',0)
        envelope.append({'public_time_relative_to514':x,'public_size_pct':y,'lambda':slope,'illustrative514_transfer_time':tx,'illustrative514_transfer_size':sy,'illustrative514_transfer_pool_pct':share,'choices':selected})
    best=max(envelope,key=lambda p:p['illustrative514_transfer_pool_pct'])
    report={'status':'INFERRED_FREE_SWITCHING_PUBLIC_OPPORTUNITY_ONLY','snapshot':pages[0]['context'],'programs':programs,'vertices':envelope,'best_illustrative_vertex':best,'raw_input_audit':audit,
            'limits':['Free per-file switching is not a runnable parser or generic route.','Means within a runner and medians across runners reduce selected one-run peaks but do not remove selection bias.','The illustrative514factor is not validated across high-compression families; do not treat this as a forecast or private-corpus bound.','Zero switching/feature/proof overhead is assumed only to identify work worth measuring.','No new candidate, independent confirmation, fullgate, admission or payout is established by this analysis.']}
    (ROOT/'evidence/round18/oracle-opportunity.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps({'programs':len(programs),'vertices':len(envelope),'best':{k:v for k,v in best.items()if k!='choices'},'choices':{f:v['name']for f,v in best['choices'].items()}},indent=2))

if __name__=='__main__':main()
