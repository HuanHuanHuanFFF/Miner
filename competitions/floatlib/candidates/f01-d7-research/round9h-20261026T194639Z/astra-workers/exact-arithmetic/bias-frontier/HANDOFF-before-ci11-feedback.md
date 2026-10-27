# 最新决定：原 seed 公共源可验证，资源改稿仍 HOLD

CI10 40425497337/e0cee877 两独立前缀退出0，5.284/5.905s；运行中scope cap均4GiB，采样峰1.423/1.450GB，无oom_kill。原始quotient完整进程已完成，未复现旧OOM；该helper没有新private根的整模块重放/公理审计，不能当1180或公共证明闭合。16原件精确绑定见prefix-review-40425497337.json，root另核全部138份。

R已释放**原seed路线验证HOLD**：下一直接 public-proof-review1/Kernel-direct-bias-public-v1.lean（fa6529…，255311 B）的statement＋48根＋真正MainFull诊断；2177 math接口仅为定位备选。不增加逐个Nat/PostBias前缀。7b03与conditional70d4继续HOLD，不改已通过该进程的原quotient。新公共源目前仍NOT_RUN，不造第3proof/source版本；实际反馈到即优先处理。

# DirectBias：完整公共出口尝试，先等 quotient 独立诊断

**编译优先副本**：`public-proof-review1/Kernel-direct-bias-public-v1.lean` 255311 B / fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5；对应数学接口32332 B / 2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266。仅42 B证明修订限定嵌套mod重写目标，原版保留，48根及运行体不变，NOT_RUN/HOLD。

当前 R 授权窗口至 2026-10-27 02:28:21Z；旧 04:46:39 窗口为历史，不修改 D 窗口。无本机 Lean、Git、CI、第二运行体。

- **已实现但 NOT_RUN**：`Kernel-direct-bias-public-v1.lean`，255269 B，SHA `79e8f72155bb60ab042d48f687668021a6821a77bdf0449c85d6b55fac1df591`。实际 public MUL 已接冻结 DirectBias guardedMul，域外原 B2；四个完整规格根齐备。新增 typed high/q/exp → FastMul.roundP/core → FastMul.mul_spec，未假设全输入条件、未移入 R14 Model 支持。
- **最小模块接口**：`MathOutlet-interface-v1.lean`，32290 B，SHA `fae38339c987417e987bf3b320fc5cd7f9a05f725e5380de8364268f6fa19889`；导入已编译精确 B2 Submission，出口 `Submission.R19DirectBias.guardedMul_spec`。`HelperAudit-math-outlet.lean.inc` 自动生成 48 根，含 WordBias 六根。它只验证新数学模块，四个 public 操作仍 B2，不是性能候选。
- **预算与冻结**：seed 仅保留原始 Nat 依赖闭包 2018 B（未改原 quotient）；剔除未用 word 尾段。完整源只删 9 个无引用 B2 普通定理叶共 4814 B，155 个非证明声明逐字相同；逆补丁 `public-source-budget.patch`。原 1359 B 文件未改，嵌入只去最终 CR 并改 namespace。原静态 intake/policy/options PASS；Lean/axioms/replay/fullgate/timing 全 NOT_RUN。
- **必要次序仍 HOLD**：CI7 40415182202 的 scope OOM 已核实；旧 1180 原因保持 UNKNOWN。`#eval` markers 被固定 Lean 的 isolated streams 捕获，flush 是 no-op，不能定位首个定理。先 ImportOnly→QuotientOnly 独立进程；7b03 仍 HOLD、未并入本源。只有新证据定位 quotient 后才决定换 private proof。参见 `MARKER-HANDOFF.md`。
- **投入依据**：R/runtime sibling 已核 CI9 7489 完整诊断接受路径一 imul、无 FP/表读/call，bias 分支消除；仍有 shared frame。该代码生成证据支持验证公共出口，不是新 MUL 计时或采用。Jam b271 whole .998885/p05 −.010815 精确负结果继续停放。

完整清单 `public-v1-manifest.json`、`math-outlet-manifest.json`；生成器 `build_full_public.py`。新源码后续修复须另存副本，保留本版/hash。只做实际反馈所需修复，不改运行域/NaN 回退/资源上限。GRS 旁支推导已保存 `../grs-jam-lemma-paused.md` 并暂停。

条件性private proof迁移已备于 `public-resource1-conditional/`：完整255322 B / 70d4daff7016779dc2c4132d13aaac5d8e6658eefbd786d3ef29b338a7ee7ed1，模块32343 B / ed80ac813276d8453221f260d9748665955e8fc5f8ef5f8f0de3ec635cd0de62。精确7b03私有块，仅+11 B，同48根/运行体/公开假设，原静态gate PASS。仍HOLD：正控成功且原quotient确诊目标scopeOOM后由R/D放行；没有自动替换当前review1。
