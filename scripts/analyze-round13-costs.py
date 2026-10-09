"""Decompose measured R13 axes without treating components as promotion evidence."""
from pathlib import Path
import hashlib,json,statistics

ROOT=Path(__file__).resolve().parents[1]
EVIDENCE=ROOT/'evidence/round13'

def median_rep(method):
    reps=sorted((r for r in method['reps'] if r['phase']=='measured'),key=lambda r:r['total_s'])
    assert len(reps)==11 and method['deterministic'] and not method['errors']
    assert all(abs(r['time_s']+r['encode_s']-r['total_s'])<1e-12 for r in reps)
    return reps[5]

def main():
    analysis=json.loads((EVIDENCE/'final-analysis.json').read_bytes());runs=[]
    for run in analysis['runs']:
        folder=EVIDENCE/run['run_id']/run['batch']/'gate'
        state=json.loads((folder/'state.json').read_bytes());entries={e['name']:e for e in state['spec']['entries']}
        metrics={(m['candidate'],m['round']):m for m in state['metrics']};raw={}
        for (name,block),metric in metrics.items():
            path=folder/f'round{block}-{name}.jsonl'
            rows=[json.loads(s) for s in path.read_text().splitlines()];files=[r for r in rows if r['kind']=='file']
            assert len(files)==28
            raw[name,block]={f['file']:f for f in files}
        comparisons=[]
        for (name,block),metric in metrics.items():
            if entries[name].get('control'):continue
            parent=entries[name]['comparison_baseline'];details=[]
            for filename,f in raw[name,block].items():
                p=raw[parent,block][filename]
                assert f['sha256']==p['sha256']
                c,cr=median_rep(f['methods'][name]),median_rep(f['methods']['incumbent'])
                b,br=median_rep(p['methods'][parent]),median_rep(p['methods']['incumbent'])
                parse_delta=c['time_s']/cr['total_s']-b['time_s']/br['total_s']
                encode_delta=c['encode_s']/cr['total_s']-b['encode_s']/br['total_s']
                details.append({'file':filename,'parent_parse_fraction':b['time_s']/b['total_s'],
                    'total_axis_delta':parse_delta+encode_delta,'parse_axis_delta':parse_delta,'encode_axis_delta':encode_delta,
                    'same_tokens_and_output':all(f['methods'][name][k]==p['methods'][parent][k] for k in ('tokens_sha256','output_sha256','output_bytes'))})
            total=metric['time']-metrics[parent,block]['time'];parse=statistics.mean(d['parse_axis_delta'] for d in details);encode=statistics.mean(d['encode_axis_delta'] for d in details)
            assert abs(total-parse-encode)<1e-12
            comparisons.append({'candidate':name,'parent':parent,'block':block,'source_sha256':entries[name]['hashes']['parse.rs'],
                'parent_mean_file_parse_fraction':statistics.mean(d['parent_parse_fraction'] for d in details),
                'total_axis_delta':total,'parse_axis_delta':parse,'encode_axis_delta':encode,'files':details})
        runs.append({'run_id':run['run_id'],'batch':run['batch'],'comparisons':comparisons})
    result={'status':'VERIFIED_RAW_MEDIAN_AXIS_DECOMPOSITION','analysis_sha256':hashlib.sha256((EVIDENCE/'final-analysis.json').read_bytes()).hexdigest(),
        'runs':runs,'scope':'For each file/method the actual measured repetition at the median of11 total_s is selected; parse+encode equals that measured total. Deltas retain separate incumbent measurements in the two standard processes, so encoder-axis movement includes measurement drift even with identical bytes. This is descriptive accounting, not causal attribution, an independent confirmation, or a parser-only score.'}
    (EVIDENCE/'cost-decomposition.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'status':result['status'],'runs':len(runs),'comparisons':sum(len(r['comparisons']) for r in runs)}))

if __name__=='__main__':main()
