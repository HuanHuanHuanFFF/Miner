# R5-W02 finish 独立静态审查

状态：NOT_RUN。未执行 Lean 编译、官方 gate、生成 C 或任何计时。本记录区分用户提供的实际 C 观察、固定源码事实和候选代码形态推导。

## 1. 精确父本与最小集成边界

公开父本：

https://github.com/HuanHuanHuanFFF/Miner/blob/e5b144bf77d477919f4787e36311cf65d2a23c15/competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean

本地公开读取文件为 132965 bytes，SHA256 为 `ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630`，与用户给定一致。

`Packed10.finish` 位于父本 2671 行起。其非有限分支实际是直接写出的 `Fin.foldl`，使用原 `Araw`、`Braw`、`Submission.add`、`Submission.mul` 和 `posZero`；父本没有把这段命名为 `NativeFinal.dotFallback`。这里应保留原 fold 的表达式、原索引和原 raw 数组。

最小实现改动只需要：

1. 在 finish 中绑定一次 `u := result.toBits`。
2. 用可内联 UInt32 指数检测替换 native isFinite 检测。
3. 在有限分支从这个 u 构造 Binary32。
4. 原 else 分支保持相同。

现有 `finish_eq_dot` 的证明是 `rw [hs] <;> rfl`。替换实现后，这个定理不再仅靠定义相等成立，因此必须同时调整这一个桥证明。后续 `finish_eq_fold`、`finish_eq_kernel_fold`、lane 和输出正确性定理都通过它连接，可以保持原接口。

## 2. 惰性 fallback 是集成要求

不要把昂贵 `Fin.foldl ...` 作为普通值参数传给一个可执行通用选择函数。Lean 的执行语义会先求值实参，可能导致正常路径也计算 fallback。

可靠实现是把原 fallback 继续写在 if 的 else 分支，或使用 `Unit → Binary32` thunk 并只在 else 调用它。数学等式可以对任意 fallback 值量化；证明参数的泛化不意味着运行时代码应提前求值该 fallback。

同样，raw Binary32 构造最好放在有限分支内。只绑定 UInt32 的 `u` 到 guard 之前，避免非有限路径额外进行 Binary32 的构造。

## 3. 固定运行时源码事实

Lean v4.34.0 的 `src/runtime/object.cpp`：

- 第 1977 行：`lean_float32_isfinite` 调用 C/C++ `isfinite`。
- 第 2000 行起：`lean_float32_to_bits` 先检查 `isnan`；NaN 返回固定 `0x7fc00000`；其余值 bit_cast 为 UInt32。
- `src/include/lean/lean.h` 只对这两个函数给出外部声明。
- 同一头文件中的 UInt32 and、shift_right、dec_eq 是 static inline 的整数运算。shift_right 的位移量对 32 取模，常量 23 可直接约化。

所以 toBits 自己并不是无条件 bit_cast：它仍包含 NaN 分类与规范化工作。候选减少一个独立的 isFinite 边界调用，不等于消除了所有浮点分类成本。

源码链接：

- https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp#L1976-L2004
- https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h#L2098-L2115
- https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h#L3253-L3254

用户报告当前实际生成 C 在 finish 上有一次 isFinite 调用，有限分支再有一次 toBits 调用。本轮没有重新生成 C；候选的一次 toBits 形态仍须实际编译确认。

## 4. 调用次数推导

令 R 为执行 finish 的输出数，F 为其中 native result 有限的数量。只统计 finish 自身的这两个 runtime 边界，不包括 fallback 内部未改变的工作。

| 路径 | 原实现 | 候选 |
|---|---|---|
| 有限 result | isFinite + toBits，两次 | toBits，一次；加 UInt32 分类 |
| 非有限 result | isFinite，一次；原 fallback | toBits，一次；原 fallback |
| R 个输出总计 | R + F 次 | R 次 |

因此减少的调用数量是 F。若默认 R=5000 且 F=5000，则 finish 边界从 10000 次变为 5000 次。仅“5000 个有效输出”不自动证明所有 native result 都有限，报告中应写明条件。

这不是耗时、加速比或完整 kernel 成本模型。整数位运算、branch、raw 构造、编译器是否真正共享 u、ABI 的调用成本以及 fallback 比例都影响最终计时。不能把调用数减半换成 kernel 加速两倍。

## 5. 全域语义要求

| native result 类别 | 指数测试 | 输出动作 |
|---|---|---|
| +0 / −0 | 指数 0，有限 | 用同一个 toBits 结果，保留零符号 |
| subnormal | 指数 0，有限 | 用同一个 toBits 结果 |
| normal，包括最大有限值 | 指数 1..254，有限 | 用同一个 toBits 结果 |
| +Inf / −Inf | 指数 255，非有限 | 原 raw A/B fallback |
| NaN | toBits 规范化为 0x7fc00000，指数 255 | 原 raw A/B fallback |

