# Reuse the public23 carrier proof if block cost is positive

The253KB source limit makes concatenating the entire accepted WordMod3 module unnecessarily expensive. Public23 already contains a compatible128-bit carrier proof backbone:

- `D8`: adding two low/high pairs preserves the integer sum modulo2^128, including unsigned carry.
- `Qsx`/`S7`: the sign extension of an arbitrary UInt64 q represents `Ye q` modulo2^128.
- `E2`: source metadata bounds each shifted decoded mantissa by2^(24+span).
- `C9`: the existing prepared product callback is the exact signed dyadic term; its proof contains the stronger parameterized magnitude bound before weakening to63bits.
- `C8`, `R5`, `I9`: existing scalar carrier, finalizer and prepared-cache interfaces.

This suggests a smaller proof boundary than replacing the whole dot theorem. Prove that folding16 sourceQhiS updates produces exactly the same UInt64 high/low pair as merging their UInt64 sum once, whenever the16 terms have absolute mass<2^63. Both carriers are canonical words representing the same value modulo2^128, so pair equality follows without imposing a new global signed128 bound. Subsequent QY6G processing, bias insertion, sentinel handling and YD finish are literally the original function.

For the actual callback, `E2` on each row/column metadata span and the new sumspan<=11 guard give product magnitude<2^59. A generic word-fold modular64 lemma plus signed uniqueness under the mass bound proves the block-sum value; it does not require both coefficients to fit UInt32. The fixed16 unroll needs a separate equality to that fold, including USize index arithmetic and proof irrelevance. Existing P/I getter and sparse-filter facts from `I9` remain necessary.

If a cost candidate warrants adoption, modify originalQPa in place rather than duplicatingQPa and the dense scheduler. Keep the old<=15 guard; select grouped processing only when<=11, otherwise invoke originalQY6G. Updating the actualI9 path around a `run_eq_QY6G` theorem can preserve the existing all12 endpoint and avoid a second complete dense proof. The current NativeOnly duplicate exists solely to buy cost evidence cheaply; it is not a formal implementation or certified source.

Proof source size, Lean elaboration cost and final exact candidate size remain UNKNOWN. No helper or full gate was dispatched by this role. Do not invest in the larger endpoint before complete native model cost shows useful headroom over the current champion.
