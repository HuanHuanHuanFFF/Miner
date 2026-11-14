"""Freeze explicit owned technical publication paths; never stage or push."""
from pathlib import Path
import datetime
import hashlib
import json
import re
import subprocess

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = next(p for p in ROUND.parents if (p / 'AGENTS.md').is_file())
OUTPUTS = {HERE / 'PUBLICATION-INVENTORY.json', HERE / 'public-allowlist.txt'}
ROLES = [ROUND / 'research', ROUND / 'development/native', ROUND / 'verification']


def sha(data):
    return hashlib.sha256(data).hexdigest()


def manifest_paths(path, key, relative_to_root=False):
    manifest = json.loads(path.read_bytes())
    result = []
    for entry in manifest[key]:
        file = ROOT / entry['path'] if relative_to_root else path.parent / entry['path']
        assert file.resolve().is_relative_to(path.parent.resolve()), file
        data = file.read_bytes()
        assert len(data) == entry['bytes'] and sha(data) == entry['sha256'], file
        result.append(file)
    return result


def main():
    paths = set(manifest_paths(ROUND / 'research/public-research-manifest.json', 'files', True))
    paths |= {ROUND / 'research/public-research-manifest.json', ROUND / 'research/public-research-allowlist.txt'}
    paths |= set(manifest_paths(ROUND / 'development/native/PUBLIC-MANIFEST.json', 'files'))
    paths |= {ROUND / 'development/native' / name for name in ['PUBLIC-MANIFEST.json', 'PACKAGE-CHECK.json', 'ROLE-DELIVERY-INDEX.json']}
    paths |= set(manifest_paths(ROUND / 'verification/PUBLIC-MANIFEST.json', 'public_files'))
    paths |= {ROUND / 'verification/PUBLIC-MANIFEST.json', ROUND / 'verification/status.json'}
    for mode in ['--modified', '--others']:
        args = ['git', 'ls-files', mode]
        if mode == '--others':
            args += ['--exclude-standard']
        args += ['--', ROUND.relative_to(ROOT).as_posix()]
        for line in subprocess.check_output(args, cwd=ROOT, text=True).splitlines():
            file = ROOT / line
            if any(p in {'source-private', 'local-private', 'private', 'pro-results', '__pycache__'} for p in file.parts):
                continue
            if not any(file.is_relative_to(role) for role in ROLES) and file not in OUTPUTS:
                paths.add(file)
    paths |= {ROOT / 'dashboard.md', ROOT / 'competitions/torchlean/coordination/HANDOFF.md'}
    private = re.compile(r'chatgpt\.com/(?:c/|library)|rollout-[^\s"<>]*\.jsonl|BEGIN (?:RSA |OPENSSH )?PRIVATE KEY|gh[pousr]_[A-Za-z0-9]{20}', re.I)
    entries = []
    for file in sorted(paths):
        assert file.resolve().is_relative_to(ROOT.resolve())
        rel = file.relative_to(ROOT)
        assert not any(p in {'source-private', 'local-private', 'private', 'pro-results', '__pycache__', '.registration-private'} for p in rel.parts), rel
        assert file.suffix.lower() not in {'.zip', '.exe', '.dll', '.o', '.so', '.a', '.olean'}, rel
        data = file.read_bytes()
        assert not private.search(data.decode('utf-8-sig')), rel
        entries.append({'path': rel.as_posix(), 'bytes': len(data), 'sha256': sha(data)})
    receipt = {
        'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'state': 'FROZEN_OWN_TECHNICAL_PUBLICATION_ALLOWLIST',
        'branch': 'huan/codex-gpt', 'files': entries,
        'bytes': sum(e['bytes'] for e in entries),
        'scope': 'Owned R28 recipes, mathematics, proof drafts, fixed technical evidence, current dashboard/handoff. No formal competition submission.',
        'exclusions': 'Full private upstream/reconstructed kernels/C/ASM, private chats/anchors, credentials/wallet, large binaries and all unrelated work.',
        'metadata_self_hash': 'This manifest and public-allowlist.txt excluded from recursive hashes; Git index checks cover their exact bytes too.',
    }
    (HERE / 'PUBLICATION-INVENTORY.json').write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    allowlist = [e['path'] for e in entries] + [p.relative_to(ROOT).as_posix() for p in sorted(OUTPUTS)]
    (HERE / 'public-allowlist.txt').write_text('\n'.join(allowlist) + '\n', encoding='utf-8', newline='\n')
    print(json.dumps({'public_paths': len(allowlist), 'bytes': receipt['bytes'], 'manifest_checks': 'PASS'}))


if __name__ == '__main__':
    main()
