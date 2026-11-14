# R20角色A：8列核心已严验，广域接口待实现

实际执行 **07:55:13—共同截止08:32:58 UTC**，晚接入不延长；末段仍做静态核对。应用huan-open-research，D唯一Git/CI，本方无本机Lean/子agent/开发状态写入。

**冻结探针** `Probe-row-broadcast8.lean`，239638 B，SHA **ec40e88eb85730520a1cd1e6adcbaea3c8161fc5c0f7e4b2f5795e178d24a5a6**。CI40471664006/a0724a5b已statement、Submission/VerifyFull原重放、9根三允许公理PASS；本方source/verdict/helper/replay绑定在accepted.json。真实新机制是8条原序链共享每k一个A解码、无全局A缓存，B8每调用只准备一次，沿用原finish/NaN回放。**公开四入口仍622d B2，新publicBMM与性能未验**；D terminal后继不在本文件改动。

**广域后继接口** `postfreeze/WideRowRefinement.lean.inc`，2477 B，SHA **dd00510c38d6835ddff612b59050728fb2b1e02284d310182dc103aeb75e5ade**，NOT_RUN。任意列数/状态S，只需有效k<n的整行step逐列满足原FP32乘加式，就可投影到NativeFinal.dotLoop并复用finish；实际Array.modify状态实现仍须证明hstep与长度，不能借此声称已闭合。它承接representation角色的safe modify/独占CtorReuse条件，本方不重复实现、不扩manylane网格。

**成本与旧负区别**：c36 Dual全D whole.998184/BMM.985768/p05负；本次删除其整个A4生命周期，未重复声称新SIMD或省原本不存在的A分配。旧完整pass里p8探针即使占全部B2也最多6.244%whole；B2/DC/Packed10全部路由免费上界14.920%，2倍理想仅7.460%。精确全p8份额UNKNOWN；这些不是速度预测。广域Array状态须计两次slot写、RC/独占、字段读写、closure、初始化/释放和emit。详postfreeze/coverage-bound.json与DECISION.md。

**下一判别**：ec40/terminal实际C/ASM确认A每4k四codec、无backedge对象，并核所有跨call spill；广域实现确认Array.modify没有COW/新record分配及逐列原序。FloatArray跨宽opaque旧障碍已重核，未重开。冻结源未动，无新CI请求；旧失败/未验字段保留原状态。
