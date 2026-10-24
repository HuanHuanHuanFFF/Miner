"""Read-only live pairing authentication; never invokes adoption/model writes."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,math,sys

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
D7=HERE.parent
SOURCE='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
BASE='6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'
CONTROL='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
OPS=('add','mul','sum','bmm')
FIELDS=('run','seed','suite_sha256','official_commit','runner_execution','drawn_plan_sha256','provenance_sha256',
        'incumbent_sha256','reference_champion_sha256','verifier_fingerprint','cell_work')
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def read(path):return json.loads(Path(path).read_bytes())


def module(name,path):
    old=sys.dont_write_bytecode;sys.dont_write_bytecode=True
    try:
        spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
    finally:sys.dont_write_bytecode=old


def main():
    estimator_path=ROOT/'competitions/floatlib/scripts/estimate_champion_time.py'
    adopter_path=HERE/'adopt-three-confirmed.py'
    retained_path=D7/'round7h-20261023T193125Z/retained-estimate-freeze.json'
    retained=read(retained_path)
    assert sha(estimator_path.read_bytes())==retained['estimator_sha256']
    estimator=module('r12_frozen_pair_authentication',estimator_path)
    adopter=module('r12_score_pair_authentication',adopter_path)
    anchor_path=Path(estimator.DEFAULT_ANCHOR);anchor=read(anchor_path)
    assert sha(anchor_path.read_bytes())==retained['anchor_sha256']and anchor['candidate_kernel_sha256']==CONTROL
    estimator.validate_anchor(anchor)
    view=read(D7/'multiplier-comparison.json');index_path=ROOT/view['public_results']
    records=read(index_path)['records']
    full_rows=[r for r in records if r.get('kernel_sha256')==SOURCE and r.get('full_gate')is True]
    runs=sorted(r['run']for r in full_rows);assert len(runs)==len(set(runs))and runs
    scripts={str(p.relative_to(ROOT)):sha(p.read_bytes())for p in (estimator_path,adopter_path,anchor_path,retained_path,HERE/'final-choice-policy.json',Path(__file__))}
    index_sha=sha(index_path.read_bytes())
    # Only these two authenticating constructors are called. No adopter.adopt,
    # prepare_views, estimator.main/save, renderer or state transaction call.
    estimate_pairs=estimator.select_pairs(records,runs,SOURCE,anchor,root=ROOT)
    score_pairs=adopter.scoring_pairs(records,estimate_pairs,estimator,ROOT)
    assert len(estimate_pairs)==len(score_pairs)==len(runs)
    by_score={c['run']:(c,b)for c,b in score_pairs};rows=[]
    for candidate,control in estimate_pairs:
        sc,baseline=by_score[candidate['run']]
        assert candidate==sc and candidate['kernel_sha256']==SOURCE
        assert control['kernel_sha256']==CONTROL and baseline['kernel_sha256']==BASE
        assert all(candidate.get(k)is not None and candidate[k]==control[k]==baseline[k]for k in FIELDS)
        assert set(candidate['classes'])==set(control['classes'])==set(baseline['classes'])==set(candidate['cell_work'])
        totals={};raw_files={}
        for role,row in (('candidate_df5c',candidate),('estimate_control41',control),('score_baseline6c',baseline)):
            sub={op:sum(c['submission_ns']*row['cell_work'][key]for key,c in row['classes'].items()if key.startswith(op+':'))for op in OPS}
            ref={op:sum(c['incumbent_ns']*row['cell_work'][key]for key,c in row['classes'].items()if key.startswith(op+':'))for op in OPS}
            assert all(math.isclose(sub[op],row['operation_total_ns'][op],rel_tol=1e-12)and math.isclose(ref[op],row['operation_reference_total_ns'][op],rel_tol=1e-12)for op in OPS)
            assert math.isclose(sum(sub.values())/sum(ref.values()),row['ratio'],rel_tol=1e-10)
            assert all(math.isclose(sub[op]/sum(sub.values())*100,row['time_share_percent'][op],rel_tol=1e-12)for op in OPS)
            totals[role]={'operation_submission_total_ns':sub,'operation_reference_total_ns':ref,'ratio':row['ratio'],
                         'verdict':row['verdict'],'verdict_sha256':row['verdict_sha256'],'all_raw_cell_recomputations_match':True}
            for item in row['raw_evidence']:
                assert sha((ROOT/item['path']).read_bytes())==item['sha256'];raw_files[item['path']]=item['sha256']
        run_root=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{candidate["run"]}'
        original_path=run_root/'original-artifact-hashes.json';original=read(original_path)
        ci_path=run_root/'ci-run.json';ci=read(ci_path)
        head=original['artifact']['workflow_run']['head_sha']
        provenance_path=ROOT/candidate['runner_execution']/'provenance.json'
        provenance=read(provenance_path)
        assert provenance['source_commit']==head and ci.get('headSha',ci.get('head_sha'))==head
        raw_files[original_path.relative_to(ROOT).as_posix()]=sha(original_path.read_bytes())
        raw_files[ci_path.relative_to(ROOT).as_posix()]=sha(ci_path.read_bytes())
        rows.append({'run':candidate['run'],'seed':candidate['seed'],'source_commit':head,
            'estimate_pair':'df5c/41 AUTHENTICATED_BY_FROZEN_SELECT_PAIRS','score_pair':'df5c/6c AUTHENTICATED_BY_R12_SCORING_PAIRS',
            'matching_fields':{k:candidate[k]for k in FIELDS},'totals':totals,'raw_source_hashes':raw_files,
            'execution_observer':candidate.get('execution_has_observer'),'sample_role':candidate.get('sample_role')})
    assert sha(index_path.read_bytes())==index_sha
    assert all(sha((ROOT/name).read_bytes())==value for name,value in scripts.items())
    report={'state':'LIVE_PAIR_AUTHENTICATION_ONLY_PASS','recorded_at_utc':datetime.now(timezone.utc).isoformat(),
        'source_sha256':SOURCE,'declared_all_full_source_runs':runs,'full_source_row_count':len(rows),
        'index_path':index_path.relative_to(ROOT).as_posix(),'index_sha256':index_sha,'script_and_anchor_sha256':scripts,
        'frozen_estimator_sha256_matches_R11':True,'anchor_control_sha256':CONTROL,'score_baseline_sha256':BASE,
        'pair_functions_called':['Frozen estimator.select_pairs','R12 adopt-three-confirmed.scoring_pairs'],
        'rows':rows,'frozen_A_B':'NOT_YET_AVAILABLE','three_group_selection':'NOT_RUN_NO_FROZEN_A_B',
        'accepted_selection_created':False,'adoption_performed':False,'eligible_for_adoption':'NO_FROM_THIS_RECEIPT',
        'state_model_dashboard_writes':False,'existing_tests_or_CI_run':False,
        'scope':'Read-only raw full-row/41 estimate-pair/6c score-pair authentication and cell-total recomputation. Does not select final candidate, accept a cohort, compute a new model or authorize adoption. Await016 and the predeclared final-choice policy.'}
    (HERE/'scalar-live-pair-preflight.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':report['state'],'runs':runs,'estimate_pairs':len(estimate_pairs),'score_pairs':len(score_pairs),
        'operation_totals':'RAW_MATCH','frozen_A_B':report['frozen_A_B'],'adopt':False},indent=2))


if __name__=='__main__':main()
