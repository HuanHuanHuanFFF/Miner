# R14：word-add 完整 Nat 边界、单比特 log2 与 carry/fraction

时间：2026-10-25T00:12Z。接 00:08 首份片段；总收据 `astra-word-add-fragments2.json`。

首份 alignment1 与 small-shift1 字节已保留；首选各自 **2** 版，仅将 `Nat.pow_le_pow_right (a := 2)` 改成显式结果类型，减少隐式参数名称依赖，定理陈述相同。alignment2 SHA `eaa89fa496e6dad3d82d6c14b18503c918cec02b43876c134cc851daaf3d08f9`；small-shift2 SHA `e3de8acf9ec5ec3434419e1c7a1b46c2a1b92bdef495bd0d4e6ff9e1ff07e585`。旧 t23/24 的 parity 展开修复仍为 biased-rne2/e9ab。

新增 `astra-word-add-bounds1.lean`，4499 B，SHA `c7fa39b51d238d0d5b99a7bed58dcf31f3a20b9da19e69c94ec447fe7dd5cfee`：

- normal 24 位尾数、gap<=7、同号或 gap>=2 下，N 在 [16777216,2164260735]，从而无 UInt32 对齐加减回卷。
- base=(同号?23:22)+gap，证明 2^base<=N<2^(base+2)，并得到精确 `log2 N = base + (N >>> (base+1))`。
- 24<=log2 N<=31，且 log2 N<=gap+24，故 t1..8。
- 若 carry<=1、elo>=1、ehi<=254、有序，完整 E=h+elo-23+carry 在 [2,256]。
- 同时提供 `%256` 后字段判断与实际 runtime2 **直接未掩码 `e-1<=253`** 的判定引理。看到 runtime2 已改用完整 e 判断，按实际源码集成，不把旧打包字段说明当现运行体。

新增 `astra-word-add-rounding1.lean`，1934 B，SHA `b8e6674548e9ad8a4d8fcfb948f85ab48056c576b3289ece1829ddd91b69bff7`：仅依赖已有 FastMul.log2_shift 与 R14NatNormal 定义，推广 rounded 的 [2^23,2^24] 界到任意非零 N 且 log2>=23；据此证明 `rounded>>>24 = carry` 和 `rounded%2^23 = mantissa-2^23`。不要求 N 可写成两个 24 位乘数，适合 add 的新 N。

所有片段仍 **NOT_COMPILED**，没有额外候选／CI。总片段大于可用源码余量；它们是可选数学库，不应整套机械拼接：small-shift 的 Nat 部分约 0.5K 可先接实际桥；alignment 辅助和旧 mul 共享证明可按实际引用裁剪到新版本。原件、负面结果、旧候选都保留。我的下一步核对新桥接口与固定源，不触碰开发文件和 Git/index。

路径基准：`D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/`。
