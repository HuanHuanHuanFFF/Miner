"""One low-exponent signed-zero probe, preserving exact FULL60f elsewhere."""
from pathlib import Path
import ast
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / 'f01-d7-direct-nonnan/Kernel.lean'
PARENT_SHA = '60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15'
DOMAIN_SOURCE = ROOT / 'f01-r6-web-lowguards/Kernel.lean'
DOMAIN_SHA = '75ddbcff076c7fe17ba3d38616025eec9b74d647fe711ed6d77459454d3fbdbf'
OUT = ROOT / 'f01-d7-low-zero'
POLICY = ROOT.parent / 'research/materials/20261022/R2-W01c/FloatLib_R2-W01c/public_sources/official/gate.py'
OPPORTUNITY = ROOT / 'f01-d7-research/scalar-opportunity-807.json'

OLD_MUL = '''@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y
'''

EXTRA_PROOFS = '''
@[inline] def signedZero (sign : Bool) : UInt32 :=
  if sign then 0x80000000 else 0

theorem mantissa_zero (a : UInt32) (h : R2W01b.magnitude a = 0) :
    finiteMantissa (expField a) (fracField a) = (0 : UInt64) := by
  cases (R2W01b.magnitude_zero_iff a).mp h with
  | inl ha =>
    subst a
    decide
  | inr ha =>
    subst a
    decide

theorem product_zero (a b : UInt32)
    (hz : R2W01b.magnitude a = 0 ∨ R2W01b.magnitude b = 0) :
    finiteMantissa (expField a) (fracField a) *
      finiteMantissa (expField b) (fracField b) = (0 : UInt64) := by
  cases hz with
  | inl ha => simp only [mantissa_zero a ha, UInt64.zero_mul]
  | inr hb => simp only [mantissa_zero b hb, UInt64.mul_zero]

theorem core_zero (a b : UInt32)
    (hz : R2W01b.magnitude a = 0 ∨ R2W01b.magnitude b = 0) :
    FastMul.core a b = signedZero (Bool.xor (signBit a) (signBit b)) := by
  simp [FastMul.core, product_zero a b hz, FastMul.roundP, signedZero]

theorem zero_eq_low (x y : Binary32)
    (h : expField x.raw.1 + expField y.raw.1 < (128 : UInt32))
    (hz : R2W01b.magnitude x.raw.1 = 0 ∨ R2W01b.magnitude y.raw.1 = 0) :
    FastMul.ofBits (signedZero (Bool.xor (signBit x.raw.1) (signBit y.raw.1))) =
      LowScale.mul x y := by
  rw [LowScale.mul_eq]
  have hs := outer_special_false x.raw.1 y.raw.1 h
  simp [FastMul.mul, hs, core_zero x.raw.1 y.raw.1 hz]

end LowZero

'''

