# R16：大收益机制优先的三小时协作

窗口：2026-10-25北京时间17:18:10—20:18:10。[计划与权限](round-plan.json)；唯一当前验收入口为[开发状态](../../../coordination/development-status.json)，用户看[四运算看板](../../../../../dashboard.md)。当前保留B2 `622d8394`，冠军数值模型`9222bdf6`保持冻结。

| 机制 | 已取得的证据 | 决定 |
| --- | --- | --- |
| 正常乘法一次原生乘法后重打包 `c972fd72` | 完整gate通过；对B2整包耗时1.03055×、乘法1.08190× | 保留负结果，不组合 |
| 四行×双列复用 `2a937bb0` | 完整gate通过；对B2整包1.00785×、矩阵1.04344×；实际循环无转换／分配 | 停止当前实现晋级 |
| 高位对齐加法 `f7f4702f` | 完整入口已冻结；前版两处证明脚本错误已针对性修正 | 完整gate与整包计时中 |

[首轮原始完整结果](../../f01-mul-log2-proof1/ci-runs/40183711165/original-artifact-hashes.json)、[实际生成代码](../../f01-mul-log2-proof1/ci-runs/40185444601/original-artifact-hashes.json)、[加法首次完整尝试](../../f01-mul-log2-proof1/ci-runs/40187127847/original-artifact-hashes.json)。全部失败与慢样本保留；小模型、源码检查和编译探针分别记录，不代替完整验收。

研究方维护`astra-status.json`及各主题目录；D负责Git、CI、采用和[经验](development-lessons.md)。普通协作走公共文件交接，当前确认数据完成前不用于下一代调参。当前尚未生成本轮确认组。
