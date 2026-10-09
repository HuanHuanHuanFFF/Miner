"""Freeze a separate, still-uncompiled proof draft for the exact measured Rust."""
from pathlib import Path
import hashlib, json

ROOT = Path(__file__).resolve().parents[1]

def main():
    parent = ROOT / 'candidates/r15-550-base-ring1024'
    name = 'r15-550-base-ring1024-proof'
    dest = ROOT / 'candidates' / name
    dest.mkdir(exist_ok=True)
    proof = (parent / 'Parse.lean').read_text()
    needle = '@[local step]\ntheorem u592 (lf zf b)'
    assert proof.count(needle) == 1
    helpers = (ROOT / 'evidence/round15/ring-helper-draft.lean').read_text()
    data = {'parse.rs': (parent / 'parse.rs').read_bytes(), 'Parse.lean': proof.replace(needle, helpers + '\n' + needle).encode()}
    for f, raw in data.items():
        assert not (dest / f).exists() or (dest / f).read_bytes() == raw
        (dest / f).write_bytes(raw)
    m = json.loads((parent / 'manifest.json').read_bytes())
    m.update(candidate=name, source_parent=parent.name, hashes={f: hashlib.sha256(v).hexdigest() for f,v in data.items()}, proof_status='DRAFT_UNCOMPILED; helper signatures checked against actual official extraction37915493157; no accepted certificate', performance_status='Exact Rust measured inring-s; proof-only sibling does not create an independent performance result', proof_derivation='scripts/make-round15-ring-proof.py + evidence/round15/ring-helper-draft.lean', formal_submission_sent=False)
    (dest / 'manifest.json').write_bytes((json.dumps(m, indent=2) + '\n').encode())
    print(json.dumps({'candidate': name, 'hashes': m['hashes'], 'proof': 'UNCOMPILED'}))

if __name__ == '__main__': main()
