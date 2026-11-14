"""Replay the fixed R19 public-gate verifier, with only the R22 receipt path mapped.

No policy, original gate, source, benchmark or CI mutation. A single passed discovery
never adopts a source; original checks and two fresh frozen confirmations still apply.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random
import statistics
import sys
import types

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OWN = HERE.parent.parent
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()

if __name__ == '__main__':
    run, candidate, candidate_sha, head = sys.argv[1:]
    baseline = 'f01-r15-dev-packed-b2-1'
    rp = HERE.parent / 'ci-runs' / run
    ip = rp / 'original-artifact-hashes.json'
    ix = json.loads(ip.read_bytes())
    assert str(ix['artifact']['workflow_run']['id']) == run
    assert ix['artifact']['workflow_run']['head_sha'] == head
    base = (rp / ix['directory']).resolve()
    assert base.is_relative_to(rp.resolve())
    suite = base / 'diagnostics/f01-d7-public-suite/public-suite'
    summary = json.loads((suite / 'summary.json').read_bytes())
    verdicts = {n: json.loads((suite / f'{n}-verdict.json').read_bytes()) for n in (candidate, baseline)}
    assert sha(suite / f'inputs/{candidate}/Kernel.lean') == candidate_sha
    assert sha(suite / f'inputs/{baseline}/Kernel.lean') == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    out = {'utc': datetime.now(timezone.utc).isoformat(), 'run': int(run), 'head': head,
           'candidate': candidate, 'source_sha256': candidate_sha, 'index_sha256': sha(ip),
           'original_files': len(ix['files']), 'original_bytes': sum(x['bytes'] for x in ix['files'].values()),
           'scope': 'Original released discovery evidence only; two fresh frozen confirmations and complete adoption audit still required. No formal/private/champion score inherited.'}
    both = all(v.get('passed') and v.get('mode') == 'gate' and v.get('stage') == 'score'
               and len(v.get('rounds', [])) == 25 for v in verdicts.values())
    if not both:
        for name, meta in ix['files'].items():
            p = (base / name).resolve()
            assert p.is_relative_to(base) and p.stat().st_size == meta['bytes'] and sha(p) == meta['sha256']
        out.update(state='ORIGINAL_BYTES_VERIFIED_GATE_INCOMPLETE_NO_METRICS',
                   results={n: {k: v.get(k) for k in ('passed', 'stage', 'reason')} for n, v in verdicts.items()})
    else:
        old_path = OWN / 'round9h-20261026T194639Z/adoption-guard.py'
        old = old_path.read_text(encoding='utf-8')
        before = "rp = root / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs' / str(rid)"
        after = "rp = root / 'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs' / str(rid)"
        assert old.count(before) == 1
        mapped = old.replace(before, after)
        g = types.ModuleType('fixed_public_guard_R22_path_only')
        g.__file__ = str(old_path)
        exec(compile(mapped, str(old_path), 'exec'), g.__dict__)
        packet = g.load_run(ROOT, OWN, int(run), (candidate, baseline))
        assert packet['kernel_hashes'][candidate] == candidate_sha and packet['evidence']['source_commit'] == head
        assert all(v['verifier_fingerprint'] == v['verifier_fingerprint_end'] for v in packet['verdicts'].values())
        relative = verdicts[candidate]['ratio'] / verdicts[baseline]['ratio']
        values = [[sub / inc for inc, sub in verdicts[n]['rounds']] for n in (candidate, baseline)]
        rng = random.Random(90423)
        gains = []
        for _ in range(2000):
            medians = [statistics.median(v[rng.randrange(25)] for _ in range(25)) for v in values]
            gains.append(1 - medians[0] / medians[1])
        gains.sort()
        k = .05 * 1999
        lo = int(k)
        p05 = gains[lo] + (gains[lo + 1] - gains[lo]) * (k - lo)
        ops = {}
        for op in ('add', 'mul', 'sum', 'bmm'):
            sums = {n: {kind: sum(v['classes'][c][kind + '_ns'] * work
                                     for c, work in packet['cell_work'].items() if c.startswith(op + ':'))
                        for kind in ('submission', 'incumbent')} for n, v in verdicts.items()}
            ops[op] = (sums[candidate]['submission'] / sums[candidate]['incumbent']) / (sums[baseline]['submission'] / sums[baseline]['incumbent'])
        out.update(state='ORIGINAL_COMPLETE_PUBLIC_DISCOVERY_VERIFIED', full_gate_both=True,
                   fixed_verifier_sha256=sha(old_path), path_only_mapped_sha256=hashlib.sha256(mapped.encode()).hexdigest(),
                   mapped_expression_count=1, evidence=packet['evidence'], relative_normalized_ratio=relative,
                   gain_p05=p05, per_operation_normalized=ops, discovery_screen_passed=relative <= .97 and p05 > 0,
                   original_rounds=25, bootstrap_replicates=2000, bootstrap_seed=90423,
                   codegen_observer_present=packet['codegen_present'], adoption='NOT_ESTABLISHED_BY_ONE_DISCOVERY')
    (HERE / f'originals-verified-{run}-public-discovery.json').write_text(json.dumps(out, indent=2) + '\n')
    print(json.dumps({k: v for k, v in out.items() if k not in ('evidence',)}))
