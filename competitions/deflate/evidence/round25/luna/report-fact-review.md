# R25报告事实核对

**结论：**本次覆盖的事实没有发现实质数值或状态矛盾。需保留一个快照范围说明，并有一个预期中的待补链接：Sol仍在撰写next-route评估。根报告未被修改。

## 核对结果

| 项目 | 结果 | 精确位置与证据 |
|---|---|---|
| 作业、成功/失败与配对进程 | 34 dispatch/run；30成功、4失败；180个原协议配对进程。180与 outcome 的9个成功测量run之paired_processes求和一致。 | `docs/rounds/round25.md:3,42`; `evidence/round25/outcome-29697.json` (`/original_paired_processes`, `/runs[*].paired_processes`); `ci-cost-final.json` (`/coverage/status_counts`) |
| 主候选/副本/校准计数 | 12种不同Rust，14条source-pair元数据；11个实际有scorer summary的候选，tiny-tail明示未计时/未评分。128个单项scorer view中64 primary、64 shadow。candidate有30个primary测量块(22 discovery+8 confirmation)及30个shadow重投影；control有34个primary块和34个shadow视图。Shadow、同源码control、副本不增加候选独立样本。联合保留pair为4个primary物理块+4个shadow视图。 | `docs/rounds/round25.md:19,21-36,49`; `outcome-29697.json` (`/source_pairs`, `/distinct_rust_count`, `/candidates`, `/same_source_controls`, `/retained_pair_joint`); `score-algebra-29697.json` (`/single_views`, `/single_effects`, `/joint_cases`) |
| 质量/时间对照口径 | 表内质量可沿源父链归一到combo；时间用实际父版本。逐候选从outcome主候选primary rows重新取min/max后，与表的四舍五入范围吻合。详细表见下。 | `docs/rounds/round25.md:19,21-34`; `outcome-29697.json` (`/source_pairs[*].native_quality_observations`, `/candidates[*].observations`) |
| 榜首和正式事实 | Snapshot 29697记录#612为榜首，payable weight 16.382040392%；坐标(0.4304598592, 36.5273012167)。freshness仍unknown；候选分享只是public→formal条件投影，正式submission=false、admission=UNKNOWN、正式份额null。| `docs/rounds/round25.md:11-15,77`; `official-confirmation/receipt.json`, `leaderboard-pages.json`, `pareto-pages.json`; `outcome-29697.json`; `score-algebra-29697.json` |
| 评分代数 | 独立扫描报告VERIFIED；97个baseline frontier点、128单项view、56个联合案例。outcome与独立代数在128条view上逐键一一对应，projected_time、projected_size_pct与share无差异；与保存API重放最大误差约1.4e-15 pp。它不是私有性能或部署身份验证。 | `score-algebra-29697.json` (`/status`, `/method`, `/baseline_max_api_error_pp`, `/single_max_error_pp`, `/joint_max_error_pp`, `/limits`) |
| gate与M证明 | End4与tiny-PC8各有原版public gate receipt，状态`EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED`且Rust/Lean哈希匹配。Stage2未运行，根报告明确。M新proof状态`ACTUAL_M_EXTRACTION_ADAPTED_DRAFT_UNCOMPILED`；文中明确尚未完整gate，无过度声称。 | `docs/rounds/round25.md:36,53-58`; 两份gate receipt；`outcome-29697.json` (`/source_pairs` M proof row) |
| 时间/资源 | 固定授权5小时(08:06:21–13:06:21 UTC)与BJT报告时段一致。实际CI runner合计201.25min、queue 1.90min；作业分钟不误作研究墙钟、账单或模型用量。 | `docs/rounds/round25.md:1,71-77`; `evidence/round25/budget.json`; `luna/ci-cost-final.json` |
| 反例入口/链接 | Round25报告43个本地链接中仅next-route一个目标尚不存在；Round25方法补充段所检链接全部存在。其他已链接的E/F、G/J、K、M、L、O、snapshot失败与gate证据路径均存在。 | `docs/rounds/round25.md:62-71`; `docs/research/optimization-methods.md:335-353`; link scan |

## 表格数值独立复核

质量按来源所列父链加总到combo，并与9份`VERIFIED_ORIGINAL_ENCODER_BYTES_ONLY`原始native回执逐项比对；时间按primary主候选观测中的`time_change_pct_vs_parent`取范围。encoder-only回执的timing明确为`NOT_MEASURED`，时间范围来自outcome观察。表中数值四舍五入到原报告精度。

| 候选 | 相对combo质量(B / pp) | 报告声明的时间父版 | primary时间范围(%) | 核对 |
|---|---:|---|---:|---|
| dual8 | -14,674 / -0.050599 | combo | +3.019–+3.264 | 与primary观测匹配 |
| H | +2,556 / +0.009779 | dual8 | -1.456–-1.276 | 与primary观测匹配 |
| end4 | -7,397 / -0.032859 | combo | +0.720–+1.294 | 与primary观测匹配 |
| gap1 | -1,007 / -0.005834 | combo | +0.124–+0.479 | 与primary观测匹配 |
| M | -46 / -0.013690 | I | -1.381–-1.226 | 与primary观测匹配 |
| I | -332 / -0.098810 | combo | +1.574–+2.845 | 与primary观测匹配 |
| tiny-tail | -8 / -0.002381 | combo | UNKNOWN (not timed) | 未计时如实标UNKNOWN |
| N | +1,271 / +0.002755 | end4 | +0.363–+0.531 | 与primary观测匹配 |
| T | +6,533 / +0.029023 | combo | +0.509–+1.343 | 与primary观测匹配 |
| backtie | -1,964 / -0.007430 | combo | +0.202–+0.344 | 与primary观测匹配 |
| duplicate-hop J | -3,497 / -0.016728 | combo | +0.617–+0.815 | 与primary观测匹配 |
| wordtail | -7,397 / -0.032859 | end4 | -0.060–+0.495 | 与primary观测匹配 |

N对end4、wordtail对end4、H对dual8、M对I；其余为combo。质量路径复算得到H `-14,674 + 17,230 = +2,556B`，M `-332 + 286 = -46B`，wordtail `-7,397 + 0 = -7,397B`，因此父链质量与实际父版时间没有混用。

## 快照边界与待补项

`docs/rounds/round25.md:15`引用的[晚期目标说明](late-target-note.md)使用29690采样几何网格，且明示它不是连续边界；最终独立候选与strict-first计数来自29697。该句应读作跨快照的投入背景，不能当作29697的精确边界证明。29697的直接single/joint投影当前主候选strict-first、≥10%、≥15%计数均为0。

唯一待补目标是`docs/rounds/round25.md:81`的`../../evidence/round25/sol/next-route-assessment.md`；文件目前不存在，主线程说明Sol正在撰写。其余Round25报告本地链接与优化方法第25轮段链接检查通过。

检查未联网，外部GitHub链接未取回；official API freshness为unknown；正式准入、私有stage2和未提交候选奖励均保持UNKNOWN。
