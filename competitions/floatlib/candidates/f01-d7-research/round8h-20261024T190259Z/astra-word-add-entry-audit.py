"""Independently reconstruct the frozen public add entry; read-only sources."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import re
import json

start=monotonic();base=Path(__file__).resolve().parent;root=base.parents[4]
cdir=root/'competitions/floatlib/candidates/f01-r14-dev-word-add-entry1'
manifest=json.loads((cdir/'manifest.json').read_bytes());parts=[]
for item in manifest['components']:
    b=(root/item['path']).read_bytes()
    assert len(b)==item['bytes'] and sha256(b).hexdigest()==item['sha256']
    parts.append(b)
parent=(root/manifest['slim_parent']['path']).read_bytes()
assert sha256(parent).hexdigest()==manifest['slim_parent']['sha256']
text=parent.decode('utf-8')
first=text.index('@[inline] def add (x y : Binary32) : Binary32 :=\n  let result :=')
last=text.index('@[inline] def nativeMul ',first)
old=text[first:last]
fallback=re.sub(r'(?m)^(@\[inline\] def )add\b',r'\1addBeforeWord',old)
fallback=re.sub(r'(?m)^theorem add_spec\b','theorem addBeforeWord_spec',fallback)
fallback=fallback.replace(', add x y = ExecFloat.Spec.add x y',', addBeforeWord x y = ExecFloat.Spec.add x y')
fallback=re.sub(r'(?m)^  unfold add$','  unfold addBeforeWord',fallback)
wrapper='''
namespace Submission
open FloatLib.Floats Competition

@[inline] def add (x y : Binary32) : Binary32 :=
  R14WordAdd.guardedAdd addBeforeWord x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  exact R14WordAdd.guardedAdd_spec addBeforeWord addBeforeWord_spec x y

'''
expected=(text[:first]+fallback+'\nend Submission\n').encode()+b'\n'.join(parts)+wrapper.encode()+text[last:].encode()
actual=(cdir/'Kernel.lean').read_bytes()
assert actual==expected
assert sha256(actual).hexdigest()==manifest['candidate_sha256']
assert len(actual)==manifest['candidate_bytes']<=256000

original=(base/'astra-word-add-raw-model1.lean').read_bytes()
begin=original.index(b'theorem raw_add_sorted_conditions ')
end=original.index(b'theorem raw_add_model ',begin)
removed=original[begin:end]
raw=original[:begin]+original[end:]
raw=raw.replace(b'raw_add_sorted_conditions',b'sorted_domain').replace(b'raw_add_gap_nat',b'gap_pair')
assert raw==(base/'development-word-add-raw-model-integration1.lean').read_bytes()
assert sha256(removed).hexdigest()==manifest['raw_model_derivation']['removed_duplicate_sha256']
def main_statement(b):
    return b.split(b'theorem raw_add_model ',1)[1].split(b' := by',1)[0]
assert main_statement(original)==main_statement(raw)

fields=(base/'development-word-add-fields1.lean').read_bytes()
fields2=fields.replace('    R2W01c.wordExp (low u v) ≤ R2W01c.wordExp (high u v) ∧\n'.encode(),b'')
fields2=fields2.replace('  refine ⟨hehi, helo, ?_, hc.2.2.1, ?_⟩\n  · rw [hs.1, hs.2]\n    omega\n'.encode(),
                        '  refine ⟨hehi, helo, hc.2.2.1, ?_⟩\n'.encode())
fields2=fields2.replace(b'hs.2.2.2.1',b'hs.2.2.1').replace(b'hs.2.2.2.2',b'hs.2.2.2')
assert fields2==(base/'development-word-add-fields2.lean').read_bytes()
spec=(base/'development-word-add-spec1.lean').read_bytes()
assert spec.replace(b'R2W01c.rawModel_eq_ofUInt32',b'R2W01c.rawModel_eq_native32')==(base/'development-word-add-spec2.lean').read_bytes()
assert actual.count(b'import ContractTensor')==1
assert b'R14ExponentShift.guardedMul' not in actual
assert actual.index(b'theorem raw_add_model ')<actual.index(b'theorem core_model ')<actual.index(b'R14WordAdd.guardedAdd addBeforeWord x y')<actual.index(b'theorem add_eq :')
assert actual.endswith(text[last:].encode())
assert b'else fallback x y' in parts[2]
assert 'if e - 1 ≤ (253 : UInt32) then'.encode() in parts[2]
assert not re.search(rb'(?m)^\s*(axiom|constant|unsafe|partial)\b',b'\n'.join(parts))

receipt=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='FROZEN_ENTRY_BYTE_COMPOSITION_VERIFIED_NOT_COMPILED',elapsed_seconds=monotonic()-start,
    candidate=manifest['candidate'],sha256=manifest['candidate_sha256'],bytes=len(actual),remaining_bytes=256000-len(actual),
    all_manifest_components_match=True,full_source_reconstructed=True,
    raw_model=dict(original_sha256=sha256(original).hexdigest(),integrated_sha256=sha256(raw).hexdigest(),
        public_theorem_statement_unchanged=True,removed_only_duplicate_helpers_bytes=len(removed),
        replacements=manifest['raw_model_derivation']['replacements']),
    field_revision='Only unneeded derived order conjunct and proof removed; corresponding projections adjusted. Root raw bridge derives order separately.',
    actual_public_entry='R14WordAdd.guardedAdd addBeforeWord x y',
    original_ordered_fallback=True,suffix_unchanged_from_slim_parent=True,
    scope='MUL/SUM source definitions retained from slim parent. Existing thin-cache/p8 BMM is itself new, and raw replay/reference callers may see the new public add. No acceptance or performance inheritance.',
    cost_questions=['Actual optimized caller C/assembly', 'Elimination of higher-order fallback wrapper overhead',
                    'Guard/branch and UInt64 boxing cost', 'Whole-operation paired timing including BMM routes'],
    remaining='Lean elaboration, axiom replay, original full gate, actual timed caller, frozen independent confirmations all NOT_RUN on this exact source.',
    authority='No source/index/push/CI mutation; D remains coordinator.')
Path(__file__).with_suffix('.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False,indent=2))
