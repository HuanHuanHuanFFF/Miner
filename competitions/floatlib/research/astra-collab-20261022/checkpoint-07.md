# R2-07 — raw-word finite guards, ready as the next scalar component

Responds to D's explicit checkpoint request to freeze the raw-word finite predicate follow-up while the current three layout/fold candidates and D index repair receive statement feedback.

Frozen source: `competitions/floatlib/candidates/f01-r2-word-finite-guards/Kernel.lean`, SHA `1c0f8496c85fb3a4e84494ac1708576b048a183e90eb8bbc1b62eb5375d5ab6e`, 59474 bytes. Parent is full-gate-passed final-finite86312a37. Exact upstream lexical policy PASS; new Lean bridge NOT_RUN.

The scalar add/mul wrappers inspect the raw UInt32 exponent before converting, instead of calling native Float32.isFinite twice. The raw Model dyadic-decoder proof establishes finiteness of the native conversion. Existing finite native add/mul and finiteRoundtrip close the exact scalar obligations; final-finite sum/bmm loops are unchanged, and their software fallback uses the new exact wrappers. Finite-input overflow remains on the native fast path. Nonfinite inputs still use the original software operations.

Minimal request: statement feasibility, followed by exact full gate and paired scalar class timing only if it passes. Inspect scalar generated C for removal of lean_float32_isfinite, retaining bit conversions and separate exact operations. D remains the sole dispatcher. R's fragment and generator are in this directory; no extra local toolchain or job was launched.

The optional tiny-product software/native hybrid is now lower priority: fresh same-run no-raw candidate has mul:tiny0.946486 vs shipped, removing the old regression. Do not revive the hybrid from old native-both data without a new current-wrapper comparison. Detailed bounded reasoning is in scalar-guard-analysis.md.

Web R2-W03's original package has been delivered in R2-06. Its follow-up R2-W03b is actually running in the same GPT6 Pro chat, focused on closing the full signed-table conversion proof; two other web routes continue. Downloads and local experiments proceed independently.
