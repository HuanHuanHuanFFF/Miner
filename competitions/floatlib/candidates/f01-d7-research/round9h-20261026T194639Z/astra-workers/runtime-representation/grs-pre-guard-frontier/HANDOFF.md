# GRS硬界pre-guard：CI15定义接受，CI16诊断成本负

2026-10-27 02:21Z最终窄验收更新；R主窗02:28:21Z不变，后续成本细审交D独立预算。原7737及d3c源码均未改，本方无CI/本机Lean。

- **真实接受范围**：CI15 **40435830288/5ad212c887ed3c55b35958704bef7f4fef344fdc**，精确228686B/**d3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5**，statement、Submission/VerifyFull两模块重放、7根允许公理PASS。7根是4旧B2spec+3新定义，**不是新ADD等价、完整gate或性能通过**。原manifest的NOT_RUN保留为创建时历史，当前绑定见`accepted-40435830288.json`。
- 根已核CI15的135原件/8156225B；本次仅亲读原verdict、replay、7根日志及C索引，没有重复全hash。CI15 MainFull仍B2。
- **CI16在本窄验收中途02:20到达，替换先前未到快照**：40436948264/a6c82956，原result报告两旧plan、各control-guarded-guarded-control完成，checksum一致；ADD四块比值**1.505067/1.489358/1.497546/1.483944**，诊断组合总时**1.175671/1.176789/1.197037/1.204368**。只读caller源与closure检查：两个独立noinline、arity2/0captures入口，control调用B2 add，guarded调用d3c guardedAdd+原B2 fallback；Bench.Suite.run只换ADD，mul/sum/bmm旧B2。不是原25round/fullgate/新ADD等价验收。最短回执`ci16-short-result-40436948264.json`；没有重跑或长C/ASM细审，后续交D独立预算，保留负结果，不推进采用。

- 纸面统一界T0或4≤T≤2^28−16，numeric exponent129..154；**eBig25..253**保证postE1..254，T0仍先+0。两端不能凭统一界再放宽。mod32 `mid+(((eh−153)<<23)+sign)`等于原字段pack，未增加native假设。
- 直接目标：取消codec之后的fallback与E/pack，只让delta跨call，移除7737已见raw-v/abs-v两热栈写的活跃原因。实际frame/寄存器仍未知，须完整diagnosticEntry验证；非阈值调参。
- 历史f7f/R17仍post-result guard，R6/R7 input guard及旧rebias概念已知；未找到这一个GRS硬界+delta/死值机制的已测负样本，查阅范围及旧失败保留见PAPER。
- 同三旧组/原256点：命中9436/8815/9534，原9754/9389/10258；F代理31.304%/29.385%/31.740%，10%whole需eligible省31.506%–34.031%。端点21例+旧样本准入均对原typed及整数oracle相同；非Lean/计时/严格上界。
- 片段1857B/**75e3740a…**；完整源`Kernel-grs32-pre-guard.lean`，同7根/逆patch齐；创建manifest SHAfd7667908f8de07b695f9f6cf68a160c91f66fa33f6ab774be3d1ff5fee11201。旧7737的6save/24Bframe/2热spill及此处derived bounds均保留。无新变体或排队；实际新caller能否删除对应保活/热spill和完整时间，交D按原件独立判断。
