# TorchLean 当前交接

本轮 R27：UTC 2026-10-29 19:44:43—2026-10-30 00:44:43，目标改为**任意一榜冠军**；只用现任冠军耗时乘数。Droot独占Git／公共手动CI，分支 `huan/codex-gpt`。初始唤醒后全部文件交接；下一轮预算须从当轮原始用户消息核对，摘要恢复和历史转述不重设计时。

接手先读 [R27结果](../candidates/r27-5h-20261029T194443Z/README.md)、[当前状态](../candidates/r27-5h-20261029T194443Z/development-status.json)、[数学结论](../candidates/r27-5h-20261029T194443Z/research/MATHEMATICS-RESULTS.md)。需要证明／反例／下一研究时再读角色HANDOFF；CI原件按run在R27/evidence，均保留字节与哈希，不依赖7天附件链接。R26历史从其候选README或Git原版本恢复，不沿用其旧倍率。

现任：overall8、MLP33、Mixer36、ResNet11、MobileNet7、归一化MLP43；最新逐榜官方原件见 R27/competition-state/champion-refresh-003007.json。Mixer最接近已测约1.037×冠军；归一化MLP单行block16约1.091×、新完整证明缺失。所有本轮候选均不足以取代冠军，保留版未采纳新候选。

三个精确源通过完整原12义务／内核／公理门禁：dced7848（guard）、6fe5feb6（GEMM组合）、f60551d5（原生加法组合）；其性能均不达目标。后两源分别两组全新输入、11轮／50ms标准测试，不能将其门禁转给其他源。完整记录见各CI-RESULTS。Band12显式字类型修复后完整360对校验通过，但约2.562×当前43，亦停止主投入。

下一选路优先保留public27的优化small-k GEMM、原生add与LN，再研究移植更小的public23稀疏dense端点。6fe5/f605未保留原small-k引擎；全组合闭包碰到256000B上限，不能假定拼装即获益。FP-only约2.405×、分带权重缓存约2.562×，不再为这些消费者先堆大证明。诊断中linear占三个记录入口87.8—93.2%，不等于全模型占比。Winograd必须保留强稀疏回退，纸面／有限模型不代替原生成本或全12证明。

当前正式工具版本为27fb1d19；相对历史pins的accb82b6只改超时归属，证明指纹不变。R27的prepare-current和当前政策重放绑定新版本，六榜配置哈希已复算；历史批次按其原提交复现。官方contracts/gate/bench不改；本地不编译Lean或大型Linux工具链。

原始whole Kernel/C、Pro聊天与包原件留忽略目录；公开自写配方、证明、有限模型、原始CI回执及hash恢复索引。研发推送持续授权；正式参赛、钱包与资金仍另核。没有执行正式提交、merge或分支清理。
