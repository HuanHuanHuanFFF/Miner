# 97f canonical BMM 冷扫描集成审查

**需要补的是实际 Nat loop／Fin.foldl 的执行等式、raw codec 和精确源码集成；无需重做 W12 的 canonical 数学。** W12 已有“raw dot = 导入 native dot”的真实定理，但它不是“扫描成功就输出 C”。`dot([1],[1])` 的扫描为 true，raw 输出仍为 `0x3f800000`；只有再有 native 终点 NaN，才能得到正 canonical NaN 字。

目标为 [97f 源码](../f01-d7-direct-nonfinite/Kernel.lean)：174925 字节，SHA `97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26`，manifest 标记 `NOT_RUN_NEW_COMPOSITION`。新 [scanner](dot-nonnan-scan-block.lean) 为 `5e46e932…12ea8f`，6 个声明仍 NOT_RUN。本次只写本报告和 [JSON](canonical-bmm-integration-review.json)，不改候选、R 或原件，不执行 Git 修改、CI、上传或工具链安装。开始 2026-10-22 23:10:49 UTC，45 分钟上限至 23:55:49 UTC；总截止仍为 2026-10-23 04:22:17 UTC。

## 已确认的集成缺项

| 项 | 精确证据 | 可直接落实的处理 |
|---|---|---|
| 旧操作桥不能处理新分支 | 97f L3209–3243 的 `dotLoop_eq` 在 L3211 要求 `result.isNaN=false`。W12 的 `nativeDotFin` 是另一个具体 Fin fold。 | 保留旧桥仅供旧非 NaN 分支。新增一个无分类限制的 **native loop 执行适配**，接到 W12 Fin 定理。 |
| scanner 与 W12 的分类层不同 | scanner L95–104 给 `Model.NativeBinary32.ofUInt32 raw.1` 的分类；W12 Fin 定理要 `ExecFloat.Binary.toModel`。97f 没有通用 `exec_toModel_eq_rawModel` 声明。 | 索取 W12 已验 codec 的实际映射名；不要臆造 `Submission.R7W02`，也不要把目标层间转换当成已经通过的 `change/rfl`。 |
| 两个运行时 hook 目前靠定义相等 | dot L3245–3248、Packed10.finish L3495–3498 的 cold tail 都是 `replayEarly`。L3505 的 `finish_eq_dot` 仅 `rw [hs]; rfl`。 | 若保持统一路线及现有证明，**两处同时使用同一 guard／scanner／返回／fallback 表达式**。只改 dot 会漏实际 packed 输出的 hook，且打破这条 rfl 证明。 |
| 全局声明顺序 | 97f 没有 DWord/DDot；L3164 后 namespace 栈只有 `Submission`。DWord 完整块的 selected_add/mul 还依赖已在 L3082 前定义的 R7Native。 | 可在 L3164 后暂闭 `Submission`，放全局块，再重开后进入 NativeFinal。仅追加到文件末尾不能供前面的定义调用。R 语义前置依赖也须在 dot 证明之前。不要动 R2W01c.NativeBridge。 |
| W12 原增量不能直接过 policy | 原增量 L189 注释 `native import/export pair` 命中原 gate BANNED 的 `export`。97f、DWord、scanner 的同一正则均无命中。 | 保留原件，在 policy-ready 映射副本只改说明词并重绑哈希，随后检查完整候选。网页编译不覆盖 policy。 |
| 整源拼接会超字节帽 | 97f 174925 + W12 整源 139292 + scanner 3526 = **317743 > 256000**，尚未加 classifier 和运行时改动。 | 由 R 提供最小映射声明／依赖闭包。scanner 只需要 DWord 的 rawNaN/rawNaN_eq，不需要选词与 selected_add/mul 的无关证明。 |

若 D 有意识只优化 packed 路线，正确性可以通过语义等式重证 `finish_eq_dot`，但原 `rfl` 不再成立，DirectSmall 也不会受益。这是另一个明确范围选择；本审查没有创建变体或认定它更快。

## 向 R 索取的最小语义接口

W12 当前 **真实**签名（Increment L577–587，以下为接口记录，不是新增声明）：

```lean
theorem R7W12.dotFin_eq_native_of_model_not_nan {n : Nat}
    (a b : Fin n → Competition.Binary32)
    (ha : ∀ i, Model.isNaN (ExecFloat.Binary.toModel (a i)) = false)
    (hb : ∀ i, Model.isNaN (ExecFloat.Binary.toModel (b i)) = false) :
    Fin.foldl n (fun acc i => ExecFloat.add acc (ExecFloat.mul (a i) (b i)))
        Competition.posZero =
      ExecFloat.Binary.ofFloat32
        (R7W12.nativeDotFin a b
          (ExecFloat.Binary.toFloat32 Competition.posZero))
```

