"""Rank middle-frontier research by same-family formal anchors and stress cases."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from round3 import load_scorer

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('receipt',type=Path)
    ap.add_argument('--snapshot',type=Path,default=ROOT/'evidence/round7/frontier-start/pareto-pages.json')
    args=ap.parse_args()
    state=json.loads((args.receipt/'state.json').read_text())
    pages=json.loads(args.snapshot.read_text())
    rows=[r for p in pages for r in p['items']]
    official={r['id']:r for r in rows}
    published=[r for r in rows if (r.get('score') or {}).get('on_frontier')]
    sc=load_scorer(ROOT/'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    points=[sc.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct']) for r in published]
    bounds=sc.Boundaries(10,40)
    replay=sc.local_global_improvement_space_log_weights(sc.pareto_front(points),bounds)
    replay_error=max(abs(replay[r['id']]-r['score']['pareto_weight']) for r in published)
    assert replay_error<1e-10
    entries={e['name']:e for e in state['spec']['entries']}
    by={(m['candidate'],m['round']):m for m in state['metrics']}
    def geometry(x,y):
        ds=[p.name for p in points if p.time_s<=x and p.ratio_pct<=y]
        legal=x<=10 and y<=40
        w=sc.local_global_improvement_space_log_weights(sc.pareto_front(points+[sc.Point('candidate',x,y)]),bounds)
        return {'time_ratio':x,'compressed_pct':y,'on_geometric_frontier':legal and not ds,
            'conditional_share_pct':w.get('candidate',0)*100 if legal and not ds else 0,
            'dominating_ids':ds,'size_gap_pp':max(0,y-min((p.ratio_pct for p in points if p.time_s<=x),default=40))}
    results=[]
    shadow={}
    for n,e in entries.items():
        anchor=e.get('anchor',n)
        if anchor not in entries or 'formal_id' not in entries[anchor]:continue
        blocks=sorted(b for candidate,b in by if candidate==n and (anchor,b) in by)
        if not blocks:continue
        formal=official[entries[anchor]['formal_id']]['metrics']
        for b in blocks:
            assert by[n,b]['source_sha256']==e['hashes']['parse.rs']
            assert hashlib.sha256((ROOT/e['path']/'parse.rs').read_bytes()).hexdigest()==e['hashes']['parse.rs']
        relative=[by[n,b]['time']/by[anchor,b]['time'] for b in blocks]
        public_size=by[n,blocks[0]]['size_pct']
        assert all(abs(by[n,b]['size_pct']-public_size)<1e-12 for b in blocks)
        x=formal['balanced_time_ratio']*statistics.mean(relative)
        y=formal['mean_file_compression_pct']*public_size/by[anchor,blocks[0]]['size_pct']
        if e.get('control'):
            if n!=anchor:shadow[n]={'anchor':anchor,'block_time_changes_pct':[100*(r-1) for r in relative]}
            continue
        stress_x=formal['balanced_time_ratio']*max(relative)*1.02
        stress_y=y+0.01
        results.append({'candidate':n,'source_sha256':e['hashes']['parse.rs'],'proof_sha256':e['hashes']['Parse.lean'],
            'anchor_submission_id':entries[anchor]['formal_id'],'blocks':blocks,
            'public_time_ratio':statistics.mean(by[n,b]['time'] for b in blocks),'public_compressed_pct':public_size,
            'relative_time_changes_pct':[100*(r-1) for r in relative],
            'public_size_change_pp':public_size-by[anchor,blocks[0]]['size_pct'],
            'own_family_transfer':geometry(x,y),'stress_time_2pct_size_001pp':geometry(stress_x,stress_y),
            'gate':state.get('gates',{}).get(n),'transfer_status':'INFERRED; not private evaluation, admission or payment'})
    results.sort(key=lambda r:(-r['stress_time_2pct_size_001pp']['conditional_share_pct'],
        -r['own_family_transfer']['conditional_share_pct'],r['own_family_transfer']['size_gap_pp'],r['public_time_ratio']))
    result={'status':'VERIFIED_PUBLIC_RECEIPT_WITH_INFERRED_FORMAL_TRANSFERS','run_id':state['run_id'],
        'source_commit':state['git_sha'],'batch':state['batch'],'snapshot':pages[0]['context'],
        'scorer_replay_max_error':replay_error,'same_byte_shadow':shadow,'failures':state['failures'],
        'stress_scope':'Declared adverse scenario, not a statistical confidence interval: maximum block-relative time plus 2%, transferred size plus 0.01 percentage points.',
        'candidates':results}
    (args.receipt/'middle-analysis.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result))

if __name__=='__main__':main()
