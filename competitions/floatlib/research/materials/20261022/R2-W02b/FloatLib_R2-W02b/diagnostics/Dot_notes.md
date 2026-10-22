# Dot.lean integration and verification notes

`Dot.lean` is a fragment for insertion in the parent's still-open `Submission` namespace, after the layout declarations. It has no import and wraps its declarations in `namespace Packed4`. The required layout declarations are `F4`, `zero32`, `zero4`, `lane`, `update`, `lane_update`, and `lane_zero4`.

## Implementation

- `dot4` accepts four separate `Float32` accumulator arguments. Every recursive step reads one native A element and one four-lane B packet. It performs four multiply/add updates and passes four scalar arguments to the next recursive call. Only the terminal branch constructs the result `F4`.
- The loop uses the same `n - k` termination measure and increasing index as `Submission.NativeFinal.dotLoop`.
- `nativeA_getD` states total-read preservation for `Araw.map ExecFloat.Binary.toFloat32`; its out-of-bounds branch checks the positive-zero conversion by definitional equality.
- `dot4_lane` takes only a deterministic B-read correspondence as its additional premise. The mapped A array is constructed directly from the original A array. It allows arbitrary starting index and accumulator values.
- `finish` preserves the original guard and fallback expression. `finish_eq_dot` uses only equality of the computed result to the parent loop result; `finish_eq_fold` reuses `NativeFinal.dot_eq`. `finish_eq_kernel_fold` exposes the same left fold using unchanged `Submission.add` and `Submission.mul`.
- `finish_dot4_lane` is the integration theorem for a zero-started lane. `finish_dot4_lane_fold` exposes the corresponding exact `ExecFloat` fold.

## Source inspection

The implementation was written after reading the supplied parent `GuardBridge`, `NativeBridge`, `FinalFinite`, and `NativeFinal` sections, including `dotLoop`, `dotLoop_eq`, `dot`, and `dot_eq`. The parent array map API was checked against the supplied Lean 4.34 source: `Array.size_map` and `Array.getElem_map` in `Init/Data/Array/Lemmas.lean`.

An independent source review checked the pinned FloatLib revision `0d91825727839f597fd06b22fdd038ea21480f0c`: `Native.lean` defines `toFloat32` through `Float32.ofBits` and `toBits32`, with `toBits32` selecting the raw word. The positive-zero construction reduces through `Configured/Value/Core`, `Model/Carrier`, `Storage/Code/Runtime`, and the transparent word constructor in `Numerics/Representations/StaticStorage`. This supports the definitional-equality proof in the out-of-bounds read branch; it does not substitute for running the compiler.

## Verification boundary

The supplied official gate's exact `BANNED` regular expression was applied to `Dot.lean`; it found no matches. The fragment contains no import line. This is a source-text check only.

The environment has no Lean/lake toolchain; no toolchain was installed. The new fragment has been reviewed structurally and against the supplied source declarations, but its elaboration and termination obligations have not been run. The recursive proof uses the same recursive-theorem pattern and measure as the existing parent proof. The aggregate file still needs the official Lean build and verifier before claiming acceptance.
