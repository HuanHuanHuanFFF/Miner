# R27 word proof — current

First clock19:48:05 UTC; common deadline00:44:43 unchanged. Strict files;
only this directory writable; no local Lean/native, Git or CI.

- First minimal request ready: unchanged R26 runtime3287B/2612bcae…;
  modular64 cut7805B/00c3ee19…; exact roots/hashes in `CI-REQUEST.json`.
  Original intake/policy AST passes; runtime now elaborated in40945451009
  with wrapper AX propext/Quot.sound. Modular64 remains NOT_COMPILED.
- Second mechanism `NatBlockCore.lean`4819B/3f77a75e…: UInt32 magnitudes
  widened multiply→two Nat sign buckets→Int only at finish. Exact core proof
  source removes carry/modular128 proof burden. Native cost remains UNKNOWN.
- Primary-source cost discriminator rejected Int-MAC: Lean4.34 small Int is
  INT_MAX. Nat multiply also has division overflow test; helper uses UInt64
  multiply instead. `route-decision.json` preserves evidence and limits.
- New27 interface audit in `PREDECESSOR-INTERFACES.md`: `Ybo/X7` is existing
  fast192-bit→official finishWord bridge; `YL16/I6` and four-lane scalar loops
  are already implemented. Bias-inclusive metadata and zero sentinel already
  exist. Next: self-written128→192 bridge and block-guard coverage; do not
  reconstruct old41KB bridge before small compile feedback.

No fullgate, native cost or champion result claimed. Existing R26 failures
preserved at their original paths; new output is standalone source research.

Caller/bias/size obligations are now explicit in `INTEGRATION-CONDITIONS.md`.
The 128-bit body bound does not bound bias; do not truncate arbitrary aligned
bias into a native128 terminal. `Predecessor27Endpoint.lean.inc` is an original
1600B-class interface extension, not a full candidate; literal appended27
exceeds256000B, while12 exposes the same interface with space.

20:11 next substantive bridge: `ReciprocalNatCore.lean` and
`CI-REQUEST-reciprocal.json` give the all-input Nat estimate/correction proof
for Dimpl fixed-denominator norm route. Reuse public27 `m64_v` (12 lacks it) to connect
actual multiply-high, then a short UInt64 no-wrap bridge. This is higher
priority than expanding old41KB block proof; NOT_COMPILED.

20:20发现D07已独立给完整13KB reciprocal + actualnorm接线；已做一次
数学/接口复核，见 `RECIPROCAL-REVIEW.md`。其Nat证明自动化尚待编译，
未发现数学反例。为避免重复排队，本方reciprocal请求降为诊断备选；
`ReciprocalDAdapter.lean.inc`可在其Nat前缀失败时接本方显式消去证明。
继续modular64反馈与原word接口，D07为集成主路。
