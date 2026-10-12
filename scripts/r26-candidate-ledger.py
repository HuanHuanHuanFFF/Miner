"""Bind the current R26 source inventory to quality, timing roles and exact gates."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT/'evidence/round26'


def sha(path): return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--analysis', required=True, type=Path)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args(); assert not a.output.exists()
    analysis = json.loads(a.analysis.read_bytes())
    by_rust = {x['rust_sha256']: x for x in analysis['candidates']}
    quality = {}; sources = {}; used = {str(a.analysis): sha(a.analysis)}
    for path in sorted(BASE.glob('quality-*-summary.json')):
        value = json.loads(path.read_bytes())
        if value.get('status') != 'VERIFIED_ORIGINAL_ENCODER_BYTES_ONLY': continue
        used[str(path.relative_to(ROOT))] = sha(path)
        for row in value['summary']:
            if not row['candidate'].startswith('r26-'): continue
            pair = value['candidate_hashes'][row['candidate']]; key = (pair['parse.rs'], value['run'])
            item = {'run_id': value['run'], 'files': pair, 'public_size_pct': row['public_size_pct'],
                'output_bytes': row['total_bytes'], 'ci_conclusion': value.get('ci_conclusion', 'success'),
                'encoder_scope': 'Completed original-encoder bytes only; not timing or proof', 'receipts': []}
            prior = quality.setdefault(key, item)
            assert all(prior[k] == item[k] for k in item if k != 'receipts'), key
            prior['receipts'].append(str(path.relative_to(ROOT)))
    for path in sorted((ROOT/'candidates').glob('r26-*/manifest.json')):
        manifest = json.loads(path.read_bytes())
        pair = {name: sha(path.parent/name) for name in ('parse.rs', 'Parse.lean')}
        assert manifest['hashes'] == pair, str(path)
        used[str(path.relative_to(ROOT))] = sha(path)
        rust = pair['parse.rs']
        record = sources.setdefault(rust, {'rust_sha256': rust, 'packages': [], 'native_quality': [],
            'original_protocol_main_observations': [], 'current_main_projection': 'UNKNOWN_UNMEASURED',
            'formal_status': 'NOT_SUBMITTED_BY_R26', 'independent_confirmation': 'NOT_RUN'})
        gate = path.parent/'VERIFICATION.json'
        certificate = None
        if gate.exists():
            cert = json.loads(gate.read_bytes()); assert cert['files'] == pair
            certificate = {'path': str(gate.relative_to(ROOT)), 'sha256': sha(gate), 'status': cert.get('status', 'UNKNOWN')}
        record['packages'].append({'path': str(path.parent.relative_to(ROOT)), 'files': pair,
            'bytes': {name: (path.parent/name).stat().st_size for name in pair},
            'proof_declaration': manifest.get('proof_status', 'UNKNOWN'),
            'exact_gate': certificate or 'NOT_RUN', 'manifest_sha256': sha(path)})
    for rust, record in sources.items():
        record['native_quality'] = [q for (h, _), q in quality.items() if h == rust]
        if rust in by_rust:
            observations = [x for x in by_rust[rust]['observations'] if x['entry_role'] == 'candidate']
            record['original_protocol_main_observations'] = [{k: x[k] for k in ('run_id', 'block', 'role',
                'calibration', 'entry_name', 'single_pool_share_pct', 'time_change_pct_vs_parent', 'proof_sha256')} for x in observations]
            record['current_main_projection'] = 'CONDITIONAL_PUBLIC_PROJECTION_OBSERVED' if observations else 'UNKNOWN_NO_DECLARED_MAIN_MEASUREMENT'
            confirmations = [x for x in observations if x['role'] == 'independent_confirmation']
            if confirmations:
                record['independent_confirmation'] = [
                    {'proof_sha256': proof,
                     'runner_count': len({x['run_id'] for x in confirmations if x['proof_sha256'] == proof}),
                     'main_blocks': len({(x['run_id'], x['block']) for x in confirmations if x['proof_sha256'] == proof})}
                    for proof in sorted({x['proof_sha256'] for x in confirmations})]
    out = {'status': 'VERIFIED_CURRENT_FILE_IDENTITIES_WITH_SEPARATE_EVIDENCE_LAYERS',
        'generated_utc': datetime.now(timezone.utc).isoformat(), 'projection_snapshot': analysis['snapshot'],
        'distinct_rust_count': len(sources), 'package_count': sum(len(r['packages']) for r in sources.values()),
        'sources': list(sources.values()), 'inputs': used,
        'limits': ['Unmeasured candidates have UNKNOWN share, never fabricated zero.',
            'Same Rust aliases and shadow calibrations do not create distinct candidates or independent runners.',
            'Native encoder success inside failed CI certifies that component only.',
            'Manifest proof descriptions are declarations; only exact gate receipts can certify acceptance.',
            'Candidate correctness, private metrics, formal admission and realized payability remain separate.']}
    a.output.write_bytes((json.dumps(out, indent=2)+'\n').encode())
    print(json.dumps({k: out[k] for k in ('distinct_rust_count', 'package_count', 'projection_snapshot')}))


if __name__ == '__main__': main()
