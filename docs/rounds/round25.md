# 第二十五轮：五小时快速端低成本压缩研究

北京时间 **2026-10-11 16:06:21–21:06:21**，目标稳定冲击竞赛奖励池份额榜首。状态：研究进行中。执行规则见 [AGENTS.md](../../AGENTS.md)，预算与接手状态见 [budget](../../evidence/round25/budget.json)、[研究状态](../../evidence/round25/research-state.md)、[GitHub 接手回执](../../evidence/round25/github-start.json)。

起点 main `48baf622466792f4d505c5c06d5696f784e27b7a` 与 origin/main 一致，工作区干净、只有一个 worktree；远端公开、最近查询的作业均结束。使用同一 checkout 的实验分支 `codex/round25-fast-quality`。

先比较低成本质量机制与既有快速端负例，再做少量受控实现。新候选的公共条件估算、完整验收与正式可支付成绩分别记录；本轮不包含正式上传。

## 前两圈：实际压缩与取舍

最新已捕获官方快照29673，计算北京时间15:48:20、freshness为unknown；[原始响应](../../evidence/round25/official-feedback-a/receipt.json)与[评分源码](../../evidence/round25/official-rules-start/receipt.json)分列。612为当前可支付榜首20.524717%，新626已进入快速前沿。纯scorer重放官方权重最大差异2.78e-17；[目标区域](../../evidence/round25/target-map-start.json)只是合成坐标网格，并非候选成绩。

两圈共五份不同Rust经过原encoder的28文件decode/真实字节检查；[首批逐文件结果](../../evidence/round25/feedback-a-native.json)、[第二批](../../evidence/round25/feedback-b-native.json)。相对精确combo父版：end4少7397B、均衡压缩率少0.0328587pp；backtie少1964B/0.00742976pp；gap1少1007B/0.00583408pp并保留文件级损失。替换尾key的tail4多6533B，暂停；tiny-tail只少8B，先留作微组件。[后两者取舍](../../evidence/round25/feedback-b-decision.json)。这些是质量筛选，时间、份额和完整正确性另行验收。

end4/backtie实际重新提取均成功，[原始模型与日志](../../evidence/round25/38124536539/proof-a-extract/diagnostics/research5/research.json)支持证明接口迁移；完整Lean尚未因此成立。首批原协议配对计时38124524718与end4原版完整gate38125243582已按预声明启动，状态随原始结果更新。

把R23旧快速组合的原始确认重放到29673，四个主块仍2次零、影子3次零，详见[历史数据当前快照重放](../../evidence/round25/historical-fast-rank-29673.json)。这是旧测量重算，不能增加本轮独立样本数，亦不能解释为成功概率。
