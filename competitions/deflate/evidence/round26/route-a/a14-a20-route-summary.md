# R26 延长窗口路线 A：可复用结论与停止边界

本段覆盖 A14–A19 已执行结果，以及 A20 已完成的独立测量诊断。没有新候选建立稳定 5%／10% 条件份额；没有正式上传或完整 Lean gate。正确性、计数、编译结果、配对性能和正式成绩分开。全局最新榜单重放由主线程维护，下面份额只指保存的 29879 快照，不是本文件新查询。

| 动作 | 已执行证据 | 改变下一轮起点的结论 |
|---|---|---|
| A14，641 有序 tag8/pos24 head | Native 444 等价、169 边界、2,090,204 oracle；28 同 token/output。原协议两块总轴慢 3.121938%／3.336960%，同源码副本也回退 | 19.05% tag miss 并未覆盖维护和查询成本；逐文件回退集中于实际修改的 PC parser。停止这份表示及完整 proof，不扫 tag 位布局救回 |
| A15，上一已发射距离替换既有探测 | 原轨迹 shadow：normal 正 3,940／负 37,837；lazy 正 6,804／负 61,808；双向收益损失覆盖 | 固定替换损失占优，不能从少数大赢轨迹挑文件或继续补阈值。尚未执行真实新 parse，质量／速度 UNKNOWN |
| A16，641 producer 保留近距离旧 head | 原编码少 510 B，仅 −0.00141475 pp；decode 通过。真实路径 3,923,837 次 link 只省 16,897 次（0.430624%） | 近匹配消费者拒绝规则一致不等于 producer 改动同 token。新增比较覆盖全部调用而省写很薄，停止这份精确版配对；未知速度不是零收益或已证慢 |
| A17，658 不读取最后一个 prev | 原 shim/release 实际 lowering；源级 499,847 末读中 depth1 的 362,448 与长度终止 3,405 已被编译器消除，残留 normal 133,994 | 必须按实际特化分支判断。源级末读次数严重高估剩余机会；不直接投入独立候选和 full gate |
| A18，把必要 prefix 窗口移到658 U118 | 444 等价、5,527 helper、28 同 token/output。取消 59,350／614,598 次 common（9.6567%），新增 query word 1,458,709 读及窗口维护 | 必要性判断正确，但取消覆盖不足以证明新增读有净利。停止配对；不叠加 A17 或扫窗口参数。有限等价不替代 Lean |
| A19，658 common 两处安全 offset wrapping | 1,548 helper、28 同 token/output、前置官方提取、原协议双副本两块；实际 row2 ASM 未变，row9 main word loop 未变，lazy 少一热 guard | 不能把 IR 的 checked 操作数或全函数 opcode 下降当速度。两块主总轴 +0.277417%／−0.148876%，副本 +0.129353%／+0.573086%；不足以分配完整 gate |
| A20，原 engine 有效 CPU 放置 | 独立作业 38227767865 成功；精确 exe/PID/starttime 绑定后52样本，实际 mask 0–3、采样 CPU 0／2，原28输入/token/output及DSO同A19 | 本次 CPU0 请求没有限制成单核。频率与scope cpuset字段不可见，原因 UNKNOWN；不形成候选成绩，也不能反推 A19 历史根因 |

A19 按 29879 的主候选／主校准两块条件份额为 0／0.77630185%；主候选／影子校准为 0／0.88489789%。候选同源码副本在两种校准下两块均 0。最低值均 0，所有视图均未达 5% 或 10%；同一 runner 的副本及校准视图不增加独立样本。保留两个非零峰作为线索，不把中位数或达标次数解释为正式概率。

## 同源码分歧已定位到什么

[A19 精确 total 中位 rep 的分解](a19-paired-cost.json)按代数恒等式将原总轴差分成 parser、encoder 和各自 incumbent 分母项，不产生修正成绩。主候选第二块总轴 −0.148876% 中，parser 是 +0.623787 pp、encoder 是 −0.840774 pp、分母是 +0.068111 pp。四种父／候选配对视图的全轴 parser 项均为正；row9 五文件局部混合，不能简单扩大到所有 parser 调用。

