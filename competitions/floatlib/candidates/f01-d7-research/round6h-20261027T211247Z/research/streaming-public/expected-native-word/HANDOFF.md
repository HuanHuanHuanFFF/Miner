# R22 A：当前 expected native word 小接口

**本接口已冻结**；root随后授权的独立变体当前索引在[../floatarray-expected-variant/HANDOFF.md](../floatarray-expected-variant/HANDOFF.md)。本37cd原件不改，仅新装配副本修正会触发import词扫描的注释。

阶段 **01:50:33—02:10:33 UTC**；共同截止 **03:12:47**。仅3根数学储备，无运行版本、Kernel、CI；不读新确认组。f5a/303a/91ac再次核字节不变。

- [ExpectedNativeWord.lean.inc](ExpectedNativeWord.lean.inc)：**37cd4435 /1700B/3根/NOT_RUN**。任意raw x导入native再导回，其word在absraw≤Inf时为原raw，否则为正0x7fc00000；继而**任意stored**下fb7d双边native检查等于backcast word与整数expected比较，不假设检查必过。
- 常量经固定0d918源码核实：native nan→canonicalNaN；canonicalNaN=expMask OR quietBit；binary32 exp8/frac23给0x7f800000 OR0x00400000。5份primary新取源码全部Git blob SHA原字节匹配；来源/版权在[primary/source-index.json](primary/source-index.json)。不是猜NaN字或采用论文断言。
- [manifest.json](manifest.json)保存根/依赖/SHA；3072纯整数字段例与3个变异覆盖±Inf/−0/非canonical负NaN边界，不是Lean/Float32/cast验收。
- 未来唯一成本前提：保已读raw和sourceF32，用expected(raw)省source侧toBits表达式，每字段2→1，另加整数mask/比较/选择；不加decode，保backcast检查失败和原NaN replay。实际FFI/速度UNKNOWN，**不改当前冻结源，不接当前确认候选**。

[INTERFACE.md](INTERFACE.md)给精确等式和后续边界。上一阶段包装/容量核验仍在../floatarray-storage/ALLOCATION-PREMISE.md；当前只等已分派真实首错或下一独立方向，不展开public BMM证明。
