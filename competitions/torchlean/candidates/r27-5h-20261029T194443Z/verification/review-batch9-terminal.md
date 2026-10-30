# B9 terminal acceptance review

Review time: 2026-10-29 23:47 UTC  
Role: verification-only; acceptance inputs/results were not used for tuning.  
Run: 40972962791, GitHub Actions conclusion `success`; source commit `9b8b74f3d7839a4b38dcdd50b2b8d6ea3a5616dc`.  
Plan SHA-256: `15f477331026f648deafe1f218c20c75024eff2759dc3cb202c5d12941a99a77`; official source head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`.

## Candidate and proof

- Candidate `public23-gemm27-all-positive-k`, SHA-256 `6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada`, 252,719 bytes. Static recipe review is [review-batch9-gemm27-static.md](review-batch9-gemm27-static.md); the CI artifact regenerated it from receipt-bound public submission 23 plus the pinned submission 27 donor and matched the candidate hash.
- Exact official full gate passed for this source hash: exit 0, stage `axioms`, passed=true, verifier fingerprint start/end both `3a69968c7210ab18b325047e518ddfa942e642e21268a241e8693b075377bee6`, not exhausted. The candidate therefore passed the frozen original correctness gate. CI completion by itself is not the correctness evidence; this exact gate record is.
- `MainExact` bytes are preserved and rechecked: SHA-256 `b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab`; runner copy assertion is present and matches the dispatch-pinned runner.
- Compile, link, and response-file arguments match the original after target-path mapping: 22 compile args, 4 link args, 10,080 response args on each side. Only root-target paths are normalized.

## Standard Mixer native data

The exact R26 independent audit script [audit-native-run-40972962791.py](audit-native-run-40972962791.py) reused `analyze-native-only.py`'s pinned R25 tools and replayed the scorer. Pinned source identities are config `42150b6f1e13b51d18116bb0d9b4b017904793470ae8fdcb364de614499182b5`, multiseed `f171929b08cce37d848e736bb1d3c0bb422daeda1bbbd0da2ba3707d43d19341`, and scoring `8950678e5f093c9c14d82abe5b42275c122b068e81c95c106a7760a596e1baef`. Independent score, guard, and champion-estimate reconstruction match the root audit.

This is the Mixer single-board cohort: six Mixer cells × six official seeded workloads = 36 cell/workload pairs per round. The overall-board 30-cell cohort does not apply to a Mixer-only entry. Each of two distinct root seeds has 11 rounds, three inner repetitions, and 50 ms per cell, yielding 396 paired rows and 792 reported nanosecond values per seed. Exact current benchmark identity, cells, workload subseeds, timing request, candidate/reference hashes, and request parsing passed the pinned checks.

- Seeds: `113424343` and `1997857825`; each request hash, measurement hash, plan binding, and generated workloads are in the audit JSON.
- All 792 paired checksums match; no invalid or missing rows. Alternation is exact by round: reference first on rounds 0,2,4,6,8,10 and candidate first on 1,3,5,7,9.
- Same runner identity and CPU across both seeds: `runnervm48cm3`, x86_64, affinity `0`; candidate/reference binary hashes are stable. Raw CPU information SHA-256: `1d6c36e0f76fe6c94ad97cce5ff1fb9521c245b4602f37f0727b70cc145c5376`.
- Slow samples were retained with the raw measurements. The largest candidate sample in seed `113424343` is round 0, `s4|mixer:b1:sparse`, 171,344,478 ns; in seed `1997857825` it is round 9, `s2|mixer:b1:sparse`, 103,229,269 ns. Their paired checksums match. No sample was discarded.

## Current champion comparison

Latest saved board snapshot `boards-230552.raw` binds to publication `a8167e489762b43fab49513568bb2ba9d218a0713213c7e645c1cfdebf312f21`. The saved Mixer champion response `champions-mixer-2130.raw` carries the same publication hash and one current row: promotion 27, submission 36. Its source is unavailable. The current target is submission 36; submission 27 is only the historical anchor in submission 36's report and is not the current champion. Details and byte hashes are in [audit-mixer-current-binding-230552.json](audit-mixer-current-binding-230552.json).

Using the official #36-to-submission-27 report edge, fixed R25 score, and B9 local cohort gives **1.7477679374609987× current Mixer #36 time** (`INFERRED`; slower). This crosses benchmark/report config, environment, and seed contracts. The report config `ab0fdb552d44b82ee286607a8ad0d914b6426615853ea3fe255878208a744f0e` differs from the live Mixer board config `4a9278fefa8f3799173bf1dfec50c7ea02819d3e312c819e267ecfeb89b5dbf9`; the current champion source is unavailable. The strict converter correctly remains `UNKNOWN`. The pinned scorer's guard failed, so this candidate does not establish a Mixer promotion or a win.

The older champion-only record flags the 21:29 response as mismatched because it compares it to an older snapshot with publication `a103...`. The saved 23:05 snapshot instead has the exact response publication `a816...`; the supplemental binding audit rechecks this from existing raw files, without another API request. This corrects identity binding only; it does not repair the report-config calibration gap.

## Integrity and remaining integration

- Outer manifest: 79/79 files pass; runner inner manifest: 78/78 pass; no missing or unexpected files.
- GitHub artifact 12942246310 is retained with archive digest `sha256:4daef84900cf583ebe208243a5ebcbd8430b1d578f482edc5da88e0622ba2457`.
- The independent audit result is `PASS_B9_GATE_AND_NATIVE_ACCEPTANCE_AUDITED_NO_PROMOTION`, with zero failures. Its captured root audit SHA-256 is `b5adea640d45d86cff0482983f2563934443f36d0153b13db8e311c2a06956d9`; runner summary SHA-256 is `0d13abb9f300f335075e8fda0d84e95beb4e33581b3bdc0d3bd78568c0115f5b`.
- `CI-RESULTS-BATCH9.json` appeared at 23:45:53 UTC, after the independent audit capture. It matches the audited candidate hash, full-gate verdict, two 396-row cohorts, checksum counts, and inferred current #36 multiplier; file SHA-256 `07c69d473588932a00faa6bd798713c0200140ca8c588debc7636cdf384986dd`. Droot owns the integrated result file and Git.

Conclusion: B9 is correctness-gate PASS for the exact candidate, but performance is a large inferred regression against current Mixer #36; no promotion. Keep this candidate and all raw evidence for reproducibility, then continue only with any new frozen candidate/CI that Droot identifies before the common deadline.
