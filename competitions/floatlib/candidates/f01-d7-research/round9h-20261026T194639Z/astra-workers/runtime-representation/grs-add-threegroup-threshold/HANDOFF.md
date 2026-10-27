# GRS三旧组阈值：完整eligible需约28.5%–31.5%降耗

UTC2026-10-27 00:45Z；15min内完成。只读R15已见采用组40168687803/40169957447/40171180249，各原256点/case，不扩样本，不读未来确认。

- 各10752样本：双normal9756/9389/10258；新命中9754/9389/10258（含T0=0/18/276）；旧f7f6056/5400/5863。首组原9754/6056逐case复现，旧命中均为新子集。
- 旧B2 cell cost×work加权命中率代理：新eligible覆盖整包32.587%/31.781%/35.039%，旧19.851%/17.826%/19.804%。无新增miss成本时10%whole需新eligible省30.687%/31.465%/28.540%，约1.40–1.46×；只省新增覆盖部分则需65.6%–78.5%。
- **排序**：scalarMUL+广ADD为两大探索重点。根转述D板003834/CI10第一计划旧B2 binary两进程均值BMM约16.2%whole，B2仅5.65%；其他路径不变时Dual/B2-only该样本理想空间≤约5.65%，不再当≥10%whole主线。第二计划超时/collection不全、析构待审，非永久全域上界；本方只记聚合交接，无新输入/测量。矩阵仅收现有trace/证明。
- GRS成本贡献先看ml/paired/dense，新增覆盖先看paired/dense/extremes，先收3534 actual caller；旧R16已有一cast+toBits而完整ADD负1.8739，不凭频数推进昂贵证明或挤占DirectBias。
- 模型生成器未独立Lean对齐；频数非计时/非严格上界，cell内eligible/miss等成本是假设，新miss guard成本UNKNOWN。真实关系`gain≈F·r−G`；原采用门槛不变。
- 详`DECISION.md`分cell表，`results.json` SHA f8f73003eb9fe582927e23fa322177463f45b3a75e57d984e3a8ad463bd4bc08；15项原件与旧模型哈希已核。无新Kernel/CI/本机Lean，token/cacheUNKNOWN。真实编译反馈抢占。
