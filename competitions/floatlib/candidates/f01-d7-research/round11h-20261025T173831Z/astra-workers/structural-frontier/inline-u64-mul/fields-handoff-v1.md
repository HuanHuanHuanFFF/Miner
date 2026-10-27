# UInt64 运行字段恢复桥

第一编译输入继续保持probe-b2-v1/的9f9a源不变，优先验证13个UInt64数值声明。新增Fields-u64-integer-v1.lean.inc是独立后续证明尝试，沿真实UInt64阈值、shift、narrow与UInt32减法，得到原R14ExponentShift的middleExponent/storedFraction，并证明输出E1..254及fraction<2^23。`packed_fields`的结论逐字段匹配原full-gated `model_mul_normal_fields`，没有换成实数等价。

Runtime-fields-bridge-v1.lean.inc再把真实选中normalCore的let链化为上述字段表达式，复用B2的mantissa_bounds；仍显式保留一个原字sign-XOR对应Bool sign的逻辑前提。该前提必须在原始mul_spec接线中证明，不能当作新primitive假设。精确公共guard、sum与原始raw指数关系、sign关系，以及原model_mul_normal_fields/Configured carrier桥仍由最后接线闭合。

这些文件尚未编译。依赖顺序：9f9a math/interface附录→冻结Runtime-u64-mul-integer-v3-lf.lean.inc→Fields→Runtime-fields。不要在首个9f9a确认前修改其文件或把这些后续声明当成其已验结果；不为它们独立排第二条完整计时队列。下一决定由首个实际编译错误/成功及代码生成证据驱动。
