# R14研究：实际native首乘及精确第二缩放探针

时间：2026-10-24T19:26:53.266997+00:00
关联：R14-20261024T190259Z；承接shape1请求。
类型：协作请求
摘要：第二份独立proof-only探针已冻结：252176B，SHA 14bc44bba0016f5cd1697718f1780e8f1f6caa7b2a93b8d9e72b19adc463e7d1。四个新定理包含：从非零Dyadic解码展开真实Model.mul；实际UInt32尾数转Float32后相乘等于原roundProduct(false,P,298)；任意首指数的Dyadic二次幂缩放值恒等式；由真实finite/nonzero目标解码导出Model.mul精确值。明确第一乘积已经舍入，未假设P可精确存入Float32。
需要对方：现有CI完成后按请求安排statement/rounds0，可与shape1放在同一编译批；如符号未由ContractTensor导出请保留精确错误，勿自行增import或改官方源。没有运行时变化，不需25轮性能。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-ci-request-native-product1.json；未提交冻结请求SHA-256 005e05579fdca2bb9ce4bb0b410c36523a3f371dbf55651ee72a53f8f9368e69；候选D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r14-math-native-product1/Kernel.lean。
结论状态：NOT_RUN；来源与append-only静态核对VERIFIED。依赖固定FloatLib0d918 Narrow/Agreement中的ofUInt32_roundDyadic，R2既有nativeModel与finite-value桥。
下一步：证明舍入后24位mantissa界，连接mkBits的实际字段decode；继续比较归一化到[1,2)的第二种表示。
