import ContractExact

/- Independent post-freeze follow-on, using only pre-freeze source/API evidence.
No candidate kernel, extra trusted declaration or new CI request. -/
namespace Submission.R24PortableF64

-- Exact scalar recurrence from the owned R26/R27 runtime.
def sumRemaining (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat) : Float :=
  match remaining with
  | 0 => acc
  | rest + 1 =>
    sumRemaining a b (index + 1) (acc + a.get! index * b.get! index) rest

end Submission.R24PortableF64

namespace Submission.R27CheckedGetter
open Submission.R24PortableF64

/-- Existing safe get and get! agree when the existing API's bound holds. -/
theorem getBang_eq_get (a : FloatArray) (i : Nat) (h : i < a.size) :
    a.get! i = a.get i h := by
  cases a with
  | mk ds => exact getElem!_pos ds i h

/-- Proof arguments erase; each native load uses FloatArray.get, preserving
exactly the original multiply/add order and original Float operands. -/
def checked (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat)
    (ha : index + remaining ≤ a.size) (hb : index + remaining ≤ b.size) : Float :=
  match remaining with
  | 0 => acc
  | rest + 1 =>
    checked a b (index + 1)
      (acc + a.get index (by omega) * b.get index (by omega)) rest
      (by omega) (by omega)

theorem checked_eq_original (a b : FloatArray) (remaining : Nat) :
    ∀ index acc (ha : index + remaining ≤ a.size) (hb : index + remaining ≤ b.size),
      checked a b index acc remaining ha hb = sumRemaining a b index acc remaining := by
  induction remaining with
  | zero => intro index acc ha hb; rfl
  | succ rest ih =>
    intro index acc ha hb
    have hia : index < a.size := by omega
    have hib : index < b.size := by omega
    rw [checked, sumRemaining, getBang_eq_get a index hia, getBang_eq_get b index hib]
    exact ih (index + 1) (acc + a.get index hia * b.get index hib) (by omega) (by omega)

/-- All arrays remain in the domain. Failed bounds retain the old get! behavior. -/
def dispatch (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat) : Float :=
  if h : index + remaining ≤ a.size ∧ index + remaining ≤ b.size then
    checked a b index acc remaining h.1 h.2
  else
    sumRemaining a b index acc remaining

/-- Scalar equivalence needs no finiteness, size cap, prepared-cache origin,
floating-point algebra law or changed numerical error theorem. -/
theorem dispatch_eq_original (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat) :
    dispatch a b index acc remaining = sumRemaining a b index acc remaining := by
  unfold dispatch
  split
  · exact checked_eq_original a b remaining index acc _ _
  · rfl

end Submission.R27CheckedGetter
