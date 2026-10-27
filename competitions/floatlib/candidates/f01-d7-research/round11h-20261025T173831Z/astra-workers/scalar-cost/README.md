# R17 scalar cost review and C extractor

Current reviewed mechanism is **B**, exact UInt64 product → Float32 → UInt64, runtime `cd301ba4…` in `Runtime-u64-mul-integer-v3-lf.lean.inc`. The v1 runtime and old cost-contract paragraph describe **A**, two UInt32 casts plus a Float32 multiply. They are historical controls and were not edited.

Run this when D has a new **runtime-containing** diagnostic archive:

```powershell
python "D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/astra-workers/scalar-cost/audit_u64_roundtrip_c.py" --diag "<nested diagnostics/candidate directory>" --input "<archived inputs/candidate/Kernel.lean>" --expected-sha "<exact Kernel SHA256>" --operation mul --focus-pattern "R17NumericMulInteger" --out "<new authorized output directory>"
```

The output folder must be new, preventing timestamp refreshes from replacing previous receipts. It contains `audit.json` and exact extracted function bodies. The parser verifies the archived input and every generated C hash against `candidate-c-index.json`, derives the actual `Bench.Suite.run` closure argument and unboxed callback, and labels separately any matching diagnostic/helper functions. `--operation mul` uses the fixed `Bench.Suite.run(add,mul,sum,bmm)` signature. It never assumes a lambda number or substitutes the outer8eb carrier.

For each numeric reverse-cast site, the report traces a direct forward expression and, when recognizable, the masked integer multiply's bounds. These are conservative **semantic source bounds**, not Clang range-analysis results. Missing/merged operands stay UNKNOWN. Full-function primitive counts include alternative fallback branches; they are not dynamic counts. Generated `lean_uint64_to_float32`/`lean_float32_to_uint64` call syntax denotes fixed `static inline` primitives, not automatically external calls. The report lists generated callee reachability, which may include cold paths. If an important generated callee is not extracted by the focus pattern, rerun against a new output folder with a precise pattern for that callee; do not infer that a forwarded call contains no roundtrip.

When matching symbols exist in `native-assembly-index.json`, hashes are verified and conversion/call/constant hints are returned. Missing scalar symbols, missing constant-pool values or absent hint strings do **not** prove clamp/2^63 handling was eliminated. Actual accepted-path ASM/IR and relocations must decide that. The original capture scope is retained; statement-object evidence is not relabeled as the timed ELF.

The current9f9a B2-prefix probe contains only mathematical helpers and no new runtime entry. Its MainFull MUL remains B2. Finding no numerical roundtrip there is expected and is not a negative code-generation result. A diagnostic entry also does not establish that the official public callback executes B. The old c972 archive was used once as a binding/selection control (`audit-old-c972-v1/audit.json`): it correctly resolves the actual MUL callback and reports no U64 reverse chain. It is not a new timing run.

`--self-test` checks a synthetic masked-product chain, an opaque operand remaining UNKNOWN, a nonstandard closure name, and missing-selection handling. No C is compiled or executed. One independent cost review is in `review.md`; its exact source bindings are in `source-review.json`. No candidate, proof, official file, Git or CI changes are made by this tool.
