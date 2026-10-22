# R5-W01 Packed10 接线说明

## 交付状态

`Packed10OutputRows.inc.lean` 是追加片段，不是独立模块。先追加通用 `Rectangular.lean` 的 namespace 内容（去掉它的 import），再追加本文件。父本唯一原 `import ContractTensor` 保留；父本 add/mul/sum、数值桥、十路循环和所有原证明均不改。

该片段有完整实现与证明体，没有外部正确性假设或占位。**Lean elaboration、kernel checking、公理检查及 gate 均 NOT_RUN**。它不能被称为已编译候选。

## 实际核对的父本

- commit：`e5b144bf77d477919f4787e36311cf65d2a23c15`
- 文件：`competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean`
- 固定 SHA256：`ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630`
- 字节数：132965。
- 实际阅读：Packed10.groups、groups_pos_of_col、vector_get_ofFn、packB、finish、tileResults、inlineDecodeC、outputFromTiles、core/core_eq_reference，以及 Submission.bmm/bmm_spec。

父本真实 `inlineDecodeC` 的列坐标为 `(q % (m*p)) % p`，不是直接在源码中写 `q % p`。两者在合法索引下可证明相等；本片段直接使用同样的嵌套坐标，从而不需要额外变量除余数重写。

## 一条固定实现路线

1. A.toArray、B.toArray 在整个输出构造器外提。
2. 每个 batch 取一次 batchTiles，并构造 aBatch=b*m、bBatch=b*n*p。
3. 每行取一次 rowTiles，并计算 baseA=(aBatch+i)*n。
4. 行内 `Vector.ofFn` 只需 j/10、j%10、该组 get、lane、原 finish；不重新调用 dot、tileResults 或 packB。
5. `OutputRows.rowsOfFn m p` 先物化 m 行，再 flatten 为该 batch 的 m*p 个结果。
6. 外层 batch Vector 再 flatten，最后用 `Nat.mul_assoc` 的类型 cast 从 batch*(m*p) 转为 batch*m*p。

`cast` 只调整 Vector 的长度类型证明；固定 Vector.cast 源码保留同一 toArray。没有显式整数截断或新机器字地址。

## 证明依赖

`outputRows_eq` 对 **任意**给定 tiles 成立，不要求其等于 tileResults，也不要求任何 lane finite。通过 Vector.ext 对每个合法输出 q 证明完整 finish 表达式相同，包含 raw A/B 地址，因此并非只证明长度或普通 finite 快路。

由合法 q 推出 p≠0、m*p≠0，只用于展开父本条件式 decode；它们是逐元素证明中的局部推导，不增加最终规格前提。随后用实际 Lean 4.34 的 Vector.getElem_cast、getElem_flatten 和 getElem_ofFn 化简，双方所选 Fin 值和 finish 参数相同，索引证明由证明无关性处理。

`coreRows_eq`：相同 nativeA、packedB、tiles 准备后直接应用 outputRows_eq。

`coreRows_eq_reference`：传递接上原 Packed10.core_eq_reference；不重做数值证明。

`bmmRows_eq_reference`：保留原空输出和 n=0 的前置参考分支，非空分支应用 coreRows_eq_reference。

`bmmRows_spec`：由 bmmRows_eq_reference 重写到原 referenceBmm_spec，量词仍为任意 Nat 维度和全部原始 Binary32 输入。整个追加片段不依赖原 Submission.bmm 的声明顺序。

## 启用边界

追加这些定义不会自动改变现有 `Submission.bmm`。它给出可直接调用和验证的新入口 `Submission.Packed10OutputRows.bmmRows`。完整候选启用时，需让原入口的非空核心分支使用 coreRows，并相应使用 coreRows_eq_reference；或者在候选整理阶段将新入口接到正式要求的 bmm 名称。不要只追加片段后仍对旧入口计时，再声称测到新构造器。

## 零维与成本

等式证明允许 batch=0、m=0、p=0；此时没有合法输出索引，Vector.ext 的元素义务为空。n=0 不影响输出排列等式。用于完整调用的 bmmRows 在准备前返回原参考，因而不会为巨大 batch 配 m=0 的空输出物化大量空行。单独直接调用 outputRows 则仍可能构造这些空中间数组，不能把其运行费用与外层提前返回混淆。

本路线有两级标量 flatten：行结果复制进 batch 数组，再复制进最终数组。默认形状产生100个长度50的行数组、2个长度2500的 batch 结果数组，再得到5000元素结果；额外遍历输出元素两次，另有收集行/批数组引用的中间容器。不能从这些源级计数推定物理内存指令、引用计数次数、实际分配复用或速度。

完整调用仍包括准备、转换、tileResults、finish 及可能 raw 回退、中间缓冲构造/释放、最终输出。禁止只计行内 finish 子段，也不能遗漏新 flatten 成本。

## 最需要编译确认的具体边界

未获得编译器错误输出；以下是首次编译的关注点，不是已观察失败：

- outputRows_eq 中一次 `simp only` 是否在当前导入闭包中完成依赖 Fin 证明的化简。
- `OutputRows.rowsOfFn` 与父本 namespace 的解析，以及 fixed Vector.ofFn/flatten/cast 的实例推断。
- 三允许公理输出与整合后单文件词法/字节政策。

若第一项未闭合，剩余数学目标应是同一个 q 下两侧完全相同的 finish/tiles.get 表达式，而不是新的数值或乘法理论；应将实际 Lean 目标保存再局部修复，不引入额外 sound 参数。
