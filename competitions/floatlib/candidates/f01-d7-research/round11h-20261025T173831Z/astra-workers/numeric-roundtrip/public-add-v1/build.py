"""Build a new public ADD proof attempt with reversible identifier maps; never edits frozen inputs."""
from pathlib import Path
from datetime import datetime, timezone
from types import SimpleNamespace
import ast
import hashlib
import importlib.util
import json
import re

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
SOURCE = PARENT / 'Probe-sorted-add-chain-v1.lean'
SPEC = PARENT / 'Public-add-spec-v1.lean.inc'
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
LEXER = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
sha = lambda b: hashlib.sha256(b).hexdigest()
def binding(p):
    b = p.read_bytes()
    return {'path': p.relative_to(ROOT).as_posix(), 'bytes': len(b), 'sha256': sha(b)}

original = SOURCE.read_bytes()
assert sha(original) == '6816ca1bade81c8c7efa6140c01c8ff0611cd4cd0d1fce5fcfd8def37b6eb7cf'
base = BASE.read_text(encoding='utf-8')
joined = original.decode('utf-8') + '\n' + SPEC.read_text(encoding='utf-8')
namespace_map = {'Submission': 'R18A', 'R16UInt32Roundtrip': 'U18', 'R14NatNormal': 'N18',
    'R14WordAddRounding': 'W18', 'R17NumericNormalize': 'Z18', 'R17Threshold': 'T18',
    'R17NumericOutput': 'O18', 'R18SortedWord': 'A18', 'R17NumericAdd': 'K18',
    'R18AddSpec': 'P18', 'A16L': 'L18'}
short_names = {
    'native_round_normal':'nativeNormal', 'model_round_normal':'modelNormal', 'raw_normal_decode':'rawNormal',
    'no_carry_at_31':'noCarry31', 'rounded_leading':'roundedLead', 'high_mantissa':'highMant',
    'roundedInteger_fit':'roundIntFits', 'roundedInteger_eq_RNE':'roundIntRNE',
    'native_high_decode':'decodeHigh', 'toUInt32_of_nonnegative_integral_decode':'castDecoded',
    'output_exponent_bounds':'expBounds', 'output_exponent_guard':'expGuard',
    'numeric_shift_toNat':'shiftNat', 'numeric_fraction_toNat':'fracNat',
    'same_magnitude_bounds':'sameMagBounds', 'opposite_magnitude_bounds':'oppMagBounds',
    'same_top_no_carry':'sameNoCarry', 'opposite_top_no_carry':'oppNoCarry',
    'same_leading_bounds':'sameLeadBounds', 'opposite_leading_bounds':'oppLeadBounds',
    'same_R_interval':'sameInterval', 'opposite_R_interval':'oppInterval',
    'same_threshold_from_inputs':'sameThreshold', 'opposite_threshold_from_inputs':'oppThreshold',
    'word_threshold_toNat':'thresholdNat', 'same_word_shift_from_inputs':'sameWordShift',
    'opposite_word_shift_from_inputs':'oppWordShift', 'pack_of_masked_fraction':'packFrac',
    'word_exponent_shift_relation':'wordExpShift', 'numeric_pack_model':'packModel',
    'numeric_add_of_alignment':'addAligned', 'shifted_ne_zero':'shiftNeZero',
    'align_high_low':'alignHL', 'exact_high_low':'exactHL', 'exact_low_high':'exactLH',
    'spec_add_of_decodes':'addDecoded', 'magnitude_bounds':'magBounds',
    'magnitude_word_nat':'wordMagNat', 'high_low_model':'modelHL', 'low_high_model':'modelLH'}
pat = lambda name: r"(?<![\w'])" + re.escape(name) + r"(?![\w'])"
for old, new in list(short_names.items()):
    # Never rename a pre-existing B2 symbol or any name that could collide.
    if re.search(pat(old), base):
        del short_names[old]
        continue
    assert not re.search(pat(new), joined), new
