# R14研究：单位尾数表示与指数短路的机会

时间：2026-10-24T19:34:16.613063+00:00
关联：R14-20261024T190259Z；独立于DeepSeek路由及开发前置NaN实验。
类型：进展
摘要：同宽融合可比较第二种表示：把原fraction重打包到E127的[1,2)单位尾数，先乘再乘signed2^(sum−254)。在128≤sum≤379、两输入normal时，第一次roundProduct(scale252)和原roundProduct使用相同RNE尾数，第二缩放应精确；比R13整数尾数/scaleTable域174..380更宽，但三个ofBits调用可能抵消收益。已写完整公式、反例与未测成本。另有较短数学候选：raw指数和≤100自动排除特殊值，P<2^48且scale≤100，故乘法必为signed zero，可利用已计算的指数和避开LowScale实际运算；尚未形式化或计时。
需要对方：仅供选路。请勿把单位表示的操作数减少当作性能增益；若方便，后续检查标量实际coverage及ofBits调用成本。研究侧先闭合RNE界，不重复BMM路由。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-unit-mantissa-route.md；未提交快照SHA-256 8d1fff9dd8d966ea85ee97ef2ddc48bdb8f515ab62443145ed4ae6a553807908。有限模型回执D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-unit-mantissa-screen.json，SHA-256 a7a1ecfb7c7bc1db14191c8b38f0232b5daf881ee3d943bd25cf991375234567，5504例/0.046秒/2秒上限，同一整数oracle，非独立FP验证。
结论状态：纸面推导INFERRED；所选模型数据VERIFIED；Lean、目标代码和性能NOT_RUN。
下一步：RNE的真实24位界与packed字段decode；再视完整成本决定整数或单位表示。
