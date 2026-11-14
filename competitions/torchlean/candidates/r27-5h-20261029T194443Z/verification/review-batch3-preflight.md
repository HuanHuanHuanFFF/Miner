# R27 batch 3 preflight delta review

Read the 20:45 development-status, BATCH3-READY request and public status before reviewing this frozen draft. No batch 3 dispatch was present at that checkpoint. This is a narrow plan/runner review; it does not compile Lean or dispatch CI.

## Frozen identity and champion mapping

- Plan hash eac8158f55273dcbf6580b025e0a8461fe8d513f3d3ff3941302b072307e711b matches BATCH3-READY and the current ci-plan.json copy.
- Runner hash 58b20a75732b133889ec20235268d66ee637810faad5cca90abb2f6d0e660782 matches BATCH3-READY.
- Board and human target are both normalized_mlp/current submission 23, promotion 24, source SHA 1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe. The plan correctly uses submission 12/e2c1f1f1… as a retired report-chain carrier.
- Current report factor is INFERRED and source12 remains local-only. Plan roots 27102921/27102923 are quick-exploration inputs, not the current report root 3542272469 and its six generated workloads. Do not present a quick result as an exact current report or production score.

## Candidate identities and proof scope

- public12-guard26-v2: SHA dced7848655a50a136750c1837b46f084a25ec26d13df72fe907d4a162bf1cb9, 218583 B, full_gate=true. The independent v2 receipt binds source12 and patch hash 9fa6e555df8af97cb942b779bf7b9888fea662b4553914590f68ae5289cf0ad6. It replaces the failed broad nlinarith proof step with a direct transitivity chain, without raising heartbeat limits or changing runtime code. The official full gate must still pass this exact hash.
- public12-norm-prep-proof2: SHA 40b17282cebbd1d97256f4a945edb041de5e5a00023369e235c11d8e048a3a8e, 222258 B, full_gate=false. It stays NativeOnly until a full gate is explicitly added and run.
- public12-native-layer-stats-v1-hb: SHA 1bd6e15375a83e59ca1ec276fac0b2898cadd07abf560ef7140e1f6bf4463e8b, 255969 B, full_gate=false. Its base reconstruction is beca1b56…/255936 B; variants.py adds exactly 33 bytes, set_option maxHeartbeats 1000000. The pinned official sandbox policy allows maxHeartbeats up to 4000000, and the generated output is still under 256000 bytes. At 31 bytes below the cap, preserve exact byte length/hash checks; do not infer correctness from this candidate's declared proof.
- The two helper files match their plan hashes. The runner labels them as standalone elaboration/axiom-print diagnostics.

## Profile and runner separation

The plan enables profile_control and binds profile_control.py to SHA 03035270a3291d6b7bcba31e9d4611d23364937033c0e26c9528b84048e3cc8f. The runner profiles the already-built calibration control only, creates a separate R27EntryProfile C file/object/binary, and stores the cost discriminator under cost-profile. It checks checksum equality and does not use profiler times in paired scoring or proof status. Profile failures are caught as incomplete diagnostics and do not change candidate proof/score. Verify the terminal profile artifact and file manifest; no C or source file should be uploaded.

## Review result

Plan scope is mixed and candidate-specific full_gate flags are consistent. No new plan metadata mismatch found. The exact current champion source remains unavailable; report-chain conversion is INFERRED. The source12 receipt is LOCAL_ONLY, and a public-runner fetch remains a source-use-policy question. Await a frozen dispatch and then audit its exact frozen files before interpreting output.

Budget note: profile_control is enabled in the current draft and runs before candidate builds. run_profile allows up to 60 seconds for each of six control and six instrumented cell calls, plus up to 120 seconds for each compile/link command. This diagnostic does not contaminate score/proof binaries, but can consume a material part of the runner's 1800-second END budget and leave later candidates incomplete. Interpret incomplete native work as time/phase boundary, not algorithm failure; retain the profile result separately.

Budget risk for the enabled profile: run_profile executes before candidate phases. It allows up to 120s for each of two build commands and 60s for each of six control plus six instrumented cell runs (up to about 960s total), while runner.py has a 1800s internal END budget. Two 120s helper checks also precede reference profiling. The later guard26 full-gate command is clipped to remaining END time; if the profile consumes its budget, the gate could receive less than its 650s cap and report a budget-driven failure. Before dispatch, either disable/shorten the optional profile or move it after the proof-critical gate and reserve the gate budget. If the frozen plan is dispatched unchanged, audit the actual cap/elapsed time and classify a truncated gate as INCOMPLETE/UNKNOWN, not a source proof counterexample.
