# n=1 direct-row prerequisite

The opportunity is present in exactDF generated C. Actual row-specialized `DirectContinuous_output_spec__1` computes baseA/baseB once, then enters column-specialized `spec__0`. Every column directly calls `NativeFinal.dot`; its arguments still contain raw A/B, dynamic n/baseA/p and no shared native A float. There is no generated-C n=1 specialization or cross-column A conversion hoist.

`dot` initializes k=0 and positive zero, calls `dotLoop`, tests the native result and returns bits or `R7NaNReplay.replayEarly` on original raw inputs. Each `dotLoop` iteration performs dynamic k<n, A size/bounds/get/unbox/of_bits, B size/bounds/get/unbox/of_bits, multiply, add and k+1 tail-loop bookkeeping. The actual column specialization has a direct dot call and no lean_apply. A generic row wrapper with a boxed closure also exists, but it is not the actual public output path.

The input seed1224016 contains three applicable DirectContinuous n=1 cases: dense4 (p3), ml0 (p11) and specials5 (p4). Their original whole anchors sum to4.882728ms in this diagnostic. The generated source schedules410,364 redundant A decodes per one sweep compared with one decode per row. This is an operation count, not a cycle/score saving. The n=1 Cross sparse2 case is excluded.

LLVM behavior remains UNKNOWN: no exactDF dot/dotLoop disassembly was exported, and this artifact has compile/link traces but no actualDF MainFull C bytes. The nearby native assembly belongs to outer carrier8eb and is rejected as DF evidence. Recorded compile/link flags contain no flto; this still does not prove which same-unit operations clang O3 hoists or inlines.

For the proposed candidate, inspect the actual specialized column loop rather than an unused wrapper: A getD/of_bits should appear once before its column fold; sharing a Float32 through a boxed closure, lean_apply or extra allocation may offset the saving. Preserve positive-zero+fa*fb, the nonNaN guard, original raw replay inputs and the single final array. Eliminating the positive-zero addition can change signed zero.

The audit binds original DF C SHA `31e1409237ccf2e66b3b107a1ff8b3a257c9faa4e2786749c624b6aac03ccbc2`, original object SHA `e1f73d5f62be23be3ad75f948014478e8f15b75a36a35861ea2bea88c1904128`, per-function C body hashes/lines, source Kernel and original artifact index. JSON SHA `e8a1df6f0dee626bfa54f4314bac86c2277ee0161ae937531682c49af0b10036`. This was read-only; no duplicate candidate, runtime edit, build or CI was created.
