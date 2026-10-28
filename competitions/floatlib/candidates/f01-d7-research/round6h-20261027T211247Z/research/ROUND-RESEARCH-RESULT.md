# R22研究成果与未闭合边界

共同窗口为2026-10-27 21:12:47至2026-10-28 03:12:47 UTC，北京05:12:47至11:12:47。D统一Git/CI，R统筹三Astra研究子方向；最后执行时段与容量故障见capacity-interruption.json及research-status.json。到共同截止停止新研究，已启动CI收齐。准备、协调、修复、复测和整理均计入本轮；不能把首末跨度当每个子agent连续计算时间。

## 本轮可复核结果

| 项目 | 实际证据 | 决定 |
|---|---|---|
| native冷尾公共ADD+MUL，f7ba/233664B | 406159原四义务、两模块回放、公理及25轮通过；固定统计whole/B2=.9555001521，gain_p05=−.0041730576 | 观测快4.45%，统计门槛未过；精确体停放，不采用/不启A/B/不追seed |
| Nat偏置证明资源 | 原24f0/Seed/401d各独有scope4GiB OOM；b9b只改外层简化策略、private quotient前缀不变，5.128s typingPASS；02ecd/14d约6秒typingPASS | 早期简化瓶颈得到控制；完整MathOutlet仍有类型目标，不闭原完整MUL；Rootd8备用未跑，不冒领D结果 |
| 矩阵数学接口 | 77a完整公共流式BMM38根；f7b19投影4根；7981机器字loop3根；均对应原statement/两模块回放/允许公理 | 已验可复用组件；后两者未形成完整新publicBMM，不继承速度 |
| 原生乘积数学 | 6589实际UInt64原生乘积字段桥5根通过 | 不是新publicMUL；后继directscale负面停放 |
| 其它成本路线 | Pair8、resident、Flat2、宽wordADD、far-only和ade4端点均有完整成本/原件 | 细小或不稳定收益保留记录，不扫seed或为负体铺大证明 |

所有headline为公开suite原协议，分清候选/reference再对B2/reference归一化；未改SUM的观测变化不归新增标量因果。当前保留B2；没有新正式竞赛上传、新冠军或奖励结论。

## 研究储备与下一决定

后续主要投入先给编译器8累加链ABI和缓存表示两个不同机制；狭窄E0特例只留低边际判别，避免替代较大路线。以下编号是优先级，不是已验证收益。

1. `independent-frontier/` 680ca1b3/1400B借用同ABI mutual探针：固定源码保留borrow信息，但机器跨边尾跳/RC/栈仍未知；toy不能当矩阵性能候选。普通UInt32/64.log2实际wrapper已见shift-counter loop，不能再假设BSR。

2. `streaming-public/floatarray-expected-variant/` f59d/237426B：B-only连续F64 backing仍逐项F32运算；checked native目标每字段少一个source.toBits表达式。16根、编译/实际caller/成本/完整publicBMM全未验；逆回旧f5a/303a及37cd已独立核。先成本，负面不扩证明。

3. 对MathOutlet只按原typed目标修正UInt64/Nat与比较方向，保持4GiB及原义务；先组件闭合，禁止盲跑旧整包或借有限模型替代证明。

4. `subnormal-cold-add/` 2292584c/807B：只改已测nativeADD的miss；双E0分数按符号精确整数加减，包括±0。旧sameExp的同sign子臂负面保留，不能称新算术或已提速。仍需完整guard/cold调用成本与公共证明。

## 资源与交付

- Pro在内置浏览器多次实时复查仍disabled/Usage limit reached，没有人机验证问题、未提交网页任务；研究由三Astra并行持续，不空等Pro。
- 主控发生capacity故障，原turn终止02:39:15、新turn恢复02:47:58，8分43秒空档单列。子agent自报情况分别保留，未知实际累计秒数写UNKNOWN。
- 固定原RNE两份MIT源码先存E:/Download/FloatLib/20261028-R22/rne-primary/20261028T014257Z，再逐字节整理到本分支rne-primary同名目录；14039B，无ZIP残留。本轮无本机Lean、大型工具链、正式上传、资金或账号重置。
- 当前唯一根入口为HANDOFF.md/research-status.json；各子当前索引从该入口引用，旧UNKNOWN/失败/原件保留。D按持续授权提交推送全部本方研究产物；远端回执另核，未收到前不声称全已推。
