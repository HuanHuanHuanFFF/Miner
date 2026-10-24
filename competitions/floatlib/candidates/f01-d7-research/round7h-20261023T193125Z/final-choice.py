"""Bind the pre-observation final choice to its original indexed full evidence."""
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import random
import statistics

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
PREDECLARED_SHA = '7b6310569f39a0fed4d71331b0b28abe8899537608773b73c22b214a5605c38b'
NEW_D = 40047321773
BASE = 'f01-r8-combined-result-guard'


def require(ok, message):
    if not ok:
        raise ValueError(message)


def compare(packet, candidate, baseline):
    cv, bv = (packet['verdicts'][n] for n in (candidate, baseline))
    values = [[sub/inc for inc, sub in v['rounds']] for v in (cv, bv)]
    rng = random.Random(90423)
    gains = sorted(1-statistics.median(values[0][rng.randrange(25)] for _ in range(25))/
                   statistics.median(values[1][rng.randrange(25)] for _ in range(25))
                   for _ in range(2000))
    k = .05*1999; lo = int(k)
    return {'relative_normalized_ratio': cv['ratio']/bv['ratio'],
            'gain_p05': gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)}


def choose(pre, new_full, new_screen, versus_backup):
    take_new = bool(new_full and new_screen['relative_normalized_ratio'] <= .97 and
                    new_screen['gain_p05'] > 0 and
                    versus_backup['relative_normalized_ratio'] < 1 and
                    versus_backup['gain_p05'] > 0)
    return {'candidate': pre['new_candidate'] if take_new else pre['backup_candidate'],
            'sha256': pre['new_sha256'] if take_new else pre['backup_sha256'],
            'discovery': NEW_D if take_new else pre['backup_first_clean_D_run']}


def evaluate():
    raw = (HERE/'final-selection-predeclared.json').read_bytes()
    require(hashlib.sha256(raw).hexdigest() == PREDECLARED_SHA, 'Pre-observation policy changed')
    pre = json.loads(raw)
    spec = importlib.util.spec_from_file_location('r11_final_guard', HERE.parent/'adoption-guard.py')
    g = importlib.util.module_from_spec(spec); spec.loader.exec_module(g)
    new, backup = pre['new_candidate'], pre['backup_candidate']
    # The baseline-only load authenticates the complete original artifact tree,
    # request, source HEAD, suite and execution even if the new candidate failed.
    observed = g.load_run(ROOT, HERE.parent, NEW_D, (BASE,))
    require([r['candidate'] for r in observed['plan']['candidates']] == pre['next_full_D_candidates'], 'Wrong final discovery order')
    require(observed['plan'].get('sample_role') == 'DISCOVERY' and not observed['codegen_present'], 'Final discovery is not clean')
    run_dir = ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(NEW_D)
    index = json.loads((run_dir/'original-artifact-hashes.json').read_bytes())
    evidence = run_dir/index['directory']/'diagnostics/f01-d7-public-suite/public-suite'
    summary = json.loads((evidence/'summary.json').read_bytes())
    require([r['candidate'] for r in summary['results']] == pre['next_full_D_candidates'], 'Incomplete final discovery')
    for name, expected in ((new,pre['new_sha256']),(backup,pre['backup_sha256'])):
        raw = g.read_tree_blob(ROOT, observed['evidence']['source_commit'],
                              'competitions/floatlib/candidates/'+name+'/Kernel.lean')
        require(raw == (evidence/'inputs'/name/'Kernel.lean').read_bytes() and
                hashlib.sha256(raw).hexdigest() == expected, 'Final exact sources changed')
    new_full = all(r.get('full_gate') is True and r.get('stage') == 'score' and r.get('exit_code') == 0
                   for r in summary['results'])
    ns = nb = None
    new_evidence = observed['evidence']
    if new_full:
        require(observed['run_conclusion'] == observed['job_conclusion'] == 'success', 'Passing source with unsuccessful wrapper requires inspection')
        new_packet = g.load_run(ROOT, HERE.parent, NEW_D, (new, backup, BASE))
        ns, nb = compare(new_packet, new, BASE), compare(new_packet, new, backup)
        new_evidence = new_packet['evidence']
    old = g.load_run(ROOT, HERE.parent, pre['backup_first_clean_D_run'], (backup, BASE))
    require(old['run_conclusion'] == old['job_conclusion'] == 'success', 'Backup first discovery was unsuccessful')
    require(old['kernel_hashes'][backup] == pre['backup_sha256'] and
            old['plan'].get('sample_role') == 'DISCOVERY' and not old['codegen_present'], 'Backup first discovery identity changed')
    bs = compare(old, backup, BASE)
    require(bs['relative_normalized_ratio'] <= .97 and bs['gain_p05'] > 0, 'Backup first discovery did not qualify')
    return {'schema_version': 1, 'predeclared_sha256': PREDECLARED_SHA,
            'new_discovery': NEW_D, 'new_full_gate': new_full,
            'new_results': [{k:r.get(k) for k in ('candidate','kernel_sha256','stage','full_gate','exit_code','reason')} for r in summary['results']],
            'new_vs41': ns, 'new_vs_backup': nb,
            'backup_first_D': pre['backup_first_clean_D_run'], 'backup_first_D_vs41': bs,
            'choice': choose(pre, new_full, ns, nb),
            'new_evidence': new_evidence, 'backup_first_D_evidence': old['evidence']}


def validate(candidate, discovery):
    actual = evaluate()
    saved = json.loads((HERE/'final-selection-receipt.json').read_bytes())
    require(all(saved.get(k) == v for k, v in actual.items()), 'Final selection receipt differs from original evidence')
    require(actual['choice']['candidate'] == candidate and actual['choice']['discovery'] == discovery,
            'Candidate/D violates pre-observation choice; backup must use first cleanD930')
    return actual


if __name__ == '__main__':
    result = evaluate()
    result['recorded_at_utc'] = datetime.now(timezone.utc).isoformat()
    with (HERE/'final-selection-receipt.json').open('x', encoding='utf-8', newline='\n') as out:
        out.write(json.dumps(result, ensure_ascii=False, indent=2)+'\n')
    print(json.dumps({k: result[k] for k in ('choice','new_vs41','new_vs_backup','backup_first_D_vs41')}))
