"""Freeze research-owned proof repair and source-grounded handoff; no compiler."""
from pathlib import Path
from hashlib import sha256, sha1
import json
from datetime import datetime, timezone

base = Path(__file__).resolve().parent
old = base / 'astra-biased-rne1.lean'
raw = old.read_bytes()
needle = b'    rw [parity, UInt64.toNat_and, hshift]'
assert raw.count(needle) == 1
nl = b'\r\n' if b'\r\n' in raw else b'\n'
repaired = raw.replace(needle,
    b'    dsimp only [parity]' + nl + b'    rw [UInt64.toNat_and, hshift]')
target = base / 'astra-biased-rne2.lean'
if target.exists():
    assert target.read_bytes() == repaired
else:
    target.write_bytes(repaired)

def info(path):
    b = path.read_bytes()
    return dict(path=path.relative_to(base).as_posix(), bytes=len(b),
                sha256=sha256(b).hexdigest(),
                git_blob_sha1=sha1(b'blob ' + str(len(b)).encode() + b'\0' + b).hexdigest())

meta = base / 'astra-upstream-lean/src/Lean/Meta/Tactic/Rewrite.lean'
elab = base / 'astra-upstream-lean/src/Lean/Elab/Tactic/Rewrite.lean'
assert info(meta)['git_blob_sha1'] == 'f616c869ab7dd86e771fc22918303ab8b7aa2998'
files = [target, base / 'astra-small-shift-bias1.lean',
         base / 'astra-word-add-alignment1.lean']
receipt = dict(
    timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='SOURCE_GROUNDED_DRAFT_NOT_COMPILED',
    requested_by='20261024T230553016Z-r14-development-word-add-domain-and-headroom.md',
    files=[info(p) for p in files], original_bias1=info(old),
    original_preserved=True,
    bias2_delta='Unfold local let parity with dsimp, then rewrite UInt64.toNat_and/hshift. Runtime definition and theorem statements unchanged.',
    static_error_evidence=dict(
        lean_ref='293d5d0c0c3f3dded4688b3ccd6a33939ac5102b',
        sources=[info(elab), info(meta)],
        local_ident_behavior='Elab withRWRulesSeq sends a local identifier directly to elabRewrite; no global definition equation theorem is generated.',
        equality_requirement='Meta MVarId.rewrite infers its type and matches Eq/Iff; local parity has type UInt64, so rw [parity] is not an equality rewrite.',
        status='CONFIRMED_BY_PINNED_SOURCE_NOT_A_COMPILER_RECEIPT'),
    dependencies=dict(
        floatlib_ref='0d91825727839f597fd06b22fdd038ea21480f0c',
        alignment='astra-add-upstream-index.json',
        small_shift='FixedWord.roundShiftRightEven_toNat and existing Nat roundQuotientEven API'),
    scope='Only astra fragments; no full candidate, runtime change, extra CI dispatch, Git index or publication.',
    next='D integrates fresh fragments into a new exact candidate. Compiler/public gate/performance all NOT_RUN.')
(base / 'astra-word-add-fragments-intake.json').write_text(
    json.dumps(receipt, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps(receipt, ensure_ascii=False, indent=2))
