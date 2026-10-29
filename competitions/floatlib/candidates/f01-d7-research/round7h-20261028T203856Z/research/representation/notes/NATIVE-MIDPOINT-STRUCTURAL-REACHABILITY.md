# Native64 midpoint：公开 profile 的结构可达性

**投入决定：406 条件没有淘汰公开 weighted-dot 形状；保留 native64 大路线，下一步观察实际输出指数／抵消／零项摘要，不凭宽指数标签推命中率。** 本阶段 2026-10-28 23:41:03 UTC 开始；共同截止仍为 03:38:56。只读原件与轻量标量结构计算，没有 LCG 样本、Tensor、inference、benchmark、CI 或候选改动。

**固定证据。** `development-broad/torchlean-source/lean/bench/ExactSuite.lean`，官方 commit `accb82b6e2adeda1b41a57a260d68fb3879c427e`，Git blob `f78b33ea5ac54b5210bcaa19a03b70e93f5c5f6d`，SHA-256 `99574dc2925d7db5cba56c4452cc1fc9b6fa27625e9ba81fde9f9b74db147530`，11479 B；D 原回执 20:51:54。新必要条件来自 Pro 第3报告 `8976c8cd…`，本次不重审其数学。

- **源码确定：** gen 的 normal 非零指数域为121…126，wide为87…126，sparse为零或121…126（25–32行）；三者初始绝对值均<1。wide 的权重仍用 normal 分布，sparse 权重保留零（45–50行）。bias=normal/256，指数域113…118且非零（53–55行），作为 bias×1 时 `H_bias≤243`。首层输入／权重／bias／padding 全处于 normal-or-zero widening 域；此保证不推广到后续层。
- **严格范围推导，尚非 Lean 证明：** 所有公开 weighted-dot fan-in 在4…1024，含 bias 的 n≤1025，所以 L≤11。权重 scale=RNE32(4/floor√k)≤2；生成值最大为1−2^-24，因此经单调舍入，权重仍<2，非零指数域至多127、idx≤126。任意有限 binary32 激活 idx≤253，所以保守 all-pair／shared-max H≤379，含 bias仍≤379，**H+2L≤401<406**。它保证该硬排除条件在这些域内不触发，不保证任何证书接受。此界只针对与 `wts` 相乘的 dot，不适用于 norm 的 x² moments；非有限／非零 subnormal 激活也可能先被当前 widening guard 拒绝。
- **源码形状：** MLP/NMLP 58–62、96–103、200–205、217–219行；CNN最大fan-in72，MobileNet depthwise9／pointwise≤16，见70–93、208–211行；Mixer token≤32、channel≤48、classifier≤768，见110–115、221–225行。把多维独立 draw 支撑集作笛卡尔积只得到安全包络，不声称每个组合都由某个 seed 实现。按 fan-in 精确标量 RNE 缩放计算，结构包络可收紧至 **H+2L≤397**；不依赖该更紧数值也已有401的排除判断。

另核固定 `ContractExact.lean` SHA `bddd6bd9caa19f9419e0e38cd553b109a7675fc710fdf82a6d6f7d0f2a4c8b1b`：60行 natW 对这些小整数精确；313/327行确认 Mixer `.gemm m k n` 的 dot 长度是 T，batch 不在该长度中。

首层可使用更紧的初始输入上界。下表最后一列是 `E≥H_upper+2L−278` 的充分阈值范围，**只保证满足 cell 宽度必要条件**；低于该阈值仍可能因实际 H 更小而通过。

| 首层 | fan-in（typical / scale / boundary） | bias计入后的 L | E 阈值范围 |
|---|---|---|---|
| MLP | 256–784 / 128–1024 / 255–785 | 8–11 | −13…−9 |
| NMLP | 128–512 / 64–768 / 127–513 | 7–10 | −15…−10 |
| CNN/MNet | 27 | 5 | −18 |
| Mixer | 先经过 layernorm | 按实际 token/channel | 不套初始<1界 |

**仍 UNKNOWN／不能推出：** 每层实际 E、midpoint 距离、抵消、guard 命中率、全部深层激活是否在 widening Domain、完整 caller 成本与计分收益。这里 H 是按值计算的 all-pair／分离最大值，或选用所证的上界；dot1 只要求传入 H 安全，并不会自动缩小它。若 caller 无条件传506，公开小输入仍会必拒；若只传379，对普通小输出也可能过松。batch只是更多独立输出，不乘进每个 dot 的 n/L。bias 在 k=2^r 时令 L 从r变r+1，B×4；边界 profile 的 k=2^r±1不可错当此跳变。当前 dot1 保守计所有配对，零项可抬 H；nonzero-only H 的更好结果不能直接计入其接受率。root 的 `(0,max32),(2^-30,2^-30)` 是泛域反例，不能当公开 sparse workload 的命中统计。

**唯一下一最小观察：** 在 D 已计划的 immutable-reference 观察中，按实际层／输出记录 `H_all,H_nonzero,H_bias,L,E_reference` 及正常／零／非有限分类，重点看 `H+2L−E>278` 的严格排除份额和 all/nonzero 差异；不另排 Tensor 或 CI。fused-ReLU 输出为零时，post-activation word 不透露 pre-activation E，须标 UNKNOWN，不能据此把该 dot 判成必拒。宽度过关仍需完整 caller 成本，不能当接受。若严格排除已覆盖主要成本，先改 H/半径或转 exact128；否则保留 native 证书等待实际成本，不做收益承诺。

**半径范围限制：** 406只否定当前 B=2^(H+2L−303)，不否定整个 native64。将 bias 另加，可用 dot 半径与最后一次 native 加法误差合成上取 power-of-two 半径；证明／额外成本／命中均 UNKNOWN，本次不改 dot1。

结构数据：`native-midpoint-structural-bounds.json`（72个层/形状包络，附每个fan-in的标量元数据）；生成器 `structural_profile_bounds.py` 只做整数/Fraction计算。tokens/cache UNKNOWN；没有读取新的冻结确认输入或结果。
