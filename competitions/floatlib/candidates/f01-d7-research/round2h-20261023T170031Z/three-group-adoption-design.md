# R10：三组确认后的窄范围采纳入口

新增 `adopt-three-confirmed.py`，不调用旧两组adopter，不重建冠军或dashboard政策，不改资源授权与研究轮次。**本地17项测试通过；真实采纳NOT_RUN。** 子任务只在临时fixture ROOT上运行采纳流程，原始gate／估算I/O均为mock；真实state、view、model、dashboard及既有helper前后hash相同。

接口严格为：

```text
python -B competitions/floatlib/candidates/f01-d7-research/round2h-20261023T170031Z/adopt-three-confirmed.py --freeze <cohort-freeze.json> --freeze-sha256 <事前外部记录的SHA256> --discovery <D> --confirmation-a <A> --confirmation-b <B>
```

成功退出0，拒绝／回滚退出2。每次运行创建独立 `adoption-attempt-<UTC>-<随机后缀>/`，保存验证结果、失败、前后hash与回滚状态；通过全部预检后才保存原目标文件备份。最终receipt使用独占创建，不覆盖历史失败。根协调者须将本脚本、当前estimator及 `estimator.DEFAULT_ANCHOR` 的精确SHA加入事前cohort冻结；现有verify_freeze要求的原规则／helper仍全部检查。

## 先验证，后写盘

入口直接调用本轮 `verify_freeze` 和 **fresh `verify_three_groups`**，重新读取原始D/A/B证据，拒绝diagnostic_only、重复／缺失组与任一未达原阈值组。没有“读取旧receipt的accepted布尔即采纳”路径。当前state、view与其真实Kernel都必须仍为精确41。既有guard在真实运行中仍会读取immutable Git blob来认证原HEAD；新入口不执行Git提交、切换、推送、CI或正式竞赛动作，本子任务未执行任何Git。

随后先运行estimator的dry-run，核对原官方响应、原锚及当前冠军身份；再用 `select_pairs` 收齐候选**所有同源full索引行**，通过 `estimate_from_anchor` 预检新源码相对当前冠军的冻结估值。缺配对、错source／suite／冠军或估算拒绝时，四份目标文件保持零写入。还会从已认证classes×work复算索引运算总量、参照总量、headline、份额，并对照fresh guard的三组归一化比值，避免被改写的便利索引污染UI。

所有预检通过后才复制原view／state并作窄范围更新。全部同源full run进入 `full_gate_runs`，包括额外慢样本；D/A/B单独进入 `independent_adoption_runs`，每组只计一次。`performance`保存全部源样本，同时以 `independent_samples`、`independent_seeds`、`independent_ratio_vs_shipped` 等字段明确列出三组；通用seeds／ratio／kernels数组与全部full runs对应。previous_package绑定当前41和三组比值。候选相关直接冠军比值置UNKNOWN，当前冠军身份保持不变。

state／view按现有对象复制，保留原dashboard_policy、资源、授权、research_round起止、实际CI状态与无关字段；没有旧R7剩余时间文字生成逻辑。estimator.main会刷新policy时间，因此入口在其后恢复两处原policy的完整内容，再render，并检查其他无关state字段未被触碰。

## 写后失败与并发保护

事务只拥有view、state、champion-time-estimate和dashboard四个目标。每次写都先比较预期字节，用同目录临时文件和atomic replace落盘；estimator的save与renderer的最终write_text被临时接入同一事务，不允许意外输出路径。源码、索引、官方snapshot和冻结输入在写前／写后重新核对。

若估算或渲染在写后失败，按原备份回滚；**只有当前字节仍等于本次最后写入字节的文件才恢复**。若外部修改了state等文件，保留外部内容，写明 `EXTERNAL_CHANGE_PRESERVED`，不把它覆盖为旧备份。失败receipt原样保留；若首次审计receipt写失败，也会触发回滚并尝试保存替代失败收据。

这是根协调者唯一状态所有者前提下的内容CAS保护，不是四文件的OS级原子事务。对不配合的外部writer，在比较与replace之间极窄区间内仍无法提供绝对互斥；出现冲突时由根根据备份与失败收据协调，不静默宣称已全部恢复。

## 验证与接管

17项测试覆盖三组成功／缺失／偏慢、拒绝旧accepted替代fresh结果、state／source改变、索引变化、估算拒绝时零目标写入、diagnostic拒绝、索引聚合篡改、保留政策／资源／CI、额外慢样本不遗漏、写model／dashboard后故障回滚、外部state不被回滚覆盖、内容CAS拒绝外部写，以及审计失败回滚。原始输出与最终hash在 `three-group-adoption-design.json`。

根协调者在额外两组实际通过后再运行；代码交付、mock测试通过和单个discovery通过均不等于真实采纳，更不等于当前冠军准入或正式提交。
