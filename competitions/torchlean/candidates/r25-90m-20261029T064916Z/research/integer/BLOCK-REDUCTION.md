# Blocked exact integer reduction: narrow body, wide final sum

Scope: original derivation against pinned `ContractExact.dotOf`; NOT a compiled
kernel, speed result or formal proof. The old standard-complement two-chain128
loop already exists. This proposal changes when sign extension/carry happens.

For finite nonzero words let the decoded integer significands be signed `sx_i`,
`sy_i`, each with absolute value below `2^24`. A zero term is zero independently
of its exponent. Prepare each body vector at its own minimum nonzero `idxOf`:
`B0 = minIdxX + minIdxY`, `S = spanX + spanY`.
The exact aligned term is

`t_i = sx_i * sy_i * 2^(idxX_i + idxY_i - B0)`, so `|t_i| < 2^(48+S)`.

If `S <= 15`, both separately shifted factors fit signed64 and their UInt64
product is the standard two's-complement encoding of `t_i`. Choose a block size
`b = 2^k` with `k + 48 + S <= 63`; optionally cap `k` for code size. Every block,
including the shorter tail, has `|sum t_i| <= sum |t_i| < 2^63`.
Its UInt64 modular sum therefore has exactly that signed64 interpretation.
Only the completed block is sign-extended and added into UInt128. With
`n <= 2^20`, the complete body magnitude is below `2^83`, so signed128 is exact.
This proof uses an absolute bound per block, not observed cancellation, the
final-sum oracle or an assumed lack of intermediate machine wrap.

Normal first-layer public MLP at seed42: `S=11`, hence `b=16`. All 243 outputs
and all 243 sparse outputs satisfy the same body bound. Their 537 terms become
34 signed128 additions. The bias is a separate exact terminal add: its signed
mantissa is shifted by `idxOf(bias)+149-B0`. The retained finite fixture check
finds that shift nonnegative and reproduces all 486 complete binary32 outputs.
The exact caller must guard negative/oversize bias shifts and preserve zero,
nonfinite and out-of-domain fallback behavior. Bias separation itself is not a
new result; it is necessary to avoid a dummy-one Cartesian range artifact.

Compared with a two-chain128 hot loop, each body MAC retains factor loads,
multiplication and a low-word addition. Carry comparison, high-word addition
and sign extension move to block boundaries. It adds block control and may
reduce instruction-level parallelism versus two independent chains. Codegen,
callback specialization, allocation, preparation, fallback and end-to-end
cost remain UNKNOWN. The arithmetic operation reduction is not a speedup.

Wide initial inputs have per-term bound 93 bits and do not enter this path.
Later sparse MLP layer1 has conservative `S=17`, so it also falls back even
though a pair-dependent oracle accepts many outputs. Do not weaken this guard
from the observed sums. The generic UInt128 route remains necessary.

Proof interface still needed: actual prepared vector getters and bounds;
UInt64 block-fold modular invariant; signed64 unique decoding under the block
bound; UInt128 merge invariant; bias encoding; original `finishWord` and
`dallNZ`/special transport into `dotFn_eq_dotOf`. Existing R24 MIT-based word
helpers may discharge parts of the modular merge; they do not supply this
new block recurrence or its actual ContractExact caller.

Next discriminating action: one public-runner C/ASM or Lean-generated loop
comparison using the same prepared source and full dot boundary for block16
versus the existing two-chain128 loop. Include preparation, terminal, fallback
and storage cost in a later caller test before deciding whole-model adoption.
