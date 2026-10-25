# R16：大收益机制优先的三小时协作

窗口：2026-10-25北京时间17:18:10—20:18:10。[计划与权限](round-plan.json)；唯一当前验收入口为[开发状态](../../../coordination/development-status.json)，用户看[四运算看板](../../../../../dashboard.md)。当前保留B2 `622d8394`，冠军数值模型`9222bdf6`保持冻结。

| 机制 | 已取得的证据 | 决定 |
| --- | --- | --- |
| 正常乘法一次原生乘法后重打包 `c972fd72` | 完整gate通过；对B2整包耗时1.03055×、乘法1.08190× | 保留负结果，不组合 |
| 四行×双列复用 `2a937bb0` | 完整gate通过；对B2整包1.00785×、矩阵1.04344×；实际循环无转换／分配 | 停止当前实现晋级 |
| 高位对齐加法 `f7f4702f` | 完整gate通过；对B2整包1.29455×、加法1.87392× | 保留新数学桥梁，停止当前实现晋级 |

[首轮原始完整结果](../../f01-mul-log2-proof1/ci-runs/40183711165/original-artifact-hashes.json)、[实际生成代码](../../f01-mul-log2-proof1/ci-runs/40185444601/original-artifact-hashes.json)、[加法首次完整尝试](../../f01-mul-log2-proof1/ci-runs/40187127847/original-artifact-hashes.json)。全部失败与慢样本保留；小模型、源码检查和编译探针分别记录，不代替完整验收。

三小时研究窗口已完成，10次CI全部终态，500份原始文件已回收核对。三条机制均未达到确认标准，没有新采用或正式参赛提交；B2与既有冠军数值模型保留。[完整结果](development-round-results.json)

同输入新runner／反转顺序复查恢复B2加法正常表现，旧慢样本仍保留，具体原因UNKNOWN。最后数值往返数学探针在`toUInt32_of_nonnegative_integral_decode`剩一处rewrite失败，辅助定理内核／公理审计未执行；不宣称证明已闭合。[原始错误索引](development-compiler-error-map-40192000569.md)

研究方维护`astra-status.json`及各主题目录；D负责Git、CI、采用和[经验](development-lessons.md)。本轮没有生成确认组；诊断与采用样本分列。
