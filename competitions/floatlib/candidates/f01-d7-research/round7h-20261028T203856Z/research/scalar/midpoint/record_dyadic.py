"""Record the two new source fragments and exact public MIT dependencies."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[8]

def sha(b):
    return hashlib.sha256(b).hexdigest()

def main():
    fixed = '0d91825727839f597fd06b22fdd038ea21480f0c'
    inputs = [
        ('ShiftRight.lean.raw', 'd53bd9ec15f51006a945e3c49d7c3e1d3185af19', 'FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean'),
        ('Dyadic-Real.lean.raw', 'bd209088275cd14b5fbafd6578fc0da1618670bf', 'FloatLib/Numerics/Exact/Dyadic/Real.lean'),
        ('Integer-Rounding.lean.raw', '0f79753745f67a8e29e539570b2c66139cc29313', 'FloatLib/Floats/Formats/IEEE754/Native/Integer/Rounding.lean')
    ]
    public = []
    for name, blob, remote in inputs:
        path = HERE / 'sources' / name
        data = path.read_bytes()
        def git_blob(b):
            return hashlib.sha1(b'blob ' + str(len(b)).encode() + b'\0' + b).hexdigest()
        if git_blob(data) != blob:
            assert data.endswith(b'\n') and git_blob(data[:-1]) == blob
            data = data[:-1]
            path.write_bytes(data)
        assert git_blob(data) == blob
        assert b'Released under MIT license' in data and b'Authors: FloatLib Team' in data
        public.append({'path': str(path.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(data),
                       'sha256': sha(data), 'git_blob_sha1': blob, 'git_blob_verified': True,
                       'url': f'https://github.com/lean-dojo/FloatLib/blob/{fixed}/{remote}',
                       'license': 'MIT; Authors: FloatLib Team'})
    model = json.loads((HERE / 'dyadic-model-receipt.json').read_text(encoding='utf-8'))
    for item in model['sources']:
        data = (ROOT / item['path']).read_bytes()
        assert sha(data) == item['sha256'] and len(data) == item['bytes']
        assert not re.search(rb'\b(sorry|admit|axiom|unsafe|extern|native_decide)\b', data)
    out = {
        'observed_at_utc': datetime.now(timezone.utc).isoformat(),
        'round_start_utc': '2026-10-28T20:38:56Z', 'round_deadline_utc': '2026-10-29T03:38:56Z',
        'independent_component': model['sources'][0], 'independent_root': model['roots'][0],
        'independent_scope': 'All Bool signs, Nat significands including zero, Int exponents. Exact actual native32 word equality; includes signed zero, subnormal, normal, carry, infinity. No real-valued or finiteness premise.',
        'independent_source_dependencies': 'Only fixed public FloatLib/Mathlib reachable through original ContractTensor; no D cell, NormalCell, B2 body or new target dependency.',
        'composition_component': model['sources'][1], 'composition_root': model['roots'][1],
        'composition_dependencies': ['DyadicAgreement.lean.inc', model['sources'][2], 'The exact four dependency files in normal-cell-source-receipt.json'],
        'composition_scope': 'Actual roundDyadic of an exact Dyadic value whose toReal is strictly inside the signed cell of a normal raw32 q, including maximum-finite upper half. Candidate sign is derived by the retained NormalCell wrapper.',
        'public_sources': public,
        'attribution': 'quotient_normal_one adapted from the public MIT Integer/Rounding proof. Its exponent-zero top-level theorem is not assumed for arbitrary exponent.',
        'model_receipt_sha256': sha((HERE / 'dyadic-model-receipt.json').read_bytes()),
        'verification': {'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN', 'performance': 'NOT_RUN'},
        'source_status': 'DRAFT_WITH_COMPLETE_PROOF_TERMS_PENDING_PUBLIC_TYPING',
        'first_discriminator': 'D can type the independent 6876-byte fragment with one audited root on the original old-ContractTensor carrier before integrating its thin cell corollary.',
        'token_usage': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN', 'CI_owner': 'D only'
    }
    (HERE / 'dyadic-source-receipt.json').write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'independent': out['independent_component'], 'composition': out['composition_component'], 'fixed_blobs_verified': len(public)}))

if __name__ == '__main__':
    main()
