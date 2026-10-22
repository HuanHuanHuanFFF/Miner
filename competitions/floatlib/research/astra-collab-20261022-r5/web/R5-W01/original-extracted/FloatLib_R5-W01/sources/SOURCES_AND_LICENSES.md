# Sources and licenses

All source reads for this request used the fixed public files listed with complete URLs, byte counts and SHA256 values in `source_manifest.json`.

The parent is `HuanHuanHuanFFF/Miner` at commit `e5b144bf77d477919f4787e36311cf65d2a23c15`, path `competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean`. Its exact 132965 bytes have SHA256 `ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630`. Relevant Packed10 preparation, finish, output and proof definitions were read directly. Three previous full gates are user-provided feedback, not rerun evidence.

Lean sources use fixed tag v4.34.0. Reviewed APIs: Vector.flatten/ofFn/cast/get, Vector.ext/getElem_flatten/getElem_cast/getElem_ofFn, Array.ofFn/append/flatten, and Nat.div_lt_iff_lt_mul. The exact use of Nat.pos_of_lt_mul_left matches the fixed Vector.getElem_flatten proof.

Official ContractTensor and gate.py are from `978cc5b445edb9943fd9953b0a9037d97a9f33a8`. Only the fixed gate's BANNED regular expression was extracted and applied locally; the gate was not imported, executed, or changed.

FloatLib remains pinned to `0d91825727839f597fd06b22fdd038ea21480f0c`. Its numeric sources were not freshly downloaded in this narrow task. Existing parent definitions and proofs are reused, not postulated as new assumptions.

The complete original parent license block is copied unchanged to `PARENT_NOTICES.txt`; it contains MIT notices for Conjectures.io, FloatLib and TorchLean. The compose script preserves the parent's original license block. Lean source headers specify Apache 2.0; its implementation is not redistributed in this package. See https://github.com/leanprover/lean4/blob/v4.34.0/LICENSE .

Newly written snippets, scripts, report and analytical fixtures are provided under the accompanying MIT license. This does not change any upstream license.
