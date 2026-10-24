# ExactDF profile40092014611

The frozen analyzer passed once with exit0. It authenticated794 exported original files, all156 exact seed1224016 cases, exactDF bytes, original whole log/JSON, both profile processes, checksums, pure-root call counts and nested-exclusive partitions. Analysis SHA: `63c5b77d8ad8cbfa9460bc7a9787b1114773515755ee6e836eeee2033bb9c4e7`.

The uninstrumented whole-call anchor is the useful cost locator here. These sums describe one fixed diagnostic workload and are not official score weights:

| BMM source-model route | Timed cases | Original whole sum, ms |
| --- | ---: | ---: |
| DirectContinuous | 8 | 14.246874 |
| Cross | 5 | 12.615592 |
| RowStream | 15 | 6.231684 |
| DirectSmall | 2 | 4.479591 |
| UnderflowZero | 4 | 0.233924 |

The largest original BMM case is `bmm:sparse:2` on Cross,6.846718ms. DirectSmall `bmm:ml:7` is3.396324ms; RowStream `bmm:dense:0` is2.190925ms. Original whole sums across operations are add61.341221ms, mul62.652136ms, sum12.830920ms and BMM37.807665ms. Each timing is the original fastest of three sweeps with caller checksum/cleanup included.

The stage probes perturb execution substantially. RowStream `bmm:dense:0` has1,284,100 Bpack probes per process and profile whole17.567458/17.501598ms, about8.00times its original anchor. Cross `bmm:sparse:2` has1,588,240 output probes and profile whole32.087681/32.094637ms, about4.69times its anchor. Different process/cache/layout also contributes; these factors are not isolated probe-cost measurements.

Therefore RowStream's instrumented Bpack75.275%/Amap2.921%, Cross output63.717%/combined preparation19.706%, and DirectContinuous output53.556%/compute46.263% locate executed families but do not establish their original cost fractions. In particular Bpack includes allocation, fill, padding and conversion, and Amap includes mapping overhead. Neither percentage is a removable-cost bound for708. Exclusive accounting prevents nested double counting; it cannot remove instrumentation cost or restore original compiler layout.

UnderflowZero executes scans and zero output with no compute phase, matching the source model. DirectSmall root-exclusive53.373% and sum root-exclusive53.573% remain unresolved regions. Fused arithmetic, inline work, uninstrumented helpers and fine-grained probe overhead remain UNKNOWN. A future quantitative stage diagnosis would need coarse boundaries without per-element producer/consumer probes; this report performs no new run or source modification.

No official score, incremental candidate benefit or champion multiplier is inferred. Route classification is a literal official-input/frozen-source model, not an individual machine branch trace. Full JSON retains every case and raw provenance; this summary intentionally avoids a per-case narrative.
