# FloatLib R3-W01：把 Packed4 机器字准入移到整次 bmm

日期：2026-10-22（Asia/Shanghai）。范围：外围矩阵地址界、一次准入与原 Packed4 证明的连接。

## 结论与交付状态

**数学上可以只保留完整调用中的 `nativeA.size < USize.size` 检查。** 需要保留原空输出和 n=0 分支；在已有合法 `b : Fin batch`、`i : Fin m` 的行内，前三项条件都从 shape、Vector 长度与该全局检查推出。

已交付完整辅助证明体与包装：

- 独立 `MatrixBounds.lean`：90 行、3,801 字节，只有 `import ContractTensor`；
- `WholeCall.inc.lean`：138 行、5,979 字节，提供 tile/get/lane/finish/core 和并列 bmmOnce 的完整等价连接；
- 去掉重复 import 后的组合插入片段：227 行、9,758 字节；
- 最小集成、分离诊断、实际整数结果、来源与 SHA 清单。

**Lean elaboration、内核检查、公理输出、真实 within 执行和计时均为 NOT_RUN。** 环境没有 Lean/lake/elan，没有安装工具链。此包没有复制 72 KB 父本，也没有实现或改写 within 热循环、布局或数值桥。

公开父本中没有用户另一路正在验收的 within / within_eq。因此：纯矩阵界文件可在已有 ContractTensor 环境单独检查；完整包装必须与用户实际的这两个声明联编。包内没有为此添加替身、未证声明或外部 sound 参数。源码中的两处全名统一写为 `Submission.Packed4.within`、`Submission.Packed4.within_eq`，实际命名空间若不同，只需对齐名称。

组合片段 SHA256：

```text
a84ced5d975f7caed47d3b9126f284b726815f81cccd268ef065b51de0dd981f
```

## 1. 精确父本核对

本轮实际读取的公开父本是 Miner commit `9fa0c60d8d5589d58b3152202adac2df444ec5e2` 的 `f01-d2-web-packed4-proof1/Kernel.lean`，72,452 字节，SHA256：

```text
bb1f783fd3103fba89e1e072459d7fdcff9ffdb5edc3e2983b39f1eafced2f18
```

与用户给定精确版本一致。已实际核对其 tileResults、tileResults_get、tile_finish、outputFromTiles、core、core_eq_reference 和最外层 bmm 分支。父本 full gate 与约 1.45 ns/MAC 是用户提供的开发反馈，本轮未复跑，不据此推断新包装速度。[PARENT]

固定环境仍为 Lean v4.34.0、FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`、官方 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。本轮数学不修改任何浮点运算或其规格。[CONTRACT]

## 2. 数学核心：先整行，再单点，再机器界

记 r=b*m+i，L=batch*m*n，W=USize.size。

对 b<batch、i<m，有：

\[
bm+i < bm+m=(b+1)m\le batch\cdot m.
\]

因此 r+1≤batch*m。乘以任意自然数 n，得到整行排他上界：

\[
rn+n=(r+1)n\le L.
\]

此处 n 可以为 0。对于 k<n，再加一步严格比较：

\[
rn+k<rn+n\le L.
\]

这就是 `point_bound`。当 0<n 时，n−1<n，从而得到用户指定的完整末元素界：

\[
(bm+i)n+(n-1)<batch\cdot m\cdot n.
\]

此外，由 rn≥0 和 rn+n≤L 得到 n≤L。给定真实 nativeA 长度 L 及 L<W，便有：

\[
n\le L<W,\qquad baseA<L<W,\qquad baseA+(n-1)<nativeA.size.
\]

`baseA<L` 是 `point_bound` 取 k=0、使用 0<n。所有实际 k<n 的地址还满足 `baseA+k<nativeA.size<W`。所以 count、baseA 和访问地址都有严格机器字界；本轮不重复已有 within 内的转换与 uget 等价桥。

源码先用乘法单调性建立整行上界，`omega` 只处理线性推论和正 n 下的 n−1，不要求它解决变量乘法。

## 3. 可直接喂给 within 的定理

核心接口是：

```lean
theorem array_row_bounds (batch m n : Nat) (A : Array Float32)
    (hsize : A.size = batch * m * n) (b : Fin batch) (i : Fin m)
    (hn : 0 < n) (hAS : A.size < USize.size) :
    n < USize.size ∧
      (b.val * m + i.val) * n < USize.size ∧
      (b.val * m + i.val) * n + (n - 1) < A.size
