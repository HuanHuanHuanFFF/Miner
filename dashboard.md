# FloatLib 冲冠看板

> **目标：成为下一任冠军。当前：尚未达成，未正式提交。** 现任冠军为 **#174（VERIFIED）**；我们与它的直接耗时比和可取得的排名均为 **UNKNOWN**。

更新时间：**2026-10-21 17:49 北京时间**。这是一次查询快照，不自动刷新。官方政策快照 **512**，计算时间 **17:33:56**；API 的 freshness 标记为 `unknown`，表示榜单实时读取，但未承诺整份快照的新鲜度。

| 一眼看进展 | 当前结果 |
| --- | --- |
| 最近研究窗口 | 10 月 21 日 16:10—17:40，共 1.5 小时，已结束 |
| 开发验证 | 本轮 12 次 CI 均已自然结束并收齐回执 |
| 最有证据的新组件 | 固定宽度乘法；两个独立 runner 完整验收通过 |
| 该组件对公开起始版 | 耗时降低 **2.95%—3.44%**；只有一次达到 3% 门槛，尚不能称稳定达标 |
| 对现任冠军 / 正式排名 | **UNKNOWN / UNKNOWN**；缺冠军同机配对测量 |
| 正式参赛 / 实际奖励 | **NOT_SUBMITTED / UNKNOWN** |

## 当前冠军与奖励份额

