# R3-W01 矩阵地址界片段

状态：`MatrixBounds.lean` 含完整证明体，无证明占位。当前环境没有 Lean/lake；elaboration、内核检查与公理输出均 **NOT_RUN**。此说明只记录源码和数学审阅。

## 使用位置

文件只 `import ContractTensor`，命名空间为 `Submission.Packed4.MatrixBounds`。可单独编译此文件；拼入最终 Kernel 时删去这一重复 import 行，其余声明可直接插入文件顶层。它不依赖父本 F4，也不定义或改动机器字循环。

## 核心声明

- `row_lt hb hi`：`b*m+i < batch*m`。
- `row_end_le hb hi`：`(b*m+i)*n+n ≤ batch*m*n`，允许 n=0。
- `point_bound hb hi hk`：`(b*m+i)*n+k < batch*m*n`，前提 k<n。
- `row_span hb hi hn`：`(b*m+i)*n+(n-1) < batch*m*n`，前提 0<n。
- `row_count_le hb hi`：`n ≤ batch*m*n`，允许 n=0。
- `nativeA_size batch m n A`：真实从 `Array.size_map` 和 `A.size_toArray` 得到映射后长度。
- `array_row_bounds batch m n nativeA hsize b i hn hAS`：结论依次是 count 可表示、baseA 可表示、最后一个行元素在 A 内。
- `native_row_bounds batch m n A b i hn hAS`：上条的 typed 原输入版本，内部已提供 `hsize`。
- `array_point_bounds ... k hk hAS`：每个实际索引同时小于 A.size 和 USize.size。

`array_row_bounds` 的三项结论可通过 `.1`、`.2.1`、`.2.2` 传给用户既有 `within`；`hAS` 本身作为第四个证据传入。所有新定义都是 theorem，除单一全局检查外不生成运行时判定。

## 数学组织

先利用 b+1≤batch 和 i<m 得到扁平 row 的上界；再将 row+1≤batch*m 乘以 n，得到整行的 exclusive end 上界。`point_bound` 只在最后一步把 k<n 加到同一个 base 上。`row_span` 是 k=n-1 的特例。因此证明无需把带变量乘法交给线性算术求解器。`omega` 只处理线性比较或 n-1 在 0<n 下的界。

## 零维和反例边界

`row_span` 必须要求 0<n：当 n=0 时，Nat 减法使 n-1=0，而待证式变为 0<0，不能成立。外层 n=0 参考分支必须保持。`point_bound` 在 n=0 时没有可供构造的 k<n 前提。

`nativeA.size<USize.size` 单独不能推出 n<USize.size。例如 batch=0、m=1、n=USize.size 时输入长度为 0。派生 n 的界使用了有效 b 与 i；空 batch 或空 m 时不存在这样的 Fin 值。不要先把巨大 n 转成 USize 再决定是否为合法快路。此片段仅在有效 b/i 和既有 0<n 快路内产生证据，未扩大最终合同前提。

## 已核固定 API

公开源码均为 Lean tag `v4.34.0`：

- `src/Init/Data/Nat/Basic.lean` 第 496 行：`Nat.add_lt_add_left (h : n<m) (k : Nat)`。
- 同文件第 757 行：`Nat.mul_le_mul_right (k : Nat) (h : n≤m)`。
- 同文件第 283、303、312 行包含 `Nat.lt_of_le_of_lt`、`Nat.lt_trans` 的实际使用/实例。
- `src/Init/Data/Array/Lemmas.lean` 第 1190 行：`Array.size_map : (xs.map f).size = xs.size`。
- `src/Init/Data/Vector/Basic.lean` 第 36 行：结构证明字段 `size_toArray : toArray.size = n`；第 39 行注册 simp。

链接：

- https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Basic.lean
- https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Lemmas.lean
- https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean

合同源为官方 commit `978cc5b445edb9943fd9953b0a9037d97a9f33a8` 的 `lean/contract/ContractTensor.lean`。父本公开文件已在本轮读取，内层布局与数值桥均未改动。
