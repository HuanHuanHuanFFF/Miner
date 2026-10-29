"""Inventory reviewed R24 research for D; never stage, push or delete files."""
from pathlib import Path
import datetime
import hashlib
import json
import re
import subprocess

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'AGENTS.md').is_file())
HERE = Path(__file__).resolve().parent
BASE = ROOT / 'competitions/floatlib/candidates'
OUTPUTS = {'public-research-allowlist.txt', 'public-research-manifest.json'}
PRIVATE = re.compile(r'chatgpt\.com/(?:c/|library)|rollout-[^\s\"<>]*\.jsonl|\.codex[/\\]memories', re.I)


def main():
    paths = []
    for directory in [HERE, *sorted(BASE.glob('f01-r24-research-*'))]:
        result = subprocess.run(['rg', '--files', str(directory)], cwd=ROOT,
                                capture_output=True, text=True, check=False)
        assert result.returncode in (0, 1), result.stderr
        paths.extend(Path(line) for line in result.stdout.splitlines())
    # Historical wrong-window directory contains a frozen mathematical input.
    # Include the necessary source only; its mistaken plan/private transcript
    # reference is not part of the public research export.
    historical = BASE / 'f01-d7-research/round3h30m-20261028T230130Z/research/representation'
    paths.extend(p for p in historical.glob('*') if p.suffix in {'.py', '.inc'})
    allowed, excluded = [], []
    for path in sorted(set(p.resolve() for p in paths)):
        relative = path.relative_to(ROOT).as_posix()
        if path.name in OUTPUTS:
            continue
        if '/pro-results/' in relative:
            excluded.append({'path': relative, 'reason': 'Private original/receipt retained locally; technical extraction is public'})
            continue
        data = path.read_bytes()
        try:
            value = data.decode('utf-8')
        except UnicodeDecodeError:
            excluded.append({'path': relative, 'reason': 'Non-text item requires separate review'})
            continue
        if PRIVATE.search(value):
            excluded.append({'path': relative, 'reason': 'Private chat/reference content requires local-only retention or a separate sanitized extraction'})
            continue
        allowed.append({'path': relative, 'bytes': len(data),
                        'sha256': hashlib.sha256(data).hexdigest()})
    record = {'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'owner': 'R; D is sole Git coordinator',
              'state': 'REVIEWED_ALLOWLIST_SNAPSHOT_NOT_A_PUSH_RECEIPT',
              'public_scope': 'Own research code/technical findings, licensed pinned primary source, proof and failed-result records; no private Pro originals/URLs, wallet or third-party whole unknown-license code',
              'files': allowed, 'public_bytes': sum(x['bytes'] for x in allowed),
              'local_only': excluded,
              'limits': 'Live indexes can change until closeout. Rebuild immediately before D commit and verify exact Git blob bytes afterwards. No Lean/performance acceptance is implied.'}
    manifest = HERE / 'public-research-manifest.json'
    manifest.write_text(json.dumps(record, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    stage_paths = [x['path'] for x in allowed]
    stage_paths.extend([(HERE / 'public-research-manifest.json').relative_to(ROOT).as_posix(),
                        (HERE / 'public-research-allowlist.txt').relative_to(ROOT).as_posix()])
    (HERE / 'public-research-allowlist.txt').write_text('\n'.join(stage_paths) + '\n', encoding='utf-8', newline='\n')
    print(json.dumps({'public_files': len(stage_paths), 'public_bytes': record['public_bytes'],
                      'local_only_files': len(excluded), 'manifest': manifest.relative_to(ROOT).as_posix()}))


if __name__ == '__main__':
    main()
