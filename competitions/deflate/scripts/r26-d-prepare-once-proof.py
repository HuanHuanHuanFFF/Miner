"""Prepare D2's separate uncompiled proof pair, preserving both D1 pairs."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/extension90m/route-d'
SOURCE = ROOT / 'candidates/r26-d-658-once-budget'
NAME = 'r26-d-658-once-budget-proof1'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, data):
    path.write_bytes((json.dumps(data, indent=2, ensure_ascii=False) + '\n').encode())


def main():
    target = ROOT / 'candidates' / NAME
    assert not target.exists(), target
    rust = (SOURCE / 'parse.rs').read_bytes()
    lean = (SOURCE / 'Parse.lean').read_bytes()
    assert sha(rust) == '3f866acdc2f16cea804f9abe30094519f9b26e1632cc4585f88c278d5418591f'
    assert sha(lean) == '354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494'
    helper = (OUT / 'D1-helper-proof-UNCOMPILED.lean').read_text().replace('d1_', 'd2_')
    start = helper.index('theorem d2_current_spec')
    end = helper.index('@[local step]', start)
    helper = helper[:start] + helper[start:end].replace('r.2.val', 'r.2.1.val') + helper[end:]
    helper = helper.replace('(l d lazy mode : Std.Usize)', '(l d lazy mode : Std.Usize) (budget : Std.U32)')
    helper = helper.replace('hlit l d lazy mode ⦃', 'hlit l d lazy mode budget ⦃')
    helper = ('-- D2: expected same loop tuples; go2 budget is consumed togo1 on first attempt.\n'
              '-- Triple current result adds an untrusted strategy flag, not a correctness premise.\n' + helper)
    (OUT / 'D2-helper-proof-UNCOMPILED.lean').write_bytes(helper.encode())
    scope = lean.index(b'namespace U118_MAIN')
    insert = lean.index(b'def Near (s : Slice Std.U8)', scope)
    result = lean[:insert] + helper.encode() + b'\n' + lean[insert:]
    assert len(rust) <= 524288 and len(result) <= 524288
    target.mkdir()
    (target / 'parse.rs').write_bytes(rust)
    (target / 'Parse.lean').write_bytes(result)
    hashes = {'parse.rs': sha(rust), 'Parse.lean': sha(result)}
    manifest = json.loads((SOURCE / 'manifest.json').read_bytes())
    manifest.update(candidate=NAME, hashes=hashes,
        proof_parent=SOURCE.relative_to(ROOT).as_posix(),
        proof_status='UNCOMPILED_DRAFT. D1 three helper specifications migrated to d2 names, current triple, and lazy budgetU32. Existing loop proofs left structurally intact because go already belongs to their decreasing measure. D2 exact extraction and fullgate NOT_RUN; D1 Funs signatures were statically compatible.',
        byte_sizes={'parse.rs': len(rust), 'Parse.lean': len(result)},
        helper_fragment_sha256=sha(helper.encode()))
    dump(target / 'manifest.json', manifest)
    entry = json.loads((OUT / 'd2-entry.json').read_bytes())
    entry.update(name=NAME, path=target.relative_to(ROOT).as_posix(), hashes=hashes)
    dump(OUT / 'd2-proof1-entry-UNCOMPILED.json', entry)
    print(json.dumps({'path': target.relative_to(ROOT).as_posix(), 'hashes': hashes,
                      'bytes': manifest['byte_sizes'], 'status': 'UNCOMPILED_DRAFT'}, indent=2))


if __name__ == '__main__':
    main()
