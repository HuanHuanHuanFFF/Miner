# R19精确算术：Jam17已闭合，首完整成本未达门槛

UTC 2026-10-26 21:58:41；ACTIVE，主窗截至10月27日04:46:39，冻结目标02:16:39。仅写本目录，D唯一Git/index/CI；保留B2/622d。

- **真正public源**：repair1/Kernel-jam17-public-repair1-parser.lean，254877B，SHAb2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff。40404258098/ba0602：四公开规格、Submission及VerifyFull整模块重放、40根allowed-only全部PASS；1234探针同项12根PASS。54原件逐字核验见verified-40404258098.json，旧f784失败原件保留。
- **真实成本证据**：codegen-404042/audit.json从BENCH_PLAN追到MainFull lam3。接受路径只有一前向及一反向转换，无旧U64第二reverse/subss/sar补偿、无快臂call/spill；上界选择、5组push/pop和16Bframe仍在。是诊断构建对象，非计时ELF，不据指令数宣称加速，不加signmask变体。
- **当前完整D**：40407333869/76b1e794/seed1927005，原fullgate/25轮；B2+b271+f84+41，无观察器。58原件已重哈希、两源各25轮fullgatePASS；whole/B2=0.9988850281，MUL1.0171211598，p05=-0.0108148042。见full-discovery-40407333869.json；精确b271运行版停放，不A/B、不换seed，保留证明。
- **并行bias新阶段**：root因真实cast/clamp残余授权30min，21:55:27—22:25:27。bias-frontier/Probe-direct-bias-v1.lean，235339B，SHA1180c82c69ded5619978a2673f47ce9ed6d94a80930099429fc0b7cd5b0044bd；14根，原静态gatePASS，已由D在40410895344/d6b76/seed1927006启动，结果待收。只选directP64，不建Jam32第二稿。优先关闭旧4307B seed实际编译UNKNOWN及postbias恢复；详情bias-frontier/HANDOFF.md。主b271反馈优先。
- **成本边界**：th0首D达标但A失败，根验收摘要确认不采用/不做B；只是可选机制诊断，不增原采用门槛。未读peer A原输入/逐项数据。prefix-decision.json的更宽共同量子证书仅新增3个SUM样本、BMM不变，停放，不推广成所有整数累加不可能。

下一动作：收b271完整D及bias1180关键编译/完整caller证据；有真实错误只修精确源，保留旧哈希和原日志。任何采用仍原D+A+B，未正式提交。不要重跑旧builder覆盖repair1；token/cacheUNKNOWN，本方直接CI0。


最新偏置反馈：1180在404108实际SIGTERM−15/31.3s、1byte空输出，无Lean错误，原因UNKNOWN。当前proof资源稿7b03/235350B仅改private数学、所有runtime/public头不变，但HOLD；D先跑404151/e23e49的逐声明标记+RSS/cgroup隔离，回执决定后续，详bias-frontier/HANDOFF.md。
