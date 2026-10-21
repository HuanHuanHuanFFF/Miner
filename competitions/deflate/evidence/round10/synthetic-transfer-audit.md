# Fixed synthetic transfer audit

The eight generated `synthetic-transfer` inputs were recomputed directly from `SYNTHETIC_RAW` lines in the completed gate logs. Seven runs contain measurements; failed `prove-a` (37682364860) has no synthetic state section and zero raw markers. The seven measured runs provide 34 candidate/block groups (306 raw lines), each covering 8 files with 1 warmup and 11 measured repetitions. All 34 recomputed time/size pairs match the corresponding state metrics within 1e-12; source hashes, input hashes, repetition counts, deterministic flags, and raw artifact manifests also match.

The fixed inputs are the same eight byte-for-byte files across the seven measured runs (884,251 bytes total). Each observed source hash produces identical per-file token/output fingerprints across its captured blocks/runs. The complete input SHA map, each CI log SHA, state SHA, source SHA and raw line range are in the JSON receipt.

No synthetic `r9-block-scalar` group was recorded. The synthetic ratio below is therefore candidate versus same-block `r3-432-fast3` as a diagnostic. The public-versus-scalar figures come separately from `corpus-stage1`; they are not synthetic scalar measurements and cannot establish a formal direction reversal on the generated inputs.

| Candidate | Public time vs scalar | Synthetic time vs same-block fast3 | Synthetic size vs fast3 |
|---|---:|---:|---:|
| `r10-forward-seed` | -5.61% | +166.06% | -2.549 pp |
| `r10-forward-seed2` | +9.54% | Not captured | Not captured |
| `r10-forward-lazyseed` | -5.13% | Not captured | Not captured |
| `r10-forward-costseed` | -3.10% | +161.55% | -2.944 pp |
| `r10-forward-endprobe` | +0.07% | +166.62% | -3.044 pp |
| `r10-forward-delta16` | +1.25% | Not captured | Not captured |
| `r10-finder-row16` | +10.90% | +208.02% | -3.038 pp |
| `r10-finder-row16-mask` | +7.06% | +183.00% | -3.038 pp |
| `r10-finder-key5` | +4.78% | Not captured | Not captured |
| `r10-finder-key6` | +2.25% | Not captured | Not captured |
| `r10-forward-rebase16` | +2.97% | +190.99% | -3.042 pp |
| `r10-record-nonempty` | -1.23% | +181.65% | -3.042 pp |

The public column is the per-block ratio of candidate and scalar score axes from `corpus-stage1`; it is separate context. For seed, costseed, and record-nonempty, those public blocks show small speed improvements against scalar, while their fixed-synthetic time axes are **2.60–2.82×** the same-block fast3 axis. This is a transfer warning against fast3, not a scalar reversal: the synthetic bench omitted scalar. Row16, row16-mask, and rebase16 are slower in both the public scalar comparison and the synthetic fast3 diagnostic. Endprobe is near neutral in public scalar blocks (one block each way) and slower than fast3 on both generated blocks. Every measured candidate in these runs emits fewer bytes than fast3 on this fixed synthetic set; this is a comparison against fast3, not against scalar.

The synthetic capture does not include key5/key6, seed2, lazyseed, delta16, or the row-c repeat of record-nonempty; `prove-a` contains no synthetic run at all. The row-c public repeat of record-nonempty is -1.1746% versus scalar, but has no generated-input counterpart. The proof-a seed rerun also lacks generated-input rows, so the seed source has only its explore-a two-block synthetic result. These absences are kept explicit in the JSON, with available source hashes and separate public metrics. No missing synthetic comparison is filled from a public-only result.

These are public fixed-script generated-input measurements. They are **not held-out**, **not private/stage2**, and **not leaderboard estimates**.
