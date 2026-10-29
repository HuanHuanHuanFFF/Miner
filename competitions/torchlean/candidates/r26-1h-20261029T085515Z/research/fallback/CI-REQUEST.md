# Optional D CI slot request — R26 fallback 09:09 UTC

09:40 update: this request is **DEFERRED after the09:38 new-job cutoff**.
No fallback job was started by this role. Existing D batch1 does not include
these sources. Preserve the following as next-window diagnostic instructions;
do not add another job this window just because this file says ready.

Minimum first compile: `research/fallback/WordBlockRuntime.lean` (no arithmetic proofs).
Actual indexed block16/getters, scalar UInt64 lo/hi recursion, max guard, tail,
one Int terminal plus bias/finishWord, lazy shipped fallback are all present.

Proof checkpoint `WordBlockCarrier-v1.lean` SHA256 e9f75791697779c268f6459cb95d1231468d3587a680efe80939a32f5f516059
is 9402B, single import ContractExact, no prohibited declaration/tactic tokens.
It adds actual indexed modular invariant and merge128. NOT_COMPILED.
Prioritize existing native/fullmodel queue; this is optional minimal diagnostic,
not a request for independent gate/fullmodel jobs or more CI capacity.

If compiler emission is cheap, retain generated C for `block`, `blocks`,
`body128Each`, sign extension and UInt32 getter specialization. C result alone
would judge actual boxing/control and would not claim runtime speed.

09:11 extension: current `WordBlockCarrier.lean` SHA256
33746c383576029185f062c011705191fbbe0f97a965a187f5729e095d151201 adds
signed32-to64, actual float factor getter alignment, array map getter and
block/tail composition through original finishWord, 18821B. Runtime source is
unchanged. A full carrier compile can replace the v1 request without another job.

All later candidate versions remain distinct files/receipts when CI freezes one.

09:18 smallest native discriminator is ready: `WordBlockCostMain.lean`,
single import ContractExact, ~9KB, plus `word-fixture-{normal,sparse}.txt`.
Build recipe and hashes: `cost-probe-receipt.json`; regenerate with
`build_cost_probe.py`. Driver verifies all80 outputs per fixture, then11
alternating trials×3 calls, each128 vsblock16 at prepared/full boundaries.
This is diagnostic, no shipped/fullmodel comparison and no acceptance claim.
Run only if existing main queue permits; preserve generated C and full stdout.

The driver is not wired into D's MainExact-only native bridge. It needs its own
temporary Lake executable target; see `NEXT-COMPILE.md`. The source and fixtures
are ready, but the target wiring/compilation/timing have not been performed.