[全部原始 11 次分布及执行顺序](a19-process-audit.json)确认输入、token、output、同源 DSO 和 incumbent DSO 身份。第二块候选副本 encoder 与 incumbent encoder 的方向在 28／28 文件一致；父副本为 26／28。父副本连续尾段普遍跨阶段下降约 9–14%，候选副本前五文件也有类似下降，而 lean／machine-code 同升约 13–14%。因此既不是单慢 rep，也不是全进程一个固定乘数。

进程内部始终 incumbent 先、候选后；反序块只反转不同配对进程的顺序。R23 已有等次数 fixed20／balanced20 干预证据，顺序能改变符号但未消除全部残差。A19 的分段共同移动与未闭合的机器／进程状态兼容，根因是否相同仍 UNKNOWN。旧 driver affinity 不能证明 engine 迁移，A20 只读本次精确 engine 状态。

## 后续可复用起点

- 641 原 PC kernel 仍有完整冻结父证明与明确有限 observer。A14、A15、A16 分别排除了这次具体表示、固定交换与薄省写设计，不能推广成所有过滤／重复距离／近链接机制都无效。
- public658 是已测真实质量起点：公开原编码 5,159,012 B，较 641 少 63,817 B，平衡质量改善约 0.36457 pp。其活跃 U118 路由与特化已定位；这不是新 DP kernel，也未建立其稳定可支付位置。
- A19 精确 Rust 保留为一个窄安全算术组件；证明接口只需局部 common_loop 地址不变量适配的预审已在 [proof-interface notes](a19-proof-interface-notes.md)。尚未编译新 Lean，剩余字节约束与原 obligation 仍须完整 gate。
- 下一次若有真实质量／总时间余量，应先按原协议和同源码对照验增益，再为精确 Rust／Lean 做 gate 和冻结后新 runner 独立确认；本段没有一份足以据现有信号跳过这些步骤。

## A20 的新证据及未来最小诊断

本次 runner 是 AMD EPYC 7763；A19 是 Intel Xeon 6973P-C。引擎二进制仍为同一 SHA-256 `ab202460691492f48d5c632375f5df2a74fc3769a81337e876607e9326a46fac`。唯一 PID 5818／starttime 49478，在13秒左右观察窗的52样本中，CPU0占14次、CPU2占38次；第一次观察到CPU变化约在首样本后3.521秒。这里 CPU 字段是该task最后执行CPU，不是逐调用trace。监控线程5816有效固定CPU1。

引擎有效 mask 始终0–3，原请求CPU0未落实为单核限制。实际scope的cpu.stat可读，但cpuset.cpus、cpuset.cpus.effective、cpu.max均不存在；CPU0/2的cpufreq字段全部不可见。不能从缺失字段推出限制机制或频率原因。R24早已发现pre-exec广mask，且显式绑核没统一修复副本差，本次新增的是当前已exec引擎的精确身份和运行中观察。[A20原始绑定反馈](a20-placement-feedback.json)

未来若同源码分歧继续左右晋升，最小有区分力的下一步是把原始阶段时长与逐调用CPU前后值关联，见[未执行建议](a20-next-diagnostic-plan.md)。只做两份同binary原配对进程，使用scratch引擎的计时区外遥测；不再先重复balanced20或扫绑核条件。遥测属于诊断，不校正任何原协议成绩。本轮未准备或运行这一新实验。

逐次原始回执、失败边界和哈希见 a14-screen-feedback.json、a15-feedback.json、a16-feedback.json、a17-feedback.json、a18-feedback.json、[a19-screen-feedback.json](a19-screen-feedback.json)及[a20-placement-feedback.json](a20-placement-feedback.json)。A20预声明与原始云端文件保持原字节。
