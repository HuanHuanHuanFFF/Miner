"""Only generate source: exactraw8 arithmetic + machine indices, no build/CI."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r22-dev-resident8-cost1/Kernel.lean'
OLD = HERE.parent / 'development-resident8/Resident8.lean.inc'
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    original = BASE.read_bytes()
    assert sha(original) == '24c60123b76214c4da31d2765fca0010985c0289dad77e8bc18b2de507625e34'
    old = OLD.read_bytes()
    assert sha(old) == 'e41232252cde52abe05b4539ac281067da51c9ba2708c2286f9a2faaf54f65b3'
    frag = (HERE / 'IndexedResident8.lean.inc').read_bytes()
    start = original.index(b'abbrev State (p : Nat) := Vector Cell (groups p)', original.index(b'namespace Submission.R22Pair8'))
    end = original.index(b'end Submission.R22Pair8', start)
    removed = original[start:end]
    # Only the old per-k ArrayState Pair8 variant is removed. Its pack producer,
    # Cell, exact raw8 namespace and the retained B2 prefix stay byte-identical.
    trimmed = original[:start] + original[end:]
    result = trimmed + b'\n' + frag
    assert len(result) <= 256000 and result.count(b'import ') == 1
    (HERE / 'KernelIndexed8Cost.lean').write_bytes(result)
    data = {'source': 'KernelIndexed8Cost.lean', 'sha256': sha(result), 'bytes': len(result),
        'base_sha256': sha(original), 'base_bytes': len(original),
        'dead_Pair8_State_variant_removed_sha256': sha(removed),
        'dead_Pair8_State_variant_removed_bytes': len(removed),
        'retained_B2_prefix_byte_identical': result[:226829] == original[:226829],
        'old_resident8_fragment_byte_identical': old in result,
        'old_fragment_sha256': sha(old), 'fragment_sha256': sha(frag), 'fragment_bytes': len(frag),
        'builder_sha256': sha(Path(__file__).read_bytes()),
        'caller': 'R22Indexed8CostMain.lean',
        'caller_sha256': sha((HERE / 'R22Indexed8CostMain.lean').read_bytes()),
        'status': 'SOURCE_ONLY_NOT_COMPILED', 'public_roots': 'Exact B2 remains public; new runtime not proved.',
        'changed': 'One whole-call n/A/cache word-fit guard; machine k, A base additions and B stride cursor; uget proofs erase.',
        'unchanged': 'Raw A, row-major Pair8 B cache/prep,8 MAC chains, R2 codec, +0, finish/raw replay, Words/read/tail/fallback algorithm.',
        'actual_hot_register_residency': 'UNKNOWN', 'cost': 'NOT_RUN', 'new_BMM_equivalence': 'UNKNOWN',
        'standalone_statement': 'NOT_RUN', 'full_gate': 'NOT_RUN'}
    (HERE / 'indexed8-source-manifest.json').write_text(json.dumps(data,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(data))


if __name__ == '__main__': main()
