# Pro 单次关键审查：缓存候选 f1b3

07:43 UTC回收；原件先下载至E:/Download，再按原字节整理入本分支research/pro-results/20261029T074305Z/，7098 B、SHA256 `7317369c0196e020768ba622c1eb221ae2c6f37bde36730dc33420c5eb50bfa4`。无压缩包。UI Pro独立审查12m16s，要求不派子agent；backend型号／额度UNKNOWN。附件精确f1b3/52849B，与当前policy1仅声明作用域修正的差异另按D源码回执核对。本文件为公开技术提取，不发布私有会话原文／链接。

没有找出缓存导致的数学值反例，也没有确认具体Lean tactic错误；不能据此写Lean/gate通过。报告核对了全部输入量词、默认decode、原raw special fallback、Nat空间索引、stable norm域与最终舍入不变。实际源的full gate仍以原CI为准；第一批f1b3停于policy。

## 新的具体执行边界

对ConvShape `cin=h=w=kh=kw=stride=1, pad=cout=0`，输入、权重、bias均空，官方输出直接为空；候选`conv2dCached`却在输出Array.ofFn前先求`patchWords s inp`。R已读policy1源码997–1028和最终kernels1138，确认这个预计算顺序仍存在；它会尝试构造一个patch并走空dinp的get!。

这不是逻辑值等式的反例：Lean模型中的越界默认值允许证明相等。它是可能新增panic与无用大分配的执行风险；是否被编译器消去、panic是否退出，尚未在原生生成物核验，不能写成已经实测崩溃。最小后续诊断是编译后对这一空输出调用检查实际执行与分配；或在独立新源先判断输出为空，保留当前冻结源和全输入证明。不要因此取消在途CI。

## 成本判别

patch相对tensor-decode-cache的增量主要删除重复坐标／padding／索引，不能再把解码共享计一次收益。P=ho*wo、K=cin*kh*kw、C=cout时，坐标工作由约CPK到PK，同时新增PK个引用槽和P个数组头；例如P=4096、K=576，仅8字节引用槽即18MiB。深复制、引用计数和缓存存活成本仍UNKNOWN，须看实际生成物和完整调用。C=1无通道复用。

norm原版本就按行缓存mean／rounded denominator，新增的是word→Rat共享，不能算成删除统计、sqrt或最终rounder。源码调用点计数RMS约4Rn→Rn+n+R，LN约6Rn→Rn+2n+R；这不是机器码成本或提速证明，现编译器是否已有hoist仍UNKNOWN。

若整体结果需要归因，最小比较是同形状conv tensor-cache vs patch（C=1/64），和同宽norm raw vs Rat-cache（rows=1/16），包含建立／释放并检查原转换是否仍在循环。主overall原协议与在途CI优先；不为这份纸面审查另开配置扫点。

## 当前决定

先保留整体模型验证队列；空输出预读取作为待原生核验风险，patch和norm必须用完整调用结果决定采用。未建立任何champion差距、整体10%收益或库升级许可。原始固定规范为官方accb82b6、Lean4.34，数学陈述与执行行为分开验收。
