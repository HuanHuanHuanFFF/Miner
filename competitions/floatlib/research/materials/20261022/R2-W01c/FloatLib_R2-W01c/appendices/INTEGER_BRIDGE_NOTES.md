# R2-W01c：原生 UInt32 整数转换的 Model / dyadic 短桥

状态：**Lean NOT_RUN**。本环境无 `lean` / `lake`。这里只给针对固定源码核对过的全量词证明文本；尚未通过 elaboration、kernel 检查或公理审计。

## 结论

`UInt32.toFloat32` 的整数精确性不需要重新展开 `UnpackedFloat.round`、`targetExponent`、`pack`。固定 FloatLib 已有公开的

```lean
Model.ofModel_ofInt_eq_roundDyadic
  (fmt : FloatFormat) (hfmt : fmt.isIEEE = true) (n : Int)
```

以及在 `Conversion/Text/Representation.lean` 中的

```lean
Model.roundDyadicWithRounding_toDyadic?
  (hfmt : fmt.isIEEE = true) (mode : IEEERoundingMode)
  (hd : toDyadic? x = some d)
```

第一条给出整个 Model 字相等；第二条把一个已解码的有限 dyadic 舍入回同一个完整字。这里调用固定库中的证明，不移植新库。

`IntegerDyadic.lean` 的基本命题是：任意 `n : UInt32`，若一个 binary32 Model `z` 恰好解码成 `{negative := false, significand := n.toNat, exponent := 0}`，则 `Model.ofFloat32Model n.toFloat32.toModel = z`。该条件是一个精确表示见证，不是 finite 样例或性能域限制。

对 mantissa 所需区间 `2^23 ≤ n.toNat < 2^24`，直接取

```lean
z = Model.ofFields FloatFormat.binary32 false 150 (n.toNat - 8388608)
```

固定 `toDyadic?_ofFields_normal` 给出 `z` 解码为 `⟨false, n.toNat, 0⟩`。结果为全量词 `uint32_mantissa_model_decode`，无需任何浮点结果假设。

## 所有前提及其来源

| 引理 | 前提 | 本次如何满足 |
|---|---|---|
| `Model.ofModel_ofInt_eq_roundDyadic` | `fmt.isIEEE = true`；任意整数 `n` | binary32 固定描述符；`n = (u.toNat : Int)` |
| `Model.roundDyadicWithRounding_toDyadic?` | IEEE 描述符；任意模式；`toDyadic? z = some d` | `.nearestEven`；通过 normal fields 得到解码等式 |
| `Model.toDyadic?_ofFields_normal` | exponent 非零；exponent `< fmt.expAllOnesNat`；fraction `< 2^fracWidth` | exponent 固定150；`nN-2^23 < 2^23` |
| `Model.isFinite_eq_true_of_toDyadic?_some` | 有限 dyadic 解码成功 | 上述解码等式 |

没有依赖 `toReal` 相等来跳到 raw 字相等。整数桥使用已有完整字 roundtrip；原始 `normal_eq` 的乘法部分可独立使用 finite / nonzero uniqueness。

## 源码中的定义链

1. Lean4.34 `UInt32.toFloat32 n = Float32.ofModel (Float32.Model.ofUInt32 n)`。
2. `Float32.Model.ofUInt32 n = Float32.Model.pack (UnpackedFloat.ofUInt32 Format.binary32 n)`。
3. `UnpackedFloat.ofUInt32 spec n = UnpackedFloat.ofNat spec n.toNat`，后者为 `UnpackedFloat.ofInt spec (n.toNat : Int)`。
4. FloatLib `Model.ofFloat32Model_pack` 把 native packed model 对接到 descriptor `Model.ofModel`。
5. `ofModel_ofInt_eq_roundDyadic` 直接获得 nearest-even dyadic round 的完整 Model 等式。
6. `roundDyadicWithRounding_toDyadic?` 完成原 Model 字恢复。

## 固定来源

- [UInt32.toFloat32，Lean4 v4.34.0](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean#L303-L304)。Apache 2.0。
- [Float32.Model.ofUInt32](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean#L223-L224)。Apache 2.0。
- [UnpackedFloat.ofNat / ofUInt32](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/OfNat.lean#L18-L35)。Apache 2.0。
- [Model.ofFloat32Model_pack](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model.lean#L56-L60)。MIT。
- [ofModel_ofInt_eq_roundDyadic](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/Rounding.lean#L84-L108)。MIT。
- [fixed raw dyadic roundtrip](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean#L110-L152)。MIT。
- [normal fields 解码](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Fields/Proof.lean#L351-L370)。MIT。
- [dyadic ofScaledInt 定义](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Exact/Dyadic/Basic.lean#L76-L80)。MIT。

本轮新下载的 7 份源码已逐一核对 Git blob SHA1 与本会话已有固定 tree；详见 `source_manifest.json`。本目录 `.lean` 候选只有 `import ContractTensor`，官方禁止词扫描零匹配；这不代替 Lean 编译。

## 还不包含的义务

本片段不承担 UInt32 fraction mask 到 `[2^23,2^24)` 的位算术，也不承担 scale / target 的 arbitrary-word field decode。它把原生整数转换环化为单独、短小、可重用的全量词定理。完整 `normal_eq` 仍需把这两项 decode 与有限原生乘法桥、Model exact-product 定理合并。

若首次真实编译在常数定义的 `change` / `simpa only` 处失败，应只修正字段归约或显式 rewrite，不能把失败替换成新假设。若已有固定 API 未由唯一入口导入，应核查公开导入链；不可增加候选 import 或升级依赖。
