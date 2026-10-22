"""Add only an n=1 ordered scalar path to the exact verified direct-small parent."""
from pathlib import Path
import ast
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / 'f01-d7-direct-small/Kernel.lean'
PARENT_SHA256 = 'd9a808479dd6a7c7da345ce680773105b638cc6c9e8145e34d10f59751411fb3'
OUT = ROOT / 'f01-d7-singleton'
POLICY = ROOT.parents[0] / 'research/materials/20261022/R2-W01c/FloatLib_R2-W01c/public_sources/official/gate.py'

ADDITION = '''

namespace Submission

open FloatLib.Floats Competition

def singletonCore (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    Submission.add posZero
      (Submission.mul (A.toArray.getD ((b * m + i) * n + 0) posZero)
        (B.toArray.getD ((b * n + 0) * p + j) posZero))

theorem singletonCore_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (h : n = 1) :
    singletonCore batch m n p A B = referenceBmm batch m n p A B := by
  subst n
  unfold singletonCore referenceBmm
  apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
  funext q
  dsimp only
  simp only [Fin.foldl_succ, Fin.foldl_zero]

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n = 1 then singletonCore batch m n p A B
  else bmmBeforeSingleton batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i h
    rw [singletonCore_eq_reference batch m n p A B h]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeSingleton_spec batch m n p A B

end Submission
'''


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def main():
    raw = PARENT.read_bytes()
    source = raw.decode('utf-8')
    require(hashlib.sha256(raw).hexdigest() == PARENT_SHA256, 'exact direct-small parent hash differs')
    require('singletonCore' not in source and 'bmmBeforeSingleton' not in source, 'new declaration collides with parent')
    position = source.rindex('def bmm (')
    tail = source[position:]
    require(tail.count('def bmm (') == tail.count('theorem bmm_spec :') == 1, 'final parent dispatcher format drift')
    renamed = re.sub(r'\bbmm\b', 'bmmBeforeSingleton', tail).replace('bmm_spec', 'bmmBeforeSingleton_spec')
    restored = renamed.replace('bmmBeforeSingleton_spec', 'bmm_spec').replace('bmmBeforeSingleton', 'bmm')
    require(restored == tail, 'parent rename is not exactly reversible')
    payload = (source[:position] + renamed + ADDITION).encode('utf-8')
    child = payload.decode('utf-8')
    require(payload[:len(source[:position].encode())] == raw[:len(source[:position].encode())], 'parent prefix changed')
    tree = ast.parse(POLICY.read_text(encoding='utf-8'))
    banned_node = next(n for n in tree.body if isinstance(n, ast.Assign)
                       and any(isinstance(t, ast.Name) and t.id == 'BANNED' for t in n.targets))
    banned = re.compile(ast.literal_eval(banned_node.value.args[0]))
    require(banned.search(child) is None, 'official saved policy banned-token check failed')
    imports = [line for line in child.splitlines() if re.search(r'\bimport\b', line)]
    require(imports == ['import ContractTensor'], 'imports differ from allowed sole contract')
    options = [line for line in child.splitlines() if re.search(r'\bset_option\b', line)]
    parent_options = [line for line in source.splitlines() if re.search(r'\bset_option\b', line)]
    require(options == parent_options == [], 'unexpected/new elaboration options')
    require(len(payload) <= 256000, 'candidate exceeds official byte limit')
    # New runtime core must remain a direct ordered scalar expression.
    core = ADDITION.split('theorem singletonCore_eq_reference', 1)[0]
    require('NativeFinal' not in core and 'Fin.foldl' not in core, 'singleton core accidentally retains dot/fold machinery')
    OUT.mkdir(exist_ok=True)
    (OUT / 'Kernel.lean').write_bytes(payload)
    manifest = {
        'candidate': OUT.name, 'candidate_file': 'Kernel.lean',
        'candidate_sha256': hashlib.sha256(payload).hexdigest(), 'candidate_bytes': len(payload),
        'parent': 'competitions/floatlib/candidates/f01-d7-direct-small/Kernel.lean',
        'parent_sha256': PARENT_SHA256, 'parent_bytes': len(raw),
        'validation_mode': 'full-gate', 'proof_status': 'NOT_RUN', 'compile_status': 'NOT_RUN',
        'full_gate_status': 'NOT_RUN', 'performance_status': 'NOT_RUN', 'gain': 'UNKNOWN',
        'mechanism': 'Only n=1 uses one Submission.mul followed by Submission.add posZero at the exact reference k=0 addresses; bypasses NativeFinal.dot recursion, final-result guard and fallback replay. All other dimensions use the unchanged renamed direct-small dispatcher.',
        'scope': 'Shape-only n=1 branch; all input bit patterns and all batch/m/p including empty output. No seed, data or workload dispatch.',
        'proof_route': 'Substitute n=1 and reduce the reference ordered fold with Fin.foldl_succ and Fin.foldl_zero; reuse referenceBmm_spec and exact prior dispatcher spec.',
        'proof_source': 'https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Fin/Fold.lean',
        'semantic_review': {'signed_zero': 'Keeps the initial positive-zero add; never returns raw product alone.',
                            'nan': 'Uses unchanged Submission.mul and Submission.add, preserving their established exact semantics.',
                            'addresses': 'Original bmmDecodeC and exact k=0 getD address expressions/defaults.',
                            'empty_output': 'Vector.ofFn over Fin(batch*m*p); no nonemptiness assumption.',
                            'non_singleton_path': 'Exact reversible rename to bmmBeforeSingleton and bmmBeforeSingleton_spec.'},
        'local_static_validation': {'status': 'PASS_STATIC_ONLY', 'imports': imports, 'set_options': options,
                                    'banned_matches': [], 'policy_source': POLICY.relative_to(ROOT.parents[2]).as_posix(),
                                    'policy_sha256': hashlib.sha256(POLICY.read_bytes()).hexdigest(),
                                    'parent_prefix_unchanged_bytes': len(source[:position].encode()),
                                    'prior_dispatcher_reverse_rename': True},
        'validation_gap': 'Lean elaboration, kernel replay, axiom audit, all checksums and full current public-v2 paired timing remain NOT_RUN; static review is not proof acceptance.',
        'formal_submission': 'NOT_SUBMITTED'
    }
    (OUT / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(manifest, indent=2))


if __name__ == '__main__':
    main()
