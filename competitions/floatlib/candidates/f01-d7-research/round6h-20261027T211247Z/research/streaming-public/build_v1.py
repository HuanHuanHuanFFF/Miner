"""Assemble exact R21 streaming pair/writer into a complete public BMM draft.

No Lean invocation, Git operation, or CI dispatch is performed here.
"""
from pathlib import Path
import hashlib
import json
import re
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[7]
OUT = Path(__file__).resolve().parent
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round1h-20261027T103538Z/research'
SOURCE = OLD / 'terminal-proof/writer/full-matrix-proof-reproduction.lean'
EXPECTED = 'c3c3d6cb7fca720beebcf270036f076508abbe62ab40e722e37c8a3a7ffe2705'

def sha(data):
    return hashlib.sha256(data).hexdigest()

def main():
    raw = SOURCE.read_bytes()
    assert sha(raw) == EXPECTED
    text = raw.decode('utf-8')
    old_start = text.index('\ndef bmm (batch m n p : Nat)')
    old_end = text.index('\nend Submission', old_start)
    block = text[old_start:old_end]
    assert block.count('def bmm ') == 1 and block.count('theorem bmm_spec ') == 1
    block = re.sub(r'\bbmm_spec\b', 'bmmBeforeR22Streaming_spec', block)
    block = re.sub(r'\bbmm\b', 'bmmBeforeR22Streaming', block)
    text = text[:old_start] + block + text[old_end:]
    public = (OUT / 'PublicEntry.lean.inc').read_text(encoding='utf-8')
    text += '\n\n' + public
    dest = OUT / 'v1'
    dest.mkdir(exist_ok=True)
    payload = text.encode('utf-8')
    (dest / 'Kernel.lean').write_bytes(payload)
    roots = json.loads((OLD / 'terminal-proof/writer/full-matrix-manifest.json').read_text(encoding='utf-8'))['roots']
    roots += ['Submission.bmmBeforeR22Streaming_spec', 'Submission.R21StreamingMatrix.core_eq_reference']
    assert len(roots) == len(set(roots))
    audit = 'import Submission\n\n' + '\n'.join('#print axioms ' + r for r in roots) + '\n'
    (dest / 'HelperAudit.lean.inc').write_text(audit, encoding='utf-8', newline='\n')
    manifest = {
        'candidate': 'r22-streaming-public-v1',
        'created_at_utc': datetime.now(timezone.utc).isoformat(),
        'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(payload),
        'candidate_bytes': len(payload), 'parent_sha256': EXPECTED,
        'parent_source': str(SOURCE.relative_to(ROOT)),
        'streaming_pair_base_sha256': '4e36c931825b4c152933208987f066c95a5a0aada79cdea67202a045a7953ba4',
        'proof_status': 'NOT_RUN', 'performance': 'UNKNOWN',
        'formal_submission': 'NOT_SUBMITTED',
        'public_algorithms_unchanged': False,
        'mechanism': 'Original underflow-zero guard; otherwise complete batch-local floor(m/2) pair driver and original single-row odd tail. Each output retains original k order and Packed10.finish NaN replay.',
        'runtime_components_changed': ['public bmm binding'],
        'old_public_root_preserved_as': 'Submission.bmmBeforeR22Streaming',
        'explicit_helper_audit': roots,
        'helper_audit_expected_count': len(roots),
        'helper_audit_required_endpoints': roots,
        'helper_audit_source_sha256': sha(payload),
        'source_size_limit_pass': len(payload) <= 256000,
        'limits': [
            'R21 19-root PASS covers original pair component only; no PASS inherited for new writer composition or public entry.',
            'No threshold selection or adoption is justified; D is separately measuring complete two-row caller costs.',
            'Matrix route currently covers narrow widths too; this is a proof/integration specimen rather than a measured dispatch policy.',
            'No local Lean compilation, no CI dispatch, no Git mutation.'
        ],
    }
    (dest / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: manifest[k] for k in ['candidate_sha256','candidate_bytes','helper_audit_expected_count','proof_status']}, ensure_ascii=False))

if __name__ == '__main__':
    main()
