# FloatLib 新一小时协作结果

研究窗口：北京时间2026-10-22 **12:36:27—13:36:27**。按用户要求持续推进一小时；窗口内启动的最终验收、独立确认和回执回收自然完成后再停止。没有取消任何已启动CI，也没有在截止后新增研究方向。

最终采用 [f01-d3-final-package](../../f01-d3-final-package/Kernel.lean) 的完整源码在 [completion.json](completion.json) 绑定；实际文件为同赛道f01-d3-final-package/Kernel.lean，SHA6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7。410/411在两台新runner完整通过：四个全输入义务、kernel重放、三允许公理、全部校验和及12类25轮配对计时。逐类、逐轮、CPU、种子、慢样本及原始回执见 [summary.json](summary.json)。[四运算看板](../../../../../dashboard.md)以当前冠军为1.00，当前仍不能取代冠军。

主要变化是八路有序原生累加配合USize/证明uget的矩阵循环，以及已证明全输入等价的数值重构输入转换接入有序求和。独立矩阵版405/408也完整通过；最终实际组合另验，未拼接不同版本最佳成绩。4路机器字、8路Nat与8路机器字在405同批对照；实际C确认热循环消掉Nat加乘和Array.size读取，尚未核对汇编，不声称SIMD。

数学路线从24位整数精确转换、带符号缩放表、可表示Model值的唯一性和native乘法桥得到无条件convert_eq。原草稿及三次实际修复保留；初次运行集成因重开命名空间缺少open失败，补齐后409编译通过，再由410/411接受实际sum_spec依赖并确认三允许公理。完整边界及源码身份见 [decoder-proof-status.json](decoder-proof-status.json)。

单遍FloatArray准备403完整通过但bmm耗时比约0.098，未优于四输出方向，保留负结果。R3原始机器字稿的uget/get等式缺项、八路零构造缺项、所有命名/类型失败均保留原件。全局边界检查外提只作为下一起点，未编译/计时。

沿用同一Astra/xhigh研究会话，D唯一Git/CI协调者；研究侧已结束。旧网页任务与本轮辅助网页均已回收，E盘9份ZIP和9份报告全部重读校验，压缩包脚本未执行。原始源码、未采用边界和研究交接见 [research-closeout-receipt.json](research-closeout-receipt.json)。

前轮十小时任务曾被错误套用历史半小时收尾消息，提前停止；这是执行误判，未作为本轮授权或时长来源。原始记录保留在previous-state.json，当前唯一状态入口为../../../coordination/development-status.json。
