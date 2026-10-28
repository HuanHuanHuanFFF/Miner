# 入口之外：共享乘积吸收证书的首判别

**PARK 当前公共约 10% 主线，不造候选或 CI。** 这是一个新的成本前提分析，数学原型未接 Lean，未声明性能。旧 cross-batch A4/B8、singleton 首乘积负零修复、SUM 块吸收均已核历史，不能重复命名为新路线。

与 R20 SUM 扫描不同的实质变化：BMM 为每段 k 计算原 A 行块的最大 raw exponent，跨 p 列复用；原 B 列块最大指数跨 m 行复用。若当前点积非零 normal accumulator 远大于两头能产生的所有原始乘积，跳过这一整段原顺序乘加。这里不合并乘积、不重关联，也不把 native NaN canonicalization 当原始 NaN payload 等价。NaN/Inf 头、零 accumulator、证书失败均走原路径。

一个保守充分域的纸面推导：设 accumulator raw exponent 为 e∈[26,254]。块内所有 A/B raw exponent 的最大值 ea/eb 均<255，且 ea+eb≤e+99。有限 binary32 幅值满足 |a|<2^(ea−126)、|b|<2^(eb−126)，含 subnormal 与零。因此每个精确乘积严格小于 T=2^(e−153)。T 的指数范围为 −127..101，是可表示的有限 binary32；RNE 单调且固定 T，故实际单次舍入乘积幅值≤T<2T=2^(e−152)。后者正是 R20 保守双符号吸收阈值 2^(E−25)，E=e−127。每一步相同 accumulator 是固定点，按原 k 序归纳可跳整块。此处原 product 仍先舍入；不是 FMA 或精确实数替代。待证的是这些界到真实 FloatLib 原 mul/add 的桥。

首个最小证伪先用固定块长 4 的全 case 触达上界，不扫描新输入。原 R22 四组发现成本中，所有 n≥4 case 的全部时间仅占整包 **9.84%、10.16%、11.48%、11.33%**；入口外部分分别 **6.75%、7.03%、4.10%、4.03%**。即使把这些 case 整个删除，一组仍不足 10%；其余需要近乎消除所有时间。真实方案还保留初始不能吸收的 +0 段、输出、未命中、准备和回收，不能把这些数当收益预测。已有 SUM 单用扫描跳过低、附加 raw 读取高的负结果依旧有效，但未直接测这个 BMM 复用方案。

若将来一个独立允许研究的分布给出更大范围，下一最小实验也先只读：固定块长 4，逐原 prefix 运行精确 oracle，按上述 guard 统计跳过的真实 MAC、两种头的唯一读取与复用次数、每 checkpoint 的 acc.toBits 次数，以及 miss 重读。保留每条原 rounding、第一步 +0、NaN/Inf/±0 和 binade 下沿反例。先要求可删除工作足以覆盖新增扫描；随后只做一个实际入口完整调用成本，不扩块宽网格。当前没有满足这一投入条件。

重放：`shared_block_frontier.py` → `shared-block-frontier.json`，绑定 producer 的原 cost-frontier 哈希及其原始回执列表。历史对照：R20 `research/mathematical/HANDOFF.md` 与 `next-round/opposite-sign-absorption.md`；R22 `development-prepared-resident8/NEXT-REFACTOR-DISCRIMINATOR.md`；旧 `seed-normalize-design.md` 与 `singleton-normalize-review.md`。没有把旧发现输入当作新的独立确认。
