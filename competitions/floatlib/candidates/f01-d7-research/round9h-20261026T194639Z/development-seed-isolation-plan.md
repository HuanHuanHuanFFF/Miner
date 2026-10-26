# 构建SIGTERM的窄反馈环，不改验收限额

真实红信号：原1180源在40410895344运行`lake build VerifyFull`，31.3s后exit=-15，完整输出仅1B；旧4307 seed在40153361143曾26.6s同症状。不是已定位数学错误，复现率和根因均UNKNOWN，原失败保留。

下一1927007只编译原字节B2，再以独立helper导入已编译Submission，逐字复用4307B seed和2839B PostBias。每个顶层声明前后插入唯一`[DEBUG-R19-SEED]`标记并显式flush，去掉标记可逐字节恢复原数学片段；11个边界无改证明正文。同步只读记录Lean/lake进程RSS、cgroup memory.current/peak/max/events和已观察scope的状态，不读环境/命令行，不改原gate、compiler flags或资源上限。180s仅是更窄诊断上限。

此步骤为diagnosing-bugs的反馈环与缩小场景：当前完整失败命令已实际红，先取得最后完成声明与资源回执，再按证据排序可证伪原因，不把源码阅读猜测直接当修复。编译依赖边界与日志属于诊断变化，不能据helper成功推断原完整Kernel已修复；未来必须回到完整新源、全部spec/模块及原性能验收。诊断不含计时，不混入任何清洁D/A/B。

`f01-r19-dev-seed-isolation1/Kernel.lean`仍为B2/622d，所有公开入口不变。新审计器只对这个显式诊断manifest启用，基线4根先按原v5回放/审计。固定Lean293d源`Init/System/IO.lean`的IO.getStdout、Stream.putStrLn和flush已按Git blob64faef77核实。无本机Lean；临时标记只在隔离helper和清楚标注的debug证据中保留。
