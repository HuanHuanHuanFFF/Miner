# 声明依赖与源码归属

状态：`WRITTEN_NOT_RUN`。下表依据声明正文和固定公开源码整理，不是 Lean 自动输出的依赖图或公理集合。

## 顶层链

`fromBitsTable_all` → `fromBitsTable_eq_ofBits` → `signedScaleTable_lookup` + `reconstruct_normal`。

`reconstruct_normal` → `uint32_mul_scale_eq_ofBits`，并由 `mantissa_ne_zero`、`mantissa_log2`、`exponent_bounds`、`scale_unpack_normal`、`raw_unpack_normal` 完整满足各项条件。

`uint32_mul_scale_eq_ofBits` → native model 的可展开定义、`uint32_mul_scale_toModel` 与 `float32_eq_of_toModel_eq`。

`uint32_mul_scale_toModel` → `uint32_unpack_exact24` + `mul_normal_scale_exact`。

## 本地 34 项声明

| 组 | 本地声明 | 作用 |
|---|---|---|
| 相等 | float32_eq_of_toModel_eq | 从 packed model 结构相等恢复 Float32 相等 |
| round | round_at_target, round_normalized24 | 在正确目标指数处保持 24 位正规尾数 |
| cast | ofNat_eq_round, ofNat_exact24, unpack_pack_normal24, uint32_unpack_exact24 | 归约 native UInt32 构造，明确 pack/unpack 范围条件 |
| mul | mul_normal_scale_target, mul_normal_scale_exact, uint32_mul_scale_toModel, uint32_mul_scale_eq_ofBits | 先证桥前提，再去掉乘积中的精确左移，最后 pack |
| 数值字段 | exponent_toNat, mantissa_toNat, mantissa_positive, mantissa_ne_zero, mantissa_log2 | 固定掩码、整数范围与 log2 |
| raw unpack | unpackExponent_toNat, unpackMantissa_toNat, unpackSign_toNat, fullMantissa_toNat, exponent_bounds, raw_unpack_normal | 正规 word 的完整模型解码 |
| scale | nat_and_256_of_lt, scaleWord_toNat, scale_unpack_fields, scale_raw_unpack_normal, ofBits_unpack, scale_unpack_normal | sign 不变、指数 E−23、fraction=0、canonicalization 层 |
| 表 | table_index_lt, signedScaleTable_lookup | 九位索引界与具体 Array.ofFn 查找 |
| 主结论 | reconstruct_normal, fromBitsTable_eq_ofBits, fromBitsTable_all, fromBitsTable_eq | 守卫内等式、全输入等式、函数相等 |

准确声明位置见 `declarations.json`，完整类型和证明正文以候选为准。中间引理的 hscale/hraw 不是顶层新增前提。

## 直接调用的 FloatLib 公共定理

共同固定提交：`0d91825727839f597fd06b22fdd038ea21480f0c`。

| 公共声明（namespace 前缀为 FloatLib.Floats.Formats.BinaryInterchange.Model） | 文件 | 关键适用条件 |
|---|---|---|
| round_shiftLeft | IEEE754/Native/Integer/Constructors.lean | 原 Nat 尾数非零；移位和指数补偿精确匹配 |
| roundWithAccuracy_exact_eq_round_of_le_targetExponent | BinaryInterchange/ModelRounding/Proof.lean | 输入 exponent ≤ targetExponent(totalExponent ...) |
| unpack_pack_finite_normal | BinaryInterchange/Model/Packing/Finite.lean | 位数、biased exponent 非负且正、toNat+1 严格小于 exponent 全空间 |
| unpack_pack_unpack | IEEE754/Native/Model/Representation.lean | 任意 raw bits，无额外 normal 假设 |

上述路径均以 `FloatLib/Floats/Formats/` 为文件前缀。全部为当前 pin 公共声明；不依赖后续 commit。

## 两项局部 MIT 移植

来源：[Constructors.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/Constructors.lean)。

- 原 private `ofNat_eq_round`，本地保留名称。
- 原 private `round_eq_finite_of_targetExponent`，本地改名 `round_at_target`。

这两项在本地重新给出证明体，没有引用原 private 名称。候选头与独立许可文件保留 Copyright (c) 2026 FloatLib、FloatLib Team 以及完整 MIT 许可。候选的全限定定义名称与变量名有调整，证明思路保留原来源。

## Lean v4.34.0 直接依赖

- `UInt32.toFloat32`，`Float32.ofBits`、mul 和 toModel/ofModel 的逻辑定义；`Float32.Model` pack/unpack/ofUInt32/ofBits/mul。
- `UnpackedFloat.ofNat/ofInt/normalize`、finite mul、round、roundWithAccuracy、decreaseExponent、shiftToTargetExponent、shiftToExponent。
- Format.binary32、mantissaBits、exponentBias、minExponent、targetExponent、totalExponent。
- UInt32 的 toNat 位运算、toNat 范围、toNat_sub_of_le、ofNat_toNat。
- Nat.log2_eq_iff、log2_shiftLeft_of_ne_zero、位掩码/OR 与二次幂移位引理。
- BitVec.extractLsb'_toNat、toNat_append、eq_of_toNat_eq。
- Array.getD_eq_getD_getElem?、Array.getElem?_ofFn。

所有这些使用均来自 `ContractTensor` 的传递导入。固定源文件和 SHA256 见 source_manifest.json。实际环境的可见性及 elaboration 仍待编译确认。

## 策略与许可边界

官方 gate 仅作为公开规则核对来源；未把官方工程文件收入本包。内部检查器为本次编写，其结果不是官方 policy/gate 结果。Lean 许可文本附于包中用于来源记录；没有改写任何 Lean 或 FloatLib 依赖文件。

最终依赖公理集合不能由本表替代。独立诊断文件提供实际 `#print axioms` 命令；本交付没有伪造它的输出。
