"""Audit separate diagnostic raw records without promoting them to official scores."""
from pathlib import Path
import argparse,hashlib,json,statistics as st
ROOT=Path(__file__).resolve().parents[1]

def read(p):return json.loads(p.read_bytes())

def main():
    ap=argparse.ArgumentParser();ap.add_argument('folder',type=Path);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args()
    folder=a.folder.resolve();ci=read(folder/'ci-run.json');inv=read(folder/'raw-artifact-files.json')
    for name,v in inv['files'].items():
        p=folder/name;b=p.read_bytes();assert len(b)==v['bytes'] and hashlib.sha256(b).hexdigest()==v['sha256']
    source=folder/'r18-order/order.json';d=read(source)
    assert d['status']=='COMPLETE_DIAGNOSTIC_ORDER_COMPARISON' and ci['conclusion']=='success' and ci['headSha']==d['git_sha'] and str(ci['databaseId'])==d['run_id']
    spec=read(ROOT/'evidence/round22/noise-f-diagnostic.json');by={e['name']:e for e in spec['entries']}
    names=spec['diagnostic_methods'];identities={};results=[]
    for r in d['blocks']:
        raw=source.parent/r['raw_file'];assert hashlib.sha256(raw.read_bytes()).hexdigest()==r['raw_sha256']
        rows=[json.loads(v) for v in raw.read_text().splitlines()];meta=rows[0];fs=[f for f in rows if f['kind']=='file'];assert len(fs)==28
        assert all(meta['methods'][n]['source_sha256']==by[n]['hashes']['parse.rs'] for n in names)
        for p,s in ((names[0],names[1]),(names[2],names[3])):
            assert meta['methods'][p]['lib_sha256']==meta['methods'][s]['lib_sha256']
        axes={n:[] for n in ['incumbent']+names}
        for f in fs:
            med={}
            for n in axes:
                m=f['methods'][n];assert not m['errors'] and m['deterministic']
                reps=[q['total_s'] for q in m['reps'] if q['phase']=='measured'];assert len(reps)==r['reps']
                med[n]=st.median(reps)
                key=(meta['methods'][n]['source_sha256'],f['file']);identity=(f['sha256'],m['tokens_sha256'],m['output_sha256'])
                assert identities.setdefault(key,identity)==identity
            for n in axes:axes[n].append(med[n]/med['incumbent'])
        axes={n:st.mean(v) for n,v in axes.items()};assert all(abs(axes[n]-r['axes'][n])<1e-12 for n in axes)
        deltas=[100*(axes[c]/axes[p]-1) for c in names[2:] for p in names[:2]]
        results.append({'protocol':r['protocol'],'block':r['block'],'reps':r['reps'],'parent_alias_gap_pct':100*(axes[names[1]]/axes[names[0]]-1),'candidate_alias_gap_pct':100*(axes[names[3]]/axes[names[2]]-1),'candidate_vs_parent_primary_pct':100*(axes[names[2]]/axes[names[0]]-1),'candidate_vs_all_parent_aliases_range_pct':[min(deltas),max(deltas)],'axes':axes,'raw_file':raw.relative_to(ROOT).as_posix(),'libraries':{n:meta['methods'][n]['lib_sha256'] for n in names}})
    result={'status':'VERIFIED_SEPARATE_DIAGNOSTIC_RECORDS','run_id':d['run_id'],'blocks':results,'original_encoder_sha256':d['source_hashes']['src/deflate.rs'],'original_token_sha256':d['source_hashes']['src/token.rs'],'protocols':d['protocols'],'matched_fixed20_control_missing':'original_fixed20' not in d['protocols'],'limits':['These are explicitlyCPU-bound multi-method diagnostic measurements, excluded from original isolated protocol reward forecasts.','Fixed11 versus balanced20 changes both ordering and repetition count; this run cannot uniquely identify an order-only effect.','Actual alias differences and negative or positive candidate comparisons are observations, not private-corpus guarantees or extra independent promotion samples.']}
    a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps([{k:v for k,v in r.items() if k not in ('axes','raw_file','libraries')} for r in results],indent=2))

if __name__=='__main__':main()
