"""Select checked R14 mathematical components for a single high-N native ADD route.
Only the new copies are generalized from opposite gap>=2 to gap>=1; no original edited.
This script does not invoke Lean or claim that modified proofs compile.
"""
from pathlib import Path
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
OLD=ROOT/'competitions/floatlib/candidates/f01-r14-dev-word-add-entry2/Kernel.lean'
s=OLD.read_text(encoding='utf-8')
assert hashlib.sha256(OLD.read_bytes()).hexdigest()=='f958071e037ea5627a34d41b296d07cc97fd13eec41117de7c9b184bf0fad653'
def ns(name):
 a=s.index('namespace '+name+'\n');b=s.index('end '+name,a)+len('end '+name)
 return s[a:b]+'\n'
def cut(a,b):
 i=s.index(a);return s[i:s.index(b,i)].rstrip()+'\n'
def rename(t):
 return t.replace('R14WordAddAlignment','R16AddAlignment').replace('R14WordAdd','R16AddWord')
def gapone(t):return t.replace('2 ≤','1 ≤').replace('(2 : UInt32) ≤','(1 : UInt32) ≤')

pieces=[ns('Submission.R14ExponentShift'),ns('Submission.R14NatNormal'),ns('Submission.R14WordAddRounding')]
runtime=cut('@[inline] def high (u v : UInt32)', '@[inline] def leadingWord')
runtime=gapone(rename(runtime))
fields=gapone(rename(cut('theorem normal_field (u : UInt32)', 'end Submission.R14WordAdd\n\n/- Draft / NOT_RUN. Exact dyadic')))
pieces.append('namespace Submission.R16AddWord\nopen FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange\n'+runtime+fields+'end Submission.R16AddWord\n')
alignment=gapone(rename(ns('Submission.R14WordAddAlignment')))
alignment=alignment.replace('have hp : 4 ≤ 2 ^ gap','have hp : 2 ≤ 2 ^ gap').replace('2 ^ 2 ≤ 2 ^ gap','2 ^ 1 ≤ 2 ^ gap')
pieces.append(alignment)
pieces.append('''namespace Submission.R16AddAlignment
theorem magnitude_bounds (sh sl : Bool) (hi lo d : Nat)
    (hhi : 8388608 ≤ hi) (hhi' : hi < 16777216)
    (hlo : 8388608 ≤ lo) (hlo' : lo < 16777216)
    (hd : d ≤ 7) (hdom : sh = sl ∨ 1 ≤ d) :
    1 ≤ magnitude sh sl hi lo d ∧ magnitude sh sl hi lo d ≤ 2164260735 := by
  by_cases hs : sh = sl
  · interval_cases d <;> simp only [magnitude, if_pos hs, Nat.shiftLeft_eq', Nat.shiftLeft_eq] <;> norm_num <;> omega
  · have hg : 1 ≤ d := hdom.resolve_left hs
    interval_cases d <;> simp only [magnitude, if_neg hs, Nat.shiftLeft_eq', Nat.shiftLeft_eq] <;> norm_num <;> omega
end Submission.R16AddAlignment
''')
support='namespace Submission.R16AddWord\nopen FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange\nopen FloatLib.Numerics\n'
support+=rename(cut('abbrev magnitudeNat (u v : UInt32)', 'abbrev baseNat'))
support+=gapone(rename(cut('theorem gap_pair (u v : UInt32)', 'theorem magnitudeNat_bounds')))
support+='''theorem magnitudeNat_bounds (u v : UInt32) (hd : eligible u v = true) :
    1 ≤ magnitudeNat u v ∧ magnitudeNat u v ≤ 2164260735 := by
  have hh := R2W01c.mantissa_bounds (high u v)
  have hl := R2W01c.mantissa_bounds (low u v)
  have hs := sorted_domain u v hd
  exact R16AddAlignment.magnitude_bounds _ _ _ _ _ hh.1 hh.2 hl.1 hl.2 hs.2.2.1 hs.2.2.2
'''
support+=gapone(rename(cut('theorem left_word_nat (u v : UInt32)', 'theorem base_word_nat')))
raw=cut('theorem raw_add_model (u v : UInt32)', '  have hb := R14WordAddAlignment.magnitude_bounds')
raw=raw[raw.index('  have hc :='):]
support+='''theorem raw_add_dyadic (u v : UInt32) (hd : eligible u v = true) :
    Model.add (R2W01c.rawModel u) (R2W01c.rawModel v) =
      Model.roundDyadic FloatFormat.binary32
        ⟨R2W01c.wordSign (high u v), magnitudeNat u v,
          (R2W01c.wordExp (low u v) : Int) - 150⟩ := by
'''+gapone(rename(raw))+'''
  rw [Model.Proof.add_eq_spec]
  rw [R16AddAlignment.spec_add_of_decodes _ _ _ _
    (R14NatNormal.raw_normal_decode u hc.1.1 hc.1.2)
    (R14NatNormal.raw_normal_decode v hc.2.1.1 hc.2.1.2), hsum]
end Submission.R16AddWord
'''
pieces.append(support)
out='\n\n'.join(pieces)
(HERE/'Add-native-high-support.lean').write_text(out,encoding='utf-8')
print(json.dumps({'bytes':len(out.encode()),'sha256':hashlib.sha256(out.encode()).hexdigest(),'state':'SOURCE_DRAFT_NOT_COMPILED'}))
