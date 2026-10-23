# Canonical dot scan 实际接线独立源审查

开始 2026-10-23 00:41:39 UTC，最多 35 分钟；主窗截止仍为 04:22:17 UTC。只写本报告和同名 JSON。未修改候选/R，未执行 builder、Git、CI、上传或安装工具链，未读取 future confirmation。 最终核对：2026-10-23T01:02:38Z。

**未发现可确定的静态源错误。** 实际 scanner 对原 A 行/B 列读取作 nonNaN 检查；dot 与 Packed10.finish 两条实际路线均在原生 NaN 终点后才调用它。新实际循环桥允许任意 native accumulator，但右侧 raw seed 精确限制为 `ofFloat32 acc`，再由导出 dot 专化到 +0。**新 4792 的 Lean、kernel/axiom/fullgate、C/asm 和性能均为 NOT_RUN；收益 UNKNOWN。**

## 身份、逆变换与旧 scope 缺口

| 对象 | 字节 | SHA-256 |
|---|---:|---|
| [精确4792](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean) | 195683 | `4792e9679c9607efd84a461a9d1ad7ca0e6bcb59d657fccacde8b96bf075f43c` |
| [父97f](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonfinite/Kernel.lean) | 174925 | `97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26` |
| [冻结scope0](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/negative-sources/canonical-dot-scan-scope0/Kernel.lean) | 195649 | `70386323c2a91b053f91f5312f3eeee0e477219771f09189fdb89d6353af10f8` |

从真实源独立构造 classifier/codec、scanner、canonical image、dot glue，以及两个相同 cold hook 与 dot proof，正向重建 4792 完整字节；逆向移除/还原得到精确 97f。四个插入块各出现一次；除明示范围外，scalar add/mul、sum、普通 dot 分支、tensor 地址/布局/次序和后续证明文本都保持。

4792 与旧 703 **只差 34 字节**，即在重新打开 `Submission` 后恢复 [Kernel:3316](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3316) 的 `open FloatLib.Floats Competition`。新 NativeFinal 的父作用域 active open 与 97f 完全一致。旧 703 是保存的**静态 scope 缺口**，没有被改写为曾经发生的 Lean 编译失败；本修复也没有编译回执。

## 扫描的是实际原输入范围

[Kernel:3212](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3212) 的 scanner 完整读取顺序为：

```lean
A.getD (baseA + k) posZero
B.getD (baseB + k * p) posZero
```

仅在 `k<n` 时读；A 命中 rawNaN 就不读 B，B 命中则不再读下一 k。全程 Nat，没有 USize 截断或新增长度上界。数组越界按原实际语义读 +0，空范围不读任何 word。

| 源接口 | 实际含义 |
|---|---|
| [Kernel:3222](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3222) `loop_true_iff` | 从任意 k 到 n 的每一实际 A/B 原 word 均 rawNaN=false |
| [Kernel:3273](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3273) `whole` | 上述 loop 从 0 开始 |
| [Kernel:3299](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3299) `whole_model_nonNaN` | 对每个 `Fin n`，两原 word 的 NativeBinary32 model isNaN=false |
| [Kernel:3673](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3673) `raw_nonNaN_native_nonNaN` | 用真实 codec/classifier 桥得到两原输入 toFloat32 的 isNaN=false |

`rawNaN_eq` 的方向是 raw classifier=Model classifier；scanner 的 `.symm.trans ha/hb` 正好得到所需 Model=false。codec 比较具体 UInt32/BitVec，不经 Float32 再反推原始 word。

条件是**所有实际读取的原输入非 NaN**，允许 ±Inf；不要求整个存储数组没有 NaN，也不要求乘积、accumulator 或 endpoint 非 NaN。未读取的别列/前缀 NaN 不影响条件。实际 B stride 必须是 p；定向反例显示，错误地按 p=1 扫描本应 p=2 的列，会把 `0xffc01234` 的原结果错当 canonical `0x7fc00000`。当前源两侧地址一致，没有漏掉 stride。

## 核心桥的种子与中间 NaN 范围

[Kernel:3681](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3681) 的关键量词和种子是：

```lean
(k : Nat) (acc : Float32)
(hscan : DDotNonNaNScan.whole n baseA baseB p A B = true)
...
Fin.foldl.loop n rawStep (ExecFloat.Binary.ofFloat32 acc) k
```

这里是**任意 native `acc : Float32`，不是任意 raw `Binary32` seed**。归纳中只对原 A/B 输入使用 nonNaN roundtrip；acc 和 product 依靠无 nonNaN 前提的 `R7W12.ofFloat32_add/mul` 保持 canonical native image。因此：

- `+Inf + -Inf` 可以产生中间 canonical NaN；
- `0 × Inf` 的 product 可以是 NaN；
- 两个 finite max 相加溢出为 Inf，再遇相反 Inf 也可以 NaN；
- 递归 native acc 可以已经是 NaN。

这些都不违反 hscan。源码没有把“原输入非 NaN”误写成“中间值/终点非 NaN”。[Kernel:3711](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3711) 再仅以 `Float32.ofBits 0` / `posZero` 专化，建立实际导出 dot 所需的完整 carrier equality，不额外断言结果一定是 NaN。

