# 007 cold selection: tensor gains concentrate in specials

Independent re-reading of original run40072436647 / source `55c304b19eaab4c35de59e070bc6ae1da6d0a8d5` confirms exact3ff4,6c and41 all passed the original25-round gate without observers. Whole normalized3ff4/6c is0.8915118332519889, gain p05 is0.10550664454897736. This is one clean discovery group, not frozen independent confirmation. Complete original per-cell raw reference/submission times, work, normalized ratios, source dependency lines and accounting are in `scalar-007-audit.json`.

The apparent sum/BMM aggregate improvement is not uniform over their unchanged ordinary loops:

| Operation | Whole operation ratio | specials ratio | Other cell ratios |
|---|---:|---:|---:|
|sum|0.934342|0.484515|1.0050–1.0858, all slower|
|bmm|0.847705|0.281766|0.9815–1.0063, near1|

There is a real source dependency despite the tensor definitions being byte-identical. Public sum enters R7SinglePassSum.run and its machine/nat loop. On the first raw NaN input it calls `Submission.add (ofFloat32 acc) q`, then switches to R7SumRepair.suffixLoop. The new cold add changes that repair transition; the suffix itself uses the pre-existing R7W02.step and is not repeated scalar-add savings. The ordinary prefix runs native arithmetic directly. The original6c actual C corroborates this dependency: `R7SinglePassSum_loop___redArg` C40508–40715 contains the actual TunedAdd_add cold call at40583 followed by suffixLoop at40584.

For BMM, NativeFinal.dot and packed finish helpers reject a native NaN endpoint and enter R7NaNReplay.replayEarly→replayLoop→replayStep. That step calls exported Submission.mul and then Submission.add, so their new NaN-result branches can reduce replay cost. ReferenceBmm also uses both exported operations on its fallback path. Normal native/packed inner loops do not call those scalar wrappers per MAC. The entire source tail starting at the original public mul dispatcher, including tensor bodies and dispatch, was freshly checked byte-identical to6c; unchanged bodies do not make their changed callees performance-independent.

Raw candidate/reference drift is small: each corresponding reference cell ratio lies in0.995265–1.005526. Large submission reductions concentrate in add:specials(0.26020 raw), sum:specials(0.48348 raw) and bmm:specials(0.28168 raw); this pattern does not support one large uniform frequency scaling shared by reference and submission. No CPU frequency counters were recorded, so system effects are still UNKNOWN.

Using the exact whole-score normalization, four specials cells account for9.7409 percentage points of the observed10.8488-point net whole gain: add4.8402, mul0.8984, sum0.5742 andbmm3.4281. This is arithmetic attribution of **observed scores**, not proof that NaN selection caused precisely that share. Non-special mul also improves2.3–9.5% after normalization despite retaining its finite expressions; ordinary sum regresses. New3ff4 C/asm, hot/cold inlining, linked layout and instruction/cache/cycle shares were not captured in this clean run and remain UNKNOWN. Do not label these residual movements new scalar or tensor mechanisms.

The result supports the cold dependency explanation and retains all slower cells. It does not justify attributing the full10.8% to NaN selection or inheriting an independent confirmation result. Cold+59de interface/capacity work was initially kept in memory only; its separate preflight records248144B/7856B headroom and two independent composition orders agreeing, while combined acceptance/performance stay NOT_RUN/UNKNOWN until the newly authorized complete combination is gated.
