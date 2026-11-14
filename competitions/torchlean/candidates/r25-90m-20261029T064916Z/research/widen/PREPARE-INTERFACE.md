# 原 prepare → getter 的最短接口（07:17 UTC，源码分析；NOT_RUN）

对象是 R24 `development-dot-cost/PortableF64Dot-tail-v2.lean.inc` 的原 `Prepared/prepare/sumRemaining/attemptPrepared`，不改 runtime，不新增大 Kernel。现有三组 widening carrier 冻结，优先等 CI。`FloatArray` 在 Lean4.34 中是公开 `data : Array Float` 包装；`push/size/get!` 直接投影到 data。固定源码 Git blob `29eb263dfd77c1be05e3cd3d45b94023b4188ed9`；Array.Monadic 固定 blob `8d22e214a6618e814fbc804b792f473b13e9f552`。

## 一个可组合的 producer 结论

令 `p := Submission.R24PortableF64.prepare raw`。需要证明的最小强接口为：

```lean
p.raw = raw ∧
(p.valid = true →
  raw.size ≤ 1073741824 ∧
  p.values.size = raw.size ∧
  p.maxIndex.toNat ≤ 253 ∧
  ∀ (i : Nat) (hi : i < raw.size),
    Submission.R24RepresentationWiden.expWord raw[i] ≠ 255 ∧
    p.values.get! i = Float.ofBits (Submission.R24PortableF64.widenBits raw[i]) ∧
    (Submission.R24PortableF64.index32 raw[i]).toNat ≤ p.maxIndex.toNat)
```

这一个结论即可把已写 `R25FiniteWiden.finite_actual_value` 应用于每次真实 `FloatArray.get!`。无需额外假设缓存与 raw 相同，也不把条件接口当成 producer 已证明。只对 `i < raw.size` 运输，不把越界 `get!` 当 +0；长度等式先给出读取边界。异常值分支实际存 +0 且置 `valid=false`，之后不会恢复为 true。

## 原循环的最小不变量

对已消费前缀 `ys`，保留四项：

1. `values.data = ys.toArray.map stored`，其中 `stored w` 是原分支 `if expWord w = 255 then Float.ofBits 0 else Float.ofBits (actual widenBits w)`；因此 size 为已消费数。
2. `valid = true ↔ ∀ w ∈ ys, expWord w ≠ 255`。
3. `peak.toNat ≤ 253`。
4. 每个已消费有限 word 满足 `(index32 w).toNat ≤ peak.toNat`。

`index32` 对 exp=0 为0，否则是原 `UInt32` 减1；证明 nat 公式必须使用 exp>0 排除 word subtraction underflow。`UInt32.lt_iff_toNat_lt` 运输原 `if peak < idx`，无需为 UInt32 假设额外全序实例。前三项足够 getter；第四项仅供半径。

归约原 `Id.run` 循环时，先固定 Lean4.34 实际 elaborated state，不猜 mutable tuple 顺序。已核源码存在 `Array.forIn_pure_yield_eq_foldl` 与 `Array.idRun_forIn_yield_eq_foldl`；循环无 break，每次分支均 yield，可用它们把原循环归约至 fold 后做前缀归纳。不要仅证明一个新造的 pure prepare 而遗漏原 `prepare = model`。

## 后接 Tail 与半径

原 `sumRemaining a b index acc remaining` 的结构等式可直接对 remaining 归纳：

```lean
sumRemaining a b index acc remaining =
  Submission.R24RepresentationSum.loop
    ((List.range' index remaining).map (fun i => a.get! i * b.get! i)) acc
```

零分支由两个定义，succ 分支用 `List.range'_succ`、`List.map_cons` 与原 `loop`，保持加乘顺序和初始 `Float.ofBits 0`。该等式没有越界假设；精确数值解释必须再使用上面的 producer 长度和 getter 结论。

`NativeMul-v4.native_mul_exact_from_raw32_values` **已经是全 finite binary32 值接口**，不只normal，因此可直接接总finite widening，不需要重写乘法网格证明。仍需原 raw finite 证明及 `|rawReal w| < 2 ^ ((index32 w).toNat - 125)` 的 Int 指数版本；subnormal/zero 也满足此宽松界。两端 peak 的和 `H≤506`，从 `0<n≤2^30` 得原 `ceilLog2 n` 的 `L≤30`、`n≤2^L`。

于是 `k=H-250` 可喂给原 SUM3，误差为 `2^(H+2L-303)`。还须证明实际半径字 `((H+(L+L)+720) <<< 52)`：指数域在[720,1286]，无UInt64加法/移位截断、为正常正binary64，native值精确等于此幂。到此才是 actual producer→Tail 的封闭接口；B的真实orderKey/checker和最终FloatLib舍入/fallback另接。这里没有声称上述尚未实现的 producer/组合引理已通过。

固定源码：[FloatArray.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/FloatArray/Basic.lean)、[Array.Monadic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Monadic.lean)。当前本轮新Lean接受仍以D原回执为准。
