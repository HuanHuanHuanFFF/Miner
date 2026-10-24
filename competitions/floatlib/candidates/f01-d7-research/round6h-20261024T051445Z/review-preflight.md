# R12 轮次工具适配只读预检

**结果：需按 R12 基线和 R12 采集边界适配后再运行。** 本报告是 2026-10-24 05:26 UTC 的只读预检；没有运行 prepare、CI、测试或候选代码，也未修改 R11、共享状态、候选、gate、bench、pins 或 reference。SHA-256 与证据范围见同目录 `review-preflight.json`。

## 当前边界

- R12 是 `2026-10-24T05:14:45Z—11:14:45Z` 的 360 分钟窗口，状态文件已显示 `R12-20261024T051445Z / ACTIVE`。共享 worktree 在 `codex/multi-track-floatlib`，HEAD 为 `8bc5d799ba5f20986dddb1921c0d2bedf46cf3a3`；工作区有既存 R11 未跟踪研究内容，本次未碰。
- 当前保留候选是 `f01-d11-bmm-combined-classifier`，SHA `6c2d394d…fa4277d`；评分基线须是这个 6c2d。估算器匹配控制仍是 `f01-r8-combined-result-guard`，SHA `41bce485…cf9ce9a7`。
- 所有评分组必须用原 full gate、25 轮；每组候选相对 6c2d 的整体归一化比值 `≤0.97` 且收益 bootstrap `p05 > 0`。三组均须完整通过：一个无 observer 的干净 D，及 freeze 后两组此前未见的新输入。每份 full 计划至少包含 `[41, 6c2d, new]`，以便保留估算器所需的同 runner 41 对照；41 不再充当 R12 评分基线。
- 现有 `champion-time-estimate.json` 的 6c2d/冠军数值受 R11 `retained-estimate-freeze.json` 约束。新 6c2d/41 样本可以作为原始对照证据，但不能因此重校当前 6c2d 数值模型。若 fresh champion digest 与冻结模型不同，应单独记录并走审阅的 re-anchor 路径，不能静默改写。
- 用户给出的 05:21 UTC 官方检查为 champion 285、HEAD `4b7e8384…`、公开 suite `a16494e9…`。本地 `current-official-snapshot.json` 仍是 02:23Z，且 R12 `development-status.json` 中 `official_refresh` 仍为 `PENDING`；这份本地快照不能替代 05:21 回执。由 Root 将新鲜官方原始回执、时间和哈希接入唯一状态；本 reviewer 不更新状态。

## R11 工具最小迁移表

| 工具 | R11 不能沿用的接口假设 | R12 最小适配与保留项 |
|---|---|---|
| `prepare-plan.py` | 要求状态 ID 为 R11；要求 41 出现在 scored plan；`comparison_baseline=41`；写 R11 publication label，并修改共享 `suite-plan.json` 与 `development-status.json`。 | R12 版本从本目录的 `round-plan.json`、`selection-policy.json` 取 round ID、评分基线 6c2d 与控制 41；强验两个精确 SHA。每份评分 full plan 必含 `new + 6c2d + 41`，用 `comparison_baseline=6c2d`，将 41 单独标记为 `estimator_control`。R12 的计划/冻结清单只落本轮目录。共享 suite-plan 指针和 state 由 Root 协调写入；本 reviewer 不调用此脚本。`capture_codegen` 仍须进冻结计划。
| `freeze-cohort.py` | 调入 R11 `final-choice.py`，该脚本绑定旧的一次性选择回执和 `D933`；`baseline` 固定为 41；只读取候选与 41。 | 去掉 final-choice/D933 依赖。只接受按 R12 规则相对 6c2d 首个合格、无 observer 的 clean D；在 D 冻结时绑定新候选、6c2d 与 41 三个精确源及三者测量顺序，再冻结两个未见 seed。保留完整 suite/generator、commit、工具和 D/A/B 身份绑定。
| `verify-three-groups.py` | `BASELINE_SHA`、baseline name、round-plan 对照都固定 41；测试夹具只有 `[candidate,41]`。 | R12 的局部统计基线改为 6c2d；每个 D/A/B 包仍核验并要求 41 完整 full gate，但只用 `new/6c2d` 配对计算阈值。三者都须精确 SHA、25 轮、同 suite/verifier、成功终态；冻结顺序必须是三源排列。输入多样性、每组独立接受、失败/慢组保留与冻结后二次复核照旧。`adoption-guard` 中 0.97/2000/bootstrap 逻辑可复用，但它的调用 baseline 参数及采集识别需绑定 R12。
| `adopt-three-confirmed.py` | `BASELINE` 和写前状态条件都要求当前源仍是 41；R11 以 41 作本地基线。 | 写前现任源/状态条件改为精确 R12 baseline 6c2d；新候选只在三组均通过相对 6c2d 的原门槛后才可进入 adoption。41 仅是估算器匹配 control/anchor。任何估算更新须按 R11 freeze 和原估算器使用同 run 的 41 对照；本轮单纯诊断/新 6c2d 控制不能修改当前数值。采用与 state/dashboard/model 写入仅 Root 执行。
| `execution-binding.py` | 本地路径清单含 `final-choice.py`、R11 预声明与选择回执；执行清单尚未为 R12 新 post-MainFull collector 定义身份。 | 替换为 R12 `round-plan.json`、`selection-policy.json`、R12 冻结/验证/汇总工具和实际使用的 candidate sources/manifests；保留官方 runner、adapter、workflow、pins 的原始精确绑定。把 post-MainFull hook/抽取器及其实际调用代码加入 run-HEAD `EXECUTION_FILES`，并冻结 estimate freeze、anchor、estimator 源哈希。最终验证仍从每个 run 的不可变 HEAD 读 blob。
| `sync-ci-state.py` | 只认 R11 ID 和 `plan-*.json`；只按 `capture_codegen` 计划列表记录采集。 | R12 版只消费 R12 计划/dispatch，保留 `allow_private=false`、最大并发 2、重复 seed/run 拒绝和原始 artifact 哈希校验。state 更新由 Root 执行。不能只看 `sample_role=DISCOVERY` 判作 clean D：计划的 `capture_codegen`、summary 的 post-MainFull capture、profile 或实际 observer 任一存在时都要标为诊断，不能进入 clean D。
| `summarize-run.py` | 默认 `--baseline=41`，只输出候选相对一个 baseline 的评分。 | 评分默认改为 6c2d，复用 25 轮与既定 2000 次 bootstrap 口径；同 run 的 41 对照作为独立 `estimator_control` 字段保存，供估算器配对，不混作评分基线。摘要必须反映 source/kernel、run/job、suite、capture 状态；不能写回或重校当前 6c2d 模型。

