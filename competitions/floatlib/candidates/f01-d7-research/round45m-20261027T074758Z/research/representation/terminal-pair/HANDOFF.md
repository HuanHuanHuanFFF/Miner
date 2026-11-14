# b6b7：结果对象删除已真实编译；完整成本未测

源`Kernel-terminal-pair-diagnostic.lean`230373B/SHA **b6b77553d49e968db27639b84f104783a9cf474ed963ec9cff7753a7adb17962**，片段3544B/893156f57b441ac02187952e2ed5a88b6268bcaa2495db22fc01d033807a6f11，08:08:34冻结后未改。

- CI40472418849/f83ab586，主控独立核40原件/2370657B，声明+Submission/VerifyFull两重放+8根仅三允许公理PASS。8根含四旧public及loopPair两投影、loopEmit_eq、terminal_eq_control；是完整pair输出等式，四public仍B2，无新publicBMM/fullgate/性能。
- 主控窄审真实control/terminal及各自loop：新emit无直接F2 malloc/heartbeat，3个of_bits仍在；6整数保存不变，单frame168→120B。普通steady显式FP栈由6×16B=96变8×4B=32，但双lane mulps/addps变双scalar链；**不是延迟或速度模型**，Array.push/NaN replay/析构/完整路由仍计入。
- 旧rawpair实际selectedcaller已无emitclosure，本稿只计真实F2删除，不计不存在的closure或64位UInt32即时装箱堆分配。真实spill布局也改变了旧6a0c停止前提，保留未来一次完整调用测量价值，不能继承旧计时或称已提速。
- 证据指向`research/originals-verified-40472418849.json`与`research/terminal-native-narrow-review.json`，旧selected链6份重哈希见本方`../history-bindings.json`。D独占Git/CI，本方不追加运行。下一在真实public集成或完整诊断caller下买成本；新域/闭合证明另验。
