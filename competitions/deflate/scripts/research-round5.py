"""CI-only extraction/cost diagnostics. Never certifies a complete Lean gate."""
from __future__ import annotations
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from round4 import ROOT, validate, save


def main():
    spec = validate(os.environ['ROUND4_SPEC'])
    names = spec.get('extract_candidates', [])
    differential = spec.get('cost_differential', False)
    if not names and not differential:
        print('ROUND5_RESEARCH_NOT_REQUESTED'); return
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and sys.platform == 'linux'
    assert os.environ['GITHUB_REPOSITORY'] == 'HuanHuanHuanFFF/Miner'
    upstream = Path(os.environ['DEFLATE_ROOT']).resolve()
    output = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/research5'
    output.mkdir(parents=True, exist_ok=True)
    entries = {e['name']: e for e in spec['entries']}
    assert len(names) == len(set(names)) <= 3 and set(names) <= set(entries)
    report = {'scope': 'Research-only extraction and cost comparison; not complete proof, admission or timing evidence',
              'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'],
              'batch': os.environ['ROUND4_SPEC'], 'spec': spec, 'extractions': {}, 'cost_differential': None}
    save(output / 'research.json', report)
    for name in names:
        folder = output / name
        folder.mkdir(exist_ok=True)
        command = [str(upstream / '.venv/bin/python'), 'validator/verifier/verify.py',
                   str(ROOT / entries[name]['path'] / 'parse.rs'), '--stage', 'extract', '--keep', 'always']
        proc = subprocess.run(command, cwd=upstream, capture_output=True, text=True, timeout=1100)
        log = proc.stdout + proc.stderr
        (folder / 'extract-only.log').write_text(log)
        verdict = {'exit_code': proc.returncode, 'extraction_accepted': proc.returncode == 0,
                   'source_sha256': entries[name]['hashes']['parse.rs'], 'files': {}, 'proof_status': 'NOT_RUN'}
        match = re.search(r'^workspace: (.+)$', log, re.M)
        if match:
            work = Path(match[1].strip()).resolve()
            assert work.parent == (upstream / 'data/verification-workspace').resolve()
            for filename in ('Types.lean', 'Constants.lean', 'Funs.lean'):
                src = work / 'lean/Slot' / filename
                if src.is_file():
                    data = src.read_bytes(); assert len(data) <= 10_000_000
                    (folder / filename).write_bytes(data)
                    verdict['files'][filename] = {'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
            for src in (work / 'logs').glob('*.log'):
                data = src.read_bytes(); assert len(data) <= 10_000_000
                (folder / src.name).write_bytes(data)
        report['extractions'][name] = verdict
        save(output / 'research.json', report)
        print('RESEARCH_EXTRACTION', name, proc.returncode, 'PROOF_NOT_RUN', flush=True)
        if proc.returncode == 2:
            raise RuntimeError('Official extraction infrastructure failed; inspect retained logs')
    if differential:
        module_spec = importlib.util.spec_from_file_location('r5_generator', ROOT / 'scripts/make-round5-opt.py')
        generator = importlib.util.module_from_spec(module_spec)
        module_spec.loader.exec_module(generator)
        build = Path(os.environ['RUNNER_TEMP']) / 'round5-cost-diagnostic'
        build.mkdir(exist_ok=True)
        source = build / 'cost-check.rs'
        source.write_text(generator.diagnostic_source(upstream))
        binary = build / 'cost-check'
        compiled = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C',
                                   'overflow-checks=yes', str(source), '-o', str(binary)], capture_output=True, text=True, timeout=180)
        (output / 'cost-build.log').write_text(compiled.stdout + compiled.stderr)
        cost = {'compile_exit': compiled.returncode, 'runtime_exit': None, 'cases': None,
                'status': 'FAILED', 'driver_sha256': hashlib.sha256(source.read_bytes()).hexdigest()}
        if compiled.returncode == 0:
            measured = subprocess.run([str(binary)], capture_output=True, text=True, timeout=180)
            (output / 'cost-runtime.log').write_text(measured.stdout + measured.stderr)
            cost['runtime_exit'] = measured.returncode
            count = re.search(r'^COST_DIFFERENTIAL_OK (\d+)$', measured.stdout, re.M)
            if measured.returncode == 0 and count:
                cost.update(status='FINITE_COST_DIFFERENTIAL_PASSED', cases=int(count[1]))
        report['cost_differential'] = cost
        save(output / 'research.json', report)
        print('COST_DIAGNOSTIC', json.dumps(cost), flush=True)
    subprocess.run(['git', 'diff', '--exit-code'], cwd=upstream, check=True)


if __name__ == '__main__':
    main()
