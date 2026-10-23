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
    tmp = path.with_name(path.name+'.r11-'+uuid.uuid4().hex+'.tmp')
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
    assert round_state['id'] == 'R11-20261023T193125Z'
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
        assert seed not in seeds, 'More than one identified run for an R11 seed'
        seeds.add(seed)
        plan_path = prepared[seed]
        plan = read(plan_path)
        assert receipt['inputs']['allow_private'] == 'false'
        assert receipt['inputs']['candidates'] == 'f01-d7-public-suite'
        assert receipt['run']['headSha'] == receipt['source_commit']
        key = 'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'
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
        if ci_path.exists() and index_path.exists():
            ci, index = read(ci_path), read(index_path)
            assert ci['databaseId'] == run and ci['headSha'] == row['source_commit']
            assert ci['status'] == 'completed'
            artifact = (folder/index['directory']).resolve()
            assert artifact.is_relative_to(folder.resolve())
            for relative, info in index['files'].items():
                file = (artifact/relative).resolve()
                assert file.is_relative_to(artifact)
                assert file.stat().st_size == info['bytes'] and digest(file) == info['sha256']
            summary_path = artifact/'diagnostics/f01-d7-public-suite/public-suite/summary.json'
            summary = read(summary_path)
            assert summary['seed'] == seed and summary['source_commit'] == row['source_commit']
            assert summary['requested_plan_sha256'] == digest(plan_path)
            assert [x['candidate'] for x in summary['results']] == row['candidates']
            row.update(state='TERMINAL_COLLECTED_'+str(ci['conclusion']).upper(),
                       conclusion=ci['conclusion'], collected=True,
                       summary=summary_path.relative_to(ROOT).as_posix(),
                       summary_sha256=digest(summary_path),
                       results=[{k: x.get(k) for k in ('candidate', 'kernel_sha256', 'full_gate', 'statement_pass', 'stage', 'exit_code')}
                                for x in summary['results']])
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
