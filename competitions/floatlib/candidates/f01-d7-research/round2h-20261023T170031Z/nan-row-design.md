# R10：A 行首 NaN 分流，低覆盖停放

状态为 **PARKED_BEFORE_IMPLEMENTATION_LOW_EXPOSED_COVERAGE**，不可标记 READY。父源精确 SHA-256为 `41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7`，235169字节。本子任务在读完相关实现、完成机制可行性检查后收到停止指令，未创建候选目录、Kernel、builder或manifest，未修改任何原源码／工具／状态。

候选机制是在 `RowStream.core` 每行计算 `rowTiles` 前检查A首元素的raw NaN分类；命中时直接为每个输出调用原 `R7NaNReplay.replayEarly`，否则保持原packed rowstream。`DirectSmall` 可相应绕开原生整段dot后再replay的重复路径。`nativeA.map`和`packB`完整准备仍在原计时入口内。

从父源可核对，`R7NaNReplay.replayEarly_eq` 对所有输入均等于原顺序软件fold；所以guard只负责性能分流，正确性不依赖新的“首项NaN”数学引理。实际实现仍需证明新行向量／flatMap地址与旧输出相同，并经过完整Lean／公理／checksum／计时gate。不能直接填入quiet后的A：第一步原乘法还需读取该列B，B的signaling NaN可能有优先级，必须保留每列原始B与已有replay语义。

根协调者提供的 `first-nan-row-exposure.json` 对已暴露输入使用源码生成器转写计数。本子任务复核每组34个计时BMM case的字段求和，均与总计一致；也核对相应已存在的原drawn-plan SHA，并由原summary确认seed。原计数报告的seed为null，原文件没有被补写，映射另存在本设计JSON。

| 已暴露seed | 全BMM MAC工作量 | 首A为NaN的行数 | 可免后缀MAC | 占MAC工作量 |
|---|---:|---:|---:|---:|
| 821 | 4456884 | 472 | 369 | 0.008279% |
| 822 | 4154372 | 96 | 1792 | 0.043135% |
| 841 | 4198383 | 111 | 1362 | 0.032441% |

821的472个首NaN行中421个来自n=1，后缀n−1为0。822／841的可免后缀工作量也很小；不能将821的n=1占比泛化到所有样本。这个最小计数实验削弱了当前投入理由，根协调者据此决定在实现前停放，不消耗完整候选证明与CI窗口。

这里的百分比是**工作量计数**，不是耗时占比或严格性能上界。它没有计入原生第一步本身、packed补齐lane、guard／读数组开销、精确replay成本，以及不变的map／pack／output成本；生成器转写也不是runner事件计数。因此该方向的实际收益仍为 **UNKNOWN**，没有宣称数学不可能、实测退步或对未来／私有输入无效。

证据原件SHA-256为 `2b8f4b697e1c5839bd273e6e9d447c7e0157e537abaa7ca6de8f22e7ff372615`。输入、来源、逐组有效case、总数复核与限制均保存在 `nan-row-design.json`。完整Lean、完整gate与性能均 **NOT_RUN**；没有Git、CI、网络、派发、未来842／843输入查看或生成。
