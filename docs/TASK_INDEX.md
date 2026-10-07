# 竞赛任务索引

先按任务读取对应报告。执行规则统一见 [AGENTS.md](../AGENTS.md)，这里只维护查找入口、已有结论和证据位置。

原始会话：**主优化agent**，ID `01a11272-3ca5-75d3-aa0a-68376e856f18`。需要回看原始请求或授权理由时，可用 Codex 任务读取工具按此 ID 查询。

| 任务 ID | 主题 | 结论与回看入口 |
|---|---|---|
| environment | [环境与验证入口](validation.md) | 手动 CI；环境和当前工具版本从实际入口、回执读取。 |
| round01 | [首轮：扩表与 probe2](rounds/round01.md) | probe2 明显改善公共大小，耗时略增；公共 gate 通过。 |
| round02 | [第二轮：probe3 与 bucket2 修复](rounds/round02.md) | probe3 更小；bucket2 后续 gate 修复成功，速度收益不稳定。 |
| round03 | [第三轮：速度端 fast3](rounds/round03.md) | fast3 后续 #453 正式 admission 通过，有历史奖励及到账确认。 |
| round04 | [第四轮：H 系列与多方向筛选](rounds/round04.md) | 大量质量／速度交换；公共筛选不能代替正式表现。 |
| round05 | [第五轮：H16 证明与完整编码成本](rounds/round05.md) | 精简证明使部分 H16 通过 gate；完整成本选择的收益不足。 |
| round06 | [第六轮：H16 CPU 复测与 #474 校准](rounds/round06.md) | #474 正式 gate 通过但被支配，否定乐观跨族系数。 |
| round07 | [第七轮：中段与 block1](rounds/round07.md) | 17 个版本均未进入预测前沿；block1 成为后续父版本。 |
| round08 | [第八轮：距离成本重选](rounds/round08.md) | 三种变体无大小收益，停止扩展；两个完整公共 gate 通过。 |
| round09 | [第九轮：块级 CPU 与前向瓶颈](rounds/round09.md) | scalar 约 0.884% 小幅速度信号，仍无预测份额；前向阶段约 73%，整份 q9 预处理过贵。 |
| round10 | [第十轮：五小时结构研究（进行中）](rounds/round10.md) | 首批六版本均无预测份额；转向压链、长键替换及空记录消除。证明和第二轮结果待收齐。 |
| maintenance-20261008 | [合并、去重与竞赛环境整理](history/maintenance-2026-10-08.md) | 实验历史合入 main；回执去重、文档分层、规则统一，CI 手动启动。 |

## 常用查找

```powershell
python scripts/project.py find 前向
python scripts/project.py find H16
python scripts/project.py find fast3
python scripts/project.py resolve ROUND9.md
python scripts/project.py check
```

查找返回任务 ID、报告、证据和原始会话 ID。旧报告路径和已去重的早期回执通过 [路径映射](path-aliases.json) 定位；命令不会启动 CI 或查询钱包。

## 候选定位

| 用途 | 候选 | 当前证据边界 |
|---|---|---|
| 正式历史获奖参照 | [fast3](../candidates/r3-432-fast3) | #453 正式 admission 与历史奖励；实时份额另查 |
| 最新均衡研究起点 | [scalar](../candidates/r9-block-scalar) | 完整公共 gate，公共平均小幅速度信号；未进入预测前沿 |
| 块级父版本 | [block1](../candidates/r7-mid361-block1) | 完整公共 gate；质量改善带来明显时间成本 |
| H16 正式校准 | [H16-small proofopt](../candidates/r5-h16-small-proofopt) | #474 正式 gate 通过，被支配 |
| 原始公开参照 | [#361](../references/round7-public-361) | 原作者／文件哈希保留；正式坐标只作同族锚 |

其他候选保留用于复现实验；`python scripts/project.py candidates scalar` 可查源码／证明哈希和本地验证记录。文件名带 proof 不代表已通过 gate。
