# 直接路径复用连续 writer

状态：DESIGN / NOT_COMPILED / NOT_BENCHMARKED。本稿不生成 Kernel 包，不改变当前冻结 proof2。

## 实质变化

当前 a066 的短 n、多列分支已经按行共享地址，但仍构造行号 Vector、每行 Vector，再 flatMap。当前 p≤2 的 DirectSmall 则逐输出解码。一个共同的直接 writer 可以按平面行 r 遍历，固定 baseA=r*n 和 baseB=(r/m)*n*p，再把 p 个原 `NativeFinal.dot` 结果直接 emit 到预分配的最终 Array。

它保持每个输出的原始字读取、从正零开始的原始 mul/add 顺序及独立 NaN 回放。直接路径本来不使用 F10，因此此处没有把完整 F10 点积按输出重复计算的问题。

```lean
namespace Submission.DirectContinuous
open FloatLib.Floats Competition

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  RowStream.emit p (fun j =>
    NativeFinal.dot n baseA (baseB + j.val) p A.toArray B.toArray) out

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  Fin.foldl (batch * m) (row batch m n p A B)
    (Array.mkEmpty (batch * m * p))
```

这里代码是待验设计，未写入任何候选 Kernel。还需补 row_prefix/output_prefix、Vector 包装和以下连接后才构成完整实现。

## 最小证明连接

1. `row_prefix` 目标沿用 `RowStream.Prefix (RowStream.point ...)`，入口长度 r*p，出口长度 (r+1)*p。使用已写 `emit_prefix`，每个 lane 的 read 等式由 `point_row` 的反向等式给出。m 正由 r.isLt 得到；p 正由当前 j.isLt 得到，因此 p=0 时不构造虚假正性条件，也无需全局 p>0 假设。
2. `output_prefix` 沿用 `foldl_inv`，不变式 P(r,out)=Prefix(point,r*p,out)，初始 Array.mkEmpty 的空前缀。空 batch/m/p 和巨大 Nat 都保留相同全域定义；不把有限布局诊断当作证明。
3. 包装 Vector 时使用 output_prefix.1。用 Vector.ext 比较 `DirectContinuous.core` 与 `RowStream.core`，分别先显式建立 q<output.size 和 q<RowStream.output.size，再以两个 output_prefix.2 消去读值。最后传递到 `RowStream.core_eq_reference`。这条证明路线不在直接路径运行时准备 nativeA/packedB；相关证明在运行时擦除。
4. 现有 `DirectSmall.core_eq_reference` 仍可作对照，但没有必要复制浮点证明。四个正式 *_spec 的接口保持原样，任何组合后的精确源仍须完整 gate。

## 分派与隔离实验

首个独立比较可以只替代 a066 的 `n≤4 ∧ 2<p` 分支，检验去行数组本身的完整成本。若需要覆盖原 DirectSmall 的 p≤2，可在跨 batch 新分支之后作为原直接路径的完整回退；由协调者在实际组合源上统一确定 guard，避免 writer 抢先截住跨 batch 内核。不能从其中一个族的结果推断所有直接形状收益。

原 packed writer 与直接 writer共用前缀证明，不强求共用一个高阶运行时循环。此后若要按 batch 准备→写出→释放，也可把初始前缀位置改为 b*m*p，并使用完全相同的 Prefix/emit。单纯复制目前整批 nativeA/packedB到新命名空间不会带来生命周期变化。

## 验证判别

- 先接受精确 proof2 的语句反馈，再生成一份集成候选，避免积压多个未验包。
- 旧辅助链精简的默认干运行脚本在 `f01-d11-bmm-fused-output-proof2/compact-plan.py`；精确2c73投影235613 B、余量20387 B。脚本核对每段SHA、唯一整段匹配、精确规格替换和逆变换。当前没有写出精简Kernel；Lean依赖闭包仍未验。
- 生成 C 检查直接运行路径是否消除 Array.ofFn/行Array/Array.append，输出是否独占，Fin.foldl是否产生每行或每元素闭包／额外控制开销。不能仅凭 inline 标记判断。
- 完整计时按所有已授权原版gate；独立新输入/runner确认由Root保留。源码容量减少不算运行加速。

冻结 proof2：SHA256 `2c73622e91fa0edef0e37a22bac1724190451479b0dceeee04ef5d181cc811ed`，245054 B。其语句、公理、重放、checksum、生成代码和性能目前均未取得新通过证据。
