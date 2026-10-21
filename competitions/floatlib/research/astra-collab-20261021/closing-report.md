# FloatLib R 研究收尾

R按共同截止完成研究收尾。2026-10-21 11:31:26 UTC的实际平台状态仍显示最终CI在完整gate／计时阶段，原始产物尚未回收；D继续负责已启动作业的自然结束与回收。已找到并验证公开native加法路径；冠军目标未达成，冠军同机比值仍UNKNOWN。共同窗口仍为10:32:09—11:32:09 UTC，没有延长。

| 精确候选 | 实际验证 | 整包／起始参考 | sum | bmm |
| --- | --- | ---: | ---: | ---: |
| D native-add-proof1 `7f51b433…` | run39589111347完整gate，三项允许公理、12类25轮 | 0.623247 | 0.378156 | 0.584480 |
| R direct-dot-loop `cb09e9c6…` | run39586444651完整gate | 0.973328 | 0.999262 | 0.933632 |

比值分母均为精确起始参考 `5d0cef3f…7d65868`，不是当前冠军。直接循环继承基址外提，父版本已有特化C循环，6.64%的bmm改善不能全归因于这次改写。直接sum的D近似实现完整通过但sum慢3.94%，未采用。

最终CI **39590684208**：native-add同版独立确认、native-both-proof1 `707d22fe…` 首次完整gate、native-sum-acc `75524a31…` 首次完整gate。后两者收益当前UNKNOWN；sum包已实际编译，C确认原生float累加器与结束处分配。不同版本的最好结果不合并为已验收整包。

最有用的公开起点是pinned FloatLib的 `ofFloat32_add_of_isFinite`，加上Lean4.34已有逻辑模型的Float32原语。乘法缺少的指数前提从FloatLib后续公开MIT版本移植了三个引理，保留归属且未变更官方依赖；修复与精确来源见[R-06](checkpoint-06.md)、[R-07](checkpoint-07.md)。

零回退有限模型显示：dense/wide只占sum0.1%、bmm1%；relu分别50.1%/51%。这支持relu零路径优化，不能解释所有量级差距。实际native加法计时确认算术路径有显著成本；冠军内部机制及剩余差距来源仍UNKNOWN。未找到历史冠军精确源码。

复核入口：[原始回执与哈希审计](window-audit.json)、[冻结源码／舍入复核](closing-source-review.md)、[46项本地工件检查](bundle-audit.json)、[有限模型](fallback-probe-result.json)、[FMA／重排／零反例](counterexamples.json)。原始runner证据由D保留，R只生成派生索引。

后续先收齐已启动作业。若native-both通过，可作为下一窗起点；与native累加器集成后要验证完整新版本。去除重复raw guard、位级finite证明草稿留存但未编译，不算已完成组件。新的研究需要继续有效授权，本次截止不延长。

最终平台状态见[closing-ci-state.json](closing-ci-state.json)。R无自己启动的本地／远端活动作业，没有安装Lean、派CI、提交／推送、正式参赛或资金动作。D是Git与CI唯一协调者；当前执行与回收状态以[开发状态](../../coordination/development-status.json)为准。
