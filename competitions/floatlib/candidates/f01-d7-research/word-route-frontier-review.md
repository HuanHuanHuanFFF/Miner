# R7 当前组件前沿：807 残余标量冷路

本轮开始 2026-10-23 00:09:49 UTC，最多 45 分钟；主窗截止仍为 04:22:17 UTC。只新增本报告、`frontier-scalar-counts-807.py/.json` 与同前缀 verification JSON；候选、R 文件、Git、CI、上传均未改动。

**旧 60f 的完整回放次数已不能用作下一条标量路线的新增机会量。** 按真实 97f quiet-stop BMM 与真实 3d9 单遍 sum，计分域残余冷路为 **18,519 次**：NaN 选择 **10,053**，无 NaN 特殊输入 **8,466**。这包含独立标量案例；后者沿用已锚定的 807 统计。数字是一遍输入域的源模型调用数，**没有新二进制、时间份额或收益结论**。

## 精确输入与核对

| 组件 | 精确 SHA-256 | 本次用途 |
|---|---|---|
| 旧 `f01-d7-direct-nonnan` | `60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15` | 完整回放旧口径 |
| [97f direct-nonfinite](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonfinite/Kernel.lean:3114) | `97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26` | BMM 原始 mul 后 add，quiet NaN 后不再读取 |
| [3d9 singlepass-fused-proof1](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r7-sum-singlepass-fused-proof1/Kernel.lean:6094) | `3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576` | 首个原 rawNaN 精确修复一次，后缀只扫描 sNaN |

只读已暴露 plan，SHA `9cc5d7368749c369172b019d66bc4cd8455ae4323d0b9a175bd031f936e78622`，没有读取未来 seed。复用 S 的 AST 加载器及 R 已有 generator/oracle 函数定义；不运行它们的 imports/main。native 运算是既有“规范化操作数和结果”的 word 模型，**不是硬件 Float32 实测**。

一次完整有界运行 **110.19 秒**，低于 600 秒上限；未重跑该 807 枚举。所有 **70 个 tensor 案例 × 四份既有实际 Lean checksum** 相符；同时 **70 个旧模型 output-word SHA**、每案例旧 60f 调用计数全部相符。旧 word SHA 是模型字节锚，不冒充逐输出 Lean 记录。另对复用的 86 个独立 scalar 案例重新核对四份原始 checksum，共 344 项；未重新枚举其大域。

三份源的 add/nativeMul/mul 运行定义相同，TunedAdd、FastMul、LowScale、R2W01b、R2W01c 五个相关 namespace 的文本也一致。精确源哈希和文本块摘要保存在 [verification JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/frontier-scalar-counts-807-verification.json)。这支持沿用未改 scalar 入口的旧计数，不能继承新组合的编译或性能结果。

## 计分域：完整回放与残余调用分列

以下为 68 个计分 tensor 案例的一遍 checksum 输入域。表内“冷路”严格指这一次实际 scalar 调用的任一原始参数 exponent=255；“NaN 选择”指该调用的实际两个参数可命中 chooseNaN2；“无 NaN 特殊”是冷路中剩余的 Inf/invalid 情况。

| 调用 | 旧完整调用 → 前沿调用 | 旧冷路 → 前沿冷路 | 旧 NaN 选择 → 前沿选择 | 旧无 NaN 特殊 → 前沿 |
|---|---:|---:|---:|---:|
| sum.add | 14,939 → **320** | 11,512 → **320** | 11,393 → **320** | 119 → **0** |
| BMM.add | 18,797 → **7,365** | 16,204 → **4,772** | 13,659 → **2,227** | 2,545 → **2,545** |
| BMM.mul | 18,797 → **7,365** | 4,113 → **2,734** | 2,940 → **2,132** | 1,173 → **602** |

