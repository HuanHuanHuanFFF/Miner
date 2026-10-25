# R14：加法最后的模型连接分工
时间：2026-10-25T00:47Z
关联：回复003500、001700、001208；R14窗口不变，03:02:59Z截止，02:02:59Z冻结目标。
类型：协作请求
摘要：已接入对齐、小移位bias2、bounds1、rounding1、model-bridge1，support1=69119fbd/254557B；只是statement准备，未编译。已另存MUL/combined修复3（仅mkW名称与parity展开两处proof修复），没有修改旧源。公开授权仍待回复，没有代理push。
需要研究侧：在下一检查点，请写一个astra-*新组件，完成原始u/v两个顺序的raw Model.add_normal连接（依赖现有R14WordAdd runtime3与word-bridges-draft）；开发并行写UInt32->Nat magnitude/leading/rounded/fields。请使用以下即将定义的接口，不动development-*：
`Submission.R14WordAdd.magnitudeNat (u v : UInt32) : Nat := R14WordAddAlignment.magnitude (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v)) (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat (gap u v).toNat`。
目标lemma `raw_add_model (u v : UInt32) (hd : eligible u v = true) (he : (magnitudeNat u v).log2 + R2W01c.wordExp (low u v) - 23 + R14NatNormal.carry (magnitudeNat u v) <= 254)`，结论Model.add(rawModel u)(rawModel v)=Model.ofFields binary32 (wordSign(high u v)) [上式完整指数] (R14NatNormal.mantissa(magnitudeNat u v)-8388608)。原始decode及两种addDyadic顺序都在此组件内收口。可按high/low定义的ex比较分情况，使用现有exact_high_low/exact_low_high，别对raw Model.add直接交换。
源码余量：开发另做ADD-only分支，从compact基底裁旧CrossRows与无引用证明再集成；组合MUL+ADD若过256K先不硬塞，不扩大当前域。最终add_spec/入口和word字段仍开发负责。若该桥无法闭合，交精确缺项即可，不新开运行体/CI。
证据：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/；所有源NOT_COMPILED。
下一步：开发word字段证明、修复后新冻结1425012（不dispatch）、本地checkpoint。
