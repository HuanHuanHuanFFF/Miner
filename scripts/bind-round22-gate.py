"""Bind an accepted complete original gate to its exact current source pair."""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('artifact', type=Path)
    args = ap.parse_args()
    artifact = args.artifact.resolve()
    assert artifact.is_relative_to((ROOT / 'evidence/round22').resolve())
    receipt_path = artifact / 'exact-gate/gate-receipt.json'
    receipt = json.loads(receipt_path.read_bytes())
    ci = json.loads((artifact / 'ci-run.json').read_bytes())
    inventory = json.loads((artifact / 'raw-artifact-files.json').read_bytes())
    assert receipt['status'] == 'EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED'
    assert all(receipt['checks'].values()) and receipt['paired_performance_blocks'] == 0
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    assert ci['headSha'] == receipt['git_sha'] and str(ci['databaseId']) == receipt['run_id']
    for file, expected in inventory['files'].items():
        path = (artifact / file).resolve()
        assert path.is_relative_to(artifact)
        assert path.stat().st_size == expected['bytes']
        assert hashlib.sha256(path.read_bytes()).hexdigest() == expected['sha256']
    source = (ROOT / receipt['spec']['path']).resolve()
    assert source.is_relative_to((ROOT / 'candidates').resolve())
    for file, digest in receipt['spec']['files'].items():
        assert hashlib.sha256((source / file).read_bytes()).hexdigest() == digest
    log = (artifact / 'exact-gate/gate.log').read_text()
    accepted = re.search(r'verification accepted in ([\d.]+)s \(bwrap, (\d+)s,', log)
    assert accepted and accepted[2] == '900'
    ax = re.search(r"depends on axioms: \[([^\]]+)\]", log)
    assert ax
    axioms = sorted(x.strip() for x in ax[1].split(','))
    assert axioms == ['Classical.choice', 'Quot.sound', 'propext']
    certificate = {
        'status': 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED', 'run_id': receipt['run_id'],
        'git_sha': receipt['git_sha'], 'ci_conclusion': ci['conclusion'], 'files': receipt['spec']['files'],
        'receipt': receipt_path.relative_to(ROOT).as_posix(), 'gate_seconds': float(accepted[1]),
        'original_lean_timeout_seconds': 900, 'axioms': axioms,
        'gate_scope': 'Original fresh extraction, original LZ77.Obligation, axiom whitelist andpublic stage1 roundtrip; exact pair only.',
        'public_output_bytes': receipt['spec']['expected_public_output_bytes'],
        'performance_status': 'See separate original-protocol discovery andfresh confirmation receipts. Gate smoke time is not a performance score.',
        'formal_submission_sent': False, 'formal_admission': 'UNKNOWN', 'formal_reward_pool_share_pct': None,
    }
    path = source / 'VERIFICATION.json'
    assert not path.exists()
    path.write_bytes((json.dumps(certificate, indent=2) + '\n').encode())
    manifest_path = source / 'manifest.json'
    manifest = json.loads(manifest_path.read_bytes())
    assert manifest['hashes'] == certificate['files']
    manifest['proof_status'] = certificate['status']
    manifest['verification_certificate'] = path.relative_to(ROOT).as_posix()
    manifest_path.write_bytes((json.dumps(manifest, indent=2) + '\n').encode())
    print(json.dumps(certificate, indent=2))


if __name__ == '__main__':
    main()
