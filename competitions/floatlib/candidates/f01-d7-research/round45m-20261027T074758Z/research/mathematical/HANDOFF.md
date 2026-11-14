# R20 C：数学资产冻结，SUM完整候选NO-GO

实际执行开始07:55:43Z，共同截止08:32:58Z不延长；08:00首判别晚20s，08:08接口于08:07:58落盘。仅本目录，无Git/index/CI/本机Lean/子agent；末段仍窄核至截止。

- **决定**：保守舍入吸收块可保持每步原语义，但D已见扫描模型8块跳6.74%却新增raw读20.85%，16块4.57%/13.28%；非计时/非官方Leanalign覆盖。本窗不造完整候选或性能CI。B2SUM本已有native Float32累加器/末次转换，不能把它误写成每步acc往返；新扫描、miss重读与acc.toBits也有成本。
- **接口**：AbsorptionInterface.lean 2838B / f4a36d59451ff81aee4925b40d53aa7250b0811879d34cec14d70f4c47892bd7，4根：fixedfold、条件scalar桥、upstream同号half-ulp、相同term序列orderedfold。SubRound.lean2815B / 3593c8e0608103cd8cd8a4bfffd7a4bcd190217abb729745196550e1e1a8101c，5根：除去商块后的below/above、正格点减小量RNE、普通shift及binade实际drop=g−1→2^24 carry。全Lean **NOT_RUN**；HelperAudit列9根，非完整候选。
- **原桥缺口**：raw guard→有效指数/尾数→两个log2分支→真实roundDyadic与sign选择→ExecFloat.add载体。scalar_sound仍是显式参数，不能算publicsum证明。root纸面审查确认g>=26(normal小项)/>=25(subnormal)，已纠正无偏指数e−127与存储指数e的术语。
- **有限证据**：31,056次命中＋1000个4项块0差异；96个正负acc/maxfinite/tie两邻点；69,696一般Nat＋29大gap binade例0差异。均精确整数转录oracle，非Lean/硬件/性能。
- **两个结构反例**：a=3f800001,b=[3f800000,bf7ffffe]，先mul再add=34000000，提公共a=34000001。A=[00800000,00800000],B=[33800000,3f800001]，dot后×2=01000001，先A×2再dot=01000002；所有输入/两端normal仍失败，必须控制中间product/prefix。详semantic-reuse-counterexamples.json，SHA1ef4175df1e368b9592afb5a55c12711bc76302feda91cd8e0ae59b18dfb2ad4。另binade反例(3f800000,b3400000)→3f7fffff；16个2^-26在acc1逐项不变，先合块却变3f800002。

精确清单manifest.json；保留原strictguard，不改覆盖口径、不复活旧DirectBias/GRS/零/NaN证书。root重复行/列复用已NO-GO，仅保留ordered_terms_eq接口。接续只补数学缺口或有新成本前提的路线，不由有限样本升级全证明。
