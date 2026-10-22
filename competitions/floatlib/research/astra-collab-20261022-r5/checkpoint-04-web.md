# R5-04：两路网页原件全部回收，新增有限性位域证明可供D集成

10:43Z两路均已自然完成并下载到E:/Download；R在它们运行期间独立交付了三份候选，未等待网页才开始实现。没有新增网页job。完整收据在web/R5-W01与web/R5-W02/download-receipt.json。

## W02 数学桥：一次toBits复用为guard与输出

主文件：`research/astra-collab-20261022-r5/web/R5-W02/original-extracted/FloatLib_R5-W02_FiniteBits/candidate/Kernel.lean`。136051 bytes，SHA `c09eb599cebddb59acd2a5fad1e6d8ce4eba1ca27f8469e03e6592b40d944b7a`。它是针对ba93父本的完整实际bmm入口候选，不是只追加未启用的定义。辅助证明`candidate/FiniteBits.lean`2693 bytes，完整七个证明体；R已逐项阅读，编译、公理、完整gate、性能仍NOT_RUN。

全域关键结论：`v.isFinite = finiteBits v.toBits`，其中finiteBits u为`((u >>> 23) &&& 255) != 255`。直接按公开逻辑模型unpack分类，再由UInt32/BitVec提取指数对应得到Bool相等；不要求v有限，不使用错误的NaN raw往返。构造端ofBits32(v.toBits)=ofFloat32(v)定义相等。新finish先取u，再判断指数并复用u；非finite仍走原raw A/B的内嵌Fin.foldl，未将昂贵fallback作为提前求值的函数实参。finish_eq_dot用新增finish_eq_original修复连接。

若R次finish中F次有限，两个相关runtime调用源级预期由R+F变R；不是整个内核加速倍数。非finite路径原来只isFinite，现在做toBits及整数guard；必须实测，不假设全部输出有限。这个数学变化可独立于R的输出组织及lazy地址机制合并。

已读D5-03队列与截止要求：R不再扩充另一个本地f01-r5候选/变体。这里完整网页原件作为小而独立的可合并机制交D按下一个槽和预算决定是否验证；若暂不进入本窗，保留为明确WRITTEN_NOT_RUN起点。D若验证，直接复制上述精确Kernel或只合并小证明+finish变化，保持父本出处；实际组合另绑SHA并gate。

ZIP：`E:/Download/FloatLib_R5-W02_FiniteBits.zip`，SHA `4ed3278ca5c155411cf959930bbd1aea8f71480b8cfdb06aa7432721cfb0700b`；CRC与16项清单已核对。MD副本与ZIP内报告字节一致。下载脚本没有执行。

## W01 独立输出审查

ZIP：`E:/Download/FloatLib_R5-W01_OutputRows.zip`，SHA `24fbddcf7558d955eaf43991bfce22cfebf7b8c70530946f4d36d5e218a21904`；CRC与19项清单通过。`OutputRows.inc.lean`5143 bytes，SHA `881f7638a5e20dfb0dc2784c9e0219f349c376e237284341a90d3c183e9f1f0c`，NOT_RUN。

它采用与R首稿相同的两层flatten路线，补了通用rowsOfFn等价引理、batch级base外提和16个解析输入。为控制重复CI，建议保留审查与引理，不重复测试等机制版本。双方论证一致不增加编译或性能证据。其“finite结果掩盖raw回退地址错误”已对照父本实际finish确认，并进入checkpoint-03定向见证。
