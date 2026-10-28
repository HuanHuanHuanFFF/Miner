# 四行流式的解码复用前提

21:41 UTC新证据：D已沿cost1真实计时loop追到专化map helper，两者closure/Float32 box静态分配site均为0；standalone advance的分配不能外推热循环。见`../development-cost1-actual-loop-audit.json`。这里后继机制的理由是B转换复用及有效四lane，不再以删除每k闭包为理由。Cell复用分支与分配fallback的动态频率仍未单独测量。

这是后继路线的成本前提，未生成新候选，也未读取冻结确认数据。D已观察两行Cell实际使用mulps/addps的低两lane，四行Cell能否更快仍待完整调用。

原B2并非独立dot：它按两列打包B，在一次矩阵调用中只解码每个有效B一次（奇尾另有padding），而A按每个两列组重复解码。忽略padding/奇尾时，源级转换数分别约为B的`batch*n*p`和A的`batch*m*n*ceil(p/2)`。

四行流式若仍每k直接读取raw B，则A解码约`batch*m*n`，B却为`batch*(m/4)*n*p`；当m大时，B重复解码会吃掉A的复用。有效四lane本身不消除这个问题。若首完整成本没有明确优势，下一次有实质变化的判别应考虑**一次准备B、由全四行组共享**，而非只换行阈值或seed。转换总数可接近`batch*n*(m+p)`，仍保留每输出原k序。

准备B的实际成本不能省略。安全Array Float32可能带逐元素Float32 box/槽，比B2的双字段record不同；map创建、读取、RC、缓存容量和完整析构都需计时。也可复用现有F2/F4字段包作为只读prepared B，但若改变访问布局必须一并计入准备/尾部/读取成本。原raw B保留给NaN replay，不能仅留下prepared副本。

证明接口可只要求`prepared_get k j = Binary.toFloat32(rawB[...])`，再实例化既有逐lane storageLoop精化。它是有具体变化的下一判别，**不支持预言收益、分配字节或采用**。D先收首成本screen；不改当前冻结22c/ebfb源。
