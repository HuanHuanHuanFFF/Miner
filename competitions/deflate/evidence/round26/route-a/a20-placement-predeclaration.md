# A20：一次原引擎实际 CPU 放置观察

缺口：A19 同源码副本存在跨阶段、跨文件的计时共同移动，历史字段 process_affinity 来自外层驱动，不能证明原 sandbox 请求 AllowedCPUs=0 对被测 engine 的有效限制。R23 等次数顺序干预已经完成，但没有消除所有分歧。此次不重复顺序干预，不从遥测校正成绩。

变化与最小动作：使用现有 diagnostic workflow 的原 ci-prepare/ci-setup，原 pins、bench driver、模板、sandbox 参数及 engine。仅 public658 与 incumbent 一对，原 28 文件、1 预热、11 测量、固定原调用顺序；不修改上游源码、不加候选、不运行 gate。自行调用原 bwrap.argv 后使用与 bwrap.run 相同的 Popen/communicate 配置，以获得这一次外层 PID。

一个独立只读监控线程以 4 Hz 从该 PID 的 children 递归，只读取这次子树的公开 PID/status/stat/exe，绝不扫描全部 /proc 或读取环境。精确引擎必须满足 exe 路径、/proc/PID/exe SHA-256 与启动前原二进制相同，并记录 PID/starttime，才接受其 affinity/cgroup/CPU 样本。读取匹配引擎 cgroup 的 cpuset.cpus.effective、cpu.max、cpu.stat，以及该次 sampled CPU 的可见 cpufreq 字段；缺失明确 UNKNOWN。监控线程在引擎启动后尽可能绑到非请求 CPU，记录其线程 ID、前后 mask 和失败状态；引擎 affinity 不改。

判别：只回答本次精确引擎有效 CPU 集与实际采样 CPU 是什么、频率字段是否可见。请求值、驱动 mask、实际引擎 mask 三者分列。若无精确 PID 匹配，不能写成有效单核；作业失败并保留原始遥测。低频 CPU 样本不证明没有两次采样间迁移；可见频率不等于每次函数调用实际频率。此次证据不能回推 A19 或旧运行根因。

成本与边界：建议作业 cap 25 分钟；原单次 build/measure 的 300 秒限制不改。只有一份配对进程，计时全部标为 diagnostic；监控即使固定其他 CPU 也可能扰动运行，不加入候选两轴、榜单、份额或晋升。原始输出、stderr、telemetry、源码/引擎/模板/pins SHA-256 全部保留，上游前后 pins 及 git diff 复核。

授权与入口：主线程 UTC 09:00 前明确请求本次独立有限诊断，要求 09:18 前派发。A20 不重开算法方向，不延长总窗口。
