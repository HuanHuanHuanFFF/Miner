"""Read-only check of D's current carrier; writes only this worker's receipt."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
TARGET = ROOT / 'competitions/floatlib/candidates/f01-r22-dev-multistatic-cost1'
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    manifest = json.loads((TARGET / 'manifest.json').read_bytes())
    raw = (TARGET / 'Kernel.lean').read_bytes()
    assert sha(raw) == manifest['candidate_sha256'] and len(raw) == manifest['candidate_bytes']
    own = (HERE / 'KernelResident16Cost.lean').read_bytes()
    suffix = own[226829:]
    assert raw.endswith(suffix)
    matrix = HERE.parent / 'development-multistatic/MatrixSuffix.lean.inc'
    assert matrix.read_bytes() == suffix
    base = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
    assert raw[:226829] == base.read_bytes()
    components = []
    for item in manifest['components']:
        path = ROOT / item['path']
        b = path.read_bytes()
        assert sha(b) == item['sha256'] and len(b) == item['bytes']
        components.append({'path': item['path'], 'sha256': sha(b), 'bytes': len(b)})
    caller = HERE.parent / 'development-multistatic/R22MultiStaticCostMain.lean'
    text = caller.read_text(encoding='utf-8')
    assert '@[noinline] def runResident16 : IO UInt32 :=\n  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22Resident16.guarded' in text
    assert text.count('Bench.Suite.run ') == 5
    report = {'status': 'EXACT_MATRIX_INTEGRATION_SOURCE_PASS',
        'carrier_sha256': sha(raw), 'carrier_bytes': len(raw),
        'own_matrix_kernel_sha256': sha(own), 'own_matrix_fragment_sha256': sha((HERE / 'Resident16.lean.inc').read_bytes()),
        'matrix_suffix_exact': True, 'retained_B2_prefix_exact': True,
        'caller_sha256': sha(caller.read_bytes()), 'separate_static_resident16_runner_syntax': True,
        'components': components,
        'scope': 'Source identity and callback wiring only. Statement/actual selected C+ASM/cost/replay/full proof UNKNOWN.'}
    (HERE / 'integration-read-receipt.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: v for k, v in report.items() if k != 'components'}))


if __name__ == '__main__':
    main()
