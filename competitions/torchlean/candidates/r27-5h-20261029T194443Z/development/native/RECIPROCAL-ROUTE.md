# R27 high-ceiling norm route: one reciprocal per row

Created2026-10-29 20:00 UTC. Source12 `Ya7G` (line1921) performs up to six quotient/remainder expressions by the same denominator `D = nU * Yf dw`, per output element. `dw` and nU are constant across a normalization row; denominator preparation belongs inside the timed kernel and can be amortized across n columns. `rrsG` also divides, but this proposal initially leaves its final rounding untouched.

**Mechanism:** prepare `R = floor((2^64 - 1) / D)` once per row. For unsigned a and D>0, let `q0 = high64(a * R)`, `r0 = a - q0*D`. Then `q0 <= floor(a/D) <= q0+1`, `r0 < 2*D` as mathematical integers, so `q = q0 + (D <= r0)`, `r = if D <= r0 then r0-D else r0`. Products q0*D and mathematical remainder fit64 because q0*D <= a <2^64; exact remainder can have r0≥2^64 if2D>2^64, but r0<=a still ensures it fits. D=0 needs the exact UInt64 division-by-zero semantics branch.

The proof bound follows directly from `R*D <= 2^64-1 < (R+1)*D`: `a*R/2^64` cannot exceed a/D, and `(a/D)-a*R/2^64 <1` because `(2^64-R*D) <= D` and a<2^64. No approximate numerical proof or FP premise involved.

**Why potentially larger:** replace variable64 divisions/remainders inside every output with exact64 multiply-high plus one correction, keeping a single setup division per row. `Ya7G` has repeated q/r pairs (`cv`, then `r0`, then `ra`) so refactoring each pair through an inline tuple may share one multiply. Full model fraction, actual compiler div/rem fusion and gain UNKNOWN; obtain one layer profile/generated ASM before promoting.

**Proof/helper interface useful from R if capacity exists:**

1. Self-authored `mulHigh64 : UInt64 → UInt64 → UInt64`, implemented from four32-bit partial products (no extern/UInt128 assumption), theorem `toNat(mulHigh64 a b) = a.toNat*b.toNat /2^64`.
2. Exact `divRem64 a d reciprocal`, theorem at `reciprocal = UInt64.max /d` that outputs equal `(a/d,a%d)` for every UInt64a,d. Handle d=0 by original operation, d=1 by normal correction.
3. New `Ya7G` runtime body reconstructed from exact official source by replacing only three q/r pairs, and equality theorem via helper rewrites. Row setup computes the same denominator once and passes reciprocal. Actual12 correct then follows old `Ya7Ge`/`Zdt`.

Dimpl will prepare own finite arithmetic/native prototype and exact reconstruction patch. This remains independent of R's packed output and blocked MAC routes. Parent may assign a small proof helper through existing files; no direct message requested/used. No whole-source publication or local native build.
