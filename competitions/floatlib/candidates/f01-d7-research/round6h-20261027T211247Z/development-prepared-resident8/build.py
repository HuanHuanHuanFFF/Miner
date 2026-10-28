"""Reproduce source-only diagnostic. No Lean/build/CI/Git commands."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r22-dev-resident8-cost1/Kernel.lean'
BASE_SHA = '24c60123b76214c4da31d2765fca0010985c0289dad77e8bc18b2de507625e34'
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    original = BASE.read_bytes()
    assert sha(original) == BASE_SHA and len(original) == 241789
    fragment = (HERE / 'PreparedResident8.lean.inc').read_bytes()
    assert fragment.count(b'namespace Submission.R22PreparedResident8') == 1
    source = original + b'\n' + fragment
    assert len(source) <= 256000
    assert source.startswith(b'import ContractTensor')
    assert source.count(b'import ') == original.count(b'import ') == 1
    target = HERE / 'KernelCost.lean'
    target.write_bytes(source)
    info = {
        'route_status': 'PARK_NOT_FOR_NEW_COST',
        'reason': 'R16 already borrowed both inner vectors and bounded four-row tiles; global A extends lifetime without removing hot record reads.',
        'source': target.name, 'sha256': sha(source), 'bytes': len(source),
        'base': str(BASE.relative_to(ROOT)).replace('\\', '/'),
        'base_sha256': sha(original), 'base_bytes': len(original),
        'fragment': 'PreparedResident8.lean.inc', 'fragment_sha256': sha(fragment),
        'fragment_bytes': len(fragment), 'base_exact_prefix': True,
        'public_four_roots': 'Original B2. New prepared runtime only via diagnostic caller.',
        'new_prepared_runtime_all_input_equivalence': 'UNKNOWN_NOT_PROVED',
        'Lean_statement': 'NOT_RUN', 'kernel_replay': 'NOT_RUN', 'axiom_audit': 'NOT_RUN',
        'machine_code': 'NOT_RUN', 'full_call_timing': 'NOT_RUN', 'full_gate': 'NOT_RUN',
    }
    (HERE / 'source-manifest.json').write_text(json.dumps(info, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(info))


if __name__ == '__main__':
    main()
