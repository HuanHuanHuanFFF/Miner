# 单一 Cross + Wide 组合准备

唯一组合已经冻结：**e5b279b326e404d210cf2fb254c11a1773f84d2ab39cc853b9172f428c69c2d7，254988 B，余1012 B**。基于冻结 28b819，把已 full PASS 的 5c5e 中 R11CrossRows 命名空间完整复制，再加最小 dispatcher/spec 接线；没有修改其中的循环、证明或形状阈值。

入口顺序为：原最外层 UnderflowZero；原 Wide guard；其 miss 内测试原 5c 的 p=2 Cross guard；最后走原 Direct/fused 路径。Wide 的 p>2 与 Cross 的 p=2 不交。此结构兼容不等于新组合通过了 Lean、完整 gate 或性能确认，以上仍全部 NOT_RUN。不同 seed 的旧数据也不能归因为 Cross 的净收益。

未裁剪组合为268635 B。已严格采用 Luna 最终审核的137段纯数学说明（12112 B），以及原注释外普通空白1535 B；另3 B普通空白属于最外层1039 B，额外保留。作者/许可/来源/运行义务共73段未选注释保持原文、顺序及哈希；没有使用较宽的16174 B旧池。live代码物理行与缩进逐字一致，完整原始1039 B后缀仍为b135a8ee。

reviewed-allowlist.json绑定原审核b5b80286和精确28b819；inverse-review.json保存每段原文与字节以及组合接线，可完整逆恢复。build.py默认读取冻结allowlist做只读重构验证，不调用启发式prepare，也不覆盖Kernel。新Lean/full/perf均NOT_RUN，历史dry-run.json保留落盘前阶段。

本准备不修改或延迟 28b819 的真实完整 gate。是否进入新组合测试由协调者依据929完整成本、剩余验证时间和00:46:25源码冻结目标决定。
