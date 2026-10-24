# R12 采集接线只读审查

**结论：1224001 的冻结接线与源码哈希匹配；采集器在有效 R12 配置下只启动一次原 gate。存在三处 fail-closed/证据完整性加固点，当前运行尚无本地 artifact，须在终态回收后再确认实际对象。** 本审查只读，未运行测试、CI、gate 或写入其他文件。

## 当前执行与冻结身份

- 状态文件确认 1224001 → run `40067286343`、source `c2d92ffb0a92888a39388145a41d1f8def38071c`，计划顺序 `[41, 6c2d]`，6c2d 是最后候选且单独 `capture_codegen=true`；当前仍 `DISPATCH_IDENTIFIED_WAITING_TERMINAL_COLLECTION`、`active_ci`，对应本地 run/artifact 目录尚未出现。
- 1224001 的 plan SHA `c01a8685…5a5077` 与 freeze `request_sha256` 一致。freeze 绑定 D7 wrapper `926e0e72…c12d90d`、R12 helper `d15aa6da…58b1ef7`、legacy fd17 `fd17f35a…df9078b`、public-suite `86084d93…ca24`；我从 `c2d92` commit tree 复核了这四个 blob，均与 freeze SHA 相同。`public-suite.py`、官方 gate/bench/pins 没有为此接线改写。
- 1224002 → run `40067469469`、source `5da1dc3fe0c978c249c9d989c3933a91c893ac6e`，状态 `TERMINAL_COLLECTED_SUCCESS`，但 verdict 是 `statement_pass=true, full_gate=false, stage=statement, exit_code=0`。这是 statement 诊断；不提供完整证明或计时结论。

## 采集路径与边界

`public-suite.py` 仅对计划中 `capture_codegen=true` 的 full-gate 候选调用共享 D7 `capture-codegen.py::run_gate`。共享 wrapper 从冻结 `suite-plan.json` 读 `r12_mainfull_capture`，核验 round、候选 flag、传入 Kernel SHA、R12 helper SHA 与 legacy SHA 后，调用 R12 helper；R12 helper 再 hash-check fd17 legacy，并只替换 `_snapshot` / `_disassemble` 两个回调。原 `argv/cwd/env/log_path/timeout/output/kernel` 直接传给同一个 legacy `run_gate`，没有修改 official gate、bench 或 compiler flags。

fd17 legacy 子进程只启动一次；原始 stdout/stderr 以 byte tee 到 stage log，非零 `returncode` 原样返回，timeout 会 kill/drain 子进程组并把原 `TimeoutExpired` 连同记录抛出。delegate 已开始后 wrapper 直接返回/传播，不会回退再跑 gate；只在 delegate 前 setup/hash 失败时，走原 legacy 路径单跑一次，并标 `UNKNOWN`。R12 `_snapshot` 在 `[statement]` 事件对临时 upper 做有界 copy；`nm/objdump` 在原 gate 退出后对私有副本运行。代码路径未发现重新编译或二次 gate 调用。

R12 `_snapshot` 先读 `lean/work/Submission.lean` 并要求其 SHA 与本候选输入一致，然后只从本次 `.sandbox/layer/upper` 取 MainFull；不从 shared cache 回退 MainFull。它记录 MainFull/Submission C、trace、ELF object 的原路径、`build_origin`、字节数及 SHA，并要求两者均具 C/trace/object；object 在 artifact 外私有暂存、分析后删除。BenchSuite 缺少 upper 产物时会明确从 `lean/.lake/build` 读 shared module。`benchFull.trace/.hash` 如存在会保存，记录的 `final_link_identity` 明确为 UNKNOWN。

因此，采集数据足以支持“该 run 的候选输入精确匹配、该次 upper 中捕获了这些哈希对应的 C/trace/object，并对该 object 哈希执行了记录的工具分析”这一诊断范围。它**不能**支持“该 MainFull object 已被证明进入最终被计时的 benchFull binary”：最终 link identity 被明确留为 UNKNOWN，原始 ELF 也未保留，只保留 object SHA、C/trace、nm/objdump 输出。运行终态 artifact 收齐后还须核对 capture-record、compiled source、对象 SHA、原 stage log 与原始 verdict；当前 1224001 仍未到此检查点。

