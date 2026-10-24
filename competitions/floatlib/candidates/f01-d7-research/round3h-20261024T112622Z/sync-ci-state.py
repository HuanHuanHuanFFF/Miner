"""Rebuild only this round's CI state from frozen requests and exact receipts."""
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import uuid

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
RUNS = ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
STATE = ROOT/'competitions/floatlib/coordination/development-status.json'


def read(path):
    return json.loads(path.read_bytes())


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def save_atomic(path, value):
    tmp = path.with_name(path.name+'.r13-'+uuid.uuid4().hex+'.tmp')
    try:
        with tmp.open('x', encoding='utf-8', newline='\n') as stream:
            stream.write(json.dumps(value, ensure_ascii=False, indent=2)+'\n')
        os.replace(tmp, path)
    finally:
        if tmp.exists():
            tmp.unlink()


def main():
    state_raw = STATE.read_bytes()
    state = json.loads(state_raw)
    round_state = state['research_round']
    assert round_state['id'] == 'R13-20261024T112622Z'
    prepared = {int(p.stem.split('-')[1]): p for p in HERE.glob('plan-*.json')}
    rows = []
    seeds = set()
    for path in sorted(RUNS.glob('dispatch-*/dispatch.json')):
        receipt = read(path)
        if receipt.get('state') != 'RUN_IDENTIFIED':
            continue
        seed = int(receipt['inputs']['seed'])
        if seed not in prepared:
            continue
        assert seed not in seeds, 'More than one identified run for an R13 seed'
        seeds.add(seed)
        plan_path = prepared[seed]
        plan = read(plan_path)
        assert receipt['inputs']['allow_private'] == 'false'
        diagnostic = plan.get('kind') == 'PROFILE_DIAGNOSTIC'
        wrapper = 'f01-d13-cost-profile' if diagnostic else 'f01-d7-public-suite'
        assert receipt['inputs']['candidates'] == wrapper
        assert receipt['run']['headSha'] == receipt['source_commit']
        key = ('competitions/floatlib/candidates/f01-d13-cost-profile/profile-request.json'
               if diagnostic else 'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json')
        if diagnostic:
            # Original ci.py binds the wrapper; this additional request is
            # independently frozen and read back from the exact run commit.
            import subprocess
            raw = subprocess.check_output(['git', 'show', receipt['source_commit']+':'+key], cwd=ROOT)
            assert hashlib.sha256(raw).hexdigest() == plan['profile_request_sha256']
            freeze=read(HERE/f'freeze-{seed}.json')
            assert freeze['request_sha256']==digest(plan_path)
            for name, expected in freeze['files'].items():
                actual=subprocess.check_output(['git','show',receipt['source_commit']+':'+name],cwd=ROOT)
                assert hashlib.sha256(actual).hexdigest()==expected['sha256'] and len(actual)==expected['bytes'],name
        else:
            assert receipt['frozen_file_sha256'][key] == digest(plan_path)
        run = receipt['run']['databaseId']
        row = {'run': run, 'seed': seed, 'source_commit': receipt['source_commit'],
               'state': 'DISPATCH_IDENTIFIED_WAITING_TERMINAL_COLLECTION',
               'candidates': [x['candidate'] for x in plan['candidates']],
               'role': plan['sample_role'],
               'capture_codegen': [x['candidate'] for x in plan['candidates'] if x.get('capture_codegen')],
               'collected': False, 'dispatch_receipt': path.relative_to(ROOT).as_posix()}
        folder = RUNS/str(run)
        ci_path = folder/'ci-run.json'
        index_path = folder/'original-artifact-hashes.json'
        # ci.py writes the complete raw job log last. Artifact download alone
        # must not appear as collected while the collector is still running.
        log_path = folder/'ci.log'
        if ci_path.exists() and index_path.exists() and log_path.is_file() and log_path.stat().st_size > 0:
            ci, index = read(ci_path), read(index_path)
            assert ci['databaseId'] == run and ci['headSha'] == row['source_commit']
            assert ci['status'] == 'completed'
            artifact = (folder/index['directory']).resolve()
            assert artifact.is_relative_to(folder.resolve())
            for relative, info in index['files'].items():
                file = (artifact/relative).resolve()
                assert file.is_relative_to(artifact)
                assert file.stat().st_size == info['bytes'] and digest(file) == info['sha256']
            summary_path = (artifact/'diagnostics/f01-d13-cost-profile/cost-profile/summary.json'
                            if diagnostic else artifact/'diagnostics/f01-d7-public-suite/public-suite/summary.json')
            row.update(state='TERMINAL_COLLECTED_'+str(ci['conclusion']).upper(),
                       conclusion=ci['conclusion'], collected=True,
                       raw_ci_log_sha256=digest(log_path), raw_ci_log_bytes=log_path.stat().st_size)
            if diagnostic and summary_path.exists():
                summary = read(summary_path)
                assert summary['dispatch_seed'] == seed and summary['source_commit'] == row['source_commit']
                assert summary['requested_plan_sha256'] == plan['profile_request_sha256']
                assert summary['source_sha256'] == plan['candidates'][0]['sha256']
                assert summary['diagnostic_only'] is True and summary['full_gate'] is False
                row.update(summary=summary_path.relative_to(ROOT).as_posix(),
                           summary_sha256=digest(summary_path), diagnostic_only=True,
                           results=[{'candidate':row['candidates'][0], 'kernel_sha256':summary['source_sha256'],
                                     'full_gate':False, 'diagnostic_only':True}], unexecuted_candidates=[])
            elif not diagnostic and summary_path.exists():
                summary = read(summary_path)
                assert summary['seed'] == seed and summary['source_commit'] == row['source_commit']
                assert summary['requested_plan_sha256'] == digest(plan_path)
                actual = [x['candidate'] for x in summary['results']]
                assert actual == row['candidates'][:len(actual)]
                if summary.get('complete') is True:
                    assert actual == row['candidates']
                row.update(summary=summary_path.relative_to(ROOT).as_posix(),
                           summary_sha256=digest(summary_path),
                           results=[{k: x.get(k) for k in ('candidate', 'kernel_sha256', 'full_gate', 'statement_pass', 'stage', 'exit_code')}
                                    for x in summary['results']],
                           unexecuted_candidates=row['candidates'][len(actual):])
            else:
                # A wrapper failure can precede the actual candidate adapter. Do
                # not manufacture candidate failures or timing zeros from it.
                outer_path = artifact/'summary.json'
                outer = read(outer_path)
                assert int(outer['run_id']) == run and outer['source_commit'] == row['source_commit']
                assert len(outer['results']) == 1 and outer['results'][0]['candidate'] == wrapper
                verdict_path = artifact/outer['results'][0]['verdict']
                verdict = read(verdict_path)
                assert verdict.get('passed') is False and ci['conclusion'] != 'success'
                row.update(state='OUTER_ADAPTER_FAILURE_COLLECTED', results=[],
                           summary=outer_path.relative_to(ROOT).as_posix(), summary_sha256=digest(outer_path),
                           unexecuted_candidates=row['candidates'],
                           outer_failure={'verdict': verdict_path.relative_to(ROOT).as_posix(),
                                          'sha256': digest(verdict_path), 'stage': verdict['stage'],
                                          'reason': verdict.get('reason', '')})
        rows.append(row)
    rows.sort(key=lambda x: x['seed'])
    completed = [x['run'] for x in rows if x['collected']]
    assert set(round_state['completed_ci']) <= set(completed), 'Previously collected CI would disappear'
    assert len({x['run'] for x in rows}) == len(rows)
    round_state['started_ci'] = rows
    round_state.pop('experiments', None)
    round_state['completed_ci'] = completed
    round_state['active_ci'] = [x['run'] for x in rows if not x['collected']]
    round_state['ci_state_schema'] = 'CANONICAL_STARTED_CI_RECORDS_FROM_FROZEN_REQUESTS'
    state['updated_at_utc'] = datetime.now(timezone.utc).isoformat()
    assert STATE.read_bytes() == state_raw, 'Concurrent state write'
    save_atomic(STATE, state)
    print(json.dumps({'started': len(rows), 'collected': len(completed), 'active': round_state['active_ci'],
                      'scope': 'Receipt inventory only; source/full-gate acceptance remains the original verifier.'}))


if __name__ == '__main__':
    main()
