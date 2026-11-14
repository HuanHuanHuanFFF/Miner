# Normalization opportunity: model coverage before implementation

Read-only evidence: fixed `ExactSuite.lean` at upstream accb82b6, Git blob `f78b33ea5ac54b5210bcaa19a03b70e93f5c5f6d`, retrieved through GitHub. `nmlpLayers` uses one RMS normalization and one layer normalization between linear layers. `mixerLayers` uses two layer normalizations; its remaining work includes GEMM, linear layers and residual adds. The other three model families do not call these normalization kernels.

D's20:49:45 official boards snapshot assigns overall model weights0.2 each to mlp/mixer/resnet/mobilenet/normalized_mlp and hardware weights0.5 each to prod-amd64/prod-arm64. These are geometric score weights, not fractions of elapsed time. A single AMD result cannot establish the production two-environment score.

With all other models unchanged:

- Only improving normalized_mlp by ratio r gives overall r^0.2. An overall ratio0.9 would require r≤0.9^5=0.59049, a40.951% model-time reduction.
- Improving both normalized_mlp and mixer by the same ratio r gives overall r^0.4. Reaching0.9 requires r≤0.9^2.5≈0.76843, a23.157% reduction in each affected model.
- More generally, if the target normalization portion occupies model fractions f1/f2 and that portion becomes a factor c faster, the simple fixed-cost prediction is [(1−f1+f1*c)(1−f2+f2*c)]^0.2. The f values must come from actual profiling; current values are UNKNOWN.

Therefore the RMS quotient checker is the smallest arithmetic/proof falsifier, not yet a sufficient whole-score strategy. The larger route must reach layer normalization or reveal exceptionally large RMS cost. Former #2 already replaced rational moments and sqrt precision; profiling the shipped base would overstate remaining opportunity against current competition. Source #5 remains unavailable; observations on #2 are an inspectable starting point, not confirmed current-champion internals.

Current exact-root/report access attempts and local failures are preserved in `torchlean-report-receipts.json`. Parent is acquiring the reports through its working public-API path. Even complete model reports may lack layer timing; missing layer costs remain UNKNOWN rather than being inferred from operation counts.

**23:25 evidence update:** D had obtained full200 reports at21:54; `read_public_reports.py` now independently verifies their SHA and recomputes both official overall scores exactly. #5's projections within its overall evaluation against#2 are normalized_mlp .9667038093 and mixer .9688314629; all-family wide projection .8928156343. These reweighted projections are not the independent family-board evaluations. In particular #5's mixer-board guard failure/1.0645455943 compares against another source b343f5e…, whereas its overall evaluation compares against#2 cea442…. Raw CPU times were never pooled. Layer attribution, current ranking after that snapshot and prospective candidate gains remain UNKNOWN. Prior403 receipts retain their original scope and bytes.
