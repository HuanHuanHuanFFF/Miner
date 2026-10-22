# R5-W01 通用矩形构造引理

状态：**NOT_RUN**。已读固定 Lean v4.34.0 实际 API；没有 Lean 编译、内核或公理输出。所有证明体已写出，没有把等价关系作为参数。

文件 `Rectangular.lean` 唯一导入 `ContractTensor`，命名空间为 `Submission.OutputRows`。它定义：

- `rowsOfFn rows cols f`：对每个行索引先构造该行的 `Vector.ofFn`，再 `Vector.flatten`。
- `rowIndex q`、`colIndex q`：把 `Fin (rows*cols)` 分解为商和余数对应的两个 Fin。
- `rowsOfFn_getElem`、`rowsOfFn_get`：逐元素正确性。
- `rowsOfFn_eq_ofFn`：构造器等于平坦 `Vector.ofFn (fun q => f (rowIndex q) (colIndex q))`。

## 精确 API

实际阅读的固定文件：

- [Vector.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean)：`flatten (xs : Vector (Vector α n) m) : Vector α (m*n)`；实现把子 Vector 转成 Array 后执行 Array.flatten；Vector.get 与 GetElem 实例按值索引定义。
- [Vector.Lemmas](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Lemmas.lean)：`Vector.ext` 接受自然数索引与界；`getElem_flatten` RHS 精确为外层商索引、内层余数索引；`getElem_cast` 不改元素。
- [Vector.OfFn](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/OfFn.lean)：`getElem_ofFn (h : i<n)` 的 RHS 是 `f ⟨i,h⟩`。
- [Nat.Div.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Div/Basic.lean)：`Nat.div_lt_iff_lt_mul`。

`Nat.pos_of_lt_mul_left` 的使用形式直接与固定 Vector.getElem_flatten 的证明一致：从 `q<rows*cols` 得到 `0<cols`；再用 div_lt_iff_lt_mul 和 mod_lt 构造两个 Fin。没有使用变量除法的 omega 猜测。

## 零维与巨大 Nat

所有引理量化任意 rows、cols；没有外部正维条件。rows=0 或 cols=0 时不存在 `Fin(rows*cols)`，逐元素命题空泛成立，Vector.ext 仍证明向量相等。

通用构造器本身对 cols=0 仍可能构造 rows 个空行；这不是新的优化承诺。完整 bmm 必须保留父本“空输出或 n=0 在准备前回参考”的分支，才能避免对巨大 Nat 空形状做无用准备。等价证明并不授权移除该分支。

所有维度和索引公式为 Nat；本片段没有进行新的 USize 转换。有限资源能否实际分配某巨大非空向量，与全 Nat 逻辑等价是不同问题。

## 与 Packed10 接线

推荐内层 `rowsOfFn m p`，其 f 行闭包先读取 rowTiles、计算 baseA，然后列闭包选择已有 tile lane 并调用父本 finish。外层对 batch 构造上述结果后 flatten，再用 `Nat.mul_assoc ... |>.symm` 作长度 cast。

可以直接用 `rowsOfFn_getElem` 证明，也可展开 `rowsOfFn` 后用两个标准 getElem_flatten 公式，与父本 `inlineDecodeC` 中的嵌套商余数逐项匹配。cast 的证据被擦除，不改变元素；flatten 可能带来额外行/批缓冲与复制，不能宣称零成本。

独立文件的 import 用于最小检查。追加父本时仅追加 namespace 内容，保留父本唯一 import，不新增模块依赖。
