#!/usr/bin/env python3
"""Create a separate R5-W02 candidate from the exact public parent."""
from pathlib import Path
import argparse
import hashlib
import json

EXPECTED_PARENT = 'ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630'

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('parent', type=Path)
    p.add_argument('output', type=Path)
    args = p.parse_args()
    here = Path(__file__).resolve().parent
    raw = args.parent.read_bytes()
    actual = hashlib.sha256(raw).hexdigest()
    if actual != EXPECTED_PARENT:
        p.error(f'parent SHA256 mismatch: {actual}')
    if args.parent.resolve() == args.output.resolve():
        p.error('output must differ from parent')
    if args.output.exists():
        p.error('output already exists; choose a new path')
    source = raw.decode('utf-8')
    core = (here.parent / 'candidate/FiniteBits.lean').read_text(encoding='utf-8')
    old = (here / 'ParentFinish.lean.txt').read_text(encoding='utf-8')
    new = (here / 'Packed10Replacement.lean.inc').read_text(encoding='utf-8')
    if not source.startswith('import ContractTensor\n'):
        p.error('unexpected parent import')
    if not core.startswith('import ContractTensor\n') or source.count(old) != 1:
        p.error('unexpected fragment structure')
    result = source.replace('import ContractTensor\n', core, 1)
    result = result.replace(old, new, 1)
    data = result.encode('utf-8')
    if len(data) > 256000:
        p.error('candidate exceeds byte limit')
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open('xb') as f:
        f.write(data)
    print(json.dumps({'parent_sha256': actual, 'output': str(args.output),
                      'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}, indent=2))

if __name__ == '__main__':
    main()
