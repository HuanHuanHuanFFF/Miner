# 直接尾递归求和候选

冻结 SHA-256 `5187f6bb52fd18e70dd561e4221f2f376616729c23530d625a9f640928c75e90`，33505 字节。

仅替换 sum 为直接尾递归累加和带界 Vector.get，保持逐次舍入、顺序、+0 初始值与所有长度。标量与 bmm 保持官方起始参考。证明草稿沿 Fin.foldl.loop 同步递归；NOT_COMPILED，性能 NOT_RUN。

由 D 复制到自身目录后完整 gate、检查 C 中 scalar accumulator/direct loop，再执行官方完整计时；本包不作已通过声明。生成脚本在 research/astra-collab-20261021/build-direct-sum.py。
