# DirectBias 当前：成本复核无稳定收益，精确运行体及大型证明停放

R截止2026-10-27 02:28:21Z；D窗口不改。只写本目录，无Git/CI/本机Lean/新运行版本。B2保留。

- **最新实证**：CI12 40430974047/f4211856，精确2177数学模块在B2-import上下文−15/24.132s，stdout0；唯一scope达到4GiB，Result=oom-kill、OOMPolicy=stop、oom_kill1。9原件含B2绑定 `math-review-40430974047.json`。没有typed goal，新48根/replay未运行。CI11 fa652−15/30s无采样，历史原因继续UNKNOWN，不能由CI12回填。
- **停放决定已生效**：D在01:53 development-batch14-live.md接受独立caller成本审核；R01:49已给同条件决定。CI13四block未显示稳定正收益，停止为精确7489运行体购买大型public证明，两个共享数学helper不排队。诊断负面不等于原完整D或算术机制普遍慢；异常SUM/Bool捕获样本均保留。
- **精确后继**：`shared-block-isolation/NatPostClosure.lean` 4877B/cbdb2fb8e83908a6c6179c286b1648891c0186727db53b6d635a5af2689b8f31；`NoWrapOnly.lean`1821B/8d49e866e3ea7257af5d78709dea54b8b805a7a7f66f7e39ed74e98e8050fe39。分别原Natseed+PostBias、原biased_sum_nat逐字切出，无proof/runtime/域修改。两独立进程，原caps；首段失败不逻辑阻断另一段，base失败/预算不足才停。源和决定表见该目录manifest/HANDOFF。
- **禁止误修**：CI10原quotient-only已exit0/5.905s，7b03/70d4继续HOLD。三份失败源除了六Nat定理，还共有旧word_grouped复制到新biased_sum_nat的1338B无回卷块（bfa7d6f5…）；声明名交集不能排除它。`failed-source-intersection.json`仅记录共性，不定位cause。
- **公共源保留**：`public-proof-review1/Kernel-direct-bias-public-v1.lean`255311B/fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5；`MathOutlet-interface-v1.lean`32332B/2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266。48根、原f3e86842运行体/guard不改。静态gate通过，9旧证明叶删除/逆patch已核；余689B，另1756B只读储备。无第3proof实现。

Jam b271真正public的完整D负结果whole.998885/p05−.010815继续停放；GRS a78a1534一次独立审查报告在../grs-jam-independent-review.md，未改其源/未宣称publicADD通过。下一真实反馈优先；未测写NOT_RUN。token/cache UNKNOWN，直接CI0。

收尾身份核验：10个关键冻结源SHA全部再次匹配，含b271、fa652、2177、7b03/70d4及两helper；总清单../FINAL-STATE.json。无新采用/正式提交；后续只有新成本前提或明确独立数学目标才恢复此分支。
