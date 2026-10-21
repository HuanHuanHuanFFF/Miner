"""Retain exact gate-passed R25 source packages for review and future reuse."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import zipfile

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round25'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    plan = json.loads((E / 'confirm-components-plan.json').read_bytes())
    out = E / 'review-packages'
    out.mkdir(exist_ok=False)
    stamp = datetime.fromisoformat(plan['frozen_plan_utc']).astimezone(timezone.utc)
    packages = []
    for entry in plan['pairs']:
        source = ROOT / 'candidates' / entry['candidate']
        cert = json.loads((source / 'VERIFICATION.json').read_bytes())
        assert cert['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
        assert cert['files'] == entry['files'] and cert['run_id'] == entry['gate_run']
        receipt = json.loads((ROOT / cert['receipt']).read_bytes())
        assert receipt['status'] == 'EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED'
        assert all(receipt['checks'].values()) and receipt['spec']['files'] == entry['files']
        files = {name: (source / name).read_bytes() for name in ('parse.rs', 'Parse.lean')}
        assert all(sha(data) == entry['files'][name] for name, data in files.items())
        archive = out / (entry['candidate'] + '-' + entry['files']['parse.rs'][:12] + '.zip')
        with zipfile.ZipFile(archive, 'w') as z:
            for name, data in files.items():
                info = zipfile.ZipInfo(name, stamp.timetuple()[:6])
                info.create_system = 3
                info.external_attr = 0o100644 << 16
                z.writestr(info, data, compress_type=zipfile.ZIP_DEFLATED, compresslevel=9)
        with zipfile.ZipFile(archive) as z:
            assert z.namelist() == ['parse.rs', 'Parse.lean'] and z.testzip() is None
            assert all(z.read(name) == data for name, data in files.items())
        packages.append({'candidate': entry['candidate'], 'source_path': source.relative_to(ROOT).as_posix(),
                         'files': entry['files'], 'gate_run_id': cert['run_id'],
                         'gate_receipt': cert['receipt'], 'frozen_plan_utc': plan['frozen_plan_utc'],
                         'archive': archive.relative_to(ROOT).as_posix(),
                         'archive_sha256': sha(archive.read_bytes()), 'archive_bytes': archive.stat().st_size,
                         'contents': ['parse.rs', 'Parse.lean'],
                         'role': 'Correct quality component retained; stable payable performance not established'})
    result = {'status': 'VERIFIED_EXACT_SOURCE_ONLY_REVIEW_PACKAGES',
              'prepared_utc': datetime.now(timezone.utc).isoformat(), 'packages': packages,
              'formal_submission_sent': False, 'formal_admission': 'UNKNOWN',
              'performance': 'Separate independent confirmation receipts; neither source established stable positive share.',
              'scope': 'Two frozen source files per archive. No wallet data, registration, signature or upload.'}
    (out / 'packages.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
