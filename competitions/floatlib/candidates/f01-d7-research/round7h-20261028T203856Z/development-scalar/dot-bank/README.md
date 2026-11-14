# Generic dot-bank whole caller

Research prototype only: UNPROVED / Lean NOT_RUN / native NOT_RUN / cost NOT_RUN.
It is not a competition matrix benchmark, new record or old BMM equivalence.

`Submission.R24GenericDotBank.exactBank/eagerBank/lazyBank` each has exactly
two raw arguments, `Array (Array UInt32)` banks A and B, and returns one owned
`Array UInt32`. Output index i*B.size+j is the selected exact dot of A[i] and
B[j], using the current Probe's explicit research policy. No function or Bool
selects a dot engine inside any hot loop.

Each whole function independently prepares every primary operand row once
inside the call, O(m+c) row-cache constructions, then iterates its concrete
prepared Probe callback over cached row pairs. Exact uses integer rows; eager
uses EagerOperand (both integer/FP rows); lazy uses FP rows. Lazy misses still
run the Probe's full exact fallback, including rebuilding its two integer row
caches per miss. That is paid work, not a free per-pair prepared context.

Output capacity m*c and every output push are inside the whole call. Cache
objects have no references in the scalar-word output and are released before
return, possibly earlier at their last use. The consumer owns the returned
array: a complete timing caller must observe/hash and release that array
before its end clock. It must pass only raw banks, not prebuilt row caches.
No cache construction, pair-preparation or output allocation may move outside
the claimed whole-call measurement. Repeated resident raw inputs describe
hardware reuse; they do not remove these per-call preparation costs.

Prerequisites and engine binding:

- Append after Root's Probe adapters, currently Adapters4ac3cf62, with
  `ExactOperand`, `EagerOperand`, `FpPrepared`, `prepareEagerOperand` and all
  three concrete prepared Probe methods. The fragment has no imports.
- Integer preparation is `R24ExactDotCost.prepareOperand`; FP preparation is
  the selected `R24PortableF64.prepare`. Probe binds the implementation at
  source composition. It may be original5bf or Tail e50; no runtime switch is
  introduced. Parent decides which exact source/hash is benchmarked.
- The intended lowest C ABI is three concrete exported functions returning
  `lean_object*` (owned UInt32 array), each taking two `lean_object*` raw-bank
  arguments. Trace each row-preparer outside the inner row-pair backedge,
  concrete two-operand Probe calls inside it, and output allocation/push and
  cache release within the whole function. This remains an expectation until
  actual selected C/ASM is captured.
- A repeated-call timing harness needs a separate external raw-bank barrier
  without LTO, then a concrete whole-bank function and output checksum/drop.
  The earlier single-pair prepared benchmark is not this frame.

The two own seeds24282601/24282603 each have n32/64/128 and rows/cols4x8,
6x12,8x16. All six cases are retained: moderate values plus directed alternating
cancellation, negative-zero rows, zero columns and opposed mixed exponent
spans. There are464 output words and44032 MACs total, below200000. Expected
results use signed integer dyadic sums and an independent per-output rational
rounding check; no Fraction loop is used per MAC and no CNN model is built.
FNV32 is only an output observer, with the full expected words retained.

No CI is requested. Compile/benchmark only on parent's decision after a
positive complete Tail pilot and before03:15 runtime freeze. A successful
finite oracle would still leave universal bank/refinement proof, target
integration, official performance and adoption unestablished.
