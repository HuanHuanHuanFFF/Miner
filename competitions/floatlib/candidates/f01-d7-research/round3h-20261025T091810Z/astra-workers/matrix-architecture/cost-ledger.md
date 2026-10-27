# A4B2 complete-cost ledger before any new timing

Scope is the actual5f53a930 source. Let G=ceil(p/2), H=floor(m/4), T=m mod4. Preparation of B2 and treatment of the odd second lane are identical to accepted622d. The formulas below compare the new4-row body against four existing B2 rows. They are exact source-level event counts, not CPU time, physical allocation, or a comparison with F10 outside the old p2..8 domain.

| Per complete4-row block | Four old B2 rows | A4B2 |
|---|---:|---:|
| A raw conversions |4Gn|4n|
| B2 packet reads |4Gn|Gn|
| A raw reads in MAC loop |4Gn|0|
| A4 packet reads in MAC loop |0|Gn|
| k-loop iterations |4Gn|Gn|
| Active+odd-padding scalar multiply/add pairs |8Gn|8Gn|
| Final original raw finish calls |4p|4p|
| Result records |4G F2|G F8|
| New A panel records / pointer array |0|n A4 /1 array|
| New tile cache pointer array |0|1 array with G slots|
| Tail row body |T old B2 rows|T identical old B2 rows|

The expected direct-field representation is A4 payload16B and F8 payload32B, using the established Lean scalar-field layout. Baseline F2 payload8B is verified actual C. New payloads require actual generated C. Fixed Lean runtime source (`lean-header.txt` from pinned293d) defines an8B object header and24B Array header on64-bit. Conditional request-size model, assuming exact-capacity arrays: A panel32n+24B; F8 results+tile slots48G+24B; four old F2 results64GB. Thus the added cumulative request bytes per block are **32n+48−16G**, before closures, alignment/allocator classes, temporary preparation lifetimes, output capacity, Nat operations and RC. This is often positive, especially p=2. No claim of lower heap allocation is justified.

At p=2, A conversions are unchanged, so of_bits *call count* is not a benefit. The gain premise is that the MAC body can become two packed4-lane mul/add chains with no calls and fewer loop/index/packet operations; conversion calls execute during preparation before live accumulators exist. At p>=3, A conversion work additionally amortizes across G. New preparation still pays all4n raw bounds/default checks and converts every valid A once; result finish may redo raw work for NaNs. These costs cannot be deleted in a cycle model.

Old B2 C has5 object arguments+2float accumulators, a Nat test/increment and raw-A bounds path. New source projects to2 object arguments(A4/B2),2 USize arguments(count/k),8float arguments. On the expected x86-64 ABI the8floats fit the vector argument bank; unlike old40float wide-loop calls there is no mandatory incoming float stack spill. This is an ABI inference, not a measured assembly result. Clang may still spill or fail to combine lanes; the exact function/caller decides.

For p>8, actual622d uses Packed10/other paths, so the four-B2-row comparison is counterfactual. Ignoring tails, four F10 rows use roughly4n*ceil(p/10) iterations, while A4B2 uses n*ceil(p/2), about1.25x as many for large p. Arithmetic count stays unchanged apart from different final packet padding; A4 reduces scalar pointer gathers but adds panel construction and increases B packet-object count. The broad guard is therefore a genuine complete-cost experiment, not an assumption that more coverage must improve speed. Keep this source fixed for its first complete test; a failure is not repaired by excluding slow shapes after a confirmation result.

The current score evidence (`analysis.json`) only gives class totals: BMM16.142/20.023/19.058% of whole on completed R15 D/A/B. Shape selection19/23/20 touches every BMM class but cannot identify time within those classes or actual underflow misses. Dynamic preparation/core/replay/output shares and target-only time are UNKNOWN. Current raw plans are already seen evidence, never fresh confirmation.

New source proof dependencies reuse existing definitions and previously checked projection/writer patterns. A4B2 uses the old Panel4 idea with a materially different B representation, width and actual caller; novelty is not claimed. Existing R13 global converter negative and R11 e5 whole1.000347/BMM1.004928 remain valid for their exact sources. Old4x10 had global A boxes and40accumulators, so its result neither proves nor disproves this new8-lane prepared layout.
