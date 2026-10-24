# Coarse DF diagnostic40094358287

Independent reader passed once, exit0:156 exact cases,794 original files, checksums, root calls, non-root calls≤BMM root, exact C instrumentation reconstruction and exclusive partitions all matched. Analysis SHA `eea04b549751f61aa3772803b9b2b82f1515fc51fc821ceee0f27af85ab9c6c0`.

| Route | Original timed whole sum, ms | Profile/original sum ratio | Use of coarse intervals |
| --- | ---: | ---: | --- |
| RowStream | 3.001537 | 1.008730 | Low overall disturbance; retain per-case variation |
| DirectContinuous | 8.791641 | 1.003442 | Complete compute/output scope only |
| DirectSmall | 2.590828 | 0.979142 | Complete compute/output scope only |
| Cross | 6.476568 | 1.181010 | Qualitative cost location; material context/layout disturbance |
| UnderflowZero | 0.150327 | 0.701161 | Context shift; no speedup claim |
| sum | 8.153764 | 3.330953 | Root clocks remain too frequent for quantitative attribution |

BMM overall ratio is1.053773. Ratios combine instrumentation, compiler/layout, process/cache and system effects; they do not isolate timer overhead or measure a candidate improvement. Original whole times locate cases within this run. Absolute times must not be compared with the prior fine diagnostic on another runner.

RowStream coarse pure-root exclusive distribution is Amap17.035%, packB33.896%, remaining computation/output/cleanup48.888%. Its largest whole case `bmm:dense:0` has ratio0.9874; the distribution is Amap22.215%, packB54.096%, remainder23.657%. Each selected outer runs exactly4 times across warmup+three sweeps, rather than the old1,284,100 Bpack probes. PackB and Amap still include allocation/fill/conversion overhead, so these are not removable-conversion ceilings.

Cross words combines preparation, packet computation and repair; its inclusive interval is69.140% of measured Cross pure roots. Core-exclusive materialization/cleanup is30.820%. The largest Cross case `bmm:sparse:2` has words54.325% and materialization45.657%, with exactly4 calls to each boundary. Its whole ratio is1.258484: the materialization is nontrivial in observed execution, but45.657% is not its established original cost or a formal improvement ceiling.

DirectContinuous's complete scope contains99.970% of its measured pure roots; internal compute/output remain UNKNOWN. Sum cannot be treated as low-disturbance: `sum:dense:2` calls the root705,880 times per process and has ratio6.786963. Sum has no internal stage measurements. Underflow scan/fill costs also retain large process/context variation.

No official score, candidate increment or champion multiplier is inferred. Full case rows, per-process ratios, calls, intervals and original hashes are retained in JSON. Frozen readers, runtime files and original artifacts remain unchanged.
