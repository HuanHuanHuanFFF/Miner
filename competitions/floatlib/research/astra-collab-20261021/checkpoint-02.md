# R 检查点 02：零回退频率与 sum 直接循环

2026-10-21 10:44 UTC；读取了 D 对 R-01 的采用反馈。R 的 bmm 原包继续冻结，不增加 bmm 变体。

## 可立即采用的 sum 检查

`candidates/f01-r1-direct-sum-loop/Kernel.lean` 已冻结，SHA-256 `5187f6bb52fd18e70dd561e4221f2f376616729c23530d625a9f640928c75e90`，33505 字节。只改 sum：显式尾递归、Binary32 累加器、带界证明的 Vector.get；所有标量与 bmm 保持起始参考的定义。证明桥接使用 `Fin.foldl.loop` 逐步等价，再以 `Fin.foldl_eq_finRange_foldl` 改写到原 sumSpec。四义务齐全，但 **NOT_COMPILED**。

按 D 反馈准备此独立候选。D 有验证余量时复制到自己的目录，优先检查与 R-01 相同的递归证明是否能通过，再完整 gate 与 C 核对。若两者在同一展开／dependent-if 点失败，先统一修桥接，不增加相似候选。

## 零回退：执行的有限模型

`fallback-probe.py` 逐位整数舍入模型重放 pinned 三类官方生成器，seeds=211/2654435769，每类每 seed=500000 次累加；本地约20.77秒。先对60000组有限 add/mul 与 Python binary64运算后转binary32核对，并检查6个零／次正规边界。结果与源码哈希见 `fallback-probe-result.json`。

| 运算 | dense | relu | wide |
| --- | ---: | ---: | ---: |
| sum 的 add 零回退次数占比 | 0.1% | 50.1% | 0.1% |
| bmm 的 add 零回退次数占比 | 1% | 51% | 1% |

两个 seed 都得到上表。dense/wide 没有观察到非零相消成零，零回退都来自每次归约起始 +0。relu 的零乘积恰好50%，生成器最低位交替造成这一结构。wide 中非零加法指数差>39占 sum约22.9—23.0%、bmm约50.0—50.7%。这些只是实际执行模型的路径频率，**不是目标计时或耗时占比，也未与 Lean 官方 checksum 对账**。

决策：零捷径值得作为 relu 的独立组件，无法仅凭路径次数解释 dense/wide 巨大差距。优先等待直接循环判别；在未看到收益前，不应为整个新加法算法投入长证明。

## 可复用的精确零桥接

真实 pinned `FloatLib/Numerics/Exact/Dyadic/Arithmetic/Runtime.lean` 的 `Dyadic.addFields` 已在左/右 significand=0时直接返回另一 dyadic；两者均零时符号取 `leftNegative && rightNegative`。

用于把 dyadic 恒等式提升为原位模式的公开定理已定位并核对 pinned 源码：

`FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean`

```lean
Model.roundDyadicWithRounding_toDyadic?
  (hfmt : fmt.isIEEE = true) (mode : IEEERoundingMode)
  (hd : Model.toDyadic? x = some d) :
  Model.roundDyadicWithRounding fmt mode d = x
```

nearestEven 分支定义上是 roundDyadic。通过 `TunedAdd.dec_eq`、`dec_word`、`word32`、`addFiniteImpl_eq`、`addFinite_eq` 可先归到 Model；非零另一操作数用该 round-trip 定理；两零用 `Model.roundDyadicWithRounding_zero` 保留 AND 符号。最后用 `ExecFloat.ModelCodec.decode_injective` 回到 Binary32。仍需证明位 guard 与 Model.toDyadic?／significand 的联系，以及查完整公理依赖；这里交付的是可执行证明路线，非已编译证明。

全域保护顺序：先对任一 exponent=255 保留原实现；再处理一零非零；两零返回 `a & b & 0x80000000`；其他仍原实现。可从仅“右操作数为 +0 且左为有限非零”开始，避免同时搬入所有特殊情况。

反例已执行：`+0 + -0 = +0`，所以左零一律返回右值错；`-0 + +0 = +0`，所以右零一律跳过也错。`0×Inf` 的 NaN 情形不在有限模型内，必须继续原 fallback，不把有限模型外推。

## 来源与局限

上述版本为 FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`。检索会返回更新版本 `1f5771...` 的位置，已重新取 pinned 文件；特别是 round-trip 在 pinned 版本位于 Conversion/Text/Representation，不能照搬新版本 DirectedSemantics/Exact 路径。来源、正文、SHA 在 research sources/ 和 receipts 中维护。没有新 Lean 实验，没有正式上传。
