# R14 经验与复现入口

|结论|证据与后续约束|
|---|---|
|整数化不保证提速|f958通过原版完整gate，但加法1.56213／整体1.18928；9038通过完整gate，但乘法1.29080／整体1.04714。以后先用已有证明的最小实现测完整成本，再投资额外舍入证明。|
|B复用有实际矩阵收益，但不能叠加组件百分比|177b矩阵0.84473、整体0.97271，未过既定0.97；9038矩阵0.80397，但整体仍回退。全部按精确源自己的首次D决定，保留负结果。|
|新bias数学证明的终止原因仍UNKNOWN|原Nat-only及q/r备选反复exit-15、无Lean诊断；当前runner未改compact父源通过。没有OOM事件/逐tactic证据，不将其写成数学反例或资源修复成功。|
|复用已验RSE、抽象模型层使具体乘法证明可验收|rseAny_eq＋roundShiftRightEven_toNat复用既有证明；core_model在8192下递归过深，拆成抽象Nat/Model字段lemma与短word桥后9038完整通过；未调大gate/cap或引入新公理。|
|源码层“调用”不等于实际分配／动态耗时|f958真实statement MainFull两份add函数未见lean_apply或lean_alloc；UInt/F32多个primitive是固定运行时inline。C静态站点数不是动态次数，也不是timed对象汇编；完整计时决定采用。|

[13批终态与决定](development-round-results.json) · [三项完整比较](README.md) · [失败D与模型冻结](development-NEXT.md)。本机未跑Lean/重型编译。网页四份数学原件保持NOT_RUN；完整研究资料单独公开范围仍待授权，原件留本地。
