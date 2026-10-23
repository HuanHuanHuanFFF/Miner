# cc06：815实际编译失败的证明修复稿

精确源SHA-256：`a84c1618cebe5892cbffd3657de8f2e6b96f0f70df2811af75c09a6ea3c5f736`；233714字节，余22286字节。

父本为`f01-d7-direct-singlepass`，SHA `cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc`。811完整gate在statement失败，815对同源采集完整编译输出，再次失败；没有cc06计时结果。

本稿只替换7个theorem的证明体：quiet suffix归纳、raw NaN边界、两个Bool判据、Nat归纳的fold累积值连接、USize与Vector读取对齐、最终sumSpec定义闭合。全部theorem类型、终止度量、运行声明、导入、options和许可保持原字节。排除这7个证明体后的228722字节完全相同；逆向替换恢复原cc06全部232363字节。

新源原静态policy检查通过，**精确Lean statement、kernel replay、公理、checksum、完整gate与25配对轮均NOT_RUN**。这不是已通过证明或已获得提速的报告。源码运行部分一致也不声明生成对象逐字节相同。

实际错误、逐条修复映射、原输出SHA和可逆patch在[修复说明](../../research/astra-collab-20261023-r7/proof-repair-815.md)与[机器记录](../../research/astra-collab-20261023-r7/proof-repair-815.json)。D负责精确CI验证；R未操作Git、push、CI、其他会话、网页或子agent，也未本地运行/安装Linux工具链。
