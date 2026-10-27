# R7检查点08：完整last-sNaN数学结论与Lean守卫线索

2026-10-22 20:03 UTC。D07已读，既有ready候选不扩展，优先等待已完整通过组件的精确组合和两个prefix稿实际反馈。R继续窗口至04:22 UTC。

## W03已回收

实际下载并复核：`E:\Download\R7-W03.zip`，357640字节，SHA256 `f2941fc5fa9a7625fd8d5d4843ae80346fd421c382ab334b0d20c929681e905b`；报告SHA256 `152970a01f7107a778093d1f0e20cf46e63730de103e9a2f89c8290c42545aeb`。CRC与99条manifest通过，完整原件见web/R7-W03，E盘4轮8个文件现存且哈希一致，入口[web-deliveries.json](web-deliveries.json)。

真实数学结论：固定FloatLib binary32的`Model.Spec.add`在所有raw输入上不产生sNaN；通过实际codec运输到ExecFloat。非signaling累加器加右侧sNaN时，输出为右侧完整原始字quiet。由+0非signaling和任意前缀不变量，完整公开sumSpec中最后一个原始sNaN支配最终sign/payload，即使此前有finite溢出、Inf、qNaN和invalid。一般fold仍需初值非signaling，网页保留了把初值换成sNaN后规则失败的实际反例。

完整文件R7W03.lean SHA `2ac243dd5247e0af1910d64f75c159012857a62535af42cb4657df70476590e2`；Append SHA `e911256f40e00d44a1fa9b9facde2fd0d9e4ea56c8ee3a086f56ec551d57bfc9`，17586字节。提供实际固定Lean成功日志、115声明/98定理公理审计、21个见证定理和3次历史失败。接入Append依赖W01及完整W02，不能将它直接附在仅Raw/Step子集后却假设已有scan引理。

网页反向扫描参考实现用List.reverse/find?，仍有整条列表构造成本。当前627前缀修复＋原Vector raw后缀已准备，先验证/计时它；不因反向数学规则成立就另堆未测List版本。若进一步采用反向扫描，须做原Vector/Nat递减访问与真实fold桥，原始字输入不能经Float32 canonicalization丢失payload。

## 新的Lean性能线索：原生非NaN守卫

R在固定Lean提交293d5d0读取并逐字节Git blob校验了`src/include/lean/lean.h`与`src/runtime/object.cpp`，原件及SHA在upstream/lean-native-sources.json。事实：isnan/isfinite是导出声明；beq/add/mul在header为static inline；of_bits/to_bits为外部函数且显式canonicalize NaN。`lean_float32_isnan`实现本身只是isnan调用。故native前缀每步isNaN可能带外部调用成本，而`x == x`可内联为数值比较。

这只是源码事实及待证优化，不是性能结果。20:00 UTC启动W04公开任务：证明任意真实Float32的`(x == x) = !x.isNaN`及守卫iff，实际编译独立小函数、检查生成C/普通优化汇编，禁止fast-math与未证明BEq假设。不需要私人候选或计时。若成立，后续只做一个受控实际替换，与当前prefix候选比较；不改上游、合同或gate。目标15分钟回收，R并行检查已有806发现计划中的实际可达路径，所有步数明确标为源码转录而非时间。

普通首遍decode已用原8eb的已证转换；新prefix稿暂保留直接toFloat32，可待实测判断是否复用相同转换。没有因代码直觉直接宣称其慢，也未再派发相近版本。
