"""Package shared portable proofs. Old sources stay immutable; no Lean or CI."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, re, ast

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
C = ROOT / 'competitions/floatlib/candidates'
sha = lambda b: hashlib.sha256(b).hexdigest()
base = (C / 'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(base) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
wp = C / 'f01-d7-research/round3h30m-20261028T230130Z/research/representation/WidenNormal.lean.inc'
sp = HERE / 'NativeSumEnclosure.lean.inc'
mp = C / 'f01-r24-research-native-mul-bridge2/NativeMul.lean.inc'
assert sha(wp.read_bytes()) == '5e09ce0e1222074c48896394285796b276faf13b7c686c2e2eaa67548cf97fa3'
assert sha(sp.read_bytes()) == '99d69cc98d96662d2daab76a907af18fdd263136881d62f8947d76795b3bee73'
assert sha((mp.parent / 'Kernel.lean').read_bytes()) == 'ce6813a7421922e188ed779400bd6e830fde1c8f9ffcad991d47fe38d300e3eb'
w, s, m = [p.read_text(encoding='utf-8') for p in [wp, sp, mp]]
clean = lambda t: re.sub(r'\n\s*\n', '\n', re.sub(r'/\-.*?\-/', '', t, flags=re.S)).strip() + '\n'
w = w[:w.index('theorem native_finite_of_decode')] + '''theorem native_finite (u : UInt32) (h : Domain u) : (value u).isFinite = true := by
  rw [← Submission.R24RepresentationSum.native_finite_eq]
  change Model.isFinite (native64 (value u)) = true
  rw [native_model u h]
  exact raw_finite u h

''' + w[w.index('theorem shift29_toReal'):]
w = w[:w.index('theorem actual_native_value')] + 'end Submission.R24RepresentationWiden\n'
renames = dict(zip(['expWord_toNat','fracWord_toNat','signWord_toNat','expWide_toNat',
    'expWide_shift_toNat','fracWide_shift_toNat','widenBits_normal_toNat','raw64_bits',
    'raw64_sign','raw64_exp','raw64_frac','raw64_eq_fields','widenBits_normal_fields',
    'wordExp_lt','widenBits_posZero','widenBits_negZero','shift29_toReal','native_ofBits_of_decode'],
    ['eNat','fNat','sNat','ewNat','esNat','fsNat','wideNat','bits','sign','exp','frac',
     'fields','wideFields','eLt','wideZ','wideNZ','shiftReal','ofBitsModel']))
for old, new in renames.items():
    w = re.sub(r'\b' + old + r'\b', new, w)
s = s[:s.index('theorem actual_sum_enclosure')] + 'end Submission.R24RepresentationSum\n'
mul = '''namespace Submission.R24DotEnclosure
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange FloatLib.Floats.Formats.Flocq
open Submission.R24RepresentationSum
abbrev F64 := FloatFormat.binary64
abbrev F32 := FloatFormat.binary32
abbrev raw32 (u : UInt32) : Model F32 := Model.ofUInt32 u
'''
mul += '''theorem native_mul (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x * y) = Model.mul (native x) (native y) := by
'''
mul += m[m.index('  change Model.ofFloatModel (Float.Model.mul'):m.index('private theorem mul_view')]
mul += m[m.index('private theorem f32_product_grid'):m.index('/-- Once two native')].replace('private theorem', 'theorem')
mul += 'end Submission.R24DotEnclosure\n'
parts = [clean(s), clean(w), clean(mul), (HERE / 'DotComposition.lean.inc').read_text(encoding='utf-8')]
names = ['DotSharedSum.lean.inc', 'DotSharedWiden.lean.inc', 'DotProductGrid.lean.inc', 'DotComposition.lean.inc']
for name, part in zip(names[:3], parts[:3]):
    (HERE / name).write_text(part, encoding='utf-8', newline='\n')
blobs = [p.encode('utf-8') for p in parts]
blob = base + b'\n' + b'\n'.join(blobs)
budget = dict(base_bytes=len(base), component_bytes=[len(b) for b in blobs], total_bytes=len(blob), cap=256000,
              bytes_remaining=256000-len(blob), observed_at_utc=datetime.now(timezone.utc).isoformat())
(HERE / 'dot1-byte-preflight.json').write_text(json.dumps(budget, indent=2)+'\n', encoding='utf-8')
print(json.dumps(budget))
assert len(blob) <= 256000, 'Preserved exact byte gap; no candidate is emitted above cap'
assert blob[:len(base)] == base
for b in blobs:
    assert re.search(rb'(?m)^\s*(?:import|axiom|unsafe)\b', b) is None
    for forbidden in (b'sorry', b'implemented_by', b'@[extern', b'native_decide'):
        assert forbidden not in b, forbidden
out = C / 'f01-r24-research-dot-enclosure-1'
out.mkdir(exist_ok=True)
(out / 'Kernel.lean').write_bytes(blob)
helper = 'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
roots = ['Submission.R24RepresentationWiden.native_value', 'Submission.R24RepresentationSum.sum_enclosure']
roots += ['Submission.R24DotEnclosure.' + n for n in ['native_mul', 'f32_product_grid',
          'raw_abs_bound', 'raw_product_bound', 'product_exact', 'actual_dot_enclosure']]
manifest = dict(candidate=out.name, candidate_file='Kernel.lean', candidate_sha256=sha(blob), candidate_bytes=len(blob),
    created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='statement-only', diagnostic_only=True,
    diagnostic_timeout_seconds=180, proof_status='NOT_RUN', performance='NOT_RUN', formal_submission='NOT_SUBMITTED',
    official_submission_inherited=False, helper_audit_module='development-helper-audit-v8.py',
    helper_audit_module_path=helper, helper_audit_module_sha256=sha((C/helper).read_bytes()),
    explicit_helper_audit=roots, helper_audit_required_endpoints=roots, helper_audit_expected_count=len(roots),
    helper_audit_source_sha256=sha(blob), diagnostic_evaluations=[], runtime_base_sha256=sha(base),
    runtime_base_prefix_bytes=len(base), byte_identical_base_prefix_verified=True,
    components=[dict(path=(HERE/n).relative_to(ROOT).as_posix(), sha256=sha(b), bytes=len(b)) for n,b in zip(names,blobs)],
    public_endpoints='All four B2 public endpoints and proofs are unchanged byte-for-byte in the complete prefix.',
    scope='Portable old ContractTensor/B2 raw32-pair to actual Native64 exact product and actual native SUM enclosure. No ContractExact kernels or benchmark.',
    semantic_endpoint='Given H<=506,L<=30,length<=2^L and each pair Domain(a),Domain(b),(E(a)-1)+(E(b)-1)<=H, dot is finite and actual model real error from exact raw32 dot <=2^(H+2L-303). Products are proved finite/exact/bounded, not external hypotheses.',
    guard_scope='Domain excludes all nonzero subnormals and exponent255 words. Nat exponent index truncates at zero, conservatively checks zero products too.',
    omissions='Comments and unused presentation-only W.actual_native_value/signed_zero_bits and S.actual_sum_enclosure wrappers omitted; W.native_finite shares S.native_finite_eq; C native_mul uses the shared native model alias directly, omitting redundant Binary adapter rewrites; grid proof unchanged. Old source artifacts remain unchanged.',
    widen_internal_proof_name_map=renames,
    runtime_limit='List.map product then native left fold is an executable proof probe; no optimized kernel or codegen/performance claim.',
    source_inputs=[dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(p.read_bytes())) for p in [wp,sp,mp]],
    local_Lean=False, CI_owner='D', window_start_utc='2026-10-28T20:38:56Z', shared_deadline_utc='2026-10-29T03:38:56Z',
    actual_phase_first_utc='2026-10-28T23:20:48Z', tokens='UNKNOWN', cached_input_tokens='UNKNOWN',
    source_of_authorization='Parent R24 portable mathematical composition task; no new track implementation')
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
receipt = dict(manifest=manifest, budget=budget, builder_sha256=sha(Path(__file__).read_bytes()),
    checked_at_utc=datetime.now(timezone.utc).isoformat(), Lean_status='NOT_RUN',
    static_checks=['exact B2 prefix', '256000 B cap', 'source identity hashes', 'no added import/unsafe/axiom/sorry/extern',
                   'v8 candidates-relative helper path/hash; root-relative components', 'original180 timeout and R24 deadline'])
(HERE/'dot1-source-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
ast.parse(Path(__file__).read_text(encoding='utf-8'))
print(json.dumps(dict(candidate=out.name,sha256=sha(blob),bytes=len(blob),roots=roots,status='NOT_RUN')))
