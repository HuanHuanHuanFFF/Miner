# Empty/singleton pixel shortcut: stop as a new implementation route this window

This is a subset of parent/A sparse-input work, not an independent mechanism. The idea was to broadcast a nonzero finite bias when a whole pixel vector is zero, or replace a single-nonzero-input dot by exact FMA plus the same bias. Actual finite/sign guards and raw-zero behavior would still be required; future BN cannot be assumed by a general kernel.

`support01-census.json` on the same18 old full formula models:

| Stage / weight path | Outputs | Empty support | Singleton support |
|---|---:|---:|---:|
| pw1 dense |38408|126|1491|
| pw2 dense |9222|0|119|
| pw1 sparse |19204|43|958|
| pw2 sparse |4611|0|64|

Only1736/47630 (3.64%) dense-path outputs have support≤1. This is output coverage, **not a runtime share or rigorous latency upper bound**. A new scan/metadata/branch paid on all inputs for this narrow scope is a weaker use of the remaining window than the already-selected full local-scale cost experiment and its proof diagnosis. No kernel, proof expansion, or CI request is added. General multi-element sparse support remains a different, larger opportunity inside the same family.

Signed-zero caveat retained for any later revisit: zero body plus negative-zero bias is not always negative zero; original raw zW/Ybz checks all product signs. For singleton support with nonzero selected weight, exact FMA can match the same unrounded body+bias, but input nonfinite values and zero weights still require real guard/fallback reasoning. The tiny observed scope does not justify that bridge now.
