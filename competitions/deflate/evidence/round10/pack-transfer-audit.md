# Pack-i transfer audit

Pack-i `37698560245` completed successfully. I recomputed its public total-time axes from both raw paired JSONL blocks and the fixed synthetic `SYNTHETIC_RAW` lines; no source or raw receipt was changed. The raw-artifact manifest has 46 entries and no byte/hash mismatches.

| Corpus | Block 1 vs record | Block 2 vs record | Two-block mean | Packed/record/scalar token and output hashes |
|---|---:|---:|---:|---|
| Public, 28 files | +1.873958% | +1.017215% | +1.445586% | 28/28 equal in each block |
| Fixed synthetic, 8 files | -0.069268% | -0.218374% | -0.143821% | 8/8 equal in each block |

Public size is unchanged at 33.934365748% for packed, record, and scalar. Synthetic size is unchanged at 33.569505508% for the same three methods. The synthetic packed/record comparison is a small faster signal on this fixed set; it is not a private/stage2 guarantee. These fixed generator inputs are not held out and are not leaderboard estimates.

Against scalar, packed is +0.601777% and -0.106854% in the two public blocks (mean +0.247461%); on synthetic it is -0.611567% and -0.018876% (mean -0.315221%). Packed tokens and output hashes match scalar and record in every block, so these timing differences do not come from a byte or token change.

The packed-record native diagnostic reports 18 D-routed public inputs, 10 non-D skips, 24 forced synthetic D calls, and 39 header-boundary cases including the single-word zero node. All compared firstplans and decoded `(position, payload)` node streams match; the saved word count equals the number of nodes. Across the 18 public D inputs, it sums 4,309,747 words or 17,238,988 bytes saved in the `rs` record streams. This is accumulated storage across test inputs, not peak RSS or simultaneous live-memory reduction.

The measured public total-time axis is slower in both blocks despite identical output and reduced `rs` storage. The small synthetic timing improvement remains scoped to the fixed generated inputs. This run has no full proof gate for packed; CI success and finite node-stream checks do not establish all-input equivalence. The root has stopped additional packed proof or combination work.

Raw paths, source/input hashes, per-block recomputations, synthetic line ranges, and diagnostic sums are in [pack-transfer-audit.json](pack-transfer-audit.json).
