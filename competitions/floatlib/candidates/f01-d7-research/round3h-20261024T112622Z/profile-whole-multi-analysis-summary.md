# Three exposed-input whole-call diagnosis

Independent audit passed, exit0:69 original files, three already exposed plans with156 cases each, six complete uninstrumented processes and936 original whole rows. Same-seed checksums match; source/object/binary remained identical. Each plan also matches its original R12 plan field by field. No new holdout was generated or read. Full analysis SHA `5e8fb8f19c87a61698974e00ec2a14da8b45aef42bf8b349260c473b92297df5`.

Each share uses the mean of two processes' per-case fastest-of-three whole rows. These are diagnostic workload shares, not official score weights or candidate improvements.

| Seed | add | mul | sum | BMM |
| --- | ---: | ---: | ---: | ---: |
| 1224011 | 35.78% | 35.86% | 7.68% | 20.69% |
| 1224091 | 39.65% | 34.57% | 7.43% | 18.35% |
| 1224092 | 34.17% | 36.58% | 11.25% | 18.00% |

| Source-model route, share of BMM | 1224011 | 1224091 | 1224092 |
| --- | ---: | ---: | ---: |
| RowStream | 32.71% | 35.27% | 38.77% |
| Cross | 13.66% | 30.04% | 18.46% |
| DirectContinuous | 15.66% | 8.75% | 34.43% |
| DirectSmall | 37.66% | 25.92% | 7.07% |
| UnderflowZero | 0.31% | 0.02% | 1.26% |

The current n=1,p>2 DirectContinuous scope appears in exactly one case per seed: sparse1/p4, specials0/p16 and ml3/p6. Its diagnostic whole share is1.768%,1.223%,1.594%, respectively (BMM8.55%,6.67%,8.86%). It does not cover p1 DirectSmall, p2 Cross, n2..4 DirectContinuous or ordinary RowStream. In particular1224011's largest BMM case is n1,p1 DirectSmall ml6, which this mechanism omits.

P2 Cross covers3/4/2 cases. Their output-element ranges are42–58,800;600–176,454;35,292–88,224. Corresponding n ranges are3–190,1–124 and2–5. The n1,p2 high-output case occurs only in1224091: dense3 has176,454 outputs and3.575% of whole diagnostic time. The other two seeds have no n1 Cross case. Output materialization therefore has real but input-dependent exposure; all p2 Cross work cannot be described as high-output n1. No arbitrary output threshold was introduced.

Important context variation: on1224091, process1 add is1.3704times process0; add dense and ML cells are near1.9times, while mul and BMM remain near1. This inflates that seed's add and denominator shares. Across the other two seeds, operation process ratios are within about1.7%. Route differences combine input variation with this observed system/context noise; they are not pure causal effects of input shape.

The26 timed cell summaries, individual shapes, two process times, route model and raw hashes remain in JSON. RowStream-only changes leave roughly61–67% of BMM outside their route in these inputs; Cross fusion leaves all non-p2 routes and Cross preparation/compute outside its materialization target. These are coverage descriptions, not recoverable-cost or formal speedup claims.
