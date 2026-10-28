"""Fixed original-byte and independent four-column log checks for released batches."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import sys

HERE = Path(__file__).resolve().parent
BATCHES = {
    '40596173085': ('96c66ba12f988791010775bbec95109a1926d733', [
        ('f01-r22-dev-flat-scale-cost2', 'ef1fa46164ecce62cb27c7f101d488eff386c03f21c19636760832f79c04926b', ['flatadd', 'flatmul']),
        ('f01-r22-dev-pair8-cost1', '0ec168de06c5e2da6098ff362b4adc07946bb5f42d81fd06309bd8d246706fd8', ['quad', 'prepared', 'pair8'])]),
    '40602369221': ('7bb32397178df619cb046d9976df6d054643a5d9', [
        ('f01-r22-dev-resident8-cost1', '24c60123b76214c4da31d2765fca0010985c0289dad77e8bc18b2de507625e34', ['pair8', 'resident8']),
        ('f01-r22-dev-broadword-cost1', '0274763264d760775e6a447848e873db418adc2e6fb651d117c5fc04b4b5d4a5', ['broadword'])]),
    '40607316341': ('11d392ce4eb099cb74b9c3a9be8fb7846fb112e8', [
        ('f01-r22-dev-multistatic-cost1', 'fd4e5b5144d00f3413b0b367a748e9be8f55d51017b4a8aaa5be53d404b1d6c1',
         ['inlineOld', 'outline', 'nativeprod', 'resident16'])]),
    '40608387129': ('808bab5c47efa87a88015092c5416b739e0e4a61', [
        ('f01-r22-dev-farstatic-cost1', 'cdf46f51fd945232af9784fd021e6a931f17b275d1a567a78ba0ec924f0776c2', ['far'])]),
    '40611570030': ('25281fa9f694f68af31f28817400ea92e447aaa5', [
        ('f01-r22-dev-nativecold-cost1', '5d610468556f5660c0b80551be22149c9d086badbe10342ddecc3f6509ea8d93',
         ['th0', 'nativeinline', 'nativecold', 'nativeadd']),
        ('f01-r22-dev-indexed8-cost1', '8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd', ['raw8', 'indexed8'])]),
    '40612985754': ('81edb6cfaa8d8b0dce2d2a1a061f5feb3c87c8e6', [
        ('f01-r22-dev-wordcarry-cost1', 'e0550cec2fccc7a555f3247d5c95815771117c41e2ca518e36fd7dcea2e99b70', ['oldword', 'wordcarry'])]),
    '40621932164': ('b7fd7e0fd9cec435b4ee5aace81772a448289101', [
        ('f01-r22-dev-endpoint-cost1', 'ade42f0ab6c69db3f2e0eb3a4520587cd6fd552f7697912c026149065bf98efa', ['oldnative', 'endpoint'])]),
}

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def verify(run_id):
    head, candidates = BATCHES[run_id]
    run = HERE.parent / 'ci-runs' / run_id
    ip = run / 'original-artifact-hashes.json'
    index = json.loads(ip.read_bytes())
    assert str(index['artifact']['workflow_run']['id']) == run_id
    assert index['artifact']['workflow_run']['head_sha'] == head
    base = (run / index['directory']).resolve()
    assert base.is_relative_to(run.resolve())
    total = 0
    for name, meta in index['files'].items():
        p = (base / name).resolve()
        assert p.is_relative_to(base) and p.stat().st_size == meta['bytes'] and sha(p) == meta['sha256'], name
        total += meta['bytes']
    suite = base / 'diagnostics/f01-d7-public-suite/public-suite'
    parsed = 0
    outputs = []
    for candidate, source_sha, variants in candidates:
        assert sha(suite / 'inputs' / candidate / 'Kernel.lean') == source_sha
        cost = suite / 'diagnostics' / candidate / 'runtime-cost'
        result = json.loads((cost / 'result.json').read_bytes())
        assert result['source_sha256'] == source_sha and result['complete'] and result['measurement_complete']
        assert result['official_originals_unchanged'] and result['full_gate'] is False
        assert all(v['equal_after_only_root_target_path_mapping'] for v in result['flags_and_link'].values())
        order = [x for v in variants for x in ('control', v, v, 'control')]
        assert len(result['runs']) == 2 * len(order)
        ratios = []
        for seed in (2220001, 2220003):
            plan = json.loads((cost / f'plan-{seed}.json').read_bytes())
            cases = {c['name']: c for c in plan['cases']}
            assert len(cases) == 156 and sum(c['timed'] for c in cases.values()) == 152
            logs = []
            for i, variant in enumerate(order):
                rows = {}
                for line in (cost / f'{seed}-{i}-{variant}.log').read_text().splitlines():
                    match = re.fullmatch(r'(\S+) (true|false) ([0-9]+) ([0-9]+)', line)
                    assert match, line
                    name, flag, ns, checksum = match.groups()
                    assert name not in rows
                    rows[name] = {'timed': flag == 'true', 'best_ns': int(ns), 'checksum': int(checksum)}
                assert set(rows) == set(cases)
                assert all(rows[n]['timed'] == cases[n]['timed'] for n in rows)
                assert rows == json.loads((cost / f'{seed}-{i}-{variant}-rows.json').read_bytes())
                if logs:
                    assert all(rows[n]['checksum'] == logs[0][n]['checksum'] for n in rows)
                logs.append(rows)
                parsed += len(rows)
            for vi, variant in enumerate(variants):
                for block, control, trial in ((0, 4 * vi, 4 * vi + 1), (1, 4 * vi + 3, 4 * vi + 2)):
                    computed = {}
                    for op in ('add', 'mul', 'sum', 'bmm', 'whole'):
                        names = [n for n, c in cases.items() if c['timed'] and (op == 'whole' or c['kernel'] == op)]
                        computed[op] = sum(logs[trial][n]['best_ns'] for n in names) / sum(logs[control][n]['best_ns'] for n in names)
                    original = next(p for p in result['pairs'] if p['seed'] == seed)[f'{variant}_block_{block}']
                    assert all(abs(computed[op] - original[op]['variant_over_control']) < 1e-14 for op in computed)
                    ratios.append({'seed': seed, 'variant': variant, 'block': block, 'ratios': computed})
        outputs.append({'candidate': candidate, 'source_sha256': source_sha, 'recomputed': ratios})
    receipt = {'verified_utc': datetime.now(timezone.utc).isoformat(), 'run': run_id, 'head': head,
               'original_files': len(index['files']), 'original_bytes': total, 'index_sha256': sha(ip),
               'raw_rows_independently_parsed': parsed, 'candidate_results': outputs,
               'scope': 'Fixed released discovery batches only. Every slow/control-anomaly sample retained. Not original25round, public proof, adoption, private score, or native recompilation.'}
    (HERE / f'originals-verified-{run_id}-discovery.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps({k: v for k, v in receipt.items() if k != 'candidate_results'}))

if __name__ == '__main__':
    for run_id in sys.argv[1:]:
        verify(run_id)