域外推广有最小反例：n=0，任意 raw qNaN seed `0xffc01234` 的 raw 空 fold 返回原 seed；native image seed 则是 `0x7fc00000`。非空且所有原输入非 NaN 时，qNaN seed 仍可保持原 payload；raw sNaN seed 还能变成 `0xffc00011`，而 canonical native import 仍是 `0x7fc00000`。**新定理没有宣称这些错误等式**，也没有对 arbitrary raw seed 使用同态逆推。

## 两处真实接线及完整 dot/BMM 前提

| 路线 | 新源行为 | 证明接口 |
|---|---|---|
| [Kernel:3724](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3724) NativeFinal.dot | 原 result nonNaN 直接返回；仅 NaN 时 whole=true 返回同一 native import，否则保留原 quiet-stop replay | [Kernel:3731](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3731)：原 normal proof、新 whole 桥、原 replay proof 三分支 |
| [Kernel:3979](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3979) Packed10.finish | 条件与 dot 在 A/B→Araw/Braw 重命名后逐字相同 | [Kernel:3986](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3986)：仍要求真实 `result = NativeFinal.dotLoop ... 0 zero32` |

`finish_eq_dot` 的整条声明/证明与 97f 字节相同，仍以 `rw [hs] <;> rfl` 连接同一表达式。这里不允许把任意不相关的 result 塞进 finish 后无条件声称得到 dotSpec。实际传入的 native lane/result 与 dotLoop 的 equality 由原 lane/tile/address 链提供，接口未动。

[Kernel:3993](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:3993) 的 finish_eq_fold、[Kernel:4014](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4014) 的 lane finishing、[Kernel:4218](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4218) 的 tile_finish 到 [Kernel:4297](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4297) 的 core refinement 保持原链。小维度 [Kernel:4597](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4597) DirectSmall 仍调用 NativeFinal.dot；其余 packed 路线使用实际 finish；[Kernel:4629](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4629) 的最终分流及 bmm_spec 仍使用原 shape/address/order 证明。没有只改一条路线，也没有为 BMM 偷加全局数组长度或 nonNaN 前提。

namespace 栈均闭合且无冲突：

| namespace | 行号 |
|---|---|
| 全局 DWordNaN | 3168—3203 |
| 全局 DDotNonNaNScan | 3206—3311 |
| Submission.R7W05 | 3318—3405 |
| Submission.R7W12 | 3409—3588 |
| Submission.NativeFinal | 3591—3750 |

## 公共数学已验到哪里

本次直接读取 W12c 原始 source snapshot、实际 returncode 和日志，没有只采信审计报告的 PASS。公共 host 精确 SHA 为 `173a091ecfa2d6ae7c3c048459e570cbffed4098d2a5ce70af3d2da6afa5c911`：**公开 60f 仅插入未使用的证明声明**。其 increment `e2e2ce789b087824239d2b6ae52ac6f8e4620c7d36bb1ea1fc00c0c09b40f218` 与本地 minimal61d 在去注释/空白后的 proof text 相符。

[Kernel-attempt2 原记录](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W12c/original-extracted/R7-W12c/logs/Kernel-attempt2.json) 和 [KernelDiagnostics 原记录](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W12c/original-extracted/R7-W12c/logs/KernelDiagnostics-attempt1.json) 都明确 exit0，snapshot SHA 与各自记录一致，没有 raw error。诊断源中的四条 closure assertion 确实量化 `∀ a b : Float32`，没有 nonNaN 前提。41 条原始 axiom 报告与精确要求名称集合相同，只有 propext、Classical.choice、Quot.sound。

这验证公开 host 上可复用闭包的真实命题边界，**不验证新 4792 的 classifier、scanner、实际 Nat 归纳、dot/finish 接线或完整义务**。不能将公共 60f 的 unused-proof 接受继承给本候选，也没有把普通 Lean 接受说成新 kernel/fullgate。

## 小模型、源级成本与首个外部检查

仅执行 **20 个手选 word/address 模型**，使用已有 oracle 的 AST 函数；未重跑 807 域。独立 masked-word 分类、从 k 开始的 suffix 范围检查相符；16 个 whole=true 用例满足实际 seed 限制的桥，14 个实际 +0 导出用例与完整 raw fold 相符。保留三个错误 raw-seed 推广反例及错误 B stride 反例。

模型还覆盖 ±0、空输入、Inf invalid、finite overflow 后 opposite Inf、任意 native canonical NaN acc、越界 +0 与“默认 +0 × Inf”。模型中的 standalone scan trace 表示**若调用 scanner 的读取**；normal endpoint 的真实源分支扫描数仍为零。这不是 Lean/硬件执行或形式证明。

源级新增成本边界清楚：

- normal endpoint：不执行 scanner；
- whole=true：额外读/分类 2n 个原 word，随后省掉旧 replay；
- A 在 k 首次失败：读 2k+1 个 word；B 首次失败：读 2k+2 个；之后仍重启原 quiet-stop replay；
- 原完整 native pass、packed preparation 和原 result import 已有成本不消失。源码使用 Nat/getD，没有据此宣称零分配或实际时间收益。

下一次应在**精确 4792 全文件**先看 raw classifier/codec、scanner 的 Bool/termination、whole_model_nonNaN、三条新 dot bridge 的递归 rewrite/roundtrip/Fin.foldl +0 化简、dot_eq 的 hscan 分支与 finish_eq_dot 的定义等价，再完成原版 statement/kernel/axiom/fullgate。实际 C/asm 与完整配对计时之后才可决定保留；当前均为 **NOT_RUN / UNKNOWN**。

