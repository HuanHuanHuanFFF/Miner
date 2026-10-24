# 直接路径复用连续 writer

状态：IMPLEMENTED_NEW_CANDIDATE / NEW_LEAN_NOT_RUN / NEW_TIMING_UNKNOWN。2026-10-23T21:58Z：新候选 `f01-d11-bmm-direct-continuous`，SHA256 `2aaa5d9e84c758a23a8c6dc1f77d800950fbaa5769aec7a38d299741c17a5f56`，248566 B，已冻结交接。父本5b7d在911/run40027315361完整gate通过；新候选不能继承其验证或性能。

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

上述运行代码及下列row_prefix/output_prefix、Vector包装和参考连接已经写入唯一新候选，具体文件及静态逆变换证据在新目录。所有新增Lean文本仍待实际statement。

## 最小证明连接

1. `row_prefix` 目标沿用 `RowStream.Prefix (RowStream.point ...)`，入口长度 r*p，出口长度 (r+1)*p。使用已写 `emit_prefix`，每个 lane 的 read 等式由 `point_row` 的反向等式给出。m 正由 r.isLt 得到；p 正由当前 j.isLt 得到，因此 p=0 时不构造虚假正性条件，也无需全局 p>0 假设。
2. `output_prefix` 沿用 `foldl_inv`，不变式 P(r,out)=Prefix(point,r*p,out)，初始 Array.mkEmpty 的空前缀。空 batch/m/p 和巨大 Nat 都保留相同全域定义；不把有限布局诊断当作证明。
3. 包装 Vector 时使用 output_prefix.1。直接复用5b7d已接受的抽象 `prefix_vector_eq_ofFn`，再传递到 `points_eq_reference`；不对具体direct输出再次执行Vector.ext/change/rewrite。原1b71/2c73的具体输出桥曾有200000-heartbeat whnf超时，不能把该形状原样迁入新候选。抽象桥不在直接路径运行时准备nativeA/packedB；相关证明在运行时擦除。
4. 现有 `DirectSmall.core_eq_reference` 仍可作对照，但没有必要复制浮点证明。四个正式 *_spec 的接口保持原样，任何组合后的精确源仍须完整 gate。

## 分派与隔离实验

首个独立比较可以只替代 a066 的 `n≤4 ∧ 2<p` 分支，检验去行数组本身的完整成本。若需要覆盖原 DirectSmall 的 p≤2，可在跨 batch 新分支之后作为原直接路径的完整回退；由协调者在实际组合源上统一确定 guard，避免 writer 抢先截住跨 batch 内核。不能从其中一个族的结果推断所有直接形状收益。

原 packed writer 与直接 writer共用前缀证明，不强求共用一个高阶运行时循环。此后若要按 batch 准备→写出→释放，也可把初始前缀位置改为 b*m*p，并使用完全相同的 Prefix/emit。单纯复制目前整批 nativeA/packedB到新命名空间不会带来生命周期变化。

## 验证判别

- Root已授权并收到911完整结果后，只生成了这一份direct候选；下一步等待它的精确statement，避免积压多个未验包。
- 旧辅助链精简的默认干运行脚本在 `f01-d11-bmm-fused-output-proof2/compact-plan.py`；其默认源仍2c73，应用5b时必须显式传5b路径与SHA。五段精确内容及bmmPackedBase_spec重接未因proof3变化；5b投影236400 B、余量19600 B。本次direct候选没有执行该emit，也没有使用尚未验证的compact父本。
- 生成 C 检查直接运行路径是否消除 Array.ofFn/行Array/Array.append，输出是否独占，Fin.foldl是否产生每行或每元素闭包／额外控制开销。不能仅凭 inline 标记判断。
- 完整计时按所有已授权原版gate；独立新输入/runner确认由Root保留。源码容量减少不算运行加速。

当前冻结基座5b7d：SHA256 `5b7d926cf628c2d87042386834f7c1581b9a6aa7441af196453984b395534ba2`，245841 B、余量10159 B。907statement与911完整gate通过；新build读取911原verdict确认score/PASS、25轮及前后fingerprint一致。本direct候选自身所有Lean/完整gate/性能仍NOT_RUN。

## 关键证明接线草稿

以下为唯一新候选的关键证明摘录。每个row沿用真实NativeFinal.dot；p=0没有Fin p元素，hp只在有效j内构造。

```lean
theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m))
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (r.val * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((r.val + 1) * p)
      (row batch m n p A B out r) := by
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  have h := RowStream.emit_prefix (RowStream.point batch m n p A B)
    (r.val * p) p
    (fun j : Fin p => NativeFinal.dot n (r.val * n)
      (r.val / m * n * p + j.val) p A.toArray B.toArray) out hout
    (by
      intro j
      have hp : 0 < p := Nat.zero_lt_of_lt j.isLt
      exact (RowStream.point_row batch m n p A B r.val j.val hm hp j.isLt).symm)
  simpa only [row, Nat.add_mul, Nat.one_mul] using h

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  exact RowStream.foldl_inv (batch * m) (row batch m n p A B)
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B) (r * p) acc)
    (fun r acc hacc => row_prefix batch m n p A B acc r hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.DirectContinuous
```

最终bmm仍只把原 `n≤4 ∧ 2<p` 的DirectRows.core替成DirectContinuous.core；该分支spec通过新core_eq_reference接referenceBmm_spec，else仍原bmmBeforeDirectRows_spec。不是再做tiny-unroll或numeric decoder替换，p2留给Astra。

## 原路径对照与容量

|项目|原5b7d短n直接路径|本设计|
|---|---|---|
|行遍历|构造Fin行号Vector再flatMap|Fin.foldl带一份最终Array|
|行输出|每行Vector.ofFn，再Array append|emit逐输出push，无行Array|
|A地址|b=r/m、i=r%m，再(b*m+i)*n|直接r*n|
|B地址|每行共享b*n*p|每行共享(r/m)*n*p|
|点积/NaN|原NativeFinal.dot|同一函数同原字同顺序|
|打包|无|无|

因此实质变化除了去掉行数组，还消除恢复i及重建平面A行号的步骤；不能把未来收益全部归因为数组分配。Fin.foldl的Nat控制与闭包开销可能抵消节省，必须查实际C/完整调用。

精确5b旧DirectRows命名空间为1190 B，本次保留原字节，没有删除。实际新block2734 B、净增2725 B，完整候选248566 B、余量7434 B，低于8k新增目标；逆变换恢复精确5b。P1–P5精确剪枝净省9441 B的投影仍仅用于后续容量规划，本新候选没有应用。任何underflow/P12/batch-local组合仍由Root重新核对容量，不在本稿相加宣称可用。

`layout-precheck.json`的有限数学整数诊断覆盖2880组形状、108000个输出位置、270000对原有序地址，另有12个巨大Nat地址恒等式spot check。它只说明有限布局/地址核对，不是Lean、浮点或性能通过。
