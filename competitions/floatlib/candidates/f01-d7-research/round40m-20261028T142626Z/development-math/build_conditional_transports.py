"""Source-only fallback bodies. Never edits the frozen MathOutletR23Fix1 input."""
from pathlib import Path
import difflib
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
raw = (HERE/'MathOutletR23Fix1.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest() == '159e0633eee16fa1b054d2b0adcb0a99b0a5fc7dfe96e776097de6d9f4e467e9'
text = raw.decode()
start = text.index('set_option maxHeartbeats 1000000 in\ntheorem normalCore_eq_roundP')
stop = text.index('\ntheorem finiteMantissa_eq', start)
original = text[start:stop]
needle = '  rw [roundP_normal sign p s hp.1 hp.2 hs0 hs1]\n'
assert original.count(needle) == 1
focused = original.replace(needle, '  conv_rhs => rw [roundP_normal sign p s hp.1 hp.2 hs0 hs1]\n')
prefix = original[:original.index(needle)]
staged = prefix + '''  have hshape : normalCore s u v =
      ((u ^^^ v) &&& (0x80000000 : UInt32)) |||
        (exponentWord s p <<< 23) ||| (mantissaWord p-8388608) := by
    rfl
  have hpack :
      ((u ^^^ v) &&& (0x80000000 : UInt32)) |||
        (exponentWord s p <<< 23) ||| (mantissaWord p-8388608) =
      FastMul.mkW sign (exponentWord s p) (mantissaWord p-8388608) := by
    rw [hsign, mkW_eq_unmasked sign _ _ hb.1 hb.2]
  calc
    normalCore s u v =
        FastMul.mkW sign (exponentWord s p) (mantissaWord p-8388608) :=
      hshape.trans hpack
    _ = FastMul.mkW sign (oldPosition p s-171).toUInt32 (FastMul.fracW (oldMantissa p)) := by
      rw [exponentWord_eq_old p s hp.1 hp.2 hs0 hs1, fractionWord_eq_old p hp.1 hp.2]
    _ = FastMul.roundP sign p (s.toUInt64-2) := by
      symm
      exact roundP_normal sign p s hp.1 hp.2 hs0 hs1
'''
rows = []
header = original[:original.index(' := by')]
public=(ROOT/'competitions/floatlib/candidates/f01-r23-dev-outline-public1/Kernel.lean').read_bytes()
assert hashlib.sha256(public).hexdigest()=='f90d42e346a1634ffeb537ea7e9980e0a91baea8499dc6c2235da5ab8fe0e85f'
assert public.decode().count(original)==1
for label, candidate in [('focused', focused), ('staged', staged)]:
    assert candidate[:candidate.index(' := by')] == header
    target = HERE/('normalCore-'+label+'.lean.inc')
    target.write_bytes(candidate.encode())
    patch = ''.join(difflib.unified_diff(original.splitlines(True), candidate.splitlines(True),
        fromfile='normalCore-current-159e.lean.inc', tofile=target.name))
    (HERE/('normalCore-'+label+'.patch')).write_bytes(patch.encode())
    projected=public.decode().replace(original,candidate,1).encode()
    assert len(projected)<=256000
    rows.append({'name':label, 'file':target.name, 'sha256':hashlib.sha256(target.read_bytes()).hexdigest(),
        'bytes':target.stat().st_size, 'theorem_statement_byte_identical':True,
        'typing':'NOT_RUN', 'axioms':'NOT_RUN', 'replay':'NOT_RUN',
        'conditional_public_projection':{'base_sha256':hashlib.sha256(public).hexdigest(),
            'sha256':hashlib.sha256(projected).hexdigest(),'bytes':len(projected),
            'cap_headroom':256000-len(projected),'materialized':False,
            'recipe':'Exactly one replacement of the original full normalCore_eq_roundP declaration by this same-header variant; no other public bytes change.'}})
(HERE/'conditional-transport-manifest.json').write_text(json.dumps({
    'state':'RESERVE_NOT_RUN_DO_NOT_INTEGRATE_BEFORE_EXACT_CI_FAILURE',
    'frozen_helper_unchanged':hashlib.sha256((HERE/'MathOutletR23Fix1.lean').read_bytes()).hexdigest(),
    'trigger':'Only if current full-public CI still times out in normalCore_eq_roundP',
    'order':'Try focused first; staged only if raw feedback continues to require localization.',
    'same_domain_constants_runtime_memory_gate':True, 'local_maxHeartbeats':1000000,
    'reason':'Focused removes unrestricted LHS rewrite search. Staged separates runtime definitional equality, bounded packing, old-shape transport and roundP. Cost explanation is INFERRED.',
    'variants':rows},indent=2)+'\n',encoding='utf-8')
print(json.dumps(rows))
