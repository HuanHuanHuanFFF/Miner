# Portable exact-dot component COST falsifier

Priority reset from D at UTC23:58: frozen mathematical sources stay unchanged. This experiment is an old ContractTensor portable primitive diagnostic. It defines no ContractExact kernel or new record, and does not claim correctness or performance before the proposed checks. D owns driver, actual caller/codegen capture, dispatch and evidence collection; broad owns the signed UInt128 exact-dot/cache baseline. Scalar owns the FP64 implementation below. Target runtime source within30–45minutes; no further proof package before cost evidence.

## Interface confirmed by D, UTC00:07

`Submission.R24PortableF64.Prepared` contains `raw : Array UInt32`, `values : FloatArray`, `maxIndex : UInt32`, `valid : Bool`. `prepare(raw)` preserves the raw array and caches exact finite values as unboxed doubles. `attemptPrepared(x,y)` returns a normal nonzero UInt32 on strict certificate acceptance, or0 as a miss sentinel; `attemptCold(rawx,rawy)` prepares both inputs then attempts. D's closed, static2argument adapters call broad's complete exact fallback on0. Public add/mul/sum/bmm remain the exact original B2 prefix. No captured Bool controls the timed callback.

D confirmed separate-operand summaries for both treatments to support row/column reuse. Broad's paired nonzero-H cache is not a free per-dot oracle: baseline primary comparison must combine two already prepared operand summaries in O(1), with the same separable H policy. Raw cold FP64 misses call the full exact path, including its cache preparation; prepared-reuse misses may use prepared exact caches, whose actual treatment-specific preparation and final drop must be reported. The e0 widening extension remains finite-oracle prototype evidence until a new source proves it.

Preparation uses direct raw-word widening: normal exponent E maps to E+896 and fraction<<29; signed zeros map exactly; nonzero subnormals use existing B2 six-stage `FastMul.fastLog2` to normalize the fraction. Exponent255 marks invalid. This is a cost implementation with finite-model validation, not an already accepted all-finite widening proof. Float.toFloat32/Float32.toFloat are absent. `FloatArray` allocation/fill, metadata scans, flags, retains and release belong to cold timing. Reuse timing prepares the same frozen inputs once per treatment outside the repeated dot loop, then includes its final drop separately.

## FP64 attempt

Require equal nonzero lengths, n≤2^30, and valid caches. Native fold is acc+x[i]*y[i] from+0. Index is max(E−1,0), including zero operands; H=maxIndex(x)+maxIndex(y)≤506. L=ceilLog2(n), computed once with B2 fastLog2, not UInt64.log2. Radius B=2^(H+2L−303) is exact normal64 via biased exponent H+2L+720. This separable H can be loose; do not replace it with exact product-H silently.

Pure-word arbitrary q uses abs64bits+2^28, >>29 and bias subtraction, then the original sum sign bit. It intentionally rounds ties upward; no accuracy premise is needed. Reject q outside normal32. Construct exact64 midpoint words from q per R's `research/controller/MIDPOINT-CERTIFICATE.md`, including the doubled lower delta at minimum normal. Compute native endpoints s−B and s+B. Require finite s/endpoints and strict order-key comparisons lower<endpointLow and endpointHigh<upper. Otherwise return0 and incur the entire lost prefix plus broad fallback. NaN/Inf/zero/subnormal proposals, cancellation, ties and overflow remain misses; source must preserve the complete fallback.

## Discriminating evidence

D will fix two new own seed groups plus directed cancellation, midpoint/tie, zeros, subnormals, extreme exponents, sign combinations and capacity misses. Compare complete cold prepare/evaluate/miss/recompute/drop against broad baseline, and separately prepared reuse/evaluate/miss/final-drop. Input generation is fixed outside per-case timing, while treatment-specific preparation remains in the appropriate boundary. Raw per-case checksums, domain/miss observations, order and process times are retained. Domain observer runs separately from measured callbacks.

Actual selected C/ASM must show the closed twoargument callback, ordinary flags, FloatArray native loads, word-only hint, endpoint/native arithmetic, strict key checks, all miss branches and fallback. No profitability inference from isolated tail cost or accepted-case counts. Native correctness/formal proof/whole-kernel adoption and actual CPU cost stay NOT_RUN/UNKNOWN until their own evidence. Stop if complete cost has no meaningful advantage; do not buy full proof or retry seeds on a failed body.
