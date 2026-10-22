# R2-W02b 证明依赖与状态

## 当前状态

新增及最终定理都有完整 Lean 证明文本，无新增全局数学前提或禁止的证明占位。环境没有 Lean/lake，全部新增证明 elaboration、内核重放、公理输出与完整 gate 均 **NOT_RUN**。静态审阅不能保证编译成功；当前没有由 Lean 报告的错误目标可提供，不能虚构“已消除全部编译错误”。

## 已实际读取、原样保留的父本链

| 父本声明 | 内容 | 新候选如何依赖 |
| --- | --- | --- |
| `GuardBridge.finiteRoundtrip` | 原生转换结果 finite 时恢复原始 Binary32 | 被父本 `dotLoop_eq` 使用 |
| `NativeBridge.ofFloat32Mul` | 两个 finite 原生操作数的乘法桥 | 被父本 `dotLoop_eq` 使用 |
| `FinalFinite.add_finite_inputs` | finite 加法结果推出两个输入 finite | 被父本 `dotLoop_eq` 逆向归纳使用 |
| `FinalFinite.mul_finite_inputs` | finite 乘法结果推出两个输入 finite | 同上 |
| `NativeFinal.dotLoop_eq` | 原生尾递归的 finite 终点等于原始有序 fold | 被父本 `dot_eq` 使用 |
| `NativeFinal.dot_eq` | 最终 guard 与精确回退整体等于 ExecFloat fold | 新 `core_eq_reference` 直接使用 |
| `referenceBmm_spec` | 原参考 Vector.ofFn 的元素满足固定 bmmSpec | 新 `bmm_spec` 的最终连接 |
| `NativeFinal.sumLoop_eq`、`sum_spec` | 父本 sum 的完整有限性与回退连接 | 原样保留，不参与新 bmm 改造 |

这些声明全部在同一 Kernel 中，来源是公开父本，不是等待外部开发者提供的接口。

## 新增链

1. `vector_get_ofFn`：三层 typed cache 的读取定理。
2. `lane_packet`、`packB_get`、`packB_lane`：有效 lane 恢复原始 B 的 total read 后转换值。
3. `nativeA_getD`：A.map 的 total read，包括越界 +0。
4. `lane_update`、`dot4_lane`：任意 k、任意四个初始累加器的逐 lane 原生表达式等价。
5. `finish_eq_dot`、`finish_dot4_lane`：四路结果接入父本同一终点 guard 和回退。
6. `tileResults_get`、`tile_finish`：缓存块对应父本同一列的 `NativeFinal.dot`；用父本 `index_address` 连接 B 地址。
7. `decode_bounds`、`groups_pos_of_col`、`column_decomposition`：从 q 构造有界 b/i/g/l。
8. `outputFromTiles_eq`：任意合法 q 从结果缓存选出的 lane 等于该 q 的父本点积。
9. `core_eq_reference`：在 Vector.ofFn 下对 q 作函数外延，得到整个 Vector 与父本 referenceBmm 相等。
10. `bmm_spec`：空输出/n=0 直接 referenceBmm；其他情况使用 core_eq_reference，然后调用原样 referenceBmm_spec。

`dot4_lane` 的 hb 是明确的缓存读取等式，由 `tile_finish` 内部逐 k 用 `packB_lane` 和 `index_address` 提供。`finish_eq_dot` 的 hs 也在 `finish_dot4_lane` 中由 `dot4_lane` 提供。它们都不遗留到最终 theorem 的参数中。

## 最终精确目标

```lean
example : Competition.BmmObligation Submission.bmm := Submission.bmm_spec
```

四函数合取目标与固定 VerifyFull 一致：

```lean
Competition.Obligation Submission.add ∧ Competition.MulObligation Submission.mul ∧
  Competition.SumObligation Submission.sum ∧ Competition.BmmObligation Submission.bmm
```

待验收的是完整候选在固定工具链中的 elaboration、上述目标、内核重放和公理集合。此包没有代码占位或请求外部补入的数值 lemma。若编译产生失败目标，应保存真实首个错误，不用一份想象的 Lean 错误清单替代。

## 为什么不再需要 push 前缀不变量

结果缓存类型为 `Vector (Vector (Vector F4 (groups p)) m) batch`；每个 g 的 dot4 只运行一次。最后 `Vector.ofFn` 的类型直接给出输出长度，`outputFromTiles_eq` 为每个 q 提供实际元素等式。最终证明使用两者，不以长度相等冒充元素正确。

## 全输入边界

- `dot4_lane` 没有 finite 前提，只比较相同原生表达式和顺序。
- 最终非finite时使用原始 A/B 与父本 add/mul，不使用已规范化的 native buffer 回退。
- 无效尾 lane 不被输出读取；其状态可以非finite，证明不要求它正常。
- A 的 total read 证明适用于所有 Nat 索引。B 的有效 lane 保持原始 getD 默认 +0。
- `decode_bounds` 对任意 q : Fin(batch*m*p) 成立；空维度不存在这样的 q，无需外部正尺寸假设。
- 新实现与证明使用 Nat，不新增 USize 优化或截断条件。
