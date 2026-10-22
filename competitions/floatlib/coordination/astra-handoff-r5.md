# R5 九十分钟协作

用户新授权继续协作1.5h。共同窗口2026-10-22 10:05:04—11:35:04 UTC，北京18:05:04—19:35:04。全部准备、协调、等待计入；已启动CI与实验自然跑完回收，截止停止新增。约11:05冻结，11:15前发出独立确认。

沿用你现有Astra会话和设置。R唯一文件范围research/astra-collab-20261022-r5/及candidates/f01-r5-*/；D拥有f01-d5-*、公共状态/看板，独占Git/推送/CI，最多2个并行公共标准runner，无正式提交/资金。保持已有未提交文件，不切分支/reset/stash/暂存他人文件。普通交接文件化、自然检查点读取。

本轮对照是完整冻结f01-d4-final-lowmul/Kernel.lean，SHA ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630，132965bytes，FULL 513/514/516三次通过。champ174，bmm约4.4倍、mul2.1、sum1.8、add1.1。目标击败现任冠军，优先最大bmm差距。

R负责提出并实现减少bmm准备/结果输出成本的实质候选，优先行内/行序输出避免每个flat q的Nat除模和嵌套查表；也可选择有证据更强的存储组织变化。先读R4最终checkpoint和D4最终源码：10列+USize热循环、精确数字解码、output解码公式inline已经采用。2x4和2x8虽真实SIMD/B共享、无热spill，完整调用仍慢9%/0.6%；单纯再增tile宽没有新成本证据，不重开。保留原k顺序及每次mul后add，不FMA/重排，所有特殊值/维度回退和全部四义务不变。

D独立做候选局部的完整调用成本诊断，尝试隔离packB/nativeA、tileResults与output组装成本；官方gate/bench/pins不改。诊断不算正式gate。R可以直接走最小新候选，不要等待D。10:35左右首个可编译完整候选，10:45前至少可验证关键桥接；11:05前冻结。若证明困难，先落下精确障碍及可运行最小变化。R不本地安装重型工具链，D负责CI编译/正式gate反馈。R状态落盘research-status.json，候选manifest必须SHA/bytes且不可写成已验证。网页6 Pro可辅助但不阻塞直接Lean；若开启须预算内完成回收，原件E:/Download。

最终输出：精确候选和证明、机制与失败条件、成本与未知、受控最小实验；D复核后决定采用。请开始实际研究，先写状态，然后在自然检查点读取development-status.json及coordination内R5反馈。
