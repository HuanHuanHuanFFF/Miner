# 声明依赖与来源

状态：NOT_RUN。下表是按固定源码核对的显式声明依赖，不是 Lean 输出的递归公理清单。

## 新声明

| 声明 | 性质与依赖 |
|---|---|
| `R5W02.finiteBits` | 可执行 UInt32 右移、按位与和 Bool 不等比较 |
| `unpack_isFinite_eq` | 对任意 Format、raw BitVec 展开 `UnpackedFloat.unpack` 与 `UnpackedFloat.isFinite` 的完整分类 |
| `exponent_toNat` | `unpackExponent`、`BitVec.extractLsb'_toNat`、`UInt32.toNat_toBitVec`、`UInt32.toNat_and`、`UInt32.toNat_shiftRight`、`Nat.and_two_pow_sub_one_eq_mod` |
| `exponent_allOnes_iff` | 上一引理；`UInt32.toNat_inj.mp`、`BitVec.toNat_inj.mp`；闭数值的定义规约 |
| `isFinite_eq_finiteBits` | 前述分类与指数桥；公开 `Float32.isFinite/toBits`、`Float32.Model.isFinite/unpack`；UInt32 的标准 LawfulBEq 简化 |
| `isFinite_true_iff` | Bool 等式直接改写 |
| `ofBits32_toBits_eq_ofFloat32` | FloatLib 公开 `ExecFloat.Binary.ofFloat32` 定义；rfl |
| `finish_expr_eq` | guard 等式；let 与 ofFloat32 定义展开；没有 fallback 前提 |
| `Submission.Packed10.finish_eq_original` | 实例化 `finish_expr_eq`；只存在于证明中 |
| `Submission.Packed10.finish_eq_dot` | 上一桥，再使用父本原来的 hs 改写与 rfl |

候选中未引入新的类型类假设或语义假设。泛型 unpack 引理中的 Format/bits 是普通量化参数；不存在需要外部补齐的正确性条件。

## 固定源码位置

- Lean `src/Init/Data/Float/Float32.lean`：145–146 toBits；265–266 isFinite。
- Lean `src/Init/Data/Float/Model/Float32.lean`：47–48 unpack；184–185 isFinite。
- Lean `src/Init/Data/Float/Model/Unpacked/Pack/Basic.lean`：74–76 unpackExponent；90–109 unpack 分类。
- Lean `src/Init/Data/Float/Model/Unpacked/Operations/Status.lean`：20–24 UnpackedFloat.isFinite。
- Lean `src/Init/Data/BitVec/Lemmas.lean`：134 toNat_inj；1109–1110 extractLsb'_toNat。
- Lean `src/Init/Data/UInt/Lemmas.lean`：53 toNat_toBitVec；168–169 toNat_inj。
- Lean `src/Init/Data/UInt/Bitwise.lean`：37 toNat_and；41 toNat_shiftRight；这些声明由同文件标准 UInt 宏生成。
- Lean `src/Init/Data/Nat/Bitwise/Lemmas.lean`：537 and_two_pow_sub_one_eq_mod。
- FloatLib `FloatLib/Floats/Formats/IEEE754/Native.lean`：62–65 ofBits32；120–122 ofFloat32。
- 官方 `lean/contract/Contract.lean`：17 定义 `Competition.Binary32`。
- 官方 `lean/contract/ContractTensor.lean`：仅通过 Contract 引入 FloatLib；候选仍只 import ContractTensor。

每个文件的完整固定 URL、SHA256 与字节数见 `source_manifest.json`。

## 编译与公理检查

`simp`、`rw`、`split_ifs` 等沿既有 ContractTensor 导入环境使用，未增加 import。公开父本本身已有 `split_ifs` 用例。所有新定义与引理仍需目标环境 elaboration 和 kernel 检查。

`diagnostics/Commands.lean.inc` 是独立诊断命令尾部，需与临时候选副本拼接后在原环境运行。它会打印关键桥与最终 sum/bmm 定理的公理依赖。允许集合只有 propext、Classical.choice、Quot.sound；本轮并未实际取得打印输出，不将源码中没有新声明等同于递归依赖已审计。

## 许可与复制范围

Lean 固定源：Apache 2.0；FloatLib 固定源：MIT。原父本自带 Conjectures.io、FloatLib 等通知，完整保留在集成候选和 `LICENSES/ParentNotices.txt` 中。实际复制的父本 finish/fallback 小段受这些通知覆盖。

新小桥使用公开定义与引理，未移植私有证明。附录并未包含 Lean 或 FloatLib 的大量完整源文件；来源清单提供精确固定链接，许可证原文随包提供。
