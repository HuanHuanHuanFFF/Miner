# 粗ReLU证书对本轮近榜模型的覆盖判别

状态：**源码调用覆盖 VERIFIED；无native计时或全Kernel新证明**。R主控首先检查R27粗精度ReLU符号证书是否能影响新近榜ResNet11/Mobile53，未先付量化、缓存或证明成本。

本轮读取固定官方commit `9d4640e4d92b7f29611643e54601d5a114dc70b1` 的 `lean/bench/ExactSuite.lean`（完整原件仅research/source-private）。`cnnLayers`中四个conv全部`false`，最后linear也`false`；`mnetLayers`中三个conv、两个depthwise和最后linear也全部`false`。`true`的激活发生在独立`.bn`层，以及ResNet的`.addSaved true`，不在对应精确dot入口。函数接口是彼此独立的全输入算子，不能从后续层的激活倒推出当前conv可丢弃负数结果。

R27证书的必要dispatch前提是`relu=true`，保证有限含bias精确总和严格负时返回+0。直接照搬到这两模型时，**目标dot调用覆盖为0**（这是当前公开模型源码的计数，不是缺测性能记零）。若忽略`false`，取conv结果-1、下一BN scale=-1即可得到本应+1而错误变0的简单接口反例；全输入正确性不允许假设模型里scale总为正。即使当前生成器的scale为正，BN另有bias，负conv也未必最终relu为0，且独立conv义务本身已先被破坏。

决定：不为当前ResNet/Mobile冠军目标安排粗ReLU证书native试验或producer大证明。已有证书数学仍保留，可用于本来传`true`的MLP/NMLP/Mixer线性层；这些分榜当前差距较大，另算收益和证明成本。若要重访，须出现真实relu-true dot调用，或合法且明确的新融合API；不能擅改官方合约、benchmark或借未来层约束。

本轮变化在于新公开强近榜源和官方实际完整模型调用；不是依据R27 FP-only负结果封死整数证书。A/B/C原卷积布局/精确表示研究不受影响。