以及已验通用 codec（W12 整源 L483–490）：

```lean
theorem R7W05Cached.R7W02.exec_toModel_eq_rawModel (q : Competition.Binary32) :
    ExecFloat.Binary.toModel q = Model.NativeBinary32.ofUInt32 q.raw.1
```

R 应交付这两个接口、`nativeDotFin` 定义及必要证明依赖的 **policy-ready 实际命名空间映射**；当前网页名字不能直接假定已存在于 97f。scalar 非 NaN 原生基桥应映射到 `Submission.R7Native.ofFloat32Add/Mul`，不要误选早期 finite-only 的 `Submission.NativeBridge.ofFloat32Mul`。

W12 原件：整源 SHA `6baa0a8007e85c24633d540a9f6687ddd5da1381da8aa93b1a29d166345fc288`；增量 SHA `d907d96bd44159ba1b85569d7ff6d2d2b04fac0ef18a659665fc35dfd28aa26e`。本次核原 compile-attempt3、diagnostic-attempt2 的 exit 均 0，成功源码快照逐字节相同；所引 dot、codec、import add/mul 与 canonical 字接口的原始公理行均只有三允许公理。固定 Lean 4.34.0 / `293d5d0c…102b`。这只是该网页精确证明，不是 97f 或新集成的完整 gate。

该 Fin 定理**没有终点 NaN 条件**，因为它只证明完整 carrier 等于 native 导入，有限数、Inf、±0、canonical NaN 都允许。它本身不能推出输出 C。新运行时仍只在已有 NaN 冷路使用扫描，这是成本控制；推荐继续返回既有 `ofFloat32 result`。若硬码 C，另外需要终点 NaN、`native_eq_nan_of_isNaN`、W12 L7 的 `ofFloat32_nan_raw` 及实际 carrier 构造等式。

## D 需要的执行适配与证明接法

下列是 **待实现签名／NOT_RUN**，只描述实际执行序列；任意 native acc 允许，不涉及任意 raw seed 的 canonical 性：

```lean
theorem dotLoop_eq_nativeFold
    (n baseA baseB p : Nat) (A B : Array Competition.Binary32)
    (k : Nat) (acc : Float32) :
    Submission.NativeFinal.dotLoop n baseA baseB p A B k acc =
      Fin.foldl.loop n
        (fun (s : Float32) (i : Fin n) =>
          s + ExecFloat.Binary.toFloat32 (A.getD (baseA + i.val) Competition.posZero) *
            ExecFloat.Binary.toFloat32 (B.getD (baseB + i.val * p) Competition.posZero))
        acc k
```

证明只需同步展开 `dotLoop` 与 `Fin.foldl.loop`，按 k<n 分支，同一 native mul-then-add 更新后递归到 k+1，度量 n-k。不能用要求终点非 NaN 的旧 `dotLoop_eq` 代替它。k=0 时再把真正 seed 对齐：Packed10.zero32 在 97f L3303 定义为 `Float32.ofBits 0`，与 `toFloat32 posZero` 的对应须在新精确上下文核查。

D 的最终 true 分支只需得到：

```lean
theorem dotCold_accept
    (n baseA baseB p : Nat) (A B : Array Competition.Binary32)
    (result : Float32)
    (hresult : result =
      Submission.NativeFinal.dotLoop n baseA baseB p A B 0 (Float32.ofBits 0))
    (hscan : DDotNonNaNScan.whole n baseA baseB p A B = true) :
    ExecFloat.Binary.ofFloat32 result =
      Fin.foldl n
        (fun acc i => ExecFloat.add acc
          (ExecFloat.mul (A.getD (baseA + i.val) Competition.posZero)
            (B.getD (baseB + i.val * p) Competition.posZero)))
        Competition.posZero
```

接法为 scanner 的两个 word-Model 非 NaN 后件 → 已映射 codec → W12 Fin 定理 → 新 native 执行适配。W12 等号方向是 raw fold 在左，fast return 目标相反，需要取对称。这个 carrier 等式不需要再次假设终点 NaN；**将它误读成 raw=C 才是错误**。不能把 +0 起点推广成任意非 canonical raw seed：seed=`7fc00001`、A=B=[1] 是反例。

两个 finishing body 的设计形状应一致（仅设计文本，未应用）：

```lean
if hf : result.isNaN = false then ExecFloat.Binary.ofFloat32 result
else if hs : DDotNonNaNScan.whole n baseA baseB p A B = true then
  ExecFloat.Binary.ofFloat32 result
else R7NaNReplay.replayEarly n baseA baseB p A B
```