for new in namespace_map.values():
    assert not re.search(pat(new), joined), new
mapping = {**namespace_map, **short_names}
mapped = joined
map_receipt = []
for old, new in mapping.items():
    hits = [m.start() for m in re.finditer(pat(old), mapped)]
    before = mapped
    mapped = re.sub(pat(old), new, mapped)
    assert re.sub(pat(new), old, mapped) == before
    map_receipt.append({'old': old, 'new': new, 'occurrences': len(hits),
                        'saved_bytes': len(before.encode()) - len(mapped.encode()), 'exact_inverse': True,
                        'before_sha256': sha(before.encode()), 'after_sha256': sha(mapped.encode()),
                        'byte_offsets_before_this_mapping': [len(before[:i].encode('utf-8')) for i in hits]})
inverse = mapped
for old, new in reversed(list(mapping.items())):
    inverse = re.sub(pat(new), old, inverse)
assert inverse == joined

sp = importlib.util.spec_from_file_location('budget_lex', LEXER)
lex = importlib.util.module_from_spec(sp); sp.loader.exec_module(lex)
_, comments, literals = lex.lex(mapped)
assert not literals
attribution = re.compile(r'copyright|license|authors?\s*[:：]|SPDX|https?://|来源|作者|许可', re.I)
remove = []
for a, b, kind in comments:
    line_a = mapped.rfind('\n', 0, a) + 1
    line_b = mapped.find('\n', b)
    if line_b < 0: line_b = len(mapped)
    if not mapped[line_a:a].strip() and not mapped[b:line_b].strip() and not attribution.search(mapped[a:b]):
        remove.append((a, b))
comment_receipts = []
compact = mapped
for a, b in reversed(remove):
    piece = compact[a:b]
    comment_receipts.append({'char_start': a, 'char_end': b, 'bytes': len(piece.encode()), 'sha256': sha(piece.encode())})
    compact = compact[:a] + '\n' * piece.count('\n') + compact[b:]
_, remaining_comments, _ = lex.lex(compact)
protected = set()
for a, b, _ in remaining_comments:
    protected.update(range(compact.count('\n', 0, a) + 1, compact.count('\n', 0, b) + 2))
no_blanks = ''.join(line for i, line in enumerate(compact.splitlines(keepends=True), 1)
                    if i in protected or line.strip())
# Code tokens/layout-indentation survive; attribution comments are preserved exactly.
assert [s for s in lex.lex(mapped)[0].splitlines() if s.strip()] == [s for s in lex.lex(no_blanks)[0].splitlines() if s.strip()]
for a, b, _ in remaining_comments:
    assert compact[a:b] in no_blanks

wrapper = '''
namespace Submission
open FloatLib.Floats Competition
@[inline] def add (x y : Binary32) : Binary32 := R18A.K18.guardedAdd R18A.add x y
theorem add_spec (x y : Binary32) : add x y = ExecFloat.Spec.add x y :=
  R18A.P18.guarded_spec R18A.add R18A.add_spec x y
@[inline] def mul := R18A.mul
theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y := R18A.mul_spec
@[inline] def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R18A.sum x
theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := R18A.sum_spec
@[inline] def bmm := R18A.bmm
theorem bmm_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := R18A.bmm_spec
end Submission
'''
assert not re.search(pat('Submission'), no_blanks)
data = (no_blanks + wrapper).encode('utf-8')
stats = {'raw_joined_bytes': len(joined.encode()), 'identifier_map_saved': len(joined.encode()) - len(mapped.encode()),
         'comment_blank_saved': len(mapped.encode()) - len(no_blanks.encode()), 'wrapper_bytes': len(wrapper.encode()),
         'final_bytes': len(data), 'margin': 256000 - len(data)}
(HERE / 'size-check.json').write_bytes((json.dumps(stats, indent=2) + '\n').encode())
assert len(data) <= 256000, stats
out = HERE / 'Kernel.lean'; out.write_bytes(data)
assert b'\r' not in data
assert re.findall(rb'^namespace Submission\s*$', data, re.M) == [b'namespace Submission']

t = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS', 'ATTRIBUTES', 'BANNED']:
    n = next(n for n in t.body if isinstance(n, ast.Assign) and any(isinstance(x, ast.Name) and x.id == name for x in n.targets))
    env[name] = re.compile(ast.literal_eval(n.value.args[0])) if name == 'BANNED' else ast.literal_eval(n.value)
fs = [n for n in t.body if isinstance(n, ast.FunctionDef) and n.name in ['intake', 'policy', 'options']]
exec(compile(ast.Module(body=fs, type_ignores=[]), str(GATE), 'exec'), env)
checks = {'intake': env['intake'](out, SimpleNamespace(slot='full')),
          'policy': env['policy'](out, SimpleNamespace(slot='full')),
          'options': env['options'](out.read_text(encoding='utf-8'))}
assert all(v is None for v in checks.values()), checks
old_roots = json.loads((PARENT / 'sorted-add-chain-v1-manifest.json').read_text(encoding='utf-8'))['explicit_roots']
new_roots = ['Submission.R18AddSpec.' + n for n in re.findall(r'^theorem (\w+)', SPEC.read_text(encoding='utf-8'), re.M)]
def rename(s):
    for old, new in mapping.items(): s = re.sub(pat(old), new, s)
    return s
roots = [rename(x) for x in old_roots + new_roots]
assert len(roots) == len(set(roots)) == 67
public_roots = ['Submission.' + x for x in ['add_spec', 'mul_spec', 'sum_spec', 'bmm_spec']]
audit = HERE / 'HelperAudit.lean.inc'
audit.write_bytes((''.join('#print axioms ' + name + '\n' for name in roots + public_roots)).encode())
manifest = {
    'created_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'TRUE_PUBLIC_ADD_ENTRY_PROOF_ATTEMPT_NOT_COMPILED', 'candidate': binding(out),
    'inputs': [binding(p) for p in [SOURCE, SPEC, BASE, LEXER, GATE]], 'size': stats,
    'identifier_mapping': map_receipt, 'identifier_mapping_exact_reverse': True,
    'removed_nonattribution_comments': comment_receipts, 'attribution_and_license_preserved': True,
    'nonblank_code_lines_preserve_indentation_and_tokens_after_mapping': True,
    'extra_theorem_deletions': [], 'inherited_theorem_deletions': '../source-budget-add/plan.json',
    'all63_previous_roots_preserved_under_explicit_mapping': True,
    'new_helper_roots': [rename(x) for x in new_roots], 'helper_roots': roots,
    'public_gate_roots': public_roots, 'audit_file': binding(audit),
    'public_mapping': {'add': 'R18A.K18.guardedAdd R18A.add', 'add_spec': 'R18A.P18.guarded_spec R18A.add R18A.add_spec',
                       'mul': 'R18A.mul', 'sum': 'R18A.sum', 'bmm': 'R18A.bmm'},
    'fallback_cycle_check': 'Old renamed body has no Submission identifier; new ADD receives R18A.add. Other public entries alias the old implementations.',
    'static_checks': checks, 'canonical_LF': True,
    'compile': 'NOT_RUN', 'kernel': 'NOT_RUN', 'helper_audit': 'NOT_RUN', 'full_gate': 'NOT_RUN', 'performance': 'UNKNOWN',
    'limits': 'Complete proof attempt, not formal closure. All67 helpers and4 public specs require actual pinned validation; old22-root success does not transfer.',
    'Git': False, 'CI': False, 'local_Lean': False,
}
(HERE / 'manifest.json').write_bytes((json.dumps(manifest, indent=2, ensure_ascii=False) + '\n').encode('utf-8'))
print(json.dumps({'candidate': manifest['candidate'], 'size': stats, 'checks': checks, 'audit_roots': len(roots + public_roots)}, indent=2))
