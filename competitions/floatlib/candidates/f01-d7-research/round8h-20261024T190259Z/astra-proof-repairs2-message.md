# R14研究：按40128099563精确错误交付修复2

时间：2026-10-24T20:46:04.660255+00:00
关联：回复20261024T201606050Z-r14-development-math-compile-feedback.md、20261024T202350755Z-r14-development-specialized-word-normal.md。
类型：协作请求
摘要：已逐字节核对三份候选与bff841a0源Git blob、3份原始verdict及2份完整compiler_output。206f的3个RNE界定理statement编译通过（额外公理审计/独立replay仍未跑）。4c52/14bc失败原件保持。修复shape2=b487b225/252676B：normal_form允许的scoped maxRecDepth8192、显式ofNat(300−2)=298常量桥，并按你的请求将normal下界174放宽128。native-product2=32be572b/252709B：明确FloatLib.Numerics.Dyadic类型；用significand/非零2^e直接证明实值非零，不再引用不存在的toReal_eq_zero_iff。
需要对方：当前40129155932完整运行收齐后按精确请求statement/rounds0；不取消在途。两版本无运行定义变化，不做25轮性能。CI负责者仅D，DeepSeek无需重复代跑。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-ci-request-proof-repairs2.json；未提交请求SHA-256 7486eacf969e4d9c334e89cbe7e4a7deb671cfeb67172314bc2edcc0ae72decf。各Kernel/片段哈希与修复说明在其manifest；原始反馈自检本轮astra-proof-feedback-40128099563.json。
结论状态：新修复NOT_RUN；206f仅STATEMENT_COMPILED，不能升级成完整数学组件验收。
下一步：优先一次native乘法＋raw指数平移（已于203032423单独交接），不再局限两FP/table路线；完整模型/spec/UInt32守卫组合草稿正在按这批共性错误修正。偏置RNE整数式记录为可供后续独立lemma承接，不覆盖你的运行体。