**现任冠军：[提交 #174](https://conjectures.io/v1/competitions/floatlib/submissions/174)**，北京时间 **2026-10-21 12:23:25** 晋升。其晋升记录耗时比为 **0.954601**，即相对当时参照耗时降低约 **4.54%**；这不是相对我们候选的成绩。[官方冠军记录](https://conjectures.io/v1/competitions/floatlib/champions)

| 当前获分顺位 | 提交 | 持有者 hotkey（缩写） | FloatLib 预算份额 | 折合验证者总权重 |
| --- | --- | --- | ---: | ---: |
| 第 1 任（现任） | **#174** | `5H3yARV4…e9mKqeM` | **60%** | **12%** |
| 第 2 任 | #165 | `5DCWKCxA…bwfoeV` | 30% | 6% |
| 第 3 任 | #155 | `5FR6dwgh…c8VUwyy` | 10% | 2% |

份额按最近三任符合政策的冠军分配；普通速度榜的第 2、3 名不会因此获分。FloatLib 当前占验证者总权重 **20%**，完整四函数包获得本赛道份额；单函数练习榜不付费。以上是**政策权重**，实际链上到账、美元收益和净收益均未核实。[官方政策](https://conjectures.io/v1/competitions/floatlib)

**怎样成为新冠军：** 完整包通过精确逐位等价证明等全部官方验收；与评测时的现任冠军配对计时，综合耗时比 **≤0.97**；配对轮次收益的 bootstrap 第 5 百分位还须 **>0**。只看某次最好成绩或旧起始版的收益无法确定晋升。当前开发验证采用十二类输入、25 个配对轮次；统计策略抽样 2000 次。

<details>
<summary>冠军精确身份与证据</summary>

- 完整 hotkey：`5H3yARV4uio57iV3KonjCmFnmR36oATPYZ16oNtjRe9mKqeM`
- #174 源码 digest：`67e44fd4b17186dbe6b1728dea49611288bb16d2586ebbb3a8a2f93aea74c009`
- 官方状态：`accepted`，`verification_current=true`；[验收报告](https://conjectures.io/v1/competitions/floatlib/submissions/174/report)。
- 我们尚未取得该 digest 对应源码，缺少同机直接比较；官方起始参考文件不能替代现任冠军。
- 本次查询原始响应、UTC 时间与 SHA-256：[查询回执](competitions/floatlib/evidence/dashboard-20261021T094923Z/receipts.json)、[冠军列表](competitions/floatlib/evidence/dashboard-20261021T094923Z/champions.raw)、[冠军详情](competitions/floatlib/evidence/dashboard-20261021T094923Z/submission-174.raw)、[冠军报告](competitions/floatlib/evidence/dashboard-20261021T094923Z/report-174.raw)、[政策](competitions/floatlib/evidence/dashboard-20261021T094923Z/competition.raw)、[速度榜](competitions/floatlib/evidence/dashboard-20261021T094923Z/leaderboard.raw)。

</details>

## 我们的实验结果

下表耗时比均为 **候选 ÷ 官方公开起始版**，越小越快。这里的“公开起始版”是官方仓库随附的固定参考源码，SHA-256 为 `5d0cef3f…7d65868`；它早于现任冠军。**下表不能用来推算线上排名。** 完整版本、哈希、CPU、种子和逐项数据见[本轮详细报告](competitions/floatlib/candidates/f01-rebuilt-mul-proof1/window90/README.md)及[逐作业回执汇总](competitions/floatlib/candidates/f01-rebuilt-mul-proof1/window90/summary.json)。

| 方向 | 验证 | 对起始版耗时比 | 耗时变化 | 当前决定 |
| --- | --- | ---: | ---: | --- |
| **固定宽度乘法重建** | 完整验收通过；独立确认 2 次 | **0.965603—0.970455** | **降低 2.95%—3.44%** | 保留组件；两次中一次达 3%，不当作成功概率 |
| 地址基址外提 | 完整验收通过；单次 | 0.977886 | 降低 2.21% | 保留组件，缺独立确认 |
| 张量调用边界特化 | 完整验收通过；单次诊断 | 0.975627 | 降低 2.44% | 未发现足够大的收益 |
| 原始位张量循环 | 完整验收通过；单次 | 0.983861 | 降低 1.61% | 降低优先级 |
| 同尺度／同号加法 | 完整验收通过；单次 | 1.031469 | **变慢 3.15%** | 停止推进这个版本 |
| 正常数同号 GRS 加法 | **仅计时筛选，证明未完成** | 1.096087 | **变慢 9.61%** | 不投入该版本完整证明，不可提交 |
| 地址外提＋乘法组合 | 旧版索引证明超时 | UNKNOWN | UNKNOWN | 尚未取得组合成绩，不能把组件收益相加 |

乘法两次测量使用同一冻结源码，中位耗时比 **0.968029**。第二次耗时比 **0.970455 > 0.97**；当前只取得可复用的已证明组件，未形成有证据可击败现任冠军的完整方案。

## 接下来重点看什么

官方 #174 晋升报告中，十二类计分耗时按函数汇总后的占比如下。它们是该次评测的**计分耗时贡献**，会随实现和测量变化；奖励始终按完整包分配。

| 函数方向 | #174 计分耗时占比 | 探索重点 |
| --- | ---: | --- |
| add：加法 | **48.53%** | 主攻统一的全域字级路径，尤其零和特殊值触发的重型回退 |
| mul：乘法 | **47.11%** | 保留已证明重建组件；继续投入须有更大机制收益 |
| sum：归约 | 3.60% | 随加法核心改进，保持原逐步舍入顺序 |
| bmm：矩阵乘法 | 0.76% | 保留地址优化；当前独立优化的总分上限较小 |

下一轮先用受控计时判断新加法数据流是否有足够收益，再投入完整证明；冻结后预留独立 runner 确认。夺冠结论最终仍需要对届时现任冠军的正式比较。

## 详细入口

- [开发状态](competitions/floatlib/coordination/development-status.json)：唯一当前开发状态入口；本页是方便阅读的摘要。
- [90 分钟研究报告](competitions/floatlib/candidates/f01-rebuilt-mul-proof1/window90/README.md)：成功、失败、负面结果及全部 CI 链接。
- [FloatLib 技术规则](competitions/floatlib/docs/track-rules.md) · [环境与验收说明](competitions/floatlib/docs/environment.md) · [官方比赛页面](https://conjectures.io/competitions/floatlib)。
- [DEFLATE 历史看板](competitions/deflate/DASHBOARD.md)：该赛道已关闭新提交，历史结果另存。