证明必须连接实际 v.isFinite 与实际 v.toBits 指数，而不只断言有限输入 roundtrip。NaN 的 raw payload 不应被当作保真 roundtrip。新的 toBits 对 NaN 得到 canonical word，但这一 word 仅用于检测，不能替换原 raw fallback 的输入。

## 6. 可证与性能两层结论

在固定逻辑模型上，isFinite 由 unpack 的构造类别定义，指数全一正好分到 infinity 或 notANumber，两者均非有限；其余分支为 finite 或 zero。完整的 guard 等价应能不借助 native conversion roundtrip 获得。

性能上，这是一个值得直接接入既有真实起点的小变动：不改点积或布局、避免第二个 runtime 边界。但本记录没有实际编译或计时证据，因此不能给出胜负结论。

## 7. NativeFiniteBits 全域证明独立复核

复核对象为本轮 `nativeproof/NativeFiniteBits.lean` 的五个证明，包含将 `BitVec.eq_of_toNat_eq` 改成已逐字核对的 `BitVec.toNat_inj.mp` 的版本。本节为人工静态核对，仍非 Lean 编译结果。

- `unpack_isFinite_eq`：固定源码的指数全一分支只有 infinity / notANumber，其余分支只有 zero / finite。展开 unpack 后逐个拆 if，构造器的 isFinite 都可定义约化，`split_ifs <;> rfl` 与实际分支结构相符。包括退化 Format 宽度也未引入额外前提。
- `exponent_toNat`：`BitVec.extractLsb'_toNat` 的右侧准确是 `(x.toNat >>> s) % 2^m`；`UInt32.toNat_shiftRight` 的右侧准确含 `b.toNat % 32`。binary32 的 23/8 位字段、常量 23 取模 32，以及 255 的 toNat 都可定义约化。`Nat.and_two_pow_sub_one_eq_mod` 的方向正好把右侧低八位 mask 转成模 256。
- `exponent_allOnes_iff`：`UInt32.toNat_inj` 与 `BitVec.toNat_inj` 都以 `toNat` 相等为左边，`.mp` 方向正确。八位全一和 UInt32 的常量 255 的 `toNat` 都定义约化为 255。
- `isFinite_eq_finiteBits`：`Float32.isFinite`、`Float32.Model.isFinite`、`Float32.Model.unpack` 和 `Float32.toBits` 是有定义体的声明。最终 `change` 所需的是这些定义展开，不是新的模型一致性假设。指数是否 255 分两支后，`he` 消去模型 if、`h` 消去 UInt32 不等比较。
- `isFinite_true_iff`：由 Bool 值相等直接改写两个 `= true` 命题。

对应固定源码位置：`Init/Data/UInt/Lemmas.lean` 53、164–169 行；`Init/Data/UInt/Bitwise.lean` 37、41 行；`Init/Data/BitVec/Lemmas.lean` 131–134、1109 行；`Init/Data/Nat/Bitwise/Lemmas.lean` 537 行。以上文件均来自公开 Lean v4.34.0。此复核没有发现具体 elaboration 错误；真实固定环境仍需编译确认，并单独报告声明依赖审计。

## 8. 最小集成片段独立复核

已查看 `deliverable/candidate/FiniteBits.lean`、`deliverable/integration/Packed10Replacement.lean.inc` 和完整 `IntegratedKernel.lean` 的逐行 diff：

- `finish_expr_eq` 对全部 `Float32` 和任意 `Competition.Binary32` fallback 量化，无额外正确性前提。`change` 只做 let 展开与原 `ofFloat32` 的定义展开，随后把右侧 native guard 用全域 Bool 等式改写成左侧 guard。
- `finish_eq_original` 只是 theorem；`exact R5W02.finish_expr_eq result _` 在预期目标中推断 fallback 为原 fold，并按定义展开 finish。没有为该 theorem 引入可执行的通用 fallback 值参数函数。
- `finish_eq_dot` 新增一次 `finish_eq_original` 改写后恢复父本的 `hs` 改写及定义相等证明。定理接口未变。
- 完整 diff 中 `R5W02` 命名空间在顶层完整打开和关闭；原 finish 的 else fold 文本未变；点积、布局和输出行序没有改动。
- 通用全一值由 `-1#_` 改写为 `(-1 : BitVec spec.exponentBits)` 是为了避开扫描模式。`BitVec/Basic.lean` 175–176 的字面量宏和 49 行的 `ofNat_eq_ofNat := rfl` 证明二者定义相等，因此不是数学证明变更。这里只确认此处 lexical 修复与语义；内部扫描不能代替官方 policy 或 gate。

上述静态复核没有发现具体错误。仍未运行：核心 Lean 文件编译、完整集成文件编译、诊断中的声明依赖打印、候选 C 生成、官方 policy/gate 和计时。全域定理文本已写完整与这些运行状态是分别报告的两件事。
