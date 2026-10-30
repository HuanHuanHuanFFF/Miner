# Accepted reusable reciprocal component, negative model screen

`ReciprocalUInt64ContractOnly-v4.lean` is12500B, SHA013a5fd2e87c4da32bf791529564b587d67f8a94d096fe9f058826f2a8873dda. Public run40967910604 accepted the complete helper file with exit0 on the pinned4.34.0/ContractExact environment. The original helper log has SHA36517f2fb66bab0a0059c787496bfb816769e64951b8b9b15739a643cee4959f.

The printed roots are:

- `R27ReciprocalProof.reciprocal_estimate_bounds`: forB>0, a<B and d>0 in Nat, with R=floor((B-1)/d), q=floor(a*R/B), q*d<=a<(q+2)*d. AX propext,Quot.sound.
- `R27ReciprocalProof.reciprocal_divrem`: one correction produces exact Nat quotient/remainder under those premises. Same AX.
- `R27Reciprocal.mulHigh_toNat`: the portable four32-bit-partial UInt64 multiply returns the exact product high64 bits. AX additionallyClassical.choice.
- `R27Reciprocal.divRem_correct`: for arbitrary UInt64a,d, cachedprepare(d) yields exactly the original pair(a/d,a%d); the d=0 branch delegates the original operations. Same allowed AX as the word multiply root.

This acceptance belongs to the exact standalone helper file and original log. It does not accept the new full kernel, a compact spelling of the helper, different imports, a runtime replacement, or a source23m64 bridge. The helper's import boundary remains ContractExact; independent minimal-library portability has not been tested.

The actual255415B/c688f107 whole normalizedMLP experiment completed360 pairs/720 timing values with matching checksums. Its inferred time/current43 was1.1297896864, insufficient. The fully integrated253499B/9654b727 source failed the statement stage because compact helper application spacing broke parsing; the resulting missing theorem and q/r rewrite errors are preserved. A separate archive-only spelling repair21bbffda was prepared without a new queue or acceptance claim. No gain or future performance conclusion follows from the accepted proof component.

Canonical receipts: `../../CI-RESULTS-BATCH6.json`, `batch6-native-result.json`. Raw original helper and full-gate logs remain under the parent evidence40967910604 directory. The native performance route is stopped; the exact mathematical component is retained for later justified use.
