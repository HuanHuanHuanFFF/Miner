"""Build a distinct uncompiled proof pair without touching the frozen D1 pair."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/extension90m/route-d'
PARENT = ROOT / 'candidates/r26-d-658-selective-depth'
NAME = 'r26-d-658-selective-depth-proof1'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, data):
    path.write_bytes((json.dumps(data, ensure_ascii=False, indent=2) + '\n').encode())


def main():
    target = ROOT / 'candidates' / NAME
    assert not target.exists(), target
    rust = (PARENT / 'parse.rs').read_bytes()
    lean = (PARENT / 'Parse.lean').read_bytes()
    assert sha(rust) == 'f6c7f97f9fb275d5a27ff4a52d02f065bb9c4cfd39e73e311c5a7f5a3ea8e0a8'
    assert sha(lean) == '354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494'
    helper = (OUT / 'D1-helper-proof-UNCOMPILED.lean').read_bytes()
    start = lean.index(b'namespace U118_MAIN')
    insert = lean.index(b'def Near (s : Slice Std.U8)', start)
    result = lean[:insert] + helper + b'\n' + lean[insert:]
    assert len(rust) <= 524288 and len(result) <= 524288
    target.mkdir()
    (target / 'parse.rs').write_bytes(rust)
    (target / 'Parse.lean').write_bytes(result)
    hashes = {'parse.rs': sha(rust), 'Parse.lean': sha(result)}
    manifest = json.loads((PARENT / 'manifest.json').read_bytes())
    manifest.update(candidate=NAME, proof_parent=PARENT.relative_to(ROOT).as_posix(),
                    hashes=hashes,
                    proof_status='UNCOMPILED_DRAFT. Three helper specs plus a bounded-find local bridge added in U118_MAIN. Exact extracted signatures and the original full gate remain unverified. No new axiom or sorry introduced.',
                    byte_sizes={'parse.rs': len(rust), 'Parse.lean': len(result)},
                    helper_fragment_sha256=sha(helper))
    dump(target / 'manifest.json', manifest)
    entry = json.loads((OUT / 'd1-entry.json').read_bytes())
    entry.update(name=NAME, path=target.relative_to(ROOT).as_posix(), hashes=hashes)
    dump(OUT / 'd1-proof1-entry-UNCOMPILED.json', entry)
    print(json.dumps({'path': target.relative_to(ROOT).as_posix(), 'hashes': hashes,
                      'bytes': {'parse.rs': len(rust), 'Parse.lean': len(result)},
                      'status': 'UNCOMPILED_DRAFT'}, indent=2))


if __name__ == '__main__':
    main()
