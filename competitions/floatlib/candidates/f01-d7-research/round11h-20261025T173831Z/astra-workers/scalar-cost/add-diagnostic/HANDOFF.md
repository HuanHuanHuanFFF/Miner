# Frozen e085 ADD runtime: optional same-batch lowering probe

**Source ready for D's throughput decision; NOT_COMPILED, not a timed/public ADD candidate.**

- `Probe-b2-add-u32-lowering-v1.lean`: **228712B**, SHA **3d35d67eb74f03b6c97d341f2fe40220dbccfc71eed8af4d1d0b413d31594776**. Exact B2 `622d`226829B prefix +LF+ frozen1699B runtime **e08543ac5c20cd53c39b010edfc684226032926418ea3125df8aa4a3805f799e** +LF+182B ordinary caller. All original public implementations/specs remain unchanged.
- Caller is `Submission.R17NumericAdd.diagnosticEntry`, calling `guardedAdd Submission.add x y`. The fallback is only original B2 ADD. Runtime references `R2W01b.mantissa`, `FastMul.mkW`, `R7W02.fromRaw` and fixed expField/conversions already available under B2's sole ContractTensor import. No missing c972-specific name or extra proof API was introduced. Actual elaboration remains to be checked.
- Exactly **3 new roots**, enumerated from the two appended files: `Submission.R17NumericAdd.sortedAdd`, `.guardedAdd`, `.diagnosticEntry`. Full names and source lines are in `manifest.json`. `HelperAudit.lean.inc` is a separate explicit audit input; do not append its print commands to Kernel. Auditing these data definitions does not prove the new ADD's equivalence.
- Original fixed gate intake/policy/options **PASS**, including comments; size and single-import checks passed. Original e085 bytes preserved, local canonical LF, UTF-8/no BOM, `read_bytes == read_text.encode` verified. D still owns publication-byte preflight, actual compile/replay and scheduling. No new attributes were added; the runtime's two inline annotations are its frozen originals.

If D can include one statement/codegen probe in an already justified batch, capture nested candidate C and exact object disassembly/relocations/constants for the unboxed **diagnosticEntry** and **sortedAdd** (plus any retained generated callee). Discover actual symbols from C instead of assuming lambda indices. The public MainFull ADD is intentionally still B2. This checks the ordinary diagnostic caller's lowering only; no second full timing queue is requested.

Questions for that actual C/ASM:

1. Does the accepted path have one forward UInt32 cast and one numeric reverse conversion, and does the reverse lower to one `cvtt`? Which0/2^32 clamp work survives? A single C primitive site does not prove a single instruction.
2. Are there external bits/conversion calls, reachable Nat/heap/closure operations, or only ordinary scalar arithmetic? Ignore unrelated boxed wrappers and reject-path fallback sites when answering for the fast arm.
3. Are the two raw exponent fields and the one sort reused in the concrete caller? Are magnitude, threshold/shift and sign calculated once on an accepted path, including after the numeric conversion? Count path work, not alternative inlined copies.
4. What P/N/R live values, stack saves or actual spills remain? Distinguish the function's shared prologue from spills introduced by a conversion call.

The existing `audit_u64_roundtrip_c.py` can still bind/extract this archive with `--operation add --focus-pattern R17NumericAdd --input <exact archived input> --expected-sha 3d35d67eb74f03b6c97d341f2fe40220dbccfc71eed8af4d1d0b413d31594776 --diag <nested candidate diagnostics> --out <new authorized folder>`. Its numeric-chain recognizer is deliberately U64-focused: zero recognized chains here is **not** a UInt32 failure or proof of no roundtrip. Use the extracted primitive sites/body and matching ASM for the four questions. The prior MUL876 review/tool is unchanged.

No CI/Git/local Lean, source tuning or numerical model rerun occurred. No lowering or speed result is predicted. `manifest.json` and `build_add_diagnostic.py` preserve exact construction and roots; stop if the source hash changes rather than reusing this receipt for a different input.
