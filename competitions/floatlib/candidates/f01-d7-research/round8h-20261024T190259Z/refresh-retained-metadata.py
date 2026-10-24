"""Append authenticated DF control evidence; keep its displayed model byte-frozen."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
OWN=HERE.parent
def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result
def sha(raw):return hashlib.sha256(raw).hexdigest()
def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--dry-run',action='store_true');a=ap.parse_args()
    if not __debug__:raise RuntimeError('Optimized Python refused')
    verifier=module('r14_metadata_identity',HERE/'verify-three-groups.py')
    adopter=module('r14_metadata_transaction',HERE/'adopt-three-confirmed.py')
    estimator=module('r14_metadata_authenticator',ROOT/'competitions/floatlib/scripts/estimate_champion_time.py')
    identity=verifier.retained_model_identity(ROOT)
    model=ROOT/identity['model_path'];original_model=model.read_bytes()
    assert sha(original_model)==identity['sha256'],'Same-source numeric model changed'
    index=OWN/'public-suite-results.json';index_raw=index.read_bytes()
    rows=[r for r in json.loads(index_raw)['records'] if r['kernel_sha256']==identity['source_sha256'] and r.get('full_gate')]
    for row in rows:estimator.checked_record(row,ROOT)
    runs=[r['run'] for r in rows];assert len(runs)==len(set(runs)) and runs
    viewpath=OWN/'multiplier-comparison.json';statepath=ROOT/'competitions/floatlib/coordination/development-status.json'
    tx=adopter.Transaction([viewpath,statepath]);v=json.loads(tx.before[viewpath.resolve()]);s=json.loads(tx.before[statepath.resolve()])
    assert (ROOT/v['public_results']).resolve()==index.resolve(),'View points at a different raw index'
    assert v['kernel_sha256']==s['kernel_sha256']==identity['source_sha256']
    before=list(v['full_gate_runs']);assert set(before)<=set(runs),'Prior source evidence disappeared'
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':identity['source_sha256'],
        'before_declared_full_runs':before,'after_declared_full_runs':runs,'input_index_sha256':sha(index_raw),
        'numeric_model_sha256_unchanged':sha(original_model),'retained_identity':identity,
        'scope':'Authenticated raw-control evidence and count metadata only; independent adoption samples and numeric model unchanged.'}
    if a.dry_run or before==runs:
        print(json.dumps({'status':'DRY_RUN' if a.dry_run else 'NO_CHANGE','before':len(before),'after':len(runs),'model_unchanged':True}));return
    samples={r['run']:r for r in s['performance']['all_source_samples']}
    for row in rows:
        if row['run'] not in samples:
            samples[row['run']]={k:row[k] for k in ('run','seed','ratio','verdict','verdict_sha256','sample_role','execution_has_observer')}
            samples[row['run']]['codegen_capture_state']=row.get('codegen',{}).get('state','NOT_REQUESTED')
    v['full_gate_runs']=runs
    s['performance'].update(full_gate_runs=runs,seeds=[r['seed'] for r in rows],ratio_vs_shipped=[r['ratio'] for r in rows],
        kernels_vs_shipped=[{op:r['operation_total_ns'][op]/r['operation_reference_total_ns'][op] for op in ('add','mul','sum','bmm')} for r in rows],
        all_source_samples=[samples[run] for run in runs])
    s['current_multiplier_view']['all_retained_source_public_gate_runs']=runs
    s['updated_at_utc']=receipt['at_utc']
    try:
        assert model.read_bytes()==original_model and index.read_bytes()==index_raw
        tx.write(viewpath,adopter.encoded(v));tx.write(statepath,adopter.encoded(s))
        assert model.read_bytes()==original_model and index.read_bytes()==index_raw
        tx.unchanged()
        receipt['before_sha256']={p.relative_to(ROOT).as_posix():sha(raw) for p,raw in tx.before.items()}
        receipt['after_sha256']={p.relative_to(ROOT).as_posix():sha(p.read_bytes()) for p in tx.before}
        stamp=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ')
        with (HERE/f'retained-control-metadata-{stamp}.json').open('xb') as stream:stream.write(adopter.encoded(receipt))
    except BaseException as error:
        rollback=tx.rollback()
        failure={**receipt,'status':'METADATA_WRITE_FAILED','error_type':type(error).__name__,
                 'reason':str(error),'rollback':rollback,'model_sha256_after':sha(model.read_bytes())}
        stamp=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
        with (HERE/f'retained-control-metadata-failure-{stamp}.json').open('xb') as stream:stream.write(adopter.encoded(failure))
        raise
    print(json.dumps({'status':'METADATA_UPDATED','before':len(before),'after':len(runs),'model_unchanged':True}))
if __name__=='__main__':main()
