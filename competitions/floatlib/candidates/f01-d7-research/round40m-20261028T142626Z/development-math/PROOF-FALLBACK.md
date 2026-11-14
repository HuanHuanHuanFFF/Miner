# Conditional proof bottleneck reserve — no new source or CI

Current frozen helper is still `159e0633...` / 37874B. Do not replace it unless fixed CI returns a remaining failure.

The old 406219 timeout names `normalCore_eq_roundP` at declaration line 699 and `whnf`; it does **not** identify the failing tactic. The local 1M heartbeat is the current tested-next change, and its sufficiency is UNKNOWN.

If this exact declaration still times out, the smallest distinct source experiment is to focus its first rewrite on the right side:

```lean
  conv_rhs => rw [roundP_normal sign p s hp.1 hp.2 hs0 hs1]
```

This replaces only `rw [roundP_normal ...]`, leaving the theorem's complete original domain, conclusion, later `change`, bounds and transport proofs unchanged. Rationale is INFERRED: unrestricted rewrite can attempt reducible matching against the large left-side `normalCore`, while the targeted right side already has `FastMul.roundP` at its head. The declaration-location timeout alone does not prove this is the expensive operation. The analogous `conv_lhs => rw [hcache]` syntax exists in the 406219 typed indexed8 source; this new focused rewrite itself is NOT_RUN.

If the timeout persists after that focused rewrite, avoid attributing it to rewriting; the next discriminating probe is to isolate the explicit runtime-shape equality from the final `mkW`/old-position transport (same theorem and process cap). A successful focused rewrite is a helper resource result only; no runtime speed or full-public acceptance follows.

Do not spend another independent review or CI on this reserve if `159e0633...` succeeds. Keep the current fixed verifier and react to exact raw failures.

The source-only builder also projects each exact single-declaration replacement into frozen public f90d without writing another public file. Focused: SHA `668a911161c6408f450baf3b98d979a1d36cd8ac7bb355d9c9ec1f43141299de`,253990B,2010B headroom. Staged: SHA `7ece2315467b9f26ca2f4e8317e8bc8e3b46989ca020172e825634d14589a317`,254435B,1565B headroom. These are **NOT_MATERIALIZED / NOT_RUN** conditional identities, not proposed replacements before feedback; recipes and exact fragment hashes are in `conditional-transport-manifest.json`.
