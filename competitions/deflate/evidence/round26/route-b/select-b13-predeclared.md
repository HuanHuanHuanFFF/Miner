# B13 ordinary inherited-distance reselect

缺口：B12 原轨迹全部 12,257,237 个继承前缀字节有效，但只有约 0.060% A 位置的旧 best 被更便宜的已提供域改善。局部模型不能回答原编码器是否获益。固定-only 漏前缀需 8.82M 新归约，绝大多数改善为同价短 tie，本次明确不恢复它，也不改其端点。

实质变化：只为原普通 record 的已提供长度，在现有继承前缀覆盖且当前 distance 价更低时增加该距离选择。保持所有原匹配、XL/XD、record 最大长度、PD、原 uncovered extension、价格重建与 passes。每个被选中的普通域只扫描一次；同一 cost/lc 读取产生原 packed 值及 `v.wrapping_sub((oldD-newD)<<9)`，分别保留两个 min，最后只有严格胜过原最终 best 才采用新距离。不能对原 interval min 作一次减法代替逐项新比较。固定端点／前缀均不新增。

消费成本：每个 DP invocation 内随原 XL/XD 携带一个 U32 价；max-record fallback 复用该 record 已读 dc，原继承 extension 距离不变，价也不变；每个 pass 的价格数组固定，不跨 pass 缓存。新增 preceding-byte guard、普通 record 价判断、helper 归约、价状态写都计入真实 A DP 包含成本。省掉观察器完整-prefix check 依赖原记录有效性／递推边界，原最终 emitter 的独立 check 仍保留；B12 公共前缀有效不能替代完整 gate。

旧反例与界限：R8D 重选未获字节收益；本次新增来源不同，但仍只允许一次完整质量判别，不扫阈值／价格／passes。B12 位价差不当作输出字节。父时间下 29805 条件规划约需减 .00577pp/.00877pp 才到 5/10%，不是私有保证；微小字节变化不自动值得 paired。

最小操作：一份候选 `r26-b-552-overlap-select`，全部 28 输入原 encoder/token/decode 与原552比较；只对 parse/A_engine/A_find/A_dp whole-call 作低频粗剖析（不计每pair/helper时钟）。native 20 分钟 cap，root 统一调度。事前完成源反撤销、brace/function-span、完整 round4.validate/round26-preflight、100k packed-point/10k domain/131072 code有限模型。精确原 Lean 保留但 DRAFT，当前无提取／paired／完整证明／正式提交。

改变选择：若实际质量微弱或更差，本轮直接 NO_GO，不加更多重选修补；若可见质量收益与新成本有足够空间，再用最新官方同一快照作二维判断，按 root 统一预算考虑原协议计时。正式分红仍须正式结果。