`prepare-plan.py` 与 `sync-ci-state.py` 会写全局 suite-plan/state；它们不是只读审查器。R12 轮次工具应将 `round-plan.json` 中的时间、权限、`allow_private=false`、并发上限、baseline 和 model-freeze 当作运行时输入；不能把 R11 常量改名后当作通用工具。

## post-MainFull 采集边界

R11 `public-suite.py` 在 `capture_codegen=true` 时调用 `capture-codegen.py` 包住原始 `gate.py` 子进程。R11 的 wrapper 在 `[statement]` 事件观察真实编译输出，并在 transient `upper` 被 gate 清理前有界复制对象；`nm/objdump` 分析留在原子进程结束后。不能把“copy 时点”误推迟到 25 轮之后，因为 gate 退出时对象会被 wipe。相反，statement 时复制会带来潜在 observer/cache 扰动，所以 R11 自己也把这类 run 限为诊断，不用于独立确认。`f01-word-tensors/ci-diagnostics.py` 产生的诊断重放对象不是原计时 gate 对象。

R12 post-MainFull wrapper 应采用这个两阶段边界：在原 gate 的 `[statement]` 成功事件中，等目标 MainFull 已 build 后，对该计划中**真实最后候选**的 `MainFull`/`Submission`/`BenchSuite` C 与 object 做有界只读 copy，记录来自本次 source commit 的 Kernel SHA、候选和 object SHA；必须在 `gate.finally` 清理 transient `upper` 前完成 copy。随后只对私有副本在原候选完整 25 轮测量结束后运行 `nm/objdump`，不可重跑、重编译或改写 gate/bench/compiler flags。copy 可能扰动计时，因此该 run 的完整 gate 数值可保留作带观察器诊断样本，但不得用于 clean D 或独立确认。

诊断 plan 必须带 `capture_codegen=true`，并由 plan、summary、原始 CI receipt 与 run-HEAD execution binding 贯穿记录；即使 copy 缺失/失败，依然不能把该 run 误标为 clean D。只有之后无 capture、无 profile 的完整 D 才能冻结为 clean D。确认 A/B 的 plan 与运行必须关闭所有 observer。采集只能是诊断证据，不能改变原 gate exit/verdict、25 轮或计时字段；失败、未知与慢结果原样留存。

新增回归夹具至少要证明：(1) 在原始 `[statement]` 目标事件内、对象 wipe 前有界复制；(2) `nm/objdump` 在原 25 轮完成后仅读私有副本；(3) 仅处理真实最后候选且 source/object SHA 与本次 run 匹配，找不到/不匹配时 fail closed；(4) `capture_codegen=true` 的 run 无论 capture 是否成功都不能成为 clean D，A/B no-observer 由冻结计划与回执验证；(5) observer/工具失败不篡改原 gate exit、verdict 与计时证据。

## 需要失效或重写的 R11 夹具

- `test_final_choice.py` / `final-choice.py`：仅适用于 R11 的 `D933`、6c backup 一次性选择。R12 不导入、不迁移 D933；改测 R12 的“首个干净且相对 6c2d 达标的 D”，并拒绝 capture 诊断样本。
- `test_verify_three_groups.py`：`BASELINE` 是 41，fixture plan 只有 candidate 与 41。扩展为 candidate/6c2d/41 三源，阈值只针对 candidate/6c2d；给 41 做独立完整控制验证，保留顺序、源哈希、runner/head、shape/generation 与失败组反例。
- `test_adopt_three_confirmed.py`：初始 view/state 被固定为 41。更改为当前 retained source 6c2d、anchor/control 41 独立存在；覆盖不能用 41 取代评分基线、不能对未采用的 6c2d 新 control 重估模型、只在完整三组证据后才允许 Root 的 adoption 路径。
- `test_outer_diagnostic_capture.py`：当前只测旧 statement 内嵌诊断、工具超时/异常与 adapter 行为；不能验证 post-MainFull 时间边界、最后候选实际对象及其 source/object 哈希。增加上述边界夹具，不把重编译的诊断对象当作原计时对象。
- `test_prepare_state_atomic.py`：原子替换/并发修改的通用回归可参考；R12 不能因此授权 reviewer 写 state，测试输入和目标 round ID 仍须改到 R12。

## 结论与后续检查点

只读预检通过；**工具迁移尚未完成、未做候选性能或 codegain 判断**。Root 落地 R12 工具和 collector 后，reviewer 可按授权只读检查精确接口、运行 HEAD 的执行绑定、post-MainFull/source/object 证据、clean D 分类和无 observer 确认组；不得重复完整回归或改写状态。完整哈希、观察时间、边界和本次未执行项记录在 `review-preflight.json`。
