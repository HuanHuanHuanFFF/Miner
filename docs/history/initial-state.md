# INIT_STATE

> 历史记录，保留当时的观察与故障原因。当前执行规则以 [AGENTS.md](../../AGENTS.md) 为准，工作入口见 [任务索引](../TASK_INDEX.md)。本文件中的阶段状态、授权与价格不代表现状。

核对日期：2026-10-06（北京时间）。阶段：初始化完成，等待指令。

**VERIFIED**＝本次直接读取官方资料/源码/API 或本机观察；**INFERRED**＝据此推断；**UNKNOWN**＝未取得直接验证。源码核对不代表本地 gate 通过或线上部署逐字一致。

## 1. 官方入口与相关仓库/文档

- **VERIFIED**：[比赛页面](https://conjectures.io/competitions/deflate)、[规则 API](https://conjectures.io/v1/competitions/deflate)。保存 snapshot **20800**，计算时间 **2026-10-06 01:20:33 +08:00**，policy `compression-policy-c255effb7d5afeef`；API 自报 `freshness=unknown`，这是已发布评分快照。
- **VERIFIED**：[专用比赛仓库](https://github.com/conjectures-io/conjectures-optimisation-deflate)，本地提交 `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`。交接阅读顺序：`docs/MINER.md`、`miner/MANUAL.md`、`docs/VERIFICATION.md`、`docs/BENCHMARK.md`、`docs/SCORING.md`。
- **VERIFIED**：[平台仓库](https://github.com/conjectures-io/conjectures-validator)，本地提交 `d24e86cab809e69d388417b9114ce8d34a2256fc`；提交接口见 `docs/COMPETITION_API.md`、`submission_api/routers/competitions.py`，源码公开条件见 `competition_reads.py`。API 文档含历史 DEV 示例，当前数值按本次官方 API 核对。
- **VERIFIED**：[公共 corpus](https://github.com/conjectures-io/conjectures-compression-corpus-1)；Bittensor 官方[注册规则](https://www.bittensor.com/docs/tx/burned-register)、[权重规则](https://www.bittensor.com/docs/tx/set-weights)、[注册源码](https://www.bittensor.com/code/pallets/subtensor/src/subnets/registration.rs)。网站通用数学证明的收费/赏金流程不能套用到 DEFLATE。

## 2. 输入、输出、正确性和评分

- **VERIFIED**：替换 LZ77 parser，接口 `pub fn parse(input: &[u8], out: &mut [u32]) -> usize`。输入任意字节，输出缓冲区至少与输入等长，返回写入 token 数。公共 DEFLATE/Huffman 编码由 validator 完成。
- **VERIFIED**：literal 为 `t<256`；match 为 `2^24+(dist-1)*256+(len-3)`，距离 `1..32768`、长度 `3..258`，允许重叠复制。
- **VERIFIED**：Rust 经 Charon→Aeneas 重新提取为 Lean；`Submission.parse_spec` 必须满足官方 `LZ77.Obligation`：所有合法输入下终止、不失败，token 数≤输入长度，输出缓冲区长度不变，tokens 解码恢复输入。证明覆盖 LZ77 层；完整 DEFLATE round trip 另测。
- **VERIFIED**：有 Rust 子集/外部操作白名单；拒绝 unsafe、外部代码、条件编译等。Lean 导入限 `Lz77/Slot/Mathlib/Aeneas`，禁止 sorry。官方 obligation 做类型检查，再查传递公理，只允许 `propext/Classical.choice/Quot.sound`。[验证文档](https://github.com/conjectures-io/conjectures-optimisation-deflate/blob/a356bbff18b60c4527fbcc85d5a28ef9c20214e0/docs/VERIFICATION.md)
- **VERIFIED**：两轴越低越好。时间：每个非空文件的候选/paired incumbent **总压缩时间中位数之比**，先文件等权、再 corpus 等权平均；大小：每文件压缩/原始字节比，同样平均。计时含 **parser＋公共编码**，不是仅 parser，也不是总秒数/总字节的比值。边界为时间比≤10、平均压缩大小≤40%。
- **VERIFIED**：gate 接受后另做 admission；只有合格 Pareto 前沿点可能获奖。当前 `local-global-improvement-space-log` 按前沿贡献分配，Pareto share=1、recent improvement share=0。以速度取得位置而压缩相等/更差时，选历史前沿参考点做 2000 次固定 corpus bootstrap，速度增益第5百分位必须>0（单侧名义95%）。[评分细则](https://github.com/conjectures-io/conjectures-optimisation-deflate/blob/a356bbff18b60c4527fbcc85d5a28ef9c20214e0/docs/SCORING.md)
- **VERIFIED**：比赛占该 validator 权重20%，基础 treasury 份额80%，主网 treasury UID=121；同 hotkey 多个前沿点只付最老的，未支付份额归 treasury。每提交累计上限3600 α，以链上 emission 记账并预测封顶；不是一次性固定赏金，也不保证占全子网 emission 的20%。

## 3. Benchmark 与 submission

- **VERIFIED**：公共 stage1 为28文件、15,930,000字节；正式 gate 要求 stage1＋私有 held-out stage2。分发字节是基准，重新抓上游不能保证复现；stage2 单文件结果不公开。
- **VERIFIED**：`just bench DIR` 仅测量；`VERIFY_CORPUS=corpus-stage1 just check DIR` 跑公共 corpus 完整本地 gate。流程为 intake→policy/static→重新提取→Lean obligation→axioms→benchmark。源码默认1次 warmup＋11次测量，保留配对顺序/哈希/时间；miniz_oxide 与 zlib 两个 decoder 做 round trip，并检查重复输出一致性。本次未执行。
- **VERIFIED**：当前 CLI `miner/submit.py` 向 `POST /v1/competitions/deflate/submissions` 上传恰好 `parse.rs`＋`Parse.lean`，各1..524288字节；sr25519 hotkey 签名绑定 competition、文件 digest、身份、时间，认证字段走 `X-Conjectures-*` headers。同 hotkey/同文件重试返回原提交。另有浏览器 session 入口，须关联 coldkey 并确认注册归属。
- **VERIFIED**：一次被记录的注册提供一次 accepted submission 额度，排队占用额度，gate 接受才消耗；gate 拒绝不消耗。**被接受但 dominated/统计不确定仍可无奖励**。这是平台数据库额度规则，链负责注册/权重/emission，链不直接检查 Lean。注册由 coldkey 付款，价格浮动；官方链源码拒绝仍已注册的同一 hotkey，“register again”不等于能立即重复注册它。
- **VERIFIED**：公开 GET 可查 status/report/admission/leaderboard/weights。accepted 源码在最新前沿上或尚未评分时 withheld；已评分且非前沿后可公开，baseline 除外。[平台 API](https://github.com/conjectures-io/conjectures-validator/blob/d24e86cab809e69d388417b9114ce8d34a2256fc/docs/COMPETITION_API.md)

## 4. 本地环境/依赖现状

**VERIFIED**：工作目录开始为空，无适用上级/本地 AGENTS.md。仅新增本记录、`evidence/` API 原始快照/回执、`sources/` 两个官方浅克隆；两个源码工作树无修改。未安装、运行 gate/benchmark、复制候选、优化/搜索、注册、读取钱包、签名、付款或提交。

| 项目 | VERIFIED 现状 |
|---|---|
| 已有工具 | Windows/PowerShell；Git 2.45.1、Python 3.14.0、uv 0.11.32 |
| Linux/Docker | WSL2 仅列出停止的 docker-desktop；Docker CLI 29.0.1 在，Linux daemon 不可连接；无已确认可用开发发行版 |
| 缺口 | PATH 未发现 Rust/Cargo、Lean/Lake/elan、just、Charon/Aeneas、bubblewrap；常见用户 Lean/Rust 安装位置也不存在，未全盘搜索 |
| 项目状态 | 无项目环境/工具链；stage1 未拉取，现有 legacy corpus-initial 不等于正式 corpus |
| 官方要求/pins | x86_64 Linux/Bash/apt、Python≥3.11、C构建环境、bubblewrap；生产限额用 systemd user；just≥1.58.0、setup 固定 uv 0.12.15；Rust nightly-2026-08-18、Lean/Mathlib 4.31.0、Aeneas nightly-2026.08.27-5b9dcf3、Charon rev 4ad295c1…（LLBC 0.1.245） |
| Windows 克隆限制 | core.autocrlf=true；70个 PINS 文件原始哈希均不匹配，恢复LF后70/70匹配；slot/src/parse.rs 应为symlink，本机是普通文本。保持现状，副本用于阅读，未认证为可运行gate环境 |

副本：`D:\CodingProject\Bitget\sources\`。证据：[API快照](../../evidence/deflate-competition-2026-10-06.json)、[查询回执](../../evidence/deflate-competition-2026-10-06-receipt.json)。依赖依据为专用仓库 `setup.sh`、`validator/verifier/config.sh`、Rust toolchain 与 Lean manifest。

## 5. 已确认事实与仍待确认的问题

- **VERIFIED**：已定位合约、提取/验证、benchmark、admission、提交认证/额度、奖励/公开机制，并固定此次源码提交与API快照。
- **INFERRED**：完整Linux克隆适合作为可复现起点；Windows阅读副本与stage1本地成绩不足以预测线上时间/held-out表现。
- **UNKNOWN**：线上实际 gate/compiler/incumbent/corpus 哈希、机器/timeout 与部署版本；API timeout 字段为null，未取得部署凭据。
- **UNKNOWN**：SN66 当前 finalized block 的注册价格/开关/容量、tempo、commit-reveal、实际权重/emission 与treasury身份。未独立查询链RPC，公开源码规则不等于即时链状态。
- **UNKNOWN**：本机原版模板的编译、Lean公理检查与完整gate结果。不存在本项目候选成绩或submission结果。

## 6. 初始化时的下一步（已完成）

**取得可复现的“未修改官方模板完整gate＋公共corpus baseline”结果**：在合适Linux环境保留LF/符号链接，固定源码/工具链/corpus身份，运行 `miner/template` 的公共corpus完整检查并留存报告。本阶段未执行，也未制定优化路线。

后续原版公共基线已经在 CI 37353587399 通过。继续研究时从当前任务索引选择最近一轮，不重复初始化阶段。
