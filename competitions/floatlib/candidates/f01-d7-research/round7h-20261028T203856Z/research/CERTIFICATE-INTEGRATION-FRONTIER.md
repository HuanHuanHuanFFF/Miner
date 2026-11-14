# FP64 点积证书：运行时代码与证明之间的剩余接口

UTC2026-10-29 03:04，R首次整合；不扩大比赛目标，不修改运行时或官方门槛。实际性能原件与数学源分别验收。

目前最强的成本证据是 `40804860824`：64进程、9408条原始ns可独立重建，Tail full/lazy 的49样本中位耗时之和相对自建UInt64/128参照降低27.5%–32.9%。该比例含每次调用的准备、失败回退与临时值释放；prepared主循环比例不含首次准备。固定MAC的合成混合不是模型权重，也不是新runner确认。完整运行时正确性仍UNPROVED。

## 必须按真实表达式接合

| 接口 | 当前证据／源码 | 尚缺义务与最小判别 |
|---|---|---|
| UInt32 有限值 → Float64 | `WidenNormal5`及待定点修复的6；`SubnormalWiden-v1` | normal主组合在Math8仍有两处嵌套Nat→Int→Real cast失败。subnormal草稿未编译；另需实际零分支、`prepare`循环不变量、size/getter、valid与maxIndex对应原输入，而非仅单word值公式。 |
| FloatArray读取及FP64逐项乘法 | `NativeMul-v4`、D的getter/fold接口 | 两个binary32乘积精确可表示的引理须绑定实际widen值及getter。不得把所有Float64乘法当精确；normal、subnormal、零与符号都需实际前提。 |
| 未装箱tail循环的误差界 | `NativeSumEnclosure3`、dot-enclosure草稿 | 这些片段原本针对既定循环。需要把实际Tail显式递归、同序读取与误差引理接合；C/ASM无装箱只证明编译形态，不能代替等价或误差证明。半径H和L来自实际Prepared，不得直接作为已正确的ghost输入。 |
| `radius = ofBits((H+2L+720)<<52)` 与两个native端点 | `RadiusEndpoints-v1` | H≤506、n≤2^30、ceilLog2/maxIndex的实际word无溢出；从原输入和循环得到sum有限及大小界，继而得到两个加减端点有限。该片段先证明有限再调用native RNE，不把有限作为结论前提。 |
| q的真实raw32字段 → lower/upper raw64 | `MidpointWords`、`MidpointReal`、`NativeSignOr`、`RawMidpoint` | 草稿包含normal e=1..254、最小正规lower不同间距、负号OR与交换。均需Lean接受及实际`certify`展开后的表达式等式；不能仅由Real等式推raw字相等。 |
| **实际`orderKey`比较 → Real严格序** | `NativeCompare`只针对`Float.lt`，并不等于当前运行时的UInt64比较 | 当前执行表达式是`decide(orderKey lower < orderKey lowerEndpoint)`和另一端比较。需有限raw64的排序键定理。`key(-0)<key(+0)`而Real相等，因此一般的严格等价为假；这里normal q的边界必非零，可以证明“有限且至少一端非零”的严格比较运输。不能直接引用Float.lt桥声称已接上。 |
| 严格夹入normal q的cell → 实际binary32 rounder | `NormalCell`、`DyadicAgreement`、`DyadicCell` | 正负、最小正规和最大有限已在草稿语句范围；绑定实际精确dot的sign/N/exponent及已有roundDyadic定义，再组合。任意proposal无需先证明cast正确；只要被证书接受。所有新终端桥目前NOT_RUN。 |
| miss sentinel及实际fallback | `Adapters.lean.inc`、实际old exactdot | q通过e=1..254筛选，0只作miss。需要证明接受⇒原rounder精确同word，失败⇒保留原fallback全部输入语义。不能把诊断参照的canonical NaN当正式NaN policy，也不能忽略exactdot的有符号零分支。 |

## 下一轮投入顺序

先关闭最小类型失败并保存精确主组合replay/AX回执；该组合通过仍只代表其片段范围。然后用一个最小certificate checker组件，直接以真实`orderKey`和raw字段为目标，补“有限且边界非零”的排序运输。它比再增加proposal精度、四链浮点或一组新合成种子更接近可采用代码。

性能侧优先共享行／列缓存的矩阵调用，计入准备、失败回退、所有输出生成与释放；只有实际矩阵收益保留后才投入大额完整producer/consumer证明。完整门槛、冻结和新runner确认继续按原规则，不能从这些成本进程继承。两链精确UInt64/128路线保留独立源码与反例，当前没有编译形态或速度结论。

到本轮截止未完成的接口保留为UNKNOWN/NOT_RUN，不把静态复核、有限数值检查、片段通过、整包成绩四层合并。
