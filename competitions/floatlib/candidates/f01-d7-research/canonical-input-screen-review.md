# D16：raw 非 NaN 输入冷扫描的反方审查

结论：**完整原顺序 sum/dot 从 `Competition.posZero` 开始，所有实际读取的原始 raw 输入均非 NaN，而对应 native 终点是 NaN，则完整 raw 规格结果必为正 canonical `0x7fc00000`。** 这是基于固定定义及已验组件的静态数学推导（INFERRED）；本次未编写新证明、候选或扫描器，**新 Lean 命题、原版完整 gate、性能均 NOT_RUN / UNKNOWN**。未发现满足完整前提的反例。

范围：2026-10-22 22:37:27 UTC 起，25 分钟预算；只写本报告及同名 JSON。FloatLib 固定 `0d91825727839f597fd06b22fdd038ea21480f0c`，Lean 4.34.0 / `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`。完整原件路径、字节数、SHA-256、历史 exit、41 个定向用例见 [JSON](canonical-input-screen-review.json)。网页原件均 LOCAL_ONLY，仍在既有 `research/astra-collab-20261023-r7/web/R7-W05/original-extracted/R7-W05/`，本次未复制原件。

## 精确命题和简短归纳

令 `C = 0x7fc00000`，`P(w) := raw.isNaN(w)=false ∨ w=C`。sum 检查全部 `x[i]`；dot 检查每个 `k<n` 的 `A.getD (baseA+k) posZero`、`B.getD (baseB+k*p) posZero`。BMM 还须用实际输出的 `bmmDecodeC`，即 A 地址 `(b*m+i)*n+k`、B 地址 `(b*n+k)*p+j`。该命题对所有 Nat 长度成立；USize 只属于实现选择，不能缩窄原义务。

+0 和所有筛过的原始输入满足 P。固定 `Spec.add/mul` 的有限 rounding、zero、overflow 分支返回非 NaN；invalid 分支返回 C；NaN 选择只能选到 C，而 `quietNaN C=C`。所以 P 对原顺序 add/mul 封闭，依序归纳到完整 raw fold。dot 必须先分别舍入 mul、再 add；乘积及 accumulator **可以成为 NaN**，归纳只保证此时恰为 C。

随后使用 W05 的**正向** canonical 投影及精确 isNaN 分类，把实际 native 终点 NaN 传回 raw 终点 NaN。P 的非 NaN 分支因此排除，只剩 raw=C。这没有从 `toFloat32` 等式反推任意 raw 逆像。

固定源证据：Carrier L272–273、L300–302、L338–354；Dyadic Spec L37–52、L70–92。两份本地原件的 Git blob SHA 分别为 `8849d6b29facd7ccff8d1f32e2b15626d0771023`、`2204e7bd34af9f7d82469ecae247eb2942d78e73`；JSON 另存 SHA-256。

## 必须保留的条件

| 项 | 精确边界／反例 | 源定位与处理 |
|---|---|---|
| 种子与范围 | 只扫后缀而允许任意 accumulator 时为假：seed=`7fc00001`，suffix=[`3f800000`]，raw 仍为 `7fc00001`。 | ContractTensor L19–25、L55–64；必须完整 +0 fold，或另外证明起点 P 及 native 匹配。 |
| 原输入与中间值 | `+Inf + -Inf`、`0×Inf`、overflow 后 opposite Inf 均可从无 raw NaN 输入产生 C。全有限 dot 也可先形成 +Inf/-Inf 两个舍入乘积。 | Dyadic L37–52、L70–92；不能把“输入非 NaN”误作“中间非 NaN”。扫描谓词须允许 Inf；用 isFinite 虽安全拒绝，却会漏机会。 |
| BMM 实读地址 | `batch=1,m=1,n=2,p=2,A=[1,1],B=[0,0,7fc00001,1],j=0`：正确 B 读 [0,2]，连续扫 [0,1] 会漏 NaN，raw 输出为 `7fc00001`。 | ContractTensor L33–64；60f L2690–2697、L3020–3027、L3607–3611。逐输出／lane 证明 screen=true 覆盖实际读。 |
| default getD | 泛用 dot 的越界读为 +0；空 A、B=[+Inf]、n=1 会因默认 `0×Inf` 产生 C。未读 storage 中的 NaN 不相关；多扫只会保守拒绝。 | ContractTensor L33–34；60f L2921–2926。先证明地址在界内再 uget，或保留相同 getD。 |
| Nat / USize | n、base、`k*p`、地址加法都要对应 Nat，不仅 n 安全。若 `n=USize.size` 盲转 count 则为 0，首项 qNaN 其余零的形式输入可被空扫描误接受。该巨大向量未分配／执行。 | 60f L3173–3202、L3380–3419 已有受护 USize 与 Nat 后备；新 scanner 需独立地址无 wrap 证明或 Nat 后备，不能继承旧 A guard 覆盖 B stride。 |
| 空输入、±0 | 空 sum/dot 是 +0，all 条件虽真，native NaN 前提是假。±0、subnormal 消去都是允许的非 NaN。 | ContractTensor L19–25、L55–64；不能只凭空扫描成功返回 C，也不需额外 n>0。 |
| 返回 raw 字 | native add/mul 在 C header 为裸运算，硬件 NaN 的原始 sign/payload 不应直接假定。现有 `ofFloat32` 经 `Float32.toBits`，固定 runtime 明确将 NaN 返回字规范为 `7fc00000`。 | FloatLib Native L120–122、L137–139；Lean object.cpp L1995–2003，header L3255–3257。沿该 codec 或直接构造已证 C；新机器码仍 NOT_RUN。 |

