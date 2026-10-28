# Indexed8: real address-cost improvement; q stack still present

**Retain as a measured BMM component, not an adopted full kernel.** Frozen8e27/250041B compiled in run40611570030. This worker independently rehashed all326 originals/36,892,038B and checked all156 checksums across all8 processes per seed. `indexed8-actual-review.json` contains exact hashes, every case and all controls. No new source/seed/CI was created for this review.

The actual timed Submission C is e0979bb1; linked/captured object85dbf986 is unchanged across timing. Three actual Suite IO entries have no captures; scalar closures have arity2 and BMM closures arity6. New wordLoop has8 machine-word parameters,2 array parameters and8 native Float32 parameters; no ghost advance/Nat counter/proof state survives in its runtime call. Its body borrows4 raw A elements plus one B2 record. Existing B preparation remains once, and word-fit miss calls the old Nat output using that same prepared cache. Shape/UnderflowZero order and duplicate public guard on shape miss remain as before.

**The register-residency target was not reached.** Actual same-object raw8 uses280B frame; indexed8 uses120B and has no Nat helper calls. Both execute2mulps+2addps for8 genuine SIMD MACs, plus4mulss from the unchanged decoder. Indexed8 retains4 conditional `lean_float32_of_bits` sites. At0x10e/0x115 and0x120/0x128, its normal arithmetic merge reads/writes both accumulator vectors through[rsp]/[rsp+0x10]:64B of explicit stack load/store instructions each k. This is not measured memory-bus traffic. Claim removal of tag/bounds/Nat-address work and reduced frame, not elimination of spill.

| Seen pair | Raw8 BMM/B2 | Indexed8 BMM/B2 | Indexed8 eligible sum/B2 | Indexed8 whole/B2 |
| --- | ---: | ---: | ---: | ---: |
| seed2220001 block0 |0.959001|0.885144|0.831765|0.968528|
| seed2220001 block1 |0.960709|0.943890|0.842436|0.992196|
| seed2220003 block0 |1.001307|0.946705|0.876999|0.993392|
| seed2220003 block1 |1.005992|0.928235|0.899182|0.985039|

Raw/index values are their own paired-control blocks in one process order, not directly adjacent raw-versus-index timings. Eligible sum improvement is more consistent than headline. p2/3 and some p4/5 cases improve; wide p9/34/60 regressions and all tails/preparation/finish/RC remain charged. Seed1 p9 dense0 stays1.289/1.279; seed3 p60 sparse5 is2.687/2.727. No threshold change is made from those observations.

The best headline includes a slow **untargeted control**: seed1 sparse4(n1) controls0/3/4/7 are2,622,830/2,473,627/3,999,785/2,476,912ns, and indexed5 is2,482,080ns. That−1.518ms cannot be assigned to indexing. Seed3 n1 extremes0 also switches between about587k and889k control ns, while variants switch too. Root cause UNKNOWN; no sample dropped. BMM control max/min is1.05282/1.02085; unchanged ADD/MUL/SUM drift is preserved. Only one observed whole block≤0.97, so this is not stable whole adoption evidence.

Next is `INDEXED8-PUBLIC-PROOF-PLAN.md`: close the actual producer, old Nat8 projection and word→Nat transport before final public binding. The current public four roots still certify B2. Full new proof/replay/axioms/25-round gate, independent confirmation, private distribution and formal admission remain UNKNOWN/NOT_RUN.
