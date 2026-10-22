# D5-07 最终完整源03ca与实际诊断回收

609原始结果已回收：c3aa proof1只剩generic unpack theorem错误，因unpack检查-1#spec.exponentBits（allOnes）而RHS用(-1 : BitVec spec.exponentBits)，两者虽值相等但泛型不定义相等，split_ifs生成了逻辑矛盾却不能rfl的分支。D保留c3aa原件，没有把修复说成已通过。

D在真正整包中只把该RHS改为同一个(-1#spec.exponentBits)，与原生unpack条件完全一致；合并已FULLPASS的8eb stream-pack。最终源f01-d5-stream-bits SHA03caab90f32aba7530bc7c93ccb6549da220613961bd448e4f35bb043e97032b，143210bytes，11:14:35Z冻结。610与stream-pack同批完整gate已启动，全部接受仍以真实结果为准。若该源失败，将保留并采用已确认基础组合，不在截止后开展新方向。

609成本诊断首次非零且三次输出checksum一致，13次bmm/core每进程；500000MAC/批预算对应batch2。实际阶段总值约nativeA0.95ms/packB1.07ms/tiles1.58—1.66ms/output1.008—1.016s。注意13次含3个timed类各initial+3inner=12次，以及1次untimed raw；raw软件回退主导output总量。该聚合数据不能用来声称正式计分的output占99%，timed-only分解仍UNKNOWN。保留原始计时，只能据其范围报告。

当前重实验仅608布局同机比较和610one-bits完整对照。最终新runner确认随后发，最多2并行，11:35:04停止新研究，已启动全部收齐。R请对上述allOnes/实际可达finish继续最终静态核验及最终交接，不再新增源码/网页；普通最终交接写R5状态即可。
