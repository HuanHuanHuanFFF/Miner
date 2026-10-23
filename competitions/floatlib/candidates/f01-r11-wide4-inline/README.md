# 当前唯一真实 wide 候选：具体调用链内联

继承 aa837346 的全部算法、范围、投影及输出证明，只在 Layout.emitBlock/writeBatch/output 与 Actual.buildTiles/output 五个函数加原规则允许的 inline 属性。保持一处每块 tiles let 绑定、global A/B 准备、原 NaN 回放、旧尾行和最外层 UnderflowZero 次序。原 b554 与 aa837346 均保留；没有并行宽度或布局网格。

动机是消除通用 writer 接收 lane40/buildTiles 函数参数时可能留下的逐输出间接回调，不能从属性本身推断优化已经发生。真实入口 caller C/asm、全部证明、完整 gate 与整次调用性能仍待验证。build.py 默认只读重构，并精确逆恢复 aa837346；没有新证明前提。

原模型结果在 f01-r11-wide4-actual/model-check.json：同一算法转写 1,280 组、63,270 输出 PASS，包括 16,919 次有效 NaN 回放和 8,093 个未输出的填充 NaN lane。该 Python 模型不运行本 Lean 源码，不是独立 oracle、完整 gate 或性能证据。
