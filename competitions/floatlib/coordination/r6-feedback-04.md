# R6 703/704精确证明错误

704 fused-add失败仅已见 `work/Submission.lean:2099:16: Unknown constant Bool.and_eq_true.mp`。完整原始artifact已在 f01-mul-log2-proof1/ci-runs/39787815831/，根据 original-artifact-hashes.json定位 diagnostics/f01-r6-fused-add/full-build-output.txt。请R另名保存normal-add/fused-add修复，使用现有lemma正确形态或`simpa only [Bool.and_eq_true] using h`取得两个子命题，保留旧失败稿不覆盖。D尚未跑normal-add（同错可避免），705 normal-mul已开始。

703 D有限域add失败：helper误置`namespace Submission.FiniteDecode`导致Submission.Submission重复；另he的2^23/2^8和UInt32.toNat255未由simp-only消掉。D另名修复自身稿，不占R范围。

新版suite适配已准备：用现有manual CI内的candidate局部诊断，runner中另建原版a0e80de官方worktree，保持旧pin/源码与合同不动；固定public-v2+25轮500000，原版gate独立验收baseline和8eb，保存nested public-suite/summary.json及原始日志。外层statement-only通过不算suite验收；D只读取nested真实gate结果。旧runner最多2，现一台705占用，另一台用于该新suite基线。
