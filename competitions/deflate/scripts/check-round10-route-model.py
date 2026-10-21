"""Check that restored model settings change output only in the intended routes."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics

ROOT=Path(__file__).resolve().parents[1]
ROUTES=ROOT/'evidence/round10/37679261323/explore-a/gate/forward-diagnostics/forward.json'


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('receipt',type=Path)
    args=ap.parse_args()
    routes=json.loads(ROUTES.read_bytes())
    assert routes['status']=='VERIFIED_FINITE_FORWARD_DIAGNOSTIC'
    corpus={p['file']:p for p in routes['corpus']}
    by_file={routes['corpus'][r['case']]['file']:r['row'] for r in routes['seed_records'] if not r['synthetic']}
    state=json.loads((args.receipt/'state.json').read_bytes())
    names=('r10-forward-routecfg','r10-record-nonempty')
    by={}
    for name in names:
        for block in (1,2):
            records=[json.loads(l) for l in (args.receipt/f'round{block}-{name}.jsonl').read_text().splitlines()]
            by[name,block]={r['file']:r for r in records if r['kind']=='file'}
            assert len(by[name,block])==28
    result=[]
    for file in sorted(corpus):
        c,p=by[names[0],1][file],by[names[1],1][file]
        assert c['sha256']==p['sha256']==corpus[file]['sha256']
        changed_row=by_file.get(file) in (5,6,7)
        tokens_equal=c['methods'][names[0]]['tokens_sha256']==p['methods'][names[1]]['tokens_sha256']
        output_equal=c['methods'][names[0]]['output_sha256']==p['methods'][names[1]]['output_sha256']
        if not changed_row:
            assert tokens_equal and output_equal, ('Unexpected unchanged-route difference',file)
        row={'file':file,'d_row':by_file.get(file),'model_changed':changed_row,
             'tokens_equal_to_record':tokens_equal,'output_equal_to_record':output_equal,
             'output_bytes_delta':c['methods'][names[0]]['output_bytes']-p['methods'][names[1]]['output_bytes']}
        times=[]
        for b in (1,2):
            values={}
            for n in names:
                r=by[n,b][file]
                def med(m):
                    reps=[v['total_s'] for v in r['methods'][m]['reps'] if v['phase']=='measured']
                    assert len(reps)==11
                    return statistics.median(reps)
                values[n]=med(n)/med('incumbent')
            times.append((values[names[0]]-values[names[1]])/28)
        row['public_time_axis_delta_contribution']=statistics.mean(times)
        row['public_size_axis_delta_contribution_pp']=100*row['output_bytes_delta']/c['raw_bytes']/28
        result.append(row)
    report={'status':'VERIFIED_FINITE_UNCHANGED_ROUTE_OUTPUTS','run_id':state['run_id'],
            'route_diagnostic_sha256':hashlib.sha256(ROUTES.read_bytes()).hexdigest(),
            'scope':'Existing unchanged source classifier mapping bound to identical public input hashes. This is a finite public route/output check, not a universal statement or private transfer result.',
            'intended_changed_d_rows':[5,6,7],'files':result,
            'intended_model_changed_files':sum(r['model_changed'] for r in result),
            'unchanged_model_files_all_equal':all(r['tokens_equal_to_record'] and r['output_equal_to_record'] for r in result if not r['model_changed'])}
    (args.receipt/'route-model-audit.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps({k:v for k,v in report.items() if k!='files'}))
    print(json.dumps([r for r in result if r['model_changed']]))


if __name__=='__main__':
    main()
