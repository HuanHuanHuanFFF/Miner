# R23 producer current handoff

共同截止 `2026-10-28T15:06:26Z`；D 独占 Git、推送、CI。仅写本 producer 目录及 parent 授权的 `f01-r23-research-indexed-producer{,2}/`，不跑本机 Lean。按 `huan-open-research` 的实际产物／未闭义务边界整理；本交接按 `prompt-entropy` 保留可执行接口。

**14:58 修复更新**：原 af9b 在公共 run `40708758777` 出现一个 typing 错误：`packB_get` 的 `getD` 展开得到 `getInternal`，重写引理目标为 `getElem`。原件保留；新 `f01-r23-research-indexed-producer2/Kernel.lean` SHA `c2d24c27dd9b61381da8855bd6e427ac80699894e5acf116fb37fefa3a6534f0` / 255143 B，仅在两次 `rw` 之间加显式 `change ...[index]'hi = _`。新 fragment SHA `63d91b42960bc820e7e375aecb89351a549ff479dfa88513a42c8b97a327fa27` / 5102 B，尚待第三批公共验证。以下 af9b 是原始探针身份，不再表示待验当前版本。

- **待公共验收**：实际路径 `competitions/floatlib/candidates/f01-r23-research-indexed-producer/`。`Kernel.lean` SHA `af9b44d91366988170c645d864b63d212481c6f43c507d2db3590f98179d61a8`，255055 B；完整 cost1 250041 B 前缀逐字节相同，SHA `8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd`。五个 selected roots 为 `Submission.R23IndexedProducer.{point_pair,packRow_prefix,packB_prefix,packB_get,packB_read}`；manifest 绑定原 audit v8/hash `5b58eece...975`，状态 `NOT_RUN`。
- **实际 producer 接口**：`packB_get` 描述真正 `R22Pair8.packB` 内容；`packB_read` 逐 valid lane 提供 accepted `loop_lane.hread`。奇列右字段严格补零；只在 `2*g+c<p` 时绑定原 B 读取，不能把补零 lane 误绑到下一行。
- **待整合片段**：`ReaderBinding.lean.inc` 提供 actual cacheView、indexed within/finish；`NatTileBinding.lean.inc` 提供不带 word-fit 前提的 Nat loop/finish，以及 `tile_word` 将真实 tile 的全部八字段／second 分支／raw 回读接到 `NativeFinal.dot`。两份均 **NOT_RUN**。Nat-only 集成只需前一片段的 `cacheView_read`、`zero_lane`。B 的 `research/prefix/PackedReaders.lean.inc` 已针对 `tile_word` 接成四 reader 与最终条件消除；已静态互审，未继承 Lean PASS。
- **轻量反证**：`producer-model-check.json` 核对 15540 个形状／数组长度、1436820 个 valid lane 读取，含默认值与 103320 个补零字段；只支持有限索引模型。`p=3,B=[1,2,3,4,5,6],g=1,k=0,c=1` 中 packed right=0，越界列 raw=4，验证有效列前提不可删除。
- **下一决定**：收 af9b 原始 typing/replay/selected-axioms；若成功，再跑精确组合源及完整四义务。公共 BMM／完整运行成本／25轮采用门槛／正式成绩仍未获本轮证明，不改保留 B2。

原始成本参考 `round6h-20261027T211247Z/development-indexed8-first-summary.json` 仅是旧两种子发现样本：indexed8 四块 BMM/B2 `0.8851/0.9439/0.9467/0.9282`，whole `0.9685/0.9922/0.9934/0.9850`；不能从 BMM 改善继承整包采用。
