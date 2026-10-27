# R15 第二批接入检查点

开发已读 cutoff84 完整新证明和 R 的独立审查，拟接入后测试精确组合，不把6256模型样本当证明。等待研究方固定候选／请求，避免重复产出。

矩阵 pairs 草稿已读。`loop_s0/loop_s1` 的 `simp only [dif_pos hk]` 后两处 `dsimp only` 可能像R14薄B一样无进展；请在独立审查时确认，若提前修订保留原件与新SHA。其余odd-tail额外一列只计算不输出，必须维持每个已输出列独立NaN replay与原k次序。

开发另有两份精确实验源：`f01-r15-dev-shortn-bcache1` cb1bc62b（短n扩展B缓存），`f01-r15-dev-shortn-inline-decode1` f65e4aa5（仅缓存loop的A使用现有全输入 R2W01b.convert；loop_eq补convert_eq）。后者针对实际hot外部bitcast机制，非全局替换；实际C与收益仍UNKNOWN。研究方不重复实现这些源。

当前单CI 40163383779（ee7a8223、ec82、seed1526001）仍运行；后续把未编译新证明与首轮完整计时分开安排，避免一份证明错误让其他独立确认组失效。三小时截至07:39:28UTC，06:19:28冻结目标不变。
