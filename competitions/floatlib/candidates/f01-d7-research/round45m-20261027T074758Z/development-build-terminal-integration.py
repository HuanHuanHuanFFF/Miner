"""Prepare the next full-entry proof attempt; no inherited compilation claim."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
CANDIDATES = HERE.parent.parent


def main():
    parent = CANDIDATES / 'f01-r19-dev-dc-rawpair2'
    original = (parent / 'Kernel.lean').read_bytes()
    metadata = json.loads((parent / 'manifest.json').read_bytes())
    assert hashlib.sha256(original).hexdigest() == metadata['candidate_sha256']
    source = original.decode('utf-8')
    fragment_path = HERE / 'research/representation/terminal-pair/TerminalPair.lean.inc'
    fragment = fragment_path.read_text(encoding='utf-8')
    helpers = fragment[fragment.index('@[inline] def emit2'):fragment.index('@[noinline] def control')]
    helpers = helpers.replace('loopPair', 'loop')
    start = source.index('@[inline] def groupFrom (n baseA baseB p : Nat)')
    end = source.index('@[inline] def group (batch m n p : Nat)', start)
    old = source[start:end]
    renamed = old.replace('def groupFrom ', 'def groupFromOriginal ', 1)
    addition = '''@[inline] def groupFrom (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (g : Fin (groups p)) : Array Binary32 :=
  let count := min 2 (p - 2 * g.val)
  if count = 1 then groupFromOriginal n baseA baseB p A B out g
  else loopEmit n baseA (baseB + 2 * g.val) p A B out
    0 Packed10.zero32 Packed10.zero32

theorem groupFrom_eq_original (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (g : Fin (groups p)) :
    groupFrom n baseA baseB p A B out g =
      groupFromOriginal n baseA baseB p A B out g := by
  have hg : 2 * g.val < p := by
    have h := g.isLt
    unfold groups at h
    omega
  by_cases h : min 2 (p - 2 * g.val) = 1
  · simp only [groupFrom, h, if_pos]
  · have hc : min 2 (p - 2 * g.val) = 2 := by omega
    simp only [groupFrom, groupFromOriginal, h, if_neg]
    rw [loopEmit_eq]
    simp only [hc]
    rfl

'''
    source = source[:start] + helpers + renamed + addition + source[end:]
    proof_old = '  unfold group groupFrom\n  dsimp only\n  split'
    proof_new = '  unfold group\n  rw [groupFrom_eq_original]\n  unfold groupFromOriginal\n  dsimp only\n  split'
    assert source.count(proof_old) == 1
    source = source.replace(proof_old, proof_new)
    reverse = source.replace(proof_new, proof_old)
    reverse = reverse.replace(helpers + renamed + addition, old)
    assert reverse.encode() == original
    raw = source.encode()
    assert len(raw) <= 256000 and source.count('import ContractTensor') == 1
    name = 'f01-r20-dev-terminal-dc1'
    dest = CANDIDATES / name
    dest.mkdir(exist_ok=False)
    (dest / 'Kernel.lean').write_bytes(raw)
    helper = HERE.parent / 'round9h-20261026T194639Z/development-helper-audit-v8.py'
    roots = ['Submission.' + n for n in ('add_spec', 'mul_spec', 'sum_spec', 'bmm_spec',
             'R19DCRawPair.loop_s0', 'R19DCRawPair.loop_s1', 'R19DCRawPair.loopEmit_eq',
             'R19DCRawPair.groupFrom_eq_original', 'R19DCRawPair.core_eq_reference')]
    manifest = {'candidate': name, 'candidate_file': 'Kernel.lean',
                'candidate_sha256': hashlib.sha256(raw).hexdigest(), 'candidate_bytes': len(raw),
                'created_at_utc': datetime.now(timezone.utc).isoformat(),
                'parent': parent.name, 'parent_sha256': hashlib.sha256(original).hexdigest(),
                'validation_mode': 'statement-only', 'proof_status': 'FULL_ENTRY_PROOF_ATTEMPT_NOT_RUN',
                'performance': 'NOT_RUN', 'formal_submission': 'NOT_SUBMITTED',
                'mechanism': 'Complete two-column DC groups consume the dot accumulators directly into finish/push; odd tail keeps original single-dot path. Public BMM now reaches the new loop through original dispatch. Other operations and guards unchanged.',
                'important_boundary': 'The earlier 8-root result covers the isolated diagnostic b6b77553 only. This new public integration and its proof edits have NOT_RUN status; no new CI is started late in R20.',
                'inverse_splice_exact': True, 'explicit_helper_audit': roots,
                'helper_audit_expected_count': len(roots),
                'helper_audit_required_endpoints': ['Submission.bmm_spec', 'Submission.R19DCRawPair.groupFrom_eq_original'],
                'helper_audit_source_sha256': hashlib.sha256(raw).hexdigest(),
                'helper_audit_module': helper.name, 'helper_audit_module_sha256': hashlib.sha256(helper.read_bytes()).hexdigest(),
                'diagnostic_evaluations': [],
                'next_gate': 'First statement + original whole-module replay + explicit nine roots. Inspect actual new public selected caller and lost/reintroduced closure/array lifetime. Only then buy complete full-call performance D against B2; new A/B confirmations remain required.'}
    (dest / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    (HERE / 'development-terminal-integration-next.json').write_text(
        json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: manifest[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))


if __name__ == '__main__':
    main()
