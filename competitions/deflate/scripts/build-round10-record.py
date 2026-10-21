"""Remove zero-candidate records while retaining the prefix-covering node zero."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'candidates/r9-block-scalar'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    original = {f: (BASE / f).read_bytes() for f in ['parse.rs', 'Parse.lean']}
    parent = json.loads((BASE / 'manifest.json').read_text())
    assert all(hashlib.sha256(b).hexdigest() == parent['hashes'][f] for f, b in original.items())
    source = original['parse.rs'].decode()
    old = '''    let cnt = rs.len().wrapping_sub(l0) as u32;
    d_push32(rs, i as u32);
    d_push32(rs, cnt);
'''
    new = '''    let cnt = rs.len().wrapping_sub(l0) as u32;
    // Empty records carry no match edge. Keep node zero so the backward sweep
    // still visits the whole prefix even when no match exists anywhere.
    if cnt > 0 || i == 0 {
        d_push32(rs, i as u32);
        d_push32(rs, cnt);
    }
'''
    assert source.count(old) == 1
    rust = source.replace(old, new)
    assert rust.replace(new, old) == source
    proof = original['Parse.lean'].decode()
    start = proof.index('@[local step]\ntheorem d_record_spec')
    end = proof.index('@[local step]', start + 1)
    old_proof = proof[start:end]
    statement = old_proof[:old_proof.index(' := by')]
    new_proof = statement + ''' := by
  rw [slot.d_record]
  step*
  repeat' (split <;> step*)

'''
    lean = proof[:start] + new_proof + proof[end:]
    assert lean.replace(new_proof, old_proof) == proof
    files = {'parse.rs': rust.encode(), 'Parse.lean': lean.encode()}
    manifest = {'candidate': 'r10-record-nonempty', 'parent': 'candidates/r9-block-scalar',
        'parent_hashes': parent['hashes'], 'attribution': parent['attribution'],
        'hashes': {f: hashlib.sha256(b).hexdigest() for f, b in files.items()},
        'bytes': {f: len(b) for f, b in files.items()},
        'mechanism': 'Omit [position,0] records except position zero. Retain all match records and all original search/seed-planning work, letting backward gaps handle omitted literal-only positions.',
        'equivalence_hypothesis': 'An empty searched node cannot lie inside a lower recorded match with at least three bytes remaining, because the forward continuation would be offered. Gaps preserve literal/pushed-value choices and block transitions. This needs whole-parser finite discrimination.',
        'important_boundary': 'Node zero must remain: d_dp has no separate final prefix sweep after consuming rs.',
        'source_audit': 'One d_record write guard and its totality proof only. Reverse edits restore exact parent bytes.',
        'proof_status': 'UNCOMPILED_ADAPTED_D_RECORD_SPEC; original obligation/axiom/public roundtrip gate required.',
        'performance_status': 'NOT_RUN; same-byte finite check and paired total-compression timing required.',
        'stop': 'An output mismatch refutes the claimed equivalence; retain negative evidence and diagnose before any combination.'}
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    target = ROOT / 'candidates/r10-record-nonempty'
    target.mkdir(exist_ok=True)
    for f, b in files.items():
        assert len(b) <= 524288
        if args.check:
            assert (target / f).read_bytes() == b
        else:
            assert not (target / f).exists() or (target / f).read_bytes() == b
            (target / f).write_bytes(b)
    print(json.dumps(manifest))


if __name__ == '__main__':
    main()
