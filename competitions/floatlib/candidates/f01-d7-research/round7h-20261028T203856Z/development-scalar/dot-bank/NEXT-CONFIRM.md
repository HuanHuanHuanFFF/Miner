# Next generic whole-bank confirmation — plan only

UTC2026-10-29; runtime frozen at03:15. No new confirmation inputs, seeds,
Lean/native build or CI are created by this plan. All six banks below are
already seen exploratory evidence. They cannot be relabeled unseen confirmation.

## What the frozen corpus actually exercises

Fixture SHA256 `986eaf0dd77ec19d6f64bed9a1f653da6004f28c3d4968fd31358c98e421d7f1`.
Replayed against the unchanged finite Python FP model, not an instrumented native
acceptance counter. The native464×3 output check is a separate evidence layer.

| Seed / inner | Rows × columns | Outputs | Model accept / reject | Exact zero / nonzero-product cancellation | Active product scale span≥64 |
| --- | --- | --- | --- | --- | --- |
| 24282601 / 32 | 4 × 8 | 32 | 19 / 13 | 12 / 1 | 8 |
| 24282601 / 64 | 6 × 12 | 72 | 53 / 19 | 18 / 1 | 14 |
| 24282601 / 128 | 8 × 16 | 128 | 100 / 28 | 24 / 1 | 20 |
| 24282603 / 32 | 4 × 8 | 32 | 19 / 13 | 12 / 1 | 8 |
| 24282603 / 64 | 6 × 12 | 72 | 52 / 20 | 18 / 1 | 14 |
| 24282603 / 128 | 8 × 16 | 128 | 103 / 25 | 24 / 1 | 20 |

Total464 outputs /44032 MAC /9216 stored input words; model346 accept/118 reject.
108 exact-zero outputs include102 all-zero-product dots and6 cancellation dots;
12 outputs are negative zero,96 positive zero. All356 other outputs are normal.
There are no exact RNE midpoint outputs, subnormal outputs or nonfinite outputs.
84 dots have actual active product scale span≥64. These classifications overlap;
their counts must not be added as disjoint strata.

There are36 A-row occurrences (30 raw-value-unique) and72 B-row occurrences
(63 unique); combined108 occurrences have90 distinct raw rows. The implementation
prepares all108 occurrences and performs no content deduplication. The three
shapes reuse each A row8/12/16 times and each B row4/6/8 times. Primary row
preparation calls are12/18/24 instead of64/144/256 for cold per-dot preparation,
ratios3/16,1/8,3/32 respectively. This is actual caller reuse and also a source
of synthetic-workload advantage; it is not a universal production reuse rate.
Eager builds both cache types per occurrence. Lazy additionally builds236 exact
fallback rows in the finite model, so its total cache work is not O(rows+cols).
The integer reference selects114 word64,260 word128 and90 replay outputs in the
model. Preparation counts are operations, not measured time fractions.

## Coverage limits and next decisions

Random nonzero exponent fields concentrate in116..138; constructed rows add80,
127 and180 plus signed zeros. No nonzero input subnormal, NaN, infinity,
maximum-finite product, rounded overflow/underflow, minimum-normal boundary or
exact midpoint is present. No inner length exceeds128. Empty/ragged/mismatched
rows, one-row/column shapes, large output allocation or cache pressure, layout,
stride, alias reuse and concurrency are absent. Results are for this generic
all-pairs caller and its own integer reference. They establish no official BMM,
new-target kernel, current champion comparison, formal adoption or rank.

1. Keep Kernel b285, fixture bytes and all current slow cases/results frozen.
   Cost2 only repairs Python driver API and is independently checked against
   cost1 for exact C/ASM bytes in `review-native-bank/cost2-same-body.json`.
   Retain all16 processes,144 raw nanosecond values, failures and CPU/flags;
   no case exclusion based on misses or observed speed.
2. Close primitive proof prerequisites before describing semantic adoption:
   exact finite/subnormal widening, ordered structural fold/error enclosure,
   actual endpoint/midpoint/order-key certificate, optimized64/128 reference
   refinement and bank row-cache/row-major refinement. The currently measured
   generic program is not replaced by a cheaper abstract callback in these proofs.
3. After the user selects a target, establish that target's exact reduction,
   zero/nonfinite policy, shape/layout and complete operation boundary from its
   pinned contract. Preserve current generic benchmark as a separate experiment.
   Unknown target workload or source license is not filled by the synthetic bank.
4. If parent authorizes another engineering confirmation, freeze ONE selected
   eager backend, integer control, caller, audit, parser, compiler flags and
   acceptance rule before producing any new inputs. Proposed diagnostic criterion:
   pooled paired whole-call ratio≤0.90 with positive one-sided bootstrap gain p05,
   plus publish all per-case regressions. This is a proposed engineering decision
   rule, not the official competition gate; official gates stay unchanged.
5. Predeclare independent unseen seed groups and a small shape/domain matrix,
   then generate the new fixture file once. Do not choose or reveal seeds now.
   Shape families should include1×1,1×many,many×1, the current rectangular reuse
   family and inner1024/2048 with a capped total MAC budget. Domain strata should
   include cancellation and signed zero, exact midpoint, near minimum-normal,
   nonzero subnormal, extreme finite and opposing separable/paired scale maxima.
   Invalid/nonfinite/ragged semantics need verification-only tests under the
   explicitly chosen policy, not an invented official-payload oracle.
6. Use independent fresh public runner allocation and balanced fixed ABBA
   ordering with same-source controls, retaining three raw timing samples per
   process and all process/trial identifiers. Same selected whole-call boundary:
   raw banks in; every operand-cache preparation, output allocation, full output
   traversal and releases inside timing. No free paired scan/cache preparation.
   Warm/witness runs and lifecycle wall remain recorded separately.
7. First verify all new output words against exact integer/dyadic sum rounding,
   and compare actual attempts with the model in a diagnostic pass. Keep model
   hit counts separate from uninstrumented cost runs. Re-run the fixed selected
   C/ASM audit: concrete two-argument bank+external barrier in backedge, row prep
   before pair loops, identical result variable fed to full element observer and
   released before backedge, native FP worker still double argument/result.
8. Only then collect the frozen statistical comparison. Any source fix or chosen
   next candidate gets its own new confirmation inputs and allocation. Preserve
   failed/slow samples and report UNKNOWN for any missing claim. Formal target
   gate/adoption and formal upload remain separate from engineering confirmation.
