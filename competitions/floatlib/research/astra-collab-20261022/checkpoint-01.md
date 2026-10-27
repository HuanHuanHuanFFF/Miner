# R2-01：消除原生标量 raw 往返守卫

2026-10-21 18:20 UTC。已恢复十小时共同窗口及上轮完整验收；优先交付一个单机制包，不更改D正在做的原生bmm累加器。

候选：`competitions/floatlib/candidates/f01-r2-no-raw-guards/Kernel.lean`

- SHA-256 `923dfef502735784a9750b768d9c9de5c44c7c7b740318fe632c3ecf335fea13`，45359字节。
- 父版 `f01-d1-native-both-proof1`，SHA `707d22fed8443d883a183983397496492f9a09e071ffcf2715ef818384e44b85`；已核对真实文件。
- 只移除add和mul各自的两次raw往返运行比较。finite测试、原始输入异常回退、四个全域义务、sum/bmm算法与逐次舍入顺序保持原定义。
- `GuardBridge.finiteRoundtrip`沿用上轮未编译草稿：native finite排除NaN，证明原Model满足canonical invariant；用ofFloat32Model/toFloat32Model与canonicalizeModel_eq_self恢复完整位等式。它不要求结果仍finite。

**证明草稿尚未运行，性能NOT_RUN。** D请复制到f01-d2目录，先编译／审计，若通过执行完整gate和固定计时，并保留生成C。最小判别是每个标量快路径少两次`lean_float32_to_bits`，并检查是否保留正确异常回退。若桥接只在change／canonical字段处失败，请回传精确目标，R只修相应版本。

全域边界：NaN payload不可直接经过native转换而返回；本候选保留finite守卫。±0、次正规数及有限运算溢出都在原有有限native定理范围。guard消除正确性以Lean证明及完整gate为准，不能由有限样本替代。

后续R先核查位级finite桥接，作为上述包的后续候选；同时用实际可用网页6 Pro研究bmm多输出／转换摊销方向。网页输出需下载原件到E:/Download并索引给D，不因网页不可用阻塞源码研究。D仍是唯一Git／CI协调者；共同截止2026-10-22 04:16:11 UTC不变。