NEW_MUL = '''@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then
    if R2W01b.magnitude x.raw.1 = 0 ∨ R2W01b.magnitude y.raw.1 = 0 then
      FastMul.ofBits (LowZero.signedZero
        (Bool.xor (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit x.raw.1)
          (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit y.raw.1)))
    else LowScale.mul x y
  else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · rename_i h
    split
    · rename_i hz
      rw [LowZero.zero_eq_low x y h hz]
      exact LowScale.mul_spec x y
    · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y
'''


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    raw, domain_raw = PARENT.read_bytes(), DOMAIN_SOURCE.read_bytes()
    require(sha(raw) == PARENT_SHA, 'exact FULL60f parent differs')
    require(sha(domain_raw) == DOMAIN_SHA, 'accepted domain-proof source differs')
    source, domain = raw.decode('utf-8'), domain_raw.decode('utf-8')
    require(source.count(OLD_MUL) == 1 and 'namespace LowZero' not in source, 'root mul pattern drift or namespace collision')
    start = domain.index('theorem outer_finite (')
    end = domain.index('/-- Preserve the parent', start)
    accepted = domain[start:end]
    require(accepted.count('theorem ') == 2 and 'theorem outer_special_false' in accepted, 'domain proof extraction differs')
    helpers = ('namespace LowZero\n\nopen FloatLib.Floats Competition\n'
               'open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32\n\n'
               + accepted + EXTRA_PROOFS)
    position = source.index(OLD_MUL)
    payload = source.replace(OLD_MUL, helpers + NEW_MUL, 1).encode('utf-8')
    child = payload.decode('utf-8')
    require(child.replace(helpers + NEW_MUL, OLD_MUL, 1).encode() == raw, 'unexpected changes outside root mul/proof and new helpers')
    prefix = source[:position].encode()
    suffix = source[position + len(OLD_MUL):].encode()
    require(payload.startswith(prefix) and payload.endswith(suffix), 'native/add prefix or sum/bmm suffix changed')
    require('else LowScale.mul x y\n  else nativeMul x y' in NEW_MUL, 'miss/high branch must retain exact prior paths')
    require('R6Domain.core' not in helpers and '@[inline] def core' not in helpers, 'runtime lowguards changes must not be imported')
    tree = ast.parse(POLICY.read_text(encoding='utf-8'))
    node = next(n for n in tree.body if isinstance(n, ast.Assign)
                and any(isinstance(t, ast.Name) and t.id == 'BANNED' for t in n.targets))
    banned = re.compile(ast.literal_eval(node.value.args[0]))
    require(banned.search(child) is None, 'saved official banned-token check failed')
    imports = [line for line in child.splitlines() if re.search(r'\bimport\b', line)]
    options = [line for line in child.splitlines() if re.search(r'\bset_option\b', line)]
    require(imports == ['import ContractTensor'] and not options and len(payload) <= 256000, 'import/options/size policy failed')
    observed = json.loads(OPPORTUNITY.read_bytes())
    require(observed['complete'] and observed['all_scalar_checksums_match_actual_lean'] and observed['discovery_seed'] == 807,
            'opportunity evidence incomplete or not discovery807')
    require(observed['totals']['mul']['timed']['mul_low_zero_hits'] == 387516, 'expected exact discovered zero count')
    manifest = {
        'candidate': OUT.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(payload), 'candidate_bytes': len(payload),
        'parent': 'competitions/floatlib/candidates/f01-d7-direct-nonnan/Kernel.lean', 'parent_sha256': PARENT_SHA, 'parent_bytes': len(raw),
        'validation_mode': 'full-gate', 'proof_status': 'NOT_RUN', 'compile_status': 'NOT_RUN',
        'full_gate_status': 'NOT_RUN', 'performance_status': 'NOT_RUN', 'gain': 'UNKNOWN',
        'mechanism': 'Inside the unchanged ex+ey<128 branch only, zero magnitude of either operand returns FastMul.ofBits signedZero with the exact original Bool.xor signBit. A miss executes unchanged LowScale.mul; high/native/add/sum/bmm runtime source is unchanged.',
        'scope': 'Proposed all-input exact equality. Outer low exponent sum excludes NaN/Inf, including zero-times-Inf/NaN. No seed, data-distribution or benchmark dispatch.',
        'proof_route': 'Reuse accepted outer_finite/outer_special_false proof bytes only; magnitude_zero_iff reduces each zero word to +/-0; finiteMantissa=0, UInt64 product=0, original FastMul.roundP zero branch, LowScale.mul_eq and existing full specs.',
        'domain_proof_source': {'candidate': DOMAIN_SOURCE.parent.name, 'kernel_sha256': DOMAIN_SHA,
                                'accepted_theorems_sha256': sha(accepted.encode()),
                                'theorems': ['outer_finite', 'outer_special_false'],
                                'copied_byte_identically_inside_new_namespace': True, 'runtime_core_or_guard_deletion_copied': False,
                                'accepted_source_full_gate_run': '39791810276'},
        'local_static_validation': {'status': 'PASS_STATIC_ONLY', 'imports': imports, 'set_options': options,
                                    'banned_matches': [], 'policy_source_sha256': sha(POLICY.read_bytes()),
                                    'parent_prefix_unchanged_bytes': len(prefix), 'parent_suffix_unchanged_bytes': len(suffix),
                                    'parent_prefix_sha256': sha(prefix), 'parent_suffix_sha256': sha(suffix),
                                    'exact_reverse_patch_check': True, 'old_low_miss_and_native_high_paths_preserved': True},
        'discovery_evidence': {'file': 'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity-807.json',
                               'sha256': sha(OPPORTUNITY.read_bytes()), 'timed_low_zero_pairs': 387516,
                               'timed_low_pairs': observed['totals']['mul']['timed']['mul_outer_low_pairs'],
                               'warning': 'Finite Python model with 86 actual per-case checksums matched against 4 repeated records; not Lean proof or measured gain. No future confirmation sample used.'},
        'potential_lean_targets': ['decide reduction of finiteMantissa for literal +/-0',
                                   'product-zero rewrite under FastMul.core lets',
                                   'Bool special guard and signedZero unfolding in zero_eq_low',
                                   'nested low/zero split transports exact root mul_spec'],
        'validation_gap': 'New theorem elaboration, kernel replay, axiom audit, checksum suite and complete paired timing remain NOT_RUN.',
        'formal_submission': 'NOT_SUBMITTED'
    }
    OUT.mkdir(exist_ok=True)
    (OUT / 'Kernel.lean').write_bytes(payload)
    (OUT / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    require(PARENT.read_bytes() == raw and DOMAIN_SOURCE.read_bytes() == domain_raw, 'a parent/proof source changed during generation')
    print(json.dumps(manifest, indent=2))


if __name__ == '__main__':
    main()