```

结论 `.1`、`.2.1`、`.2.2` 依次传给 within 的 count、baseA、最后元素边界证据；原 hAS 作为第四项传入。

nativeA 长度不是额外假定，已从实际接口闭合：

```lean
theorem nativeA_size (batch m n : Nat) (A : Vector Binary32 (batch * m * n)) :
    (A.toArray.map ExecFloat.Binary.toFloat32).size = batch * m * n := by
  rw [Array.size_map]
  exact A.size_toArray
```

Lean v4.34.0 的 `Array.size_map` 确实给出 map 后数组长度相等；`Vector.size_toArray` 是结构中的证明字段，精确类型是 `toArray.size = n`。[ARRAY]、[VECTOR]

完整声明清单：

| 声明 | 用途 |
| --- | --- |
| row_lt | 合法 b/i 对应合法扁平行 |
| row_end_le | 行尾排他界，允许 n=0 |
| point_bound | 任意 k<n 的地址界 |
| row_span | 0<n 下的末元素界 |
| row_count_le | 有效行存在时 n≤总长度 |
| nativeA_size | 从 map 与 Vector 结构获得长度 |
| array_row_bounds | 一次全局检查推出三个准入证明 |
| native_row_bounds | 原始 typed A 的直接版本，内部提供 hsize |
| array_point_bounds | 实际地址同时小于数组长度和 W |

这些声明都是 theorem，不构造运行时布尔证书或地址表。

## 4. 一次检查如何传到每个 tile

新增 builder 的关键部分是：

```lean
Vector.ofFn fun b =>
  Vector.ofFn fun i =>
    let h := MatrixBounds.array_row_bounds batch m n A hsize b i hn hAS
    Vector.ofFn fun g =>
      Submission.Packed4.within n ((b.val * m + i.val) * n)
        A ((B.get b).get g) h.1 h.2.1 h.2.2 hAS
```

h、hn、hsize 和 hAS 都是 Prop 证据；它们在 Lean 编译时擦除。新的叶子没有 if、decide 或旧 runDot 调用，直接调用一次实际 within。特别地，证明里的乘法和大小比较不是新增逐 tile 的运行检查。

唯一新运行分支是 builder 外层：

```lean
def selectTiles (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n) :
    Vector (Vector (Vector F4 (groups p)) m) batch :=
  if hAS : A.size < USize.size then
    tileResultsWithin batch m n p A B hn hsize hAS
  else tileResults batch m n p A B
```

`coreOnce` 与父本一样只做一次 A.map 和一次 packB，再调用一次 selectTiles。它保留同一缓存组织及 outputFromTiles；没有新缓冲，没有逐输出重算四路 dot，也没有在失败支路再调用整个 core 重做准备。

这里明确的是源码控制结构与证明擦除。没有检查本轮生成 C，不把“条件检查减少”换算为速度收益。

## 5. 具体等价桥，而非接口清单

首先对三层 Vector.ofFn 做外延，叶子应用用户真实的 within_eq，得到整个：

```lean
tileResultsWithin batch m n p A B hn hsize hAS =
  tileResults batch m n p A B
```

三个 funext 对应 b、i、g，不对浮点运算做代数变形。然后原读取桥直接复用：

```lean
by
  rw [tileResultsWithin_eq]
  exact tileResults_get batch m n p A B b i g