`NativeFinal.dot_eq` 的原非 NaN 分支不变；旧 cold 分支再分 scanner：true 用上述 carrier 等式，false 原 `replayEarly_eq` 转 raw fold 的证明照旧。其定理陈述保持原样。于是 `finish_eq_dot` 可继续靠 hs 和定义相等，`finish_eq_fold/kernel_fold`、`finish_dot10_lane`、`tile_finish`、`outputFromTiles_eq` 和 DirectSmall.core_eq_reference 的后续原式可保持。

实际调用链：导出 bmm L4145 以 n≤4 或 p≤2 走 DirectSmall.core → NativeFinal.dot；其余 bmmPackedBase → RowStream.core → RowOutput.row L3965 → Packed10.finish。packed 的 native prefix 不经 NativeFinal.dot 运行，只通过 lane 证明与其比较。只改一处不能同时覆盖两条运行路径。

## 冷扫描成本与地址边界

807 的既有计数已按原 drawn-plan SHA `9cc5d736…8622` 重算并映射到 97f 的真实 dispatcher；未重跑 tensor 或计时。2412 是可避开的 **quiet-stop prefix mul-then-add 步**，不是 7551 个旧完整回放步。扫描读取是逻辑 word 读取／分类次数，不是硬件 cache traffic 或周期。

| 97f 路径 | eligible 输出 | 可避 prefix 步 | eligible 扫词 | rejected 输出 | rejected 新增扫词 |
|---|---:|---:|---:|---:|---:|
| DirectSmall | 205 | 607 | 1738 | 2162 | 8848 |
| PackedBase | 466 | 1805 | 13364 | 27 | 685 |
| 合计 | 671 | 2412 | 15102 | 2189 | 9533 |

specials0/1/2 分别为 (n,p)=(47,1)/(1,3)/(5,1)，均走 DirectSmall；specials0 没有 eligible，却有 1304 次新增扫词。三个 extremes 为 (12,23)/(8,3)/(15,27)，走 PackedBase，本样本没有 rejected。数据说明分路成本不能忽略，**不能由读数直接认定收益**；原 native passes、nativeA/map、packB、输出构造都未省去。

- raw 地址始终是 A[baseA+k]、B[baseB+k*p]，不是 packedB 或连续 B 片段。按具体有效输出 j/lane 传相同 base；不对 padding lane 额外扫描。
- `dot10_lane` L3457、`packB_lane`／`tile_finish` L3732–3747 已保留实际列与 getD；`runDot_eq` L3703 对 USize 成功／Nat 后备均给统一 native 等式。新 scanner 本身为 Nat，不增加字长前提，也不动这些循环。
- n=0 的 scanner 虽为 true，native 终点是 +0，冷路不进入；零输出 shape 无有效 q。BMM 原有零 shape／n=0 后备及 DirectSmall guard 不改。泛用 dot 的越界默认仍为 +0，允许默认 0×Inf 产生 NaN。
- 新冷路仍有 Nat 地址算术、getD bounds、两项分类、raw A/B 重读；rejected 会先付扫描再做旧 quiet replay。ordinary 分支源式应保持，生成 C/asm 仍需核是否有 hoist／额外调用／布局变化。

## scanner 证明的具体未验目标

未发现确定的数学／API 错误；编译未运行。L18 的 [k,n) 后件、L58 的 i=k/大于 k 分解、L65 的 n-k 度量都对任意 Nat k 正确，k≥n 是空区间。主要首编译目标是 bare split 产生的上下文、递归定理在 rw 内的 elaboration，以及 Model 依赖。

若出现实际失败，更稳健的局部写法是显式 `by_cases hk : k<n`、`rw [loop, dif_pos hk]`，再分别 `by_cases ha/hb` 并用 if_pos/if_neg；先 `have ih := loop_true_iff ... (k+1)`，再重写 ih。两个 `cases ... <;> simp_all` 可用独立 Bool 二分事实 `∀ b:Bool, b≠true → b=false` 替代，避免依赖全上下文简化。它可直接按 b 的两个构造证明，无需杜撰库名。保持真实分类器、Nat 范围和严格递减，不为回避错误添加 n<USize 或 k≤n 前提。以上是首失败后的收敛处理，不代表当前源码已被编译器否定。

本次实际完成：绑定 21 个源／日志文件；读两个 hook、完整两路调用链、零 seed/shape、旧 replay；核 W12 实际源码/快照/exit/所引原公理行；重算成本和 route；跑 8 个小型整数转录见证（端点限定、payload、seed、stride、default）。新 Lean、候选 policy/原义务/fullgate、C/asm、性能和独立确认全部 NOT_RUN / UNKNOWN。后续首先关闭上述接口和声明顺序，再由 D 冻结精确候选执行原版完整验收。

