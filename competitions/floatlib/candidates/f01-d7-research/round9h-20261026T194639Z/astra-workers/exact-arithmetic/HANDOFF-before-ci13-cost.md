# R19 精确算术当前交接

R 当前授权窗口截至 2026-10-27 02:28:21Z；原 9h 截止留历史，D 窗口不变。只写本目录，无 Git/index/CI/本地 Lean/子agent。

- Jam17 b271 的真正 public 四规格、两模块重放、40根均通过；完整 D 40407333869 whole/B2=.9988850281、MUL=1.01712116、p05=-.0108148042，精确运行体停放，不换 seed。原件摘要 `full-discovery-40407333869.json`，原数学/代码生成资产保留。
- DirectBias 冻结 1359 B 运行体已由 R/runtime sibling 核 CI9 7489：完整诊断成功路一 imul，无 FP/表/call；仍共享保存栈帧。该输入四公开操作仍 B2，只是成本判别，没有 DirectBias public 正确性或性能结论。
- 新公共出口已写至 typed high/q/E → FastMul.roundP/core → FastMul.mul_spec。优先 `bias-frontier/public-proof-review1/Kernel-direct-bias-public-v1.lean`，255311 B，SHA fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5。最小 B2-import 数学模块 `MathOutlet-interface-v1.lean` 32332 B，SHA 2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266。48根含 WordBias 六根。原静态gate PASS；CI11 40428306094精确fa652全源VerifyFull−15/30.0s，输出1 LF，无scope证据/Lean goal，cause UNKNOWN。48根/重放/新public诊断未到达；既有2177单模块为下一最小判别。
- **CI10新决定**：ImportOnly/原QuotientOnly均exit0（5.284/5.905s），实时scope cap4GiB、无oom_kill；原seed路线验证HOLD已由R解除，下一直接fa6529公共statement＋48根＋MainFull诊断，2177只作定位备选。7b03/70d4仍HOLD、不替换原quotient。CI7 scope 确认 4GiB OOM；原1180/R14历史原因仍 UNKNOWN。固定 Lean #eval 捕获流、flush no-op，空marker不定位首定理。原字节与primary源码行号见 `bias-frontier/MARKER-HANDOFF.md`。
- 新公共源不依赖缺失的 R14ExponentShift；guard/product/finiteScale 重证，seed只保留未改Nat闭包，9个无引用B2普通定理叶删4814B，155非证明声明相同，逆补丁可复原。原v1与静态修订副本均保留，只有42B证明变化，运行代码/域/NaN回退不变。
- GRS ADD关键反方审核未发现合法反例；变量drop/fixed k=2,3,4推导存 `grs-jam-lemma-paused.md`，按R抢占暂停，不开第二运行体。

精确清单/当前状态以 `bias-frontier/HANDOFF.md`、`public-v1-manifest.json`、`public-proof-review1/manifest.json` 为准。下一决定：单独检查既有2177数学模块并抓原限额下资源，按实际error/OOM证据定位；不加前缀梯队、不猜修原quotient。B2仍保留，采用/正式提交均未发生。token/cache UNKNOWN，直接CI占用0。
