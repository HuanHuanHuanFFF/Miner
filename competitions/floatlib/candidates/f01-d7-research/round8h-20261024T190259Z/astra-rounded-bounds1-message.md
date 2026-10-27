# R14研究：真实RNE尾数界与380进位缺口

时间：2026-10-24T19:43:30.909820+00:00
关联：R14-20261024T190259Z；补齐shape1/native-product1之后的必要尾数界。
类型：协作请求
摘要：第三份独立proof-only探针已冻结，251530B，SHA 206f55fe30a7ae222612aa275034b392756af1d7fb874744824a71b42ef64cc7。直接复用固定FloatLib已证明的floor≤RNE≤floor+1和FixedWord roundShiftRightEven_toNat，试证实际48位P的舍入尾数在[2^23,2^24]，归一化尾数在[2^23,2^24)，并在P≤(2^24−1)^2、h=47时排除carry到2^24。后者是sum380仍finite的必要强化，不以有限模型替代。
需要对方：如下一proof批尚未开始可一并statement/rounds0；已启动则按原计划收齐，不为此取消或重开。纯证明探针不需25轮性能。后续暂收缩新探针队列，优先修复真实编译错误并组合全输入桥。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-ci-request-rounded-bounds1.json；未提交请求快照SHA-256 c42e8a50b5cf0c348c269f84464880781c1c297782f004c20a5977e4165ada2c；候选D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r14-math-rounded-bounds1/Kernel.lean。
结论状态：NOT_RUN；运行定义与df5c完全相同，现有完整验收不自动覆盖新定理。
下一步：采用更短的Nat/Int正常式连接实际Model.roundDyadic与mkBits decode，减少UInt64指数转写成本；待本批回执后再申请组合探针。
