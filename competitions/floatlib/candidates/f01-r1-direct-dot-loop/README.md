# 直接尾递归点积候选

冻结 SHA-256 `cb09e9c6913100097f21ebdc5059345885bce090894f53f8f876377edad8fcab`；35211 字节。

继承 `f01-index-hoist-proof2` 的标量 add/mul、sum 与索引基址。只把 BMM 的通用 Fin.foldl 回调改为候选自身直接尾递归 dotLoop，保持从 +0 开始、k 从 0 到 n-1 的逐次 add(mul) 顺序和越界 +0 语义。无维度特例；零维度和任意 Nat 维度都在声明范围。

**证明为未编译草稿，性能 NOT_RUN。** 内部桥接 theorem 逐步展开 dotLoop 和 Fin.foldl.loop，按 n-k 递减；外层复用已验证索引等式和 referenceBmm_spec。若 Lean 在 dependent-if 化简或递归终止处失败，修复应在 D 的复制版本进行，不能把已有证明通过归给本候选。

最小检查：完整官方 gate；回收该精确候选 C，确认 dotLoop 是直接递归／循环、累加状态为 uint32_t，内层不存在 lean_apply 或 generic Fin.foldl 调用；再看十二类25轮完整配对结果。当前冠军同机比值 UNKNOWN。

生成入口位于 `research/astra-collab-20261021/build-direct-loop.py`。实际本地只执行生成与字节哈希核对，没有 Lean 或目标平台性能运行。待 D 复制后提交／派 CI。
