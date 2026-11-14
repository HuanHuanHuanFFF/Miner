"""Bind source-only handoff and fixed public API bytes without compilation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[8]

def sha(data):
    return hashlib.sha256(data).hexdigest()

def main():
    APIs = [
        ('Scaling.lean.raw', 'ce65bc95bbedbf4554712e92e0a763a3e733a2ee',
         'FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Rational/Scaling.lean'),
        ('Native32-Base-Proof.lean.raw', 'e469f73d5fa8e5c3dc10dc91c402322aebf4db4a',
         'FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Proof.lean')
    ]
    fixed = '0d91825727839f597fd06b22fdd038ea21480f0c'
    public = []
    for name, blob, remote in APIs:
        p = HERE / 'sources' / name
        b = p.read_bytes()
        def git_hash(v):
            return hashlib.sha1(b'blob ' + str(len(v)).encode() + b'\0' + v).hexdigest()
        if git_hash(b) != blob:
            # apply_patch appends an extra blank line to terminal-newline input.
            assert b.endswith(b'\n') and git_hash(b[:-1]) == blob
            b = b[:-1]
            p.write_bytes(b)
        assert git_hash(b) == blob
        assert b'Released under MIT license' in b and b'Authors: FloatLib Team' in b
        public.append({'path': str(p.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(b),
                       'sha256': sha(b), 'git_blob_sha1': blob, 'git_blob_verified': True,
                       'url': f'https://github.com/lean-dojo/FloatLib/blob/{fixed}/{remote}',
                       'license': 'MIT; Authors: FloatLib Team'})
    model = json.loads((HERE / 'normal-cell-model-receipt.json').read_text(encoding='utf-8'))
    source = (HERE / 'NormalCell.lean.inc').read_bytes()
    assert sha(source) == model['source']['sha256']
    for dep in model['dependencies']:
        p = ROOT / dep['path']
        assert sha(p.read_bytes()) == dep['sha256']
    text = source.decode('utf-8')
    assert not re.search(r'\b(sorry|admit|axiom|unsafe|extern|native_decide)\b', text)
    assert not re.search(r'^import\s|^public import\s|^set_option\s', text, re.M)
    for root in model['roots']:
        assert re.search(r'^theorem ' + re.escape(root.split('.')[-1]) + r'\b', text, re.M)
    receipt = {
        'observed_at_utc': datetime.now(timezone.utc).isoformat(),
        'round_start_utc': '2026-10-28T20:38:56Z', 'round_deadline_utc': '2026-10-29T03:38:56Z',
        'component': model['source'], 'root_list': model['roots'],
        'exact_dependencies_in_order': model['dependencies'],
        'dependency_status': 'SOURCE_ONLY_NOT_INHERITED_ACCEPTANCE',
        'fixed_public_sources': public,
        'model_receipt_sha256': sha((HERE / 'normal-cell-model-receipt.json').read_bytes()),
        'field_domain': '1 <= e <= 254 and f < 8388608; both signs; all exact Nat numerators and positive Nat denominators; arbitrary Int source exponent',
        'sign_scope': 'Field primitive has the exact input sign. Raw wrapper derives that sign equals q.signBit from an explicit S = signedScaledRatToReal equation and signed strict cell bounds.',
        'maximum_finite': 'Upper half of the maximum-finite cell included; no abs(S) <= maxFinite sufficient guard.',
        'excluded': ['Zero/subnormal/infinite/NaN candidate words', 'Exact midpoint ties', 'Implicit identification with NativeBinary32.roundDyadic', 'New target runtime or benchmark'],
        'static_checks': 'SOURCE_HASH_DEPENDENCY_HASHES_ROOT_NAMES_NO_NEW_IMPORTS_NO_AXIOM_OR_BYPASS_TOKENS_VERIFIED',
        'verification': {'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN', 'performance': 'NOT_RUN'},
        'token_usage': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN',
        'CI_owner': 'D only; no B dispatch or compilation',
        'next': 'Root single critical review; D selects smallest old-ContractTensor statement carrier. Preserve independent arbitrary-exponent dyadic transport obligation.'
    }
    (HERE / 'normal-cell-source-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'component': receipt['component'], 'roots': receipt['root_list'], 'fixed_source_blobs_verified': len(public)}))

if __name__ == '__main__':
    main()
