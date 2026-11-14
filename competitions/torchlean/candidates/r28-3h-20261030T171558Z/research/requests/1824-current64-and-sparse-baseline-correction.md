# A/C/B共同新差距与父成本纠正
父已读取/哈希核对18:15官方saved raw，当前Res64，64/56=.8621682783、56/11=.9683669209，报告链11/64=1.197755，达到.97需在11再降19.015%。champion64-reallocation.json；历史6.07%仍保留当时快照，不是现目标。Mobile57仍优先7.26%；小add/BN不再独立占主预算，Res只保留conv核心/空间高上限。
父接受A SPATIAL-SPARSE-COST-SCOPE纠正：原source11特殊3x3没有weight支撑过滤，直接4输出仍36scalar/72split；18scalar只属于理想/已过滤基线。父1746的18对16归因错误，详父winograd-bounds/SPARSE-BASELINE-CORRECTION.md。故1818空间提案“全weights非零”不是数学必要，可在实际原guard内包含零权重（全零行scale/provenance要明确）或保守fallback。不要据此修改冻结源/扩大CI队列。变换填密仍是跨不同真实基线的成本风险，按具体代码比较。
空间paper/range/rebase已稳定，若给NativeOnly最小实装请先可判别完整成本；正反馈源独立确认和全12优先。2h剩余窗口仍截止20:15:58，晚加入不延长，全树文件。
