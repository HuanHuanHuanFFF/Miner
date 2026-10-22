# R2-W01c：固定 pin 的精确表示桥审计

## 结论

**无需移植较新库。** 固定 FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c` 的 `Conversion/Text/Representation.lean` 已有完整的 `roundDyadicWithRounding_toDyadic?`、nonzero 特例和有限非零表示唯一性定理。较新 commit `1f5771b3e36a98f17fcac2c6d76aaa024b36aa37` 将同一段证明搬到 `DirectedSemantics/Exact.lean`，原 Text 文件成为只转导入 Exact 的薄文件。两个版本的七定理块逐字相同，UTF-8 长度 6,615 字节，SHA256 为 `a1534622adfdb290ef9af0a3985dbf98a4279444f626aa40d703c73cd2780dac`。

这是源代码事实，不是 Lean 编译结果。本环境未发现 Lean，所有本轮新片段的编译状态是 **NOT_RUN**。

## 1. 已固定的来源与许可

固定表示文件：

https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean

较新 Exact：

https://github.com/lean-dojo/FloatLib/blob/1f5771b3e36a98f17fcac2c6d76aaa024b36aa37/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean

较新 Text：

https://github.com/lean-dojo/FloatLib/blob/1f5771b3e36a98f17fcac2c6d76aaa024b36aa37/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean

两版仓库 LICENSE 的 Git blob 都为 `e58f952dfd0b19ccef5061920b3af3d76a111f3f`，内容为 MIT，`Copyright (c) 2026 FloatLib`。源文件头同样说明 MIT 和 FloatLib Team。此次无需复制这七个定理到候选；直接使用固定 pin 已导出的名字，因此新增库证明字节为零。`sources/` 保留原件，`source_manifest.json` 记录 commit、URL、Git blob、UTF-8 字节数与 SHA256。`source_audit_result.json` 记录逐字对比结果。

## 2. 唯一导入 ContractTensor 的可见性

从已核公共文件可追到全部公开导入链：

1. 官方 `ContractTensor.lean` → `Contract.lean` → `FloatLib`。
2. `FloatLib` → `FloatLib.Floats` → `FloatLib.Floats.Formats` → `BinaryInterchange`。
3. `BinaryInterchange.lean` 第 37 行公开导入 `Configured`。
4. `Configured.lean` 第 22 行公开导入 `Conversion.Text.Roundtrip`。
5. `Conversion/Text/Roundtrip.lean` 第 10 行公开导入 `Conversion.Text.Representation`。
6. 固定 `Text/Representation.lean` 的定理处在 `@[expose] public section`。

因此不必改变候选唯一导入，也不必升级依赖。未把这个源级可见性审计描述成实际 elaboration 成功。

## 3. 固定表示桥的逐条前提

以下名字在 `FloatLib.Floats.Formats.BinaryInterchange.Model` 命名空间内。

| 定理 | 前提 | 结论及使用边界 |
|---|---|---|
| `cexp_toDyadic?` | `toDyadic? x = some d`，`d.significand ≠ 0` | 非零 decoded dyadic 的规范指数等于 `d.exponent`。 |
| `toDyadic?_exponent_eq_of_toReal_eq` | x、y 都有 decoded dyadic；二者 coefficient 非零；`toReal x = toReal y` | 二者 decoded 指数相等。 |
| `Dyadic.toReal_eq_zero_iff` | 任意 dyadic d | `d.toReal = 0 ↔ d.significand = 0`；不能恢复零的符号。 |
| `eq_of_toReal_eq_of_nonzero` | x finite；y finite；数值相等；x 的数值非零 | **完整 Model 等式**，包括整个字。正负零不能经此桥合并。 |
| `roundDyadicWithRounding_toDyadic?_of_nonzero` | `fmt.isIEEE = true`；任意 IEEE mode；`toDyadic? x = some d`；coefficient 非零 | 对该 decoded dyadic 舍入返回完整 x 字。 |
| `roundDyadicWithRounding_zero` | IEEE fmt；任意 mode；任意负号、指数 | 精确零舍入保留负号。此次 normal 路线不使用它。 |
| `roundDyadicWithRounding_toDyadic?` | IEEE fmt；任意 mode；`toDyadic? x = some d` | 包括 signed zero 的完整 decoded-word roundtrip。它不能直接接受任意数值相等但未规范化的 dyadic。 |

后一限制很关键：normal 乘积的 dyadic 是 `(s, M·2^23, E−173)`，目标字解码为 `(s, M, E−150)`。二者的实数值相等，结构不相等；不能把 raw roundtrip 的 `hd` 直接填成未规范化乘积。

## 4. 更短的 Model 乘法闭合

`ModelExactProduct.lean` 给出四个原创新片段，合计 2,760 字节（交付时以文件本身为准），唯一导入 `ContractTensor`，无占位证明。**仍是 NOT_RUN 草稿。**

关键通用命题为：给定 IEEE fmt 和同格式的 x、y、z，若 x、y、z 全部 finite，`toReal z ≠ 0`，且

`toReal x * toReal y = toReal z`，

则 `Model.mul x y = z`。

证明不是将实数等式强行提升成位等式，而是依次：

1. `abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite z` 给出目标字的幅值界。
2. 由 `abs_mul` 与数值乘积等式，该界就是 x、y 的精确乘积幅值界。
3. `isFinite_mul_of_abs_mul_le_posMaxFinite` 排除运算结果 Inf/NaN。
4. `toReal_mul_eq_roundAt` 连接执行的 Model 乘法与 RN-even。
5. `roundAt_toReal_eq z hz` 表示有限已存字的数值舍入不变。
6. `eq_of_toReal_eq_of_nonzero` 同时使用乘积 finite、z finite、数值相等、非零，得到完整 Model 字等式。

这种表示把“结果可表示”的证据直接选为目标 z。本题无需单独证明 `M·2^23` 的归一化、舍入位或目标指数，也无需再证明最大有限值的显式实数公式。E=254、M=2^24−1 的最大有限边界使用非严格幅值界，仍然成立。

### 三 decode 接口

`binary32_mantissa_scale_mul` 的全部前提为：

```text
x,y,z : Model binary32
s : Bool; M,E : Nat
M ≠ 0
toDyadic? x = some (false, M, 0)
toDyadic? y = some (s, 2^23, E−173)
toDyadic? z = some (s, M, E−150)
```

结论：`Model.mul x y = z`。

这里没有另外隐藏 normal 域或假设完整 `normal_eq`。证明各 decode 本身是具体转换层必须完成的工作；任意 fractional word、sign、指数的全量证据应由调用处交付。父任务正在把这些字段证据与原生桥连接。

通用 dyadic 值恒等式是

`(false,M,0).toReal · (s,2^k,e).toReal = (s,M,e+k).toReal`。

它通过按 s 分两支、实数整数幂加法律、交换结合的环等式证明。此处只用于精确数学语义；没有重排待测 ordered sum 的任何加法。

## 5. 本轮反例压力点

- **仅有 `toReal` 等式，且未排除异常值和零，不能恢复完整 word。** Model 的总 `toReal` 把 NaN/Inf 映到零；不同异常字和零可能有相同的总数值。本接口显式满足所用库定理的 finite 前提，不声称这些前提在逻辑上彼此独立：若仍保留目标数值非零和精确乘积数值等式，反而可以从总 `toReal` 的定义推导各值 finite。
- **去掉 nonzero 不能成立。** +0 和 −0 的实数值相同而完整字不同。三 decode 的 `M ≠ 0` 是实际使用前提。
- **混淆 scale 的数学指数与 decoded 指数会错。** 表中所指的 `±2^(E−150)` 解码系数为 `2^23`，其 dyadic 指数是 `E−173`；不能仍填 `E−150`。
- **仅把 `roundDyadic_of_representable` 的数值结论看成位等式会漏义务。** 此片段显式完成有限性和非零，并调用已有完整表示唯一性。
- **不能省略原生最终桥。** 片段结论目前是 Model 等式；父任务的 NativeBridge 还需把 native 乘积、目标原始 word 与这些 Model 连接。本片段没有声称已经独立完成 `normal_eq`。

## 6. 实际证据与停止条件

已执行：固定/较新公开源码获取；每份本地 source 与工具返回 Git blob 的字节校验；七定理块逐字对比；候选唯一导入和官方禁止词正则静态扫描。

未执行：Lean elaboration、内核检验、允许公理集合检查、官方 gate、性能计时。状态均为 **NOT_RUN**；本任务没有启动新 C 实验。

这条小桥不需引进任何较新库依赖。若父任务的字段/原生转换衔接仍未完成，准确停止点应写成那几个普遍 decode 命题，而非再把固定 pin 的表示唯一性当成缺失。停止扩展较新库移植调查，因为它已被固定 pin 的可见同名证明完全取代。

## 7. 补充固定源码链接

- Model rounding identity / finite grid: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean
- Finite multiplication semantics: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean
- Largest-finite bound: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Basic.lean
- Public umbrella path: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured.lean
- Public text path: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Roundtrip.lean
- Fixed license: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/LICENSE

