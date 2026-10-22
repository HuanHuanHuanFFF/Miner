#!/usr/bin/env python3
"""Compose this public-parent output rewrite without running Lean or any gate."""
from pathlib import Path
import argparse
import hashlib
import json
import re

EXPECTED_PARENT_SHA256 = 'ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630'
EXPECTED_PARENT_BYTES = 132965

parser = argparse.ArgumentParser()
parser.add_argument('--parent', required=True, type=Path)
parser.add_argument('--output', required=True, type=Path)
parser.add_argument('--mode', choices=('append', 'activate'), required=True)
args = parser.parse_args()
raw = args.parent.read_bytes()
if len(raw) != EXPECTED_PARENT_BYTES or hashlib.sha256(raw).hexdigest() != EXPECTED_PARENT_SHA256:
    raise SystemExit('Parent bytes or SHA256 do not match the fixed public parent.')
base = raw.decode('utf-8')
snippet = (Path(__file__).resolve().parent / 'OutputRows.inc.lean').read_text(encoding='utf-8')
if re.search(r'^\s*import\b', snippet, re.M):
    raise SystemExit('The append fragment must not contain an import.')

if args.mode == 'append':
    composed = base + '\n' + snippet
    entry = 'Original Submission.bmm remains selected; this mode only adds proof and alternate entry.'
else:
    anchor = 'end Packed10\n\ndef bmm (batch m n p : Nat)'
    old_call = 'else Packed10.core batch m n p A B'
    new_call = 'else Packed10OutputRows.coreRows batch m n p A B'
    old_proof = '· exact Packed10.core_eq_reference batch m n p A B'
    new_proof = '· exact Packed10OutputRows.coreRows_eq_reference batch m n p A B'
    for marker in (anchor, old_call, old_proof):
        if base.count(marker) != 1:
            raise SystemExit('Expected unique public-parent integration marker not found.')
    composed = base.replace(old_call, new_call).replace(old_proof, new_proof)
    insertion = ('end Packed10\n\nend Submission\n\n' + snippet +
                 '\nnamespace Submission\n\nopen FloatLib.Floats Competition\n\n'
                 'def bmm (batch m n p : Nat)')
    composed = composed.replace(anchor, insertion)
    entry = 'Submission.bmm now uses Packed10OutputRows.coreRows in its original nonempty branch.'
    # Reverse the two substitutions and the exact insertion to check all other parent bytes.
    restored = composed.replace(insertion, anchor).replace(new_call, old_call).replace(new_proof, old_proof)
    if restored.encode('utf-8') != raw:
        raise SystemExit('Unexpected change outside the exact output integration.')

data = composed.encode('utf-8')
imports = re.findall(r'^\s*import\s+(.+)$', composed, re.M)
if imports != ['ContractTensor'] or len(data) > 256000:
    raise SystemExit('Import or source-size constraint failed.')
with args.output.open('xb') as out:
    out.write(data)
print(json.dumps({'mode':args.mode,'path':str(args.output.resolve()),'bytes':len(data),
                  'sha256':hashlib.sha256(data).hexdigest(),'imports':imports,
                  'entry':entry,'lean':'NOT_RUN','gate':'NOT_RUN'},indent=2))
