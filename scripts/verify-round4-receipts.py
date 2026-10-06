"""Verify frozen receipts and replay arithmetic without rewriting original files."""
from __future__ import annotations
import argparse
import ast
import contextlib
from datetime import datetime, timezone
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import re
import subprocess
from unittest.mock import patch

import round4

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round4'


def load(path):
    return json.loads(path.read_text())


def digest(data):
    return hashlib.sha256(data).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--git-index', action='store_true', help='also compare every receipt with its exact staged Git blob')
    args = ap.parse_args()
    manifest = load(OUT / 'receipt-manifest.json')
    spec = importlib.util.spec_from_file_location('round4_collector', ROOT / 'scripts/collect-round4.py')
    collector = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(collector)
    git = subprocess.Popen(['git', '-c', f'safe.directory={ROOT.as_posix()}', 'cat-file', '--batch'],
                           cwd=ROOT, stdin=subprocess.PIPE, stdout=subprocess.PIPE) if args.git_index else None
    credentials = re.compile(rb'(?:gh[pousr]_[A-Za-z0-9]{30,}|github_pat_[A-Za-z0-9_]{40,}|-----BEGIN (?:RSA |EC |OPENSSH )?PRIVATE KEY-----)')
    seen, engines, templates, rustc, cpus = {}, set(), set(), set(), set()
    method_files = files_checked = gate_count = 0
    runs = []
    try:
        for run in manifest['runs']:
            directory = ROOT / run['directory']
            state = load(directory / 'state.json')
            assert state['run_id'] == run['run_id']
            for f in run['files']:
                path = ROOT / f['path']
                assert path.resolve().is_relative_to(OUT.resolve()) and not path.is_symlink()
                data = path.read_bytes()
                assert len(data) == f['bytes'] and digest(data) == f['sha256'], f['path']
                assert not credentials.search(data), ('credential-pattern', f['path'])
                if git:
                    assert '\n' not in f['path'] and '\r' not in f['path']
                    git.stdin.write((':' + f['path'] + '\n').encode()); git.stdin.flush()
                    head = git.stdout.readline().decode().strip().split()
                    assert len(head) == 3 and head[1] == 'blob', head
                    blob = git.stdout.read(int(head[2])); assert git.stdout.read(1) == b'\n'
                    assert digest(blob) == f['sha256'], ('Git changed receipt bytes', f['path'])
                files_checked += 1
            captured = []
            with patch.object(round4, 'save', side_effect=lambda path, value: captured.append((path, value))):
                with contextlib.redirect_stdout(io.StringIO()):
                    collector.analyze(directory)
            assert len(captured) == 1 and captured[0][1] == load(directory / 'analysis.json')
            for measurement in state['metrics']:
                name = measurement['candidate']
                raw = directory / f"round{measurement['round']}-{name}.jsonl"
                lines = [json.loads(line) for line in raw.read_text().splitlines()]
                meta = lines[0]
                engines.add(meta['benchmark_provenance']['engine_sha256'])
                templates.add(meta['benchmark_provenance']['template_sha256'])
                rustc.add(meta['rustc_version']); cpus.add(meta['cpu_model'])
                for row in lines:
                    if row['kind'] != 'file':
                        continue
                    for method in (name, 'incumbent'):
                        obs = row['methods'][method]
                        assert sum(r['phase'] == 'warmup' for r in obs['reps']) == 1
                        assert sum(r['phase'] == 'measured' for r in obs['reps']) == 11
                        key = (meta['methods'][method]['source_sha256'], row['sha256'])
                        value = (row['raw_bytes'], obs['tokens_sha256'], obs['output_sha256'], obs['output_bytes'])
                        assert key not in seen or seen[key] == value, (run['run_id'], name, row['file'])
                        seen[key] = value; method_files += 1
            for name, gate in state['gates'].items():
                if not gate.get('accepted'):
                    continue
                entry = next(e for e in state['spec']['entries'] if e['name'] == name)
                for f, expected in entry['hashes'].items():
                    assert digest((directory / ('input-' + name) / f).read_bytes()) == expected
                log = (directory / (name + '-gate.log')).read_text()
                matches = re.findall(r"depends on axioms: \[([^\]]+)\]", log)
                assert matches and all(set(m.replace("'", '').split(', ')) <= {'propext', 'Classical.choice', 'Quot.sound'} for m in matches)
                assert gate['corpora'] == ['corpus-stage1']
                gate_count += 1
            runs.append({'run_id': run['run_id'], 'paired_processes': len(state['metrics']),
                         'recomputed_analysis_equal': True, 'ci_conclusion': run['ci_conclusion']})
    finally:
        if git:
            git.stdin.close(); assert git.wait() == 0
    assert len(engines) == len(templates) == len(rustc) == 1
    batches = sorted(OUT.glob('batch-*.json'))
    for p in batches:
        round4.validate(p.stem)
    for p in (ROOT / 'scripts').glob('*round4*.py'):
        ast.parse(p.read_text(encoding='utf-8'), filename=str(p))
    result = {'checked_at_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'Frozen receipt hashes, source/inputs, arithmetic replay, output identity, accepted-gate hashes/axiom records and local syntax; no new timing, proof or admission claim.',
              'receipt_files_checked': files_checked, 'git_index_bytes_checked': args.git_index,
              'credential_pattern_hits': 0, 'runs': runs,
              'paired_public_processes': sum(r['paired_processes'] for r in runs),
              'method_file_records': method_files, 'unique_source_input_pairs': len(seen),
              'cross_run_output_conflicts': 0, 'accepted_gate_executions_checked': gate_count,
              'batch_source_proof_preflights': len(batches), 'cpu_models': sorted(cpus),
              'rustc_versions': sorted(rustc), 'engine_sha256': sorted(engines), 'template_sha256': sorted(templates)}
    (OUT / 'final-verification.json').write_text(json.dumps(result, indent=2) + '\n')
    print('VERIFIED', len(runs), 'runs', result['paired_public_processes'], 'paired processes',
          files_checked, 'receipt files', gate_count, 'accepted gate executions; index', args.git_index)


if __name__ == '__main__':
    main()
