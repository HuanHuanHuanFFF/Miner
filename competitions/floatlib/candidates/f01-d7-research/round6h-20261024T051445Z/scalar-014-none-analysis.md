# 014 None-result reuse: mechanism verified, incremental gain unconfirmed

Original run40078982864 / source `c66f3c0605ae4eedf076b3e4ccec8eee397d8baf` passed the complete25-round gate for41,6c,df5c and42c. The exact new proof chain and four obligations therefore remain an accepted source/mathematical asset. The incremental same-run42c/df5c normalized ratio is0.9955890614419147 with gain p05=-0.004759772255111394. Keep **PARK**; the favorable42c/6c primary result includes the parent mechanisms and is not evidence of a new increment. No follow-up variant, resampling or Column4 fusion was made.

| Same-run42c/df5c operation | Normalized ratio |
|---|---:|
|add|0.99463|
|mul|1.01127|
|sum|0.95662|
|BMM|0.97540|

All40 files in the original capture directory were rehashed against the original artifact index. Exact compiled42c matches the requested source. MainFull C SHA is `ac44997c152fa05ad2487bac591814a28b87b2fc3d4377706edec8059520f43a`; object SHA is `370e1bbeac4d4bde08cd8db00558362579f7f8568b6c94eaa4134ccd7a359217`. C/trace/nm/relocations/selected assembly remain bound to this original gate's statement capture, using immutable c124/fd17 helpers. Private ELF was removed. Final linked binary bytes were not retained. Detailed hashes, raw timings, bootstrap and exact function ranges are in `scalar-014-none-analysis.json`.

The active public BENCH_PLAN path still uses MainFull add lam0 and mul lam3 through their boxed adapters; all11 MainFull selected symbols were captured. Add is359B and public mul1172B. These sizes are observations, not an incremental parent size comparison: same-run df5c C/object/asm was not captured. Older59de/6c objects cannot establish that None alone added a particular save, spill or layout cost.

The intended mechanism really appears in the actual caller. Add computes addss once at0xbb, self-classifies at0xbf, then enters integer raw priority at0xd2. A None selection returns through0xc4 to the same to_bits tail relocation0xce using the existing xmm1 result. Multiplication computes the native product once at0x2ad, self-classifies at0x2b1, then enters raw priority at0x3fb. None branches0x458/0x481 jump to0x2ba and the same to_bits tail0x2ca. Neither cold None route repeats native arithmetic or input conversions.

Some selection remains direct integer word priority and quiet-bit setting: add returns selected left/right words at0x158/0x135, mul at0x487/0x45e. No Option heap construction appears in these captured bodies. This is caller instruction evidence, not a cycle allocation profile of every runtime primitive.

The common numeric/numeric warm path still has no float spill/reload. Converter misses retain the existing float stack roundtrip: add second-input miss at0x7c/0x87, mul at0x234/0x23f. Mul also retains five GP callee-save pushes and16B stack reservation. Without parent machine code, their *incremental* change is UNKNOWN. LowScale still branches before the numeric converter guards; its unchanged compiled machinery contains a softwareMul backend relocation at0x25c. That is distinct from the new native-NaN None path, so not all backend work disappeared from the full function.

Several controls limit interpretation. Non-special mul cells regress about0.1–2.3%; BMM specials/extremes improve strongly in this sample. Non-special sum cells improve roughly2–5% even though they never execute the new None result return. Sum's first raw-NaN repair must selectSome, so it is not a None-hit gain. Changed cold code can still affect inlining/layout, and system/reference movement exists; the actual tensor-helper machine bodies were omitted by the20-symbol scalar budget. Tensor-specific spills, branch cycles and exact causal gains remain UNKNOWN. Keep all these slower and unmodified-control movements in the record.

The retained result is a fully accepted exact None/native bridge and verified reuse of the already computed result in real MainFull callers. Stable whole-source incremental performance was not established. The parent df5c remains the comparison source; this audit changes no frozen source, helper, Git/CI state or adoption/model result.