97f 的 [replayStep](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonfinite/Kernel.lean:3089) 每步先完整 `Submission.mul`，再 `Submission.add`。[replayLoop](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonfinite/Kernel.lean:3114) 在下一步读取前检查 quiet guard。全部 2,860 个 NaN endpoint 仅重放 7,365 步，省去的 **11,432 步已从本次残余数扣除**；不能再把它计入 scalar rawNaN 的新增机会。DirectSmall 仍调用 [NativeFinal.dot](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonfinite/Kernel.lean:4111)，Packed10.finish 使用同一 endpoint/fallback，均覆盖在上述计数中。

2,860 个终止事件可拆成：2,132 次乘法原参数选出 NaN；95 次无 NaN 的 invalid 乘法先产生 canonical NaN product；633 次无 NaN 的 invalid 加法。前两者的 product 都是 add 的实际 rawNaN 参数，因此 add 选择数是 **2,227**。不能用原 A/B 是否有 NaN，直接替代 add 的参数分类。

3d9 的 [单遍前缀](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r7-sum-singlepass-fused-proof1/Kernel.lean:6151) 在 5,046,844 个原输入 word 中做 5,035,572 次 native prefix add，遇到首个原 rawNaN 时精确 scalar repair **320 次**。之后还有 **10,952 个 suffix word、160 次 sNaN 替换**，由 [suffixLoop](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r7-sum-singlepass-fused-proof1/Kernel.lean:4963) / [R7W02.step](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r7-sum-singlepass-fused-proof1/Kernel.lean:646) 完成；这些读取/位操作仍有成本，**不是额外 scalar.add**。

## 原始 checksum 案例另列

下表四个 raw 案例不进入计分域残余总数。

| raw 案例调用 | 前沿 scalar 调用 | 冷路 | NaN 选择 | 无 NaN 特殊 |
|---|---:|---:|---:|---:|
| sum:check add | 21 | 21 | 21 | 0 |
| bmm:check add | 1,425 | 903 | 27 | 876 |
| bmm:check mul | 1,425 | 27 | 27 | 0 |
| add:check | 4,096 | 37 | 37 | 0 |
| mul:check | 4,096 | 25 | 25 | 0 |

逐案例数据保存在 [主计数 JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/frontier-scalar-counts-807.json)；70 个 tensor 案例和复用的 86 个 scalar 案例都带 timed 标志。每计时 pass 使用同一运算输入域，但本报告没有乘上 inner/轮数，也没有把调用比例当时间比例。

## 原 acc 已为 canonical NaN：实际优先级

807 中有 **3 次**首个原 rawNaN 修复发生在 native acc 已为 `0x7fc00000` 之后：两次右 qNaN 保留左 canonical word，一次右 sNaN 覆盖它。模型保留了具体案例、输出和输入索引：

| 情况 | 精确输出 |
|---|---|
| `[+Inf,-Inf,0xffc01234]` | `0x7fc00000`，不能直接返回右 qNaN payload |
| `[+Inf,-Inf,0xff800011]` | `0xffc00011`，右 sNaN 优先 |
| `[0x7fc00001,0xffc00002,0xff800003]` | `0xffc00003`，后缀必须继续找 sNaN |

BMM 还核了四个小边界，包含空 dot、`+0 + (-0×1)` 与两个后缀反例。`[(qNaN1,1),(sNaN2,1)]` 的结果是 qNaN1：第二个 sNaN 会先在乘法中 quiet，不能按原输入 sNaN 的全局优先级替换已 quiet 的 acc。`[(Inf,0),(sNaN2,1)]` 的结果同样保持第一步 canonical NaN。上述都是源模型定向边界，不是形式证明；本次没有发现前沿模型与旧逐 word 锚的反例。

## 下一条 word 路线的真实覆盖

独立计分 scalar 数据复用后：

