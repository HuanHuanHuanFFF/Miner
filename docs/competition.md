# 比赛与正式提交入口

本页提供机制资料的阅读顺序。执行范围和操作权限只在 [AGENTS.md](../AGENTS.md) 维护；官方线上要求在正式操作前重新核对。

## 官方资料

- [比赛页](https://conjectures.io/competitions/deflate)及 [公开 API](https://conjectures.io/v1/competitions/deflate)。
- [DEFLATE 官方仓库](https://github.com/conjectures-io/conjectures-optimisation-deflate)：`docs/MINER.md`、`miner/MANUAL.md`、`docs/VERIFICATION.md`、`docs/BENCHMARK.md`、`docs/SCORING.md`。
- [平台仓库](https://github.com/conjectures-io/conjectures-validator)：`docs/COMPETITION_API.md`、`submission_api/routers/competitions.py`、`competition_reads.py`。

当前可复现实验固定 DEFLATE 源码为 `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`。本地 `sources/` 是忽略的阅读副本，实际运行版本由 CI 准备脚本和回执确认。阅读固定源码不代表线上部署逐字相同。

## 输出与度量

接口为 `pub fn parse(input: &[u8], out: &mut [u32]) -> usize`。literal 为小于 256 的 token；match 编码为 `2^24 + (dist-1)*256 + (len-3)`，长度 3..258、距离 1..32768，允许重叠复制。公共 DEFLATE／Huffman encoder 由 validator 执行。

两轴越低越好：时间是每文件候选／配对 incumbent **总压缩时间中位数之比**，大小是每文件压缩／原始字节比例，再按文件和 corpus 等权。时间包含 parser 与 encoder，不能用累计秒数或累计字节比例替代。公共 stage1 为 28 文件、15,930,000 原始字节；正式评测还包含 held-out stage2。

Rust 经 Charon／Aeneas 重新提取，Lean 证明原始 `LZ77.Obligation`，并查询传递公理；已用的白名单为 `propext`、`Classical.choice`、`Quot.sound`。公共完整 gate、正式 gate、admission、Pareto 贡献和实际奖励是不同证据层。

## 提交与收益的定位

正式入口上传 `parse.rs` 和 `Parse.lean`，官方客户端和 API 文档说明文件限制、digest、hotkey 签名和幂等重试。身份、额度、费用及政策参数以操作前的当前记录为准。用户本地的既有提交包装器保存在忽略目录；相关私有配置不复制到本页。

已记录的实际案例：

- [fast3 的选择](rounds/round03.md)：正式 #453 通过 admission，有历史奖励和用户到账确认；当前余额／份额需另查。
- [H16-small 的正式校准](rounds/round06.md)：#474 两轴为 `6.708626656 / 34.118589459%`，正式 gate 通过但被支配，无该快照的支付份额。
- [最近中段实验](rounds/round09.md)：保守估值均不在前沿，尚未正式提交。

初始化时的旧额度、注册和政策观察只保存在 [历史快照](history/initial-state.md)。源码是否公开与最新前沿状态有关，零支付本身不能说明源码公开；必要时直接查询对应 submission 的官方 source 入口。
