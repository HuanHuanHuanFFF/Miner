"""Attribute untimed original-encoder byte changes to an actual frozen parent."""
from pathlib import Path
import argparse, hashlib, json, statistics as st


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('artifact',type=Path)
    ap.add_argument('--base',default='combo')
    ap.add_argument('--output',type=Path,required=True)
    ap.add_argument('--completed-encoder-from-failed-job', action='store_true',
                    help='Preserve failed CI status while auditing an already complete native encoder receipt')
    a=ap.parse_args();assert not a.output.exists()
    folder=a.artifact; d=json.loads((folder/'r13-encoder/encoder.json').read_bytes())
    inv=json.loads((folder/'raw-artifact-files.json').read_bytes());ci=json.loads((folder/'ci-run.json').read_bytes())
    assert ci['conclusion']=='success' or (a.completed_encoder_from_failed_job and ci['conclusion']=='failure')
    assert ci['status']=='completed' and ci['headSha']==d['git_sha'] and str(ci['databaseId'])==d['run_id']
    assert d['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    for f,v in inv['files'].items():assert hashlib.sha256((folder/f).read_bytes()).hexdigest()==v['sha256']
    by={n:{x['file']:x for x in d['rows'] if x['candidate']==n} for n in d['source_hashes']}
    base=by[a.base];assert len(base)==28 and sum(v['raw_bytes'] for v in base.values())==15930000
    rows=[]
    for n,fs in by.items():
        assert fs.keys()==base.keys()
        assert all((v['input_sha256'],v['raw_bytes'])==(base[f]['input_sha256'],base[f]['raw_bytes']) for f,v in fs.items())
        delta=[{'file':f,'byte_delta':v['output_bytes']-base[f]['output_bytes'],
                'token_delta':v['tokens']-base[f]['tokens'],
                'size_pp':100*(v['output_bytes']-base[f]['output_bytes'])/v['raw_bytes']} for f,v in fs.items()]
        rows.append({'candidate':n,'public_size_pct':st.mean(100*x['output_bytes']/x['raw_bytes'] for x in fs.values()),
            'total_bytes':sum(x['output_bytes'] for x in fs.values()),'delta_bytes_vs_parent':sum(x['byte_delta'] for x in delta),
            'delta_balanced_pp_vs_parent':st.mean(x['size_pp'] for x in delta),
            'changed_files':[x for x in delta if x['byte_delta'] or x['token_delta']]})
    out={'status':'VERIFIED_ORIGINAL_ENCODER_BYTES_ONLY','run':d['run_id'],'git_sha':d['git_sha'],
         'ci_conclusion':ci['conclusion'],
         'ci_scope':'Encoder receipt only; a failed surrounding job remains failed. Other stages are not certified.',
         'parent':a.base,'candidate_hashes':d['source_hashes'],'source_receipt':str(folder/'r13-encoder/encoder.json'),
         'summary':rows,'timing':'NOT_MEASURED','full_gate':'NOT_RUN'}
    a.output.write_bytes((json.dumps(out,indent=2)+'\n').encode())
    print(json.dumps({'run':d['run_id'],'parent':a.base,'summary':[{k:v for k,v in row.items() if k!='changed_files'} for row in rows]},indent=2))


if __name__=='__main__':main()
