# 现任冠军比较与奖励口径核验

本次核验响应于用户明确要求“和现任冠军对比”。首次窗口的完整 gate 与内置基准提速仍成立，但未完成这一验收目标。

## 观察与推断

- 查询时间：2026-10-21 07:43 UTC 起；FloatLib 政策快照 506，政策计算时间 2026-10-21T07:08:50.136815+00:00；API 自报 freshness=unknown。原始响应、SHA-256 和查询时间见 receipts.json。
- VERIFIED：现任冠军为 #174，Kernel digest 为 67e44fd4b17186dbe6b1728dea49611288bb16d2586ebbb3a8a2f93aea74c009。官方详情与验证报告已取得；源码端点返回 HTTP 404，未取得冠军文件，不能执行同一 runner 的直接比较。
- VERIFIED：官方当前页面显示冠军相对起始内核约 8.7 倍加速。原始 HTML 保存为 official-floatlib-page.html。此项为官网展示的累计换算估值，包含多次运行的噪声，不是本候选与冠军的直接配对测量。
- VERIFIED：从 GitHub 工具取得的当前官方内置基准内容，经 current-shipped-response.json 精确还原后为 33043 字节，SHA-256 5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868，与本次 CI 内置基准逐字节相同。
- INFERRED：用同一起始基准作跨运行换算，候选／冠军耗时约为 0.967676975505967 × 8.7 = 8.418789686901912。这个约 8.4 倍的量级只作判断方向，不能作为正式成绩或精确名次；现有候选没有证据接近晋升门槛。
- UNKNOWN／NOT_RUN：候选与现任冠军的同机配对耗时、跨 runner 确认、正式准入及奖励。没有正式上传，没有执行资金动作。
- 之前“不能估算”的回答遗漏了官网累计速度指标；此次补充量级估算，不改写之前实际测量。

## 冠军与份额

完整正式包包含 add、mul、sum、bmm 与四个全输入证明。十二类输入（三类／函数）在默认 25 个配对轮次中运行；每类分别取跨轮最小值，再分别求和，headline ratio 为候选总和／现任冠军总和。四个函数没有固定 25% 权重。晋升还要求至少五轮配对证据、headline ≤ 0.97，以及 2000 次配对比值中位数 bootstrap 的收益 5% 分位数 > 0。

只有 full 槽支付，四个单函数不分配独立奖励。按官方 #174 类别 ns 数值分组求和，add、mul、sum、bmm 的观察耗时占比分别约 48.53%、47.11%、3.60%、0.76%；这只是该次测量中的时间组成，不是奖励份额。

最近三任未被显式移除的冠军 #174、#165、#155 分得 FloatLib 预算的 60%、30%、10%。政策 competition_share=20%，故对应验证者权重为 12%、6%、2%；政策权重不构成链上已到账证明。新冠军晋升后旧冠军依次后移，单纯出现在挑战榜前三不保证奖励。

竞赛索引还保留 DEFLATE 的 20% 旧政策，但其快照停在 2026-10-14、且已关闭提交；该值不与当前 FloatLib 政策直接相加解释为实时总分配。数学悬赏通过国库按题支付，也不属于四个浮点函数内部的独立份额。

## 官方来源

- 当前页面：https://conjectures.io/competitions/floatlib
- 当前政策：https://conjectures.io/v1/competitions/floatlib
- 当前冠军：https://conjectures.io/v1/competitions/floatlib/champions
- 计时与晋升：https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/main/docs/BENCHMARKING.md
- 奖励实现：https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/main/validator/reward.py
- 其他源码及 Git blob SHA：github-sources.json。网页和 API 原始字节及 SHA：receipts.json。

