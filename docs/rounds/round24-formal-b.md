# R24 B 正式提交 #625

用户明确授权提交 B，使用既有第6个 hotkey。北京时间2026-10-11 14:43:26，官方 HTTP201、created=true，编号625，剩余slots_remaining=0。新增链上支出0 TAO。

候选 `r24-609-fast-adaptive-proof1`，Rust SHA-256 `ef3268f4b4183b50af7825e505266c7dc05b49e9bb1aebb1f642a5609fc6423e`，Lean SHA-256 `09f79e1d6b4d60bdcc692425a7baae6503f3995f8cc6f9937d7f23a347e9e20e`，组合digest `bdc84570305e5629f1481635e09cfd81e643a710630a1c70d69fed4a58c45a52`。与完整公共gate38104425023文件逐字一致。

首次本地包装器重复BOM导致param报错，已修复并通过Windows PowerShell实际模拟账户自测。首次账户解锁失败，未产生上传尝试回执；之后用户在本地重新运行并完成签名上传。密码与密钥未进入研究证据。

**VERIFIED**：已上传并取得编号。最新读取北京时间14:51:40，官方状态running，快照29663。**UNKNOWN**：正式gate、admission、私有坐标和可支付份额，不能把公共条件估算视为正式结果。

- [原始接受响应](../../evidence/round24/formal-b/submission-accepted.response.json)
- [上传回执](../../evidence/round24/formal-b/submission-receipt.json)
- [当前状态](../../evidence/round24/formal-b/latest-status.response.json)
- [包装器修复核验](../../evidence/round24/formal-b/wrapper-fix.json)
- [研究报告](round24.md)
- [提交看板](../../DASHBOARD.md)

执行规则见[AGENTS.md](../../AGENTS.md)。

## 正式结果及预测差异

**VERIFIED**：#625正式gate及admission通过，处于前沿并有支付资格。快照29668，计算北京时间2026-10-11 15:05:48，当前可支付竞赛池份额 **0.383036881%**，累计奖励0 α。钱包到账UNKNOWN。正式两轴为6.760604616／34.091309337%。公共stage1输出4,864,057B，与冻结公共结果一致；held-out stage2输出4,955,503B。

份额差异主要来自新竞争点#624。研究快照29657中#624没有坐标；把#625正式坐标加入该榜单，份额3.724262581%。在当前29668排除自身后重放为0.383036881%；再移除#624则恢复3.724262581%。同一9块公共主参照重放，由旧榜单2.713093%–3.978665%、中位3.590919%，变为当前0%–0.667272%、中位0.277755%。这些是条件重放，不是新的性能实验或正式概率。

#624大小34.091076212%，比B更小；时间6.957105690，比B慢。B对#624通过速度准入（估算优势2.824466%，单侧95%下界2.710709%），但它没有支配#624，只分得相邻前沿区间的一小部分。B正式速度位于原公共主参照6.673920–7.102718范围，大小略优于投影34.091330559%，不支持将这次份额差异主要归因于私有集表现恶化。

[正式结果](../../evidence/round24/formal-b/result-summary.json) · [同坐标榜单反事实重放](../../evidence/round24/formal-b/prediction-gap-diagnosis.json)。
