# Exact3d9 single-pass sum: independent static review

Reviewed [f01-r7-sum-singlepass-fused-proof1](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r7-sum-singlepass-fused-proof1/Kernel.lean), SHA-256 3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576,230650 bytes. Review began2026-10-22 23:47:15 UTC within a45-minute bound. Only this report and its JSON record were written; R/candidates/builders were read only. No Git, CI, upload, local Lean/toolchain installation, new finite tests or9200-model rerun was performed.

**No deterministic scope, name, type/interface, indexing or semantic bug was found statically.** The exact candidate's Lean elaboration, kernel replay, transitive axiom audit, complete current gate, codegen and performance are NOT_RUN/UNKNOWN. Original W12b proof success does not certify these new loops.

## Source identity

The entire3d9 source was independently reconstructed in memory from exact0e8 parent, original W02 prefix, selected W05/W12 proof blocks, the raw suffix block, renamed old sum/spec and the appended new sum block. It matches3d9 byte-for-byte. This confirms the builder's stated composition without executing either writing script.

Relative to preserved8ec, bytes outside the sum block are identical. Its natLoop, loop and run runtime declaration text is also identical. Proof1 changes only proofs: the wrapped low lemma, explicit UInt32 order/guard proofs and the actual decoder if_pos rewrite. The low lemma is the original successful W12b low_false_lt_inf body/declaration with only its name changed. Negative8ec is preserved; no actual8ec compile failure is claimed.

The actual static current4b7 policy/options pass on exact3d9. It is25350 bytes below the256000-byte limit. This source check is separate from typechecking and the official statement obligation. Other exported declaration source is preserved from0e8; that is not an inherited compile, checksum or timing result.

## Actual suffix interface and ordering

The real interface at4963 is:

```lean
suffixLoop {n : Nat} (x : Vector Binary32 n)
  (k : Nat) (acc : Binary32) : Binary32
```

Nat prefix passes k+1; machine prefix passes k.toNat+1. Both perform one exact Submission.add on the current original raw NaN before calling the suffix. Thus q at k is consumed once and the suffix starts strictly after it. There is no missing accumulator, USize/Nat argument mismatch or partial application visible in either call.

suffixLoop_eq requires Model.isQNaN of that complete raw accumulator. repair_quiet supplies this using actual R7W05.repairSumStep_isQNaN, with the native right-NaN propagation event. The suffix keeps the quiet invariant and implements R7W02.step: later raw signaling inputs replace it with their quieted complete word; all other inputs preserve it. It does not stop before inspecting later signaling words.

## Machine indices, reads and large dimensions

run selects the word loop only under n<USize.size. Its USize.ofNat count carries the exact count.toNat=n proof. k<count then gives k.toNat<n; x.size_toArray transports that bound to the array read. Packed10Index.stepNat proves that guarded k+1 has Nat value k.toNat+1; next_decreases closes the recursion measure. Since count.toNat<USize.size, this successor cannot wrap.

The fixed Lean4.34 definitions confirm that Array.uget reads xs[i.toNat], and Vector.get reads its underlying array at the Fin value. These definitions support the word/Nat proof's rfl leaves up to proof irrelevance; actual elaboration is still unrun. [Array.uget](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean#L160-L162), [Vector.get/uget](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean#L91-L96).

At n>=USize.size, run selects natLoop and avoids truncating the logical length. The raw suffix always uses Nat indices. At n=0 the guard immediately terminates without a read and imports actual native+0. At the last valid machine element, the suffix start is at most n, so its own Nat guard prevents an extra read. These are source/proof-boundary checks, not a constructed huge-array runtime test.

## Decoder reuse and complete input classes

The ordinary prefix retains the original low UInt32 condition followed by the original strict high condition. Only both-true uses R2W01b.tableProduct. table_eq uses the actual all-word R2W01c.convert_eq and the original convert if branch; it does not assume an unproved normal-band oracle.

