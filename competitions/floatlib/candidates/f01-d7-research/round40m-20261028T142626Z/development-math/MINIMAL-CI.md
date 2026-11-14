# Minimal CI attachment

Only the Git/CI owner attaches and dispatches. This document does not claim execution.

1. Keep retained B2 `Submission` at SHA `622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58` as imported base. Bind exact `MathOutletR23Fix1.lean` from `manifest.json`; component SHA `159e0633eee16fa1b054d2b0adcb0a99b0a5fc7dfe96e776097de6d9f4e467e9` / 37874B.
2. Reuse the existing public diagnostic setup and original `g.own`/`build='read'` 4096MiB process cap. Copy exact bytes to `g.WORK.parent/'R23MathOutletFix1.lean'`; invoke `[g.LAKE,'env','lean','work/R23MathOutletFix1.lean']` with ordinary bounded timeout (prior full Math typed errors in 22.86s; allow 90s). Preserve raw UTF-8 output and elapsed/status. Do not restore a failed AX report as acceptance.
3. On exit zero only, use unchanged `parse_reports(output, roots48, g.AXIOMS)` from `round9h-20261026T194639Z/development-helper-audit-v8.py` (SHA `5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975`). Require exactly the 48 ordered names in `roots48.json`, each only `propext`, `Classical.choice`, `Quot.sound`. All 51 theorem headers remain original; private lemma dependencies are included transitively by each reported root.
4. Typing plus AX remains helper-level evidence. For independent replay, compile exact helper as a new module using the existing pinned toolchain, then apply the established leanchecker replay to that module and a separate importing verification module; preserve exact source/module hashes and original commands. No full-public, cap, runtime/checksum, timing or formal-submission acceptance follows from helper success.

No Nat prefix or mathematical domain/runtime/guard changes are required in this attachment. Keep all official gate/bench/contract/resource settings unchanged. If a typed goal remains, return its exact raw goal and source SHA; fix only that source in a new version.