## 放宽 raw NaN 的最小反例

以下是原 +0 seed 的完整操作，native 投影均为 NaN；raw 字与正 C 不同。选择规则优先 sNaN，再从左到右选 qNaN，quiet 不清除 sign/payload。

| 放宽 | 最小原输入 | raw 输出 |
|---|---|---|
| 任意 qNaN | sum([`7fc00001`]) | `7fc00001` |
| 负 qNaN，payload 零 | sum([`ffc00000`]) | `ffc00000` |
| 任意 sNaN | sum([`7f800001`]) | `7fc00001` |
| 负 sNaN 的 dot | dot([`ff800001`],[`3f800000`]) | `ffc00001` |
| invalid 后仍允许 sNaN 的 sum | sum([`7f800000`,`ff800000`,`7f800001`]) | `7fc00001` |

只允许 C 本身作为 NaN 输入与 P 相容；“允许任何 NaN 必失败”也是过强断言。dot 的后续原始 sNaN 先经 mul quiet，已有 C accumulator 会吸收它；sum 的后续原始 sNaN 可直接覆盖 C。这说明 M22 的 dot 吸收不能原样套给一般 sum。

## M21 / M22 / W05 实际能提供什么

| 已验源码 | 本次核对的真实接口 | 不能据此跳过的环节 |
|---|---|---|
| [M21 c760](../f01-r7-nonnan-runtime/Kernel.lean) | `Submission.NotNaNProbe.modelCanonicalOfNotNaN` L2380、`roundtrip` L2389；`R7Native.modelAdd/modelMul` L2536/L2595；`ofFloat32Add/Mul` L2618/L2636 都要求两个 native 输入非 NaN，允许 Inf。805 原始 summary 绑定 c760、exit=0、full-gate=true；verdict hash 与原日志相符。 | NaN 终点不能使用非 NaN roundtrip；invalid 后也不能继续声称 accumulator 非 NaN。 |
| [M22 9a](../f01-r7-nan-replay-fullpath/Kernel.lean) | `Submission.R7NaNReplay.replayStep_absorb` L2811、`replayFold_absorb` L2819、`replayLoop_eq` L2840：quiet accumulator 对后续任意原始 mul-then-add 项逐位吸收。806 原始 summary 绑定 9a、exit=0、full-gate=true。 | quiet accumulator 可带任意 sign/payload；吸收不会使它变为 C。一般 sum 的原始 sNaN 输入不满足该 dot 结构。 |
| W05 LOCAL_ONLY `R7W05.lean` | `toFloat32_isNaN` L1699；全输入 `add_toFloat32/mul_toFloat32` L1797/L1948；`sumFold_toFloat32/dotFold_toFloat32` L2146/L2216；实际 `sumSpec_toFloat32/bmmSpec_toFloat32` L2177/L2256。源码 SHA=`7ebaf282…bf7382`；原始 compile/diagnostic exit 均 0，成功快照与源码逐字节相同；所引投影定理的原公理日志均仅三允许公理。 | 这些是正向 canonical 投影，没有保留 raw NaN 元数据；需要新增 P 闭包并组合到 60f 的具体 loop、地址及 scanner。网页固定证明与候选原版 fullgate 分列。 |

新证明所需的最小组：① C 的实际字、quiet 幂等、非 sNaN 常量事实；② `Spec.add` 的 P/P 闭包，`Spec.mul` 的非 NaN/非 NaN→P（或统一 P/P 闭包）；③ 经实际 `toModelExecAdd/Mul`、carrier 注入搬回 Binary32；④ +0 原顺序 sum/dot 的 P 归纳；⑤ W05 正向投影与 60f 的 `NativeDecodeSumWord.run_eq`、`NativeDecodeSum.loop_eq`、packed lane/runDot 等式组合；⑥ screen=true→全部实读非 NaN、末态 NaN→raw=C、最终 codec 字=C。建议命题见 JSON，均明确标 NEW_REQUIRED，未伪装成已存在名称。

## 本次验证与最小外部证伪

41 个定向模型用例全部匹配逐项期望，其中 17 个满足完整前提、0 个反例；含 ±Inf 次序、±0、空输入、0×Inf、有限 add overflow、**全有限 dot 的相反溢出乘积**、±payload、invalid 后 sNaN、种子及错 stride 反例。模型复用已固定 `nonfinite-oracle.py` 的整数转录；其“native”只定义为 canonical 投影，双方共享转录，**不是 Lean、真实 native 执行或独立形式证明**。不跑随机／大规模枚举。

只读重算既有 807 统计：70 tensor 中 280 个已存 actual-checksum 比较标记均 true；**timed** sum=4 输出/188 replay 步、BMM=671/7551；加入未计时 `bmm:check` 后 BMM=747/9451。未重新运行这些 tensor 或原 checksum；这些是机会计数，与 R 前缀／后缀路线重叠，不能写作收益。

首次外部检查只需先关闭上述精确 Lean 命题并回收实际公理日志，再用最小 witness 核原义务、地址/default、USize 后备；随后核生成 C/asm 的普通路径不变、冷扫描地址及返回 codec。只有精确候选原版完整 gate、完整成本配对计时和独立新 runner 确认，才能报告新正确性接受或收益。本次未触发 Git/CI/上传。

