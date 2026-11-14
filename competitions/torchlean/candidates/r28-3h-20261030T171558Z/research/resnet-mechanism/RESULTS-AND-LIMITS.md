# R28 ResNet A：结果与边界

当前源码入口是HANDOFF.md / READY.json。零跳过c6a4da97仍未编译；support00928141与preferred空间ce1a8c2b都明确NativeOnly、没有新Submission.correct。A没有启动CI或本地Lean/native构建，因而没有A候选速度、完整gate、冠军或奖励结论。

## 本轮具体成果

- 保留public11完整旧实现/证明的可复现源配方，当前三个精确源均在256000B以内；已从只含列明依赖的干净目录重建同哈希。空间源只变更newkernels.conv2d，保留原Ybp回退及其它11入口；旧R8K/R8P不是新kernel证明。
- 空间F(2×2,3×3)的576个双线性系数精确核验；split25块8模型、父14安全/15通道实际raw-word溢出反例独立重放；完整128位逆变换、bias、−0/抵消/上下溢/边界word模型。preferred源允许mixedzero，旧seed42三profile中45244输出/舍入前整数匹配，但不是Lean/native。
- 63bit非零支撑编码的严格端点、哨兵与UInt64四累加器接口；9216有限输出状态。v1奇数通道未用bias/BW越界路径已修；单项zero仍保留原rawzW的零符号判定。
- 实际源码调用图修正：profile中的第五次conv是YlN分类器1×1。3×3占所测入口的推断份额不是整模份额；source11特殊3×3并未过滤零权重，36scalar旧计数不能被误写成18。
- 固定生成器低10位1024状态完整覆盖，最长循环零段7；CNN权重行长度至少27，BW.min!=511不会排掉此固定生成器的普通sparse行。仍保留真实guard，不按kind/seed特判，不将枚举比例写成成功概率。
- overlap32移植边界：在空间当前守卫内，一个变换乘积可宽85bit。先截低64位即使只累加一项也把4b8fffff变成415c0000（unsigned）或c0100000（signed）。这不否定overlap32，只要求其producer提供精确64位产品；当前空间源保留split25。

## 实际失败、修正和未闭合项

旧空间8e5/f59删除了必需的term application空白；旧supporta498及旧空间还有紧接标识符的!=词法缺陷。固定Lean4.34 Parser一手源码确认这些问题，当前版本恢复合法空白并只用无捕获短名节省体积；所有旧源/配方仍保留。Python表达式模型从来不能证明Lean可解析或可编译。

空间最初257224/256010B两版被本地sizeguard拒绝，未编译/未计时。当前ce1a只余13B，完整新all12证明能否装入UNKNOWN。空间源少55.6%源乘法，同时产生6.67–8倍循环step、partial数组和Nat索引检查；不能据MAC量宣称收益，native/C/ASM成本尚待D决定。

第一次空间wordpipeline JSON曾在追加边界检查时覆写。重建明确标记NOT_ORIGINAL_BYTES；当前v2原始字节和依赖清单已保存，不把重建当原件。混合域模型曾因反复导入生成器而被停止；这是本地验证脚本I/O问题，缓存不可变文本后重新完成，绝非候选性能结果。

最后标准CI6确认数据仅Droot/verification验收。A未读取其种子/输入/结果，也不将其它角色已测负结果直接当作A候选失败。Root的Mobile/Mixer/Norm确认优先级保持；本轮没有为A额外排独立CI。

## 下一次可判别动作

若继续空间路线，先用当前preferred精确源做完整ResNet同源成本判别，包含prep/cache/output/drop/fallback，并检查生成代码的循环、Nat读取和分配。只有正面信号才投入producer/array/64位真值/128同余/finisher/all12及源码预算。不得用旧正确性、公理打印、有限模型或阶段性编译替代实际新kernel完整gate。

一个尚未实现的存储备选是ByteArray64读取：base11的P2已是smallNat，因此机会仅是tag/转换指令，不是消除BigNat或缩小8B元素。固定ByteArray接口没有直接任意offset UInt64 primitive；8个字节读/shift/or是否被Clang合成一次load仍UNKNOWN，新增8byte准备成本也必须计入。此备选未建新Kernel、未排CI，不宣称收益。
