# 第十八轮 A 正式提交 #603

用户在11小时研究交付后明确要求提交当前A。本次是后续正式操作，不延长已结束的研究窗口，也没有新注册或链上交易。

- 候选：`r18-rf-sf-content-proof1`，保持冻结源码与证明。
- Rust SHA-256：`16390a77d6b500f96b37441027512b89ba2d62b5091435e0527d9aa07b9834ef`，289,763字节。
- Lean SHA-256：`0a0171ac0dda3f6c06e574145e6b89b6b90fed45bd2d1d22be0ad199d18bacc7`，494,600字节。
- 组合digest：`38c4ccfd8dc9979cb05ea09b64f93dd09ba5f528d260c787b47b3edec8cfca53`。
- 已通过完整原版公共gate：38018217854。
- 提交时间：北京时间2026-10-10 14:05:41；正式编号 **603**。
- 服务端HTTP201，created=true，初始状态queued，剩余可排队名额0。该字段不代表已通过正式gate或已取得奖励。
- 提交前重新核对finalized注册归属、官方提交规则、精确文件、空公开提交记录；使用既有第5个hotkey、UID118。用户只在自己的交互终端输入密码，进行链下提交身份签名。新增链上支出0 TAO，无注册、交易或资金签名。

## 正式结果

**VERIFIED：正式gate、admission均通过，进入前沿且具备支付资格。** 官方快照 **29505**，计算时间北京时间 **2026-10-10 14:20:47.898417**；同快照榜单排名 **第2**，正式可支付竞赛池份额 **5.712701594136391%**。没有乘验证者总权重中的20%。

| 指标 | 正式值 |
|---|---:|
| balanced_time_ratio | 6.695226672218882 |
| mean_file_compression_pct | 34.09272307637799% |
| 公共stage1总输出 | 4,864,300 B |
| held-out stage2总输出 | 4,955,619 B |
| 当前快照累计奖励 | 0 α |

正式报告确认重新执行Charon/Aeneas、原始`LZ77.Obligation slot.parse`、900秒Lean限制及原公理白名单，两套corpus均接受。准入速度检验参照#585，估算速度优势28.515797%，单侧95%下界28.328412%，通过；原报告保留其统计适用限制。

排名与权重读取都绑定29505。该次权重记录`dry_run=false`、`chain_accepted=false`，因此不将已发布可支付份额冒充本次权重已上链或钱包已到账。实际钱包到账没有查询，保持 **UNKNOWN**；未来份额会随榜单变化。

这个正式结果超过5%，但仍低于原A的15%目标，B也未正式提交，原15%/5%双候选目标仍未完成。原先公共#586校准约7.50%、#591整族校准0%的预测保留为历史假设；当前A的正式结果以本次实测为准。

收集器只读轮询已结束，没有取消或重跑服务器任务。首次代码将成功状态写作accepted，现场返回passed后已修正并重新保存终态；这只影响本地终态识别，不影响上传、官方运行或分数。

- [官方详情](https://conjectures.io/competitions/deflate/submissions/603)
- [原始上传响应](../../evidence/round18/formal-a/submission-accepted.response.json)
- [上传回执与SHA核对](../../evidence/round18/formal-a/submission-receipt.json)
- [最新已收集正式状态](../../evidence/round18/formal-a/latest-status.json)
- [正式结果及原始回执哈希审计](../../evidence/round18/formal-a/result-summary.json)
- [原11小时研究交付](round18-extension.md)

执行规则见[AGENTS.md](../../AGENTS.md)。