- Magnitude0 makes UInt32(a-1) wrap to the maximal word, so the low condition is true. Existing tableProduct zero lemmas preserve both signed zero words; the low proof correctly treats zero as impossible in its false branch.
- A false low condition implies magnitude<Inf. This includes subnormal and low normal inputs; Float32.ofBits retains the original decoder fallback.
- A rejected strict high condition with magnitude=Inf keeps the signed infinity through Float32.ofBits. Input nonNaN bridges allow either infinity and allow a NaN result from invalid arithmetic.
- A rejected high condition unequal to Inf identifies an original raw NaN. Only this high cold branch adds the Inf-versus-NaN comparison and transitions to exact raw repair.

No native-accumulator nonNaN test is assumed. native_step_eq allows an arbitrary native Float32 accumulator, including canonical NaN produced by earlier opposite infinities or overflow followed by invalid arithmetic. Original right operands remain raw until their branch is selected.

## Canonical NaN followed by original qNaN/sNaN

The runtime correctly executes actual add on the first raw NaN; it does not blindly preserve the right payload. Three exact original W12b witnesses cover this boundary:

| Native accumulator | Original right word | Actual repaired raw result |
| --- | --- | --- |
| nonNaN +Inf | 0xffc01234 quiet | 0xffc01234 |
| canonical native NaN | 0xffc01234 quiet | 0x7fc00000 |
| canonical native NaN | 0xff800011 signaling | 0xffc00011 |

Once in raw quiet suffix mode, later qNaNs do not replace the selected accumulator; later sNaNs do. This matches the actual signaling-first chooseNaN2 priority. All-nonNaN original input may nevertheless create native canonical NaN; the prefix continues and final import is justified by unconditional W12 native-add closure. The generic Nat theorem's raw initial seed is explicitly ofFloat32 acc, not an arbitrary raw metadata-bearing seed. run specializes it to original+0.

## Original W12b evidence, limited to its original source

R7W12b.lean has SHA bf334ffab956b1bad2083f60cb6fca4c364ec0a6fa65c38fc7dae5182ec7d83a (194615 bytes). Increment415bc6b9c6af184f0746181ae577eae4f96611b07e12cb21818d37a9ea8eb0ca (18188 bytes) is its exact suffix. R7W12b-attempt1.json explicitly records exit0 and its saved source snapshot equals that full file.

Diagnostic snapshot f6c552b02ee55a7c094ab947311936e123040783bde799d0303b1d33c32e397b (230137 bytes) starts with the exact full source and has its own explicit exit0. No raw error diagnostic appears in either successful log. Its369 print commands yield369 distinct raw reports,13 with no axioms. The exact name set equals the required list; the parsed mapping equals the saved audit. Only propext, Classical.choice and Quot.sound occur. The table's three witnesses and the arbitrary-accumulator/nonNaN-right and exact NaN-metadata interfaces are present in those raw reports.

R7SinglePassSum does not occur in the original W12b full source. All nine new declarations remain uncompiled in this integration: low_reject_finite, raw_nonNaN_of_le, raw_nan_of_high_reject, table_eq, native_step_eq, repair_quiet, natLoop_eq, loop_eq and run_spec. Even the renamed low lemma requires the new namespace/context to elaborate. The copied namespace mappings and suffix composition also have no exact3d9 acceptance receipt. A public60f minimal mapping compile cannot certify these private new loops.

## Remaining discriminating checks

The source has its own FloatLib/Competition/BI opens inside R7SinglePassSum, and the final export block restores FloatLib/Competition after that namespace closes. All mapped dependencies precede use. No lost-open pattern, duplicate new export, unresolved forward reference or incompatible suffix signature was found.

The next decisive test is an unchanged official statement build of exact3d9. Preserve the first concrete target, especially the native_step_eq rewrite of the recursive seed, raw-NaN suffix quietness leaf, word-loop rfl after uget/get conversion, termination helper application and final Fin.foldl/List.finRange sumSpec conversion. These are unrun elaboration surfaces, not claimed known errors.

After statement acceptance, this exact source still needs replay, axioms, complete gate/checksums, actual statement C/object inspection, paired whole-suite timing and frozen independent confirmation. Manifest operation counts, prior9200 traces and proposed branch reductions were not revalidated or converted to time shares. Gain remains UNKNOWN; this route replaces the previous sum prefix mechanism, so their gains must not be added.
