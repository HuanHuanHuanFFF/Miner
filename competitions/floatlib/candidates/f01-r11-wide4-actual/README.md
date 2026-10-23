# R11 四行真实入口初版

冻结源码 b554f9fe8e0c89ccb9caa0ddb7806fa11fefdabee6740df7a755b0b8b2e37f58，252357 B。静态政策检查和精确底座逆恢复 PASS；新 Lean、完整 gate、性能均 NOT_RUN。优先 statement 发现具体证明错误，然后原完整 gate。

底座 749bc933 / 223584 B。原最外层 UnderflowZero 全 A/B 扫描及零填充分支保持原字节。只在其 miss 路径、m≥4、n>4、p>2、n 与 A 大小都小于 USize.size 时进入新路径；未命中走原 direct/fused 路线。

一次 global nativeA 和既有 F10 packedB。按 batch 内每个完整四行块计算一个 Vector F40 (groups p)，每个列组一次四行共享 B 的 wordLoop，然后按 r=0..3、j=0..p-1 顺序调用原 Packed10.finish 并写入最终数组。每块结果缓存使用后释放，不缓存全矩阵；每 batch 剩余 0..3 行复用原 RowStream.row。运行时 lane40 直接读取 F40 字段，不先构造 F10。

机器循环参数与已获 921 实际机器码证据的 eb9e 完全相同。原投影 afd8 保留。within/run 桥闭合至 Packed10Index.runDot；run 对任意数组另有精确四个旧单行 dot 的 fallback，所以不靠抽象地址前提。buildTiles_projects 绑定真实 packB 和真实 raw A/B，输出前缀证明继续闭合至 referenceBmm 与原 bmmSpec。此前未编译的 Sol writer 最终 42a3547c 作为输入，仅在本候选中把三个 Nat 后继乘法 rewrite 改为 Nat.succ_mul；原文件未动。

生成器位于本轮 astra-build-wide-actual.py，默认只读验证；--write 只允许不存在的新 Kernel。increment.lean 留存全部插入声明。manifest 记录原始输入哈希、逆恢复和外层原字节。

待验证：投影与 wrapper 的 elaboration；泛型 writer 的全域证明；真实入口下缓存是否仅计算一次、原 F10 输入是否借用、尾部路径和 valid lane NaN 回放；完整准备/输出成本及新输入独立确认。921 的原入口 gate 与 10 路 SIMD 只支持继续实验，不是本矩阵算法验收或提速。
