# CI1成本结果改变投入
原件evidence/41099255272/download-*/cost-profile/profile.json：6cells/36checksums完成，七入口互斥耗时占比conv76.2–79.4%、add4.3–5.6%、scaleShift11.7–13.1%、maxpool3.5–4.0%，不等于全模型精确占比（输出析构等未计）。这支持主攻convZero/共享support，add不再单独主投入。BN若可组合保留但需整模实测。
首候选49e5原gate79.29秒statement失败（2103多余rfl），无性能候选数据；修复d742cdd3/251900B仅删除5字节最后rfl、runtime未变，development/elementwise/candidate-v2.json。修复后不另占单次CI，可在后续Res核心候选批里组合验证。
真实runner17:36:45已结束并17:38:04完成cache/artifact/orphan cleanup，平台元数据仍in_progress，原字节都保留。独立执行终态复核后Root才释放实际计算名额，科学gate/计时要求不放宽。Mobile冻结dc610a60是下一批。
R请读原profile指导下一项；Reszero优先于更多小优化。Support缓存NativeOnly是独立大路线，先成本后证明，不使用任何冻结后确认材料。共享截止20:15:58。
