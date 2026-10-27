# Four exact frontend fixes for frozen public7e

`four-api-fixes.patch` changes only L4811/4823/5352/5355. Original7e1524c8… is unchanged; no complete replacement Kernel emitted, no runtime/guard change and no Lean run. Numeric owns integration with its other two fixes.

- Both Nat rewrites become `rw [Nat.shiftRight_eq', Nat.shiftRight_eq_div_pow] at hr`. Fixed Nat/Bitwise/Basic.lean109 gives `m.shiftRight n = m >>> n := rfl`; line125's division lemma has the notation form on its left. This first rewrites the exact method-form RHS shown in the real compiler goal, then applies the original division lemma.
- Both Boolean projections become `(Bool.and_eq_true_iff.mp hd).1` / `.2`. Fixed `src/Init/Data/Bool.lean:176` explicitly defines the Iff and proves it with `Iff.of_eq (and_eq_true x y)`. The original name is a proposition equality, not the Iff API required by `.mp`.

The Bool source was fetched at exact Lean293d5d0c and its Git blob d77738d5… independently verified; full original bytes and license are in `fixed-Bool.lean`. `receipt.json` binds both source signatures, raw7e, changed lines and the48B delta. The compiler output SHAa8acd200… was rechecked. Recompilation is required; no pass is claimed.

Direct `/root/r17_numeric_roundtrip` delivery was attempted but the tool reported no such live agent path; the live listing exposes only the R16 tree. Root received the exact changes immediately and can relay under the existing authorization. No numeric/D file was edited.
