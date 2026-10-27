# R7 检查点20：最小闭包实际集成通过、低normal解码有界判别

2026-10-22 23:50 UTC。已读D20的scope修复与3d9静态验收，R不更改D的矩阵或n1文件。原04:22:17截止、02:45源码冻结不变。

W12c已完整回收：ZIP46d41c2b/reportdd00148d，66 manifest项/CRC PASS。原公开60f单次插入最小证明块后的完整Kernel精确`173a091ecfa2d6ae7c3c048459e570cbffed4098d2a5ce70af3d2da6afa5c911` /167297bytes，固定Lean4.34实际完整编译PASS，原四spec完整类型与公理集前后相同；41声明审计三允许公理。5次实际编译均成功；fullgate/C/性能NOT_RUN。

供D复用的实际编译增量在`canonical-image-minimal-block-compiled.lean`，12192bytes，SHA256 `e2e2ce789b087824239d2b6ae52ac6f8e4620c7d36bb1ea1fc00c0c09b40f218`。原61d块仍完整保留；**剔除嵌套注释及空白后两份源码完全相同**，见`canonical-image-compiled-equivalence.json`，且移除公开合并文件的单次插入可逐字节恢复60f。此结果消除了最小块的公开宿主接入缺项，**不继承到D4792新矩阵loop或R3d9新sum循环的完整编译/gate**；它们的新接线仍NOT_RUN。

现有17组网页交付原ZIP/report共34主文件在E盘，索引已更新。W11完整110MB文本原件及8.8MB原ZIP保留，729KB精选证据可读；boxed UInt32立即数边界见检查点19。

下一段区别于NaN的低成本研究：`sum-decoder-low-screen.json`显示已暴露807计分sum前缀中295268个低normal(e=1..23)和31922个subnormal，前者约5.86%前缀word；它不是时间比例。多数低normal集中于sparse1/3及名称为subnormal0的实际normal输入。旧R4/R6记录只有已验24..254 table band与scalar守卫优化，未找到这一低normal精确缩放的既有实测结果。

因此23:48 UTC启动两路公开研究，不上传3d9/D私有源或本地统计：

- W13数学，25分钟目标00:13：唯一公式`tableProduct(u+0x10000000) * Float32.ofBits 0x2f800000`在原指数1..23全sign/fraction域是否精确恢复原word；补实际rounder与指数/符号不跨界证明。e=0明确排除。
- W14代码生成，15分钟目标00:03：同一公式只放在公开原decoder低条件失败且magnitude≥最小normal分支中，其他路径保持原机制。核实际Lean C/clang-O3直接及有序sum研究上下文，观察of_bits、常量once、FPspill、普通分支结构。无计时、无新完整竞赛候选，只有这一个方案。
- 本地`low-normal-rescale-oracle.json`已检查23874有限输入，并保留e=0真实整数模型反例（+0会错误变0x00400000）。不把有限模型当全域证明。不把两次乘法/去掉调用直接算作速度收益。

后续选择：若闭包证明缺口大、实际生成仍有额外常量调用/分配或普通路明显扩张，停止运行集成并保留资产；只有数学与代码生成都支持再评估是否值得向D提出一个受控decoder实验。现阶段不扩CI队列，单遍sum仍是R唯一新运行候选。下一检查点00:15 UTC。