| 残余来源 | 冷调用 | NaN 选择 | 无 NaN 特殊 |
|---|---:|---:|---:|
| 独立 add | 6,689 | 3,412 | 3,277 |
| 独立 mul | 4,004 | 1,962 | 2,042 |
| BMM add + mul | 7,506 | 4,359 | 3,147 |
| 单遍 sum 修复 | 320 | 320 | 0 |
| 合计 | **18,519** | **10,053** | **8,466** |

剩余冷路集中在 add:specials 6,689、bmm:specials 5,934、mul:specials 4,004、bmm:extremes 1,572、sum:specials 320；其他 cell 的本次对应冷调用为 0。这是输入域调用统计，不表示这些 cell 的时间都能消掉。

8,466 次无 NaN 特殊调用又分为 **7,634 个 Inf 结果、832 个 canonical invalid 结果**。其中独立 add/mul 为 3,215/2,000 个 Inf 及 62/42 个 invalid；BMM add/mul 为 1,912/507 个 Inf 及 633/95 个 invalid。这表明 native result guard 与 exceptional word 都覆盖大量同一批 Inf 结果，后续不能相加收益。已有 canonical-input BMM scan 也可能继续移除其中一部分；本报告没有把尚未组合的 scan 当已执行，更没有凭旧 671 endpoint 数扣除未知的剩余步骤。

**路线次序据此调整：**

1. 先完成当前 sum/BMM 组件的实际组合验证。旧 tensor NaN 选择机会从 27,992 次降为 4,679 次，不能继续拿旧 26.37% 整 cell 曝光说明新收益。
2. 后续 scalar 冷路优先复用现存 exceptional-word 语义探针，比较它与 NaN-only selector 的实际 proof/codegen 成本。NaN-only 覆盖 10,053 次，无 NaN 特殊另有 8,466 次；覆盖数较多也不证明更快，普通路径新增判断、常量构造与冷分支成本都需实际对象和完整配对计时。
3. 仅为单遍 sum 的 320 次 repair 再造邻近变体，优先级降低；后缀读取成本与 prefix native 成本不能被 scalar helper 消除。当前不新增候选，也不重试由旧完整回放数支撑的微调。

[已有 exceptional-word-probe](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-exceptional-word-probe/Kernel.lean:3941) 精确 SHA `17331a8b2ff3ddcced087d4165eaf5887620caf0e0051da70eb01800383cc04c`，175262 字节；逐字节保留 ad014 父源前缀，只追加定义/证明。其 addWord/mulWord 已有融合 rawSNaN/rawNaN 优先级和 Inf/invalid 分支，运行体没有 Option/rawChoose 调用；这不是新的机制发现。

[addCold_spec](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-exceptional-word-probe/Kernel.lean:4099) / [mulCold_spec](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-exceptional-word-probe/Kernel.lean:4112) 精确前提都是拒绝“两原指数均非 255”，不能扩到普通有限域；例如 `addWord(0x3f800000,0x3f800000)` 给 `0x7fc00000`，正确结果应为 `0x40000000`。该探针仍是 **NOT_RUN 的追加语义**，没有改变 exported scalar runtime，不当作已取得性能。后续应核验/复用已有声明，不重复造同语义 helper。

## 边界与复核入口

97f、3d9 和该 word 探针尚无本次完整组合编译结果。主枚举与七个微型优先级/顺序边界均为共享 generator/oracle 的有限模型，不能替代新 Lean、axiom/fullgate、实际 C/asm 或时间结果。地址按实际 batch/row/column 与 B stride 读取，807 全部在数组范围内；没有把 getD default、巨大 Nat/USize 维度的一般正确性从这些样本推出。

可复跑 [有界脚本](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/frontier-scalar-counts-807.py)，固定只允许该 807 plan 和 <=600 秒。脚本每完成案例保留状态，超时/失败保存已完成行和错误；本次单次运行完整结束。metadata 独立重查全部输入哈希、624 项既有 checksum、文本块链与已有探针前缀。新候选验证和收益仍为 **NOT_RUN / UNKNOWN**。

