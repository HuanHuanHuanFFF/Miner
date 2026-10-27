# GRS硬界pre-guard：唯一成本备选，NOT_RUN

2026-10-27 01:45Z；根12min追加判别，主窗02:28:21Z不变。原7737未改，无CI/本机Lean/新public证明。

- 纸面统一界T0或4≤T≤2^28−16，numeric exponent129..154；**eBig25..253**保证postE1..254，T0仍先+0。两端不能凭统一界再放宽。mod32 `mid+(((eh−153)<<23)+sign)`等于原字段pack，未增加native假设。
- 直接目标：取消codec之后的fallback与E/pack，只让delta跨call，移除7737已见raw-v/abs-v两热栈写的活跃原因。实际frame/寄存器仍未知，须完整diagnosticEntry验证；非阈值调参。
- 历史f7f/R17仍post-result guard，R6/R7 input guard及旧rebias概念已知；未找到这一个GRS硬界+delta/死值机制的已测负样本，查阅范围及旧失败保留见PAPER。
- 同三旧组/原256点：命中9436/8815/9534，原9754/9389/10258；F代理31.304%/29.385%/31.740%，10%whole需eligible省31.506%–34.031%。端点21例+旧样本准入均对原typed及整数oracle相同；非Lean/计时/严格上界。
- 片段1857B/**75e3740a…**；完整B2append228686B/**d3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5**，`Kernel-grs32-pre-guard.lean`。同7根/逆patch齐，manifest SHAfd7667908f8de07b695f9f6cf68a160c91f66fa33f6ab774be3d1ff5fee11201。只给D备选不自动排队；若实际C不消除对应保活/热spill则停，不开更多变体。
