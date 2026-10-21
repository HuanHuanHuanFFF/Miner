"""Print the verifier's retained full logs without changing its source or verdict."""
from __future__ import annotations
import hashlib
import json
import os
from pathlib import Path
import re
import sys


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true'
    name = sys.argv[1]
    assert name in ('bucket2', 'probe3', 'probe2-nice16', 'probe2-nice64')
    reports = Path(os.environ['RUNNER_TEMP']) / 'deflate-reports'
    text = (reports / (name + '-gate.log')).read_text(encoding='utf-8')
    match = re.search(r'^workspace: (.+)$', text, re.M)
    if not match:
        print('DIAGNOSTIC_NO_WORKSPACE ' + name)
        return
    work = Path(match[1].strip()).resolve()
    expected = (Path(os.environ['DEFLATE_ROOT']) / 'data/verification-workspace').resolve()
    assert work.parent == expected and work.is_dir()
    manifest = {}
    for path in sorted((work / 'logs').glob('*.log')):
        data = path.read_bytes()
        manifest[path.name] = {'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
        # Earlier successful compiler logs do not diagnose the rejected proof.
        if b'error:' not in data and b'error: ' not in data and b'timed out' not in data:
            continue
        print(f'GATE_DIAGNOSTIC_BEGIN {name} {path.name}', flush=True)
        print(data.decode('utf-8', errors='replace'), flush=True)
        print(f'GATE_DIAGNOSTIC_END {name} {path.name}', flush=True)
    output = {'candidate': name, 'workspace': str(work), 'logs': manifest,
              'scope': 'diagnostic logs only; official verdict unchanged'}
    (reports / (name + '-diagnostics.json')).write_text(json.dumps(output, indent=2) + '\n')
    print('GATE_DIAGNOSTIC_MANIFEST ' + json.dumps(output), flush=True)


if __name__ == '__main__':
    main()
