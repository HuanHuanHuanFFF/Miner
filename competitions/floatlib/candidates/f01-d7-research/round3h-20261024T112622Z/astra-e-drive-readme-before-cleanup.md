# FloatLib R11 网页6 Pro研究原件

三个原研究及附件回收均完成。这里保存97份解包/独立工件，另保留下载ZIP；原始NOT_RUN与失败记录不改写。当前研究状态请读项目本轮astra-status.json，勿把本页当作后续验收状态。

| 目录 | 原始成果 | 当前核验边界 |
|---|---|---|
| W01/original-extracted/R11-W01 | 完整证明接线审查、条件补丁、尾部地址反例、20文件 | CRC与18项payload哈希通过；original Kernel逐字节等于4bdd；网页未编译 |
| W02 | 零列/单非零列数学报告、分类脚本、Lean义务、日志与原清单 | 5项payload哈希通过；网页分类模型不是FloatLib执行器；未编译 |
| W03/original-extracted/R11-W03 | 短n两种lowering、完整源、38份固定版本公共源码、验证方案 | CRC与payload清单哈希通过；original Kernel逐字节等于4bdd；未生成目标C/asm/计时 |

W01条件termination补丁没有实际报错支持，未采用。真实908失败另由proof2修复，原4bdd和原网页包保留。W03的A/B是同一数学机制的不同代码组织，不能当作两个独立算法收益。A的5c5e重基构建预备位于项目f01-r11-crossrow-short-shared。

W02单非零列另有本地最早两个非有限位置推导和36576有限字测试；旧852曝光很小，暂不生成新Kernel。这些补充记录见项目astra-sparse-math.md和astra-sparse-screen.json，不替换本目录的网页原报告。

下载ZIP SHA-256：
- W01/R11-W01-evidence.zip: c02cb925299415fc1caa85ff5779350c6f2987155f6ebc527076ec6b882c6118
- W02/R11-W02-recovered-artifacts.zip: 3f0076c139170349a5b83f364279ff9e180aa520594b5e08d1e94e29908cb735
- W03/R11-W03.zip: 58cb49f49c6325a795348f7fd0736de3d6974cb69c6e6d1a3f34f8d8082b7da9

项目入口：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/astra-status.json
完整逐文件下载索引：同目录astra-web-deliveries.json。
上传往返字节核验：同目录astra-upload-roundtrip.json。
后续验收安排：同目录astra-next-validation.md。

已按用户要求用Codex内置浏览器下载；无需Library额外持久上传，没有启用分享。私人会话、截图和网页原始报告保持本地。完整gate、真实代码生成、性能与正式准入仍按精确候选分别确认。
