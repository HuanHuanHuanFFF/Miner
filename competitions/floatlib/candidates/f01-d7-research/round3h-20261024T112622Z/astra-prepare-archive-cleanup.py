"""Read-only verification; write a deletion plan inside this research directory."""
from datetime import datetime, timezone
from pathlib import Path, PurePosixPath
import hashlib
import json
import stat
import zipfile

HERE = Path(__file__).resolve().parent
ROOT = Path('E:/Download/FloatLib/20261024-R11').resolve()
INVENTORY = HERE.parent / 'round7h-20261023T193125Z/astra-web-deliveries.json'
OUTPUT = HERE / 'astra-archive-cleanup-20261024.json'
sha = lambda b: hashlib.sha256(b).hexdigest()


def ordinary_path(p):
    p.relative_to(ROOT)
    for item in (p, *p.parents):
        if item.exists():
            assert not (item.lstat().st_file_attributes & stat.FILE_ATTRIBUTE_REPARSE_POINT), item


inventory = json.loads(INVENTORY.read_bytes())
payloads = []
for record in inventory['records']:
    for row in record['files']:
        p = Path(row['path'])
        ordinary_path(p)
        data = p.read_bytes()
        assert len(data) == row['bytes'] and sha(data) == row['sha256'], p
        payloads.append(row)

specs = [
    ('W01/R11-W01-evidence.zip', 'W01/original-extracted',
     'c02cb925299415fc1caa85ff5779350c6f2987155f6ebc527076ec6b882c6118'),
    ('W02/R11-W02-recovered-artifacts.zip', 'W02',
     '3f0076c139170349a5b83f364279ff9e180aa520594b5e08d1e94e29908cb735'),
    ('W03/R11-W03.zip', 'W03/original-extracted',
     '58cb49f49c6325a795348f7fd0736de3d6974cb69c6e6d1a3f34f8d8082b7da9'),
]
archives = []
for archive_rel, destination_rel, expected in specs:
    archive = ROOT / archive_rel
    ordinary_path(archive)
    data = archive.read_bytes()
    assert sha(data) == expected, archive
    members = []
    seen = set()
    with zipfile.ZipFile(archive) as z:
        assert z.testzip() is None, archive
        for info in z.infolist():
            name = info.filename.replace('\\', '/')
            parts = PurePosixPath(name)
            assert not parts.is_absolute() and '..' not in parts.parts and ':' not in name, name
            assert not stat.S_ISLNK(info.external_attr >> 16), name
            if info.is_dir():
                continue
            assert name.casefold() not in seen, name
            seen.add(name.casefold())
            target = ROOT / destination_rel / name
            ordinary_path(target)
            content = z.read(info)
            assert target.is_file() and target.read_bytes() == content, target
            members.append({'member': name, 'extracted_path': str(target),
                            'bytes': len(content), 'sha256': sha(content)})
    archives.append({'path': str(archive), 'bytes': len(data), 'sha256': expected,
                     'crc': 'PASS', 'all_members_byte_equal': True, 'members': members})

readme = ROOT / 'README.md'
original = readme.read_bytes()
(HERE / 'astra-e-drive-readme-before-cleanup.md').write_bytes(original)
receipt = {
    'state': 'VERIFIED_READY_FOR_EXPLICITLY_AUTHORIZED_ARCHIVE_DELETION',
    'verified_at_utc': datetime.now(timezone.utc).isoformat(),
    'authority': 'Human requested prompt extraction then archive deletion on E drive; preserve research records.',
    'root': str(ROOT), 'inventory': str(INVENTORY.relative_to(Path.cwd())),
    'inventory_sha256': sha(INVENTORY.read_bytes()),
    'indexed_payloads_verified': len(payloads), 'payloads': payloads,
    'archives': archives, 'logical_archive_bytes': sum(a['bytes'] for a in archives),
    'readme_before_sha256': sha(original),
    'historical_receipts_modified': False, 'research_window_extended': False,
}
OUTPUT.write_bytes((json.dumps(receipt, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({'receipt': str(OUTPUT), 'archives': len(archives),
                  'zip_members_verified': [len(a['members']) for a in archives],
                  'indexed_payloads_verified': len(payloads),
                  'logical_archive_bytes': receipt['logical_archive_bytes']}))
