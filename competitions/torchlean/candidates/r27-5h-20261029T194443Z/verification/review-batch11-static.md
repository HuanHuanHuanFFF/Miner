# B11 band64 weight-cache static review

Review time: 2026-10-29 23:49 UTC. Run 40975355668 was dispatched at 23:46:12 UTC and was queued at the capture time. This is a post-dispatch identity/policy check only; no CI outputs or new benchmark inputs were read.

## Frozen identity

- Candidate: `public23-band64-weightcache`, SHA-256 `4a9cb398cb45df02c977604e7968648716250af5e0a0dfa99a8068e8b00b8f9b`, 252,675 bytes (3,325 bytes below the 256,000-byte limit).
- Plan SHA-256 `c5773dbb1a9cd1288515b2a933eedeb8fb5436c13cd4eda4b11ab33e415b868e` matches both canonical `ci-plan.json` and the dispatch frozen-file entry.
- In-memory reconstruction from saved public submission 23 source (SHA-256 `1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe`) reproduced the candidate hash and byte count. The builder, helper fragment, compact-source helper, runner, prepare script, and every owned file match their dispatch SHA-256 values. Repository is public and `allow_private=false`.
- Standard measurement plan: normalized MLP, root seeds `27103011` and `27103013`, 11 rounds × 3 inner repetitions × 50 ms; cost driver cap 600 seconds. The original request inputs remain reserved for acceptance.

## Proof and comparison limits

- This candidate is explicitly `full_gate=false`, `declares_correct=false`, with no proof diagnostics. The new correctness theorem is absent; the new `kernels.dense` field reuses `retainedKernels.dense.2`. That does not establish correctness for the changed function. It remains **NativeOnly**, even if CI succeeds.
- The current target is normalized MLP submission #43 (promotion 28). Its saved response binds to the latest board publication, but current source is unavailable. The #43/#23 report edge is tied to the live board config; benchmark identity is inferred from current head and live-hash replay. Any local two-seed measurement can only produce an **INFERRED** current-champion multiplier across environments and seeds; the strict converter must keep that local row `UNKNOWN`.
- Submission 23 is the report-chain reference used to estimate against current #43, not the contest target and not a current champion. Do not present candidate/submission-23 timing as the human performance result.
- The transformation prepares input-row and weight factors, buckets by exponent band, and uses 64-product accumulation blocks for the selected dense route. Preparation, decoding, fallbacks, and output cost must remain inside the eventual whole-model timing. No gain is assumed before the frozen run.

The compact record is [audit-batch11-static.json](audit-batch11-static.json). It confirms the frozen target and cost-only proof boundary; it contains no performance result.
