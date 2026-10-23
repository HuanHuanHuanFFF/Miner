# 单次联合 normal-band 判断：一次限定重访

决定：仅生成 `f01-d11-scalar-normal-band` 一份候选，SHA256 `e279b35413de1a753dc38edafcca3f476745390ede518ddeab93f0ccc1b8ef1d`，240454 B；不做范围网格。它是旧数值转换／守卫融合路线的限定重访，不称为全新机制。新语句、完整gate、实际C/asm与收益全部 NOT_RUN。

## 核对的历史

| 历史源 | 真实边界和结果 | 本次关系 |
|---|---|---|
| R4 scalar-decode `a7dca716…`，run39746211363/seed504 | 精确源SHA已重核，原verdict为score/PASS。普通mul使用已有numeric convert覆盖E24..254及zero；三类mul合计归一化1.037478，near-one单类0.915636，spread1.046081，tiny1.061716 | 不能无条件再次全面numeric-mul；新域64..191排除旧tiny双输入域，减少spread命中，保留near-one。旧局部正结果只支持一份有边界的检验，不是新收益预测 |
| R6 normal-add-proof1 `8a0e40fb…` | 精确源SHA已重核；normalOK是每个word一次回卷区间判断，两输入都命中后直接tableProduct相加。706完整PASS；719公开套件整包归一化0.99700522，add约0.98936，仅一组发现样本 | 这已经做过守卫融合。新联合OR只减少为一次比较、缩窄域，并改接目前result-selfBEq父本；不是以函数改名重新卖同一机制 |
| 939 exceptional-word `939dbf31…` | 精确源SHA已重核；改的是至少一侧exp255的原冷分支，正常数／LowScale仍父本；manifest和runtime-review写新完整Lean与性能NOT_RUN | 不能把939表述为本band路线经测负面。它和本次普通数front door属于不同域；目前也不把其未知冷路收益拿来补本次预算 |

R4逐类证据由 `low-normal-history-review.md/json` 追到原两份verdict；`f01-d4-global8/window2h-20261022/same-batch-comparisons.json` 记录同批归一化。R6原结果见 `astra-collab-20261022-r6/checkpoint-11-first-full-results.md` 和 `public-suite-719.json`。当前41结果守卫及实际scalar调用上下文见 `round1h-20261023T110107Z/compiled-context-review.md`；新包不继承任何历史速度结论。

## 新入口与证明范围

确切guard是 UInt32位或：`((mX-0x20000000) ||| (mY-0x20000000)) < 0x40000000`，m为去符号mag。真实接口是 `Nat.left_le_or` / `Nat.right_le_or`，不是未核对的`Nat.le_or_left/right`。结合`UInt32.toNat_or`可分别推出两个回卷offset<2^30，再以UInt32减法的Nat等式和omega推出旧`NormalBand`。实现只需要guard的充分性；完整区间等价目前仅有有限位模式诊断。

命中后直接tableProduct两输入→一条native add/mul→ofFloat32。`normal_eq`、`normal_finite`把真实字解码接到现有finite native运算桥和raw精确roundtrip；不需要结果selfBEq，也不排斥乘法溢出为Inf的正确结果。零、次正规、极低／极高normal、NaN/Inf都miss，仍走原a066。命中指数都≥64，因此两指数和至少128，不会覆盖原`exsum<128`的LowScale路径。

旧add/mul及spec在原位置局部改名保留；nativeMul保持原名原体。新两个公共入口及spec插在原`add_eq/mul_eq`之前，后续所有sum/BMM/replay等价都接最终函数。没有重复同名常量，没有引用后声明的R7Word。逆变换恢复父a066所有字节；现有tensor运行定义均不改。

## 投入限制与下一判别

每个scalar miss仍先支付两mask、两sub、一OR、一compare；tableProduct在mul hit新增整数转float、表读和缩放乘法，可能重现旧退化。原selfBEq是否最终外调、命中是否消除重复守卫，要看实际MainFull调用体，不能凭源码call计数断定。Regular NativeFinal/packed BMM及SinglePass循环不逐步调用新scalar；只有replay/reference/repair可受影响，因此不预计由此自动获得矩阵热循环收益。

本次新增3312 B，低于18k预算，guard有限诊断2379296对字通过。最小下一动作是Root决定是否给这唯一原型一次精确statement及完整逐cell比较；若同runner没有明确收益，就PARK，不继续变换区间端点。矩阵结构与整数组下溢零仍是本轮主线。
