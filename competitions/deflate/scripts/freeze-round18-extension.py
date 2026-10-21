"""Freeze the accepted extension pair and two fresh runner orders before dispatch."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import copy
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def read(p):
    return json.loads(p.read_bytes())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--sf', choices=['r18-rf-sf-content-proof1', 'r18-rf-sf-inline'], required=True)
    ap.add_argument('--selection-evidence', required=True)
    args = ap.parse_args()
    assert (ROOT / args.selection_evidence).is_file()
    names = [args.sf, 'r18-586-selective-rf', 'r18-539-csv-lazy-content']
    accepted = {}
    for name in names:
        path = ROOT / 'candidates' / name
        cert = read(path / 'VERIFICATION.json')
        assert cert['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
        assert all(hashlib.sha256((path / f).read_bytes()).hexdigest() == h for f, h in cert['files'].items())
        accepted[name] = cert
    bf, bj = read(E / 'baseline-bf.json'), read(E / 'screen-bj.json')
    refs = {e['name']: copy.deepcopy(e) for e in bf['entries'] if e['name'] in
            ['probe3', 'r3-432-fast3', 'public432', 'public514', 'public586', 'public586-shadow', 'public591', 'public591-shadow']}
    refs.update({e['name']: copy.deepcopy(e) for e in bj['entries'] if e['name'] in ['public539', 'public539-shadow']})
    entries = list(refs.values())
    candidate_entries = []
    for name in names:
        anchor = 'public539' if name == 'r18-539-csv-lazy-content' else 'public586'
        parent = 'r18-586-selective-rf' if name == args.sf else anchor
        candidate_entries.append({'name': name, 'path': 'candidates/' + name, 'control': False,
                                  'hashes': accepted[name]['files'], 'anchor': anchor,
                                  'comparison_baseline': parent, 'native_decode_reference': anchor})
    entries += candidate_entries
    assert len(entries) == 13 and len({e['name'] for e in entries}) == 13
    order = [e['name'] for e in entries]
    rotate = order[len(order) // 2:] + order[:len(order) // 2]
    orders = [order, order[::-1], rotate]
    for batch, sequence in [('confirm-bq', orders), ('confirm-br', [o[::-1] for o in orders])]:
        spec = copy.deepcopy(bf)
        spec.update(entries=entries, screen_blocks=3, screen_orders=sequence,
                    snapshot_pages='evidence/round18/official-extension-70m/pareto-pages.json',
                    r18_role='independent_confirmation', r18_dispatch_after_gate_pair_known=True,
                    synthetic_validation=False, extract_candidates=[], shortlist=0,
                    gate_candidates=[], gate_limit=0, refine_blocks=0,
                    description='Predeclared extension frozen-pair confirmation: three original1+11 total-time blocks on a newrunner, same-source539/586/591anchors. Primarypair is acceptedSFimplementation plus oldselectiveRF; additionalaccepted539CSV pair remains independentalternative evidence. Bothrunnerorders andallfilehashes frozenbeforefirstdispatch. No result-dependent extra blocks orsourcechanges. Cap45jobminutes; fixed04:32:51UTCdeadline.')
        path = E / (batch + '.json')
        assert not path.exists()
        path.write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    targets = [dict(candidate_entries[0], role='A'), dict(candidate_entries[1], role='B')]
    plan = {
        'status': 'FROZEN_EXTENSION_TWO_RUNNER_CONFIRMATION_PLAN',
        'declared_at_utc': datetime.now(timezone.utc).isoformat(),
        'first_batch': 'confirm-bq', 'first_run_id': None, 'second_batch': 'confirm-br', 'second_run_id': None,
        'blocks_per_runner': 3, 'planned_total_final_blocks': 6,
        'candidates': targets, 'additional_validation_candidates': [candidate_entries[2]],
        'selection_evidence': args.selection_evidence,
        'predeclared_design': 'evidence/round18/extension-confirmation-design.json',
        'roles': {'A': '15percent target, not achieved or promised by selection', 'B': '5percent target, not achieved or promised by selection'},
        'source_and_proof_changes_during_confirmation': False, 'result_dependent_repetition': False,
        'job_cap_minutes': 45, 'deadline_utc': '2026-10-10T04:32:51+00:00',
        'scope': 'Every submitted pair must already have an exact complete original public gate certificate. Six blocks on two independent runners, all original per-file total reps and paired incumbents. Primary539/586 references plus same-binary shadows and same-block591 sensitivity. Formal admission and payout are UNKNOWN; no upload or wallet operation.',
    }
    path = E / 'extension-final-confirmation-plan.json'
    assert not path.exists()
    path.write_bytes((json.dumps(plan, indent=2) + '\n').encode())
    print(json.dumps({'candidates': targets, 'additional': candidate_entries[2], 'blocks_per_runner': 3, 'entries': len(entries)}, indent=2))


if __name__ == '__main__':
    main()