```

`tileResultsWithin_lane` 在此基础上保留同一 lane 投影。对使用原始 A/B 的最终结果桥，完整证明末尾是：

```lean
by
  rw [tileResultsWithin_eq]
  exact tile_finish batch m n p A B b i g l hcol
```

`selectTiles_eq` 分析唯一全局检查：成功用上述等式，失败是 rfl。`coreOnce_eq_core` 因而只需展开 core 后 `rw [selectTiles_eq]`，直接恢复公开父本的整个 core。

最后，包内提供并列诊断入口 bmmOnce：沿用空输出和 n=0 两个参考分支，其余调用 coreOnce。`bmmOnce_eq` 连接原 bmm，`bmmOnce_spec` 连接原无条件规格。它们没有在最终 theorem 上增加 n>0、机器界或 sound 前提。完整证明体均在附录。

**入口边界：**包内 bmmOnce 是新名字，不会自动改写现有 Submission.bmm。追加片段后，只运行仍指向旧入口的 VerifyFull 不能证明新入口已采用此包装。独立诊断直接检查 `Competition.BmmObligation Submission.bmmOnce`；生产接线方法见 INTEGRATION.md。

## 6. 必须保留的反例和分支

### 空形状、巨大 n

对任意 W>0，取 batch=0、m=1、n=W。此时 nativeA.size=0<W，但 n<W 为假。取 batch=1、m=0 同样成立。甚至可以取 n=2^128+123。

因此不能先仅凭全局长度检查，把任意 n 截断为机器字再判断路径是否合法。本片段在存在真实 b/i 的行内构造证据；空 batch/m 时没有这样的 Fin 值。实际 bmmOnce 还在最外层将空输出送参考分支，不建立新 native 缓冲或调用 within。

### n=0

Nat 减法下 n−1=0，所需 row_span 化为 0<0，确实为假。原 n=0 参考分支保持；0<n 只作为内部包装参数，由最终入口自己的 n≠0 分支提供。point_bound 在 n=0 时没有可满足的 k<n 前提。

### p=0 与尾块

p=0 时输出为空，保留原参考分支。末列不足四路的 packB 及其填充不变，地址界不依赖 g 或 l；有效 lane/无效 lane 的隔离由原父本证明继续承担。本轮没有改尾块运算或非finite处理。

### 两层回退

| 触发条件 | 实际路径 | 输入来源 |
| --- | --- | --- |
| nativeA.size≥W | 原 tileResults / dot4 | 复用当前 nativeA 和 packedB |
| 最终结果非finite | 原 outputFromTiles / finish 的精确 fold | 原始 Binary32 A/B |

机器字准入失败并不直接等于原软件精确回退；它先回到已证明的 Nat 点积路径。最终非finite回退始终保留原始输入，所以没有用规范化后的缓存代替 NaN payload、Inf 或有符号零的原始位型。

## 7. 实际验证和未编译边界

本轮已执行：

- 精确公开父本下载、字节数与 SHA 核对；
- 固定 Lean 数组、Vector、Nat 定理接口阅读；
- 官方 gate 原始禁止项正则扫描，三个可拼接源码文件包括注释均零命中；
- 源码结构检查：tile wrapper 无动态条件；唯一全局 hAS 分支；一个 within 调用点；无旧 runDot 调用、无新显式机器字转换；
- 纯整数诊断：batch,m=0..8、n=0..16，共 22,032 个有效行和 176,256 个有效点；
- 32/64 位界对应的 6 个大整数正例，以及空形状、n=0、严格尺寸等号拒绝等 8 个边界/反例记录。

整数诊断用 Python 整数，不分配这些巨大形状的矩阵，不运行 Float32、Lean 或 within。它验证有限样例及具体误用反例，不能替代全称证明的 Lean 验收。

独立静态审阅已覆盖本轮两个实际源码文件及父本对应接口，未发现确定的连接阻断。由于缺少工具链，当前没有真实 Lean 报错目标可列出。需要开发侧在现有固定环境中执行：

1. MatrixBounds 独立 elaboration；
2. 与真实 within / within_eq 联编；
3. 新 bmmOnce 的 obligation 与公理输出；
4. 实际接入现有入口之后，运行原有正确性验收。

若失败，保留首个真实错误与 Lean 目标；不能用增加外部假设或改环境来通过。公理集合仍须是 `{propext, Classical.choice, Quot.sound}` 的子集。本轮不请求新的性能实验，不安装工具链，不正式提交。

## 8. 已核 API、来源与许可

| API / 定义 | 固定源位置 | 本轮用途 |
| --- | --- | --- |
| Nat.add_lt_add_left | Nat/Basic.lean 第 496 行 | 加同一 base 保持严格界 |
| Nat.mul_le_mul_right | Nat/Basic.lean 第 757 行 | 由行号界推整行上界 |
| Array.size_map | Array/Lemmas.lean 第 1190 行 | nativeA 长度不变 |
| Vector.size_toArray | Vector/Basic.lean 第 36 行 | typed A 的精确数组长度 |
| Vector.ofFn | Vector/Basic.lean 第 320 行 | 相同三层缓存构造 |
| 原 tile/get/finish/core/bmm | 精确公开父本末段 | 整体等价重写与原始输入回退 |

Nat API 的显式参数顺序已实际核对，避免凭记忆猜调用形式。[NAT]、[ARRAY]、[VECTOR]

`sources/source_manifest.json` 保存 10 个本轮实际下载的固定公开文件 URL、字节数和 SHA256。FloatLib revision 按用户固定环境保持，本轮不复制或改写数值桥。公开父本的内嵌来源/许可 notice 应继续保留在实际 Kernel 中；本包不包含父本全文。Lean 源码许可为 Apache-2.0，来源声明见固定仓库；没有将其实现复制进辅助证明。[PARENT]、[LEAN_LICENSE]

[PARENT]: https://github.com/HuanHuanHuanFFF/Miner/blob/9fa0c60d8d5589d58b3152202adac2df444ec5e2/competitions/floatlib/candidates/f01-d2-web-packed4-proof1/Kernel.lean
[CONTRACT]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean
[NAT]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Basic.lean
[ARRAY]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Lemmas.lean
[VECTOR]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean
[LEAN_LICENSE]: https://github.com/leanprover/lean4/blob/v4.34.0/LICENSE

## 附录：完整组合插入片段

下面与包内 `Packed4WholeCallFragment.inc.lean` 完全一致，无 import；放在完整候选的文件顶层、真实 within / within_eq 之后。它包含纯矩阵界、包装、复用桥与并列诊断入口，没有内层机器字循环实现。

````lean
namespace Submission.Packed4.MatrixBounds

open FloatLib.Floats

/-- A valid batch and row select a valid flattened row. -/
theorem row_lt {batch m b i : Nat} (hb : b < batch) (hi : i < m) :
    b * m + i < batch * m := by
  calc
    b * m + i < b * m + m := Nat.add_lt_add_left hi (b * m)
    _ = (b + 1) * m := by simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m := Nat.mul_le_mul_right m (by omega)

/-- The exclusive end of a valid row is at most the matrix length. -/
theorem row_end_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    (b * m + i) * n + n ≤ batch * m * n := by
  have hr := row_lt hb hi
  calc
    (b * m + i) * n + n = (b * m + i + 1) * n := by
      simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m * n := Nat.mul_le_mul_right n (by omega)

/-- Every position in a valid row lies in the matrix. -/
theorem point_bound {batch m n b i k : Nat}
    (hb : b < batch) (hi : i < m) (hk : k < n) :
    (b * m + i) * n + k < batch * m * n := by
  calc
    (b * m + i) * n + k < (b * m + i) * n + n :=
      Nat.add_lt_add_left hk ((b * m + i) * n)
    _ ≤ batch * m * n := row_end_le hb hi

/-- The final position of a nonempty valid row lies in the matrix. -/
theorem row_span {batch m n b i : Nat}
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + i) * n + (n - 1) < batch * m * n := by
  exact point_bound hb hi (by omega)

/-- One valid row contains n entries, even when n is zero. -/
theorem row_count_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    n ≤ batch * m * n := by
  have he := row_end_le (n := n) hb hi
  omega

/-- Mapping changes elements but preserves the input vector length. -/
theorem nativeA_size (batch m n : Nat) (A : Vector Binary32 (batch * m * n)) :
    (A.toArray.map ExecFloat.Binary.toFloat32).size = batch * m * n := by
  rw [Array.size_map]
  exact A.size_toArray

/-- A matrix length check supplies all row admission evidence. -/
theorem array_row_bounds (batch m n : Nat) (A : Array Float32)
    (hsize : A.size = batch * m * n) (b : Fin batch) (i : Fin m)
    (hn : 0 < n) (hAS : A.size < USize.size) :
    n < USize.size ∧
      (b.val * m + i.val) * n < USize.size ∧
      (b.val * m + i.val) * n + (n - 1) < A.size := by
  have htotal : batch * m * n < USize.size := by
    simpa only [hsize] using hAS
  have hc := row_count_le (n := n) b.isLt i.isLt
  have hbase : (b.val * m + i.val) * n < batch * m * n := by
    simpa only [Nat.add_zero] using
      (point_bound (k := 0) b.isLt i.isLt hn)
  have hlast := row_span b.isLt i.isLt hn
  refine ⟨Nat.lt_of_le_of_lt hc htotal, Nat.lt_trans hbase htotal, ?_⟩
  simpa only [hsize] using hlast

/-- The original typed input supplies the array length evidence. -/
theorem native_row_bounds (batch m n : Nat)
    (A : Vector Binary32 (batch * m * n)) (b : Fin batch) (i : Fin m)
    (hn : 0 < n)
    (hAS : (A.toArray.map ExecFloat.Binary.toFloat32).size < USize.size) :
    n < USize.size ∧
      (b.val * m + i.val) * n < USize.size ∧
      (b.val * m + i.val) * n + (n - 1) <
        (A.toArray.map ExecFloat.Binary.toFloat32).size := by
  exact array_row_bounds batch m n (A.toArray.map ExecFloat.Binary.toFloat32)
    (nativeA_size batch m n A) b i hn hAS

/-- The same single length check also bounds every actual row address. -/
theorem array_point_bounds (batch m n : Nat) (A : Array Float32)
    (hsize : A.size = batch * m * n) (b : Fin batch) (i : Fin m)
    (k : Nat) (hk : k < n) (hAS : A.size < USize.size) :
    (b.val * m + i.val) * n + k < A.size ∧
      (b.val * m + i.val) * n + k < USize.size := by
  have ha : (b.val * m + i.val) * n + k < A.size := by
    simpa only [hsize] using (point_bound b.isLt i.isLt hk)
  exact ⟨ha, Nat.lt_trans ha hAS⟩

end Submission.Packed4.MatrixBounds

namespace Submission.Packed4.WholeCall

open FloatLib.Floats Competition

/-- Row evidence is passed to the existing word loop without local tests. -/
def tileResultsWithin (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size) :
    Vector (Vector (Vector F4 (groups p)) m) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun i =>
      let h := MatrixBounds.array_row_bounds batch m n A hsize b i hn hAS
      Vector.ofFn fun g =>
        Submission.Packed4.within n ((b.val * m + i.val) * n)
          A ((B.get b).get g) h.1 h.2.1 h.2.2 hAS

theorem tileResultsWithin_eq (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size) :
    tileResultsWithin batch m n p A B hn hsize hAS =
      tileResults batch m n p A B := by
  unfold tileResultsWithin tileResults
  apply congrArg (fun f : Fin batch → Vector (Vector F4 (groups p)) m => Vector.ofFn f)
  funext b
  apply congrArg (fun f : Fin m → Vector F4 (groups p) => Vector.ofFn f)
  funext i
  dsimp only
  apply congrArg (fun f : Fin (groups p) → F4 => Vector.ofFn f)
  funext g
  apply Submission.Packed4.within_eq

theorem tileResultsWithin_get (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) :
    (((tileResultsWithin batch m n p A B hn hsize hAS).get b).get i).get g =
      dot4 n ((b.val * m + i.val) * n) A ((B.get b).get g) 0
        zero32 zero32 zero32 zero32 := by
  rw [tileResultsWithin_eq]
  exact tileResults_get batch m n p A B b i g

theorem tileResultsWithin_lane (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) (l : Fin 4) :
    lane ((((tileResultsWithin batch m n p A B hn hsize hAS).get b).get i).get g) l =
      lane (dot4 n ((b.val * m + i.val) * n) A ((B.get b).get g) 0
        zero32 zero32 zero32 zero32) l := by
  rw [tileResultsWithin_get]

theorem tileResultsWithin_finish (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n)
    (hAS : (A.toArray.map ExecFloat.Binary.toFloat32).size < USize.size)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) (l : Fin 4)
    (hcol : 4 * g.val + l.val < p) :
    finish n ((b.val * m + i.val) * n)
        (b.val * n * p + (4 * g.val + l.val)) p A.toArray B.toArray
        (lane ((((tileResultsWithin batch m n p
          (A.toArray.map ExecFloat.Binary.toFloat32) (packB batch n p B)
          hn (MatrixBounds.nativeA_size batch m n A) hAS).get b).get i).get g) l) =
      NativeFinal.dot n ((b.val * m + i.val) * n)
        (b.val * n * p + (4 * g.val + l.val)) p A.toArray B.toArray := by
  rw [tileResultsWithin_eq]
  exact tile_finish batch m n p A B b i g l hcol

/-- This is the only new run-time admission branch. -/
def selectTiles (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n) :
    Vector (Vector (Vector F4 (groups p)) m) batch :=
  if hAS : A.size < USize.size then
    tileResultsWithin batch m n p A B hn hsize hAS
  else tileResults batch m n p A B

theorem selectTiles_eq (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n) :
    selectTiles batch m n p A B hn hsize = tileResults batch m n p A B := by
  unfold selectTiles
  split
  · exact tileResultsWithin_eq batch m n p A B hn hsize _
  · rfl

def coreOnce (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := packB batch n p B
  let tiles := selectTiles batch m n p nativeA packedB hn
    (MatrixBounds.nativeA_size batch m n A)
  Vector.ofFn (outputFromTiles batch m n p A B tiles)

theorem coreOnce_eq_core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : 0 < n) :
    coreOnce batch m n p A B hn = Submission.Packed4.core batch m n p A B := by
  unfold coreOnce Submission.Packed4.core
  dsimp only
  rw [selectTiles_eq]

end Submission.Packed4.WholeCall

namespace Submission

open FloatLib.Floats Competition

/-- The existing empty-output and empty-reduction branches remain outside the fast path. -/
def bmmOnce (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if hn : n = 0 then referenceBmm batch m n p A B
  else Packed4.WholeCall.coreOnce batch m n p A B (by omega)

theorem bmmOnce_eq (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    bmmOnce batch m n p A B = bmm batch m n p A B := by
  by_cases he : batch * m * p = 0
  · simp only [bmmOnce, bmm, if_pos he, dif_pos he]
  · by_cases hn : n = 0
    · simp only [bmmOnce, bmm, if_neg he, dif_neg he, if_pos hn, dif_pos hn]
    · simp only [bmmOnce, bmm, if_neg he, dif_neg he, if_neg hn, dif_neg hn]
      exact Packed4.WholeCall.coreOnce_eq_core batch m n p A B (by omega)

theorem bmmOnce_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmOnce batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  rw [bmmOnce_eq]
  exact bmm_spec batch m n p A B

end Submission
````
