# R22 B: Pair8 checked-read interface

Start **22:53:15 UTC**, bound **23:08:15 UTC**, shared deadline unchanged. cd0e runtime/0ec candidate remain frozen; A owns2850 cache values. No candidate, runtime guard, library change, local Lean or CI.

Artifacts were ready by **23:06:02 UTC**, **12m47s** elapsed, and handed to the coordinator. B remains online for the shared window; this bounded interface check is complete, not a new Lean acceptance.

- `CheckedRead.lean.inc`: **1418 B / 4 roots / NOT_RUN**, exact hash in manifest. Gives span→index bound, checked=getD, `mapFinIdx` checked inner advance=old `mapIdx/getD`, and packB batch-span from existing `packB_size`. No A pack-value reproof.
- Important API: mapFinIdx callback is **Nat index → element → erased i<size proof**, not Fin index. Existing safe backend and `mapFinIdx_eq_mapIdx` suffice. Carry baseC+n*G≤cache.size and old k<n as erased Prop arguments; no new runtime `if`.
- Actual0ec selected map **still has the check**: owned Main callback is directlyR22Pair8.guarded; C path to the loop/map is bound in `selected-read-receipt.json`. ASM110cmp /113jae200 /203zeroPair, not merely an isolated helper. Source-bound statement object scope is explicit; no new checked-read machine result or timing claim.
- `INTERFACE.md` explains exact integration and limits. This may delete the default/range branch, not Nat address arithmetic or all RC/COW. Actual new C must confirm deletion and full-call cost; old branch predictability is unknown. D decides the next experiment; no reseed request.
