# Structural helpers: measured-source ancestry, not new R26 execution

The retained R24 generated C is available at
`competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/ci-runs/40804860824/download-a29c9d41975b4c67b67aefb0158b1440/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-tail-cost1/runtime-cost/Submission.c`.
SHA-256 `763d12a687ac23ee252b4413b9ea33de7ea1afdabcdf39849834404c4b5636fe`, 756066 B.

`c-review/historical-tail-parser-check/report.json` and saved definition snippets
were extracted from those exact bytes with `inspect_native_c.py`.

- `R24ExactDotTiered.native64Loop`, definition line 17861, returns `uint32_t` and
  has one `uint64_t` accumulator parameter. Its continued-MAC path loads two raw
  immediate UInt32 array elements, does native UInt64 multiplication/shift/sign
  arithmetic, updates that accumulator and jumps to `_start`. No Float or UInt64
  boxing or constructor allocation occurs in that worker. The Int conversion and
  `round128` call are confined to the zero-remaining terminal branch.
- `R24ExactDotCost.nativeLoop`, definition line 13899, returns `uint32_t` and has
  four `uint64_t` accumulator parameters. Its continued paths update those scalar
  arguments and jump to `_start`. The selected definition contains no allocation,
  generic apply, Nat multiply, or limb-array update. Its generic Nat counter
  helpers have large-Nat slow paths; R26's ≤2^20 native guard keeps counters small.
- `R24PortableF64.sumRemaining`, definition line 23399, returns `double` and
  carries a `double` accumulator. The actual `attemptPrepared` worker calls this
  unboxed worker. Its separate `___boxed` wrapper is an ABI wrapper and is not the
  selected MAC body; counting wrappers in the whole C file would misdiagnose it.

Consequently R26 reuses already structural R24 helpers. The fresh mechanism is
their connection to the actual full twelve-kernel model entry, including the
original exact fallback and charged cache setup/drop. It is **not** evidence that
R26 newly removed boxing from the R24 word cost control. New R26 generated C/ASM,
full-model costs and all-input refinements remain separate checks.