## 需要 Root 后续收紧的点

1. **R12 配置缺失可能静默走 legacy capture。** D7 wrapper 只有在 `GITHUB_WORKSPACE` 存在且 R12 配置包含当前候选时才设置 `config`；否则调用 legacy observer，不附 `r12_mainfull_capture`。若计划已把某候选标为 `capture_codegen=true`，但 R12 config 缺失/未列该候选或 workspace 缺失，summary 可能只有旧 collector 的 `CAPTURED` 状态而没有 MainFull 证据。当前 1224001 plan 的配置齐全，尚未观察到此情况。建议出现 R12 capture flag 时，缺 config/target 就跑一次原 gate并显式记 `r12=UNKNOWN`，不要把旧 collector 成功表述为 MainFull 成功。
2. **目标“必须是 plan 最后候选”仅由当前 plan 满足，代码未强制。** 1224001 顺序确实是 `[41,6c2d]`，且配置只列 6c2d；但 shared wrapper 只验证候选在 config 中，不验证它等于 `plan.candidates[-1]`。冻结输入当前正确；后续加 `name == plan['candidates'][-1]['candidate']` 的 fail-closed 断言，避免将中途候选称为真实最后候选。
3. **metadata 持久化失败不会总把状态降为 UNKNOWN。** snapshot 或 `_finish_record` 保存 JSON 失败时，目前主要是向内存 `errors` 追加文本；`record.state` 可能仍保持 `CAPTURED`，而 `capture-record.json` 缺失时 public-suite 只会输出空 metadata path/hash。它不会重跑 gate，但容易让摘要把“有捕获尝试”显示成“MainFull 证据已保存”。metadata 写失败应将 R12 状态硬降为 UNKNOWN，保留原 gate log/exit/verdict，再让 Root 的回收门拒绝 clean D/后续 adoption。
4. **诊断资格应由请求旗标决定，不依赖捕获结果。** 1224001 的计划行设置了 `capture_codegen=true`，符合诊断约定；即使捕获/metadata 失败也必须禁止 clean D。确认组关闭 observer。不要用 `record.state=CAPTURED` 作为 clean 判据。

## 回归日志与 manifest sidecar

已读既有日志但没有重跑：shared legacy capture selftest 标 PASS；MainFull observer 的 4 项及 d15 扩展 5 项均标 PASS（范围是 fake ELF / 静态边界，`actual_Lean_ELF_gate=NOT_RUN`）；dispatcher v2 为 4 tests OK；atomic 为 3 tests OK。早期 `dispatch-tests.txt` 保留 4 项因 Windows Temp 路径权限导致的错误，不能把它并入通过数或覆盖；v2 是修正测试工作目录后的独立回归结果。

1224002 sidecar 已独立核验：Base64 解出的原 manifest 1663B，SHA `c33f8a89…5a5f1ad`；run commit 的 manifest 1635B，SHA `77134a3e…7c033e`，与当前 LF blob 相同。两份 JSON 解码后的值相等，候选 Kernel 在 commit 中 SHA 为 `22ea9e26…18e5ac7`，与 plan/freeze 完全一致。差异是 Git EOL 归一，不是 Kernel 差异；`freeze-1224002.json` 保持原样，sidecar 单独保存 raw bytes 与实际 Git blob 身份。

后续 `prepare-plan.py::canonicalize_manifest` 会先保存原 bytes/base64 再规范成 LF，方向正确；但目前 receipt 写入 `metadata-eol-receipts/` 后没有加入 generated plan 的 `files`/freeze binding。未来 freeze 应把 receipt 路径及 SHA、原始 SHA/字节数、规范化 Git SHA 一并绑定，且仍以提交中的 canonical manifest 和 Kernel SHA 作为 CI 输入；不回写本次 1224002 原 freeze，也不把 metadata EOL 差异记成 Lean 失败。
