# R22 A：一次目标word检查的独立变体

阶段 **02:11:13—02:21:13 UTC**，共同截止03:12:47。不改旧冻结源，不CI/编译，不读确认组。D未承诺本窗口成本槽。

- **精确新源**：[Kernel-probe.lean](Kernel-probe.lean) **f59d12dc /237426B**；[Runtime.lean.inc](Runtime.lean.inc) **855bdc54 /6439B**；[ExpectedCheck.lean.inc](ExpectedCheck.lean.inc) **d1f0f723 /679B**。16审计根（原四public＋12辅助）见[manifest.json](manifest.json)/HelperAudit；全部**NOT_RUN**。实际callback为`Submission.R22FloatArrayB2Expected.guarded`，原public bmm仍B2，不冒充新public证明。
- **唯一运行改动**：namespace独立；把既有B.getD各绑定raw0/raw1后各decode一次；check由native source第二次toBits换为expected(raw)。旧布局、push时序、producer递归、loop、原两F32链、writer、odd右读、underflow/guard/fallback未改。没有重复getD或decode；`check_eq_native`直接用37cd的任意stored Bool等式。
- **可精确逆转**：[forward-runtime.patch](forward-runtime.patch)/[inverse-runtime.patch](inverse-runtime.patch)和builder重建确认，逆回运行体完整SHA为f5a6cbc6…，逆回旧Kernel为303a2397…。原f5a/303a/91ac/37cd都保留原字节。
- **入口文本修复留证**：原37cd注释中的`import word`被固定policy当import声明；被拒组合67ed0c98及policy-rejection.json保留。只在新装配副本`ExpectedNativeWord-policy.lean.inc`把该注释词改为readback，数学正文不变，逆回37cd已核。现f59d原固定intake/policy静态PASS，不是Lean/gate。
- **成本边界**：每字段source侧toBits表达式2→1，换整数mask/比较/选择；raw值跨检查存活。是否真实删FFI/CSE、寄存器影响、准备成功率、全调用收益均UNKNOWN。旧f5a也无测量，本体不继承任何结果。源就绪时间02:15:19。

下一决定仍是D余槽或下轮：实际typing→所选callback真实C/ASM→含准备/失败/回放/释放的完整成本。负面不扩public证明或换种子。当前没有合入主验收、正式提交或Git操作。
