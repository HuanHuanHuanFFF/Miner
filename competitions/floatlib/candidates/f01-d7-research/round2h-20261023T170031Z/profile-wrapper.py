"""Isolated diagnostics: reuse the byte-exact public adapter, then profile retained41."""
from pathlib import Path
import hashlib, importlib.util, json, os, subprocess

def run(g,kernel,out):
    repo=Path(os.environ['GITHUB_WORKSPACE'])
    own=Path(__file__).resolve().parent
    plan=json.loads((repo/'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json').read_bytes())
    assert plan.get('profile_current') is True and not plan.get('confirmation_candidates')
    name='f01-r8-combined-result-guard'
    assert plan.get('profile_candidate')==name
    # Nested output keeps this observed diagnostic out of the scored public index.
    original_out=out/'retained-profile-gates';original_out.mkdir(exist_ok=True)
    original_path=own.parent/'public-suite.py'
    spec=importlib.util.spec_from_file_location('unchanged_original_public_suite',original_path)
    original=importlib.util.module_from_spec(spec);spec.loader.exec_module(original)
    original.run(g,kernel,original_out)
    stage=original_out/'public-suite'
    summary_path=stage/'summary.json'
    summary=json.loads(summary_path.read_bytes())
    rows=[r for r in summary['results'] if r['candidate']==name and r['full_gate']]
    assert summary['complete'] and len(rows)==1
    assert rows[0]['kernel_sha256']=='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
    verdict=stage/rows[0]['verdict']
    before={str(p.relative_to(out)):hashlib.sha256(p.read_bytes()).hexdigest() for p in (summary_path,verdict)}
    profile_out=out/'retained-stage-profile';profile_out.mkdir(exist_ok=True)
    upstream=Path(os.environ['RUNNER_TEMP'])/'floatlib-r7-public-suite-upstream'
    helper=own/'profile-retained-entry.py'
    argv=[str(upstream/'.venv/bin/python'),str(helper),'--upstream',str(upstream),'--kernel',str(stage/'inputs'/name/'Kernel.lean'),'--out',str(profile_out),'--plan',str(stage/'public-drawn-plan.json'),'--original-verdict',str(verdict),'--original-summary',str(summary_path)]
    env=os.environ.copy()
    env.update(BENCH_SEED=str(plan['seed']),GATE_FULL_SUITE=str(upstream/'suites/public-v2.json'),BENCH_ROUNDS='25',BENCH_PAIRS='500000',GATE_BUDGET_SECONDS='900',VERIFY_TOTAL_TIMEOUT='2700')
    with (out/'retained-stage-profile.log').open('wb') as log:
        try:
            code=subprocess.run(argv,cwd=upstream,env=env,stdout=log,stderr=subprocess.STDOUT,timeout=660).returncode
        except subprocess.TimeoutExpired:
            code=124
    after={str(p.relative_to(out)):hashlib.sha256(p.read_bytes()).hexdigest() for p in (summary_path,verdict)}
    assert before==after, 'Original gate/summary changed during diagnostics'
    result_path=profile_out/'profile-retained-result.json'
    result=json.loads(result_path.read_bytes()) if result_path.exists() else {}
    complete=bool(code==0 and result.get('complete'))
    receipt={'diagnostic_only':True,'complete':complete,'exit_code':code,'seed':plan['seed'],
        'original_adapter_sha256':hashlib.sha256(original_path.read_bytes()).hexdigest(),
        'wrapper_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'original_before_sha256':before,'original_after_sha256':after,
        'result_sha256':hashlib.sha256(result_path.read_bytes()).hexdigest() if result_path.exists() else None,
        'scope':'Original adapter/full gates execute in nested diagnostic output. Original source/verdict/summary unchanged. Profiling is excluded from scored selection and dashboard sample index.'}
    (out/'retained-profile-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    if not complete:raise RuntimeError('Retained41 diagnostic incomplete/failed; original gates and raw diagnostic evidence retained')
