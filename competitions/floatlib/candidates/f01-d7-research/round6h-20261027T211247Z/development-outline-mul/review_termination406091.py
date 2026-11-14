"""Reproduce the exact captured termination symptom, not a live resource cause."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
RUN = ROUND / 'ci-runs/40609195034'
RAW = RUN / 'download-13c3d6e7f764416189ed724f687fcfc6'
BASE = RAW / 'diagnostics/f01-d7-public-suite/public-suite'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    index = json.loads((RUN / 'original-artifact-hashes.json').read_bytes())
    count, total = 0, 0
    for relative, item in index['files'].items():
        p = RAW / relative
        assert p.stat().st_size == item['bytes'] and sha(p) == item['sha256']
        count += 1
        total += item['bytes']
    original = json.loads((BASE / 'f01-r22-dev-outline-public1-verdict.json').read_bytes())
    diagnostic = json.loads((BASE / 'f01-r22-dev-outline-public1-failure-statement-diagnostic.json').read_bytes())
    replay = (BASE / 'diagnostics/f01-r22-dev-outline-public1/replay.log').read_text()
    output = (BASE / 'diagnostics/f01-r22-dev-outline-public1/full-build-output.txt').read_bytes()
    assert re.search(r'VerifyFull exit=-15 in 28\.7s', replay)
    assert output.strip() == b''
    assert all(not v['passed'] and not v['exhausted'] and v['stage'] == 'statement' for v in (original, diagnostic))
    capture_path = next((BASE / 'codegen/f01-r22-dev-outline-public1').rglob('capture-record.json'))
    capture = json.loads(capture_path.read_bytes())
    assert not capture['timed_out'] and capture['gate_returncode'] == 1
    assert capture['statement_events'] == capture['snapshot_attempts'] == 0 and not capture['errors']
    helper_dir = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/exact-arithmetic/bias-frontier/shared-block-isolation'
    helpers = []
    for name, expected in (
        ('NatPostClosure.lean', 'cbdb2fb8e83908a6c6179c286b1648891c0186727db53b6d635a5af2689b8f31'),
        ('NoWrapOnly.lean', '8d49e866e3ea7257af5d78709dea54b8b805a7a7f66f7e39ed74e98e8050fe39')):
        p = helper_dir / name
        assert sha(p) == expected
        text = p.read_text()
        helpers.append({'path': str(p), 'sha256': expected, 'bytes': p.stat().st_size,
                        'omega_tokens': len(re.findall(r'\bomega\b', text)),
                        'bv_decide_tokens': len(re.findall(r'\bbv_decide\b', text))})
    public = HERE / 'public/Kernel.lean'
    assert sha(public) == '88cdf318d952d74df95ecabed5e2bbadeab76d4827af1c4e5fd88e43d9d8f054'
    adapter = ROOT / 'competitions/floatlib/candidates/f01-d7-research/public-suite.py'
    provenance = json.loads((BASE / 'provenance.json').read_bytes())
    assert sha(adapter) == provenance['adapter_sha256']
    assert "GATE_BUDGET_SECONDS='900'" in adapter.read_text()
    report = {
        'run': 40609195034, 'all_originals_rehashed': count, 'raw_bytes': total,
        'source_sha256': sha(public), 'symptom_replayed': 'STATEMENT_SIGTERM_WITH_NO_NONWHITESPACE_COMPILER_OUTPUT',
        'original_gate': {'seconds': original['seconds'], 'exhausted': original['exhausted'], 'stage': original['stage'],
                          'actual_subprocess_exit': 'Not present in retained original INFO log; parent reports-15'},
        'failure_diagnostic': {'seconds': diagnostic['seconds'], 'exhausted': diagnostic['exhausted'],
                               'VerifyFull_exit_from_DEBUG_log': -15, 'observed_build_seconds': 28.7,
                               'preserved_full_output_file_bytes': len(output), 'nonwhitespace_output_bytes': len(output.strip())},
        'observer': {k: capture[k] for k in ('timed_out', 'statement_events', 'snapshot_attempts', 'gate_returncode', 'errors')},
        'source_bv_decide_tokens': len(re.findall(r'\bbv_decide\b', public.read_text())), 'helpers': helpers,
        'gate_limits': {'build_timeout_seconds': 1800, 'entry_seconds_default': 600, 'actual_adapter_entry_seconds': 900,
                        'actual_adapter_sha256': sha(adapter), 'build_memory_MB_default': 4096,
                        'timeout_code': 124, 'timeout_signal': 'SIGKILL',
                        'exhausted_detection': '124/OVER_DISK/SIGKILL/SIGXFSZ; not SIGTERM'},
        'cause': 'UNKNOWN for this run. Earlier exact2177 physicalOOM is historical evidence, not a measured cause for88cdf.',
        'loop_scope': 'Read-only exact captured-trace replay. Root owns forthcoming same4GiB live causal probes; no live reproduction or new proof change performed here.'
    }
    (HERE / 'termination-evidence406091.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'originals': count, 'bytes': total, 'symptom': report['symptom_replayed'],
                      'observed_VerifyFull_exit': -15, 'compiler_output_nonwhitespace': 0,
                      'observer_timeout': False, 'public_bv_decide_tokens': report['source_bv_decide_tokens'], 'cause': 'UNKNOWN'}))


if __name__ == '__main__':
    main()
