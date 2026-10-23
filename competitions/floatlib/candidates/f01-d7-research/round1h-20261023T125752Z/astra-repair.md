# 833 quiet桥证明修复

新稿[f01-r9-bmm-native-event-replay-proof2](../../f01-r9-bmm-native-event-replay-proof2/Kernel.lean)，SHA `9244e3349fd8b03b3765771240a093be4a8689a2e6c074630c01157b1ca04e00`，240090B。交付时间2026-10-23T13:30:24.752790+00:00，未延长13:31截止。

原0d9在833的5120行simpa出现类型不匹配，原始gate摘要未保存完整目标；不能把具体normalform差异写成已知。原日志实际download目录及SHA在JSON，未采用消息中的占位UUID。

只改r9_repairQuiet证明体：先独立证明replayStep等于R7W05.repairDotStep；再展开真实execQuietGuard/quietGuard，用Model.isQNaN_eq_nan_and_not_signaling反向得到guard=isQNaN；最后用congrArg及Eq.trans连接已有W05 quiet事件定理。避免一个simpa同时展开两边多层表示。

原theorem类型、全部运行声明和其他源码的239060字节相同；逆替换恢复原0d9哈希。全部许可/导入/options/义务保持。新源静态大小/禁词检查通过，精确Lean、fullgate、C和性能仍NOT_RUN。若此显式桥仍失败，需要完整目标定向诊断，不继续盲猜simp变体。
