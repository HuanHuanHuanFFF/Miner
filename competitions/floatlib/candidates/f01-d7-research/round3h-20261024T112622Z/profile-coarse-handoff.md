# R13 coarse diagnostic

CLI remains `profile-coarse-entry.py --upstream --kernel --out --plan`. It loads adjacent `profile-coarse-current.py`, exactDF source, original4b7 statement gate and the already exposed seed1224016/500000 public plan. Root may use a distinct dispatch seed. New measurement prefix is `profile-r13-coarse-`; C output marker is `FC13`; entry verdict is `diagnostic-only-coarse-verdict.json`. This is diagnostic only, never a full gate or performance adoption.

The original full-plan whole/checksum anchor, two separate per-case profile processes, three inner sweeps, unchanged compile/link flags, source/object/binary hash metadata,300second module ceiling and original layer cleanup are inherited from the frozen first profile. Old entry/current/analyzer files remain byte-identical. No binary is exported.

Actual original DF C from40092014611 (SHA `31e1409237ccf2e66b3b107a1ff8b3a257c9faa4e2786749c624b6aac03ccbc2`) shows the public dispatcher calling RowStream_output and DirectContinuous_output directly, bypassing their core wrappers, and calling Cross core___redArg then words___redArg. The selector uses these actual entries. Its10 exact categories each have one function:

| Category | Complete measured boundary |
| --- | --- |
| whole_bmm | exported BMM root |
| whole_sum | exported sum root |
| rowstream_amap | actual RowStream_output specialized Array.map function; one entry before its tail label |
| rowstream_bpack | Packed10_packB outer allocation/fill/conversion |
| rowstream_scope | RowStream_output, excluding nested Amap/Bpack in exclusive totals |
| cross_words | Cross words___redArg, combined preparation, packet compute and repair |
| cross_scope | Cross core___redArg; exclusive time is materialization/cleanup around words |
| direct_continuous | actual DirectContinuous_output, complete compute/output |
| direct_small | DirectSmall_core, complete compute/output |
| underflow_fill | UnderflowZero_zeros; scans remain BMM root residual |

No lambda, boxed adapter, Fin.foldl, ofFn, row/packet producer, emit, finish or dot loop receives a probe. Every non-root category must execute at most once per BMM invocation, checked against actual counters. Unexpected per-output/packet frequency fails closed. Exclusive nested totals avoid double counting. Sum has no inner probes; its root still executes once per vector, so large batch counts can retain appreciable timer overhead. Whole disturbance is UNKNOWN until the new runner measures it.

Missing/unexecuted boundaries are UNKNOWN. The design deliberately keeps Cross preparation and compute fused and Direct compute/output fused. Amap and Bpack include their full emitted helper costs; neither is a removable-cost upper bound. Clock/compiler/layout/process effects still prevent projecting stage times into an official score.

`profile-coarse-build.py` verifies original source hashes and produces independent copied files with bounded selector/tag/scope changes. `profile-coarse-test.py` passed against the actual DF C in0.79s with exit0: ten exact functions, no indirect callback or per-row/packet caller of a selected function, all entry probes before tail labels, all return probes balanced, ten-category parser and six rejection boundaries. The complete selected-function incoming graph and original body hashes are in `profile-coarse-tests.json`; original stdout/stderr/exit are retained. New Linux compilation/execution is NOT_RUN.
