# R26 90分钟续窗：C2/C3 配对与 C4 proof2 静态审查

准备时间和精确文件对见 [frozen-pairs.json](frozen-pairs.json)。本记录是静态审查；三对均 **UNCOMPILED**，完整原版 gate、原 obligation、公理白名单最终输出与官方 round trip 全部待执行。性能取舍需要本窗新的原协议计时，不以旧计数否决 C2/C3。

## C2 fold-tail proof1

Rust 是上轮 C2 的逐字副本。新 Lean 保留完整 #658 父证明，只在 `Submission.U118_MAIN.back_loop_inv` 的循环体中补充 `p-1`、`p-1-d` 的输入界，再沿用原 `step*` 及 BackInv 分支证明。

原数学条件：`MatchAt` 给出 `d≥1`、`d≤p`、`p+l≤input.length`，`Dec` 给出 `p≤input.length`；进入旧 match 合并 guard 后又有 `w≥3`、`w≤p`、`d≤p-w`。这些足以使两个新增尾索引及其 usize 减法合法。成功分支仍执行原 `u118_same`，原 `BackInv.match` 从 `same_spec` 获取完整 Matches；失败分支仍执行原 `part_merge_spec`，因此解码正确性无需先证明新 guard 与原程序逐输入等价。

具体未验证阻点：新抽取的短路 guard 会增加 bind、输入访问和条件分支。父 `step*` 是否逐一消耗这些分支，以及原 `BackInv.match` 的隐式参数是否仍能从新假设匹配，必须由实际 Lean 构建确认。父 proof 使用固定 `i1` 的唯一关键辅助是 `idx_bang`（旧 token 索引，位于新 guard 之前）；其余 match 参数多由 assumption/scalar_tac 推导。此观察只支持试验价值，不支持 gate 通过。

## C3 deferred-extension proof1

Rust 是上轮 C3 的逐字副本。以旧 `C3-Parse-draft.lean` 为完整证明起点，仅把 `c3_write_post` / `c3_emit_step_spec` 区块替换为 C4 proof2 的同构区块并改名，保留 C3 特有 `l==64` 分支和 greedy loop 的局部 step 绑定。

原 C3 草稿和 C4 proof1 均依赖首次 `step*` 自动消费 cap；已观察的 C4 proof1 日志证明其停在 `let cap ← if rem<258 ...`。本配对显式用 `Std.WP.spec_bind` 得到 `cap≤258 ∧ cap≤rem`，恢复 `pos+rem+8=input.length` 和 `pos+cap+8≤input.length` 后再执行 `step*`。全部匹配字节仍来自原 `match_len_spec`；短提示和失败分支仍用原 emitter/literal 后置条件。

具体未验证阻点：C3 新 discovery cap 的内部 if 仍交给原 True 后置条件 `C12511!` 宏；该宏显式支持 spec_ite_cut 和通用 bind，因此静态上有处理途径，尚未实际构建。新 helper 后续 full cast、writer 值等式、fallback 和 greedy loop 是否均匹配尚待真实 gate。有限 native decode/同公共输出结果不关闭这些义务。

## C4 greedy-once proof2

Lean 为旧 `C4-Parse-proof2-UNCOMPILED.lean` 的逐字副本，Rust 为失败 proof1 的逐字副本。它只针对已发生的 cap if/bind 阻点；有相同完整后置条件，无新增 axiom、sorry 或 admit。原 stage4 失败不能用 warning 改写，也没有证据证明本 proof2 已修复后续 cast/writer/fallback。

若此次 gate 拒绝，应保留本冻结 pair 的字节和原失败输出，然后在本任务获准目录中另存修补版本与新哈希；不可覆盖上轮 proof1、草稿或原回执。原协议性能结论与正确性 gate 独立。

## 来源与写入边界

所有候选保留父 manifest 的原作者 hotkey 与 `references/round26-public-658/source-receipt.json`。Rust 均未改动；父 Lean、上轮草稿和失败证据未改动。准备器为 `scripts/r26-proof90-prepare.py`，只做轻量字节检查与文件构建，没有本地重型工具链、Git、CI、上传或资金操作。

VERIFIED：新文件字节、与上轮 Rust 的相等、父来源与静态修改范围。INFERRED：新增分支可沿用现有证明结构。UNKNOWN：三对实际 Lean acceptance、完整公共 gate 与本窗性能及份额。
