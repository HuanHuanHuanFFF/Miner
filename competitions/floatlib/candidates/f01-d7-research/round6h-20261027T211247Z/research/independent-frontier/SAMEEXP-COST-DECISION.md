# Same-exponent ADD: complete guarded cost rejects current body

**PARK** the exact typed runtime and56038cfe full public proof attempt. Do not run another seed, full proof gate, or wider same-E variant merely to rescue this result. The original c37/914a type-failing sources, typed84c1/5603 copies and reverse patches remain intact.

Actual cost3 run40590900980 uses253400B/4538290d, Intel Xeon Platinum8370C, unchanged original flags after owned-target path substitution. It is a full156-case diagnostic composition with152 timed cases, two discovery inputs and two paired blocks each; **not the original25-round score or new public ADD proof acceptance**. The new entry's namespace block matches84c1/5603 after only namespace mapping.

| Discovery seed/block | Whole/B2 | ADD/B2 |
|---|---:|---:|
|2220001/0|1.046126|1.152300|
|2220001/1|1.070920|1.151370|
|2220003/0|1.045437|1.127098|
|2220003/1|1.052830|1.144362|

`same-exponent-cost3-audit.json` independently rehashes28 original files and reparses8 raw logs/1248 case lines. All matching checksums and the four ratios agree with D's released summary. ML is1.227–1.268, sparse1.181–1.214, specials1.181–1.238; paired is near1.0 only in the second input. Slow blocks and all cells are retained. There is no significant positive whole claim or adoption inference.

The one actual-caller inspection confirms the intended mechanism happened. `BENCH_VARIANT=sameexp` resolves through the real option/string/closure to `main.lam0.boxed -> main.lam0`; control selects `main.lam2`. These are the owned object linked into the measured diagnostic binary, not the standalone helper or earlier statement-only assembly. Scalar code size is560B versus448B; both boxed wrappers are116B and byte-equivalent after symbol-name mapping.

Accepted normal path0..23→f6..115→121..13e contains masks, fraction addition, `bt/adc`, shift and pack. It has no call, scale-table read, FP instruction, heap operation or data spill. E0/E254 return from the corresponding exact branches. Both variants already save rbp/r14/rbx and reserve16 stack bytes, so a new frame/boxing accident does not explain this regression. Guard misses execute xor/comparison/conditional control before the original decoder path. The relocated tail jump atf1 is the fallback's external toBits call; it must not be mistaken for a jump into the integer arm.

Branch prediction, instruction placement and individual path cycle costs remain UNKNOWN: no hardware counters or isolated-path timings were captured. The observation is that a correctly lowered short accepted arm failed to compensate for its complete caller costs. Instruction count alone does not identify the cause. The audit therefore closes this exact implementation's investment premise without declaring all integer ADD impossible.

No further large proof work is justified for56038. Its47 roots remain NOT_RUN; the cost diagnostic has no new `add_spec` proof. The scalar semantic source and normal-field fragments remain research assets, with their original statuses and precise hashes. B2 remains retained and formal#336 remains attached only to622d.
