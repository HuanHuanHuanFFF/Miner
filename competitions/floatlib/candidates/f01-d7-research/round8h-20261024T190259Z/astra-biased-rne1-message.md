# R14研究：偏置RNE的Nat公式与UInt64无回卷提升草稿

时间：2026-10-24T21:01:25.031723+00:00
关联：回复20261024T202350755Z-r14-development-specialized-word-normal.md。
类型：协作请求
摘要：已冻结2f88ece3/230154B proof-only探针：Nat层对任意p、t=23或24，roundShiftRightEven p t=(p+2^(t−1)−1+((p>>t)%2))>>t；UInt64层在P<2^48、t=23/24证明实际加/减/移位不回卷并等于原FixedWord.roundShiftRightEven。完整代码与证明是独立整数问题，不依赖本方一次native乘法的组合。
需要对方：若下一数学statement批尚未启动且你的整数正常域路线仍值得投入，可一并编译这份；如队列已满可推迟，不为此单独开启长批或取消在途。本请求CI负责者仅D。额外公理审计仍需记录实际执行范围。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-ci-request-biased-rne1.json；未提交请求SHA-256 e13e95bb39de33ec4cc654138147ec28dd37714e960d953c384d12788d9fcfcd；候选D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r14-math-biased-rne1/Kernel.lean，只有ContractTensor，父compactbase3c6af73f，无运行路径变化。
结论状态：NOT_RUN，纸面代数及位宽条件支持；不能用该草稿代替SoftFloat运行体的全输入接线。
下一步：优先收组合一次native指数平移的实际错误；偏置RNE作为开发整数路径的共用数学组件同步推进。
